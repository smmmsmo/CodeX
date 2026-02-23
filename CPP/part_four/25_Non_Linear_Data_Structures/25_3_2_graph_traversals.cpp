/*
================================================================================
                   25.3.2: GRAPH TRAVERSALS (BFS & DFS)
================================================================================
Comprehensive Learning Guide on Graph Traversal Algorithms

TOPIC BREAKDOWN:
• Breadth-First Search (BFS) - Level-order traversal
• Depth-First Search (DFS) - Recursive and iterative
• Graph coloring and vertex labeling
• Finding connected components
• Cycle detection in undirected and directed graphs
• Applications: Shortest path, bipartiteness checking, etc.

KEY LEARNING POINTS:
✓ Understanding BFS vs DFS tradeoffs
✓ Implementing both iterative and recursive traversals
✓ Detecting cycles in graphs
✓ Finding connected components
✓ Detecting bipartite graphs

================================================================================
                    PART 1: BREADTH-FIRST SEARCH (BFS)
================================================================================
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
======================= CONCEPT 1: BFS (Breadth-First Search)
=======================

BFS explores graph level by level:
1. Start at source vertex
2. Visit all neighbors (distance 1)
3. Then visit all neighbors of neighbors (distance 2)
4. Continue until all reachable vertices visited

Algorithm:
1. Create queue and mark source as visited
2. While queue not empty:
   a. Dequeue front vertex
   b. Process vertex
   c. For each unvisited neighbor:
      - Mark as visited
      - Enqueue it

Time: O(V + E)
Space: O(V) for queue and visited set

PROPERTIES:
- Finds shortest path in unweighted graphs
- Explores vertices by distance
- Suitable for level-order operations
- Requires queue (FIFO)
*/

// ===== EXAMPLE 1: Basic BFS =====
class BFSTraversal {
private:
  int numVertices;
  vector<vector<int>> adj;
  vector<string> vertexLabels;

public:
  BFSTraversal(int v) : numVertices(v) { adj.resize(v); }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> bfs(int start) {
    vector<bool> visited(numVertices, false);
    vector<int> result;
    queue<int> q;

    // Start traversal
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
      int vertex = q.front();
      q.pop();
      result.push_back(vertex);

      // Visit all neighbors
      for (int neighbor : adj[vertex]) {
        if (!visited[neighbor]) {
          visited[neighbor] = true;
          q.push(neighbor);
        }
      }
    }

    return result;
  }

  void printBFS(int start) {
    cout << "BFS starting from " << vertexLabels[start] << ": ";
    vector<int> traversal = bfs(start);
    for (int v : traversal) {
      cout << vertexLabels[v] << " ";
    }
    cout << endl;
  }
};

void example1_basicBFS() {
  cout << "\n===== EXAMPLE 1: Basic BFS =====" << endl;

  BFSTraversal graph(7);
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");
  graph.addVertex("E");
  graph.addVertex("F");
  graph.addVertex("G");

  graph.addEdge(0, 1); // A-B
  graph.addEdge(0, 2); // A-C
  graph.addEdge(1, 3); // B-D
  graph.addEdge(1, 4); // B-E
  graph.addEdge(2, 5); // C-F
  graph.addEdge(3, 6); // D-G

  cout << "Graph structure:" << endl;
  cout << "      A" << endl;
  cout << "     / \\" << endl;
  cout << "    B   C" << endl;
  cout << "   / \\ / \\" << endl;
  cout << "  D   E   F" << endl;
  cout << " /" << endl;
  cout << "G" << endl;

  graph.printBFS(0); // Start from A
}

/*
======================= CONCEPT 2: BFS - DISTANCE & PATHS
=======================

BFS can compute:
1. Distance from source to all vertices
2. Shortest path in unweighted graphs
3. Level of each vertex (distance from source)

Modifications to basic BFS:
- Track distance to each vertex
- Track parent of each vertex for path reconstruction
*/

// ===== EXAMPLE 2: BFS with Distances and Path Reconstruction =====
class BFSPathFinder {
private:
  int numVertices;
  vector<vector<int>> adj;
  vector<string> vertexLabels;

public:
  BFSPathFinder(int v) : numVertices(v) { adj.resize(v); }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  pair<vector<int>, vector<int>> bfsDistances(int start) {
    vector<int> distances(numVertices, -1);
    vector<int> parent(numVertices, -1);
    queue<int> q;

    distances[start] = 0;
    q.push(start);

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (int v : adj[u]) {
        if (distances[v] == -1) {
          distances[v] = distances[u] + 1;
          parent[v] = u;
          q.push(v);
        }
      }
    }

    return {distances, parent};
  }

  vector<int> getPath(int start, int end, vector<int> &parent) {
    vector<int> path;
    int current = end;

    while (current != -1) {
      path.push_back(current);
      current = parent[current];
    }

    reverse(path.begin(), path.end());
    return path;
  }
};

