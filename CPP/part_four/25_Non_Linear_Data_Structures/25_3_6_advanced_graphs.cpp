/*
================================================================================
           25.3.6: ADVANCED GRAPH ALGORITHMS (SCC, FLOW, MATCHING)
================================================================================
Comprehensive Learning Guide on Advanced Graph Algorithms

TOPIC BREAKDOWN:
• Strongly Connected Components (SCC) - Kosaraju and Tarjan's algorithms
• Bipartite Graph Detection and Applications
• Network Flow - Ford-Fulkerson and Maximum Flow
• Bipartite Matching - Hungarian Algorithm basics
• Applications: Social networks, flow networks, job assignments

KEY LEARNING POINTS:
✓ Understanding strongly connected components in directed graphs
✓ Implementing Kosaraju's and Tarjan's algorithms
✓ Detecting bipartite graphs and applications
✓ Computing maximum flow in flow networks
✓ Solving matching problems

================================================================================
            PART 1: STRONGLY CONNECTED COMPONENTS (SCC)
================================================================================
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>
using namespace std;

/*
======================= CONCEPT 1: STRONGLY CONNECTED COMPONENTS
=======================

Strongly Connected Component (SCC):
- Maximal subset of vertices where every vertex reachable from any other
- Only meaningful in DIRECTED graphs
- In undirected graphs, all vertices are part of connected components

EXAMPLE:
Graph: 1→2→3→1 (cycle), 2→5
  SCC1: {1, 2, 3} (all reachable from each other)
  SCC2: {5} (isolated)
  SCC3: {4} (if exists, isolated)

APPLICATIONS:
- Social networks: Find groups of mutual friends
- Web structure: Find web communities
- Compiler: Find loops in call graphs
- Strongly connected components

KEY PROPERTIES:
1. Every vertex belongs to exactly one SCC
2. SCCs form a DAG (Directed Acyclic Graph)
3. Can contract SCCs to single "super-node"

ALGORITHMS:
1. Kosaraju's Algorithm: O(V + E), intuitive
2. Tarjan's Algorithm: O(V + E), single DFS pass
*/

void concept1_SCCBasics() {
  cout << "\n===== CONCEPT 1: Strongly Connected Components =====" << endl;

  cout << "Example: Web Structure with Mutual References" << endl;
  cout << "Sites: A, B, C, D, E" << endl;
  cout << "Links: A→B, B→C, C→A (form cycle)" << endl;
  cout << "       B→D, D→E (no return path)" << endl;
  cout << "\nStrongly Connected Components:" << endl;
  cout << "  SCC1: {A, B, C} - All mutually reachable" << endl;
  cout << "  SCC2: {D} - Can reach E but not reachable" << endl;
  cout << "  SCC3: {E} - No outgoing edges" << endl;
}

/*
======================= CONCEPT 2: KOSARAJU'S ALGORITHM =======================

Kosaraju's Algorithm (Three-step process):

Step 1: Do DFS on original graph, push vertices to stack in post-order
        (after processing all descendants)

Step 2: Create transpose (reverse) of graph
        (reverse all edge directions)

Step 3: Do DFS on transpose in order of decreasing post-time
        (pop from stack, DFS in transpose)
        Each DFS tree is one SCC

WHY IT WORKS:
- First DFS establishes finishing times
- Vertices with high finishing time → "root" of SCC in transpose
- DFS in transpose stays within SCC (edges reversed)

TIME: O(V + E)
SPACE: O(V)

INTUITION:
- If vertices u,v mutually reachable: finish-time(u) in same subtree of DFS
forest on transpose
- DFS in reverse finish order ensures SCC cohesion
*/

// ===== EXAMPLE 1: Kosaraju's Algorithm =====
class KosarajuSCC {
private:
  int numVertices;
  vector<vector<int>> adj, transpose;
  vector<string> vertexLabels;
  vector<bool> visited;
  stack<int> st;
  vector<int> component;

  void dfs1(int v) {
    visited[v] = true;
    for (int u : adj[v]) {
      if (!visited[u]) {
        dfs1(u);
      }
    }
    st.push(v); // Push after visiting all descendants (post-order)
  }

  void dfs2(int v) {
    visited[v] = true;
    component.push_back(v);
    for (int u : transpose[v]) {
      if (!visited[u]) {
        dfs2(u);
      }
    }
  }

public:
  KosarajuSCC(int v) : numVertices(v) {
    adj.resize(v);
    transpose.resize(v);
  }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    transpose[v].push_back(u); // Build transpose simultaneously
  }

  void findSCC() {
    visited.assign(numVertices, false);

    // Step 1: DFS and push to stack
    cout << "Step 1: First DFS (record finish times)" << endl;
    for (int i = 0; i < numVertices; i++) {
      if (!visited[i]) {
        dfs1(i);
      }
    }

    // Step 2: DFS on transpose in reverse finish order
    visited.assign(numVertices, false);
    cout << "\nStep 2: Second DFS on transpose (find SCCs)" << endl;

    int sccNum = 1;
    while (!st.empty()) {
      int v = st.top();
      st.pop();

      if (!visited[v]) {
        component.clear();
        dfs2(v);

        cout << "SCC " << sccNum << ": ";
        for (int u : component) {
          cout << vertexLabels[u] << " ";
        }
        cout << endl;
        sccNum++;
      }
    }
  }
};

