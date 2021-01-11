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

#include <istream>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Graph.h"

namespace granky {

void Graph::parseFile(std::string_view filename) {

    std::ifstream file(filename.data());
    file >> *this;
}

void Graph::parseString(std::string_view str) {

    std::stringstream stream(str.data());
    stream >> *this;
}

bool operator == (const Graph& left, const Graph& right) {

    return left.isSubset(right) && right.isSubset(left);
}

bool operator != (const Graph& left, const Graph& right) {

    return !(left == right);
}

std::ostream& operator << (std::ostream& out, const Graph& graph) {

    const Graph::EdgeCall edgeCall = [&out](Graph::Node from, Graph::Node to, Graph::Weight weight) {

        out << from << " ";
        out << to << " ";
        out << weight << std::endl;
        return -1;
    };

    graph.forEachEdge(edgeCall);
    return out;
}

std::istream& operator >> (std::istream& in, Graph& graph) {

    const auto endEdge = [&in]() {

        return in.peek() == '\n' || in.eof();
    };

    bool newline = in.peek() == '\n';
    
    while(!in.eof() && (!newline || in.get() == '\n')) {

        newline = true;
        Graph::Node from(-1);
        Graph::Node to(-1);
        Graph::Weight weight(Graph::DEFAULT_DEFAULT_WEIGHT);

        do {

            in >> from;

            if(endEdge()) {

                break;
            }

            in >> to;

            if(endEdge()) {

                break;
            }

            in >> weight;
        } while(false);

        if(!graph.isNode(from)) {

            continue;
        }

        if(!graph.isNode(to)) {

            graph.addNode(from);
            continue;
        }

        graph.addEdge(from, to, weight);
    }

    return in;
}

} // namespace granky
