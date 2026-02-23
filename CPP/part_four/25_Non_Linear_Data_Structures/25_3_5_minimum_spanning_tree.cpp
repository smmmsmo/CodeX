/*
================================================================================
                25.3.5: MINIMUM SPANNING TREE (MST) ALGORITHMS
================================================================================
Comprehensive Learning Guide on Finding Minimum Spanning Trees

TOPIC BREAKDOWN:
• What is Minimum Spanning Tree (MST)
• Kruskal's Algorithm - Sort edges, Union-Find approach
• Prim's Algorithm - Grow tree from vertex
• Union-Find (Disjoint Set Union) data structure
• Applications: Network design, clustering, etc.
• Comparing Kruskal's and Prim's efficiency

KEY LEARNING POINTS:
✓ Understanding MST problem and properties
✓ Implementing Kruskal's with Union-Find
✓ Implementing Prim's with priority queue
✓ Building efficient Union-Find structure
✓ Selecting appropriate algorithm for problem

================================================================================
                    PART 1: MINIMUM SPANNING TREE BASICS
================================================================================
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
======================= CONCEPT 1: MINIMUM SPANNING TREE =======================

Minimum Spanning Tree (MST):
- Subset of edges that connects all vertices
- No cycles
- Minimum total weight among all spanning trees

PROPERTIES:
1. Connected graph with V vertices has spanning tree with V-1 edges
2. Every connected graph has at least one spanning tree
3. Weights may not be unique (multiple MSTs possible)
4. MST is acyclic (forest becomes tree when connected)

VISUALIZATIONS:
Complete graph with 4 vertices:
  Input: 6 edges with weights
  MST: 3 edges connecting all 4 vertices with minimum total weight

APPLICATION EXAMPLES:
• Network Design - Connect cities with minimum cable length
• Circuit Board - Connect pins with minimum wire
• Clustering - Group similar items with minimum cost
• Transportation - Build road network with minimum construction cost

PROBLEM VARIANTS:
• Minimum Edge Weight MST (standard)
• Maximum Spanning Tree (reverse weights)
• Bottleneck MST (minimize maximum edge)
• Degree-Constrained MST

KEY FACTS:
- Any connected graph has at least one MST
- Graph may have multiple valid MSTs (same total weight)
- MST is unique if all edge weights are distinct
- Adding any non-tree edge creates exactly one cycle
*/

void concept1_MSTBasics() {
  cout << "\n===== CONCEPT 1: Minimum Spanning Tree Basics =====" << endl;

  cout << "\nExample: Network Design" << endl;
  cout << "Cities to connect: A, B, C, D" << endl;
  cout << "Cable costs (weights):" << endl;
  cout << "  A-B: 4,  A-C: 2,  A-D: 6" << endl;
  cout << "  B-C: 1,  B-D: 5" << endl;
  cout << "  C-D: 3" << endl;
  cout << "\nAll possible spanning trees:" << endl;
  cout << "  {A-B(4), B-C(1), C-D(3)} = 8" << endl;
  cout << "  {A-C(2), B-C(1), B-D(5)} = 8 ← MINIMUM" << endl;
  cout << "  {A-C(2), B-C(1), A-B(4)} = 7 ← MINIMUM" << endl;
  cout << "  ... others with larger weights" << endl;
  cout << "\nMST connects all vertices with minimum total weight" << endl;
}

/*
======================= CONCEPT 2: UNION-FIND (DISJOINT SET UNION)
=======================

Union-Find Data Structure:
- Efficiently handles connectivity queries
- Two main operations:
  1. Find(x): Return representative of set containing x
  2. Union(x,y): Merge sets containing x and y

KEY OPTIMIZATIONS:
1. Union by Rank: Attach smaller tree under larger
2. Path Compression: Flatten tree during Find

Operations with optimizations:
- Time: Nearly O(1) amortized - almost constant!
- More precisely: O(α(n)) where α is inverse Ackermann

USES:
- Cycle detection in graphs (Kruskal's)
- Connected component finding
- Equivalence class computation
- Kruskal's MST algorithm
*/

// ===== EXAMPLE 1: Union-Find Data Structure =====
class UnionFind {
private:
  vector<int> parent;
  vector<int> rank;

public:
  UnionFind(int n) {
    parent.resize(n);
    rank.assign(n, 0);
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }

  // Find with path compression
  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
  }

  // Union by rank
  bool unite(int x, int y) {
    int px = find(x);
    int py = find(y);

    if (px == py)
      return false; // Already in same set

    // Union by rank
    if (rank[px] < rank[py]) {
      parent[px] = py;
    } else if (rank[px] > rank[py]) {
      parent[py] = px;
    } else {
      parent[py] = px;
      rank[px]++;
    }

    return true;
  }

  bool connected(int x, int y) { return find(x) == find(y); }
};

