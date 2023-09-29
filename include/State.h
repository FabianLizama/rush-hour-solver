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
    char* lastMove; // last move made to reach this state

    // Constructores
    State();
    State(int id, int depth, int heuristic, int action, State* parent, Car* carList, int carListSize, int** carMatrix, char* lastMove); // constructor
    
    // Selectores
    Car* getCarList();
    int** getCarMatrix();
    int getCarListSize();
    char* getLastMove();

    // Modificadores
    void setHeuristic(int heuristic);
    void setCar(Car car);
    
    bool isFinalState(); // checks if the state is the final state
    bool verifyCarMove(int carId, int movement); // checks if the car can move in the given direction
    void calculateHeuristic(); // calculates the heuristic value of the state
    void updateCarMatrix(int carId); // updates the car matrix of the state
    void printRoute(); // prints the state
};