#pragma once
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