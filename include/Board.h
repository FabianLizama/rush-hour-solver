#pragma once
#include "Car.h"

class Board{
    public:
    int width;
    int height;
    Car **board;
    int lastCarId; // id of the last car created
    int initX, initY; // initial position of the red car
    int goalX, goalY; // goal position of the red car

    Board(int width, int height, int initX, int initY, int goalX, int goalY); // constructor
    void printBoard();
};