CC=g++
CFLAGS=-std=c++17

all:
	$(CC) $(CFLAGS) tests/FileTest.cpp src/Graph.cpp src/MatrixGraph.cpp src/HashGraph.cpp -o bin/granky.bin
