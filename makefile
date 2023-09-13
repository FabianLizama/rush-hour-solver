main: src/main.cpp State.o Board.o Car.o Stack.o StackNode.o
	g++ State.o Board.o Car.o src/main.cpp Stack.o StackNode.o -o main

State.o: src/State.cpp include/State.h
	g++ -c src/State.cpp

Board.o: src/Board.cpp include/Board.h
	g++ -c src/Board.cpp

Car.o: src/Car.cpp include/Car.h
	g++ -c src/Car.cpp

Stack.o: src/Stack.cpp include/Stack.h
	g++ -c src/Stack.cpp

StackNode.o: src/StackNode.cpp include/StackNode.h
	g++ -c src/StackNode.cpp

clean:
	rm *.o main