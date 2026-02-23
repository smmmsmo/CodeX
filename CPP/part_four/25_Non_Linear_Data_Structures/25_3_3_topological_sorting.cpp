/*
================================================================================
                    25.3.3: TOPOLOGICAL SORTING
================================================================================
Comprehensive Learning Guide on Topological Sorting

TOPIC BREAKDOWN:
• What is topological sorting and when to use it
• Kahn's Algorithm (BFS-based, in-degree method)
• DFS-based topological sorting
• Cycle detection in directed graphs
• Applications: Task scheduling, dependency resolution, etc.
• Handling disconnected DAGs

KEY LEARNING POINTS:
✓ Understanding DAG (Directed Acyclic Graph) concept
✓ Implementing both Kahn's and DFS-based algorithms
✓ Detecting cycles in directed graphs
✓ Finding valid orderings of tasks with dependencies
✓ Handling multiple valid topological orderings

================================================================================
                    PART 1: TOPOLOGICAL SORTING BASICS
================================================================================
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

/*
======================= CONCEPT 1: TOPOLOGICAL SORTING =======================

Topological Sort: Linear ordering of vertices such that for every edge u→v,
u appears before v in the ordering.

ONLY VALID FOR:
- Directed graphs
- Acyclic graphs (DAG - Directed Acyclic Graph)

EXAMPLES:
• Task scheduling with dependencies
  Task A→B means A must be completed before B

• Course prerequisites
  CS101 → CS201 → CS301

• Compiler dependency resolution

• Build system (make, gradle)

KEY PROPERTY:
A DAG always has at least one topological ordering.
A directed graph with cycle has NO topological ordering.

MULTIPLE VALID ORDERINGS:
A graph may have multiple valid topological sorts.
Example: If A→C and B→D (independent chains),
both [A,B,C,D] and [B,A,D,C] are valid.

TIME: O(V + E) for both algorithms
SPACE: O(V) for queue/stack and in-degree array
*/

void concept1_topologicalBasics() {
  cout << "\n===== CONCEPT 1: Topological Sorting Basics =====" << endl;

  cout << "\nExample: Course Prerequisites" << endl;
  cout << "CS101 (Intro)" << endl;
  cout << "  ↓" << endl;
  cout << "CS201 (Data Structures)" << endl;
  cout << "  ↓" << endl;
  cout << "CS301 (Algorithms)" << endl;
  cout << "  ↓" << endl;
  cout << "CS401 (Advanced Algorithms)" << endl;

  cout << "\nValid topological order: CS101 → CS201 → CS301 → CS401" << endl;
  cout << "(Must take CS101 before CS201, etc.)" << endl;

  cout << "\nNOTE: If we had CS401→CS101, that would create a cycle "
          "(impossible!)"
       << endl;
}

/*
======================= CONCEPT 2: KAHN'S ALGORITHM =======================

Kahn's Algorithm (BFS-based, in-degree method):

Algorithm:
1. Compute in-degree for each vertex
2. Add all vertices with in-degree 0 to queue
3. While queue not empty:
   a. Dequeue vertex u, add to result
   b. For each neighbor v of u:
      - Decrease in-degree[v]
      - If in-degree[v] becomes 0, enqueue v
4. If result has V vertices, topological sort exists
   Otherwise, cycle detected

WHY IT WORKS:
- Process vertices with no dependencies first (in-degree 0)
- When edge u→v is "processed", v's dependency count decreases
- When v has no more dependencies (in-degree 0), process v next

ADVANTAGES:
- Easy to understand
- Easy to detect cycles
- Efficient: O(V + E)
*/

// ===== EXAMPLE 2: Kahn's Algorithm =====
class KahnTopologicalSort {
private:
  int numVertices;
  vector<vector<int>> adj;
  vector<string> vertexLabels;
  vector<int> inDegree;

public:
  KahnTopologicalSort(int v) : numVertices(v) {
    adj.resize(v);
    inDegree.assign(v, 0);
  }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    inDegree[v]++;
  }

  pair<vector<int>, bool> kahnSort() {
    vector<int> result;
    queue<int> q;

    // Find all vertices with in-degree 0
    for (int i = 0; i < numVertices; i++) {
      if (inDegree[i] == 0) {
        q.push(i);
      }
    }

    // Process vertices with no dependencies
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      result.push_back(u);

      // For each neighbor of u
      for (int v : adj[u]) {
        inDegree[v]--;
        if (inDegree[v] == 0) {
          q.push(v);
        }
      }
    }

    // Check if all vertices processed (no cycle)
    bool hasCycle = (result.size() != numVertices);

    return {result, !hasCycle};
  }

  void printTopologicalSort() {
    // Reset in-degrees for fresh calculation
    inDegree.assign(numVertices, 0);
    for (int u = 0; u < numVertices; u++) {
      for (int v : adj[u]) {
        inDegree[v]++;
      }
    }

    auto [result, isValid] = kahnSort();

    if (!isValid) {
      cout << "Cycle detected! Topological sort not possible." << endl;
    } else {
      cout << "Topological Order: ";
      for (int v : result) {
        cout << vertexLabels[v] << " ";
      }
      cout << endl;
    }
  }
};

