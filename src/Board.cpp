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
};

Board Board::readInputFile(std::string filename){
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

    // Se crea el tablero
    Board board = Board();

    // Se lee el archivo línea por línea y se crean los autos
    int counter = 0;
    while (std::getline(file, line)){
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

        Car car = Car(counter, coords, length, direction);
        board.addCar(car);
        counter++;
    }
    file.close();
    return board;
}

// Los autos se representan con su id correspondiente, el auto rojo se representa con un 1
// Las casillas se representan con una x
void Board::printBoard(){
    // Se crea una matriz de characters para representar el tablero
    char** graphicBoard = new char*[this->height];
    for(int i = 0; i < this->height; i++){
        graphicBoard[i] = new char[this->width]();
    }
    // Se rellena la matriz con x
    for(int i = 0; i < this->height; i++){
        for(int j = 0; j < this->width; j++){
            graphicBoard[i][j] = 'x';
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
            cout << graphicBoard[i][j] << " ";
        }
        cout << endl;
    }
};

bool Board::addCar(Car car){
    // Se agrega el auto a la lista de autos
    this->carList[car.getId()] = car;
    this->carListSize++;
    return true;
};

Board Board::solve(){
    // Se crea una matriz para representar el tablero
    int** boardMatrix = new int*[this->height];
    for(int i = 0; i < this->height; i++){
        boardMatrix[i] = new int[this->width];
    }
    // Se rellena la matriz con -1
    for(int i = 0; i < this->height; i++){
        for(int j = 0; j < this->width; j++){
            boardMatrix[i][j] = -1;
        }
    }
    // Se rellena la matriz con los autos
    // Se iteran los autos
    for(int currentCar=0; currentCar<this->carListSize; currentCar++){
        // Se iteran las coordenadas de los autos
        for(int coord=0; coord<this->carList[currentCar].getLength(); coord++){
            int currentX = this->carList[currentCar].getCoords()[coord*2];
            int currentY = this->carList[currentCar].getCoords()[coord*2+1];
            boardMatrix[currentY][currentX] = this->carList[currentCar].getId();
        }
    }

    // Se crea el estado inicial
    State initialState = State(0, 0, 1000000, -1, nullptr, this->carList, this->carListSize, boardMatrix);
    // Se crea el heap para guardar los estados
    MinHeap heap = MinHeap(5);
    // Se agrega el estado inicial al heap
    heap.insert(initialState);

    // Se generan los estados
    State currentState;

    // Para un estado state generamos todos los movimientos posibles
    // Recorremos la lista de autos
    for(int currentCar=0; currentCar<currentState.carListSize; currentCar++){
        // Recorremos las 4 direcciones
        for(int j=1; j<=4; j++){
            // Se crea el auto temporal
            Car tempCar = currentState.carList[currentCar];
            // Se mueve el auto temporal
            tempCar.move(tempCar.calcMoveCoords(j));
            // Se crea el estado temporal
            State tempState = State(currentState.id+1, currentState.depth+1, 0, j, &currentState, currentState.carList, currentState.carListSize, boardMatrix);
            // Se agrega el estado temporal al heap
            heap.insert(tempState);
        }
    }
};
