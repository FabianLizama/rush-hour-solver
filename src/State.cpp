#include "../include/State.h"
#include "../include/Car.h"

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

State::State(){};

State::State(int id, int depth, int heuristic, int action, State *parent, Car* carList, int carListSize, int** carMatrix){
    this->id = id;
    this->depth = depth;
    this->heuristic = heuristic; 
    this->action = action;
    this->parent = nullptr;
    this->carList = carList;
    this->carListSize = carListSize;
    this->carMatrix = carMatrix;
};

bool State::isFinalState(){
    Car redCar = this->carList[0];
    if(redCar.getLength() == 2){
        if(redCar.getCoords()[2] == 5 && redCar.getCoords()[3] == 3){
            return true;
        }
    }
    else if (redCar.getLength() == 3){
        if(redCar.getCoords()[4] == 5 && redCar.getCoords()[5] == 3){
            return true;
        }
    }
    return false;
};

bool State::verifyCarMove(int carId, int movement){
    // Accedemos al auto que queremos verificar
    Car car = this->carList[carId];
    // Calculamos las coordenadas a las que se movería el auto
    int* tempCoords = car.calcMoveCoords(movement);
    //  Verificamos que todas sus coordenadas sean válidas
    for(int coord=0;coord<car.getLength();coord++){
        int currentX = tempCoords[coord*2];
        int currentY = tempCoords[coord*2+1];
        if(currentX < 0 || currentX > 5 || currentY < 0 || currentY > 5){
            return false;
        }
        if(this->carMatrix[currentY][currentX] != -1){
            return false;
        }
    }
    return true;
};