/*
================================================================================
                    25.3.4: SHORTEST PATH ALGORITHMS
================================================================================
Comprehensive Learning Guide on Finding Shortest Paths in Graphs

TOPIC BREAKDOWN:
• Dijkstra's Algorithm - Single-source, non-negative weights
• Bellman-Ford Algorithm - Single-source, handles negative weights
• Floyd-Warshall Algorithm - All-pairs shortest paths
• A* Algorithm - Heuristic-based pathfinding
• Comparison and appropriate use cases

KEY LEARNING POINTS:
✓ Understanding shortest path problem variants
✓ Implementing efficient shortest path algorithms
✓ Handling negative edges and cycles
✓ Using heuristics for A* algorithm
✓ Selecting appropriate algorithm for problem

================================================================================
                    PART 1: DIJKSTRA'S ALGORITHM
================================================================================
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>
using namespace std;

const int INF = INT_MAX;

/*
======================= CONCEPT 1: DIJKSTRA'S ALGORITHM =======================

Dijkstra's Algorithm: Find shortest path from source to all other vertices
- ONLY works with NON-NEGATIVE edge weights
- Greedy algorithm: Always pick shortest unvisited vertex

Algorithm:
1. Initialize distances[source] = 0, all others = infinity
2. Use priority queue (min-heap by distance)
3. While priority queue not empty:
   a. Extract vertex u with minimum distance
   b. For each neighbor v of u:
      - If distance[u] + weight(u,v) < distance[v]:
        * Update distance[v]
        * Enqueue v with new distance

Time: O((V + E) log V) with binary heap
Space: O(V)

WHY NOT NEGATIVE WEIGHTS?
- Greedy approach assumes shortest known distance is final
- Negative weights can update "finalized" distances
- Would require additional passes

PROPERTIES:
- Finds shortest paths to all vertices from source
- Optimal for sparse graphs with binary heap
- Can reconstruct paths using parent array
*/

// ===== EXAMPLE 1: Dijkstra's Algorithm =====
class DijkstraPathfinder {
private:
  int numVertices;
  vector<vector<pair<int, int>>> adj; // {neighbor, weight}
  vector<string> vertexLabels;

public:
  DijkstraPathfinder(int v) : numVertices(v) { adj.resize(v); }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v, int weight) {
    adj[u].push_back({v, weight});
    adj[v].push_back({u, weight});
  }

  void dijkstra(int source) {
    vector<int> distances(numVertices, INF);
    vector<int> parent(numVertices, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;

    distances[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
      auto [dist, u] = pq.top();
      pq.pop();

      // Skip if we've already processed this vertex with shorter distance
      if (dist > distances[u])
        continue;

      // Relax edges
      for (auto [v, weight] : adj[u]) {
        if (distances[u] + weight < distances[v]) {
          distances[v] = distances[u] + weight;
          parent[v] = u;
          pq.push({distances[v], v});
        }
      }
    }

    // Print results
    cout << "Shortest distances from " << vertexLabels[source] << ":" << endl;
    for (int i = 0; i < numVertices; i++) {
      if (distances[i] == INF) {
        cout << "  To " << vertexLabels[i] << ": UNREACHABLE" << endl;
      } else {
        cout << "  To " << vertexLabels[i] << ": " << distances[i]
             << " (path: ";

        // Reconstruct path
        vector<int> path;
        int curr = i;
        while (curr != -1) {
          path.push_back(curr);
          curr = parent[curr];
        }
        reverse(path.begin(), path.end());

        for (int v : path) {
          cout << vertexLabels[v];
          if (v != i)
            cout << " → ";
        }
        cout << ")" << endl;
      }
    }
  }
};

