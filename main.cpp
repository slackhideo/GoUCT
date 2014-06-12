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

    Node node(0, 0);
    Board board;
    Move* test;

    srand(time(0));

    board.makeMove(0,1);
    board.makeMove(0,2);
    board.makeMove(1,2);
    board.makeMove(1,3);
    board.makeMove(2,1);
    board.makeMove(2,2);
    board.makeMove(1,0);
    board.makeMove(2,3);
    board.makeMove(0,3);

    //test = board.UCTSearch(1000);
    //board.makeMove(test);
    //for(int i = 0; i < 50; i++) {
    //    board.makeRandomMove();
    //}
    cout << board;
    cout << "OK" << endl;
}
