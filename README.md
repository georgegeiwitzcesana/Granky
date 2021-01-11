Created by George Cesana ne Guy on January 7th, 2021

Granky is a graphing library I'm creating as I work through William Fiset's 
YouTube tutorial on graphing algorithms.

To compile the demo, run the following command from the project root directory:

    make showfile

And to run:

    bin/granky.bin in/Fiset3.gky

The showfile program takes the graph defined in the file in/Fiset3.gky, parses it into both an adjacency
matrix and an adjacency list, converts both back into text format. It then prints each edge in each graph,
followed by each node in each graph, followed by each node in each graph along with their neighbors and
weights. The graphs should be identical, although they will be in different orders because HashGraph uses
unordered_map for its adjacency list.

To compile the tests, run the following command from the project root directory:

    make test

To run the tests:

    bin/tests

If the code is working, this should output nothing.

.gky files are defined as follows:

Each line consists of two integers, optionally followed by one decimal number.

The two integers represent two nodes that share a directed edge from the first node to the second.

The decimal number represents the weight of the edge. If no weight is given, it defaults to 1.
