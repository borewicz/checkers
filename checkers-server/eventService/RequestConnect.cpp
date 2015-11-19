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
	cout << "client " << client->getNick() << " connect" << endl;
	if (client->getIsConnected()) {
		cout << "client " << client->getNick() << " already connected" << endl;
		sendResponse(shortJson("status", "already connected"), client);
		return true;
	}

	std::string nick = "";
	if (root.isMember("nick")) {
		nick = root.get("nick", "").asString();
	}

	if (nick == "") {
		cout << "Client connecting error, no nick" << endl;
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
	if (clients->getBlackClients().count(id) == 0) {
		if (clients->getWhiteClients().count(id) == 0) {
			//this case should be not possible
			cout << "Error, cant find client" << endl;
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
