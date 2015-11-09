/*
 * game.cpp
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#include <iostream>
#include "Game.h"

using namespace std;

Game::Game() {
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			gameState[y][x] = '_';
		}
	}
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 5; x++) {
			gameState[y][(x * 2) + y % 2] = 'w';
		}
	}
	for (int y = 9; y >= 6; y--) {
		for (int x = 0; x < 5; x++) {
			gameState[y][(x * 2) + y % 2] = 'b';
		}
	}
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

/*char game::getGameState() {
 return gameState;
 }*/

bool Game::movementValidation(int move[4], char color) {
	return true;
}

bool Game::move(int movement[4], char color) {
	if (movementValidation(movement, color) == false) {
		printf("wrong movement");
		return false;
	}
	gameState[movement[2]][movement[3]] = gameState[movement[0]][movement[1]];
	gameState[movement[0]][movement[1]] = '_';

	return true;
}
void Game::drawGameBoard() {
	for (int y = 9; y >= 0; y--) {
		for (int x = 0; x < 10; x++) {
			cout << gameState[y][x];
		}
		cout << endl;
	}
}