void example2_bfsWithDistances() {
  cout << "\n===== EXAMPLE 2: BFS with Distances and Path Reconstruction ====="
       << endl;

  BFSPathFinder graph(6);
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");
  graph.addVertex("E");
  graph.addVertex("F");

  graph.addEdge(0, 1); // A-B
  graph.addEdge(0, 2); // A-C
  graph.addEdge(1, 3); // B-D
  graph.addEdge(2, 3); // C-D
  graph.addEdge(3, 4); // D-E
  graph.addEdge(4, 5); // E-F

  auto [distances, parent] = graph.bfsDistances(0);

  cout << "Distances from A:" << endl;
  for (int i = 0; i < 6; i++) {
    cout << "  A to " << (char)('A' + i) << ": " << distances[i] << endl;
  }

  cout << "\nShortest path from A to F:" << endl;
  vector<int> path = graph.getPath(0, 5, parent);
  for (int i = 0; i < path.size(); i++) {
    cout << (char)('A' + path[i]);
    if (i < path.size() - 1)
      cout << " → ";
  }
  cout << " (length: " << path.size() - 1 << ")" << endl;
}

/*
======================= CONCEPT 3: DFS (Depth-First Search)
=======================

DFS explores graph by going as deep as possible before backtracking:
1. Start at source vertex
2. Visit first neighbor and recurse
3. Backtrack when dead end reached
4. Continue with other neighbors

Algorithm (Recursive):
1. Mark vertex as visited
2. Process vertex
3. For each unvisited neighbor:
   a. Recursively call DFS on neighbor

Time: O(V + E)
Space: O(V) for recursion stack and visited set

PROPERTIES:
- Explores vertices by depth
- Requires stack (implicit in recursion or explicit)
- Used for cycle detection, topological sort
- Can be both recursive and iterative
*/

// ===== EXAMPLE 3: DFS - Recursive =====
class DFSRecursive {
private:
  int numVertices;
  vector<vector<int>> adj;
  vector<string> vertexLabels;
  vector<bool> visited;
  vector<int> result;

  void dfsHelper(int v) {
    visited[v] = true;
    result.push_back(v);

    for (int neighbor : adj[v]) {
      if (!visited[neighbor]) {
        dfsHelper(neighbor);
      }
    }
  }

public:
  DFSRecursive(int v) : numVertices(v) { adj.resize(v); }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> dfs(int start) {
    visited.assign(numVertices, false);
    result.clear();
    dfsHelper(start);
    return result;
  }

  void printDFS(int start) {
    cout << "DFS (recursive) starting from " << vertexLabels[start] << ": ";
    vector<int> traversal = dfs(start);
    for (int v : traversal) {
      cout << vertexLabels[v] << " ";
    }
    cout << endl;
  }
};

void example3_dfsRecursive() {
  cout << "\n===== EXAMPLE 3: DFS (Recursive) =====" << endl;

  DFSRecursive graph(7);
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");
  graph.addVertex("E");
  graph.addVertex("F");
  graph.addVertex("G");

  graph.addEdge(0, 1); // A-B
  graph.addEdge(0, 2); // A-C
  graph.addEdge(1, 3); // B-D
  graph.addEdge(1, 4); // B-E
  graph.addEdge(2, 5); // C-F
  graph.addEdge(3, 6); // D-G

  graph.printDFS(0);
}

/*
======================= CONCEPT 4: DFS - Iterative =====

DFS using explicit stack instead of recursion:
1. Create stack and mark source as visited
2. While stack not empty:
   a. Pop vertex
   b. Process vertex
   c. For each unvisited neighbor:
      - Mark as visited
      - Push to stack

Same time/space as recursive but explicit control
*/

// ===== EXAMPLE 4: DFS - Iterative =====
class DFSIterative {
private:
  int numVertices;
  vector<vector<int>> adj;
  vector<string> vertexLabels;

public:
  DFSIterative(int v) : numVertices(v) { adj.resize(v); }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> dfs(int start) {
    vector<bool> visited(numVertices, false);
    vector<int> result;
    stack<int> st;

    st.push(start);
    visited[start] = true;

    while (!st.empty()) {
      int vertex = st.top();
      st.pop();
      result.push_back(vertex);

      for (int neighbor : adj[vertex]) {
        if (!visited[neighbor]) {
          visited[neighbor] = true;
          st.push(neighbor);
        }
      }
    }

    return result;
  }

  void printDFS(int start) {
    cout << "DFS (iterative) starting from " << vertexLabels[start] << ": ";
    vector<int> traversal = dfs(start);
    for (int v : traversal) {
      cout << vertexLabels[v] << " ";
    }
    cout << endl;
  }
};

