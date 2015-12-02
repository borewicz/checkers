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

bool VotingManager::addMovement(Movement *movement) {
	if (((movement->getColor() == 'w') && (currentColor == "white"))
			|| ((movement->getColor() == 'b') && (currentColor == "black"))) {
		if (movement->getRoundID() == actualGameID) {
			if (votes.count(movement->getMovementID()) == 0) {
				votes[movement->getMovementID()] = movement;
				votesCount[movement->getMovementID()] = 1;
			} else {
				votesCount[movement->getMovementID()]++;
				delete movement;
			}
			return true;
		}
		return false;
	} else {
		return false;
	}
}

Movement* VotingManager::getBestMove() {
	int maxCount = 0;
	string maxID = "";
	for (map<string, int>::iterator it = votesCount.begin();
			it != votesCount.end(); ++it) {
		if (it->second > maxCount) {
			maxCount = it->second;
			maxID = it->first;
		}
	}
	if (maxCount == 0) {
		Movement *movement = new Movement();
		return movement;
	}
	Movement *movement = votes[maxID];
	return movement;
}
