/*
 * main.cpp
 *
 *  Created on: 07-11-2015
 *      Author: Sebastian
 */

#include "game/Game.h"
#include "network/TCPClientAcceptor.h"
#include "network/TCPClientConnection.h"

int main() {
	int roundTime = 30;
	Game game = Game(roundTime);
	game.drawGameBoard();
	game.startGame();
	cout<<game.getActualRoundEndTime();
}
