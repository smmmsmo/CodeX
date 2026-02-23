/*
================================================================================
                     25.3.1: GRAPH BASICS & REPRESENTATIONS
================================================================================
Comprehensive Learning Guide on Graph Fundamentals

TOPIC BREAKDOWN:
• What is a graph? Vertices and edges
• Graph representation (adjacency matrix, adjacency list)
• Directed vs undirected graphs
• Weighted vs unweighted graphs
• Graph properties and characteristics
• Time/space complexity comparison

KEY LEARNING POINTS:
✓ Understanding graph data structure fundamentals
✓ Comparing different graph representations
✓ Implementing adjacency matrix and list
✓ Analyzing time/space tradeoffs
✓ Selecting appropriate representation for problems

================================================================================
                    PART 1: GRAPH FUNDAMENTALS
================================================================================
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
======================= CONCEPT 1: WHAT IS A GRAPH? =======================

A graph G = (V, E) where:
- V: Set of vertices (nodes)
- E: Set of edges (connections between vertices)

Example: Social Network
  Vertices: People
  Edges: Friendships

GRAPH TERMINOLOGY:
• Degree: Number of edges connected to a vertex
• In-Degree: Incoming edges (directed graphs)
• Out-Degree: Outgoing edges (directed graphs)
• Path: Sequence of vertices connected by edges
• Cycle: Path that starts and ends at same vertex
• Connected: Path exists between any two vertices
• Disconnected: At least one pair of vertices has no path

TYPES OF GRAPHS:
1. Undirected: Edges have no direction (A-B same as B-A)
2. Directed: Edges have direction (A→B different from B→A)
3. Weighted: Edges have associated weights/costs
4. Unweighted: All edges have equal weight (1)
5. Sparse: Few edges (E << V²)
6. Dense: Many edges (E ≈ V²)
*/

void example1_graphConcepts() {
  cout << "\n===== EXAMPLE 1: Graph Concepts =====" << endl;

  cout << "Example: Social Network Graph" << endl;
  cout << "Vertices: {Alice, Bob, Charlie, Diana, Eve}" << endl;
  cout << "Edges (undirected):" << endl;
  cout << "  Alice -- Bob" << endl;
  cout << "  Alice -- Charlie" << endl;
  cout << "  Bob -- Diana" << endl;
  cout << "  Charlie -- Diana" << endl;
  cout << "  Diana -- Eve" << endl;

  cout << "\nDegrees:" << endl;
  cout << "  Alice: 2 (Bob, Charlie)" << endl;
  cout << "  Bob: 2 (Alice, Diana)" << endl;
  cout << "  Charlie: 2 (Alice, Diana)" << endl;
  cout << "  Diana: 3 (Bob, Charlie, Eve) - HIGHEST" << endl;
  cout << "  Eve: 1 (Diana)" << endl;

  cout << "\nPaths:" << endl;
  cout << "  Alice to Eve: Alice -> Charlie -> Diana -> Eve" << endl;
  cout << "  Bob to Charlie: Bob -> Alice -> Charlie" << endl;

  cout << "\nGraph Properties:" << endl;
  cout << "  Vertices (V): 5" << endl;
  cout << "  Edges (E): 5" << endl;
  cout << "  Type: Undirected, Unweighted" << endl;
  cout << "  Connected: YES (all vertices reachable)" << endl;
}

/*
======================= CONCEPT 2: ADJACENCY MATRIX =======================

Adjacency Matrix: 2D array where matrix[i][j] represents connection from i to j

FOR UNDIRECTED UNWEIGHTED:
matrix[i][j] = 1 if edge exists, 0 otherwise
matrix[i][j] = matrix[j][i] (symmetric)

FOR UNDIRECTED WEIGHTED:
matrix[i][j] = weight if edge exists, infinity otherwise
matrix[i][j] = matrix[j][i] (symmetric)

FOR DIRECTED:
matrix[i][j] = 1 if edge i→j exists
matrix[i][j] may != matrix[j][i]

SPACE: O(V²) - Always
TIME:
- Insert edge: O(1)
- Remove edge: O(1)
- Check edge: O(1)
- Get neighbors: O(V)
- Iterate all edges: O(V²)

BEST FOR: Dense graphs, O(1) edge lookup
*/

