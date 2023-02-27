#include "../dijkstra.h"
#include <string>
#include <iostream>
#include "../cs225/catch/catch.hpp"
#include "../graph.h"
#include "../datareader.h"

Graph generateSimpleGraph_g() {
    /*
        Generate the following graph:
             ( 0 )
           1/  |2   \3
         (1)  (2)--(3)
         4|      5
         (4)
    */

    Edge e1(0, 0, 1, 1);
    Edge e2(1, 0, 2, 2);
    Edge e3(2, 0, 3, 3);
    Edge e4(3, 1, 4, 4);
    Edge e5(4, 2, 3, 5);
    vector<Edge> vec;
    vec.push_back(e1);
    vec.push_back(e2);
    vec.push_back(e3);
    vec.push_back(e4);
    vec.push_back(e5);
    Graph g(5, vec); // 5 vertices
    
    return g;

}

Graph generateComplexGraph_g() {
    /**
     * Generate the following graph:
     *             ( 0 ) -------------------
     *          /    |    \                 |
     *        (1)   (2) -- (3) --(4)        |
     *       /   \    \     |               |
     *     (5)---(6)  (7)  (8)-------------- 
     *     | \    |    /     \
     *     |  \   |   /       \
     *     |    ( 9 ) ------ (10) ------ (11) ------ (12)
     *     |                  /             \
     *    (13) ______________/_______(14)    \________(15)
     * 
     * Weight of each edge is initialized to 1.
     */

    int num_vertices = 16; // 16 vertices

    Edge e1(0, 0, 1, 1);
    Edge e2(1, 0, 2, 1);
    Edge e3(2, 0, 3, 1);
    Edge e4(3, 0, 8, 1);
    Edge e5(4, 1, 5, 1);
    Edge e6(5, 1, 6, 1);
    Edge e7(6, 2, 3, 1);
    Edge e8(7, 2, 7, 1);
    Edge e9(8, 3, 4, 1);
    Edge e10(9, 3, 8, 1);
    Edge e11(10, 5, 6, 1);
    Edge e12(11, 5, 9, 1);
    Edge e13(12, 5, 13, 1);
    Edge e14(13, 6, 9, 1);
    Edge e15(14, 7, 9, 1);
    Edge e16(15, 8, 10, 1);
    Edge e17(16, 9, 10, 1);
    Edge e18(17, 10, 11, 1);
    Edge e19(18, 10, 13, 1);
    Edge e20(19, 10, 14, 1);
    Edge e21(20, 11, 12, 1);
    Edge e22(21, 11, 15, 1);
    Edge e23(22, 13, 14, 1);

    vector<Edge> vec;

    vec.push_back(e1);
    vec.push_back(e2);
    vec.push_back(e3);
    vec.push_back(e4);
    vec.push_back(e5);
    vec.push_back(e6);
    vec.push_back(e7);
    vec.push_back(e8);
    vec.push_back(e9);
    vec.push_back(e10);
    vec.push_back(e11);
    vec.push_back(e12);
    vec.push_back(e13);
    vec.push_back(e14);
    vec.push_back(e15);
    vec.push_back(e16);
    vec.push_back(e17);
    vec.push_back(e18);
    vec.push_back(e19);
    vec.push_back(e20);
    vec.push_back(e21);
    vec.push_back(e22);
    vec.push_back(e23);

    Graph g(num_vertices, vec);
    return g;
}

TEST_CASE("testgraph 1: Simple graph, degree", "[weight=20]")
{
    /* Test 1 : check degree of each vertex */
    Graph g = generateSimpleGraph_g();
    bool test1_passed = true;
    int ans1[5] = {3, 2, 2, 2, 1};
    for (int i = 0; i < 5; i++) {
        if (g.getDegree(i) != ans1[i]) {
            //std::cout << "Degree of vertex " << i << " is incorrect." << std::endl;
            test1_passed = false;
        }
    }

    REQUIRE(test1_passed == true);
}


TEST_CASE("testgraph 2: Simple graph, adjacent v", "[weight=20]")
{
    /* Test 2 : check adjacent vertices of each vertex */
    Graph g = generateSimpleGraph_g();
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
                // std::cout << "Adjacent vertices of vertex " << i << " is incorrect: ";
                // for (auto v : adj) {std::cout << v << " ";}
                // std::cout << std::endl;
                break;
            }
        }
    }

    REQUIRE(test2_passed == true);
}

