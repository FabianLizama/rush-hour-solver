#pragma once
#include "Car.h"
#include "Stack.h"

//Corresponde al nodo del árbol de posibilidades para el algoritmo A*
//La heurística a utilizar será el número de 
class State{
    public:
    int g; // costo
    int h; // heurística
    int id; // id of the state
    int heuristic; // heuristic value of the state
    int action; // action taken to reach this state
    Car* carList; // list of cars in the state
    int carListSize; // size of the list of cars
    int** carMatrix; // matrix of cars in the state
    char* lastMove; // last move made to reach this state
    Stack path; // path to reach this state

    // Constructores
    State();
    State(int id, int heuristic, int action, Car* carList, int carListSize, int** carMatrix, char* lastMove); // constructor
    
    // Selectores
    Car* getCarList();
    int** getCarMatrix();
    int getCarListSize();
    char* getLastMove();
    int getHeuristic();
    int getF();

    // Modificadores
    void setHeuristic(int heuristic);
    void setCar(Car car);

    bool isFinalState(); // checks if the state is the final state
    bool verifyCarMove(int carId, int movement); // checks if the car can move in the given direction
    void calculateHeuristic(); // calculates the heuristic value of the state
    void updateCarMatrix(int* oldCoords, int* newCoords, Car car); // updates the car matrix of the state
    void printRoute(); // prints the state
    bool equals(State* state); // checks if two states are equal
    void printBoard(); // prints the board of the state
};