void example1_dijkstra() {
  cout << "\n===== EXAMPLE 1: Dijkstra's Algorithm =====" << endl;

  DijkstraPathfinder graph(6);
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");
  graph.addVertex("E");
  graph.addVertex("F");

  graph.addEdge(0, 1, 4);  // A-B: 4
  graph.addEdge(0, 2, 2);  // A-C: 2
  graph.addEdge(1, 2, 1);  // B-C: 1
  graph.addEdge(1, 3, 5);  // B-D: 5
  graph.addEdge(2, 3, 8);  // C-D: 8
  graph.addEdge(2, 4, 10); // C-E: 10
  graph.addEdge(3, 5, 2);  // D-F: 2
  graph.addEdge(4, 5, 3);  // E-F: 3

  cout << "Graph with weighted edges:" << endl;
  cout << "  A-B(4), A-C(2), B-C(1), B-D(5), C-D(8), C-E(10), D-F(2), E-F(3)"
       << endl;

  graph.dijkstra(0);
}

/*
======================= CONCEPT 2: BELLMAN-FORD ALGORITHM
=======================

Bellman-Ford Algorithm: Find shortest paths from source to all vertices
- Works with NEGATIVE edge weights
- Detects negative weight cycles
- Slower than Dijkstra but more general

Algorithm:
1. Initialize distances[source] = 0, all others = infinity
2. For i = 1 to V-1:
   - For each edge (u,v,w):
     * If distance[u] + w < distance[v]:
       * distance[v] = distance[u] + w
3. Check for negative cycles:
   - For each edge (u,v,w):
     * If distance[u] + w < distance[v]: cycle found

Time: O(V * E)
Space: O(V)

NEGATIVE CYCLE DETECTION:
- If distances still improve in V-th iteration, negative cycle exists
- Any vertex affected by negative cycle cannot have correct distance

USE CASES:
- Currency exchange arbitrage
- Network routing (handles link failures)
- Any graph with negative edges
*/

// ===== EXAMPLE 2: Bellman-Ford Algorithm =====
class BellmanFordPathfinder {
private:
  struct Edge {
    int u, v, weight;
  };

  int numVertices;
  vector<Edge> edges;
  vector<string> vertexLabels;

public:
  BellmanFordPathfinder(int v) : numVertices(v) {}

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v, int weight) { edges.push_back({u, v, weight}); }

  void bellmanFord(int source) {
    vector<int> distances(numVertices, INF);
    distances[source] = 0;

    // Relax edges V-1 times
    for (int i = 0; i < numVertices - 1; i++) {
      for (const Edge &e : edges) {
        if (distances[e.u] != INF &&
            distances[e.u] + e.weight < distances[e.v]) {
          distances[e.v] = distances[e.u] + e.weight;
        }
      }
    }

    // Check for negative cycle
    bool negativeCycle = false;
    for (const Edge &e : edges) {
      if (distances[e.u] != INF && distances[e.u] + e.weight < distances[e.v]) {
        negativeCycle = true;
        break;
      }
    }

    if (negativeCycle) {
      cout << "Negative cycle detected! Shortest paths undefined." << endl;
    } else {
      cout << "Shortest distances from " << vertexLabels[source] << ":" << endl;
      for (int i = 0; i < numVertices; i++) {
        if (distances[i] == INF) {
          cout << "  To " << vertexLabels[i] << ": UNREACHABLE" << endl;
        } else {
          cout << "  To " << vertexLabels[i] << ": " << distances[i] << endl;
        }
      }
    }
  }
};

void example2_bellmanFord() {
  cout << "\n===== EXAMPLE 2: Bellman-Ford Algorithm =====" << endl;

  // Example 1: No negative cycle
  cout << "Example 1: Graph without negative cycle" << endl;
  BellmanFordPathfinder graph1(4);
  graph1.addVertex("A");
  graph1.addVertex("B");
  graph1.addVertex("C");
  graph1.addVertex("D");

  graph1.addEdge(0, 1, -1); // A→B: -1
  graph1.addEdge(0, 2, 4);  // A→C: 4
  graph1.addEdge(1, 2, 3);  // B→C: 3
  graph1.addEdge(1, 3, 2);  // B→D: 2
  graph1.addEdge(2, 3, 5);  // C→D: 5

  graph1.bellmanFord(0);

  // Example 2: With negative cycle
  cout << "\nExample 2: Graph with negative cycle" << endl;
  BellmanFordPathfinder graph2(3);
  graph2.addVertex("X");
  graph2.addVertex("Y");
  graph2.addVertex("Z");

  graph2.addEdge(0, 1, 1);  // X→Y: 1
  graph2.addEdge(1, 2, -3); // Y→Z: -3
  graph2.addEdge(2, 0, 1);  // Z→X: 1 (cycle total: -1)

  graph2.bellmanFord(0);
}

