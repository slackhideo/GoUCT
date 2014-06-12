/* Node.cpp */

#include <cstdlib>
#include "Node.h"

Node::Node(int x, int y) {
    this->wins = 0;
    this->visits = 0;
    this->x = x;
    this->y = y;
    this->child = NULL;
    this->sibling = NULL;
}

Node::~Node() {
	if(this->sibling != NULL) delete(this->sibling);
	if(this->child != NULL) delete(this->child);
}

void Node::update(int val) {
    this->visits++;
    this->wins += val;
}

double Node::getWinRate() {
    if(this->visits > 0) {
        return (double)(wins / visits);
    }
    else {
        return 0; /* Should not happen */
    }
}