void example2_kahnAlgorithm() {
  cout << "\n===== EXAMPLE 2: Kahn's Algorithm =====" << endl;

  // Example 1: Valid DAG
  cout << "\nExample 1: Task Scheduling (Valid DAG)" << endl;
  KahnTopologicalSort graph1(6);
  graph1.addVertex("Task1");
  graph1.addVertex("Task2");
  graph1.addVertex("Task3");
  graph1.addVertex("Task4");
  graph1.addVertex("Task5");
  graph1.addVertex("Task6");

  cout << "Dependencies: T1→T2, T1→T3, T2→T4, T3→T4, T4→T5, T4→T6" << endl;
  graph1.addEdge(0, 1); // Task1 → Task2
  graph1.addEdge(0, 2); // Task1 → Task3
  graph1.addEdge(1, 3); // Task2 → Task4
  graph1.addEdge(2, 3); // Task3 → Task4
  graph1.addEdge(3, 4); // Task4 → Task5
  graph1.addEdge(3, 5); // Task4 → Task6

  graph1.printTopologicalSort();

  // Example 2: Graph with cycle
  cout << "\nExample 2: Graph with Cycle (Invalid)" << endl;
  KahnTopologicalSort graph2(3);
  graph2.addVertex("A");
  graph2.addVertex("B");
  graph2.addVertex("C");

  cout << "Dependencies: A→B, B→C, C→A (forms cycle)" << endl;
  graph2.addEdge(0, 1);
  graph2.addEdge(1, 2);
  graph2.addEdge(2, 0);

  graph2.printTopologicalSort();
}

/*
======================= CONCEPT 3: DFS-BASED TOPOLOGICAL SORT
=======================

DFS-based Algorithm:

Algorithm:
1. For each unvisited vertex:
   a. Perform DFS
   b. After DFS completes (post-order), push vertex to stack
2. Result is stack contents (in reverse order)

WHY IT WORKS:
- DFS explores deep first, visits descendants before returning
- Post-order: vertex processed AFTER all descendants
- By pushing in post-order, vertices with dependencies come before dependents
- Reversing gives correct topological order

ADVANTAGES:
- Alternative to Kahn's algorithm
- Naturally detects cycles (gray vertex = back edge = cycle)
- Some prefer for cycle detection
*/

// ===== EXAMPLE 3: DFS-Based Topological Sort =====
enum Color { WHITE = 0, GRAY = 1, BLACK = 2 };

class DFSTopologicalSort {
private:
  int numVertices;
  vector<vector<int>> adj;
  vector<string> vertexLabels;
  vector<Color> color;
  stack<int> st;
  bool cycleFound;

  void dfs(int u) {
    color[u] = GRAY;

    for (int v : adj[u]) {
      if (color[v] == WHITE) {
        dfs(v);
      } else if (color[v] == GRAY) {
        cycleFound = true;
      }
    }

    color[u] = BLACK;
    st.push(u);
  }

public:
  DFSTopologicalSort(int v) : numVertices(v), cycleFound(false) {
    adj.resize(v);
    color.assign(v, WHITE);
  }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v) { adj[u].push_back(v); }

  pair<vector<int>, bool> dfsSort() {
    cycleFound = false;
    color.assign(numVertices, WHITE);

    // Clear stack
    while (!st.empty())
      st.pop();

    // Visit all vertices
    for (int i = 0; i < numVertices; i++) {
      if (color[i] == WHITE) {
        dfs(i);
      }
    }

    // Extract result from stack
    vector<int> result;
    while (!st.empty()) {
      result.push_back(st.top());
      st.pop();
    }

    return {result, !cycleFound};
  }

  void printTopologicalSort() {
    auto [result, isValid] = dfsSort();

    if (!isValid) {
      cout << "Cycle detected! Topological sort not possible." << endl;
    } else {
      cout << "Topological Order (DFS): ";
      for (int v : result) {
        cout << vertexLabels[v] << " ";
      }
      cout << endl;
    }
  }
};

