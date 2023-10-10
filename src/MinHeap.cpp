#include <iostream>
#include "../include/MinHeap.h"
#include "../include/State.h"

MinHeap::MinHeap(int capacity){
    heap = new State[capacity];
    this->capacity = capacity;
    size = 0;
}

void MinHeap::setSize(int size){
    this->size = size;
}

void MinHeap::insert(State* state){
    if(size == capacity){
        capacityDoubler();
    }

    if (size == 0){
        heap[0] = *state;
        size++;
        return;
    }

    heap[size] = *state;

    int i = size;
    while (i>0) {
        if (heap[i].getF() < heap[(i-1)/2].getF()){
            State temp = heap[i];
            heap[i] = heap[(i-1)/2];
            heap[(i-1)/2] = temp;
        }
        i = (i-1)/2;
    }
    setSize(size+1);
}

State* MinHeap::pop(){
    if (this->size == 1){
        setSize(0);
        return &heap[0];
    } else if (this->size != 0){
        State* root = &heap[0];
        heap[0] = heap[size-1];
        
        int i = size;
        while (i>0) {
            if (heap[i].getF() < heap[(i-1)/2].getF()){
                State temp = heap[i];
                heap[i] = heap[(i-1)/2];
                heap[(i-1)/2] = temp;
            }
            i = (i-1)/2;
        }
        setSize(size-1);
        return root;
    }
    return nullptr;
}

void MinHeap::capacityDoubler(){
    State* newHeap = new State[capacity*2];
    for(int i = 0; i < capacity; i++){
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
    capacity *= 2;
}

bool MinHeap::includes(State* state){
    //std::cout << "Estado a comparar: " << std::endl;
    int i=0;
    //state->printBoard();
    while (i < size){
        //std::cout << "Estado en heap: " << std::endl;
        //heap[i].printBoard();
        if (heap[i].equals(state)){
            return true;
        } else if (heap[2*i+1].getF() > state->getF()){
            i = 2*i+2;
        } else if (heap[2*i+2].getF() > state->getF()){
            i = 2*i+1;
        } else {
            return false;
        }
    }
    return false;
}

bool MinHeap::isEmpty(){
    return size == 0;
}

void MinHeap::printHeap(){
    std::cout << "[";
    for(int i=0; i<size; i++){
        std::cout << this->heap[i].id << " ";
    }
    std::cout << "]" << std::endl;
}