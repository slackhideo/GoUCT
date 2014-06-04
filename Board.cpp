/* Board.cpp */

#include "Board.h"

Board::Board() {
	this->player = 1;
	this->root = new Node(-1, -1);
}

Board::~Board() {
}

Node* getBestChild(Node root) {
}

Node* UCTSelect(Node node) {
}

int playSimulation(Node node) {
}

Move UCTSearch(int time) {
}

void createChildren(Node root) {
}
