/* main.cpp */
#include <iostream>
#include "Board.h"
#include "Node.h"

using namespace std;

int main(int argc, char *argv[]) {
    Node node(0, 0);
    Board board;
    Move* test;

    test = board.UCTSearch(1000);
    board.makeMove(test);
    cout << board;
    cout << "OK" << endl;
}