/*
======================= CONCEPT 3: FLOYD-WARSHALL ALGORITHM
=======================

Floyd-Warshall Algorithm: Find shortest paths between ALL pairs of vertices
- Works with negative weights (but not negative cycles)
- Dynamic programming approach
- Simpler than running Dijkstra/Bellman-Ford from each vertex

Algorithm:
1. Initialize dist[i][j] = weight(i,j) or infinity
2. For k = 0 to V-1:
   - For i = 0 to V-1:
     * For j = 0 to V-1:
       * dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

The k loop represents "using vertex k as intermediate"

Time: O(V³)
Space: O(V²)

USE CASES:
- Small dense graphs (V < 500)
- All-pairs shortest paths needed
- Transitive closure computation
- Network routing tables

WHY NOT FOR LARGE GRAPHS?
- V³ time is prohibitive for large V
- Use Dijkstra from each vertex for sparse graphs
*/

// ===== EXAMPLE 3: Floyd-Warshall Algorithm =====
class FloydWarshallPathfinder {
private:
  int numVertices;
  vector<vector<int>> dist;
  vector<string> vertexLabels;

public:
  FloydWarshallPathfinder(int v) : numVertices(v) {
    dist.assign(v, vector<int>(v, INF));
    for (int i = 0; i < v; i++) {
      dist[i][i] = 0;
    }
  }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v, int weight) {
    dist[u][v] = min(dist[u][v], weight);
  }

  void floydWarshall() {
    // k: intermediate vertex
    for (int k = 0; k < numVertices; k++) {
      // i: source
      for (int i = 0; i < numVertices; i++) {
        // j: destination
        for (int j = 0; j < numVertices; j++) {
          if (dist[i][k] != INF && dist[k][j] != INF) {
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
          }
        }
      }
    }
  }

  void printDistances() {
    cout << "All-pairs shortest paths:" << endl;
    cout << "     ";
    for (int i = 0; i < numVertices; i++) {
      cout << vertexLabels[i] << "   ";
    }
    cout << endl;

    for (int i = 0; i < numVertices; i++) {
      cout << vertexLabels[i] << "   ";
      for (int j = 0; j < numVertices; j++) {
        if (dist[i][j] == INF) {
          cout << "∞   ";
        } else {
          cout << dist[i][j] << "   ";
        }
      }
      cout << endl;
    }
  }

  int getDistance(int u, int v) { return dist[u][v]; }
};

void example3_floydWarshall() {
  cout << "\n===== EXAMPLE 3: Floyd-Warshall Algorithm =====" << endl;

  FloydWarshallPathfinder graph(4);
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");

  graph.addEdge(0, 1, 3); // A→B: 3
  graph.addEdge(0, 2, 8); // A→C: 8
  graph.addEdge(0, 3, 7); // A→D: 7
  graph.addEdge(1, 2, 2); // B→C: 2
  graph.addEdge(2, 3, 1); // C→D: 1
  graph.addEdge(3, 0, 2); // D→A: 2

  cout << "Before Floyd-Warshall (direct edges only):" << endl;
  graph.printDistances();

  graph.floydWarshall();

  cout << "\nAfter Floyd-Warshall (all-pairs shortest):" << endl;
  graph.printDistances();
}