// ===== EXAMPLE 2: Adjacency Matrix - Undirected Unweighted =====
class AdjacencyMatrix {
private:
  int numVertices;
  vector<vector<int>> matrix;
  vector<string> vertexLabels;

public:
  AdjacencyMatrix(int v) : numVertices(v) {
    matrix.assign(v, vector<int>(v, 0));
  }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v) {
    matrix[u][v] = 1;
    matrix[v][u] = 1; // Undirected
  }

  void removeEdge(int u, int v) {
    matrix[u][v] = 0;
    matrix[v][u] = 0;
  }

  bool hasEdge(int u, int v) { return matrix[u][v] == 1; }

  vector<int> getNeighbors(int v) {
    vector<int> neighbors;
    for (int i = 0; i < numVertices; i++) {
      if (matrix[v][i] == 1) {
        neighbors.push_back(i);
      }
    }
    return neighbors;
  }

  int getDegree(int v) { return getNeighbors(v).size(); }

  void print() {
    cout << "Adjacency Matrix:" << endl;
    cout << "     ";
    for (int i = 0; i < numVertices; i++) {
      cout << vertexLabels[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < numVertices; i++) {
      cout << vertexLabels[i] << "   ";
      for (int j = 0; j < numVertices; j++) {
        cout << matrix[i][j] << " ";
      }
      cout << endl;
    }
  }

  void printStatistics() {
    cout << "\nGraph Statistics:" << endl;
    cout << "Vertices: " << numVertices << endl;

    int edgeCount = 0;
    for (int i = 0; i < numVertices; i++) {
      for (int j = i + 1; j < numVertices; j++) {
        if (matrix[i][j] == 1)
          edgeCount++;
      }
    }
    cout << "Edges: " << edgeCount << endl;

    cout << "Vertex Degrees:" << endl;
    for (int i = 0; i < numVertices; i++) {
      cout << "  " << vertexLabels[i] << ": " << getDegree(i) << endl;
    }
  }
};

void example2_adjacencyMatrix() {
  cout << "\n===== EXAMPLE 2: Adjacency Matrix (Undirected) =====" << endl;

  AdjacencyMatrix graph(5);
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");
  graph.addVertex("E");

  cout << "Adding edges: A-B, A-C, B-D, C-D, D-E" << endl;
  graph.addEdge(0, 1); // A-B
  graph.addEdge(0, 2); // A-C
  graph.addEdge(1, 3); // B-D
  graph.addEdge(2, 3); // C-D
  graph.addEdge(3, 4); // D-E

  graph.print();
  graph.printStatistics();

  cout << "\nNeighbors of D: ";
  for (int neighbor : graph.getNeighbors(3)) {
    cout << (char)('A' + neighbor) << " ";
  }
  cout << endl;
}

/*
======================= CONCEPT 3: ADJACENCY LIST =======================

Adjacency List: Each vertex has a list of its neighbors

Representation options:
1. Array of vectors: vector<vector<int>> adj
2. Hash map: unordered_map<int, vector<int>> adj
3. Linked lists: vector<LinkedList*> adj

SPACE: O(V + E) - Much better for sparse graphs!
TIME:
- Insert edge: O(1) amortized
- Remove edge: O(degree) to O(E)
- Check edge: O(degree) worst case O(V)
- Get neighbors: O(degree)
- Iterate all edges: O(V + E)

BEST FOR: Sparse graphs, general purpose
*/

