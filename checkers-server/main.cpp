/*
 * main.cpp
 *
 *  Created on: 07-11-2015
 *      Author: Sebastian
 */

#include <boost/thread/thread.hpp>

#include <iostream>
#include <string.h>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <ctime>

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

mutex serverMutex;
mutex serverSleepMutex;
condition_variable serverSleep;

int main(int argc, char* argv[]) {
	int port = 2137;
	const char* host = "127.0.0.1";
	int roundTime = 30;

	if (argc == 4) {
		printf("Usage: %s m n filename\n", argv[0]);
		host = argv[1];
		port = atoi(argv[2]);
		roundTime = atoi(argv[3]);
	}

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

	return 0;
}

void commandLine(Server *server) {
	string command;
	while (true) {
		cout << "Commands: start - start server\nstop - stop server\n";
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
		std::lock_guard<mutex> serverLock(serverMutex);
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
		int result = client->getNetwork()->receive(buffer, BLOCK_SIZE);

		if (result == -2) {
			std::lock_guard<mutex> serverLock(serverMutex);
			requestManager->requestReaction("request error", server, client);
			continue;
		}
		if (result == -1) {
			std::lock_guard<mutex> serverLock(serverMutex);
			requestManager->requestReaction("socket error", server, client);
			break;
		}
		if (result == 0) {
			cout<<"client disconnected"<<endl;
			break;
		}

		std::lock_guard<mutex> serverLock(serverMutex);
		result = requestManager->requestReaction(string(buffer), server,
				client);
		if (result == 2) {
			serverSleep.notify_one();
		}
	}
	delete requestManager;
	std::lock_guard<mutex> serverLock(serverMutex);
	server->threads.erase(client->getID());
	server->clients->removeClient(client->getID());
	delete client;
}

void runGame(Server *server) {
	RequestBoard *requestBoard = new RequestBoard();
	cout << "game server run" << endl;
	while (server->serverON) {
		{
			std::lock_guard<mutex> serverLock(serverMutex);
//			server->game->drawGameBoard();
			if (server->clients->clientsReadyToPlay()) {
				if (server->game->getIsGameStarted()) {
					if (server->game->isRoundTimeEnd()) {
//						cout << "endRoundTime" << endl;
						if (server->votingManager->isSomeMove()) {
//							cout << "is move" << endl;
							server->movementExecute();
							requestBoard->sendBoard(server);
							if (server->game->isGameEnd()) {
								requestBoard->gameOver(server);
								server->lossGame();
							}
						} else {
							cout << "no move" << endl;
							requestBoard->gameOver(server,
									server->game->getOppositeColor(
											server->game->getCurrentMovementColor()));
							server->lossGame();
						}
					} else {
						if (server->isEveryoneVoted()) {
//							cout << "everyone Voted" << endl;
							server->movementExecute();
							requestBoard->sendBoard(server);
							if (server->game->isGameEnd()) {
								requestBoard->gameOver(server);
								server->lossGame();
							}
						}
					}

				} else {
					server->game->startGame();
					server->votingManager->nextVote(
							server->game->getActualRoundEndTime(),
							server->game->getCurrentMovementColor());
					sleep(1);
					requestBoard->sendBoard(server);
				}
			} else {
				if (server->game->getIsGameStarted()) {
					requestBoard->gameOver(server,
							server->clients->getColorWithPlayers());
					server->lossGame();
				}
			}
		}
		std::unique_lock<std::mutex> sleepLock(serverSleepMutex);
		serverSleep.wait_for(sleepLock, chrono::milliseconds(4000));
	}
	delete requestBoard;
}

