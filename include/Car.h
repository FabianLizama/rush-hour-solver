#include "Board.h"

class Car{
    public:
    int id;
    Board *board; // pointer to the board
    int x;
    int y;
    int length;
    bool direction; // 0 = horizontal, 1 = vertical

    Car(Board *board, int x, int y, int length, int direction); // constructor
    int getX();
    int getY();
    int getLength();
    bool getDirection();
    void move(int direction, int steps); // 0 = left or up, 1 = right or down
};