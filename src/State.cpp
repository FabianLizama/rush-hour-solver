#include "../include/State.h"

State::State(int depth, int heuristic, int cost, int action, State *parent){
    this->depth = depth;
    this->heuristic = heuristic; 
    this->action = action;
    this->parent = nullptr;
};