// ===== EXAMPLE 3: Adjacency List - Undirected Unweighted =====
class AdjacencyList {
private:
  int numVertices;
  vector<vector<int>> adj;
  vector<string> vertexLabels;

public:
  AdjacencyList(int v) : numVertices(v) { adj.resize(v); }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u); // Undirected
  }

  void removeEdge(int u, int v) {
    adj[u].erase(remove(adj[u].begin(), adj[u].end(), v), adj[u].end());
    adj[v].erase(remove(adj[v].begin(), adj[v].end(), u), adj[v].end());
  }

  bool hasEdge(int u, int v) {
    return find(adj[u].begin(), adj[u].end(), v) != adj[u].end();
  }

  vector<int> getNeighbors(int v) { return adj[v]; }

  int getDegree(int v) { return adj[v].size(); }

  void print() {
    cout << "Adjacency List:" << endl;
    for (int i = 0; i < numVertices; i++) {
      cout << vertexLabels[i] << ": ";
      for (int neighbor : adj[i]) {
        cout << vertexLabels[neighbor] << " ";
      }
      cout << endl;
    }
  }

  void printStatistics() {
    cout << "\nGraph Statistics:" << endl;
    cout << "Vertices: " << numVertices << endl;

    int edgeCount = 0;
    for (int i = 0; i < numVertices; i++) {
      edgeCount += adj[i].size();
    }
    edgeCount /= 2; // Undirected - each edge counted twice
    cout << "Edges: " << edgeCount << endl;

    cout << "Vertex Degrees:" << endl;
    for (int i = 0; i < numVertices; i++) {
      cout << "  " << vertexLabels[i] << ": " << getDegree(i) << endl;
    }
  }
};

void example3_adjacencyList() {
  cout << "\n===== EXAMPLE 3: Adjacency List (Undirected) =====" << endl;

  AdjacencyList graph(5);
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");
  graph.addVertex("E");

  cout << "Adding edges: A-B, A-C, B-D, C-D, D-E" << endl;
  graph.addEdge(0, 1);
  graph.addEdge(0, 2);
  graph.addEdge(1, 3);
  graph.addEdge(2, 3);
  graph.addEdge(3, 4);

  graph.print();
  graph.printStatistics();

  cout << "\nNeighbors of D: ";
  for (int neighbor : graph.getNeighbors(3)) {
    cout << (char)('A' + neighbor) << " ";
  }
  cout << endl;
}

/*
======================= CONCEPT 4: DIRECTED VS UNDIRECTED
=======================

UNDIRECTED GRAPH: Edges are bidirectional (A-B means both A→B and B→A)
- Add edge: matrix[u][v] = matrix[v][u] = 1
- Symmetric matrix representation
- Example: Social networks (mutual friendships)

DIRECTED GRAPH (DIGRAPH): Edges have direction (A→B doesn't imply B→A)
- Add edge: matrix[u][v] = 1 only
- Asymmetric matrix representation
- In-degree: edges pointing TO vertex
- Out-degree: edges pointing FROM vertex
- Example: Web links, roads, following relationships
*/

// ===== EXAMPLE 4: Directed Graph =====
class DirectedGraph {
private:
  int numVertices;
  vector<vector<int>> adj;
  vector<string> vertexLabels;

public:
  DirectedGraph(int v) : numVertices(v) { adj.resize(v); }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v) {
    adj[u].push_back(v); // Only u→v, NOT v→u
  }

  int getInDegree(int v) {
    int inDegree = 0;
    for (int i = 0; i < numVertices; i++) {
      for (int neighbor : adj[i]) {
        if (neighbor == v)
          inDegree++;
      }
    }
    return inDegree;
  }

  int getOutDegree(int v) { return adj[v].size(); }

  void print() {
    cout << "Directed Graph (Adjacency List):" << endl;
    for (int i = 0; i < numVertices; i++) {
      cout << vertexLabels[i] << " → ";
      for (int neighbor : adj[i]) {
        cout << vertexLabels[neighbor] << " ";
      }
      if (adj[i].empty())
        cout << "(no outgoing edges)";
      cout << endl;
    }
  }

  void printDegrees() {
    cout << "\nVertex Degrees (In-Degree, Out-Degree):" << endl;
    for (int i = 0; i < numVertices; i++) {
      cout << "  " << vertexLabels[i] << ": (" << getInDegree(i) << ", "
           << getOutDegree(i) << ")" << endl;
    }
  }
};