/*
======================= CONCEPT 4: A* ALGORITHM =======================

A* Algorithm: Best-first search with heuristic
- Combines actual cost (g) with estimated cost to goal (h)
- f(n) = g(n) + h(n)
- g(n) = actual cost from start to n
- h(n) = estimated cost from n to goal (HEURISTIC)

Algorithm:
1. Start with source vertex
2. While goal not found:
   a. Expand vertex with lowest f(n)
   b. For each neighbor v:
      - If v not visited or new path is shorter:
        * Update cost g(v)
        * Calculate f(v) = g(v) + h(v)
        * Add to queue

HEURISTIC PROPERTIES:
- Admissible: Never overestimates actual cost to goal
- Consistent: h(n) ≤ cost(n,m) + h(m)
- Better heuristic = Fewer expansions

TIME COMPLEXITY:
- O(b^d) where b = branching factor, d = depth
- With good heuristic: much faster than uninformed search

APPLICATIONS:
- Pathfinding in games
- GPS navigation (Euclidean distance as heuristic)
- Robot motion planning
- Puzzle solving (8-puzzle, etc.)
*/

// ===== EXAMPLE 4: A* Algorithm =====
struct Node {
  int id;
  double g, h, f; // g: cost so far, h: heuristic, f: total
  int parent;

  bool operator>(const Node &other) const {
    return f > other.f; // Min-heap by f
  }
};

class AStarPathfinder {
private:
  int numVertices;
  vector<vector<pair<int, double>>> adj;
  vector<string> vertexLabels;
  vector<pair<double, double>> positions; // For Euclidean heuristic

  double euclideanDistance(int u, int v) {
    double dx = positions[u].first - positions[v].first;
    double dy = positions[u].second - positions[v].second;
    return sqrt(dx * dx + dy * dy);
  }

public:
  AStarPathfinder(int v) : numVertices(v) { adj.resize(v); }

  void addVertex(string label, double x, double y) {
    vertexLabels.push_back(label);
    positions.push_back({x, y});
  }

  void addEdge(int u, int v, double weight) {
    adj[u].push_back({v, weight});
    adj[v].push_back({u, weight});
  }

  vector<int> astar(int start, int goal) {
    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    vector<bool> closed(numVertices, false);
    vector<double> gScores(numVertices, numeric_limits<double>::infinity());
    vector<int> parent(numVertices, -1);

    gScores[start] = 0;
    double hStart = euclideanDistance(start, goal);
    openSet.push({start, 0, hStart, hStart, -1});

    while (!openSet.empty()) {
      Node current = openSet.top();
      openSet.pop();

      if (current.id == goal) {
        // Reconstruct path
        vector<int> path;
        int node = goal;
        while (node != -1) {
          path.push_back(node);
          node = parent[node];
        }
        reverse(path.begin(), path.end());
        return path;
      }

      if (closed[current.id])
        continue;
      closed[current.id] = true;

      for (auto [neighbor, weight] : adj[current.id]) {
        if (closed[neighbor])
          continue;

        double tentativeG = gScores[current.id] + weight;

        if (tentativeG < gScores[neighbor]) {
          parent[neighbor] = current.id;
          gScores[neighbor] = tentativeG;
          double h = euclideanDistance(neighbor, goal);
          double f = tentativeG + h;
          openSet.push({neighbor, tentativeG, h, f, current.id});
        }
      }
    }

    return {}; // No path found
  }

  void printPath(vector<int> &path) {
    if (path.empty()) {
      cout << "No path found!" << endl;
    } else {
      cout << "Path: ";
      for (int i = 0; i < path.size(); i++) {
        cout << vertexLabels[path[i]];
        if (i < path.size() - 1)
          cout << " → ";
      }
      cout << " (length: " << path.size() - 1 << ")" << endl;
    }
  }
};

void example4_astar() {
  cout << "\n===== EXAMPLE 4: A* Algorithm =====" << endl;

  AStarPathfinder graph(6);

  // Add vertices with positions (simulating 2D grid)
  graph.addVertex("A", 0, 0);
  graph.addVertex("B", 1, 0);
  graph.addVertex("C", 2, 0);
  graph.addVertex("D", 0, 1);
  graph.addVertex("E", 1, 1);
  graph.addVertex("F", 2, 1);

  // Add edges with weights
  graph.addEdge(0, 1, 1); // A-B
  graph.addEdge(0, 3, 1); // A-D
  graph.addEdge(1, 2, 1); // B-C
  graph.addEdge(1, 4, 1); // B-E
  graph.addEdge(2, 5, 1); // C-F
  graph.addEdge(3, 4, 1); // D-E
  graph.addEdge(4, 5, 1); // E-F

  cout << "Grid graph, finding path from A to F" << endl;
  cout << "A(0,0) - B(1,0) - C(2,0)" << endl;
  cout << "|        |        |" << endl;
  cout << "D(0,1) - E(1,1) - F(2,1)" << endl;

  auto path = graph.astar(0, 5); // A to F
  cout << "\nA* path: ";
  graph.printPath(path);
}

