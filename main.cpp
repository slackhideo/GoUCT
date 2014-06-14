/* main.cpp */
#include <iostream>
#include <cstring>
#include "Board.h"
#include "Node.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc > 1 && strcmp(argv[1], "--help") == 0) {
        cout << "Help! I need somebody. Help! Not just anybody. Help!!" << endl;
        exit(0);
    }

    Board board;

    srand(time(0));

/*
    board.makeMove(6,8);
    cout << "-------------------" << endl << board;
    board.makeMove(0,0);
    cout << "-------------------" << endl << board;
    board.makeMove(7,8);
    cout << "-------------------" << endl << board;
    board.makeMove(0,1);
    cout << "-------------------" << endl << board;
    board.makeMove(7,7);
    cout << "-------------------" << endl << board;
    board.makeMove(0,2);
    cout << "-------------------" << endl << board;
    board.makeMove(8,7);
    cout << "-------------------" << endl << board;
    board.makeMove(0,3);
    cout << "-------------------" << endl << board;
    board.makeMove(8,6);
    cout << "-------------------" << endl << board;
    board.makeMove(8,8);
    cout << "-------------------" << endl << board;

    board.makeMove(5,3);
    cout << "-------------------" << endl << board;
    board.makeMove(5,5);
    cout << "-------------------" << endl << board;
    board.makeMove(6,3);
    cout << "-------------------" << endl << board;
    board.makeMove(6,5);
    cout << "-------------------" << endl << board;
    board.makeMove(7,3);
    cout << "-------------------" << endl << board;
    board.makeMove(7,5);
    cout << "-------------------" << endl << board;
    board.makeMove(8,3);
    cout << "-------------------" << endl << board;
    board.makeMove(8,5);
    cout << "-------------------" << endl << board;

//   board.UCTSearch(1000);
*/
    for(int i = 0; i < 80; i++) {
        board.makeRandomMove();
        cout << "-------------------" << endl << board;
    }

    board.influence();
    cout << "OK" << endl;
	cout << "And the winner is... player " << board.getWinner() << endl;
}
