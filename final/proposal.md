# Final Project Proposal

*Team: dongbeicantbemuckedwith*

*Shihua Cheng, Yunxuan Yang, Yulun Wu*

## Leading Question

We will use a database and our code base to solve the following problem: what is the shortest driving distance between any two places in California? We will obtain the necessary information of all the road intersections (nodes) and the distances between these nodes from the database. Next, we will build a BFS traversal function to traverse the graph. Then, we will build an undirected graph containing the nodes and edges as well as a shortest path search function (using Dijkstra’s algorithm). The weights of each edge in the graph will be represented by the geographical length of the path, which is available in the dataset. The final output will be an ordered list of nodes or edges. Moreover, we will use ‘betweenness centrality’ to find the most central place in California.

## Data Acquisition and Processing

### Data format

We will use the Road Network of California in the Real Datasets for Spatial Databases: Road Networks and Points of interest (https://www.cs.utah.edu/~lifeifei/SpatialDataset.htm) as our dataset. The dataset has two files: cal.cnode and cal.cedge, both of which can be converted to .txt files. Each line contains the information of one node/edge that can be processed by the fstream operations in C++.

### Data correction

We will implement a function to check if each dimension of the data has its own value. We will delete the data if we find that it lacks some important information. We will also check the correctness of the data format: whether they are all in numbers. Since we are using the road network of California dataset, we will take out the X coordinate and Y coordinate of each spot and then check whether the coordinates are within the range of California to find out if the data is correct.

The estimated time for correcting data is O(|V|+|E|), where V is the set of vertices and E is the set of edges.

### Data storage

We will implement node and edge classes to store the information of each node/edge. Then, all the nodes and edges will be stored in an undirected graph data structure.

The estimated time for building the graph is O(|E|+|V|), where |V| is the total number of nodes and |E| is the total number of edges.

## Graph algorithms

### Breadth First Search

This algorithm traverses the vertices in the graph until the destination vertex is reached. During the traversal of one vertex, all its unvisited adjacent vertices are pushed into a queue and set as 'visited'.

- Function input: the starting vertex in the graph, and the destination vertex
- Function output: a vector of vertices representing one possible path between the starting point and the destination
- Function efficiency: O(|V|^2) using an adjacency matrix, where V is the set of vertices.

### Shortest path algorithm (Dijkstra's Algorithm)

This algorithm uses a min-priority queue to track the traversal of the edges. Each vertex is assigned with an index representing its distance to the starting point, which is updated during each iteration. When the destination vertex is updated, the algorithm stops.

- Function input: the starting vertex in the graph, and the destination vertex
- Function output: a vector of vertices representing the shortest path between the starting point and the destination
- Function efficiency: O((|E|+|V|)\*log(|V|)) using min-priority queue, where E is the set of edges and V is the set of vertices.

### Betweenness Centrality (Brandes' Algorithm)

This algorithm is based on the pair-wise dependencies between any two vertices in the graph. Then the algorithm will run recursively to calculate the centrality of each vertex in the graph.

- Function input: an unweighted graph representing the California road system
- Function output: void. The function assigns each node with an index representing its 'centrality'.
- Function efficiency: O(|V||E|), where V is the set of vertices and E is the set of edges.

## Timeline

### 1st week (3.21 - 3.27)

- Organize and process the data, attempt to successfully import the dataset to the program

### 2nd week - 4th week (3.28 - 4.17)

- Complete building the traversal function for BFS
- Start to preview and construct Dijkstra's Algorithm *(mid-project check in)*
- Gain basic understanding of between centrality and prepare for accomplishing the second algorithm

### 5th week - 6th week (4.18 - 5.1)

- Complete the algorithms for Betweenness Centrality
	* The calculation of betweenness centrality
	* The way to present in a colored graph described in section 3
	* Begin to compile the whole project

### 7th week (5.2 - 5.6)

- Ensure the whole project can be successfully compiled
- Design the testing program and fix bugs in data calculation and result presentation
- Prepare for the final presentation
