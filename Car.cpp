#include "Car.h"

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

Car::Car(Board *board, int x, int y, int length, int direction){
    this->board = board;
    this->id = this->board->lastCarId++;
    this->x = x;
    this->y = y;
    this->length = length;
    this->direction = direction;
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

void Car::move(int direction, int steps){
    if(this->direction == 0){ // horizontal
        if(direction == LEFT){
            this->x -= steps;
        }else if(direction == RIGHT){
            this->x += steps;
        }
    }else{ // vertical
        if(direction == UP){
            this->y -= steps;
        }else if(direction == DOWN){
            this->y += steps;
        }
    }
}