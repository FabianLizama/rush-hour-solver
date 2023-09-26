#include "../include/State.h"

State::State(){};

State::State(int id, int depth, int heuristic, int cost, int action, State *parent){
    this->id = id;
    this->depth = depth;
    this->heuristic = heuristic; 
    this->action = action;
    this->parent = nullptr;
};