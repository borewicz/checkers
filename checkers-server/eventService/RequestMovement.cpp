/*
 * RequestMovement.cpp
 *
 *  Created on: 13-11-2015
 *      Author: debian
 */

#include "RequestMovement.h"

RequestMovement::RequestMovement() {
}

RequestMovement::~RequestMovement() {
}

bool RequestMovement::action(Json::Value root, Server *server, Client *client) {
	cout << "client " << client->getNick() << " connect" << endl;
	if (!client->getIsConnected()) {
		sendResponse(shortJson("status", "not connected"), client);
		return true;
	}

	int time = root.get("time", -1).asInt();
	if (time == -1) {
		cout << "Client movement error, no time" << endl;
		return false;
	}
	cout << "time" << endl;

	const Json::Value movementJsonArray = root["movement"];
	int size = movementJsonArray.size();
	int movementIntArray[size];
	for (int i = 0; i < size; i++) {
		movementIntArray[i] = movementJsonArray[i].asInt();
	}
	cout << "tablica" << endl;
	Movement *movement = new Movement(movementIntArray, client->getColor(),
			time);
	memset(movement, 0, sizeof(Movement));
	if (server->game->movementValidation(movement)) {//to do wyjebuje sie
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
