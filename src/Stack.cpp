#include <iostream>
#include "../include/Stack.h"

using namespace std;

Stack::Stack()
{
    this->height = 0;
    this->stack = new char*[100];
    this->capacity = 100;
};

Stack::~Stack(){
    delete[] this->stack;
};

void Stack::push(char* string){
    if (this->capacity == this->height){
        char** newStack = new char*[this->capacity*2];
        for (int i = 0; i < this->capacity; i++){
            newStack[i] = this->stack[i];
        }
        delete[] this->stack;
        this->stack = newStack;
        this->capacity = this->capacity*2;
    }

    this->stack[this->height] = string;
    this->height++;
};

char* Stack::pop(){
    if (this->isEmpty()){
        return nullptr;
    }
    this->height--;
    return this->stack[this->height];
};

bool Stack::isEmpty(){
    if (this->height == 0){
        return true;
    }
    return false;
};

void Stack::printStack(){
    char* string;
    while((string = this->pop()) != nullptr){
        cout << string << endl;
    }
};