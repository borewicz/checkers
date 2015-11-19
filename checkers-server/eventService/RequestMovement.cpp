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

bool RequestMovement::action(Json::Value root, Server *server, Client *client){
	cout << "client " << client->getNick()<<" connect"<<endl;
	if (!client->getIsConnected()) {
		sendResponse(shortJson("status", "not connected"), client);
		return true;
	}

	return true;
}
