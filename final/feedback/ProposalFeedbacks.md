### Grade
Incomplete (0%), must resubmit for regrade. 

## Comments 
**Dataset** Generally looks good, I just have one comment: what is going to be weights on each edge? It seems like you want the weights to be distances between geographical points.
However, is this information already available in the dataset? Is it something that you will need to calculate? In either case, you should mention how to obtain that information. 

**Graph Algorithms** This is the major reason that you are getting a 0 for this proposal. In particular, several problems comes with your proposed kd-tree algorithm. First and for most, 
It is an algorithm that we already covered in class, and we do not allow for 2 covered algorithm. The format we require is 1+1+1, where the first 1 is selected from DFS and BFS, 
the second 1 is a covered algorithm, of which the Dijkstra's algorithm is an example, and the third 1 is an uncovered algorithm. Currently you have the second 1 (Dijkstra's) and 
the third 1 (Betweeness Centrality). The second problem is that kd-tree doesn't really make sense for your application, either. Kd-tree is a data structure that organizes points 
in the Euclidean space into hyperplanes, but the records in your dataset don't corresponds well with points in an Euclidean space. In particular, how would you define a sensible 
distance function that takes into acconut all the dimensions of a record? The third problem is that, kd-tree is not an algorithm but just a data structure, saying that the find 
nearest neighbor is an aglorithm is far-fetched, much like one would not call a binary search tree `find()` to be an algorithm. These are more accurately described as operations 
associated with a particular data structure. That being said, there is an easy fix to your problem: just replace your kd-tree with one of BFS/DFS, whichever one you like the most. 
As for the run time estimates you gave, writing them in terms of n doesn't really make much sense, as a graph has two parameters that you should account for, one is the number of 
vertices, |V|, the other is the number of edges, |E|. For example, the Dijkstra's algorithm takes time O((|E|+|V|) log |V|), assuming one uses the binary min-heap as the PriorityQueue. 
While these run times are not binding and won't really affect your grade, please still try to get them at least syntactically correct.

**Timeline** Too rough, be more specific. In particular, list which algorithm should be accomplished by what date. 

### Grade Update
Sophisticated (100%), but with a -10% regrade penalty, the final grade is 90%.
