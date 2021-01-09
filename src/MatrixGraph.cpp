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

#include <cassert>
#include <math.h>

#include "MatrixGraph.h"

namespace granky {

MatrixGraph::MatrixGraph() {};

void MatrixGraph::init(const size_t nodes, const size_t edges) {

    graph.clear();
    graph.resize(nodes, std::vector<Weight>(nodes, NAN));
}

void MatrixGraph::forEachNode(NodeCall callback) {

    for(Node node = 0; node < graph.size(); ++node) {

        if(haveNode(node)) {

            callback(node);
        }
    }
}

const Graph::EdgeList MatrixGraph::getEdges() const {

    EdgeList ret;

    for(Node from(0); from < graph.size(); ++from) {

        const auto& each = graph[from];

        for(Node to(0); to < each.size(); ++to) {
       
            if(from == to) {

                continue;
            }

            const auto& weight = each[to];

            if(isWeight(weight)) {
                
                ret.push_front({from, to, weight});
            }
        }
    }

    return move(ret);
}

bool MatrixGraph::haveNode(const Node node) const {

    return haveEdge(node, node);
}

Graph::Weight MatrixGraph::getWeight(const Node from, const Node to) const {

    if(from < graph.size() && to < graph.size()) {
        
        return graph[from][to];
    }

    return NAN;
}

void MatrixGraph::addNode(const Node node) {

    assert(isNode(node));

    if(node >= graph.size()) {

        for(auto it = graph.begin(); it != graph.end(); ++it) {

            it->resize(node + 1, NAN);
        }

        graph.resize(node + 1, std::vector<Weight>(node + 1, NAN));
    }

    if(!isWeight(graph[node][node])) {
    
        graph[node][node] = 0.0;
    }
}

void MatrixGraph::addEdge(
        const Node from,
        const Node to,
        const Weight weight) {

    assert(isWeight(weight));

    addNode(from);
    addNode(to);
    graph[from][to] = weight;
}

} // namespace granky
