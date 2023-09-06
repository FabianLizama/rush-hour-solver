#include "StackNode.h"

StackNode::StackNode(State *state)
{
    this->state = state;
    this->next = nullptr;
}