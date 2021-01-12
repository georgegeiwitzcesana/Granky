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

/**
 * LEXICON
 *
 * Node: a vertex in a graph
 * * A node is represented by a numeric ID no lower than zero.
 * Leaf: an empty or nonexistent node, represented by giving a node a value below zero.
 * Edge: a weighted, directed connection between two nodes.
 * * There may be at most one edge in a given direction between a given pair of nodes.
 * * An empty or nonexistent edge has a value of NAN.
 * Egress (from x to y): an edge leading from node x to node y.
 * Ingress (from x to y): an edge leading to node x from node y.
 * Progress: in a given context, either all ingresses or all egresses are considered progresses.
 *  * If an egress is considered a progress in a given context, than no ingresses are progresses in that context.
 *  * If an ingress is considered a progress in a given context, than no egresses are progresses in that context.
 * Regress: the opposite of a progress, for purposes of given context.
 * Digress: either an egress or an ingress, in a context that considers the distinction irrelevant.
 */

namespace granky {

class Graph {

public:
    typedef int Node;

    class Table {

    public:
        typedef std::unique_ptr<Table> Instance;
        virtual Node get(const Node node) const = 0;
        virtual void set(const Node node, const Node value) = 0;
        template<class TABLE_TYPE> static Instance create(const Node count);
    };

    class NodeCheck : public Table {

        std::vector<bool> table;

    public:
        NodeCheck(const Node count) : table(count) {};
        virtual Node get(const Node node) const;
        virtual void set(const Node node, const Node value);
    };

    class NodeTally : public Table {

        std::vector<Node> table;

    public:
        NodeTally(const Node count) : table(count) {};
        virtual Node get(const Node node) const;
        virtual void set(const Node node, const Node value);
    };

    typedef double Weight;
    typedef std::unique_ptr<Graph> Instance;
    typedef std::function<Node(Node)> NodeCall;
    typedef std::function<Node(Node, Weight)> ProgressCall;
    typedef std::function<Node(Node, Node, Weight)> EdgeCall;

    struct Edge {
        
        const Node from;
        const Node to;
        const Weight weight;
    };

    typedef std::forward_list<Edge> EdgeList;

    void parseFile(std::string_view filename);
    void parseString(std::string_view str);
    
    template<class GRAPH_TYPE> static Instance create(); 
    template<class GRAPH_TYPE> static Instance create(const std::string_view filename); 
    template<class GRAPH_TYPE> static Instance create(std::istream& in); 

    virtual bool haveNode(const Node node) const = 0;
    virtual Weight getWeight(const Node from, const Node to) const = 0;
    virtual const EdgeList getEdges() const = 0;
    virtual void addNode(const Node node) = 0;
    virtual void addEdge(const Node from, const Node to, const Weight weight) = 0;
    virtual Node getNodeCount() const = 0;

    /**
     * All forEach methods stop iterating when the callback returns a non-negative number,
     * and always return the last value returned by the callback.
     */
    virtual Node forEachNode(const NodeCall& callback) const = 0;
    virtual Node forEachEgress(const Node from, const ProgressCall& callback) const = 0;
    
    static inline bool isNode(const Node node) {
        
        return node >= 0;
    };
    
    static inline bool isWeight(const Weight weight) {
        
        return !isnan(weight);
    };
    
    inline bool haveEdge(const Node from, const Node to) const {
        
        return isWeight(getWeight(from, to));
    };
 
    inline bool haveEdge(const Node from, const Node to, const Weight weight) const {

        if(!isWeight(weight)) {

            return false;
        }

        const Weight w = getWeight(from, to);
        return isWeight(w) && w == weight;
    }

    inline bool haveDigress(const Node from, const Node to) const {

        return haveEdge(from, to) || haveEdge(to, from);
    }

    inline Node forEachEdge(const EdgeCall& edgeCall) const {

        const NodeCall nodeCall = [this, &edgeCall](Node from) {

            const ProgressCall egressCall = [&edgeCall, &from](Node to, Weight weight) {

                return edgeCall(from, to, weight);
            };

            return forEachEgress(from, egressCall);
        };

        return forEachNode(nodeCall);
    }

    inline bool isSubset(const Graph& other) const {

        const EdgeCall edgeCall = [&other](Node from, Node to, Weight weight) {

            if(other.haveEdge(from, to, weight)) {

                return -1;
            }

            return to;
        };

        return !isNode(forEachEdge(edgeCall));
    }
   
    inline void addDoubleEdge(
            const Node from,
            const Node to,
            const Weight weight) {
    
        addEdge(from, to, weight);
        addEdge(to, from, weight);
    }

    inline Table::Instance getBlankNodeCheck() {

        return move(Table::create<NodeCheck>(getNodeCount()));
    }

    inline Table::Instance getNodeCheck() {

        Table::Instance ret = getBlankNodeCheck();

        const NodeCall callback = [&ret](Node node) {

            ret->set(node, 1);
            return -1;
        };

        forEachNode(callback);

        return move(ret);
    }

    friend std::ostream& operator << (std::ostream& out, const Graph& g);
    friend std::istream& operator >> (std::istream& in, Graph& g);

    static constexpr const double DEFAULT_DEFAULT_WEIGHT = 1.0;

protected:
};

template<class TABLE_TYPE>
Graph::Table::Instance Graph::Table::create(const Node count) {

    return Graph::Table::Instance(new(std::nothrow) TABLE_TYPE(count));
}

template<class GRAPH_TYPE>
Graph::Instance Graph::create() {

    auto ret = Graph::Instance(new(std::nothrow) GRAPH_TYPE());
    return ret;
}

template<class GRAPH_TYPE>
Graph::Instance Graph::create(const std::string_view filename) {

    Graph::Instance ret = Graph::Instance(new(std::nothrow) GRAPH_TYPE());
    ret->parseFile(filename);
    return ret;
}

template<class GRAPH_TYPE>
Graph::Instance Graph::create(std::istream& in) {

    Graph::Instance ret = Graph::Instance(new(std::nothrow) GRAPH_TYPE());
    in >> *ret;
    return ret;
}

bool operator == (const Graph& left, const Graph& right);
bool operator != (const Graph& left, const Graph& right);
std::ostream& operator << (std::ostream& out, const Graph& graph);
std::istream& operator >> (std::istream& in, Graph& graph);

} // namespace granky

#endif // GRANKY_LIB_GRAPH_H