void example1_kosaraju() {
  cout << "\n===== EXAMPLE 1: Kosaraju's Algorithm =====" << endl;

  KosarajuSCC graph(7);
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");
  graph.addVertex("E");
  graph.addVertex("F");
  graph.addVertex("G");

  cout << "Adding directed edges:" << endl;
  cout << "  A→B, B→C, C→A (cycle), B→D, D→E, E→F, F→D (cycle), F→G" << endl;
  graph.addEdge(0, 1); // A→B
  graph.addEdge(1, 2); // B→C
  graph.addEdge(2, 0); // C→A
  graph.addEdge(1, 3); // B→D
  graph.addEdge(3, 4); // D→E
  graph.addEdge(4, 5); // E→F
  graph.addEdge(5, 3); // F→D
  graph.addEdge(5, 6); // F→G

  graph.findSCC();
}

/*
======================= CONCEPT 3: TARJAN'S ALGORITHM =======================

Tarjan's Algorithm (Single DFS pass):

Key Ideas:
- Maintain "low" value for each vertex
- low[v] = minimum of:
  1. discovery[v] (when v first visited)
  2. discovery[w] for all back edges v→w
  3. low[u] for all tree edges v→u

SCC Property:
- Vertices form SCC if they have same low value
- When low[v] == discovery[v], v is SCC root

Algorithm:
1. DFS traversal maintaining discovery time and low values
2. Use stack to track SCC members
3. When SCC root found (low[v] == discovery[v]):
   - Pop all vertices from stack up to v
   - Form SCC

TIME: O(V + E) in single pass
SPACE: O(V)

ADVANTAGES OVER KOSARAJU:
- Single DFS pass (more cache efficient)
- No need to build transpose
- Better for online computation
*/

// ===== EXAMPLE 2: Tarjan's Algorithm (Concept) =====
void example2_tarjanConcept() {
  cout << "\n===== EXAMPLE 2: Tarjan's Algorithm (Concept) =====" << endl;

  cout << "Similar to Kosaraju but optimized:" << endl;
  cout << "\nKey Differences:" << endl;
  cout << "1. Kosaraju:" << endl;
  cout << "   - Two full DFS passes (original + transpose)" << endl;
  cout << "   - Transpose graph needed" << endl;
  cout << "   - Easier to understand" << endl;

  cout << "\n2. Tarjan:" << endl;
  cout << "   - Single DFS pass" << endl;
  cout << "   - No transpose needed" << endl;
  cout << "   - More memory efficient" << endl;
  cout << "   - Uses low-link values" << endl;

  cout << "\nBoth produce same SCCs" << endl;
}

/*
======================= CONCEPT 4: BIPARTITE GRAPH DETECTION
=======================

Bipartite Graph:
- Vertices can be divided into two disjoint sets
- Every edge connects vertex from one set to other
- No edges within same set

CHARACTERIZATION:
A graph is bipartite if and only if it contains NO ODD CYCLES

DETECTION METHOD (BFS/DFS):
- Try to color graph with 2 colors
- Start from any vertex, color it 0
- Color all neighbors with opposite color
- If conflict (vertex needs same color as neighbor): NOT bipartite
- If all colored successfully: bipartite

Time: O(V + E)
Space: O(V)

APPLICATIONS:
- Job-person matching (bipartite matching)
- Checking planarity (related)
- Circuit design (2-coloring)
- Social networks (identifying groups)

EXAMPLES:
- Complete bipartite graph K(m,n)
- Tree (always bipartite)
- Cycle of even length (bipartite)
- Cycle of odd length (NOT bipartite)
*/

// ===== EXAMPLE 3: Bipartite Detection =====
class BipartiteDetector {
private:
  int numVertices;
  vector<vector<int>> adj;
  vector<string> vertexLabels;
  vector<int> color; // -1: unvisited, 0/1: color

public:
  BipartiteDetector(int v) : numVertices(v) {
    adj.resize(v);
    color.assign(v, -1);
  }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  bool isBipartite() {
    for (int start = 0; start < numVertices; start++) {
      if (color[start] == -1) {
        if (!bfs(start)) {
          return false;
        }
      }
    }
    return true;
  }

private:
  bool bfs(int start) {
    queue<int> q;
    q.push(start);
    color[start] = 0;

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (int v : adj[u]) {
        if (color[v] == -1) {
          color[v] = 1 - color[u]; // Opposite color
          q.push(v);
        } else if (color[v] == color[u]) {
          return false; // Same color = conflict
        }
      }
    }
    return true;
  }

