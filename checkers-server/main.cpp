/*
 * main.cpp
 *
 *  Created on: 07-11-2015
 *      Author: Sebastian
 */

#include <boost/thread/thread.hpp>
#include <iostream>

#include "game/Server.h"

void commandLine() {
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

int main() {
	int port = 2137;
	const char* host = "127.0.0.1";
	int roundTime = 30;

	Server *server = new Server(roundTime, port, host);

	boost::shared_ptr<boost::thread> thread(
			new boost::thread(server->runAcceptor);

	commandLine();
	delete server;
}
