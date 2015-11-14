/*
 * main.cpp
 *
 *  Created on: 07-11-2015
 *      Author: Sebastian
 */

#include <boost/thread/thread.hpp>

#include <iostream>
#include <string.h>
#include <iostream>
#include <atomic>

#include "game/Server.h"
#include "eventService/RequestManager.h"
#include "game/Game.h"
#include "game/VotingManager.h"

#define BLOCK_SIZE 4096

using namespace std;

void commandLine(Server *server);
void runClientAcceptor(Server *server);
void runClientConnection(Client *client, Server *server);
void runGame(Server *server);

int main() {
	int port = 2137;
	const char* host = "127.0.0.1";
	int roundTime = 30;

	Server *server = new Server(roundTime, port, host);
	if (!server->startServer()) {
		cout << "Error in starting server";
		delete server;
		return 1;
	}

	boost::shared_ptr<boost::thread> thread(
			new boost::thread(runClientAcceptor, server));
	server->threads[0] = thread;

	commandLine(server);
	delete server;
}

void commandLine(Server *server) {
	string command;
	while (true) {
		cout << "Commands: start - start server\n stop - stop server\n";
		cout << "exit - exit program\n ";
		cin >> command;

		if (command == "exit") {
			return;
		}
	}
}

void runClientAcceptor(Server *server) {
	while (server->serverON) {
		Client *client = new Client(server->clientAcceptor->acceptConnection());
		server->clients->addToRandomColor(client);

		boost::shared_ptr<boost::thread> clientThread(
				new boost::thread(runClientConnection, client, server));
		server->threads[client->getID()] = clientThread;
	}
}

void runClientConnection(Client *client, Server *server) {
	RequestManager *requestManager = new RequestManager();
	while ((server->serverON) and (client->getThreadEnabled())) {
		char buffer[BLOCK_SIZE];
		client->getNetwork()->receive(buffer, BLOCK_SIZE);
		requestManager->requestReaction(string(buffer), server, client);
	}
	delete requestManager;
	server->threads.erase(client->getID());
	server->clients->removeClient(client->getID());
	delete client;
}

void runGame(Server *server) {
	while (server->serverON) {
		if (server->clients->clientsReadyToPlay()) {
			if (server->game->getIsGameStarted()){
//				server->game->move(server->votingManager->getBestMove());

			}
		} else {
			if (server->game->getIsGameStarted()) {
				server->game->endGame();

			}
		}
	}
}

