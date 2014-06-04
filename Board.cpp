/* Board.cpp */

#include "Board.h"

Board::Board() {
	this->player = 1;
	this->root = new Node(-1, -1);
}

Board::~Board() {
}

Node* Board::getBestChild(Node& root) {
	Node* child = root.child;
	Node* best_child = NULL;
	int best_visits = -1;
	while(child != NULL) {
		if(child->visits > best_visits) {
			best_child = child;
			best_visits = child->visits;
		}
		child = child->sibling;
	}

	return best_child;
}

Node* Board::UCTSelect(Node& node) {
	Node* res = NULL;
	Node* next = node.child;
	double best_uct = 0;

	while(next != NULL) {
		double uctvalue;
		if(next->visits > 0) {
			double winrate = next->getWinRate();
			double uct = 0.44 * sqrt(log(node.visits) / next->visits);
			uctvalue = winrate + uct;
		}
		else {
			uctvalue = 10000 + 1000*(rand()%10000);
		}

		if(uctvalue > best_uct) {
			best_uct = uctvalue;
			res = next;
		}

		next = next->sibling;
	}

	return res;
}

int Board::playSimulation(Node& node) {
	int randomresult = 0;
	if(node.child == NULL && node.visits < 10) {
	//	randomresult = playRandomGame();
	}
	else {
		if(node.child == NULL) createChildren(node);

		Node* next = UCTSelect(node);
		//Makemove(next->x, next->y)
		
		int res = playSimulation(*next);
		randomresult = 1-res;
	}

	node.update(1-randomresult);
	return randomresult;
}

Move Board::UCTSearch(int time) {
}

bool Board::createChildren(Node& root) {
	Node* last = NULL;
	bool ret = false;
	for(int i = 0; i < BOARD_SIZE; i++) {
		for(int j = 0; j < BOARD_SIZE; j++) {
			if(this->b[i][j] == 0 && isLegalPlay(this->player, i, j)) {
				ret = true;
				if(last == NULL) {
					root.child = new Node(i,j);
					last = root.child;
				}
				else {
					last->sibling = new Node(i,j);
					last = last->sibling;
				}
			}
		}
	}

	return ret;
}

bool Board::isLegalPlay(int player, int x, int y) {
	return true;
}