/*
================================================================================
                        KEY CONCEPTS SUMMARY
================================================================================

1. DIJKSTRA'S ALGORITHM:
   ✓ Non-negative weights only
   ✓ Time: O((V+E)logV) with binary heap
   ✓ Best for: Sparse graphs, navigation
   ✓ Single-source shortest paths

2. BELLMAN-FORD ALGORITHM:
   ✓ Handles negative weights
   ✓ Detects negative cycles
   ✓ Time: O(VE)
   ✓ Best for: Negative weights, cycle detection

3. FLOYD-WARSHALL ALGORITHM:
   ✓ All-pairs shortest paths
   ✓ Time: O(V³)
   ✓ Best for: Small dense graphs, all-pairs needed
   ✓ Works with negative weights

4. A* ALGORITHM:
   ✓ Uses heuristic (admissible)
   ✓ Time: O(b^d) with good heuristic
   ✓ Best for: Pathfinding with known goal
   ✓ Requires Euclidean distance or similar heuristic

5. COMPARISON TABLE:
   ┌──────────────┬──────────────┬────────────┬──────────┐
   │ Algorithm    │ Time         │ Neg Weights│ Use Case │
   ├──────────────┼──────────────┼────────────┼──────────┤
   │ Dijkstra     │ (V+E)logV    │ No         │ GPS      │
   │ Bellman-Ford │ VE           │ Yes        │ Network  │
   │ Floyd-W      │ V³           │ Yes        │ All-pair │
   │ A*           │ b^d          │ No         │ Games    │
   └──────────────┴──────────────┴────────────┴──────────┘

================================================================================
                        COMMON MISTAKES TO AVOID
================================================================================

❌ MISTAKE 1: Using Dijkstra with negative weights
✓ CORRECT: Use Bellman-Ford for negative weights

❌ MISTAKE 2: Not initializing distances and parent arrays
✓ CORRECT: Set distances to infinity (except source=0)

❌ MISTAKE 3: Bad A* heuristic (overestimates)
✓ CORRECT: Use admissible heuristic that never overestimates

❌ MISTAKE 4: Not detecting negative cycles
✓ CORRECT: Do extra iteration check in Bellman-Ford

❌ MISTAKE 5: Using Floyd-Warshall for large graphs
✓ CORRECT: Use Dijkstra/Bellman-Ford for sparse graphs

================================================================================
                        PRACTICE EXERCISES
================================================================================

Exercise 1: Implement all four algorithms on same graph

Exercise 2: Compare runtime for different graph sizes

Exercise 3: Detect negative cycles and report vertices affected

Exercise 4: Find shortest path between two specific vertices

Exercise 5: Implement with path reconstruction

Exercise 6: Build GPS navigation system (Dijkstra + heuristic)

Exercise 7: Currency arbitrage detection (Bellman-Ford)

Exercise 8: All-pairs shortest paths analysis (Floyd-Warshall)

Exercise 9: A* with custom heuristics (Manhattan vs Euclidean)

Exercise 10: Implement bidirectional search optimization

================================================================================
*/

// ===== MAIN FUNCTION =====
int main() {
  cout << "\n" << string(80, '=') << endl;
  cout << "       25.3.4: SHORTEST PATH ALGORITHMS - LEARNING GUIDE" << endl;
  cout << string(80, '=') << endl;

  try {
    example1_dijkstra();
    example2_bellmanFord();
    example3_floydWarshall();
    example4_astar();

    cout << "\n" << string(80, '=') << endl;
    cout << "All examples completed successfully!" << endl;
    cout << string(80, '=') << endl;
  } catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
  }

  return 0;
}
