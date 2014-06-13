/* Board.h */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#define BOARD_SIZE 9

class Board {
	private:
		int b[BOARD_SIZE][BOARD_SIZE];
		int player;
		double moku1;
		double moku2;
		Node* root;

	public:
		Board();
		virtual ~Board();
		void changePlayer();
		Node* getBestChild(Node& root);
		Node* UCTSelect(Node& node);
		int playSimulation(Node& node);
		void UCTSearch(int time);
		bool createChildren(Node& root);
		void deleteChildren(Node* root);
		bool isLegalPlay(int x, int y);
		void copyStateFrom(const Board* orig);
		void makeMove(int x, int y);
		void makeRandomMove();
		int playRandomGame();
		bool isFinished();
		int getWinner();
		bool isDead(int x, int y);
		int removeGroup(int x, int y);

		friend std::ostream & operator<<(std::ostream & os, const Board &board);
};
#endif /* __BOARD_H__ */
