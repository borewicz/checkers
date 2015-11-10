/*
 * Clients.cpp
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#include "Clients.h"

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
	if (whiteClients.find(ID) == whiteClients.end()) {
		if (blackClients.find(ID) == blackClients.end()) {
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
	for (map<int, Client*>::iterator it = whiteClients.begin();
			it != whiteClients.end(); ++it) {
		if (it->second->getNick() == nick) {
			return false;
		}
	}
	for (map<int, Client*>::iterator it = blackClients.begin();
			it != blackClients.end(); ++it) {
		if (it->second->getNick() == nick) {
			return false;
		}
	}
	return true;
}
