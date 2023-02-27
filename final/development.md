# Development Log
*Team: dongbeicantbemuckedwith (yulun4-yunxuan5-shihuac2)*

## Mar.28 - Apr.3 (Week 2)

- 'readEdges' to read edges from a file and return a vector of edges. (Yulun Wu)
- 'checkEdges' to check if the format of the data in a file is correct. (Yunxuan Yang)
- edge.h for the Edge class and tests for data reader functions. (Shihua Cheng)

Next week, we plan to complete the implementation of graph using adjacency list, and complete some of the BFS algorithm.

## Apr.4 - Apr.10 (Week 3)

We have completed the following functions during this week:
- The implementation of graph using adjacency list (constructor functions to initiailize graph from a vector of edges as well as 'the big three' functions)
- Data access functions for graph such as 'adjacentVertices(v)' which returns the adjacent vertices to v and 'incidentEdges(v)' which returns the incident edges of v.
- Tests for graph to check its functionality

We have also made a flowchart for the BFS algorithm. Next week, we plan to complete the BFS algorithm and make tests to check its functionality (before 4/15), and start to work on Dijkstra's algorithm.

## Apr.11 - Apr.17 (Week 4)

We have completed the following functions during this week:
- The implementation of BFS algorithm using the adjacency list graph representation and STL queue object, and a 'getTotalWeight' function to calculate the weight of a path
- A Python script to modify the original edge data into a new set of data with the weight of each edge representing the actual length in kilometers
- Tests for BFS algorithm to check its functionality
- Function design for Dijkstra's algorithm: the inputs and output should be the same as the BFS function, will use a self-defined priority queue to keep track of the vertices, will not maintain a graph but only a single path (vector\<int\>).

Next week, we plan to complete the functions for Dijkstra's algorithm and start to write tests for it, and learn about Brandes' algorithm to calculate betweenness centrality.


## Apr.18 - Apr.24 (Week 5)

We have completed the following functions during this week:
- Updated test cases for BFS, Graph object and datareader. Added edge cases such as empty graph, disconnected graph, as well as complex cases such as a graph with 15 vertices. Also, we tested these code on the whole dataset.
- The implementation of Dijkstra's algorithm using adjacency list and the STL priority queue object.
- Simple tests for Dijkstra's algorithm to check its functionality. Currently, it works fine on the whole dataset, and it does return a shorter path than the BFS algorithm.

Next week, we plan to add more tests for Dijkstra's algorithm, and start to work on Brandes' algorithm to calculate betweenness centrality.

## Apr.25 - May.1 (Week 6)

We have completed the following functions during this week:
- Completed all test cases for Dijkstra, including testing on a simple graph, a complex graph, an empty graph and the whole dataset.
- The implementation of Brandes' algorithm on a weighted graph and the testing on the whole dataset.
- A multithreading implementation of Brandes' algorithm to improve speed by ~ 6 times.
- Basic testing on the multithreading implementation to check its stability.

Next week, we plan to complete all the tests required for Brandes' algorithm. After that, the code base of our final project is basically done, and we will start to work on the final report and presentation.


## May.2 - May.6 (Week 7)
