#include "Board.h"

Board::Board(int width, int height, int initX, int initY, int goalX, int goalY){
    this->width = width;
    this->height = height;
    this->board = new int*[width];
    for(int i = 0; i < width; i++){
        this->board[i] = new int[height];
    }
    this->lastCarId = 0;
    this->initX = initX;
    this->initY = initY;
    this->goalX = goalX;
    this->goalY = goalY;
};