/*
 * game.cpp
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#include <iostream>
#include "Game.h"
#include <ctime>
#include <map>

using namespace std;

Game::Game(int roundTime) {
	actualRoundEndTime = 0;
	this->roundTime = roundTime;
	isGameStarted = false;
	currentMovementColor = "";
	resetBoard();
}

Game::~Game() {
}

bool Game::startGame() {
	if (isGameStarted) {
		cout << "Game already started";
		return false;
	}
	currentMovementColor = "white";
	actualRoundEndTime = time(NULL) + roundTime;
	resetBoard();
	isGameStarted = true;
	return true;
}

bool Game::endGame() {
	if (isGameStarted == false) {
		cout << "Game is not started";
		return false;
	}
	isGameStarted = false;
	actualRoundEndTime = 0;
	resetBoard();
	return true;
}

bool Game::isGameEnd() {
	bool white = false;
	bool black = false;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			if (gameState[i][j] == 'W')
				white = true;
			if (gameState[i][j] == 'w')
				white = true;
			if (gameState[i][j] == 'B')
				black = true;
			if (gameState[i][j] == 'b')
				black = true;
			if ((white) && (black))
				return false;
		}
	return true;
}

//it check only if there is one good pawn between two fields
bool Game::beatingValidation(int sX, int sY, int dX, int dY) {

	if (!((abs(dX - sX) > 1) && (abs(dY - sY) > 1))) {
		return false;
	} else {
		/* int x = (x1 + x2) / 2;
		 int y = (y1 + y2) / 2;

		 }
		 } else {

		 }
		 return false;*/
		map<char, int> count;
		count['W'] = 0;
		count['w'] = 0;
		count['b'] = 0;
		count['B'] = 0;
		count['_'] = 0;

		if ((dX > sX) && (dY > sY)) {
			int x = sX + 1, y = sY + 1;
			while ((x != dX) && (y != dY)) {
				count[gameState[x][y]]++;
				x++;
				y++;
			}
		} else if ((dX < sX) && (dY < sY)) {
			int x = sX - 1, y = sY - 1;
			while ((x != dX) && (y != dY)) {
				count[gameState[x][y]]++;
				x--;
				y--;
			}
		} else if ((dX < sX) && (dY > sY)) {
			int x = sX - 1, y = sY + 1;
			while ((x != dX) && (y != dY)) {
				count[gameState[x][y]]++;
				x--;
				y++;
			}
		} else if ((dX > sX) && (dY < sY)) {
			int x = sX + 1, y = sY - 1;
			while ((x != dX) && (y != dY)) {
				count[gameState[x][y]]++;
				x++;
				y--;
			}
		}

		if (currentMovementColor == "white") {
			if ((count['W'] + count['w']) > 0) {
				return false;
			}
			if ((count['b'] + count['B']) != 1) {
				return false;
			}
		}
		if (currentMovementColor == "black") {
			if ((count['B'] + count['b']) > 0) {
				return false;
			}
			if ((count['W'] + count['w']) != 1) {
				return false;
			}
		}
		return true;
	}
	return true;
}
bool Game::movementValidation(Movement *movement) {
	//color checking
	if (movement->getColor() != getCurrentMovementColor()[0]) {
		cout << "wrong movement color" << endl;
		return false;
	}
	//first field checking
	if (gameState[movement->getX()[0]][movement->getY()[0]] == '_') {
		cout << "empty first field" << endl;
		return false;
	}
	if (getCurrentMovementColor() == "white") {
		if ((gameState[movement->getX()[0]][movement->getY()[0]] == 'B')
				|| (gameState[movement->getX()[0]][movement->getY()[0]] == 'b')) {
			cout << "wrong color of first pawn" << endl;
			return false;
		}
	}
	if (getCurrentMovementColor() == "black") {
		if ((gameState[movement->getX()[0]][movement->getY()[0]] == 'W')
				|| (gameState[movement->getX()[0]][movement->getY()[0]] == 'w')) {
			cout << "wrong color of first pawn" << endl;
			return false;
		}
	}
	int size = 0;
	//checking if fields free
	for (unsigned int i = 1; i < movement->getX().size(); i++) {
		if ((movement->getY()[i] < 0) || (movement->getX()[i] < 0)) {
			break;
		}
		size = i;
		if (gameState[movement->getX()[i]][movement->getY()[i]] != '_') {
			cout << "field not empty" << endl;
			return false;
		}
	}
	//check if move forward
	if (size == 1) {
		if (gameState[movement->getX()[0]][movement->getY()[0]] == 'w') {
			if (movement->getY()[1] <= movement->getY()[0]) {
				cout << "move backward" << endl;
				return false;
			}
		}
		if (gameState[movement->getX()[0]][movement->getY()[0]] == 'b') {
			if (movement->getY()[1] >= movement->getY()[0]) {
				cout << "move backward" << endl;
				return false;
			}
		}
	}

	return true;
}

