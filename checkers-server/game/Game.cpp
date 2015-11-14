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
	actualRoundEndTime = 'white';
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

bool Game::movementValidation(Movement movement) {
	return true;
}

bool Game::move(Movement movement) {
	if (movementValidation(movement) == false) {
		cout << "wrong movement";
		return false;
	}
	if (movement.getMovementID() == "0") {
		endGame();
		return true;
	}
	int size = movement.getX().size();
	for (int i = 0; i < size - 1; i++) {
		removeBetween(movement.getX()[i], movement.getY()[i],
				movement.getX()[i + 1], movement.getY()[i + 1]);
	}
	gameState[movement.getX()[size - 1]][movement.getY()[size - 1]] =
			gameState[movement.getX()[0]][movement.getY()[0]];
	gameState[movement.getX()[0]][movement.getY()[0]] = '_';

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

string Game::getCurrentMovementColor(){
	return currentMovementColor;
}
