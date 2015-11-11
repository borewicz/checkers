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

#include "game/Game.h"
#include "game/Server.h"
#include "game/Clients.h"
#include "game/Client.h"
#include "game/VotingManager.h"
#include "eventService/RequestManager.h"
#include "network/TCPClientAcceptor.h"
#include "network/TCPClientConnection.h"

using namespace std;

void commandLine(Server *server);
void runClientAcceptor(Server *server);
void runClientConnection(Server *server);

int main() {
	int port = 2137;
	const char* host = "127.0.0.1";
	int roundTime = 30;

	Server *server = new Server(roundTime, port, host);
	if (!server->startServer()){
		cout<<"error in starting server";
		delete server;
		return 1;
	}

	boost::shared_ptr<boost::thread> thread(
			new boost::thread(runClientAcceptor, server));
	server->threads[0]=thread;

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
				new boost::thread(runClientConnection, server));
		server->threads[client->getID()] = clientThread;
	}
}

void runClientConnection(Server *server) {
	while (server->serverON) {
		cout << "test";
		sleep(2000);
	}
}

