/*
 * Clients.h
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#ifndef GAME_CLIENTS_H_
#define GAME_CLIENTS_H_

#include <vector>
#include "Client.h"

using namespace std;

class Clients {
private:
	vector<Client> whiteClients;
	vector<Client> blackClients;

public:
	Clients();
	virtual ~Clients();
};

#endif /* GAME_CLIENTS_H_ */
