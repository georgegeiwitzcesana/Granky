Created by George Cesana ne Guy on January 7th, 2021

Granky is a graphing library I'm creating as I work through William Fiset's 
YouTube tutorial on graphing algorithms.

To compile, run the following command from the project root directory:

    g++ -std=c++17 tests/FileTest.cpp src/Graph.cpp src/MatrixGraph.cpp src/HashGraph.cpp -o bin/o.bin

And to run:

    bin/o.bin in/0.gky

This will run IOTest, which takes the graph defined in the file in/0.gky, parses it into both an adjacency matrix 
and an adjacency list, converts both back into text format, and prints those representations.

.gky files are defined as follows:

Each line consists of two integers, optionally followed by one decimal number.

The two integers represent two nodes that share a directed edge from the first node to the second.

The decimal number represents the weight of the edge. If no weight is given, it defaults to 1.
