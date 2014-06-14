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
	delete(this->root);
}

/* Changes the current player */
void Board::changePlayer() {
	this->player = 3 - this->player;
}

/* Select the child from a Node with the most number of simulations */
Node* Board::getBestChild(Node& root) {
	Node* child = root.getChild();
	Node* best_child = NULL;
	int best_visits = -1;
	while(child != NULL) {
		if(child->getVisits() > best_visits) {
			best_child = child;
			best_visits = child->getVisits();
		}
		child = child->getSibling();
	}

	return best_child;
}

/* Select the best child from a Node based on UCT value */
Node* Board::UCTSelect(Node& node) {
	Node* res = NULL;
	Node* next = node.getChild();
	double best_uct = 0;

	while(next != NULL) {
		double uctvalue;
		if(next->getVisits() > 0) {
			double winrate = next->getWinRate();
			double uct = 0.44 * sqrt(log(node.getVisits()) / next->getVisits());
			uctvalue = winrate + uct;
		}
		else {
			uctvalue = 10000 + 1000*(rand()%1000);
		}

		if(uctvalue > best_uct) {
			best_uct = uctvalue;
			res = next;
		}

		next = next->getSibling();
	}

	return res;
}

/* Plays a game simulation and returns who was the winner saving the wins and
 * games on the tree nodes */
int Board::playSimulation(Node& node) {
	int randomresult = 0;
	if(node.getChild() == NULL && node.getVisits() < 10) {
		randomresult = playRandomGame();
	}
	else {
		if(node.getChild() == NULL) createChildren(node);

		Node* next = UCTSelect(node);
		makeMove(next->getX(), next->getY());

		int res = playSimulation(*next);
		randomresult = 1-res;
	}

	node.update(1-randomresult);
	return randomresult;
}

/* Makes simulations and plays the best move possible */
void Board::UCTSearch(int time) {
	Node root(-1,-1);
	createChildren(root);

	Board clone;
	for(int i = 0; i < time; i++) {
		clone.copyStateFrom(this);
		clone.playSimulation(root);
	}

	Node* n = getBestChild(root);
	makeMove(n->getX(), n->getY());
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
					root.setChild(new Node(i,j));
					last = root.getChild();
				}
				else {
					last->setSibling(new Node(i,j));
					last = last->getSibling();
				}
			}
		}
	}

	return ret;
}

