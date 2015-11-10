/*
 * Clients.h
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#ifndef GAME_CLIENTS_H_
#define GAME_CLIENTS_H_

#include <map>
#include "Client.h"

using namespace std;

class Clients {
private:
	map<int, Client*> whiteClients;
	map<int, Client*> blackClients;

public:
	Clients();
	virtual ~Clients();

	bool addToRandomColor(TCPClientConnection *clientConnection);
	bool removeClient(int ID);
	bool nickAvailable(string nick);

	map<int, Client*> getWhiteClients();
	map<int, Client*> getBlackClients();

};

#endif /* GAME_CLIENTS_H_ */
