/*
 * Server.cpp
 *
 *  Created on: 10-11-2015
 *      Author: debian
 */

#include "Server.h"
#include "VotingManager.h"
#include "Game.h"
#include "Clients.h"
#include "Client.h"
#include "../network/TCPClientAcceptor.h"
#include <boost/thread/thread.hpp>

using namespace std;

Server::Server(int roundTime, int server_port, const char* addres) {
	clients = new Clients();
	game = new Game(roundTime);
	votingManager = new VotingManager();
	clientAcceptor = new TCPClientAcceptor(server_port, addres);
	serverON = false;
	requestManager = new RequestManager();
}

Server::~Server() {
	serverON = false;
	delete game;
	delete votingManager;
	delete requestManager;
	delete clientAcceptor;
	delete clients;
	for (map<int, boost::shared_ptr<boost::thread>>::iterator it =
			threads.begin(); it != threads.end(); ++it) {
		it->second->join();
	}

}

bool Server::startServer() {
	bool err = clientAcceptor->start();
	if (!err) {
		cout << "Error when start server ";
		return false;
	}
	serverON = true;

	return true;
}
