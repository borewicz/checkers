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
	boost::multi_array<char, 2> gameState{boost::extents[8][8]};
	int actualRoundEndTime;
	string currentMovementColor;
	bool isGameStarted;

public:
	Game(int roundTime);
	virtual ~Game();

	bool startGame();
	bool endGame();
	bool movementValidation(Movement *movement);
	bool move(Movement *movement);
	void drawGameBoard();

	boost::multi_array<char, 2> getGameState();
	int getRoundTime();
	int getActualRoundEndTime();
	bool getIsGameStarted();
	string getCurrentMovementColor();
	bool isGameEnd();
	bool isRoundTimeEnd();

private:
	void resetBoard();
	void removeBetween(int sX, int sY, int dX, int dY);
	bool beatingValidation(int x1, int y1, int x2, int y2);
};

#endif /* GAME_GAME_H_ */
