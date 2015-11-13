/*
 * RequestMessage.cpp
 *
 *  Created on: 12-11-2015
 *      Author: debian
 */

#include "RequestMessage.h"
#include <ctime>
#include <boost/lexical_cast.hpp>

RequestMessage::RequestMessage() {
}

RequestMessage::~RequestMessage() {
}

bool RequestMessage::action(Json::Value root, Server *server, Client *client) {
	if (!client->getIsConnected()) {
		sendResponse(shortJson("status", "not connected"), client);
		return true;
	}

	std::string message = root.get("message", "").asString();
	if (message == "") {
		cout << "Client message error, no message";
		return false;
	}

	Json::Value json;
	json["request"] = "message";
	json["timestamp"] = boost::lexical_cast<std::string>(time(NULL));
	json["nick"] = client->getNick();
	json["message"] = message;

	for (map<int, Client*>::iterator it =
			server->clients->getWhiteClients().begin();
			it != server->clients->getWhiteClients().end(); ++it) {
		sendResponse(json, it->second);
	}
	for (map<int, Client*>::iterator it =
			server->clients->getBlackClients().begin();
			it != server->clients->getBlackClients().end(); ++it) {
		sendResponse(json, it->second);
	}
	return true;
}
