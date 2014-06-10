/* Board.h */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "Node.h"
#include "Move.h"
#include <cstdlib>
#include <cmath>
#define BOARD_SIZE 9

class Board {
	public:
		int b[BOARD_SIZE][BOARD_SIZE];
		int player;
		Node* root;

		Board();
		virtual ~Board();
		Node* getBestChild(Node& root);
		Node* UCTSelect(Node& node);
		int playSimulation(Node& node);
		Move* UCTSearch(int time);
		bool createChildren(Node& root);
		bool isLegalPlay(int player, int x, int y);
		void copyStateFrom(const Board* orig);

};
#endif /* __BOARD_H__ */
