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
}

Server::~Server() {
	serverON = false;
	for (map<int, boost::shared_ptr<boost::thread>>::iterator it =
			threads.begin(); it != threads.end(); ++it) {
		it->second->interrupt();
	}
	delete game;
	delete votingManager;
	delete clientAcceptor;
	delete clients;
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

bool Server::isEveryoneVoted() {
	if (game->getCurrentMovementColor() == "black") {
		if (votingManager->getVotesNumber()
				== clients->getBlackClients().size())
			return true;
	} else {
		if (votingManager->getVotesNumber()
				== clients->getWhiteClients().size())
			return true;
	}
	return false;
}

void Server::lossGame() {
	game->endGame();
	votingManager->nextVote(game->getActualRoundEndTime(),
			game->getCurrentMovementColor());
}

void Server::movementExecute() {
	game->move(votingManager->getBestMove());
	votingManager->nextVote(game->getActualRoundEndTime(),
			game->getCurrentMovementColor());
}
