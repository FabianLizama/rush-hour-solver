#include <iostream>
#include <typeinfo>
#include <fstream>
#include <string>
#include "../include/Board.h"
#include "../include/State.h"
#include "../include/MinHeap.h"

using namespace std;

Board::Board(){
    // El máximo de autos posibles para un tablero de 6x6 pueden ser 18
    this->carList = new Car[18];
    this->carListSize = 0;
    this->carMatrix = new int*[this->height];
    for(int i = 0; i < this->height; i++){
        this->carMatrix[i] = new int[this->width];
    }
};

void Board::readInputFile(std::string filename, std::string wallFilename){
    // Cada fila es un auto
    // Columna 0 es la posición x
    // Columna 1 es la posición y
    // Columna 2 es el largo del auto
    // Columna 3 es la orientación del auto (0 es horizontal, 1 es vertical)

    // Se abre el archivo
    std::ifstream file(filename);

    // Se comprueba que el archivo se abrió correctamente
    if (!file.is_open()){
        std::cout << "No se pudo abrir el archivo " << filename << std::endl;
        throw std::runtime_error("Error al abrir el archivo");
    }
    std::string line;

    // Se lee el archivo línea por línea y se crean los autos
    int counter = 1;
    bool redCarFound=false;
    while (std::getline(file, line)){
        bool thisIsRedCar=false;
        int x0 = line[0]-'0';
        int y0 = line[2]-'0';
        int length = line[4]-'0';
        int direction = line[6]-'0';
        int* coords;
        if (length == 2){
            coords = new int[4];
        }else if (length == 3){
            coords = new int[6];
        }
        // Pares son x e impares son y
        // X_1
        coords[0] = line[0] - '0';
        // Y_1
        coords[1] = line[2] - '0';

        // Se lee una línea del archivo y se crea el auto correspondiente
        // Si es horizontal
        if (direction==0){
            // X_2
            coords[2] = coords[0]+1;
            // Y_2
            coords[3] = coords[1];
            if(length == 3){
                // X_3
                coords[4] = coords[0]+2;
                // Y_3
                coords[5] = coords[1];
            }
            // Se comprueba si es el auto rojo
            if(!redCarFound && (y0==2)){
                    redCarFound=true;
                    thisIsRedCar=true;
                    Car* car = new Car(0, coords, length, direction);
                    this->addCar(car);
            }
        // Si es vertical
        } else if (direction==1){
            // X_2
            coords[2] = coords[0];
            // Y_2
            coords[3] = coords[1]+1;
            if (length == 3){
                // X_3
                coords[4] = coords[0];
                // Y_3
                coords[5] = coords[1]+2;
            }
        }
        if (!thisIsRedCar){
            Car* car = new Car(counter, coords, length, direction);
            this->addCar(car);
            counter++;
        }
    }
    file.close();
    // Se cuentan los autos horizontales en la tercera fila
    int horizontalCars=0;
    Car** horizontalCarList = new Car*[2];

    for(int i=0; i<this->carListSize; i++){
        if (this->carList[i].getDirection() == 0 && this->carList[i].getCoords()[1] == 2){
            horizontalCarList[horizontalCars] = &this->carList[i];
            horizontalCars++;
        }
    }
    if (horizontalCars == 2){
        // Si hay dos autos horizontales en la fila 2 se identifica el rojo
        // Si están mal asignados se swapean los ids
        int xCar1 = horizontalCarList[0]->getCoords()[0];
        int xCar2 = horizontalCarList[1]->getCoords()[0];
        // Si el auto 1 está a la izquierda del auto 2 y es el auto rojo, los swapea
        if(xCar1 < xCar2 && horizontalCarList[0]->getId() == 0){
            int tempId = horizontalCarList[1]->getId();
            horizontalCarList[1]->setId(0);
            horizontalCarList[0]->setId(tempId);
        } else if (xCar2 < xCar1 && horizontalCarList[1]->getId() == 0){
            int tempId = horizontalCarList[0]->getId();
            horizontalCarList[0]->setId(0);
            horizontalCarList[1]->setId(tempId);
        }
    }

    // Se rellena la matriz con -1
    for(int i = 0; i < this->height; i++){
        for(int j = 0; j < this->width; j++){
            this->carMatrix[i][j] = -1;
        }
    }
    // Se rellena la matriz con los autos
    // Se iteran los autos
    for(int currentCar=0; currentCar<this->carListSize; currentCar++){
        // Se iteran las coordenadas de los autos
        for(int coord=0; coord<this->carList[currentCar].getLength(); coord++){

            int currentX = this->carList[currentCar].getCoords()[coord*2];
            int currentY = this->carList[currentCar].getCoords()[coord*2+1];
            this->carMatrix[currentY][currentX] = this->carList[currentCar].getId();
        }
    }

    std::ifstream wallFile(wallFilename);
    // Se comprueba que el archivo se abrió correctamente
    if (!wallFile.is_open()){
        std::cout << "No se pudo abrir el archivo " << wallFilename << std::endl;
        throw std::runtime_error("Error al abrir el archivo");
    }
    // Se lee el archivo línea por línea y se crean los autos
    while (std::getline(wallFile, line)){
        int x0 = line[0]-'0';
        int y0 = line[2]-'0';
        
        this->carMatrix[y0][x0] = -2;
    }
    wallFile.close();
}

