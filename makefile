CC=g++
CFLAGS=-std=c++17

showfile:
	$(CC) $(CFLAGS) src/app/ShowFile.cpp src/lib/Graph.cpp src/lib/MatrixGraph.cpp src/lib/HashGraph.cpp -o bin/showfile.bin