public:
  void printBipartition() {
    cout << "\nBipartite Sets:" << endl;
    cout << "Set 1 (Color 0): ";
    for (int i = 0; i < numVertices; i++) {
      if (color[i] == 0)
        cout << vertexLabels[i] << " ";
    }
    cout << endl;

    cout << "Set 2 (Color 1): ";
    for (int i = 0; i < numVertices; i++) {
      if (color[i] == 1)
        cout << vertexLabels[i] << " ";
    }
    cout << endl;
  }
};

void example3_bipartiteDetection() {
  cout << "\n===== EXAMPLE 3: Bipartite Graph Detection =====" << endl;

  cout << "Example 1: Bipartite (Job-Person Matching)" << endl;
  BipartiteDetector graph1(6);
  graph1.addVertex("Job1");
  graph1.addVertex("Job2");
  graph1.addVertex("Job3");
  graph1.addVertex("Person1");
  graph1.addVertex("Person2");
  graph1.addVertex("Person3");

  cout << "Edges (Job-Person can do):" << endl;
  cout << "  Job1-Person1, Job1-Person2" << endl;
  cout << "  Job2-Person2, Job2-Person3" << endl;
  cout << "  Job3-Person1, Job3-Person3" << endl;

  graph1.addEdge(0, 3); // Job1-Person1
  graph1.addEdge(0, 4); // Job1-Person2
  graph1.addEdge(1, 4); // Job2-Person2
  graph1.addEdge(1, 5); // Job2-Person3
  graph1.addEdge(2, 3); // Job3-Person1
  graph1.addEdge(2, 5); // Job3-Person3

  bool isBi1 = graph1.isBipartite();
  cout << "Is bipartite: " << (isBi1 ? "YES" : "NO") << endl;
  if (isBi1)
    graph1.printBipartition();

  cout << "\nExample 2: Not Bipartite (Triangle)" << endl;
  BipartiteDetector graph2(3);
  graph2.addVertex("A");
  graph2.addVertex("B");
  graph2.addVertex("C");

  cout << "Edges: A-B, B-C, C-A (triangle - odd cycle)" << endl;
  graph2.addEdge(0, 1);
  graph2.addEdge(1, 2);
  graph2.addEdge(2, 0);

  bool isBi2 = graph2.isBipartite();
  cout << "Is bipartite: " << (isBi2 ? "YES" : "NO") << endl;
}

/*
======================= CONCEPT 5: BASIC MAXIMUM FLOW =======================

Network Flow Problem:
- Directed graph with capacities on edges
- Source (s) and sink (t)
- Find maximum flow from s to t without exceeding edge capacities

FLOW PROPERTIES:
1. Capacity constraint: flow[u,v] ≤ capacity[u,v]
2. Skew symmetry: flow[u,v] = -flow[v,u]
3. Flow conservation: sum of flow out = sum of flow in (except source/sink)

FORD-FULKERSON ALGORITHM:
While augmenting path from s to t exists:
  1. Find any path from s to t in residual graph
  2. Find minimum capacity (bottleneck) on path
  3. Add bottleneck to total flow
  4. Update residual graph

Time: O(E * max_flow) with simple path finding
      O(VE²) with BFS (Edmonds-Karp)

APPLICATIONS:
- Network routing (maximum data flow)
- Airline scheduling (max passengers)
- Bipartite matching (max matching = max flow)
- Project selection (min-cut)
*/

// ===== EXAMPLE 4: Maximum Flow (Simplified) =====
class MaximumFlow {
private:
  int numVertices;
  vector<vector<int>> capacity;
  vector<string> vertexLabels;

  int bfsPath(int source, int sink, vector<int> &parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[source] = -2;
    queue<pair<int, int>> q;
    q.push({source, INT_MAX});

    while (!q.empty()) {
      int u = q.front().first;
      int flow = q.front().second;
      q.pop();

      for (int v = 0; v < numVertices; v++) {
        if (parent[v] == -1 && capacity[u][v] > 0) {
          parent[v] = u;
          int newFlow = min(flow, capacity[u][v]);

          if (v == sink)
            return newFlow;
          q.push({v, newFlow});
        }
      }
    }
    return 0;
  }

public:
  MaximumFlow(int v) : numVertices(v) { capacity.assign(v, vector<int>(v, 0)); }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v, int cap) { capacity[u][v] += cap; }

  int fordFulkerson(int source, int sink) {
    int maxFlow = 0;
    vector<int> parent(numVertices);
    int pathFlow;

    cout << "Finding augmenting paths:" << endl;
    int pathNum = 1;

    while ((pathFlow = bfsPath(source, sink, parent)) > 0) {
      cout << "  Path " << pathNum << " (flow=" << pathFlow << "): ";

      int v = sink;
      while (v != source) {
        int u = parent[v];
        capacity[u][v] -= pathFlow;
        capacity[v][u] += pathFlow;
        cout << vertexLabels[u] << "→";
        v = u;
      }
      cout << vertexLabels[sink] << endl;

      maxFlow += pathFlow;
      pathNum++;
    }

    return maxFlow;
  }
};

