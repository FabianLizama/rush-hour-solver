#pragma once
#include "Car.h"
#include "State.h"

class Board{
    public:
    int width = 6;
    int height = 6;
    Car* carList; // list of cars
    int carListSize; // size of the list of cars
    int** carMatrix; // matrix of cars
    //char** graphicBoard; // matrix that represents the board

    // Constructores
    Board(); // default constructor
    void readInputFile(std::string filename, std::string wallFilename); // reads the input file and creates the board
    
    // Selectores
    Car* getCarList();

    // Modificadores
    void setCarList(Car* carList);

    void printBoard();
    bool addCar(Car* car);
    State* solve(State* initialState);

};