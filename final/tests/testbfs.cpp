#include "../dijkstra.h"
#include <string>
#include <iostream>
#include "../cs225/catch/catch.hpp"
#include "../graph.h"
#include "../bfs.h"
#include "../datareader.h"

Graph generateSimpleGraph_b() {
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

Graph generateComplexGraph_b() {
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

TEST_CASE("testBFS 1: Simple graph, path 0-4", "[weight=20]")
{
    /* Test 1: test the path between vertex 0 to vertex 4 */
    Graph g = generateSimpleGraph_b();
    bool test1_passed = true;
    int start = 0, end = 4;
    vector<int> path1 = bfs(g, start, end); // should be {0, 1, 4}
    if (path1.size() != 3) {
        std::cout << "path length is not correct. (may contain a loop)" << std::endl;
        test1_passed = false;
    }
    int ans1[3] = {0, 1, 4};
    for (unsigned i = 0; i < path1.size(); i++) {
        if (path1[i] != ans1[i]) {
            std::cout << "path is not correct." << std::endl;
            test1_passed = false;
        }
    }
    if (g.getTotalWeight(path1) != 5) {
        std::cout << "weight of the path is not correct." << std::endl;
        test1_passed = false;
    }

    REQUIRE(test1_passed == true);

}


TEST_CASE("testBFS 2: Simple graph, path 3-4", "[weight=20]")
{

    /* Test 2: test the path between vertex 4 and 3 (a cycle is present) */
    Graph g = generateSimpleGraph_b();
    bool test2_passed = true;
    int start = 4;
    int end = 3;
    /* {4,1,0,3} is the valid output */
    vector<int> path2 = bfs(g, start, end);
    if (path2.size() != 4) {
        std::cout << "path length is not correct. (may contain a loop)" << std::endl;
    }
    
    int ans2[4] = {4, 1, 0, 3};
    for (unsigned i = 0; i < 4; i++) {
        if (path2[i] != ans2[i]) {
            std::cout << "path is not correct." << std::endl;
            test2_passed = false;
        }
    }
    REQUIRE(test2_passed == true);

}

TEST_CASE("testBFS 3: Complex graph, path 0-15", "[weight=20][valgrind]")
{
    Graph g = generateComplexGraph_b();
    vector<int> path = bfs(g, 0, 15);

    /* Check if the start & end points are correct */
    bool start_end_correct = true;
    if (path[0] != 0 || path[path.size()-1] != 15) {
        FAIL("BFS start/end point is not correct");
        start_end_correct = false;
    }
    REQUIRE((start_end_correct == true));

    /* Check if there are any duplicates in the path (loops) */
    bool duplicates = false;
    for (unsigned i = 0; i < path.size(); i++) {
        for (unsigned j = i+1; j < path.size(); j++) {
            if (path[i] == path[j]) {
                duplicates = true;
                FAIL("BFS contains at least a loop");
            }
        }
    }
    REQUIRE((duplicates == false));

    /* Check if each step is valid by checking the adjacent vertices of each step */
    bool check_steps = true;
    for (unsigned i = 0; i < path.size() - 1; i++) {
        int currentVertex = path[i];
        int nextVertex = path[i+1];

        // check if nextVertex is in the adjacent vertices of currentVertex
        bool valid = false;
        for (int adjacentVertex : g.adjacentVertices(currentVertex)) {
            if (adjacentVertex == nextVertex) {
                valid = true;
                break;
            }
        }
        if (valid == false) {
            check_steps = false;
            FAIL("BFS contains invalid steps");
            break;
        }
    }
    REQUIRE((check_steps == true));
}

TEST_CASE("testBFS 4: Complex graph, path 14-4", "[weight=20][valgrind]")
{
    Graph g = generateComplexGraph_b();
    vector<int> path = bfs(g, 14, 4);

    /* Check if the start & end points are correct */
    bool start_end_correct = true;
    if (path[0] != 14 || path[path.size()-1] != 4) {
        FAIL("BFS start/end point is not correct");
        start_end_correct = false;
    }
    REQUIRE((start_end_correct == true));

    /* Check if there are any duplicates in the path (loops) */
    bool duplicates = false;
    for (unsigned i = 0; i < path.size(); i++) {
        for (unsigned j = i+1; j < path.size(); j++) {
            if (path[i] == path[j]) {
                duplicates = true;
                FAIL("BFS contains at least a loop");
            }
        }
    }
    REQUIRE((duplicates == false));

    /* Check if each step is valid by checking the adjacent vertices of each step */
    bool check_steps = true;
    for (unsigned i = 0; i < path.size() - 1; i++) {
        int currentVertex = path[i];
        int nextVertex = path[i+1];

        // check if nextVertex is in the adjacent vertices of currentVertex
        bool valid = false;
        for (int adjacentVertex : g.adjacentVertices(currentVertex)) {
            if (adjacentVertex == nextVertex) {
                valid = true;
                break;
            }
        }
        if (valid == false) {
            check_steps = false;
            FAIL("BFS contains invalid steps");
            break;
        }
    }
    REQUIRE((check_steps == true));
}

TEST_CASE("testBFS 5: Empty graph", "[weight=20][valgrind]")
{
    vector<Edge> vec; // empty vector, no edges
    Graph g(0, vec); // empty graph

    vector<int> path = bfs(g, 0, 0);
    REQUIRE((path.empty() == true));
}

TEST_CASE("testBFS 6: Graph with only 2 vertices", "[weight=20][valgrind]")
{
    /**
     * (0)-(1)
     */
    Edge e1(0, 0, 1, 1);
    vector<Edge> vec;
    vec.push_back(e1);

    Graph g(2, vec);
    
    vector<int> path = bfs(g, 0, 1); // should be {0, 1}
    int ans[2] = {0, 1};

    bool passed = true;
    for (int i = 0; i < 2; i++) {
        if (ans[i] != path[i]) {
            FAIL("BFS fails on graph with 2 vertices");
            passed = false;
        }
    }

    REQUIRE((passed == true));
}

TEST_CASE("testBFS 7: Disconnected graph", "[weight=20][valgrind]")
{
    /**
     * (0)---(1)    (3)----(4)
     *   \   /        \    /
     *    (2)           (5)
     */
    Edge e1(0, 0, 1);
    Edge e2(1, 0, 2);
    Edge e3(2, 1, 2);
    Edge e4(3, 3, 4);
    Edge e5(4, 3, 5);
    Edge e6(5, 4, 5);
    vector<Edge> vec;
    vec.push_back(e1);
    vec.push_back(e2);
    vec.push_back(e3);
    vec.push_back(e4);
    vec.push_back(e5);
    vec.push_back(e6);

    Graph g(6, vec);

    vector<int> path1 = bfs(g, 3, 5); // should be {3, 5}
    vector<int> path2 = bfs(g, 0, 5); // no possible path, should be empty

    bool path1_correct = true, path2_correct = true;
    if (!path2.empty()) {
        path2_correct = false;
        FAIL("BFS does not return empty vector when no possible path");
    }
    int ans[2] = {3, 5};
    for (int i = 0; i < 2; i++) {
        if (ans[i] != path1[i]) {
            path1_correct = false;
            FAIL("BFS fails on disconnected graph");
        }
    }

    REQUIRE((path1_correct && path2_correct));
}

TEST_CASE("testBFS 8: Test on the whole dataset", "[weight=20][valgrind]")
{
    /* The dataset has 21,693 edges and 21,048 vertices. */
    std::string file_path = "dataset/caledge_modified.txt";
    vector<Edge> edges = readEdges(file_path);
    Graph g(21048, edges);

    int START = 666; // start vertex
    int END = 16666; // end vertex

    vector<int> path = bfs(g, START, END);

    std::cout << path.empty() << std::endl;

    /* Check if start and end vertices of the path are correct */
    bool start_end_correct = true;
    if (path[0] != START || path[path.size()-1] != END) {
        start_end_correct = false;
        FAIL("BFS start/end vertex is not correct on whole dataset");
    }

    REQUIRE((start_end_correct == true));

    /* Check if there are duplicates in the path */
    bool visited[21048];
    bool duplicates = false;
    for (int i = 0; i < 21048; i++) {
        visited[i] = false;
    }
    for (int v : path) {
        if (visited[v] == true) {
            duplicates = true;
            FAIL("BFS contains loop on the whole dataset");
            break;
        }
        visited[v] = true;
    }

    REQUIRE((duplicates == false));
}
