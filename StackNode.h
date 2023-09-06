#include "State.h"
#pragma once

class StackNode {
public:
    State *state;
    StackNode *next;

    StackNode(State *state); // constructor
};