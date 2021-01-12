#include <cassert>

#include "Query.h"

namespace granky {

Graph::Node Query::yieldNode() const {

    return node;
}

Graph::Weight Query::yieldWeight() const {

    return weight;
}

void Query::init(Graph* s) {

    assert(s);
    graph = s;
    table = graph->getBlankNodeCheck();
}

void RecursiveQuery::execute(Graph::Node s, Graph::Node t) {

    assert(graph && table && graph->isNode(s) && graph->isNode(t));
    source = s;
    sink = t;
    weight = recurse(source);
}

void RecursiveDFS::execute(Graph::Node s, Graph::Node t) {

    execute();
}

void RecursiveDFS::execute() {

    RecursiveQuery::execute(0, 0);
}

Graph::Weight RecursiveDFS::recurse(const Graph::Node sub) {

    if(Graph::isNode(table->get(sub))) {

        return 0.0;
    }

    table->set(sub, 1);

    Graph::Weight ret = 0.0;

    const Graph::ProgressCall callback = [this, &ret](Graph::Node node, Graph::Weight w) {

        ret += w + recurse(node);
        return -1;
    };

    graph->forEachEgress(sub, callback);

    return ret;
}

}; // namespace granky
