#include <iostream>
#include "../include/MinHeap.h"
#include "../include/State.h"

MinHeap::MinHeap(int capacity){
    heap = new State[capacity];
    this->capacity = capacity;
    size = 0;
}

void MinHeap::insert(State state){
    if(size == capacity){
        capacityDoubler();
    }
    heap[size] = state;
    size++;
    int i = size - 1;
    // Si el padre tiene una heurística mayor, se intercambian
    while(i != 0 && heap[i].parent->heuristic > heap[i].heuristic){
        // Primero se cambian los padres
        heap[i].parent = heap[i].parent->parent;
        heap[i].parent->parent = &heap[i];
        // Luego su posición en el heap
        State temp = heap[i];
        heap[i] = *heap[i].parent;
        *heap[i].parent = temp;
        i = (i-1)/2;
    }
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

bool MinHeap::includes(State state){
    int i=0;
    while (i < size){
        if (heap[i].id == state.id){
            return true;
        } else if (heap[2*i+1].heuristic > state.heuristic){
            i = 2*i+2;
        } else if (heap[2*i+2].heuristic > state.heuristic){
            i = 2*i+1;
        } else {
            return false;
        }
    }
    std::cout << "Error: state not found" << std::endl;
    return false;
}
