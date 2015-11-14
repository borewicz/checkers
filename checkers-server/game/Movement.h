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
	vector<int> X;
	vector<int> Y;
	char color;
	int roundID;
	string movementID;

public:
	Movement();
	Movement(int coordinates[20], char color, int roundID);
	virtual ~Movement();

	string getMovementID();
	vector<int> getX();
	vector<int> getY();
	int getRoundID();
	char getColor();

private:
	void generateID();
};

#endif /* GAME_MOVEMENT_H_ */
