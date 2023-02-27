#include "../dijkstra.h"
#include <string>
#include <iostream>
#include "../cs225/catch/catch.hpp"
#include "../datareader.h"



vector<int> customizedWeightTest_d(int s, int e){
    /**
     Generate the following graph to test the weight preference
                  ( 1 ) 
              0 --------- 1              
              |           |
         (2)  |           |(2)
              |           | 
              3 --------- 2  
                   (3)
      Weight of each edge is initialized to 1.
    */

    int V = 4;
    Dijkstra g(4);

    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 0, 4);
    g.shortestPath(s);
    vector<int> path = g.getPathTo(e);
    return path;
}


vector<int> customizedSimpleTest_d(int s, int e){
    /**
     Generate the following graph to test the weight preference
                  ( 1 ) 
              0 --------- 1 -------\               
              | \---------| ------- \ (5)
              |           |   (7)  \-\ 
         (3)  |       (2) |           4 
              |           |   (8)  /-/ 
              | / --------|------ / / (6)
              3 --------- 2 -------/ 
                   (3)
      Weight of each edge is initialized to 1.
    */

    int V = 4;
    Dijkstra g(5);

    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 0, 4);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 6);
    g.addEdge(4, 0, 7);
    g.addEdge(3, 4, 8);   
    

    g.shortestPath(s);
    vector<int> path = g.getPathTo(e);
    return path;
}



vector<int> customizedModerateTest_d(int s, int e){
    /**
     Generate the following graph to test the weight preference



                            (13)
    10 --------------------------------------    
    | \---|       (4)      (8)        (4)   |
    |  (4)\-- 0 -------- 1 -------- 2 ----- 5 ------|             
    |         |        / |        /|       /|       |   
    |    (2)  |       /  |       / |      / |       |
 (7)|         | (11) /   |  (2) /  | (14)/  |       |  
    |         |     / (4)|     /   |    /   |       |  (3)
    |         |    /     |    / (7)|   /    |       |  
    |         |   / (7)  |   /     |  / (10)|       |  
    --------- 7 -------- 8 --------3---------4  (2) |
              |       (6)|              (9)   \---\|
              |----------6--------------------------9   
                (1)                (8)

      Weight of each edge is initialized to 1.
    */
    int V = 11;
    Dijkstra g(V);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 2);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 9, 3);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
    g.addEdge(6, 9, 8);
    g.addEdge(5, 10, 13);
    g.addEdge(10, 7, 7);
    g.addEdge(4, 9, 2);
    g.addEdge(0, 10, 4);
    g.addEdge(1, 8, 4);

    g.shortestPath(s);
    vector<int> path = g.getPathTo(e);
    return path;


        /**
     Generate the following graph to test the weight preference



                            (13)
    10 --------------------------------------    
    | \---|       (4)      (8)        (4)   |
    |  (4)\-- 0 -------- 1 -------- 2 ----- 5 ------|             
    |         |        / |        /|       /|       |   
    |    (2)  |       /  |       / |      / |       |
 (7)|         | (11) /   |  (2) /  | (14)/  |       |  
    |         |     / (4)|     /   |    /   |       |  (3)
    |         |    /     |    / (7)|   /    |       |  
    |         |   / (7)  |   /     |  / (10)|       |  
    --------- 7 -------- 8 --------3---------4  (2) |
              |       (6)|              (9)   \---\|
              |----------6--------------------------9   
                (1)                (8)

      Weight of each edge is initialized to 1.
      **/
}



TEST_CASE("testdijkastra: Basic weight preference", "[weight=20]")
{
    vector<int> testResult_1 = customizedWeightTest_d(0, 2);
    vector<int> expected{0, 1, 2};
    
    REQUIRE(testResult_1 == expected);
}


TEST_CASE("testdijkastra: small graph adjacent test, from 1 to 2", "[weight=20]")
{
    vector<int> testResult_1 = customizedSimpleTest_d(1, 2);
    vector<int> expected{1, 2};
    
    REQUIRE(testResult_1 == expected);
}


TEST_CASE("testdijkastra: small graph test - Adjacent but not shortest, from 0 to 4", "[weight=20]")
{
    vector<int> testResult_1 = customizedSimpleTest_d(0, 4);
    vector<int> expected{0, 1, 4};
    
    REQUIRE(testResult_1 == expected);
}



TEST_CASE("testdijkastra: moderate graph shortest path test (short), from 5 to 6", "[weight=20]")
{
    vector<int> testResult_1 = customizedModerateTest_d(5, 6);
    vector<int> expected{5, 9, 6};
    
    REQUIRE(testResult_1 == expected);
}

TEST_CASE("testdijkastra: moderate graph shortest path test (long), from 9 to 10", "[weight=20]")
{
    vector<int> testResult_1 = customizedModerateTest_d(9, 10);
    vector<int> expected{9, 6, 7, 0, 10};
    
    REQUIRE(testResult_1 == expected);
}

TEST_CASE("testdijkstra: empty graph", "[weight=20]")
{
    Dijkstra d(0); // 0 vertices
    d.shortestPath(0);

    vector<int> path = d.getPathTo(0);
    
    REQUIRE(true);
}

TEST_CASE("testdijkstra: test functionality on the dataset", "[weight=20]")
{
    Dijkstra d(21048); // dataset has 21,048 vertices
    vector<Edge> edges = readEdges("dataset/caledge_modified.txt");
    for (Edge e : edges) {
        d.addEdge(e.getStart(), e.getEnd(), e.getWeight());
    }

    int START = 666;
    int END = 6666;

    d.shortestPath(START);
    vector<int> path = d.getPathTo(END);

    REQUIRE(true);
}