void example4_directedGraph() {
  cout << "\n===== EXAMPLE 4: Directed Graph =====" << endl;

  DirectedGraph graph(4);
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");

  cout << "Adding directed edges: A→B, A→C, B→C, B→D, C→D" << endl;
  graph.addEdge(0, 1); // A→B
  graph.addEdge(0, 2); // A→C
  graph.addEdge(1, 2); // B→C
  graph.addEdge(1, 3); // B→D
  graph.addEdge(2, 3); // C→D

  graph.print();
  graph.printDegrees();
}

/*
======================= CONCEPT 5: WEIGHTED GRAPHS =======================

Weighted Graph: Each edge has an associated weight/cost

Examples:
- Road networks: weight = distance or travel time
- Airline routes: weight = cost or distance
- Communication networks: weight = latency or bandwidth

REPRESENTATION:
Matrix: matrix[i][j] = weight (instead of 0/1)
List: vector<pair<int, int>> - (neighbor, weight)

Initialization:
- Weighted edges present: matrix[u][v] = weight
- Weighted edges absent: matrix[u][v] = infinity (INT_MAX)
*/

// ===== EXAMPLE 5: Weighted Undirected Graph =====
class WeightedGraph {
private:
  int numVertices;
  vector<vector<pair<int, int>>> adj; // {neighbor, weight}
  vector<string> vertexLabels;
  const int INF = INT_MAX;

public:
  WeightedGraph(int v) : numVertices(v) { adj.resize(v); }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v, int weight) {
    adj[u].push_back({v, weight});
    adj[v].push_back({u, weight}); // Undirected
  }

  int getWeight(int u, int v) {
    for (auto &edge : adj[u]) {
      if (edge.first == v)
        return edge.second;
    }
    return INF;
  }

  void print() {
    cout << "Weighted Graph:" << endl;
    for (int i = 0; i < numVertices; i++) {
      cout << vertexLabels[i] << ": ";
      for (auto &edge : adj[i]) {
        cout << "(" << vertexLabels[edge.first] << ", w=" << edge.second
             << ") ";
      }
      cout << endl;
    }
  }
};

void example5_weightedGraph() {
  cout << "\n===== EXAMPLE 5: Weighted Graph =====" << endl;

  WeightedGraph graph(4);
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");

  cout << "Adding weighted edges:" << endl;
  cout << "  A-B (weight: 4)" << endl;
  cout << "  A-C (weight: 2)" << endl;
  cout << "  B-C (weight: 1)" << endl;
  cout << "  B-D (weight: 5)" << endl;
  cout << "  C-D (weight: 8)" << endl;

  graph.addEdge(0, 1, 4);
  graph.addEdge(0, 2, 2);
  graph.addEdge(1, 2, 1);
  graph.addEdge(1, 3, 5);
  graph.addEdge(2, 3, 8);

  graph.print();
}

