#include <iostream>
#include <typeinfo>
#include <fstream>
#include <string>
#include "../include/Board.h"

using namespace std;

Board::Board(){}; // default constructor (does nothing

Board::Board(int width, int height, int initX, int initY, int goalX, int goalY){
    this->width = width;
    this->height = height;
    this->board = new Car*[height];
    for(int i = 0; i < width; i++){
        this->board[i] = new Car[width];
    }
    
    this->initX = initX;
    this->initY = initY;
    this->goalX = goalX;
    this->goalY = goalY;
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
    // Se obtiene el tamaño del tablero
    std::getline(file, line);
    int width = line[0] - '0';
    int height = line[2] - '0';

    // Se obtiene la salida
    std::getline(file, line);
    int goalX = line[0] - '0';
    int goalY = line[2] - '0';

    // Se obtiene el auto rojo
    std::getline(file, line);
    Car redCar = Car(0, line[0]-'0', line[2]-'0', line[4]-'0', line[6]-'0');

    // Se crea el tablero y se añade el auto rojo
    Board board = Board(width, height, line[0]-'0', line[1]-'0', goalX, goalY);
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

    for(int y = 0; y < this->height; y++){
        for(int x = 0; x < this->width; x++){
            // Si existe un auto en la casilla
            if(this->board[y][x].exists){
                graphicBoard[y][x] = this->board[y][x].id + '0';
                
                if(this->board[y][x].getDirection() == 0){ // Si el auto es horizontal
                    for(int k = 1; k < this->board[y][x].getLength(); k++){ // Se dibuja el resto del auto
                        graphicBoard[y][x+k] = this->board[y][x].id + '0';
                    }
                }else{ // Si el auto es vertical
                    if(y==5 && x==4){
                    }
                    for(int k = 1; k < this->board[y][x].getLength(); k++){ // Se dibuja el resto del auto
                        graphicBoard[y+k][x] = this->board[y][x].id+'0';
                    }
                }
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

int Board::addCar(Car car){
    // Se revisa que el auto no se salga del tablero
    if (car.getX() < 0 || car.getX() >= this->width || car.getY() < 0 || car.getY() >= this->height){
        cout << "Error: car out of bounds" << endl;
        return 1;
    }
    // Se agrega el auto
    this->board[car.getY()][car.getX()] = car;
    return 0;
};
