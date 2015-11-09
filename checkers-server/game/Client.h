/*
 * Client.h
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#ifndef GAME_CLIENT_H_
#define GAME_CLIENT_H_

#include "../network/TCPClientConnection.h"
#include <string.h>

using namespace std;

class Client {
private:
	TCPClientConnection *network;
	int color;
	string nick;

public:
	Client();
	virtual ~Client();
};

#endif /* GAME_CLIENT_H_ */