bool Game::move(Movement *movement) {
	if (movement->getMovementID() == "0") {
		endGame();
		return true;
	}
	if (movementValidation(movement) == false) {
		cout << "wrong movement";
		return false;
	}

	int size = 0;
	for (unsigned int i = 0; i < movement->getX().size(); i++) {
		if (movement->getX()[i] >= 0) {
			size = i;
		} else {
			break;
		}
	}
//execute move
	for (int i = 0; i < size; i++) {
		if (movement->getX()[i + 1] != -1) {
			removeBetween(movement->getX()[i], movement->getY()[i],
					movement->getX()[i + 1], movement->getY()[i + 1]);
		}
	}
	gameState[movement->getX()[size]][movement->getY()[size]] =
			gameState[movement->getX()[0]][movement->getY()[0]];
	gameState[movement->getX()[0]][movement->getY()[0]] = '_';

//king turn
	if ((movement->getY()[size] == 7) && (movement->getColor() == 'w')) {
		gameState[movement->getX()[size]][movement->getY()[size]] = 'W';
	}

	if ((movement->getY()[size] == 0) && (movement->getColor() == 'b')) {
		gameState[movement->getX()[size]][movement->getY()[size]] = 'B';
	}

	if (currentMovementColor == "white") {
		currentMovementColor = "black";
	} else {
		currentMovementColor = "white";
	}
	actualRoundEndTime = time(NULL) + roundTime;

	return true;
}

void Game::drawGameBoard() {
	for (int y = 7; y >= 0; y--) {
		for (int x = 0; x < 8; x++) {
			cout << gameState[x][y];
		}
		cout << endl;
	}
}

void Game::resetBoard() {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			gameState[x][y] = '_';
		}
	}
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 4; x++) {
			gameState[(x * 2) + y % 2][y] = 'w';
		}
	}
	for (int y = 7; y >= 5; y--) {
		for (int x = 0; x < 4; x++) {
			gameState[(x * 2) + y % 2][y] = 'b';
		}
	}
}

void Game::removeBetween(int sX, int sY, int dX, int dY) {
	if ((dX > sX) && (dY > sY)) {
		int x = sX + 1, y = sY + 1;
		while ((x != dX) && (y != dY)) {
			gameState[x][y] = '_';
			x++;
			y++;
		}
	} else if ((dX < sX) && (dY < sY)) {
		int x = sX - 1, y = sY - 1;
		while ((x != dX) && (y != dY)) {
			gameState[x][y] = '_';
			x--;
			y--;
		}
	} else if ((dX < sX) && (dY > sY)) {
		int x = sX - 1, y = sY + 1;
		while ((x != dX) && (y != dY)) {
			gameState[x][y] = '_';
			x--;
			y++;
		}
	} else if ((dX > sX) && (dY < sY)) {
		int x = sX + 1, y = sY - 1;
		while ((x != dX) && (y != dY)) {
			gameState[x][y] = '_';
			x++;
			y--;
		}
	}
}

bool Game::isRoundTimeEnd() {
	if (getActualRoundEndTime() < time(NULL)) {
		return true;
	}
	return false;
}

boost::multi_array<char, 2> Game::getGameState() {
	return gameState;
}

int Game::getRoundTime() {
	return roundTime;
}

int Game::getActualRoundEndTime() {
	return actualRoundEndTime;
}

bool Game::getIsGameStarted() {
	return isGameStarted;
}

string Game::getCurrentMovementColor() {
	return currentMovementColor;
}
