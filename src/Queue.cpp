#include "../include/Queue.h"
#include <iostream>

Queue::Queue(int maxSize){
    this->size = 0;
    this->maxSize = maxSize;
    this->queue = new char*[maxSize];
    for (int i = 0; i < maxSize; i++) {
        // id del auto y movimiento
        this->queue[i] = new char[3];
    }
};

int Queue::getSize(){
    return this->size;
};

int Queue::getMaxSize(){
    return this->maxSize;
};

char** Queue::getQueue(){
    return this->queue;
};

void Queue::push(char* element){
    if(this->size == this->maxSize){
        this->addMemory();
    }
    this->queue[this->size] = element;
};

char* Queue::pop(){
    if(this->size == 0){
        return nullptr;
    }
    char* element = this->queue[0];
    for(int i=0; i<this->size-1; i++){
        this->queue[i] = this->queue[i+1];
    }
    this->size--;
    return element;
};

void Queue::addMemory(){
    this->maxSize *= 2;
    char** newQueue = new char*[this->maxSize];
    for (int i = 0; i < this->maxSize; i++) {
        // id del auto y movimiento
        newQueue[i] = new char[3];
    }
    for(int i=0; i<this->size; i++){
        newQueue[i] = this->queue[i];
    }
    this->queue = newQueue;
};

void Queue::print(){
    for(int i=0; i<this->size; i++){
        char* string = this->pop();
        std::cout << "Paso " << i++ << ": " << "Auto " << string[0] << "Movimiento " << string[2] << std::endl;
    }
};