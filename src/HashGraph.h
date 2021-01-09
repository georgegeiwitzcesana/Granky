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

#ifndef GRAPHER_MAP_GRAPH_H
#define GRAPHER_MAP_GRAPH_H

#include <unordered_map>

#include "Graph.h"

namespace granky {

class HashGraph : public Graph {

public:
    typedef Graph super;

    HashGraph(const HashGraph&) = delete;
    HashGraph& operator=(const HashGraph&) = delete;
    HashGraph(HashGraph&&) = delete;
    HashGraph& operator=(const HashGraph&&) = delete;
    HashGraph();
 
    virtual void init(const size_t nodes, const size_t edges) override;
    
    virtual const EdgeList getEdges() const override;
    virtual bool haveNode(const Node node) const override;
    virtual Weight getWeight(const Node from, const Node to) const override;
    virtual void addNode(const Node node) override;
    virtual void addEdge(const Node from, const Node to, const Weight weight) override;

private:
    typedef std::unordered_map<Node, std::unordered_map<Node, Weight>> HashTable;
    HashTable graph;
};

} // namespace granky

#endif // GRAPHER_MAP_GRAPH_H