void example4_dfsIterative() {
  cout << "\n===== EXAMPLE 4: DFS (Iterative) =====" << endl;

  DFSIterative graph(7);
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");
  graph.addVertex("E");
  graph.addVertex("F");
  graph.addVertex("G");

  graph.addEdge(0, 1);
  graph.addEdge(0, 2);
  graph.addEdge(1, 3);
  graph.addEdge(1, 4);
  graph.addEdge(2, 5);
  graph.addEdge(3, 6);

  graph.printDFS(0);
}

/*
======================= CONCEPT 5: CYCLE DETECTION =======================

UNDIRECTED GRAPH CYCLE DETECTION:
- If we visit a neighbor that's already visited AND not the parent, cycle exists
- Modified DFS: track parent of each vertex

DIRECTED GRAPH CYCLE DETECTION:
- Use color coding: WHITE (unvisited), GRAY (visiting), BLACK (visited)
- If we encounter GRAY vertex during DFS, cycle exists
*/

// ===== EXAMPLE 5: Cycle Detection (Undirected) =====
class CycleDetector {
private:
  int numVertices;
  vector<vector<int>> adj;
  vector<string> vertexLabels;

  bool hasCycleDFS(int v, int parent, vector<bool> &visited) {
    visited[v] = true;

    for (int neighbor : adj[v]) {
      if (!visited[neighbor]) {
        if (hasCycleDFS(neighbor, v, visited)) {
          return true;
        }
      } else if (neighbor != parent) {
        return true;
      }
    }

    return false;
  }

public:
  CycleDetector(int v) : numVertices(v) { adj.resize(v); }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  bool hasCycle() {
    vector<bool> visited(numVertices, false);

    for (int i = 0; i < numVertices; i++) {
      if (!visited[i]) {
        if (hasCycleDFS(i, -1, visited)) {
          return true;
        }
      }
    }

    return false;
  }
};

void example5_cycleDetection() {
  cout << "\n===== EXAMPLE 5: Cycle Detection (Undirected) =====" << endl;

  CycleDetector graph1(3);
  graph1.addVertex("A");
  graph1.addVertex("B");
  graph1.addVertex("C");

  cout << "Graph 1: A-B, B-C (no cycle)" << endl;
  graph1.addEdge(0, 1);
  graph1.addEdge(1, 2);
  cout << "Has cycle: " << (graph1.hasCycle() ? "YES" : "NO") << endl;

  CycleDetector graph2(3);
  graph2.addVertex("A");
  graph2.addVertex("B");
  graph2.addVertex("C");

  cout << "\nGraph 2: A-B, B-C, C-A (has cycle)" << endl;
  graph2.addEdge(0, 1);
  graph2.addEdge(1, 2);
  graph2.addEdge(2, 0);
  cout << "Has cycle: " << (graph2.hasCycle() ? "YES" : "NO") << endl;
}

/*
======================= CONCEPT 6: CONNECTED COMPONENTS =======================

Connected Component: Maximal set of vertices where every vertex reachable from
any other

Finding connected components:
1. For each unvisited vertex, start BFS/DFS
2. All vertices in same traversal form one component
3. Count number of traversals = number of components
*/

// ===== EXAMPLE 6: Connected Components =====
class ComponentFinder {
private:
  int numVertices;
  vector<vector<int>> adj;
  vector<string> vertexLabels;

  void dfs(int v, vector<bool> &visited, vector<int> &component) {
    visited[v] = true;
    component.push_back(v);

    for (int neighbor : adj[v]) {
      if (!visited[neighbor]) {
        dfs(neighbor, visited, component);
      }
    }
  }

public:
  ComponentFinder(int v) : numVertices(v) { adj.resize(v); }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<vector<int>> findComponents() {
    vector<bool> visited(numVertices, false);
    vector<vector<int>> components;

    for (int i = 0; i < numVertices; i++) {
      if (!visited[i]) {
        vector<int> component;
        dfs(i, visited, component);
        components.push_back(component);
      }
    }

    return components;
  }
};

void example6_connectedComponents() {
  cout << "\n===== EXAMPLE 6: Connected Components =====" << endl;

  ComponentFinder graph(7);
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");
  graph.addVertex("E");
  graph.addVertex("F");
  graph.addVertex("G");

  graph.addEdge(0, 1); // Component 1
  graph.addEdge(1, 2);

  graph.addEdge(3, 4); // Component 2
  graph.addEdge(4, 5);

  // Vertex 6 is isolated

  auto components = graph.findComponents();

  cout << "Found " << components.size() << " connected components:" << endl;
  for (int i = 0; i < components.size(); i++) {
    cout << "Component " << i + 1 << ": ";
    for (int v : components[i]) {
      cout << (char)('A' + v) << " ";
    }
    cout << endl;
  }
}

