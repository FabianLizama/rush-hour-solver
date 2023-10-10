#include <iostream>
#include <string>
#include "../include/Board.h"
#include "../include/State.h"
#include "../include/Car.h"

using namespace std;

int main() {
    Board board = Board();
    try {
        board.readInputFile("in.txt", "wall1.txt");
        board.printBoard();

        State* initialState = new State(0, 1000000, -1, board.carList, board.carListSize, board.carMatrix, nullptr);
        
        State* solution = board.solve(initialState);
        if (solution == nullptr){
            cout << "No solution found" << endl;
        } else {
            cout << "Solution found" << endl;
            solution->printBoard();
        }

    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
};