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
        board.readInputFile("in.txt", "wall1.txt");
        board.printBoard();
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
};