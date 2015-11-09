/*
 * game.h
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#ifndef GAME_GAME_H_
#define GAME_GAME_H_

class Game {
private:
	char gameState[10][10];


public:
	//char getGameState();
	bool movementValidation(Movement *movement, char color);
	bool move(Movement *movement, char color);
	void drawGameBoard();
	Game();
	virtual ~Game();
};

#endif /* GAME_GAME_H_ */