void example4_maxFlow() {
  cout << "\n===== EXAMPLE 4: Maximum Flow (Ford-Fulkerson) =====" << endl;

  MaximumFlow graph(4);
  graph.addVertex("Source");
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("Sink");

  cout << "Graph with capacities:" << endl;
  cout << "  Source→A: 10,  Source→B: 10" << endl;
  cout << "  A→Sink: 4,     B→Sink: 8,   A→B: 2" << endl;

  graph.addEdge(0, 1, 10); // Source→A: 10
  graph.addEdge(0, 2, 10); // Source→B: 10
  graph.addEdge(1, 3, 4);  // A→Sink: 4
  graph.addEdge(2, 3, 8);  // B→Sink: 8
  graph.addEdge(1, 2, 2);  // A→B: 2

  int maxFlow = graph.fordFulkerson(0, 3);
  cout << "\nMaximum Flow: " << maxFlow << endl;
}

/*
================================================================================
                        KEY CONCEPTS SUMMARY
================================================================================

1. STRONGLY CONNECTED COMPONENTS:
   ✓ Maximal set of vertices mutually reachable
   ✓ Kosaraju: 2 DFS passes, O(V+E), intuitive
   ✓ Tarjan: 1 DFS pass, O(V+E), efficient
   ✓ SCCs form DAG structure

2. BIPARTITE GRAPHS:
   ✓ 2-colorable graphs (no odd cycles)
   ✓ Detection via BFS/DFS coloring
   ✓ Applications: matching, 2-coloring
   ✓ Time: O(V+E)

3. MAXIMUM FLOW:
   ✓ Ford-Fulkerson: Find augmenting paths
   ✓ Capacity constraints maintained
   ✓ Applications: routing, matching
   ✓ Time: O(E * maxflow) varies with path finding

4. FLOW PROPERTIES:
   ✓ Capacity constraint: flow ≤ capacity
   ✓ Flow conservation: in-flow = out-flow
   ✓ Augmenting path: path with unused capacity
   ✓ Residual graph: updated after each path

5. APPLICATIONS SUMMARY:
   ✓ SCC: Social networks, compiler analysis
   ✓ Bipartite: Job matching, 2-coloring
   ✓ Flow: Network routing, capacity planning
   ✓ Matching: Assignment, pairing problems

================================================================================
                        COMMON MISTAKES TO AVOID
================================================================================

❌ MISTAKE 1: Applying SCC to undirected graphs
✓ CORRECT: SCC only meaningful for directed graphs

❌ MISTAKE 2: Not checking for odd cycles in bipartite detection
✓ CORRECT: Graph is bipartite iff no odd cycles

❌ MISTAKE 3: Confusing residual graph updates
✓ CORRECT: Add reverse edges with capacity

❌ MISTAKE 4: Not maintaining flow conservation
✓ CORRECT: Sum of in-flow = sum of out-flow

❌ MISTAKE 5: Forgetting source/sink vertices
✓ CORRECT: Source has no in-flow, sink has no out-flow

================================================================================
                        PRACTICE EXERCISES
================================================================================

Exercise 1: Find SCCs using both Kosaraju and Tarjan

Exercise 2: Detect bipartite and find 2-coloring

Exercise 3: Implement maximum flow algorithm

Exercise 4: Find SCC condensation (contract to DAG)

Exercise 5: Verify bipartite matching viability

Exercise 6: Compute min-cut from max-flow

Exercise 7: Handle disconnected SCCs

Exercise 8: Find articulation points and bridges

Exercise 9: Implement push-relabel max flow

Exercise 10: Build social network analysis (SCC + analysis)

================================================================================
*/

// ===== MAIN FUNCTION =====
int main() {
  cout << "\n" << string(80, '=') << endl;
  cout << "   25.3.6: ADVANCED GRAPH ALGORITHMS - LEARNING GUIDE" << endl;
  cout << string(80, '=') << endl;

  try {
    concept1_SCCBasics();
    example1_kosaraju();
    example2_tarjanConcept();
    example3_bipartiteDetection();
    example4_maxFlow();

    cout << "\n" << string(80, '=') << endl;
    cout << "All examples completed successfully!" << endl;
    cout << string(80, '=') << endl;
  } catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
  }

  return 0;
}
