/* main.cpp */
#include <iostream>
#include "Board.h"
#include "Node.h"

using namespace std;

int main(int argc, char *argv[]) {
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
