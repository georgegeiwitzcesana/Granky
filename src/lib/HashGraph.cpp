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

#include "HashGraph.h"

namespace granky {

Graph::Node HashGraph::forEachNode(const NodeCall& callback) const {

    Node ret = -1;

    for(auto& each : graph) {

        if(ret = callback(each.first); isNode(ret)) {

            return ret;
        }
    }

    return ret;
}

Graph::Node HashGraph::forEachEgress(const Node from, const ProgressCall& callback) const {

    if(!haveNode(from)) {

        return -1;
    }

    Node ret = -1;

    for(auto& each : graph.at(from)) {

        const auto& to = each.first;
        const auto& weight = each.second;
        
        if(ret = callback(to, weight); isNode(ret)) {

            return ret;
        }
    }

    return ret;
}

Graph::Node HashGraph::forEachIngress(const Node to, const ProgressCall& callback) const {

    if(!haveNode(to)) {

        return -1;
    }

    Node ret = -1;

    for(const auto& each : graph) {

        const auto& from = each.first;
        const auto& adjacent = each.second;

        if(const auto got = adjacent.find(to); got != adjacent.end()) {

            const auto& weight = got->second;

            if(ret = callback(from, weight); isNode(ret)) {

                return ret;
            }
        }
    }

    return ret;
}

Graph::Node HashGraph::forEachLightDigress(const Node from, const ProgressCall& callback) const {

    if(!haveNode(from)) {

        return -1;
    }

    Node ret = -1;

    for(auto& each : graph.at(from)) {

        const auto& to = each.first;
        const auto weight = getLightDigress(from, to);
        
        if(ret = callback(to, weight); isNode(ret)) {

            return ret;
        }
    }

    return ret;
}

const Graph::EdgeList HashGraph::getEdges() const {

    EdgeList ret;

    for(const auto& each : graph) {
    
        for(const auto& other : each.second) {

            ret.push_front({each.first, other.first, other.second});
        }
    }
    
    return move(ret);
}

bool HashGraph::haveNode(const Node node) const {

    return graph.find(node) != graph.end();
}

Graph::Weight HashGraph::getWeight(const Node from, const Node to) const {

    if(!haveNode(from)) {

        return NAN;
    }

    const auto& exits = graph.at(from);

    if(exits.find(to) != exits.end()) {

        return exits.at(to);
    }

    return NAN;
}

void HashGraph::addNode(const Node node) {

    if(!haveNode(node)) {

        graph[node] = {};
        endNode = std::max(endNode, node + 1);
    }
}

void HashGraph::addEdge(const Node from, const Node to, const Weight weight) {

    addNode(from);
    addNode(to);
    graph[from][to] = weight;
}

Graph::Node HashGraph::getNodeCount() const {

    return static_cast<Node>(graph.size());
}

Graph::Node HashGraph::getEndNode() const {

    return endNode;
}

} // namespace granky
