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
	resetBoard();
}

Game::~Game() {
}

bool Game::startGame(){
	if (isGameStarted){
		cout<<"Game already started";
		return false;
	}
	actualRoundEndTime = time(NULL) + roundTime;
	resetBoard();
	isGameStarted = true;
	return true;
}

bool Game::endGame(){
	if (isGameStarted == false){
		cout<<"Game is not started";
		return false;
	}
	actualRoundEndTime = 0;
	resetBoard();
	return true;
}

bool Game::movementValidation(Movement *movement, char color) {
	return true;
}

bool Game::move(Movement *movement, char color) {
	if (movementValidation(movement, color) == false) {
		cout<<"wrong movement";
		return false;
	}
	gameState[movement->getFrom()[0]][movement->getFrom()[1]] = gameState[movement->getTo()[0]][movement->getTo()[1]];
	gameState[movement->getTo()[0]][movement->getTo()[1]] = '_';

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

void Game::resetBoard(){
	actualRoundID = 0;

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

boost::multi_array<char, 2> Game::getGameState(){
	return gameState;
}

int Game::getRoundTime(){
	return roundTime;
}

int Game::getActualRoundEndTime(){
	return actualRoundEndTime;
}

int Game::getActualRoundID(){
	return actualRoundID;
}

bool Game::getIsGameStarted(){
	return isGameStarted;
}