void example3_dfsTopologicalSort() {
  cout << "\n===== EXAMPLE 3: DFS-Based Topological Sort =====" << endl;

  cout << "\nSame graph as Example 2:" << endl;
  DFSTopologicalSort graph(6);
  graph.addVertex("Task1");
  graph.addVertex("Task2");
  graph.addVertex("Task3");
  graph.addVertex("Task4");
  graph.addVertex("Task5");
  graph.addVertex("Task6");

  graph.addEdge(0, 1);
  graph.addEdge(0, 2);
  graph.addEdge(1, 3);
  graph.addEdge(2, 3);
  graph.addEdge(3, 4);
  graph.addEdge(3, 5);

  graph.printTopologicalSort();

  cout << "\nNote: May differ from Kahn's but still valid" << endl;
  cout << "(Multiple valid topological orderings exist)" << endl;
}

/*
======================= CONCEPT 4: CYCLE DETECTION IN DIRECTED GRAPHS
=======================

Three-Color DFS Method:
- WHITE (0): Unvisited
- GRAY (1): Currently visiting (in recursion stack)
- BLACK (2): Fully processed

CYCLE DETECTION:
- If we encounter a GRAY vertex during DFS, back edge exists → CYCLE
- Back edge: edge to ancestor in DFS tree

Example:
  DFS from 0: 0→1→2→0 (back edge to 0 which is GRAY) → CYCLE FOUND
*/

// ===== EXAMPLE 4: Cycle Detection in Directed Graphs =====
class DirectedCycleDetector {
private:
  int numVertices;
  vector<vector<int>> adj;
  vector<string> vertexLabels;
  vector<Color> color;
  bool cycleFound;
  int cycleStart = -1, cycleEnd = -1;

  bool dfs(int u) {
    color[u] = GRAY;

    for (int v : adj[u]) {
      if (color[v] == WHITE) {
        if (dfs(v))
          return true;
      } else if (color[v] == GRAY) {
        cycleFound = true;
        cycleStart = v;
        cycleEnd = u;
        return true;
      }
    }

    color[u] = BLACK;
    return false;
  }

public:
  DirectedCycleDetector(int v) : numVertices(v), cycleFound(false) {
    adj.resize(v);
    color.assign(v, WHITE);
  }

  void addVertex(string label) { vertexLabels.push_back(label); }

  void addEdge(int u, int v) { adj[u].push_back(v); }

  bool hasCycle() {
    cycleFound = false;
    color.assign(numVertices, WHITE);

    for (int i = 0; i < numVertices; i++) {
      if (color[i] == WHITE) {
        if (dfs(i)) {
          return true;
        }
      }
    }

    return false;
  }

  void printCycleStatus() {
    if (hasCycle()) {
      cout << "Cycle detected: " << vertexLabels[cycleStart] << " ← → "
           << vertexLabels[cycleEnd] << endl;
    } else {
      cout << "No cycle found - DAG confirmed!" << endl;
    }
  }
};

void example4_cycleDetectionDirected() {
  cout << "\n===== EXAMPLE 4: Cycle Detection (Directed Graphs) =====" << endl;

  cout << "\nExample 1: DAG (No Cycle)" << endl;
  DirectedCycleDetector graph1(4);
  graph1.addVertex("A");
  graph1.addVertex("B");
  graph1.addVertex("C");
  graph1.addVertex("D");

  graph1.addEdge(0, 1); // A→B
  graph1.addEdge(1, 2); // B→C
  graph1.addEdge(2, 3); // C→D

  cout << "Edges: A→B, B→C, C→D" << endl;
  graph1.printCycleStatus();

  cout << "\nExample 2: Graph with Cycle" << endl;
  DirectedCycleDetector graph2(4);
  graph2.addVertex("A");
  graph2.addVertex("B");
  graph2.addVertex("C");
  graph2.addVertex("D");

  graph2.addEdge(0, 1); // A→B
  graph2.addEdge(1, 2); // B→C
  graph2.addEdge(2, 3); // C→D
  graph2.addEdge(3, 0); // D→A (closes cycle)

  cout << "Edges: A→B, B→C, C→D, D→A" << endl;
  graph2.printCycleStatus();
}

/*
======================= CONCEPT 5: PRACTICAL APPLICATIONS
=======================

1. TASK SCHEDULING
   - Determine order to execute tasks with dependencies
   - Check for circular dependencies

2. COURSE PREREQUISITES
   - Determine valid course registration order
   - Detect impossible prerequisite chains

3. BUILD SYSTEMS
   - Compile files in correct dependency order
   - Detect circular includes

4. DEPENDENCY RESOLUTION
   - Package managers (npm, pip, maven)
   - Resolve library dependencies

5. COMPILER OPTIMIZATION
   - Instruction scheduling
   - Dead code elimination order
*/