TEST_CASE("testgraph 3: Simple graph, weight", "[weight=20]")
{

    /* Test 3 : check if the weights of the edges are correct */
    Graph g = generateSimpleGraph_g();
    bool test3_passed = true;
    if (g.getWeight(1, 0) != 1) {test3_passed = false;}
    if (g.getWeight(2, 0) != 2) {test3_passed = false;}
    if (g.getWeight(3, 0) != 3) {test3_passed = false;}
    if (g.getWeight(4, 0) != -1) {test3_passed = false;}
    if (g.getWeight(6, 0) != -1) {test3_passed = false;}
    if (g.getWeight(1, 4) != 4) {test3_passed = false;}
    if (g.getWeight(2, 3) != 5) {test3_passed = false;}

    
    REQUIRE(test3_passed == true);
}

TEST_CASE("testgraph 4: Complex graph", "[weight=20][valgrind]")
{
    Graph g = generateComplexGraph_g();

    /* Check if the degree of each vertex is correct */
    bool degree_correct = true;
    if (g.getDegree(0) != 4) {
        FAIL("Degree of vertex 0 is not correct in complex graph");
        degree_correct = false;
    }
    if (g.getDegree(4) != 1) {
        FAIL("Degree of vertex 4 is not correct in complex graph");
        degree_correct = false;
    }
    if (g.getDegree(10) != 5) {
        FAIL("Degree of vertex 10 is not correct in complex graph");
        degree_correct = false;
    }
    if (g.getDegree(13) != 3) {
        FAIL("Degree of vertex 13 is not correct in complex graph");
        degree_correct = false;
    }

    REQUIRE((degree_correct == true));

    /* Check the adjacent vertices of vertices 2(0, 3, 7), 5(1,6,9,13), 8(0, 3, 10), 10(8,9,11,13,14),  */
    bool adv_correct = true;

    if (g.adjacentVertices(2).size() != 3) {
        FAIL("number of adjacent vertices is not correct on complex graph");
    }
    int ans2[3] = {0, 3, 7};
    for (int i = 0; i < 3; i++) {
        if (ans2[i] != g.adjacentVertices(2)[i]) {
            adv_correct = false;
            FAIL("adjacent vertices are not correct on complex graph");
        }
    }

    if (g.adjacentVertices(5).size() != 4) {
        FAIL("number of adjacent vertices is not correct on complex graph");
    }
    int ans5[4] = {1, 6, 9, 13};
    for (int i = 0; i < 4; i++) {
        if (ans5[i] != g.adjacentVertices(5)[i]) {
            adv_correct = false;
            FAIL("adjacent vertices are not correct on complex graph");
        }
    }

    if (g.adjacentVertices(8).size() != 3) {
        FAIL("number of adjacent vertices is not correct on complex graph");
    }
    int ans8[3] = {0, 3, 10};
    for (int i = 0; i < 3; i++) {
        if (ans8[i] != g.adjacentVertices(8)[i]) {
            adv_correct = false;
            FAIL("adjacent vertices are not correct on complex graph");
        }
    }

    if (g.adjacentVertices(10).size() != 5) {
        FAIL("number of adjacent vertices is not correct on complex graph");
    }
    int ans10[5] = {8, 9, 11, 13, 14};
    for (int i = 0; i < 5; i++) {
        if (ans10[i] != g.adjacentVertices(10)[i]) {
            adv_correct = false;
            FAIL("adjacent vertices are not correct on complex graph");
        }
    }

    REQUIRE(adv_correct == true);
}

TEST_CASE("testgraph 5: graph initialized with empty vector", "[weight=20][valgrind]")
{
    vector<Edge> vec; // empty edge vector
    Graph g(0, vec); // empty graph

    if (!g.adjacentVertices(0).empty()) {
        FAIL("Empty graph fails");
    }

    REQUIRE(true);
}

TEST_CASE("testgraph 6: initialize graph with the whole dataset", "[weight=20][valgrind]")
{
    /* The dataset has 21,693 edges and 21,048 vertices. */
    std::string file_path = "dataset/caledge_modified.txt";
    vector<Edge> edges = readEdges(file_path);

    Graph g(21048, edges);

    /* Run some functions to check if there is seg fault */
    g.adjacentVertices(10000);
    g.getDegree(6666);
    g.incidentEdges(9999);
    g.getWeight(16666, 20000);

    REQUIRE(true);
}
