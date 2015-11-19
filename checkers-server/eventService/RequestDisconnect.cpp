/*
 * RequestDisconnect.cpp
 *
 *  Created on: 13-11-2015
 *      Author: debian
 */

#include "RequestDisconnect.h"

RequestDisconnect::RequestDisconnect() {
}

RequestDisconnect::~RequestDisconnect() {
}

bool RequestDisconnect::action(Json::Value root, Server *server,
		Client *client) {
	cout << "client " << client->getNick()<<" disconnect"<<endl;
	client->setIsConnected(false);
	client->terminateThread();
	sendResponse(shortJson("status", "ok"), client);
	cout << "client " << client->getNick() << " disconnect" << endl;
	return true;
}

