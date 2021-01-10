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

#ifndef GRANKY_LIB_MATRIXGRAPH_H
#define GRANKY_LIB_MATRIXGRAPH_H

#include <vector>

#include "Graph.h"

namespace granky {

class MatrixGraph : public Graph {

public:
    typedef Graph super;

    MatrixGraph(const MatrixGraph&) = delete;
    MatrixGraph& operator=(const MatrixGraph&) = delete;
    MatrixGraph(MatrixGraph&&) = delete;
    MatrixGraph& operator=(const MatrixGraph&&) = delete;
    MatrixGraph();
 
    virtual void init(const size_t nodes, const size_t edges) override;
    
    virtual const EdgeList getEdges() const override;
    virtual bool haveNode(const Node node) const override;
    virtual Weight getWeight(const Node from, const Node to) const override;
    virtual void addNode(const Node node) override;

    virtual Node forEachNode(const NodeCall& callback) const override;
    virtual Node forEachEgress(const Node from, const ProgressCall& callback) const override;

    virtual void addEdge(
            const Node from,
            const Node to,
            const Weight weight) override;

private:
    typedef std::vector<std::vector<Weight>> Matrix;
    Matrix graph;
};

} // namespace granky

#endif // GRANKY_LIB_MATRIXGRAPH_H
