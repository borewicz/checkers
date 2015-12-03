/*
 * game.cpp
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#include <iostream>
#include "Game.h"
#include <ctime>

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
bool Game::beatingValidation(int x1, int y1, int x2, int y2) {

	if ((abs(x1 - x2) == 2) && (abs(y1 - y2) == 2)) {
		int x = (x1 + x2) / 2;
		int y = (y1 + y2) / 2;
		if (currentMovementColor == "white") {
			if ((gameState[x][y] == 'b') || (gameState[x][y] == 'B')) {
				return true;
			}
		}
		if (currentMovementColor == "black") {
			if ((gameState[x][y] == 'w') || (gameState[x][y] == 'W')) {
				return true;
			}
		}
	}
	return false;
}
bool Game::movementValidation(Movement *movement) {
	/*//wrong color
	if (!(((movement.getColor() == 'w') && (currentMovementColor == "white"))
			|| ((movement.getColor() == 'b')
					&& (currentMovementColor == "black")))) {
		return false;
	}
	int size;
	for (unsigned int i = 0; i < movement.getX().size(); i++) {
		if (movement.getX()[i] > 0) {
			size = i;
		} else {
			break;
		}
	}
	//too few movements
	if (size < 1) {
		return false;
	}

	for (int i = 0; i <= size; i++) {
		//no pawn on first field
		if (i == 0) {
			if (gameState[movement.getX()[i]][movement.getY()[i]] == '_') {
				return false;
			}
		}
		//field not available
		if (i > 0) {
			if (gameState[movement.getX()[i]][movement.getY()[i]] != '_') {
				return false;
			}
		}
		//field out of bounds
		if ((movement.getX()[i] < 0) || (movement.getX()[i] > 7)) {
			return false;
		}
		if ((movement.getY()[i] < 0) || (movement.getY()[i] > 7)) {
			return false;
		}
	}
	//if not king
	if (gameState[movement.getX()[0]][movement.getY()[0]]
			== movement.getColor()) {
		//only one step in movement
		if (size == 1) {
			//white color
			if (movement.getColor() == 'w') {
				//if normal step
				if ((abs(movement.getX()[1] - movement.getX()[0]) == 1)
						&& ((movement.getX()[1] - movement.getX()[0]) == 1)) {
					return true;
				}
			}
			//black color
			if (movement.getColor() == 'b') {
				if ((abs(movement.getX()[1] - movement.getX()[0]) == 1)
						&& ((movement.getX()[0] - movement.getX()[1]) == 1)) {
					return true;
				}
			}
		}
		for (int i = 0; i < size; i++) {
			if (!beatingValidation(movement.getX()[i], movement.getX()[i + 1],
					movement.getY()[i], movement.getY()[i + 1])) {
				return false;
			}
		}
	} else {

	}
	*/
	return true;
}

bool Game::move(Movement *movement) {
	cout<<"move downloaded"<<endl;
	cout<<"test if movement is good color display : "<<movement->getColor()<<endl;
	if (movementValidation(movement) == false) {
		cout << "wrong movement";
		return false;
	}
	if (movement->getMovementID() == "0") {
		endGame();
		return true;
	}
	int size;
	for (int i = 0; i < movement->getX().size(); i++) {
		cout<<movement->getX()[i];
		if (movement->getX()[i] >= 0) {
			size = i;
		} else {
			break;
		}
	}
	cout<<"size of move "<<size<<endl;
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

//bool Game::isGameFinished() {
////	for (int y = 0; y < 10; y++) {
////		for (int x = 0; x < 10; x++) {
////			gameState[y][x] = '_';
////		}
////	}
////	TODO or not don't know yet
//	return false;
//}

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
