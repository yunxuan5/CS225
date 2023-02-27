#include "../datareader.h"
#include "../graph.h"
#include <fstream>
#include <string>
#include <iostream>
#include "../cs225/catch/catch.hpp"

/* Multiple test cases have been included in test_readedges.txt. */

TEST_CASE("testdatareader 0: test read size", "[weight=20]")
{
    /*
        Read the following graph:
             ( 0 )
           1/  |2   \3
         (1)  (2)--(3)
         4|      5
         (4)
    */
    vector<Edge> edges = readEdges("tests/test_readedges.txt");
    REQUIRE(edges.size() == 5);
}


TEST_CASE("testdatareader 1: degree", "[weight=20]")
{
    vector<Edge> edges = readEdges("tests/test_readedges.txt");
    Graph g(5, edges); // generate a graph with the edges
    bool test1_passed = true;
    int ans1[5] = {3, 2, 2, 2, 1};
    for (int i = 0; i < 5; i++) {
        if (g.getDegree(i) != ans1[i]) {
            std::cout << "Degree of vertex " << i << " is incorrect." << std::endl;
            test1_passed = false;
        }
    }

    REQUIRE(test1_passed == true);
}


TEST_CASE("testdatareader 2: test read size", "[weight=20]"){
    /* Test 2 : check adjacent vertices of each vertex */
    vector<Edge> edges = readEdges("tests/test_readedges.txt");
    Graph g(5, edges); // generate a graph with the edges

    bool test2_passed = true;
    vector<int> ans2[5];
    ans2[0] = vector<int> {1, 2, 3};
    ans2[1] = vector<int> {0, 4};
    ans2[2] = vector<int> {0, 3};
    ans2[3] = vector<int> {0, 2};
    ans2[4] = vector<int> {1};
    for (int i = 0; i < 5; i++) {
        vector<int> adj = g.adjacentVertices(i);
        for (unsigned j = 0; j < adj.size(); j++) {
            if (ans2[i][j] != adj[j]) {
                test2_passed = false;
                //std::cout << "Adjacent vertices of vertex " << i << " is incorrect: ";
                //for (auto v : adj) {std::cout << v << " ";}
                //std::cout << std::endl;
                break;
            }
        }
    }

    REQUIRE(test2_passed == true);
}


TEST_CASE("testdatareader 3: weight", "[weight=20]")
{
    /* Test 3 : check if the weights of the edges are correct */
    
    vector<Edge> edges = readEdges("tests/test_readedges.txt");
    Graph g(5, edges); // generate a graph with the edges
    bool test3_passed = true;
    if (g.getWeight(1, 0) != 1) {test3_passed = false;}
    if (g.getWeight(2, 0) != 2) {test3_passed = false;}
    if (g.getWeight(3, 0) != 3) {test3_passed = false;}
    if (g.getWeight(4, 0) != -1) {test3_passed = false;}
    if (g.getWeight(6, 0) != -1) {test3_passed = false;}
    if (g.getWeight(1, 4) != 4) {test3_passed = false;}
    if (g.getWeight(2, 3) != 5) {test3_passed = false;}
    if (!test3_passed) {
        std::cout << "weights of the edges are not correct." << std::endl;
    }

    REQUIRE(test3_passed == true);
}
