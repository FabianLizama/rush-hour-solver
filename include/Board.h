#pragma once
#include "Car.h"

class Board{
    public:
    int width = 6;
    int height = 6;
    Car **board;
    int initX, initY; // initial position of the red car
    int goalX, goalY; // goal position of the red car

    Board(); // default constructor
    Board(int width, int height, int initX, int initY, int goalX, int goalY); // constructor
    Board readInputFile(std::string filename); // reads the input file and creates the board
    void printBoard();
    int addCar(Car car);
    bool solve();
};