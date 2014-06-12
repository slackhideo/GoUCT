/* Board.cpp */

#include "Board.h"

/* Board class */
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

/* Changes the current player */
void Board::changePlayer() {
	this->player = 3 - this->player;
}

/* Select the child from a Node with the most number of simulations */
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

/* Select the best child from a Node based on UCT value */
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
			uctvalue = 10000 + 1000*(rand()%1000);
		}

		if(uctvalue > best_uct) {
			best_uct = uctvalue;
			res = next;
		}

		next = next->sibling;
	}

	return res;
}

/* Plays a game simulation and returns who was the winner saving the wins and
 * games on the tree nodes */
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

/* Makes simulations and plays the best move possible */
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

/* Creates all possible moves from root Node */
bool Board::createChildren(Node& root) {
	Node* last = NULL;
	bool ret = false;
	for(int i = 0; i < BOARD_SIZE; i++) {
		for(int j = 0; j < BOARD_SIZE; j++) {
			if(this->b[i][j] == 0 && isLegalPlay(i, j)) {
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

/* Checks if the move is legal */
bool Board::isLegalPlay(int x, int y) {
	bool result = false;

	if(this->b[x][y] != 0) return result;

	// Check if suicide play
	this->b[x][y] = this->player;
	result = isDead(x, y);
	this->b[x][y] = 0;
	return !result;
}

/* Copies the board state */
void Board::copyStateFrom(const Board* orig) {
	for(int i = 0; i < BOARD_SIZE; i++) {
		for(int j = 0; j < BOARD_SIZE; j++) {
			this->b[i][j] = orig->b[i][j];
		}
	}
	this->player = orig->player;
}

/* Plays a move on the board with the coordinates (x,y) */
void Board::makeMove(int x, int y) {
	this->b[x][y] = this->player;
	this->changePlayer();
}

/* Plays a move on the board with Move object */
void Board::makeMove(const Move* move) {
	this->b[move->x][move->y] = this->player;
	this->changePlayer();
}

/* Random chooses a position on the board to play. Tries until a legal move
 * is found */
void Board::makeRandomMove() {
	
	int x = rand()%BOARD_SIZE;
	int y = rand()%BOARD_SIZE;
	while(!isLegalPlay(x, y)) {
		x = rand()%BOARD_SIZE;
		y = rand()%BOARD_SIZE;
	}

	this->makeMove(x, y);
}

/* Plays random moves until endgame and returns the winner */
int Board::playRandomGame() {
	// TODO:
	// -- Find the end position of a game
	// -- consider illegal plays in the board
	// -- Find out who won from an end game
	
	int cur_player = this->player;
	while(!isFinished()) {
		this->makeRandomMove();
	}

	return getWinner() == cur_player ? 1 : 0;
}

/* Checks the board state and returns if the game is finished */
// TODO
bool Board::isFinished() {
	return true;
}

/* Checks the endgame board state and returns the winner of the game */
// TODO
int Board::getWinner() {
	return 1;
}

/* Checks if a group of pieces is dead */
// TODO
bool Board::isDead(int x, int y) {
	// first checks if there is any liberty on the sides
	if((x > 0 && b[x-1][y] == 0) || (y < BOARD_SIZE-1 && b[x][y+1] == 0) ||
	 (x < BOARD_SIZE-1 && b[x+1][y] == 0) || (y > 0 && b[x][y-1] == 0)) {
		return false;
	}
		

	return true;
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
	return os;
}
