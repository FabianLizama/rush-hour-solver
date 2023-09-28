#pragma once
#include "Car.h"

//Corresponde al nodo del árbol de posibilidades para el algoritmo A*
//La heurística a utilizar será el número de 
class State{
    public:
    int id;
    int depth; // depth of the state
    int heuristic; // heuristic value of the state
    int action; // action taken to reach this state
    State* parent; // pointer to the parent state
    Car* carList; // list of cars in the state
    int carListSize; // size of the list of cars
    int** carMatrix; // matrix of cars in the state

    State();
    State(int id, int depth, int heuristic, int action, State* parent, Car* carList, int carListSize, int** carMatrix); // constructor
    bool isFinalState(); // checks if the state is the final state
    bool verifyCarMove(int carId, int movement); // checks if the car can move in the given direction
    int calculateHeuristic(int** carMatrix, int carList, int carListSize); // calculates the heuristic value of the state
};