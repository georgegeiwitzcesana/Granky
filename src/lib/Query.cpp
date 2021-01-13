#include <math.h>
#include <cassert>

#include <iostream>

#include "Query.h"

namespace granky {

Graph::Node Query::yieldNode() const {

    return node;
}

Graph::Weight Query::yieldWeight() const {

    return weight;
}

const Graph::EdgeList& Query::yieldSequence() const {

    return sequence;
}

const Graph::Table* Query::yieldTable() const {

    return table.get();
}

void Query::setSource(Graph::Node s) {

    source = s;
}

void Query::setSink(Graph::Node t) {

    sink = t;
}

void RecursiveDFS::init(Graph* s) {

    assert(s);
    graph = s;
    table = graph->getBlankNodeCheck();
}

void RecursiveDFS::execute() {

    assert(graph && table && graph->isNode(source));
    node = true;
    weight = recurse(source);
}

Graph::Weight RecursiveDFS::recurse(const Graph::Node sub) {

    if(Graph::isNode(table->get(sub))) {

        return NAN;
    }

    table->set(sub, node);

    Graph::Weight ret = 0.0;

    const Graph::ProgressCall callback = [this, &sub, &ret](Graph::Node node, Graph::Weight w) {

        const auto got = recurse(node);

        if(Graph::isWeight(got)) {
            
            ret += w + got;
        }

        return -1;
    };

    graph->forEachEgress(sub, callback);

    return ret;
}

Graph::Weight RecursiveDigraphDFS::recurse(const Graph::Node sub) {

    if(Graph::isNode(table->get(sub))) {

        return NAN;
    }

    table->set(sub, node);

    Graph::Weight ret = 0.0;

    const Graph::ProgressCall callback = [this, &sub, &ret](Graph::Node node, Graph::Weight w) {

        const auto got = recurse(node);

        if(Graph::isWeight(got)) {
            
            ret += w + got;
        }

        return -1;
    };

    graph->forEachLightDigress(sub, callback);

    return ret;
}

void ColorComponents::init(Graph* g) {

    assert(g);
    graph = g;
    table = graph->getBlankNodeTally();
}

void ColorComponents::execute() {

    node = 0;
    weight = 0.0;
    
    const Graph::NodeCall nodeCall = [this](Graph::Node sub) {

        const auto got = recurse(sub);

        if(Graph::isWeight(got)) {

            weight += got;
        }

        ++node;
        return -1;
    };

    graph->forEachNode(nodeCall);
}

}; // namespace granky
