#include <iostream>
#include "../include/Stack.h"

using namespace std;

Stack::Stack()
{
    this->top = nullptr;
    this->height = 0;
};

Stack::~Stack()
{
    StackNode *current = this->top;
    StackNode *next = nullptr;

    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
};

void Stack::push(State *state){
    StackNode *newNode = new StackNode(state);
    newNode->next = this->top;
    this->top = newNode;
    this->height++;
};

State *Stack::pop(){
    if (this->isEmpty()) {
        return nullptr;
    }
    StackNode *topState = this->top;
    this->top = topState->next;
    this->height--;
    return topState->state;
};

bool Stack::isEmpty(){
    if (this->top == nullptr){
        return true;
    }
    return false;
};

void Stack::printStack(){
    cout << "[";
    StackNode *actual = this->top;
    while (actual != nullptr){
        cout << actual->state->action;
        if (actual->next != nullptr){
            cout << ", ";
        }
    }
    cout << "]" << endl;
};