#ifndef GRANKY_LIB_QUERY_H
#define GRANKY_LIB_QUERY_H

#include "Graph.h"
#include "math.h"

namespace granky {

class Query {

protected:
    Graph* graph = nullptr;
    Graph::Table::Instance table;
    Graph::Node source = -1;
    Graph::Node sink = -1;
    Graph::Node node = -1;
    Graph::Weight weight = NAN;

public:
    void init(Graph* graph);
    Graph::Node yieldNode() const;
    Graph::Weight yieldWeight() const; 
    virtual void execute(Graph::Node source, Graph::Node sink) = 0;
};

class RecursiveQuery : public Query {

public:
    virtual void execute(Graph::Node source, Graph::Node sink) override;

private:
    virtual Graph::Weight recurse(const Graph::Node node) = 0;
};

class RecursiveDFS: public RecursiveQuery {

public:
    virtual void execute();

private:
    virtual void execute(Graph::Node source, Graph::Node sink) override;
    virtual Graph::Weight recurse(const Graph::Node node);
};

}; // namespace granky

#endif // GRANKY_LIB_QUERY_H
