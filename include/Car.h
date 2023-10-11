#pragma once

class Car{
    public:
    bool exists;
    int id;
    int* coords;
    int length;
    bool direction; // 0 = horizontal, 1 = vertical

    // Constructores
    Car();
    Car(int id, int* coords, int length, int direction); // constructor
    
    // Selectores
    int getId();
    int* getCoords();
    int getLength();
    bool getDirection();
    
    // Modificadores
    void setId(int id);
    void setCoords(int* coords);
    void move(int* coords);
    
    //Otros
    int* calcMoveCoords(int movement);
    Car* clone();
};