/* Checks if the move is legal */
bool Board::isLegalPlay(int x, int y) {
	bool suicide;
	bool kills = false;

	if(this->b[x][y] != 0) return false;

	// Check if suicide play
	this->b[x][y] = this->player;
	suicide = isDead(x, y);
	// Check if kills any opponent stones
	kills = ((x == 0 || this->player != 3-b[x-1][y] ? false : isDead(x-1,y))
		|| (y == BOARD_SIZE-1 || this->player != 3-b[x][y+1] ? false : isDead(x,y+1))
		|| (x == BOARD_SIZE-1 || this->player != 3-b[x+1][y] ? false : isDead(x+1,y))
		|| (y == 0 || this->player != 3-b[x][y-1] ? false : isDead(x,y-1)));

	this->b[x][y] = 0;
	return ((!suicide) || kills);
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
	if(isLegalPlay(x,y)) {
		this->b[x][y] = this->player;
		this->changePlayer();
		// Checks and removes if move captures any stone
		if(x > 0 && b[x-1][y] == this->player && isDead(x-1,y)) removeGroup(x-1,y);
		if(y < BOARD_SIZE-1 && b[x][y+1] == this->player && isDead(x,y+1)) removeGroup(x,y+1);
		if(x < BOARD_SIZE-1 && b[x+1][y] == this->player && isDead(x+1,y)) removeGroup(x+1,y);
		if(y > 0 && b[x][y-1] == this->player && isDead(x,y-1)) removeGroup(x,y-1);
	}
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
int Board::getWinner() {
	Board clone;
	int p1pts = 0, p2pts = 0;
	int value;

	clone.copyStateFrom(this);

	/* Extends players territories with their stones */
	for(int k = 0; k < TERR_ITER_NUMBER; k++) {
		for(int i = 0; i < BOARD_SIZE; i++) {
			for(int j = 0; j < BOARD_SIZE; j++) {
				if(this->b[i][j] == 0) {
					clone.b[i][j] = this->own(i, j);
				}
			}
		}
	}

	/* Counts each player's stones */
	for(int i = 0; i < BOARD_SIZE; i++) {
		for(int j = 0; j < BOARD_SIZE; j++) {
			value = clone.own(i, j);
			switch(value) {
				case 1:
					p1pts++;
					break;
				case 2:
					p2pts++;
					break;
			}
		}
	}
	std::cout << "P1 pts: " << p1pts << std::endl;
	std::cout << "P2 pts: " << p2pts << std::endl;

	/* Player 1 wins */
	if(p1pts > p2pts) {
		return 1;
	}

	/* Player 2 wins */
	else if(p1pts < p2pts) {
		return 2;
	}

	/* Draw */
	else {
		return 0;
	}
}

/* Verifies and returns which player owns (approximately) a board position */
int Board::own(int x, int y) {
	/* Trivial case: there is a player's stone */
	if(this->b[x][y] == 1) {
		return 1;
	}
	else if(this->b[x][y] == 2) {
		return 2;
	}

	/* Case where there is no stone: verify adjacent positions */
	else {
		int p1stones = 0, p2stones = 0;
		int value;
		if(x > 0) {
			value = this->b[x-1][y];
			this->updateStones(value, p1stones, p2stones);
		}
		if(y < BOARD_SIZE-1) {
			value = this->b[x][y+1];
			this->updateStones(value, p1stones, p2stones);
		}
		if(x < BOARD_SIZE-1) {
			value = this->b[x+1][y];
			this->updateStones(value, p1stones, p2stones);
		}
		if(y > 0) {
			value = this->b[x][y-1];
			this->updateStones(value, p1stones, p2stones);
		}

		if(p1stones > p2stones) {
			return 1;
		}
		else if(p1stones < p2stones) {
			return 2;
		}
		else {
			return 0;
		}
	}
}

/* Updates the number of stones around a board position */
void Board::updateStones(int value, int& p1stones, int& p2stones) {
	switch(value) {
		case 1:
			p1stones++;
			break;
		case 2:
			p2stones++;
			break;
	}
}

/* Checks if a group of pieces is dead */
bool Board::isDead(int x, int y) {
	// first checks if there is any liberty on the sides
	if((x > 0 && b[x-1][y] == 0) || (y < BOARD_SIZE-1 && b[x][y+1] == 0) ||
	 (x < BOARD_SIZE-1 && b[x+1][y] == 0) || (y > 0 && b[x][y-1] == 0)) {
		return false;
	}
	bool north = true;
	bool east = true;
	bool south = true;
	bool west = true;

	int group = b[x][y];
	/* recursively checks other stones of the same group */

	// marks as already visited
	b[x][y] *= -1;

	// checks north
	if(x > 0 && group == b[x-1][y]) {
		north = isDead(x-1, y);
		
	}
	// checks east
	if(y < BOARD_SIZE-1 && group == b[x][y+1]) {
		east = isDead(x, y+1);
	}
	// checks south
	if(x < BOARD_SIZE-1 && group == b[x+1][y]) {
		south = isDead(x+1, y);
	}
	// checks west
	if(y > 0 && group == b[x][y-1]) {
		west = isDead(x, y-1);
	}

	// returns board to original state
	b[x][y] *= -1;

	return (north && west && south && east);
}

int Board::removeGroup(int x, int y) {
	int group = b[x][y];

	int north = 0;
	int east = 0;
	int south = 0;
	int west = 0;

	b[x][y] = 0;
	// if(group == 1) captures2++;
	// else captures1++;
	// removes north if from the same group
	if(x > 0 && b[x-1][y] == group) north = removeGroup(x-1,y);
	// removes east if from the same group
	if(y < BOARD_SIZE-1 && b[x][y+1] == group) east = removeGroup(x,y+1);
	// removes south if from the same group
	if(x < BOARD_SIZE-1 && b[x+1][y] == group) south = removeGroup(x+1,y);
	// removes west if from the same group
	if(y > 0 && b[x][y-1] == group) west = removeGroup(x,y-1);

	return 1+north+east+south+west;
}

void Board::influence() {
	Board clone;
	Board temp;

	clone.copyStateFrom(this);
	std::cout << "START" << std::endl;
	for(int i = 0; i < BOARD_SIZE; i++) {
		for(int j = 0; j < BOARD_SIZE; j++) {
			if(clone.b[i][j] != 0) clone.b[i][j] = clone.b[i][j] == 1 ? 50 : -50;
		}
	}
	temp.copyStateFrom(&clone);
	for(int t = 0; t < 4; t++) {
		for(int i = 0; i < BOARD_SIZE; i++) {
			for(int j = 0; j < BOARD_SIZE; j++) {
				int north = i == 0 ? 0 : clone.b[i-1][j];
				int east = j == BOARD_SIZE-1 ? 0 : clone.b[i][j+1];
				int south = i == BOARD_SIZE-1 ? 0 : clone.b[i+1][j];
				int west = j == 0 ? 0 : clone.b[i][j-1];
				temp.b[i][j] += north + east + south + west;
			}
		}
		clone.copyStateFrom(&temp);
	}
	for(int i = 0; i < BOARD_SIZE; i++) {
		for(int j = 0; j < BOARD_SIZE; j++) {
			if(clone.b[i][j] > 1000) std::cout << "+ ";
			else if(clone.b[i][j] < -1000) std::cout << "- ";
			else std::cout << ". ";
		}
		std::cout << std::endl;
	}
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
