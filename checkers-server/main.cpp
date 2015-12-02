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
#include "eventService/RequestBoard.h"

#define BLOCK_SIZE 4096

using namespace std;

void commandLine(Server *server);
void runClientAcceptor(Server *server);
void runClientConnection(Client *client, Server *server);
void runGame(Server *server);

boost::mutex serverMutex;

int main() {
	int port = 2137;
	const char* host = "127.0.0.1";
	int roundTime = 300;

	Server *server = new Server(roundTime, port, host);
	if (!server->startServer()) {
		cout << "Error in starting server";
		delete server;
		return 1;
	}

	boost::shared_ptr<boost::thread> threadAcceptor(
			new boost::thread(runClientAcceptor, server));
	server->threads[0] = threadAcceptor;

	boost::shared_ptr<boost::thread> threadGame(
			new boost::thread(runGame, server));
	server->threads[1] = threadGame;

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
		//clientAcceptor is used only here
		Client *client = new Client(server->clientAcceptor->acceptConnection());
		cout << "client " << client->getNick() << " connect" << endl;
		serverMutex.lock();
		server->clients->addToRandomColor(client);
		boost::shared_ptr<boost::thread> clientThread(
				new boost::thread(runClientConnection, client, server));
		server->threads[client->getID()] = clientThread;
		serverMutex.unlock();
	}
}

void runClientConnection(Client *client, Server *server) {
	RequestManager *requestManager = new RequestManager();

	serverMutex.lock();
	bool run = client->getThreadEnabled();
	serverMutex.unlock();

	while ((server->serverON) and (run)) {
		char buffer[BLOCK_SIZE];
		client->getNetwork()->receive(buffer, BLOCK_SIZE);

		cout << "message received" << endl;

		serverMutex.lock();
		requestManager->requestReaction(string(buffer), server, client);
		run = client->getThreadEnabled();
		serverMutex.unlock();
	}
	delete requestManager;
	serverMutex.lock();
	server->threads.erase(client->getID());
	server->clients->removeClient(client->getID());
	delete client;
	serverMutex.unlock();
}

void runGame(Server *server) {
	RequestBoard *requestBoard = new RequestBoard();
	serverMutex.lock();
	int time = server->game->getRoundTime();
	serverMutex.unlock();
	cout << "game server run" << endl;
	while (server->serverON) {
		serverMutex.lock();
		if (server->clients->clientsReadyToPlay()) {
			if (server->game->getIsGameStarted()) {
				server->game->move(server->votingManager->getBestMove());
				requestBoard->sendBoard(server);
				server->votingManager->nextVote(
						server->game->getActualRoundEndTime(),
						server->game->getCurrentMovementColor());
				if (!server->game->getIsGameStarted()) {
					continue;
				}
			} else {
				server->game->startGame();
				server->votingManager->nextVote(
						server->game->getActualRoundEndTime(),
						server->game->getCurrentMovementColor());
				requestBoard->sendBoard(server);
			}
		} else {
			if (server->game->getIsGameStarted()) {
				server->game->endGame();
				server->votingManager->nextVote(
						server->game->getActualRoundEndTime(),
						server->game->getCurrentMovementColor());
			}
		}
		serverMutex.unlock();
		cout << "sleep" << endl;
		sleep(time);
	}
	delete requestBoard;
}

