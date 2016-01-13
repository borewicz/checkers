/*
 * Server.h
 *
 *  Created on: 10-11-2015
 *      Author: debian
 */

#ifndef GAME_SERVER_H_
#define GAME_SERVER_H_

#include "Server.h"
#include "VotingManager.h"
#include "Game.h"
#include "Clients.h"
#include "Client.h"
#include "../network/TCPClientAcceptor.h"
#include <boost/thread/thread.hpp>
#include <memory>
#include <map>
#include <atomic>

using namespace std;

class Server {
public:
	Clients *clients;
	Game *game;
	VotingManager *votingManager;
	TCPClientAcceptor *clientAcceptor;
	map<int, boost::shared_ptr<boost::thread>> threads;
	atomic<bool> serverON;

public:
	Server(int roundTime, int server_port, const char* addres);
	virtual ~Server();
	bool isEveryoneVoted();
	bool startServer();
	bool stopServer();
	void lossGame();
	void movementExecute();

};

#endif /* GAME_SERVER_H_ */
