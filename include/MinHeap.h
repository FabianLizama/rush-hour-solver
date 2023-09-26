#pragma once
#include "State.h"

class MinHeap{
    public:
        State* heap;
        int capacity;
        int size;

        MinHeap(int capacity);
        void insert(State state);
        void capacityDoubler();
        bool includes(State state);
};