void example1_unionFind() {
  cout << "\n===== EXAMPLE 1: Union-Find Data Structure =====" << endl;

  UnionFind uf(7);

  cout << "Initial components: Each element in its own set" << endl;
  cout << "  {0} {1} {2} {3} {4} {5} {6}" << endl;

  cout << "\nUnite operations:" << endl;

  uf.unite(0, 1);
  cout << "After unite(0,1): {0,1} {2} {3} {4} {5} {6}" << endl;

  uf.unite(2, 3);
  cout << "After unite(2,3): {0,1} {2,3} {4} {5} {6}" << endl;

  uf.unite(1, 2);
  cout << "After unite(1,2): {0,1,2,3} {4} {5} {6}" << endl;

  uf.unite(4, 5);
  cout << "After unite(4,5): {0,1,2,3} {4,5} {6}" << endl;

  cout << "\nConnectivity checks:" << endl;
  cout << "  connected(0,3)? " << (uf.connected(0, 3) ? "YES" : "NO") << endl;
  cout << "  connected(0,4)? " << (uf.connected(0, 4) ? "YES" : "NO") << endl;
  cout << "  connected(4,5)? " << (uf.connected(4, 5) ? "YES" : "NO") << endl;
}

/*
======================= CONCEPT 3: KRUSKAL'S ALGORITHM =======================

Kruskal's Algorithm:
1. Sort all edges by weight (ascending)
2. Initialize empty set of edges
3. For each edge in sorted order:
   - If edge connects two different components:
     * Add edge to MST
     * Union the components
   - Otherwise: Skip (would create cycle)
4. Stop when V-1 edges added

Time: O(E log E) for sorting + O(E α(V)) for Union-Find
     = O(E log E) with typical graphs

Space: O(V) for Union-Find

WHY IT WORKS (Greedy Choice Property):
- Always pick smallest unused edge that doesn't create cycle
- This greedy choice leads to optimal solution
- Proven by matroid theory and exchange argument

BEST FOR:
- Sparse graphs (E << V²)
- When edge weights are given/sorted
- When cycle detection via Union-Find is efficient
*/

struct Edge {
  int u, v, weight;

  bool operator<(const Edge &other) const { return weight < other.weight; }
};

class KruskalMST {
private:
  int numVertices;
  vector<Edge> edges;
  vector<string> vertexLabels;

public:
  KruskalMST(int v) : numVertices(v) {}

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v, int weight) { edges.push_back({u, v, weight}); }

  void kruskal() {
    // Sort edges by weight
    sort(edges.begin(), edges.end());

    UnionFind uf(numVertices);
    vector<Edge> mstEdges;
    int totalWeight = 0;

    cout << "Kruskal's Algorithm - Processing edges in order:" << endl;
    cout << fixed << setprecision(2);

    for (const Edge &e : edges) {
      cout << "  Edge " << vertexLabels[e.u] << "-" << vertexLabels[e.v]
           << " (weight:" << e.weight << "): ";

      if (uf.unite(e.u, e.v)) {
        cout << "ADDED (connects components)" << endl;
        mstEdges.push_back(e);
        totalWeight += e.weight;
      } else {
        cout << "SKIPPED (would create cycle)" << endl;
      }

      if (mstEdges.size() == numVertices - 1)
        break;
    }

    cout << "\nMinimum Spanning Tree:" << endl;
    for (const Edge &e : mstEdges) {
      cout << "  " << vertexLabels[e.u] << "-" << vertexLabels[e.v]
           << " (weight:" << e.weight << ")" << endl;
    }
    cout << "Total weight: " << totalWeight << endl;
  }
};

void example2_kruskalAlgorithm() {
  cout << "\n===== EXAMPLE 2: Kruskal's Algorithm =====" << endl;

  KruskalMST graph(6);
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");
  graph.addVertex("E");
  graph.addVertex("F");

  cout << "Adding edges:" << endl;
  graph.addEdge(0, 1, 4); // A-B: 4
  cout << "  A-B(4)" << endl;
  graph.addEdge(0, 2, 2); // A-C: 2
  cout << "  A-C(2)" << endl;
  graph.addEdge(1, 2, 1); // B-C: 1
  cout << "  B-C(1)" << endl;
  graph.addEdge(1, 3, 5); // B-D: 5
  cout << "  B-D(5)" << endl;
  graph.addEdge(2, 3, 8); // C-D: 8
  cout << "  C-D(8)" << endl;
  graph.addEdge(2, 4, 10); // C-E: 10
  cout << "  C-E(10)" << endl;
  graph.addEdge(3, 5, 2); // D-F: 2
  cout << "  D-F(2)" << endl;
  graph.addEdge(4, 5, 3); // E-F: 3
  cout << "  E-F(3)" << endl;

  graph.kruskal();
}

