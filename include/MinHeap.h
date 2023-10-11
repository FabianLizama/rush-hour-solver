#pragma once
#include "State.h"

class MinHeap{
    public:
        State* heap;
        int capacity;
        int size;

        // Constructores
        MinHeap(int capacity);
        // Selectores

        // Modificadores
        void setSize(int size);
        void insert(State state);
        State* pop();
        void capacityDoubler();
        
        // Otros
        bool includes(State* state);
        bool isEmpty();
        void printHeap();
};
