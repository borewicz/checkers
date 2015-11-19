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
	cout << "client " << client->getNick() << " message" << endl;
	if (!client->getIsConnected()) {
		sendResponse(shortJson("status", "not connected"), client);
		return true;
	}

	std::string message = root.get("message", "").asString();
	if (message == "") {
		cout << "Client message error, no message" << endl;
		return false;
	}

	Json::Value json;
	json["request"] = "message";
	json["timestamp"] = boost::lexical_cast<std::string>(time(NULL));
	json["nick"] = client->getNick();
	json["message"] = message;

	if (!server->clients->getWhiteClients().empty()) {
		for (auto const& iterator : server->clients->getWhiteClients()) {
			if (iterator.second->getIsConnected()) {
				sendResponse(json, iterator.second);
			}
		}
	}
	if (!server->clients->getBlackClients().empty()) {
		for (auto const& iterator : server->clients->getBlackClients()) {
			if (iterator.second->getIsConnected()) {
				sendResponse(json, iterator.second);
			}
		}
	}
	return true;
}
