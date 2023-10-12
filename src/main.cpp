#include <iostream>
#include <string>
#include <chrono>
#include "../include/Board.h"
#include "../include/State.h"
#include "../include/Car.h"

using namespace std;

int main() {
    Board board = Board();
    try {
        std::string option, boardInput, wallInput;

        std::cout << "Seleccione uno de los 9 tableros a resolver ingresando un numero del 1 al 9:" << std::endl;
        std::cin >> option;

        boardInput = "./games/game" + option + ".txt";
        wallInput = "./games/walls" + option + ".txt";

        board.readInputFile(boardInput, wallInput);
        std::cout << "El tablero seleccionado es el siguiente: " << std::endl;
        board.printBoard();

        auto start = std::chrono::high_resolution_clock::now();

        State* initialState = new State(0, -1, -1, board.carList, board.carListSize, board.carMatrix, nullptr);
        initialState->printBoard();
        
        State* solution = board.solve(initialState);
        if (solution == nullptr){
            cout << "Solution not found" << endl;
        } else {
            cout << "Solution found" << endl;
            solution->printRoute();
            board.carMatrix = solution->getCarMatrix();
            board.carList = solution->getCarList();
            board.printBoard();
        }
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start; 
        std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
};