// ===== EXAMPLE 5: Practical Application - Course Scheduling =====
void example5_courseScheduling() {
  cout << "\n===== EXAMPLE 5: Practical Application - Course Scheduling ====="
       << endl;

  KahnTopologicalSort curriculum(7);
  curriculum.addVertex("CS101");
  curriculum.addVertex("CS201");
  curriculum.addVertex("CS301");
  curriculum.addVertex("CS401");
  curriculum.addVertex("CS402");
  curriculum.addVertex("MATH101");
  curriculum.addVertex("MATH201");

  cout << "Course Prerequisites:" << endl;
  cout << "  MATH101 → MATH201" << endl;
  cout << "  CS101 → CS201 → CS301 → CS401" << endl;
  cout << "  CS301 → CS402" << endl;
  cout << "  MATH201 and CS201 → CS301 (both required)" << endl;

  curriculum.addEdge(4, 5); // MATH101 → MATH201
  curriculum.addEdge(0, 1); // CS101 → CS201
  curriculum.addEdge(1, 2); // CS201 → CS301
  curriculum.addEdge(2, 3); // CS301 → CS401
  curriculum.addEdge(2, 6); // CS301 → CS402
  curriculum.addEdge(5, 2); // MATH201 → CS301

  cout << "\nSuggested course order:" << endl;
  curriculum.printTopologicalSort();
}

/*
================================================================================
                        KEY CONCEPTS SUMMARY
================================================================================

1. TOPOLOGICAL SORTING:
   ✓ Only for directed acyclic graphs (DAG)
   ✓ Linear ordering where u→v means u before v
   ✓ Multiple valid orderings may exist
   ✓ Time: O(V + E), Space: O(V)

2. KAHN'S ALGORITHM:
   ✓ In-degree based, BFS approach
   ✓ Process vertices with in-degree 0
   ✓ Easy cycle detection (incomplete result = cycle)
   ✓ Good for detecting when cycle exists

3. DFS-BASED ALGORITHM:
   ✓ Post-order traversal based
   ✓ Push to stack after DFS completes
   ✓ Color-based cycle detection (gray vertex = cycle)
   ✓ More efficient cycle detection

4. COMPARISON:
   ┌─────────────────┬──────────────────┬─────────────────┐
   │ Aspect          │ Kahn's           │ DFS             │
   ├─────────────────┼──────────────────┼─────────────────┤
   │ Approach        │ BFS + In-degree  │ DFS + Post-order│
   │ Cycle Detect    │ Check result size│ Color method    │
   │ Implementation  │ Simpler          │ Slightly complex│
   │ Use Case        │ Task scheduling  │ General purpose │
   └─────────────────┴──────────────────┴─────────────────┘

5. CYCLE DETECTION:
   ✓ Gray vertex during DFS = Back edge = Cycle
   ✓ Result size < V = Cycle exists (Kahn's)

================================================================================
                        COMMON MISTAKES TO AVOID
================================================================================

❌ MISTAKE 1: Applying topological sort to cyclic graph
✓ CORRECT: First verify graph is DAG or check for cycles

❌ MISTAKE 2: Forgetting multiple valid orderings exist
✓ CORRECT: Any valid ordering satisfying constraints is correct

❌ MISTAKE 3: Not resetting in-degrees for multiple tests
✓ CORRECT: Reset in-degree array before each execution

❌ MISTAKE 4: Confusing pre-order with post-order DFS
✓ CORRECT: Use post-order (push after DFS returns)

❌ MISTAKE 5: Not detecting all cycles
✓ CORRECT: Check all unvisited vertices for DFS cycles

================================================================================
                        PRACTICE EXERCISES
================================================================================

Exercise 1: Implement both Kahn's and DFS-based sorting

Exercise 2: Detect cycles and report conflicting edges

Exercise 3: Find if valid topological sort exists

Exercise 4: Count number of valid topological orderings

Exercise 5: Determine if one task before another in topological order

Exercise 6: Build course prerequisite system

Exercise 7: Detect circular dependencies in code/imports

Exercise 8: Find critical path in task dependency graph

Exercise 9: Topological sort on disconnected DAG

Exercise 10: Build and validate compilation dependency order

================================================================================
*/

// ===== MAIN FUNCTION =====
int main() {
  cout << "\n" << string(80, '=') << endl;
  cout << "         25.3.3: TOPOLOGICAL SORTING - LEARNING GUIDE" << endl;
  cout << string(80, '=') << endl;

  try {
    concept1_topologicalBasics();
    example2_kahnAlgorithm();
    example3_dfsTopologicalSort();
    example4_cycleDetectionDirected();
    example5_courseScheduling();

    cout << "\n" << string(80, '=') << endl;
    cout << "All examples completed successfully!" << endl;
    cout << string(80, '=') << endl;
  } catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
  }

  return 0;
}
