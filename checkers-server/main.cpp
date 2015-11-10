/*
 * main.cpp
 *
 *  Created on: 07-11-2015
 *      Author: Sebastian
 */

#include "game/Game.h"
#include "network/TCPClientAcceptor.h"
#include "network/TCPClientConnection.h"

#include <boost/thread/thread.hpp>
#include <iostream>

void myFunc(){

	for (int i=0;i<12;i++){
		sleep(3);
		srand( time(NULL) );
		 //Randomize seed initialization
			int randNum = rand()%2; // Generate a random number between 0 and 1

			std::cout << randNum<<endl;
	}
}

int main() {
	int port = 2137;
	const char* host = "127.0.0.1";

	int roundTime = 30;

	Game game = Game(roundTime);

	TCPClientAcceptor server = TCPClientAcceptor(port, host);
	server.start();

	boost::thread t(myFunc);
	t.join();

}