/*
======================= CONCEPT 4: PRIM'S ALGORITHM =======================

Prim's Algorithm:
1. Start from arbitrary vertex (usually 0)
2. Mark starting vertex as in MST
3. While not all vertices in MST:
   - Find minimum weight edge from MST to outside
   - Add vertex and edge to MST
   - Update distances to new vertex

Time: O(E log V) with binary heap
      O(V²) with simple array
      O(E + V log V) with Fibonacci heap

Space: O(V) for visited and distance arrays

WHY IT WORKS:
- Grows MST from starting vertex
- Always picks minimum edge connecting MST to new vertex
- Greedy choice leads to optimal solution

COMPARISON WITH KRUSKAL'S:
- Kruskal: Good for sparse graphs
- Prim: Good for dense graphs
- Both produce optimal MST (may differ in selection order)
*/

// ===== EXAMPLE 3: Prim's Algorithm =====
class PrimMST {
private:
  int numVertices;
  vector<vector<pair<int, int>>> adj; // {neighbor, weight}
  vector<string> vertexLabels;

public:
  PrimMST(int v) : numVertices(v) { adj.resize(v); }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v, int weight) {
    adj[u].push_back({v, weight});
    adj[v].push_back({u, weight});
  }

  void prim(int start) {
    vector<bool> inMST(numVertices, false);
    vector<int> key(numVertices, INT_MAX);
    vector<int> parent(numVertices, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;

    key[start] = 0;
    pq.push({0, start});

    int totalWeight = 0;
    cout << "Prim's Algorithm - Building MST:" << endl;

    while (!pq.empty()) {
      auto [weight, u] = pq.top();
      pq.pop();

      if (inMST[u])
        continue;

      inMST[u] = true;

      if (parent[u] != -1) {
        cout << "  Added edge: " << vertexLabels[parent[u]] << "-"
             << vertexLabels[u] << " (weight:" << weight << ")" << endl;
        totalWeight += weight;
      }

      for (auto [v, w] : adj[u]) {
        if (!inMST[v] && w < key[v]) {
          key[v] = w;
          parent[v] = u;
          pq.push({w, v});
        }
      }
    }

    cout << "Total weight: " << totalWeight << endl;
  }
};

void example3_primAlgorithm() {
  cout << "\n===== EXAMPLE 3: Prim's Algorithm =====" << endl;

  PrimMST graph(6);
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");
  graph.addVertex("E");
  graph.addVertex("F");

  cout << "Same graph as Kruskal example" << endl;
  graph.addEdge(0, 1, 4);  // A-B: 4
  graph.addEdge(0, 2, 2);  // A-C: 2
  graph.addEdge(1, 2, 1);  // B-C: 1
  graph.addEdge(1, 3, 5);  // B-D: 5
  graph.addEdge(2, 3, 8);  // C-D: 8
  graph.addEdge(2, 4, 10); // C-E: 10
  graph.addEdge(3, 5, 2);  // D-F: 2
  graph.addEdge(4, 5, 3);  // E-F: 3

  graph.prim(0); // Start from A
}

/*
======================= CONCEPT 5: CYCLE DETECTION WITH UNION-FIND
=======================

Cycle Detection in Undirected Graphs:
- Use Union-Find to detect if edge creates cycle
- If both vertices already in same component: cycle exists
- Otherwise: unite components

For directed graphs:
- Use DFS with color marking (as shown in traversals)
- Union-Find doesn't work directly for directed graphs
*/

// ===== EXAMPLE 4: Cycle Detection =====
class CycleDetectorUnionFind {
private:
  int numVertices;
  vector<pair<int, int>> edges;
  vector<string> vertexLabels;

public:
  CycleDetectorUnionFind(int v) : numVertices(v) {}

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v) { edges.push_back({u, v}); }

  bool hasCycle() {
    UnionFind uf(numVertices);

    cout << "Checking for cycles:" << endl;
    for (auto [u, v] : edges) {
      cout << "  Edge " << vertexLabels[u] << "-" << vertexLabels[v] << ": ";

      if (uf.find(u) == uf.find(v)) {
        cout << "CYCLE DETECTED!" << endl;
        return true;
      } else {
        cout << "No cycle yet" << endl;
        uf.unite(u, v);
      }
    }

    return false;
  }
};

