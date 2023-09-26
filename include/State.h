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

    State();
    State(int id, int depth, int heuristic, int action, State* parent, Car* carList); // constructor
    void generateChildrens(); // generates the children of the state
};