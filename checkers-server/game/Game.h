/*
 * game.h
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#ifndef GAME_GAME_H_
#define GAME_GAME_H_

#include "Movement.h"
#include <boost/multi_array.hpp>

class Game {
private:
	int roundTime;
	boost::multi_array<char, 2> gameState{boost::extents[10][10]};
	int actualRoundEndTime;
	int actualRoundID;
	bool isGameStarted;

public:
	Game(int roundTime);
	virtual ~Game();

	bool startGame();
	bool endGame();
	bool movementValidation(Movement *movement, char color);
	bool move(Movement *movement, char color);
	void drawGameBoard();

	boost::multi_array<char, 2> getGameState();
	int getRoundTime();
	int getActualRoundEndTime();
	int getActualRoundID();
	bool getIsGameStarted();

private:
	void resetBoard();
};

#endif /* GAME_GAME_H_ */
