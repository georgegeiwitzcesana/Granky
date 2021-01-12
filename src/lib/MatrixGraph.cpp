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
#include <math.h> // isnan
#include <iostream> // cout, endl

#include "MatrixGraph.h"

#ifndef VERBOSE
#define VERBOSE 0
#endif

namespace granky {

//explicit constexpr MatrixGraph::MatrixGraph() {};

Graph::Node MatrixGraph::forEachNode(const NodeCall& callback) const {

    Node ret = -1;

    for(Node node = 0; !isNode(ret) && node < graph.size(); ++node) {

        if(haveNode(node)) {

            ret = callback(node); 
        }
    }

    return ret;
}

Graph::Node MatrixGraph::forEachEgress(const Node from, const ProgressCall& callback) const {

    if(!haveNode(from)) {

        return -1;
    }

    Node ret = -1;
    
    for(Node to = 0; !isNode(ret) && to < graph.size(); ++to) {

        if(from == to) {

            continue;
        }

        if(const auto weight = getWeight(from, to); isWeight(weight)) {

            ret = callback(to, weight);
        }
    }

    return ret;
}

const Graph::EdgeList MatrixGraph::getEdges() const {

    EdgeList ret;

    for(Node from(0); from < graph.size(); ++from) {

        const auto& each = graph[from];

        for(Node to(0); to < each.size(); ++to) {
       
            const auto& weight = each[to];

            if(isWeight(weight)) {
 
                if(!weight && from == to) {

                    continue;
                }
               
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
        ++nodeCount;
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
    
    if(VERBOSE) {

        std::cout << "matrix added: " << from << " " << to << " " << " "  << weight << std::endl; 
    }
}

Graph::Node MatrixGraph::getNodeCount() const {

    return nodeCount;
}

Graph::Node MatrixGraph::getEndNode() const {

    return static_cast<Node>(graph.size());
}

} // namespace granky
