// ================================================================================
// TOPIC 27: ADVANCED DATA STRUCTURES
// FILE 1: Disjoint Set Union (Union-Find)
// ================================================================================
//
// CONCEPTS COVERED:
//   1. What is a Disjoint Set Union (DSU)?
//   2. Naive implementation (parent array)
//   3. Union by Rank optimization
//   4. Path Compression optimization
//   5. Combined: Union by Rank + Path Compression
//   6. Applications: cycle detection, connected components, Kruskal's MST
//   7. Weighted/Rollback DSU (advanced)
//
// KEY LEARNING POINTS:
//   - DSU manages a collection of disjoint (non-overlapping) sets
//   - Two key operations: find(x) and union(x, y)
//   - Without optimizations: O(n) per operation (worst case)
//   - Union by Rank alone: O(log n) per operation
//   - Path Compression alone: O(log n) amortized
//   - Both combined: O(α(n)) ≈ O(1) amortized (inverse Ackermann function)
//   - α(n) < 5 for all practical values of n
// ================================================================================

#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <algorithm>
#include <cassert>
using namespace std;

// ========================== EXAMPLE 1: NAIVE DSU ==========================
// Simple parent-array approach — no optimizations
// O(n) worst case for find() (long chains)

class NaiveDSU {
    vector<int> parent;
public:
    NaiveDSU(int n) : parent(n) {
        iota(parent.begin(), parent.end(), 0); // parent[i] = i (each node is its own root)
    }

    // Follow parent pointers until we reach the root
    int find(int x) {
        while (parent[x] != x)
            x = parent[x];
        return x;
    }

    // Attach root of x's set to root of y's set
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx != ry) parent[rx] = ry;
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

void example1_naive_dsu() {
    cout << "======== Example 1: Naive DSU ========\n";
    NaiveDSU dsu(6); // 6 nodes: 0..5

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);

    cout << "0-2 connected? " << (dsu.connected(0, 2) ? "YES" : "NO") << "\n"; // YES
    cout << "0-3 connected? " << (dsu.connected(0, 3) ? "YES" : "NO") << "\n"; // NO
    cout << "3-4 connected? " << (dsu.connected(3, 4) ? "YES" : "NO") << "\n"; // YES
    // WARNING: long chains form — find() is O(n) in worst case
}

// ====================== EXAMPLE 2: UNION BY RANK ==========================
// Attach the shorter tree under the taller tree
// Keeps trees balanced → O(log n) per operation

class RankDSU {
    vector<int> parent, rank_;
public:
    RankDSU(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (parent[x] != x)
            x = parent[x];
        return x;
    }

    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;

        // Always attach lower-rank root under higher-rank root
        if (rank_[rx] < rank_[ry])       parent[rx] = ry;
        else if (rank_[rx] > rank_[ry])  parent[ry] = rx;
        else {
            // Same rank: pick one as root, increase its rank
            parent[ry] = rx;
            rank_[rx]++;
        }
    }

    bool connected(int x, int y) { return find(x) == find(y); }
};

void example2_union_by_rank() {
    cout << "\n======== Example 2: Union by Rank ========\n";
    RankDSU dsu(7);

    dsu.unite(0, 1); // rank[0]=1
    dsu.unite(2, 3); // rank[2]=1
    dsu.unite(0, 2); // rank[0]=2 (merges two rank-1 trees)
    dsu.unite(4, 5);
    dsu.unite(4, 6);

    cout << "0-3 connected? " << (dsu.connected(0, 3) ? "YES" : "NO") << "\n"; // YES
    cout << "0-6 connected? " << (dsu.connected(0, 6) ? "YES" : "NO") << "\n"; // NO
    // Tree height is bounded by O(log n) — no long chains!
}

// =================== EXAMPLE 3: PATH COMPRESSION ============================
// After find(x), redirect all nodes on the path directly to the root
// Dramatically flattens the tree for future queries

class PathCompressDSU {
    vector<int> parent;
public:
    PathCompressDSU(int n) : parent(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    // Recursive path compression: set parent[x] = root directly
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // compress path as we unwind
        return parent[x];
    }

