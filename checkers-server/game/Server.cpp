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
	delete clients;
	delete game;
	delete votingManager;
	delete clientAcceptor;
}

bool Server::runClientConnection(Client *client) {
	cout<<"lsdfkjslk";
}


bool Server::runAcceptor() {
	while (serverON) {
		TCPClientConnection *acceptedClient =
				clientAcceptor->acceptConnection();
		Client *client = new Client(acceptedClient);
		clients->addToRandomColor(client);
		boost::shared_ptr<boost::thread> thread(
				new boost::thread(runClientConnection,client));
		threads[client->getID()] = thread;

	}
}

bool Server::startServer() {
	bool err = clientAcceptor->start();
	if (!err) {
		cout << "Error when start server ";
		return false;
	}
	return true;
}

TCPClientAcceptor* Server::getClientAcceptor() {
	return clientAcceptor;
}

void Server::setClientAcceptor(TCPClientAcceptor* clientAcceptor) {
	this->clientAcceptor = clientAcceptor;
}

Clients* Server::getClients() {
	return clients;
}

void Server::setClients(Clients* clients) {
	this->clients = clients;
}

Game* Server::getGame() {
	return game;
}

void Server::setGame(Game* game) {
	this->game = game;
}

VotingManager* Server::getVotingManager() {
	return votingManager;
}

void Server::setVotingManager(VotingManager* votingManager) {
	this->votingManager = votingManager;
}
