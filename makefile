main: src/main.cpp out/State.o out/Board.o out/Car.o out/Stack.o out/StackNode.o out/MinHeap.o
	g++ out/State.o out/Board.o out/Car.o src/main.cpp out/Stack.o out/StackNode.o out/MinHeap.o -o main

out/State.o: src/State.cpp include/State.h
	g++ -c src/State.cpp -o out/State.o

out/Board.o: src/Board.cpp include/Board.h
	g++ -c src/Board.cpp -o out/Board.o

out/Car.o: src/Car.cpp include/Car.h
	g++ -c src/Car.cpp -o out/Car.o

out/Stack.o: src/Stack.cpp include/Stack.h
	g++ -c src/Stack.cpp -o out/Stack.o

out/StackNode.o: src/StackNode.cpp include/StackNode.h
	g++ -c src/StackNode.cpp -o out/StackNode.o

out/MinHeap.o: src/MinHeap.cpp include/MinHeap.h
	g++ -c src/MinHeap.cpp -o out/MinHeap.o

clean:
	rm out/*.o main