    // Iterative path compression (two-pass)
    int find_iterative(int x) {
        int root = x;
        while (parent[root] != root) root = parent[root]; // find root
        while (parent[x] != root) {                        // compress path
            int next = parent[x];
            parent[x] = root;
            x = next;
        }
        return root;
    }

    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx != ry) parent[rx] = ry;
    }

    bool connected(int x, int y) { return find(x) == find(y); }
};

void example3_path_compression() {
    cout << "\n======== Example 3: Path Compression ========\n";
    PathCompressDSU dsu(8);

    // Build a chain: 0->1->2->3->4->5->6->7
    for (int i = 0; i < 7; i++) dsu.unite(i, i + 1);

    cout << "Before compression: finding root of 0...\n";
    int root = dsu.find(0); // this compresses the entire chain
    cout << "Root of 0: " << root << "\n";
    cout << "0-7 connected? " << (dsu.connected(0, 7) ? "YES" : "NO") << "\n";
    // After find(0), all nodes on the path point directly to root
}

// ========= EXAMPLE 4: FULL DSU (Rank + Path Compression) ==================
// The gold standard — O(α(n)) amortized per operation
// This is what you should use in competitive programming and interviews

class DSU {
    vector<int> parent, rank_, size_;
    int components; // track number of distinct sets

public:
    DSU(int n) : parent(n), rank_(n, 0), size_(n, 1), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    // Path compression (recursive)
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // Union by rank; returns false if already in same set
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false; // already connected

        if (rank_[rx] < rank_[ry])  swap(rx, ry);
        parent[ry] = rx;            // attach ry under rx
        size_[rx] += size_[ry];
        if (rank_[rx] == rank_[ry]) rank_[rx]++;
        components--;
        return true;
    }

    bool connected(int x, int y) { return find(x) == find(y); }
    int  sizeOf(int x)           { return size_[find(x)]; }
    int  numComponents()         { return components; }
};

void example4_full_dsu() {
    cout << "\n======== Example 4: Full DSU (Rank + Path Compression) ========\n";
    DSU dsu(10);

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    dsu.unite(5, 6);
    dsu.unite(6, 7);
    dsu.unite(7, 8);

    cout << "Components: " << dsu.numComponents() << "\n"; // 4: {0,1,2},{3,4},{5,6,7,8},{9}
    cout << "Size of component containing 0: " << dsu.sizeOf(0) << "\n"; // 3
    cout << "Size of component containing 5: " << dsu.sizeOf(5) << "\n"; // 4

    dsu.unite(0, 5); // merge two big components
    cout << "After merging 0 and 5, size: " << dsu.sizeOf(0) << "\n"; // 7
    cout << "Components: " << dsu.numComponents() << "\n"; // 3
}

// =================== EXAMPLE 5: CYCLE DETECTION IN GRAPH ====================
// A classic DSU application: detect if adding an edge creates a cycle

struct Edge {
    int u, v;
};

bool hasCycle(int nodes, vector<Edge>& edges) {
    DSU dsu(nodes);
    for (auto& [u, v] : edges) {
        if (dsu.connected(u, v)) return true; // adding this edge forms a cycle
        dsu.unite(u, v);
    }
    return false;
}

void example5_cycle_detection() {
    cout << "\n======== Example 5: Cycle Detection ========\n";

    vector<Edge> edges1 = {{0,1}, {1,2}, {2,3}}; // tree — no cycle
    vector<Edge> edges2 = {{0,1}, {1,2}, {2,0}}; // triangle — cycle!

    cout << "Graph 1 has cycle? " << (hasCycle(4, edges1) ? "YES" : "NO") << "\n"; // NO
    cout << "Graph 2 has cycle? " << (hasCycle(3, edges2) ? "YES" : "NO") << "\n"; // YES
}

// =================== EXAMPLE 6: KRUSKAL'S MST ==============================
// Minimum Spanning Tree using DSU to efficiently detect cycles

