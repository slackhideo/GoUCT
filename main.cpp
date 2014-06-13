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
    board.makeMove(0,2);
    cout << "-------------------" << endl << board;
    board.makeMove(1,2);
    cout << "-------------------" << endl << board;
    board.makeMove(0,1);
    cout << "-------------------" << endl << board;
    board.makeMove(1,1);
    cout << "-------------------" << endl << board;
    board.makeMove(0,0);
    cout << "-------------------" << endl << board;
    board.makeMove(1,0);
    cout << "-------------------" << endl << board;
*/
    board.UCTSearch(1000);
    for(int i = 0; i < 60; i++) {
        board.makeRandomMove();
        cout << "-------------------" << endl << board;
    }
    board.influence();
    cout << "OK" << endl;
}