void example4_cycleDetection() {
  cout << "\n===== EXAMPLE 4: Cycle Detection with Union-Find =====" << endl;

  cout << "Example 1: No Cycle" << endl;
  CycleDetectorUnionFind graph1(4);
  graph1.addVertex("A");
  graph1.addVertex("B");
  graph1.addVertex("C");
  graph1.addVertex("D");

  graph1.addEdge(0, 1);
  graph1.addEdge(1, 2);
  graph1.addEdge(2, 3);

  cout << "Edges: A-B, B-C, C-D" << endl;
  bool cycle1 = graph1.hasCycle();
  cout << "Result: " << (cycle1 ? "HAS CYCLE" : "NO CYCLE") << endl;

  cout << "\nExample 2: With Cycle" << endl;
  CycleDetectorUnionFind graph2(3);
  graph2.addVertex("X");
  graph2.addVertex("Y");
  graph2.addVertex("Z");

  graph2.addEdge(0, 1);
  graph2.addEdge(1, 2);
  graph2.addEdge(2, 0);

  cout << "Edges: X-Y, Y-Z, Z-X" << endl;
  bool cycle2 = graph2.hasCycle();
  cout << "Result: " << (cycle2 ? "HAS CYCLE" : "NO CYCLE") << endl;
}

/*
================================================================================
                        KEY CONCEPTS SUMMARY
================================================================================

1. MINIMUM SPANNING TREE:
   ✓ Connects all vertices with minimum total weight
   ✓ Contains exactly V-1 edges for V vertices
   ✓ Acyclic (tree structure)
   ✓ Multiple MSTs possible (same total weight)

2. UNION-FIND DATA STRUCTURE:
   ✓ Efficient connectivity queries
   ✓ Path compression: O(α(n)) ≈ O(1) per operation
   ✓ Union by rank: Keeps tree shallow
   ✓ Find: Returns representative element
   ✓ Union: Merges two sets

3. KRUSKAL'S ALGORITHM:
   ✓ Time: O(E log E) for sorting
   ✓ Sort edges by weight, greedily add non-cyclic edges
   ✓ Uses Union-Find for cycle detection
   ✓ Best for: Sparse graphs

4. PRIM'S ALGORITHM:
   ✓ Time: O((V+E) log V) with binary heap
   ✓ Grow MST from single vertex
   ✓ Track minimum edge from MST to outside
   ✓ Best for: Dense graphs

5. COMPARISON:
   ┌──────────────┬──────────────┬─────────────────┐
   │ Aspect       │ Kruskal's    │ Prim's          │
   ├──────────────┼──────────────┼─────────────────┤
   │ Time         │ E log E      │ (V+E) log V     │
   │ Space        │ V (UF)       │ V               │
   │ Good for     │ Sparse       │ Dense           │
   │ Approach     │ Edge-based   │ Vertex-based    │
   │ Data Struct  │ Union-Find   │ Priority Queue  │
   └──────────────┴──────────────┴─────────────────┘

================================================================================
                        COMMON MISTAKES TO AVOID
================================================================================

❌ MISTAKE 1: Not using path compression in Union-Find
✓ CORRECT: Apply path compression for O(α(n)) operations

❌ MISTAKE 2: Forgetting union by rank optimization
✓ CORRECT: Use both path compression AND union by rank

❌ MISTAKE 3: Adding edge before checking if it creates cycle
✓ CORRECT: Check with Union-Find before adding to MST

❌ MISTAKE 4: Kruskal without sorting edges first
✓ CORRECT: Always sort edges by weight before processing

❌ MISTAKE 5: Not initializing Union-Find properly
✓ CORRECT: Each vertex starts as its own representative

================================================================================
                        PRACTICE EXERCISES
================================================================================

Exercise 1: Implement Union-Find with all optimizations

Exercise 2: Compare Kruskal's and Prim's results (should match)

Exercise 3: Find MST for different starting vertices (Prim)

Exercise 4: Detect all cycles using Union-Find

Exercise 5: Find MST for dense vs sparse graphs

Exercise 6: Implement Prim's with simple array (O(V²))

Exercise 7: Build network topology with MST

Exercise 8: Find second MST (different edge selection)

Exercise 9: Handle disconnected graph components

Exercise 10: Modify weights and observe MST changes

================================================================================
*/

// ===== MAIN FUNCTION =====
int main() {
  cout << "\n" << string(80, '=') << endl;
  cout << "    25.3.5: MINIMUM SPANNING TREE ALGORITHMS - LEARNING GUIDE"
       << endl;
  cout << string(80, '=') << endl;

  try {
    concept1_MSTBasics();
    example1_unionFind();
    example2_kruskalAlgorithm();
    example3_primAlgorithm();
    example4_cycleDetection();

    cout << "\n" << string(80, '=') << endl;
    cout << "All examples completed successfully!" << endl;
    cout << string(80, '=') << endl;
  } catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
  }

  return 0;
}
