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

#ifndef GRANKY_LIB_GRAPH_H
#define GRANKY_LIB_GRAPH_H

#include <math.h> // isnan

#include <forward_list>
#include <memory> // unique_ptr
#include <ostream>
#include <istream>
#include <functional> // fuction

namespace granky {

class Graph {

public:
    typedef int Node;
    typedef double Weight;
    typedef std::unique_ptr<Graph> Instance;
    typedef std::function<void(Node)> NodeCall;
    typedef std::function<void(Node, Weight)> EdgeCall;

    struct Edge {
        
        const Node from;
        const Node to;
        const Weight weight;
    };

    typedef std::forward_list<Edge> EdgeList;

    virtual void init(const size_t nodes, const size_t edges) = 0;
    
    template<class GRAPH_TYPE> static Instance create(const std::string_view filename); 
    template<class GRAPH_TYPE> static Instance create(std::istream& in); 

    virtual bool haveNode(const Node node) const = 0;
    virtual Weight getWeight(const Node from, const Node to) const = 0;
    virtual const EdgeList getEdges() const = 0;
    virtual void addNode(const Node node) = 0;

    virtual void forEachNode(NodeCall callback) = 0;
    virtual void forEachEgress(Node from, EdgeCall callback) = 0;
    
    virtual void addEdge(
            const Node from,
            const Node to,
            const Weight weight) = 0;

    inline void addDoubleEdge(
            const Node from,
            const Node to,
            const Weight weight) {
    
        addEdge(from, to, weight);
        addEdge(to, from, weight);
    }
    
    inline bool isNode(const Node node) const {
        
        return node >= 0;
    };
    
    inline bool isWeight(const Weight weight) const {
        
        return !isnan(weight);
    };
    
    inline bool haveEdge(const Node from, const Node to) const {
        
        return !isnan(getWeight(from, to));
    };
    
    friend std::ostream& operator << (std::ostream& out, const Graph& g);
    friend std::istream& operator >> (std::istream& in, Graph& g);

    static constexpr const double DEFAULT_DEFAULT_WEIGHT = 1.0;

protected:
    void parse(std::string_view filename);
};

std::ostream& operator << (std::ostream& out, const Graph& graph);
std::istream& operator >> (std::istream& in, Graph& graph);

template<class GRAPH_TYPE>
Graph::Instance Graph::create(const std::string_view filename) {

    Graph::Instance ret = Graph::Instance(new(std::nothrow) GRAPH_TYPE());
    ret->parse(filename);
    return ret;
}

template<class GRAPH_TYPE>
Graph::Instance Graph::create(std::istream& in) {

    Graph::Instance ret = Graph::Instance(new(std::nothrow) GRAPH_TYPE());
    in >> *ret;
    return ret;
}

} // namespace granky

#endif // GRANKY_LIB_GRAPH_H
