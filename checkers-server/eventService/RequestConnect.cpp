/*
 * RequestConnect.cpp
 *
 *  Created on: 12-11-2015
 *      Author: debian
 */

#include "RequestConnect.h"
#include "../game/Client.h"
#include "../game/Clients.h"

RequestConnect::RequestConnect() {
}

RequestConnect::~RequestConnect() {
}

bool RequestConnect::action(Json::Value root, Server *server, Client *client) {
	if (client->getIsConnected()) {
		cout << "Already connected";
		sendResponse(shortJson("status", "already connected"), client);
		return true;
	}

	std::string nick = root.get("nick", "no_nick_field_in_json").asString();
	if (nick == "no_nick_field_in_json") {
		cout << "Client connecting error, no nick";
		return false;
	}

	if (server->clients->nickAvailable(nick)) {
		client->setNick(nick);
		client->setIsConnected(true);
		sendResponse(responseJson(server->clients, client->getID()), client);
	} else {
		sendResponse(shortJson("status", "nick not available"), client);
	}
	return true;
}

Json::Value RequestConnect::responseJson(Clients *clients, int id) {
	Json::Value json;
	if (clients->getBlackClients().find(id)
			== clients->getBlackClients().end()) {
		if (clients->getWhiteClients().find(id)
				== clients->getWhiteClients().end()) {
			//this case should be not possible
			cout << "Error, cant find client";
			json["status"] = "server error";
		} else {
			json["status"] = "ok";
			json["color"] = "white";
		}
	} else {
		json["status"] = "ok";
		json["color"] = "black";
	}
	return json;
}
