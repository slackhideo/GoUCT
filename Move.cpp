/* Move.cpp */

#include "Move.h"

Move::Move(int x, int y) {
	this->x = x;
	this->y = y;
}

Move::~Move(){
}

int Move::getX() const {
	return this->x;
}

int Move::getY() const {
	return this->y;
}
