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
#include <cassert>

#include "Graph.h"

namespace granky {

bool Graph::haveEdge(const Node from, const Node to) const {
    
    return isWeight(getWeight(from, to));
};

bool Graph::haveEdge(const Node from, const Node to, const Weight weight) const {

    if(isWeight(weight)) {

        const Weight w = getWeight(from, to);
        return isWeight(w) && w == weight;
    }

    return false;
}

bool Graph::haveDigress(const Node from, const Node to) const {

    return haveEdge(from, to) || haveEdge(to, from);
}

Graph::Weight Graph::getLightDigress(const Node from, const Node to) const {

    const auto ex = getWeight(from, to);
    const auto in = getWeight(to, from);
    const auto isEx = isWeight(ex);
    const auto isIn = isWeight(in);
    return isEx && isIn ? std::min(ex, in) : isEx ? ex : isIn ? in : NAN;
}

Graph::Node Graph::forEachEdge(const EdgeCall& edgeCall) const {

    const NodeCall nodeCall = [this, &edgeCall](Node from) {

        const ProgressCall egressCall = [&edgeCall, &from](Node to, Weight weight) {

            return edgeCall(from, to, weight);
        };

        return forEachEgress(from, egressCall);
    };

    return forEachNode(nodeCall);
}

bool Graph::isSubset(const Graph& other) const {

    const EdgeCall edgeCall = [&other](Node from, Node to, Weight weight) {

        if(other.haveEdge(from, to, weight)) {

            return -1;
        }

        return to;
    };

    return !isNode(forEachEdge(edgeCall));
}

void Graph::addDoubleEdge(const Node from, const Node to, const Weight weight) {

    addEdge(from, to, weight);
    addEdge(to, from, weight);
}

Graph::Table::Instance Graph::getBlankNodeCheck() {

    return move(Table::create<NodeCheck>(getEndNode()));
}

Graph::Table::Instance Graph::getBlankNodeTally() {

    return move(Table::create<NodeTally>(getEndNode()));
}

Graph::Table::Instance Graph::getNodeCheck() {

    Table::Instance ret = getBlankNodeCheck();

    const NodeCall callback = [&ret](Node node) {

        ret->set(node, 1);
        return -1;
    };

    forEachNode(callback);

    return move(ret);
}


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

Graph::Node Graph::NodeCheck::get(const Node node) const {

    assert(Graph::isNode(node) && node < table.size());
    return table[node] ? 1 : -1;
};

void Graph::NodeCheck::set(const Node node, const Node value) {

    assert(Graph::isNode(node) && node < table.size());
    table[node] = Graph::isNode(value);
};

Graph::Node Graph::NodeTally::get(const Node node) const {

    assert(Graph::isNode(node) && node < table.size());
    return table[node];
}

void Graph::NodeTally::set(const Node node, const Node value) {

    assert(Graph::isNode(node) && node < table.size());
    table[node] = value;
};

} // namespace granky
