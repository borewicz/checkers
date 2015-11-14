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
}

VotingManager::~VotingManager() {
}

void VotingManager::nextVote(int gameID) {
	actualGameID = gameID;
	votes.clear();
	votesCount.clear();
}

void VotingManager::addMovement(Movement *movement) {
	if (movement->getRoundID() == actualGameID) {
		if (votes.find(movement->getMovementID()) == votes.end()) {
			votes[movement->getMovementID()] = movement;
			votesCount[movement->getMovementID()] = 1;
		}else{
			votesCount[movement->getMovementID()] ++;
			delete movement;
		}
	}
}

