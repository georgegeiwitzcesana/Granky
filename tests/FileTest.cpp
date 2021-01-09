/**
Granky is a toy graphing library created for practice, based on
William Fiset's graphing algorithm tutorial.
(https://youtu.be/7fujbpJ0LB4)

Copyright (C) 2021 George Cesana ne Guy

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream> // cout
#include <string> // string_view

#include "Test.h"
#include "../src/MatrixGraph.h"
#include "../src/HashGraph.h"

void writeGraph(granky::Graph::Instance& graph) {

    std::cout << *graph;
}

void writeNodes(granky::Graph::Instance& matrixGraph, granky::Graph::Instance& hashGraph) {

    granky::Graph::NodeCall callback = [](granky::Graph::Node node) {

        std::cout << node << std::endl;
    };

    std::cout << std::endl << "MatrixGraph nodes:" << std::endl;
    
    matrixGraph->forEachNode(callback);

    std::cout << std::endl << "HashGraph nodes:" << std::endl;
    
    hashGraph->forEachNode(callback);
}

void writeEgresses(granky::Graph::Instance& matrixGraph, granky::Graph::Instance& hashGraph) {

    static granky::Graph::EdgeCall edgeCall = [](granky::Graph::Node node, granky::Graph::Weight weight) {

        std::cout << node << "w" << weight << ", ";
    };

    static auto printEgresses = [](granky::Graph::Instance& graph, granky::Graph::Node node) {

        std::cout << node << ": ";
        graph->forEachEgress(node, edgeCall);
        std::cout << std::endl;
    };
    
    granky::Graph::NodeCall matrixCall = [&matrixGraph](granky::Graph::Node node) {

        printEgresses(matrixGraph, node);
    };

    granky::Graph::NodeCall hashCall = [&hashGraph](granky::Graph::Node node) {

        printEgresses(hashGraph, node);
    };
    
    std::cout << std::endl << "MatrixGraph egresses:" << std::endl;
    
    matrixGraph->forEachNode(matrixCall);

    std::cout << std::endl << "HashGraph egresses:" << std::endl;
    
    hashGraph->forEachNode(hashCall);

    std::cout << std::endl;
}

int main(int argc, const char** argv) {

    if(argc < 2) {

        std::cout << "Expected input file" << std::endl;
        return 1;
    }

    const std::string_view filename(argv[1]);
    
    std::cout << "Graph as matrix:" << std::endl;

    auto matrixGraph = granky::Graph::create<granky::MatrixGraph>(filename);
    writeGraph(matrixGraph);

    std::cout << std::endl << "Graph as hashtable:" << std::endl;

    auto hashGraph = granky::Graph::create<granky::HashGraph>(filename);
    writeGraph(hashGraph);

    writeNodes(matrixGraph, hashGraph);
    writeEgresses(matrixGraph, hashGraph);

    return 0;
}
