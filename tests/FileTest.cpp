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

#include <fstream>
#include <string>

#include "Test.h"
#include "../src/MatrixGraph.h"
#include "../src/HashGraph.h"

void writeGraphTest(granky::Graph::Instance& graph) {

    std::cout << *graph;
}

int main(int argc, const char** argv) {

    if(argc < 2) {

        std::cout << "Expected input file" << std::endl;
        return 1;
    }

    const std::string_view filename(argv[1]);
    
    std::cout << "Graph as matrix:" << std::endl;

    auto matrixGraph = granky::Graph::create<granky::MatrixGraph>(filename);
    writeGraphTest(matrixGraph);

    std::cout << std::endl << "Graph as hashtable:" << std::endl;

    auto hashGraph = granky::Graph::create<granky::HashGraph>(filename);
    writeGraphTest(hashGraph);

    return 0;
}
