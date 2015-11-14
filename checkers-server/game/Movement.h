/*
 * Movement.h
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#ifndef GAME_MOVEMENT_H_
#define GAME_MOVEMENT_H_

#include <vector>
#include <string.h>
#include <iostream>

using namespace std;

class Movement {
private:
	vector<int> from;
	vector<int> to;
	char color;
	int roundID;
	string movementID;

public:
	Movement(int fromY, int fromX, int toY, int toX, char color, int roundID);
	virtual ~Movement();

	bool isEqual(Movement *movement);
	string getMovementID();
	vector<int> getFrom();
	vector<int> getTo();
	int getRoundID();
	char getColor();

private:
	void generateID();
};

#endif /* GAME_MOVEMENT_H_ */
