#include "../include/State.h"
#include "../include/Car.h"
#include "../include/Queue.h"
#include <iostream>

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

State::State(){};

State::State(int id, int heuristic, int action, Car* carList, int carListSize, int** carMatrix, char* lastMove){
    this->id = id;
    this->heuristic = heuristic; 
    this->action = action;
    this->carList = carList;
    this->carListSize = carListSize;
    this->carMatrix = carMatrix;
    this->lastMove = lastMove;
    this->g = 0;
};

Car* State::getCarList(){
    return this->carList;
};

int** State::getCarMatrix(){
    return this->carMatrix;
};

int State::getCarListSize(){
    return this->carListSize;
};

char* State::getLastMove(){
    return this->lastMove;
};

int State::getHeuristic(){
    return this->heuristic;
};

int State::getF(){
    return this->g + this->heuristic;
};

void State::setHeuristic(int heuristic){
    this->heuristic = heuristic;
};

void State::setCar(Car car){
    this->carList[car.getId()] = car;
};

bool State::isFinalState(){

    Car redCar = this->carList[0];
    if (redCar.getCoords()[0] == 4 && redCar.getCoords()[1] == 2){
        return true;
    }
    return false;
};

bool State::verifyCarMove(int carId, int movement){
    char* string = new char[10];
    if (movement == UP){
        string = "UP";
    } else if (movement == LEFT){
        string = "LEFT";
    } else if (movement == DOWN){
        string = "DOWN";
    } else if (movement == RIGHT){
        string = "RIGHT";
    }
    // Accedemos al auto que queremos verificar
    Car* car = &this->carList[carId];
    if (car->getDirection() == 0 && (movement == UP || movement == DOWN)){
        std::cout << "Car: " << carId << " move: " << string << " Wrong direction" << std::endl;
        return false;
    } else if (car->getDirection() == 1 && (movement == LEFT || movement == RIGHT)){
        std::cout << "Car: " << carId << " move: " << string << " Wrong direction" << std::endl;
        return false;
    }
    // Calculamos las coordenadas a las que se movería el auto
    int* tempCoords = new int[6];
    for (int i=0;i<2*car->getLength();i++){
        tempCoords[i] = car->getCoords()[i];
    }

    if (movement == UP){
        for(int i=0; i<car->getLength(); i++){
            tempCoords[2*i+1]--; // y
        }
    }else if(movement == LEFT){
        for(int i=0; i<car->getLength(); i++){
            tempCoords[2*i]--; // x
        }
    }else if(movement == DOWN){
        for(int i=0; i<car->getLength(); i++){
            tempCoords[2*i+1]++; // y
        }
    }else if(movement == RIGHT){
        for(int i=0; i<car->getLength(); i++){
            tempCoords[2*i]++; // x
        }
    }

    //  Verificamos que todas sus coordenadas sean válidas
    for(int coord=0;coord<car->getLength();coord++){
        int currentX = tempCoords[coord*2];
        int currentY = tempCoords[coord*2+1];
        if(currentX < 0 || currentX > 5 || currentY < 0 || currentY > 5){
            std::cout << "Car: " << carId << " move: " << string << " Out of bounds" << std::endl;
            return false;
        }
        if(this->carMatrix[currentY][currentX] != -1 && this->carMatrix[currentY][currentX] != carId){
            std::cout << "Hay esto: " << this->carMatrix[currentY][currentX] << std::endl;
            std::cout << "Car: " << carId << " move: " << string << " Car in the way" << std::endl;
            return false;
        }
    }
    return true;
};

