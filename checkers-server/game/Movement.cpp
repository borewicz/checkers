/*
 * Movement.cpp
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#include "Movement.h"
#include <boost/lexical_cast.hpp>

Movement::Movement(int coordinates[20], char color, int roundID) {
	for (int i = 0; i < 20; i = i + 2) {
		X.push_back(coordinates[i]);
	}
	for (int i = 1; i < 20; i = i + 2) {
		Y.push_back(coordinates[i]);
	}
	this->color = color;
	this->roundID = roundID;
	generateID();
}

Movement::Movement(){
	this->color = '0';
	this->roundID = 0;
	this->movementID="0";
}

Movement::~Movement() {
}

char Movement::getColor() {
	return color;
}

int Movement::getRoundID() {
	return roundID;
}

vector<int> Movement::getX() {
	return X;
}

vector<int> Movement::getY() {
	return Y;
}

string Movement::getMovementID() {
	return movementID;
}

void Movement::generateID() {
	movementID = "";
	for (int i = 0; i < 10; i++) {
		movementID += boost::lexical_cast<std::string>(X[i]);
		movementID += boost::lexical_cast<std::string>(Y[i]);
	}
	movementID = movementID + color + boost::lexical_cast<std::string>(roundID);
}
