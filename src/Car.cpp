#include "../include/Car.h"

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

Car::Car(){
    this->exists = false;
}; // default constructor

Car::Car(int id, int* coords, int length, int direction){
    this->exists = true;
    this->id = id;
    this->coords = coords;
    this->length = length;
    this->direction = direction;
};

int Car::getId(){
    return this->id;
};

int* Car::getCoords(){
    return this->coords;
};

int Car::getLength(){
    return this->length;
};

bool Car::getDirection(){
    return this->direction;
};

void Car::setCoords(int* coords){
    this->coords = coords;
};

void Car::move(int* coords){
    this->setCoords(coords);
}
int* Car::calcMoveCoords(int direction){
    int* tempCoords = this->coords;
    if(this->direction == 0){ // horizontal
        if(direction == LEFT){
            for(int i=0; i<this->length; i++){
                tempCoords[2*i]--; // x
            }
        }else if(direction == RIGHT){
            for(int i=0; i<this->length; i++){
                tempCoords[2*i]++; // x
            }
        }
    }else{ // vertical
        if(direction == UP){
            for(int i=0; i<this->length; i++){
                tempCoords[2*i+1]--; // y
            }
        }else if(direction == DOWN){
            for(int i=0; i<this->length; i++){
                tempCoords[2*i+1]++; // y
            }
        }
    }
    return tempCoords;
}
