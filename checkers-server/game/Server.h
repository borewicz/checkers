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

using namespace std;

class Server {
private:
	Clients *clients;
	Game *game;
	VotingManager *votingManager;
	TCPClientAcceptor *clientAcceptor;
	map<int, boost::shared_ptr<boost::thread>> threads;
	bool serverON;

public:
	Server(int roundTime, int server_port, const char* addres);
	virtual ~Server();

	bool startServer();
	bool stopServer();

	TCPClientAcceptor* getClientAcceptor();
	void setClientAcceptor(TCPClientAcceptor* clientAcceptor);
	Clients* getClients();
	void setClients(Clients* clients);
	Game* getGame();
	void setGame(Game* game);
	VotingManager* getVotingManager();
	void setVotingManager(VotingManager* votingManager);

private:
	bool runAcceptor();
	bool runClientConnection(Client *client);
};

#endif /* GAME_SERVER_H_ */
