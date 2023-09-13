#pragma once

class Car{
    public:
    bool exists;
    int id;
    int x;
    int y;
    int length;
    bool direction; // 0 = horizontal, 1 = vertical

    Car();
    Car(int id, int x, int y, int length, int direction); // constructor
    int getId();
    int getX();
    int getY();
    int getLength();
    bool getDirection();
    void move(int movement);
};