/*
 * Movement.h
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#ifndef GAME_MOVEMENT_H_
#define GAME_MOVEMENT_H_

#include <vector>

using namespace std;

class Movement {
private:
	vector<int> from;
	vector<int> to;
	char color;
	int roundID;

public:
	Movement(int fromY, int fromX, int toY, int toX, char color, int roundID);
	virtual ~Movement();

	bool isEqual(Movement *movement);

	vector<int> getFrom();
	vector<int> getTo();
	int getRoundID();
	char getColor();
};

#endif /* GAME_MOVEMENT_H_ */