struct WEdge {
    int u, v, w;
    bool operator<(const WEdge& o) const { return w < o.w; }
};

pair<int, vector<WEdge>> kruskal(int nodes, vector<WEdge>& edges) {
    sort(edges.begin(), edges.end()); // sort by weight ascending
    DSU dsu(nodes);
    vector<WEdge> mst;
    int totalWeight = 0;

    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) { // only include if it doesn't form a cycle
            mst.push_back(e);
            totalWeight += e.w;
            if ((int)mst.size() == nodes - 1) break; // MST complete
        }
    }
    return {totalWeight, mst};
}

void example6_kruskal_mst() {
    cout << "\n======== Example 6: Kruskal's MST with DSU ========\n";
    // Graph:  0--1 (4), 0--2 (3), 1--2 (1), 1--3 (2), 2--3 (4)
    vector<WEdge> edges = {{0,1,4},{0,2,3},{1,2,1},{1,3,2},{2,3,4}};
    auto [weight, mst] = kruskal(4, edges);

    cout << "MST total weight: " << weight << "\n"; // 6
    cout << "MST edges:\n";
    for (auto& [u, v, w] : mst)
        cout << "  " << u << " -- " << v << " (weight " << w << ")\n";
    // Edges: 1-2(1), 1-3(2), 0-2(3) → total = 6
}

// ========== EXAMPLE 7: COUNTING CONNECTED COMPONENTS ========================
// Count distinct connected components in an undirected graph

void example7_connected_components() {
    cout << "\n======== Example 7: Connected Components ========\n";
    // 7 nodes, some edges
    DSU dsu(7);
    vector<pair<int,int>> edges = {{0,1},{1,2},{3,4},{5,6}};

    for (auto& [u, v] : edges) dsu.unite(u, v);

    cout << "Connected components: " << dsu.numComponents() << "\n"; // 3
    cout << "Node 0 and 2 same component? " << (dsu.connected(0,2) ? "YES":"NO") << "\n"; // YES
    cout << "Node 0 and 3 same component? " << (dsu.connected(0,3) ? "YES":"NO") << "\n"; // NO
}

// =================== EXAMPLE 8: FRIEND CIRCLES (INTERVIEW PROBLEM) ==========
// Classic LeetCode-style problem: number of distinct friend groups

int friendCircles(vector<vector<int>>& M) {
    int n = M.size();
    DSU dsu(n);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (M[i][j] == 1) dsu.unite(i, j);
    return dsu.numComponents();
}

void example8_friend_circles() {
    cout << "\n======== Example 8: Friend Circles ========\n";
    // M[i][j]=1 means person i and j are friends
    vector<vector<int>> M = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    cout << "Number of friend circles: " << friendCircles(M) << "\n"; // 2
}

// ================= EXAMPLE 9: WEIGHTED DSU ==================================
// Stores relative weights/distances from each node to its root
// Useful for problems like: "is A 2x heavier than B?"

class WeightedDSU {
    vector<int> parent;
    vector<double> weight; // weight[x] = ratio relative to parent

public:
    WeightedDSU(int n) : parent(n), weight(n, 1.0) {
        iota(parent.begin(), parent.end(), 0);
    }

    // Returns {root, weight from x to root}
    pair<int, double> find(int x) {
        if (parent[x] == x) return {x, 1.0};
        auto [root, w] = find(parent[x]);
        parent[x] = root;
        weight[x] *= w; // chain multiply during compression
        return {root, weight[x]};
    }

    // Merge x and y with ratio: value(x) / value(y) = ratio
    bool unite(int x, int y, double ratio) {
        auto [rx, wx] = find(x);
        auto [ry, wy] = find(y);
        if (rx == ry) return false;
        parent[rx] = ry;
        weight[rx] = ratio * wy / wx;
        return true;
    }

    // Returns value(x)/value(y), or -1 if not connected
    double query(int x, int y) {
        auto [rx, wx] = find(x);
        auto [ry, wy] = find(y);
        if (rx != ry) return -1.0; // different components
        return wx / wy;
    }
};

