/*
 * VotingManager.cpp
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#include "VotingManager.h"
#include "Movement.h"

#include <cstring>
#include <map>

VotingManager::VotingManager() {
	actualGameID = 0;
	currentColor = "white";
}

VotingManager::~VotingManager() {
}

void VotingManager::nextVote(int gameID, string color) {
	actualGameID = gameID;
	votes.clear();
	votesCount.clear();
	currentColor = color;
}

void VotingManager::addMovement(Movement *movement) {
	if (movement->getRoundID() == actualGameID) {
		if (votes.find(movement->getMovementID()) == votes.end()) {
			votes[movement->getMovementID()] = movement;
			votesCount[movement->getMovementID()] = 1;
		} else {
			votesCount[movement->getMovementID()]++;
			delete movement;
		}
	}
}

Movement VotingManager::getBestMove() {
	int maxCount = 0;
	string maxID = "";
	for (map<string, int>::iterator it = votesCount.begin();
			it != votesCount.end(); ++it) {
		if (it->second > maxCount) {
			maxCount = it->second;
			maxID = it->first;
		}
	}
	if (maxCount==0){
		Movement movement = Movement();
		return movement;
	}
	Movement movement = *(votes[maxID]);
	return movement;
}
