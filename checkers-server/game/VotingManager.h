/*
 * VotingManager.h
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#ifndef GAME_VOTINGMANAGER_H_
#define GAME_VOTINGMANAGER_H_

#include "Movement.h"
#include <map>

class VotingManager {
private:
	map<string, int> votesCount;
	map<string, Movement*> votes;
	int actualGameID;
	string currentColor;
public:
	VotingManager();
	virtual ~VotingManager();

	bool addMovement(Movement *movement);
	void nextVote(int gameID, string color);
	Movement getBestMove();
};

#endif /* GAME_VOTINGMANAGER_H_ */