void example9_weighted_dsu() {
    cout << "\n======== Example 9: Weighted DSU ========\n";
    // a/b = 2.0, b/c = 3.0 → a/c = 6.0
    WeightedDSU dsu(4);
    dsu.unite(0, 1, 2.0); // a(0)/b(1) = 2.0
    dsu.unite(1, 2, 3.0); // b(1)/c(2) = 3.0

    cout << "a/b = " << dsu.query(0, 1) << "\n";   // 2.0
    cout << "a/c = " << dsu.query(0, 2) << "\n";   // 6.0
    cout << "b/a = " << dsu.query(1, 0) << "\n";   // 0.5
    cout << "a/d = " << dsu.query(0, 3) << "\n";   // -1 (disconnected)
}

// ============ EXAMPLE 10: OFFLINE DYNAMIC CONNECTIVITY ====================
// Process queries about connectivity offline using DSU
// (Edges are added but never removed — use Link-Cut Trees for removals)

void example10_offline_connectivity() {
    cout << "\n======== Example 10: Offline Dynamic Connectivity ========\n";

    DSU dsu(6);
    vector<tuple<string, int, int>> operations = {
        {"connect", 0, 1},
        {"connect", 1, 2},
        {"query",   0, 2},   // YES
        {"connect", 3, 4},
        {"query",   0, 4},   // NO
        {"connect", 2, 4},
        {"query",   0, 4},   // YES
    };

    for (auto& [op, u, v] : operations) {
        if (op == "connect") {
            dsu.unite(u, v);
            cout << "Connected " << u << " and " << v << "\n";
        } else {
            cout << "Query " << u << "-" << v << ": "
                 << (dsu.connected(u, v) ? "YES" : "NO") << "\n";
        }
    }
}

// ========================= KEY CONCEPTS BOX ==================================
/*
 ┌─────────────────────────────────────────────────────────────────┐
 │                  DSU KEY CONCEPTS SUMMARY                       │
 ├─────────────────────────────────────────────────────────────────┤
 │ Structure:  parent[], rank[], size[]                            │
 │                                                                 │
 │ Operations:                                                     │
 │   find(x)      → returns root of x's set                       │
 │   unite(x, y)  → merges sets of x and y                        │
 │   connected(x,y) → find(x) == find(y)                          │
 │                                                                 │
 │ Complexity (with both optimizations):                           │
 │   find()  → O(α(n)) ≈ O(1) amortized                          │
 │   unite() → O(α(n)) ≈ O(1) amortized                          │
 │   Space   → O(n)                                               │
 │                                                                 │
 │ Applications:                                                   │
 │   ✓ Kruskal's MST                                              │
 │   ✓ Cycle detection in undirected graphs                       │
 │   ✓ Connected components                                       │
 │   ✓ Network connectivity queries                               │
 │   ✓ Image segmentation                                         │
 │   ✓ Dynamic connectivity (offline)                             │
 └─────────────────────────────────────────────────────────────────┘
*/

// ========================= COMMON MISTAKES ===================================
/*
 MISTAKE 1: Forgetting path compression
   WRONG:
     int find(int x) {
         while (parent[x] != x) x = parent[x]; // no compression!
         return x;
     }
   RIGHT: parent[x] = find(parent[x]); // recursive compression

 MISTAKE 2: Union without rank/size
   WRONG: parent[find(x)] = find(y); // arbitrary direction
   RIGHT: Always attach smaller/lower-rank root under taller one

 MISTAKE 3: Using find() result without calling it first
   WRONG: if (parent[x] == parent[y]) ...   // parents may differ even if same set
   RIGHT: if (find(x) == find(y)) ...

 MISTAKE 4: Not initializing parent[i] = i
   Every node must start as its own root.

 MISTAKE 5: Applying DSU to directed graphs
   DSU models undirected connectivity only.
   For directed: use Tarjan's SCC or Kosaraju's.
*/

