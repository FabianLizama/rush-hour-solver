#include "../include/State.h"
#include "../include/Car.h"

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

State::State(){};

State::State(int id, int depth, int heuristic, int action, State *parent, Car* carList, int carListSize){
    this->id = id;
    this->depth = depth;
    this->heuristic = heuristic; 
    this->action = action;
    this->parent = nullptr;
    this->carList = carList;
    this->carListSize = carListSize;
};

bool State::isFinalState(){
    Car redCar = this->carList[0];
    for(int i=0; i<redCar.getLength(); i++){
        if(redCar.getY() == 3 && redCar.getX()+i == 5){
            return true;
        }
    }
    return false;
};

bool State::verifyCarMove(int carId, int movement){
    Car car = this->carList[carId];
    // TODO
}