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
    // Se obtiene el auto rojo
    std::getline(file, line);
    Car redCar = Car(0, line[0]-'0', line[2]-'0', line[4]-'0', line[6]-'0');

    // Se crea el tablero y se añade el auto rojo
    board.addCar(redCar);
    int counter = 1;
    while (std::getline(file, line)){
        // Se lee una línea del archivo y se crea el auto correspondiente
        Car car = Car(counter, line[0]-'0', line[2]-'0', line[4]-'0', line[6]-'0');
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
                graphicBoard[car.getY()][car.getX()+j] = car.getId()+'0';
            }
        // Si es vertical
        } else if (car.getDirection() == 1){
            // Se recorre el largo del auto
            for(int j=0; j<car.getLength(); j++){
                // Se agrega el id del auto a la matriz
                graphicBoard[car.getY()+j][car.getX()] = car.getId()+'0';
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
    // Se revisa que el auto no se salga del tablero
    if (car.getX() < 0 || car.getX() >= this->width || car.getY() < 0 || car.getY() >= this->height){
        cout << "Error: car out of bounds" << endl;
        return false;
    }
    
    // Se agrega el auto a la lista de autos
    this->carList[car.getId()] = car;
    this->carListSize++;
    return true;
};

Board Board::solve(){
    // Se crea el estado inicial
    
    // Se crea el heap para guardar los estados
    MinHeap heap = MinHeap(5);
    return Board();

};
