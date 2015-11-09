/*
 * Movement.cpp
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#include "Movement.h"

Movement::Movement(int fromY, int fromX, int toY, int toX, char color,
		int roundID) {
	from.push_back(fromY);
	from.push_back(fromX);
	to.push_back(toY);
	to.push_back(toX);
	this->color = color;
	this->roundID = roundID;
}

Movement::~Movement() {
}

bool Movement::isEqual(Movement *movement) {
	if (from[0] != movement->from[0])
		return false;
	if (from[1] != movement->from[1])
		return false;
	if (to[0] != movement->to[0])
		return false;
	if (to[1] != movement->to[1])
		return false;
	if (color != movement->color)
		return false;
	if (roundID != movement->roundID)
		return false;
	return true;
}

char Movement::getColor() {
	return color;
}

int Movement::getRoundID() {
	return roundID;
}

vector<int> Movement::getFrom() {
	return from;
}

vector<int> Movement::getTo() {
	return to;
}
