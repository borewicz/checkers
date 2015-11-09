/*
 * Movement.h
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#ifndef GAME_MOVEMENT_H_
#define GAME_MOVEMENT_H_

class Movement {
private:
	int from[2];
	int to[2];
	char color;
public:
	int getFrom();
	int getTo();
	char getColor();
	bool isEqual(Movement *movement);
	Movement();
	virtual ~Movement();
};

#endif /* GAME_MOVEMENT_H_ */
