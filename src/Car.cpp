#include "../include/Car.h"

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

Car::Car(){
    this->exists = false;
}; // default constructor

Car::Car(int id, int x, int y, int length, int direction){
    this->exists = true;
    this->id = id;
    this->x = x;
    this->y = y;
    this->length = length;
    this->direction = direction;
};

int Car::getId(){
    return this->id;
};

int Car::getX(){
    return this->x;
};

int Car::getY(){
    return this->y;
};

int Car::getLength(){
    return this->length;
};

bool Car::getDirection(){
    return this->direction;
};

void Car::move(int direction){
    if(this->direction == 0){ // horizontal
        if(direction == LEFT){
            this->x--;
        }else if(direction == RIGHT){
            this->x++;
        }
    }else{ // vertical
        if(direction == UP){
            this->y--;
        }else if(direction == DOWN){
            this->y++;
        }
    }
}