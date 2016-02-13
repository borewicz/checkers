/*
 * RequestMovement.cpp
 *
 *  Created on: 13-11-2015
 *      Author: debian
 */

#include "RequestMovement.h"
#include <boost/lexical_cast.hpp>

RequestMovement::RequestMovement() {
}

RequestMovement::~RequestMovement() {
}

bool RequestMovement::action(Json::Value root, Server *server, Client *client) {
	if (!client->getIsConnected()) {
		sendResponse(shortJson("status", "not connected"), client);
		return true;
	}

	string timeStr = root.get("time", "").asString();

	if (timeStr == "") {
		cout << "Client movement error, no time" << endl;
		return false;
	}
	int time = boost::lexical_cast<int>(timeStr);

	const Json::Value movementJsonArray = root["movement"];
	int size = movementJsonArray.size();
	int movementIntArray[size];
	for (int i = 0; i < size; i++) {
		movementIntArray[i] = movementJsonArray[i].asInt();
	}
	Movement *movement = new Movement(movementIntArray, client->getColor(),
			time);
	if (server->game->movementValidation(movement)) {
		bool result = server->votingManager->addMovement(movement);
		if (result) {
			sendResponse(shortJson("status", "ok"), client);
			return true;
		} else {
			//to do what if addMovemment return false
		}
	}
	sendResponse(shortJson("status", "wrong move"), client);
	return true;
}
