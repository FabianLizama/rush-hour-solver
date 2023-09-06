#include "State.h"
#include "StackNode.h"

#pragma once

class Stack {
public:
    StackNode *top;
    int height;

    Stack();
    ~Stack();
    void push(State *state);
    State *pop();
    bool isEmpty();
    void printStack();
};
