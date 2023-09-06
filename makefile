main: main.cpp State.o Board.o Car.o Stack.o StackNode.o
	g++ State.o Board.o Car.o main.cpp Stack.o StackNode.o -o main

State.o: State.cpp State.h
	g++ -c State.cpp

Board.o: Board.cpp Board.h
	g++ -c Board.cpp

Car.o: Car.cpp Car.h
	g++ -c Car.cpp

Stack.o: Stack.cpp Stack.h
	g++ -c Stack.cpp

StackNode.o: StackNode.cpp StackNode.h
	g++ -c StackNode.cpp
clean:
	rm *.o main

