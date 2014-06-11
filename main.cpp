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

    srand(time(0));

    //test = board.UCTSearch(1000);
    //board.makeMove(test);
    for(int i = 0; i < 50; i++) {
        board.makeRandomMove();
    }
    cout << board;
    cout << "OK" << endl;
}