/*
================================================================================
                        KEY CONCEPTS SUMMARY
================================================================================

1. GRAPH COMPONENTS:
   ✓ Vertices: Nodes in the graph
   ✓ Edges: Connections between vertices
   ✓ Degree: Number of edges connected to vertex

2. GRAPH TYPES:
   ✓ Undirected: Bidirectional edges
   ✓ Directed: One-way edges (in-degree, out-degree)
   ✓ Weighted: Edges have associated costs
   ✓ Unweighted: All edges equal weight

3. ADJACENCY MATRIX:
   ✓ Space: O(V²)
   ✓ Edge lookup: O(1)
   ✓ Best for: Dense graphs

4. ADJACENCY LIST:
   ✓ Space: O(V + E)
   ✓ Neighbor iteration: O(degree)
   ✓ Best for: Sparse graphs

5. REPRESENTATION COMPARISON:
   ┌─────────────────┬────────────────┬──────────────────┐
   │ Operation       │ Matrix O(?)    │ List O(?)        │
   ├─────────────────┼────────────────┼──────────────────┤
   │ Add edge        │ 1              │ 1 amortized      │
   │ Remove edge     │ 1              │ degree           │
   │ Check edge      │ 1              │ degree / log(V)  │
   │ Get neighbors   │ V              │ degree           │
   │ All edges       │ V²             │ V + E            │
   │ Space           │ V²             │ V + E            │
   └─────────────────┴────────────────┴──────────────────┘

================================================================================
                        COMMON MISTAKES TO AVOID
================================================================================

❌ MISTAKE 1: Using matrix for sparse graphs
✓ CORRECT: Use adjacency list for sparse graphs (saves space)

❌ MISTAKE 2: Forgetting to add reverse edge in undirected graphs
✓ CORRECT: Always add both u→v and v→u for undirected graphs

❌ MISTAKE 3: Using weight 0 for missing edges
✓ CORRECT: Use infinity (INT_MAX) for missing edges

❌ MISTAKE 4: Confusing in-degree and out-degree in directed graphs
✓ CORRECT: In-degree = incoming edges, Out-degree = outgoing edges

❌ MISTAKE 5: Inefficient neighbor lookup in adjacency matrix
✓ CORRECT: Use adjacency list for efficient iteration

❌ MISTAKE 6: Forgetting graph is disconnected
✓ CORRECT: Check connectivity before algorithms requiring it

================================================================================
                        PRACTICE EXERCISES
================================================================================

Exercise 1: Implement both representations for same graph and compare

Exercise 2: Convert adjacency matrix to adjacency list and vice versa

Exercise 3: Find vertex with highest degree

Exercise 4: Count total number of edges in graph

Exercise 5: Check if graph is sparse or dense

Exercise 6: Implement directed weighted graph class

Exercise 7: Find all vertices with specific degree

Exercise 8: Implement graph representation using hash map

Exercise 9: Build a road network graph with cities and distances

Exercise 10: Implement graph serialization (save/load graph)

================================================================================
*/

void example6_comparisonAnalysis() {
  cout << "\n===== EXAMPLE 6: Representation Comparison =====" << endl;

  cout << "\nScenario 1: DENSE Graph (V=100, E≈4950)" << endl;
  cout << "Recommendation: Adjacency Matrix" << endl;
  cout << "  Space: 100² = 10,000 integers" << endl;
  cout << "  Benefit: O(1) edge lookup" << endl;

  cout << "\nScenario 2: SPARSE Graph (V=100, E=150)" << endl;
  cout << "Recommendation: Adjacency List" << endl;
  cout << "  Space: 100 + 150*2 = 400 integers (vs 10,000)" << endl;
  cout << "  Benefit: 96% space savings for sparse graph" << endl;

  cout << "\nScenario 3: Social Network (V=1M, E=100M)" << endl;
  cout << "Recommendation: Adjacency List" << endl;
  cout << "  Space: 1M + 100M*2 = ~400M integers" << endl;
  cout << "  Matrix would need: 1M² = 1 trillion integers!" << endl;
  cout << "  Difference: Infeasible with matrix" << endl;
}

// ===== MAIN FUNCTION =====
int main() {
  cout << "\n" << string(80, '=') << endl;
  cout << "    25.3.1: GRAPH BASICS & REPRESENTATIONS - LEARNING GUIDE" << endl;
  cout << string(80, '=') << endl;

  try {
    example1_graphConcepts();
    example2_adjacencyMatrix();
    example3_adjacencyList();
    example4_directedGraph();
    example5_weightedGraph();
    example6_comparisonAnalysis();

    cout << "\n" << string(80, '=') << endl;
    cout << "All examples completed successfully!" << endl;
    cout << string(80, '=') << endl;
  } catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
  }

  return 0;
}
