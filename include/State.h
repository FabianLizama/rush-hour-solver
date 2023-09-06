#pragma once

//Corresponde al nodo del árbol de posibilidades para el algoritmo A*
//La heurística a utilizar será el número de 
class State{
    public:
    int depth; // depth of the state
    int heuristic; // heuristic value of the state
    int action; // action taken to reach this state
    State *parent; // pointer to the parent state

    State(int depth, int heuristic, int cost, int action, State *parent); // constructor
    void setNext(State *next);
    void printState();
};