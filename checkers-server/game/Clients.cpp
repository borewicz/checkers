/*
 * Clients.cpp
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#include "Clients.h"
#include <cstdlib>
#include <time.h>

Clients::Clients() {
}

Clients::~Clients() {
}

map<int, Client*> Clients::getWhiteClients() {
	return whiteClients;
}
map<int, Client*> Clients::getBlackClients() {
	return blackClients;
}

bool Clients::addToRandomColor(Client *client) {
	if ((whiteClients.empty() && blackClients.empty())
			|| ((!whiteClients.empty() && !blackClients.empty()))) {
		srand(time(NULL));
		if (rand() % 2) {
			client->setColor('w');
			whiteClients[client->getID()] = client;
		} else {
			client->setColor('b');
			blackClients[client->getID()] = client;
		}
	} else {
		if (whiteClients.empty()) {
			client->setColor('w');
			whiteClients[client->getID()] = client;
		} else {
			client->setColor('b');
			blackClients[client->getID()] = client;
		}
	}
	return true;
}

bool Clients::removeClient(int ID) {
	if (whiteClients.count(ID) == 0) {
		if (blackClients.count(ID) == 0) {
			cout << "Client not found";
			return false;
		} else {
			blackClients.erase(ID);
		}
	} else {
		whiteClients.erase(ID);
	}
	return true;
}

bool Clients::nickAvailable(string nick) {
	for (auto const& iterator : whiteClients) {
		if (iterator.second->getNick() == nick) {
			return false;
		}
	}
	for (auto const& iterator : blackClients) {
		if (iterator.second->getNick() == nick) {
			return false;
		}
	}
	return true;
}

bool Clients::clientsReadyToPlay() {
	bool ready = false;
	for (auto const& iterator : blackClients) {
		if (iterator.second->getIsConnected()) {
			ready = true;
			break;
		}
	}
	if (ready) {
		for (auto const& iterator : whiteClients) {
			if (iterator.second->getIsConnected()) {
				return true;
			}
		}
	}
	return false;
}

string Clients::getColorWithPlayers(){
	if ((!blackClients.empty())&&(!whiteClients.empty())){
		return "both";
	}
	if (!blackClients.empty()){
		return "black";
	}
	if (!whiteClients.empty()){
		return "white";
	}
	return "none";
}
