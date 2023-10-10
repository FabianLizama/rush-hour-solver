FLAGS = -g

main: src/main.cpp out/Queue.o out/State.o out/Board.o out/Car.o out/Stack.o out/MinHeap.o
	g++ ${FLAGS} out/State.o out/Board.o out/Car.o src/main.cpp out/Stack.o out/MinHeap.o out/Queue.o -o main

out/State.o: src/State.cpp include/State.h
	g++ ${FLAGS} -c src/State.cpp -o out/State.o

out/Board.o: src/Board.cpp include/Board.h
	g++ ${FLAGS} -c src/Board.cpp -o out/Board.o

out/Car.o: src/Car.cpp include/Car.h
	g++ ${FLAGS} -c src/Car.cpp -o out/Car.o

out/Stack.o: src/Stack.cpp include/Stack.h
	g++ ${FLAGS} -c src/Stack.cpp -o out/Stack.o


out/MinHeap.o: src/MinHeap.cpp include/MinHeap.h
	g++ ${FLAGS} -c src/MinHeap.cpp -o out/MinHeap.o

out/Queue.o: src/Queue.cpp include/Queue.h
	g++ ${FLAGS} -c src/Queue.cpp -o out/Queue.o

clean:
	rm out/*.o main