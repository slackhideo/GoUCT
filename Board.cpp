/* Board.cpp */

#include "Board.h"

Board::Board() {
	this->player = 1;
	this->root = new Node(-1, -1);
	for(int i = 0; i < BOARD_SIZE; i++) {
		for(int j = 0; j < BOARD_SIZE; j++) {
			this->b[i][j] = 0;
		}
	}
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
		randomresult = playRandomGame();
	}
	else {
		if(node.child == NULL) createChildren(node);

		Node* next = UCTSelect(node);
		makeMove(next->x, next->y);
		
		int res = playSimulation(*next);
		randomresult = 1-res;
	}

	node.update(1-randomresult);
	return randomresult;
}

Move* Board::UCTSearch(int time) {
	Node root(-1,-1);
	createChildren(root);

	Board clone;
	for(int i = 0; i < time; i++) {
		clone.copyStateFrom(this);
		clone.playSimulation(root);
	}

	Node* n = getBestChild(root);
	return new Move(n->x, n->y);
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

void Board::copyStateFrom(const Board* orig) {
	for(int i = 0; i < BOARD_SIZE; i++) {
		for(int j = 0; j < BOARD_SIZE; j++) {
			this->b[i][j] = orig->b[i][j];
		}
	}
	this->player = orig->player;
}

void Board::makeMove(int x, int y) {
	this->b[x][y] = this->player;
}

void Board::makeMove(const Move* move) {
	this->b[move->x][move->y] = this->player;
}

int Board::playRandomGame() {
	// TODO:
	// -- Find the end position of a game
	// -- consider illegal plays in the board
	// -- Find out who won from an end game
	return 1;
}

std::ostream & operator<<(std::ostream & os, const Board &board) {
	using namespace std;

	for(int i = 0; i < BOARD_SIZE; i++) {
		for(int j = 0; j < BOARD_SIZE; j++) {
			switch(board.b[i][j]) {
			case 0:
				os << ". ";
				break;
			case 1:
				os << "X ";
				break;
			case 2:
				os << "O ";
				break;
			}
		}
		os << endl;
	}

}
