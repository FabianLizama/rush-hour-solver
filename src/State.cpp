#include "../include/State.h"
#include "../include/Car.h"
#include "../include/Queue.h"

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

State::State(){};

State::State(int id, int depth, int heuristic, int action, State *parent, Car* carList, int carListSize, int** carMatrix, char* lastMove){
    this->id = id;
    this->depth = depth;
    this->heuristic = heuristic; 
    this->action = action;
    this->parent = nullptr;
    this->carList = carList;
    this->carListSize = carListSize;
    this->carMatrix = carMatrix;
    this->lastMove = lastMove;
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

void State::setHeuristic(int heuristic){
    this->heuristic = heuristic;
};

void State::setCar(Car car){
    this->carList[car.getId()] = car;
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

void State::calculateHeuristic(){
    int heuristic;
    // Se obtiene el auto rojo
    Car redCar = this->carList[0];
    // Se calculan los autos que están bloqueando la salida
    int blockingCars = 0;
    char* countedCars = new char[this->carListSize];
    // Recorremos la fila 2 desde el auto rojo hacia la derecha
    for (int x=redCar.getCoords()[2]+1;x<6;x++){
        if(this->carMatrix[2][x] != -1){
            // Se verifica que el auto no haya sido contado
            if(blockingCars == 0){
                countedCars[blockingCars] = this->getCarMatrix()[2][x];
                blockingCars++;
            } else {
                bool counted = false;
                for(int i=0;i<blockingCars;i++){
                    if(countedCars[i] == this->getCarMatrix()[2][x]){
                        counted = true;
                    }
                }
                if(!counted){
                    countedCars[blockingCars] = this->getCarMatrix()[2][x];
                    blockingCars++;
                }
            }            
        }
    }
    // Una vez ya contados ahora se suma a la heurística total
    heuristic = blockingCars;
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
        int upBlocking;
        int downBlocking;
        for(int y=currentCar.getCoords()[1]-1; y>=0; y--){
            if(this->carMatrix[y][currentX] != -1){
                // Se verifica que el auto no haya sido contado
                if(blockingBlockingCars == 0){
                    countedBlockingCars[blockingBlockingCars] = this->getCarMatrix()[y][currentX];
                    blockingBlockingCars++;
                } else {
                    bool counted = false;
                    for(int i=0;i<blockingBlockingCars;i++){
                        if(countedBlockingCars[i] == this->getCarMatrix()[y][currentX]){
                            counted = true;
                        }
                    }
                    if(!counted){
                        countedBlockingCars[blockingBlockingCars] = this->getCarMatrix()[y][currentX];
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
                    countedBlockingCars[blockingBlockingCars] = this->getCarMatrix()[currentY][currentX];
                    blockingBlockingCars++;
                } else {
                    bool counted = false;
                    for(int i=0;i<blockingBlockingCars;i++){
                        if(countedBlockingCars[i] == this->getCarMatrix()[currentY][currentX]){
                            counted = true;
                        }
                    }
                    if(!counted){
                        countedBlockingCars[blockingBlockingCars] = this->getCarMatrix()[currentY][currentX];
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
    this->heuristic = heuristic;
}

void State::updateCarMatrix(int* oldCoords, int* newCoords){
    // Se obtiene el id del auto
    char carId = this->carMatrix[oldCoords[1]][oldCoords[0]];
    // Se pintan de -1 las coordenadas antiguas del auto
    for(int coord=0;coord<2;coord++){
        this->carMatrix[oldCoords[coord*2+1]][oldCoords[coord*2]] = -1;
    }
    // Se pintan de carId las coordenadas nuevas del auto
    for(int coord=0;coord<2;coord++){
        this->carMatrix[newCoords[coord*2+1]][newCoords[coord*2]] = carId;
    }
}

void State::printRoute(){
    Queue route = Queue(4);
    State* currentState = this;
    while (currentState->parent != nullptr){
        route.push(currentState->getLastMove());
        currentState = currentState->parent;
    }
    route.print();
}