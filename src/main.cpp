#include <iostream>
#include <string>
#include "../include/Board.h"
#include "../include/State.h"
#include "../include/Car.h"
#include "../include/Stack.h"


using namespace std;

int main() {
    Board board = Board();
    try {
        board = board.readInputFile("todo.txt");
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    board.printBoard();
    return 0;
};