void State::calculateHeuristic(){
    int heuristic;
    // Se obtiene el auto rojo
    Car redCar = this->carList[0];

    // Se obtiene la distancia a la salida
    heuristic = 4 - redCar.getCoords()[0];

    // Se calculan los autos que están bloqueando la salida
    int blockingCars = 0;
    char* countedCars = new char[this->carListSize];
    // Recorremos la fila 2 desde el auto rojo hacia la derecha
    for (int x=redCar.getCoords()[2]+1;x<6;x++){
        if(this->carMatrix[2][x] != -1){
            // Se verifica que el auto no haya sido contado
            if(blockingCars == 0){
                // std::cout << "Car: " << this->getCarMatrix()[2][x] << " is blocking the exit" << std::endl;
                countedCars[blockingCars] = this->getCarMatrix()[2][x]+'0';
                blockingCars++;
            } else {
                bool counted = false;
                for(int i=0;i<blockingCars;i++){
                    if(countedCars[i]-'0' == this->getCarMatrix()[2][x]){
                        counted = true;
                    }
                }
                if(!counted){
                    countedCars[blockingCars] = this->getCarMatrix()[2][x]+'0';
                    blockingCars++;
                }
            }            
        }
    }
    // Una vez ya contados ahora se suma a la heurística total
    heuristic += blockingCars;

    if (blockingCars != 0){
        // Si no hay autos bloqueando la salida entonces se calcula la distancia del auto rojo a la salida
        // Ahora se calcula la cantidad de autos bloqueando a los autos que bloquean la salida
        // Se suma a la heurística la mínima cantidad de autos que bloquean a los autos que bloquean la salida
        // Para esto definimos nuevas variables útiles
        int blockingBlockingCars = 0;
        char* countedBlockingCars = new char[this->carListSize];

        for(int car=0;car<blockingCars;car++){
            // Se obtiene el auto (se le resta el 0 porque es un char)

            Car currentCar = this->carList[countedCars[car]-'0'];
            // Se obtiene la coordenada x
            int currentX = currentCar.getCoords()[0];

            // Se recorre la columna desde la coordenada x hacia arriba
            int upBlocking = 0;
            int downBlocking = 0;
            for(int y=currentCar.getCoords()[1]-1; y>=0; y--){
                if(this->carMatrix[y][currentX] != -1){
                    // Se verifica que el auto no haya sido contado
                    if(blockingBlockingCars == 0){
                        countedBlockingCars[blockingBlockingCars] = this->getCarMatrix()[y][currentX]+'0';
                        blockingBlockingCars++;
                    } else {
                        bool counted = false;
                        for(int i=0;i<blockingBlockingCars;i++){
                            if(countedBlockingCars[i]-'0' == this->getCarMatrix()[y][currentX]){
                                counted = true;
                            }
                        }
                        if(!counted){
                            countedBlockingCars[blockingBlockingCars] = this->getCarMatrix()[y][currentX]+'0';
                            blockingBlockingCars++;
                        }
                    }            
                }
            }
            upBlocking = blockingBlockingCars;
            blockingBlockingCars = 0;
            int currentY;
            // Se recorre la columna desde la coordenada x hacia abajo
            if (currentCar.getLength() == 2){
                currentY = currentCar.getCoords()[3];
            } else {
                currentY = currentCar.getCoords()[5];
            }
            for(currentY; currentY<6; currentY++){
                if(this->carMatrix[currentY][currentX] != -1){
                    // Se verifica que el auto no haya sido contado
                    if(blockingBlockingCars == 0){
                        countedBlockingCars[blockingBlockingCars] = this->getCarMatrix()[currentY][currentX]+'0';
                        blockingBlockingCars++;
                    } else {
                        bool counted = false;
                        for(int i=0;i<blockingBlockingCars;i++){
                            if(countedBlockingCars[i]-'0' == this->getCarMatrix()[currentY][currentX]){
                                counted = true;
                            }
                        }
                        if(!counted){
                            countedBlockingCars[blockingBlockingCars] = this->getCarMatrix()[currentY][currentX]+'0';
                            blockingBlockingCars++;
                        }
                    }            
                }
            }
            downBlocking = blockingBlockingCars;
            if (upBlocking < downBlocking){
                heuristic += upBlocking;
            } else {
                heuristic += downBlocking;
            }
        }
    }

    this->heuristic = heuristic;
}

void State::updateCarMatrix(int* oldCoords, int* newCoords, Car car){
    // Se obtiene el id del auto
    char carId = car.getId();
    // Se pintan de -1 las coordenadas antiguas
    this->carMatrix[oldCoords[1]][oldCoords[0]] = -1;
    this->carMatrix[oldCoords[3]][oldCoords[2]] = -1;
    if (car.getLength() == 3){
        this->carMatrix[oldCoords[5]][oldCoords[4]] = -1;
    }
    // Se pintan de carId las coordenadas nuevas
    this->carMatrix[newCoords[1]][newCoords[0]] = carId;
    this->carMatrix[newCoords[3]][newCoords[2]] = carId;
    if (car.getLength() == 3){
        this->carMatrix[newCoords[5]][newCoords[4]] = carId;
    }
}

void State::printRoute(){
    // TO-DO
}

bool State::equals(State* state){
    // Se comprueba si dos estados son iguales
    // Para esto basta con comparar las matrices de autos
    for(int y=0;y<6;y++){
        for(int x=0;x<6;x++){
            if(this->carMatrix[y][x] != state->carMatrix[y][x]){
                return false;
            }
        }
    }
    return true;
}

void State::printBoard(){
    // Se imprime el tablero
    for(int y=0;y<6;y++){
        for(int x=0;x<6;x++){
            std::cout << this->carMatrix[y][x] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}