// ========================= PRACTICE EXERCISES ================================
/*
 EXERCISE 1:
   Given n cities and m roads, implement a DSU to answer:
   "Are city A and city B in the same network?"
   Then count the total number of disconnected networks.

 EXERCISE 2:
   Detect if an undirected graph has a cycle using DSU.
   Test with: 4 nodes, edges: (0,1),(1,2),(2,3),(3,0) → has cycle
              4 nodes, edges: (0,1),(1,2),(2,3)         → no cycle

 EXERCISE 3:
   Implement Kruskal's algorithm for MST on:
   Nodes: 5, Edges: (0-1,2),(0-3,6),(1-2,3),(1-3,8),(1-4,5),(2-4,7),(3-4,9)
   Expected MST weight: 16

 EXERCISE 4:
   Solve "Number of Provinces" (LeetCode 547):
   Given an n×n adjacency matrix, count connected provinces using DSU.

 EXERCISE 5:
   Implement DSU with rollback (no path compression, undo last k unions).
   Hint: Use union by rank only (path compression breaks rollback).

 EXERCISE 6:
   Solve "Redundant Connection" (LeetCode 684):
   Find the edge that, when removed, makes the graph a tree.
   Return the edge that appears last in the input.

 EXERCISE 7:
   Given an array of integers, implement DSU where you can:
   - Merge two elements' sets
   - Query the maximum value in a set
   Hint: Store max in the root node.

 EXERCISE 8:
   Use DSU to solve the "Accounts Merge" problem:
   Group email accounts belonging to the same person
   (Two accounts belong to the same person if they share an email).
*/

int main() {
    cout << "================================================================================\n";
    cout << "          TOPIC 27: ADVANCED DATA STRUCTURES — DISJOINT SET UNION               \n";
    cout << "================================================================================\n\n";

    example1_naive_dsu();
    example2_union_by_rank();
    example3_path_compression();
    example4_full_dsu();
    example5_cycle_detection();
    example6_kruskal_mst();
    example7_connected_components();
    example8_friend_circles();
    example9_weighted_dsu();
    example10_offline_connectivity();

    cout << "\n================================================================================\n";
    cout << "                           ALL EXAMPLES COMPLETED                                \n";
    cout << "================================================================================\n";
    return 0;
}

/*
 * EXPECTED OUTPUT:
 * ================================================================================
 *           TOPIC 27: ADVANCED DATA STRUCTURES — DISJOINT SET UNION
 * ================================================================================
 *
 * ======== Example 1: Naive DSU ========
 * 0-2 connected? YES
 * 0-3 connected? NO
 * 3-4 connected? YES
 *
 * ======== Example 2: Union by Rank ========
 * 0-3 connected? YES
 * 0-6 connected? NO
 *
 * ======== Example 3: Path Compression ========
 * Before compression: finding root of 0...
 * Root of 0: 7
 * 0-7 connected? YES
 *
 * ======== Example 4: Full DSU (Rank + Path Compression) ========
 * Components: 4
 * Size of component containing 0: 3
 * Size of component containing 5: 4
 * After merging 0 and 5, size: 7
 * Components: 3
 *
 * ======== Example 5: Cycle Detection ========
 * Graph 1 has cycle? NO
 * Graph 2 has cycle? YES
 *
 * ======== Example 6: Kruskal's MST with DSU ========
 * MST total weight: 6
 * MST edges:
 *   1 -- 2 (weight 1)
 *   1 -- 3 (weight 2)
 *   0 -- 2 (weight 3)
 *
 * ======== Example 7: Connected Components ========
 * Connected components: 3
 * Node 0 and 2 same component? YES
 * Node 0 and 3 same component? NO
 *
 * ======== Example 8: Friend Circles ========
 * Number of friend circles: 2
 *
 * ======== Example 9: Weighted DSU ========
 * a/b = 2
 * a/c = 6
 * b/a = 0.5
 * a/d = -1
 *
 * ======== Example 10: Offline Dynamic Connectivity ========
 * Connected 0 and 1
 * Connected 1 and 2
 * Query 0-2: YES
 * Connected 3 and 4
 * Query 0-4: NO
 * Connected 2 and 4
 * Query 0-4: YES
 */
