#include <cassert>
#include <functional>
#include <iostream>
#include <string_view>

#include "../lib/Graph.h"
#include "../lib/HashGraph.h"
#include "../lib/MatrixGraph.h"
#include "../lib/Query.h"

#define TEST2(__cnd__, __lft__, __rgt__) \
    {if(!(__cnd__)) {\
        std::cout << __lft__ << std::endl;\
        std::cout << __rgt__ << std::endl;\
        assert(__cnd__);\
    }}\

#define TEST1(__cnd__, __grp__) \
    {if(!(__cnd__)) {\
        std::cout << __grp__ << std::endl;\
        assert(__cnd__);\
    }}\

const char* CASE[] = {

    "\
        1 0 1\n\
        0 1 1\n\
    ",
    "\
        0 1 1\n\
        1 0 1\n\
    ",
    "\
        0 1 1\n\
        1 0 2\n\
    "
};

int main(int argc, const char** argv) {

    {
        auto matrix = granky::Graph::create<granky::MatrixGraph>();
        matrix->parseFile("in/0.gky");

        auto hash = granky::Graph::create<granky::HashGraph>();
        hash->parseFile("in/0.gky");

        TEST2(*matrix == *hash, *matrix, *hash);
    }

    {
        auto matrix = granky::Graph::create<granky::MatrixGraph>();
        matrix->parseFile("in/0.gky");

        auto hash = granky::Graph::create<granky::HashGraph>();
        hash->parseFile("in/1.gky");

        TEST2(*matrix == *hash, *matrix, *hash);
    }

    {
        auto matrix = granky::Graph::create<granky::MatrixGraph>();
        matrix->parseFile("in/2.gky");

        auto hash = granky::Graph::create<granky::HashGraph>();
        hash->addEdge(0, 1, 1);
        hash->addEdge(1, 0, 2);

        TEST2(*matrix == *hash, *matrix, *hash);
    }

    {
        auto matrix = granky::Graph::create<granky::MatrixGraph>();
        matrix->parseFile("in/0.gky");

        auto hash = granky::Graph::create<granky::HashGraph>();
        hash->parseFile("in/2.gky");

        TEST2(*matrix != *hash, *matrix, *hash);
    }

    {
        auto matrix = granky::Graph::create<granky::MatrixGraph>();
        matrix->parseString(CASE[0]);

        auto hash = granky::Graph::create<granky::HashGraph>();
        hash->parseString(CASE[0]);

        TEST2(*matrix == *hash, *matrix, *hash);
    }

    {
        auto matrix = granky::Graph::create<granky::MatrixGraph>();
        matrix->parseString(CASE[0]);

        auto hash = granky::Graph::create<granky::HashGraph>();
        hash->parseString(CASE[1]);

        TEST2(*matrix == *hash, *matrix, *hash);
    }

    {
        auto matrix = granky::Graph::create<granky::MatrixGraph>();
        matrix->parseString(CASE[0]);

        auto hash = granky::Graph::create<granky::HashGraph>();
        hash->addEdge(0, 1, 1);
        hash->addEdge(1, 0, 2);

        TEST2(*matrix != *hash, *matrix, *hash);
    }

    {
        auto matrix = granky::Graph::create<granky::MatrixGraph>();
        matrix->parseString(CASE[0]);

        auto hash = granky::Graph::create<granky::HashGraph>();
        hash->parseString(CASE[2]);

        TEST2(*matrix != *hash, *matrix, *hash);
    }

    {
        auto graph = granky::Graph::create<granky::MatrixGraph>("in/Fiset3.gky");
        granky::RecursiveDFS dfs;
        dfs.init(graph.get());
        dfs.execute();
        TEST1(dfs.yieldWeight() == 14.0, *graph);
    }

    {
        auto graph = granky::Graph::create<granky::HashGraph>("in/Fiset3.gky");
        granky::RecursiveDFS dfs;
        dfs.init(graph.get());
        dfs.execute();
        TEST1(dfs.yieldWeight() == 14.0, *graph);
    }

    return 0;
}