/*
================================================================================
                        KEY CONCEPTS SUMMARY
================================================================================

1. BFS (BREADTH-FIRST SEARCH):
   ✓ Uses queue (FIFO)
   ✓ Explores level by level
   ✓ Shortest path in unweighted graphs
   ✓ Time: O(V + E), Space: O(V)

2. DFS (DEPTH-FIRST SEARCH):
   ✓ Uses stack (LIFO)
   ✓ Explores by depth, then backtracks
   ✓ Can be recursive or iterative
   ✓ Time: O(V + E), Space: O(V)

3. BFS vs DFS:
   ┌────────────┬─────────────────┬──────────────────┐
   │ Aspect     │ BFS             │ DFS              │
   ├────────────┼─────────────────┼──────────────────┤
   │ Data Struct│ Queue           │ Stack            │
   │ Order      │ Level-by-level  │ Depth-first      │
   │ Path       │ Shortest        │ Not guaranteed   │
   │ Memory     │ More (wide tree)│ Less (narrow)    │
   │ Uses       │ Shortest path   │ Cycle detect     │
   └────────────┴─────────────────┴──────────────────┘

4. CYCLE DETECTION:
   ✓ Undirected: Check if neighbor is parent
   ✓ Directed: Use color marking (white/gray/black)

5. CONNECTED COMPONENTS:
   ✓ Each connected component = one traversal
   ✓ Count traversals to find number of components

================================================================================
                        COMMON MISTAKES TO AVOID
================================================================================

❌ MISTAKE 1: Not marking vertex as visited before processing
✓ CORRECT: Mark visited immediately to avoid infinite loops

❌ MISTAKE 2: Confusing BFS with DFS applications
✓ CORRECT: BFS for shortest paths, DFS for cycles/topological sort

❌ MISTAKE 3: Revisiting parent in cycle detection
✓ CORRECT: Track parent to avoid false cycle in undirected graphs

❌ MISTAKE 4: Not handling disconnected graphs
✓ CORRECT: Loop through all unvisited vertices to handle all components

❌ MISTAKE 5: Queue vs Stack mix-up
✓ CORRECT: Queue for BFS, Stack for DFS

================================================================================
                        PRACTICE EXERCISES
================================================================================

Exercise 1: Compare BFS vs DFS order on same graph

Exercise 2: Find shortest path using BFS

Exercise 3: Detect cycles in both undirected and directed graphs

Exercise 4: Find all connected components

Exercise 5: Check if graph is bipartite using BFS coloring

Exercise 6: Find path between two vertices

Exercise 7: Implement DFS using stack (all variants)

Exercise 8: Count vertices at specific distance from source

Exercise 9: Find all vertices in same component as given vertex

Exercise 10: Check if graph is connected

================================================================================
*/

void example7_comparisonBFSvsDFS() {
  cout << "\n===== EXAMPLE 7: BFS vs DFS Comparison =====" << endl;

  BFSTraversal bfsGraph(5);
  DFSRecursive dfsGraph(5);

  for (int i = 0; i < 5; i++) {
    bfsGraph.addVertex(string(1, 'A' + i));
    dfsGraph.addVertex(string(1, 'A' + i));
  }

  bfsGraph.addEdge(0, 1);
  bfsGraph.addEdge(0, 2);
  bfsGraph.addEdge(1, 3);
  bfsGraph.addEdge(2, 4);

  dfsGraph.addEdge(0, 1);
  dfsGraph.addEdge(0, 2);
  dfsGraph.addEdge(1, 3);
  dfsGraph.addEdge(2, 4);

  cout << "Same graph structure (tree):" << endl;
  cout << "    A" << endl;
  cout << "   / \\" << endl;
  cout << "  B   C" << endl;
  cout << " /     \\" << endl;
  cout << "D       E" << endl;

  bfsGraph.printBFS(0);
  dfsGraph.printDFS(0);

  cout << "BFS: Level-order (breadth first)" << endl;
  cout << "DFS: Goes deep, then backtracks" << endl;
}

// ===== MAIN FUNCTION =====
int main() {
  cout << "\n" << string(80, '=') << endl;
  cout << "       25.3.2: GRAPH TRAVERSALS (BFS & DFS) - LEARNING GUIDE"
       << endl;
  cout << string(80, '=') << endl;

  try {
    example1_basicBFS();
    example2_bfsWithDistances();
    example3_dfsRecursive();
    example4_dfsIterative();
    example5_cycleDetection();
    example6_connectedComponents();
    example7_comparisonBFSvsDFS();

    cout << "\n" << string(80, '=') << endl;
    cout << "All examples completed successfully!" << endl;
    cout << string(80, '=') << endl;
  } catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
  }

  return 0;
}
