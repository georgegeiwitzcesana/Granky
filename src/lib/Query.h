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
    Graph::EdgeList sequence;

public:
    void setSource(Graph::Node s);
    void setSink(Graph::Node t);
    Graph::Node yieldNode() const;
    Graph::Weight yieldWeight() const;
    const Graph::EdgeList& yieldSequence() const; 
    const Graph::Table* yieldTable() const;
    virtual void init(Graph* graph) = 0;
    virtual void execute() = 0;
};

class RecursiveQuery : public Query {

private:
    virtual Graph::Weight recurse(const Graph::Node node) = 0;
};

class RecursiveDFS: public RecursiveQuery {

public:
    virtual void init(Graph* graph) override;
    virtual void execute() override;

protected:
    virtual Graph::Weight recurse(const Graph::Node sub) override;
};

class RecursiveDigraphDFS : public RecursiveDFS {

protected:
    virtual Graph::Weight recurse(const Graph::Node sub) override;
};

class ColorComponents : public RecursiveDigraphDFS {

public:
    virtual void init(Graph* graph) override;
    virtual void execute() override;
};

}; // namespace granky

#endif // GRANKY_LIB_QUERY_H
