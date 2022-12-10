# CS225 Final Project Written Report

## Project Goal #1: Find Shortest Routes Between 2 Airports (Dijkstra's algorithm)
### Implementation

### Output: 

### Correctness/Testings

---
## Project Goal #2: Find Airport Cluster (Tarjan's strongly connected components algorithm)
### Implementation
Our Tarjan's algorithm uses DFS to traverse through the graph. Upon visiting a node, we add the node into a stack, and set its "low" value equal to its id (low is stored as a vector).

When we get to a visited node, and the node is also on stack, we backtrack and reassign the "low" value to minimum. 

When the current node has visited all its neighbors and its "low" value equal to its id, one strongly connected component is found. 

### Output: 
This is how it looks like in terminal, when finding the airports strongly connected to MEE (Maré Airport): 
![Tarjan output screenshot](images/tarjan_screenshot.png)
If the output has more than 10 airports, the result will be in a new text file called scc-output.txt for better readability.

### Correctness/Testings
We made sure the algorithm works as expected by taking two random nodes in the same strongly connected component, and use a method in Dijsktra.cpp to calculate their distance. If the distance is infinity, the two nodes can't reach each other, which means the algorithm is incorrect because every node in a strongly connected componenet should be able to reach every other nodes in the same component. Our test cases proved that our implementation is correct. 

### Depth-first search (DFS)
Since the Tarjan's algorithm is based on DFS, we combined the code for Tarjan algorithm and DFS together, both in [`Tarjan.cpp`](https://github.com/stacey0331/cs225-final-project/blob/master/open-flight/src/Tarjan.cpp). We go though each node's adjacency nodes first before visiting the next, and mark nodes as visited or unvisited using vectors. 