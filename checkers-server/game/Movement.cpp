/*
 * Movement.cpp
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#include "Movement.h"

Movement::Movement() {
	// TODO Auto-generated constructor stub

}

Movement::~Movement() {
}

bool Movement::isEqual(Movement *movement){
	if (from[0] != movement->from[0]) return false;
	if (from[1] != movement->from[1]) return false;
	if (to[0] != movement->to[0]) return false;
	if (to[1] != movement->to[1]) return false;
	if (color!=movement->color) return false;
	return true;
}

