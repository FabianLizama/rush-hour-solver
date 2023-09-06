#include <iostream>
#include "../include/Board.h"
#include "../include/State.h"
#include "../include/Car.h"
#include "../include/Stack.h"


using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    Board *board = new Board(6, 6, 0, 0, 5, 5);
    board->printBoard();
    return 0;
};