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
    board.makeMove(0,3);
    cout << "-------------------" << endl << board;
    board.makeMove(0,5);
    cout << "-------------------" << endl << board;
    board.makeMove(1,3);
    cout << "-------------------" << endl << board;
    board.makeMove(1,5);
    cout << "-------------------" << endl << board;
    board.makeMove(2,3);
    cout << "-------------------" << endl << board;
    board.makeMove(2,5);
    cout << "-------------------" << endl << board;
    board.makeMove(3,3);
    cout << "-------------------" << endl << board;
    board.makeMove(3,5);
    cout << "-------------------" << endl << board;
    board.makeMove(4,3);
    cout << "-------------------" << endl << board;
    board.makeMove(4,5);
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
*/
//   board.UCTSearch(1000);

    for(int i = 0; i < 80; i++) {
        board.makeRandomMove();
        cout << "-------------------" << endl << board;
    }
    board.influence();
    cout << "OK" << endl;
}
