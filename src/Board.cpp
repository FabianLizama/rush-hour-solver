#include <iostream>
#include <typeinfo>
#include "../include/Board.h"

using namespace std;

Board::Board(int width, int height, int initX, int initY, int goalX, int goalY){
    this->width = width;
    this->height = height;
    this->board = new Car*[width];
    for(int i = 0; i < width; i++){
        this->board[i] = new Car[height];
    }
    this->lastCarId = -1;
    this->initX = initX;
    this->initY = initY;
    this->goalX = goalX;
    this->goalY = goalY;
};

// Los autos se representan con su id correspondiente, el auto rojo se representa con un 1
// Las casillas se representan con una x
void Board::printBoard(){

    // Se crea una matriz de characters para representar el tablero
    char** graphicBoard = new char*[this->width];
    for(int i = 0; i < this->width; i++){
        graphicBoard[i] = new char[this->height]();
    }

    // Se rellena la matriz
    for(int i = 0; i < this->width; i++){
        for(int j = 0; j < this->height; j++){
            if(!this->board[i][j].id == 0){ // Si hay un auto en la casilla
                graphicBoard[i][j] = this->board[i][j].id;
                if(this->board[i][j].getDirection() == 0){ // Si el auto es horizontal
                    for(int k = 1; k < this->board[i][j].getLength(); k++){ // Se dibuja el resto del auto
                        graphicBoard[i][j+k] = this->board[i][j].id;
                    }
                }else{ // Si el auto es vertical
                    for(int k = 1; k < this->board[i][j].getLength(); k++){ // Se dibuja el resto del auto
                        graphicBoard[i+k][j] = this->board[i][j].id;
                    }
                }
            }
        }
    }
    // Se imprime la matriz
    for(int i = 0; i < this->width; i++){
        for(int j = 0; j < this->height; j++){
            cout << graphicBoard[i][j] << " ";
        }
        cout << endl;
    }
};
