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
	int ID;
	TCPClientConnection *network;
	char color;
	string nick;
	bool isConnected;
	bool threadEnabled;

public:
	Client(TCPClientConnection *network, char color, string nick);
	Client(TCPClientConnection *network);
	virtual ~Client();

	void terminateThread();

	char getColor();
	string getNick();
	int getID();
	bool getIsConnected();
	bool getThreadEnabled();

	void setColor(char color);
	void setNick(string nick);
	void setIsConnected(bool connected);
};

#endif /* GAME_CLIENT_H_ */