void Board::setCarList(Car* carList){
    this->carList = carList;
};
// Los autos se representan con su id correspondiente, el auto rojo se representa con un 1
// Las casillas se representan con una x
void Board::printBoard(){
    // Se crea una matriz de characters para representar el tablero
    char** graphicBoard = new char*[this->height];
    for(int i = 0; i < this->height; i++){
        graphicBoard[i] = new char[this->width];
    }
    // Se rellena la matriz con x
    for(int i = 0; i < this->height; i++){
        for(int j = 0; j < this->width; j++){
            graphicBoard[i][j] = 'x';
        }
    }

    // Se rellena la matriz con muros
    for(int i = 0; i < this->height; i++){
        for(int j = 0; j < this->width; j++){
            if(this->carMatrix[i][j] == -2){
                graphicBoard[i][j] = '#';
            }
        }
    }

    // Se rellena la matriz con los autos
    for(int i=0; i<this->carListSize; i++){
        Car car = this->carList[i];
        // Si es horizontal
        if (car.getDirection() == 0){
            // Se recorre el largo del auto
            for(int j=0; j<car.getLength(); j++){
                // Se agrega el id del auto a la matriz
                graphicBoard[car.getCoords()[1]][car.getCoords()[0]+j] = car.getId()+'0';
            }
        // Si es vertical
        } else if (car.getDirection() == 1){
            // Se recorre el largo del auto
            for(int j=0; j<car.getLength(); j++){
                // Se agrega el id del auto a la matriz
                graphicBoard[car.getCoords()[1]+j][car.getCoords()[0]] = car.getId()+'0';
            }
        }
    }

    // Se imprime la matriz
    for(int i = 0; i < this->height; i++){
        for(int j = 0; j < this->width; j++){
            int character = graphicBoard[i][j];
            if(character != 120 && character != 35){
                cout << (char)((int)graphicBoard[i][j]+17) << " ";
            }else{
                cout << graphicBoard[i][j] << " ";
            }
        }
        cout << endl;
    }
};

bool Board::addCar(Car* car){
    // Se agrega el auto a la lista de autos
    this->carList[car->getId()] = *car;
    this->carListSize++;
    return true;
};

State* Board::solve(State *initialState){
    int StatesGenerated = 1;
    // Se crea el heap para guardar los estados
    MinHeap openHeap = MinHeap(4*initialState->carListSize);
    MinHeap closeHeap = MinHeap(4*initialState->carListSize);
    openHeap.insert(*initialState);
    // Se generan los estados
    int i = 1;
    while (!openHeap.isEmpty()){
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Iteracion: " << i << std::endl;
        // Se obtiene el estado con menor f y se crea un NUEVO estado con el mismo contenido
        State* currentState = openHeap.pop();
        std::cout << "Estado seleccionado: " << currentState->id << " con h, g y f: " << currentState->heuristic << currentState->g << currentState->getF() << "\n" << std::endl;
        
        // Si es solución devuelve el estado solucionado
        if (currentState->isFinalState()){
            std::cout << "Se encontro la solucion" << std::endl;
            return currentState;
        }

        // Si no, se clona el estado para trabajarlo
        closeHeap.insert(*currentState);

        // Para cada auto generamos los movimientos posibles
        // Recorremos la lista de autos
        int currentCar = 0;
        for(currentCar; currentCar < this->carListSize; currentCar++){
            // Recorremos las 4 direcciones
            for(int j=1; j<=4; j++){
                // Se crea el auto temporal
                Car* tempCar = currentState->getCarList()[currentCar].clone();
                
                // Se guardan sus coordenadas antiguas
                int* oldCoords = new int[6];
                for(int i=0; i<2*tempCar->getLength(); i++){
                    oldCoords[i] = tempCar->getCoords()[i];
                }

                // Se verifica si el auto puede moverse en la dirección j
                if (currentState->verifyCarMove(currentCar, j)){
                    // Se crea el estado temporal
                    State* tempState = currentState->clone();

                    // Se calculan las coordenadas de llegada del auto
                    int* newCoords = new int[2*tempCar->getLength()];

                    for(int i=0; i<2*tempCar->getLength(); i++){
                        newCoords[i] = tempCar->calcMoveCoords(j)[i];
                    }

                    // Se mueve el auto
                    tempCar->move(newCoords);
                    // Se actualiza la matriz de autos
                    tempState->updateCarMatrix(oldCoords, newCoords, *tempCar);
                    // Se actualiza la lista de autos
                    tempState->setCar(*tempCar);
                    // Se actualiza el g
                    tempState->g++;
                    // Se calcula la heurística del estado
                    tempState->calculateHeuristic();
                    tempState->carMoved = currentCar;
                    tempState->action = j;
                    // Se agrega el estado temporal al heap
                    if (!closeHeap.includes(tempState)){
                        // Se agrega el estado temporal al heap
                        tempState->id = StatesGenerated++;
                        tempState->parent = currentState;
                        openHeap.insert(*tempState);
                        std::cout << "Estado " << tempState->id << " generado con h, g y f:"<< tempState->heuristic <<  tempState->g << tempState->getF() << std::endl;
                        std::cout << "Moved car: " << currentCar << " move: " << j << std::endl;
                        //tempState->printBoard();
                        // Se elimina el estado temporal
                        delete tempState;
                    }
                }
            }
        }
        std::cout << "\nSe termino de generar los estados" << std::endl;
        std::cout << "OpenHeap: " << std::endl;
        openHeap.printHeap();
        std::cout << "CloseHeap: " << std::endl;
        closeHeap.printHeap();
    i++;
    }
    return nullptr;
};
