#pragma once
#include "Car.h"

class Board{
    public:
    int width = 6;
    int height = 6;
    Car* carList; // list of cars
    int carListSize; // size of the list of cars

    // Constructores
    Board(); // default constructor
    Board readInputFile(std::string filename); // reads the input file and creates the board
    
    // Selectores
    Car* getCarList();

    // Modificadores
    void setCarList(Car* carList);

    void printBoard();
    bool addCar(Car car);
    Board solve();

};