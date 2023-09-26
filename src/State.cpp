#include "../include/State.h"
#include "../include/Car.h"

State::State(){};

State::State(int id, int depth, int heuristic, int action, State *parent, Car* carList){
    this->id = id;
    this->depth = depth;
    this->heuristic = heuristic; 
    this->action = action;
    this->parent = nullptr;
    this->carList = carList;
};