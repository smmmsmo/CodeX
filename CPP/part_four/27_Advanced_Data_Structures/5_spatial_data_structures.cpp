// ================================================================================
// TOPIC 27: ADVANCED DATA STRUCTURES
// FILE 5: Spatial Data Structures — KD-Trees, Quadtrees, R-Trees
// ================================================================================
//
// CONCEPTS COVERED:
//   1. KD-Tree (k-dimensional tree)
//      - Build, nearest neighbor search, range search
//      - Time complexity and best practices
//   2. Quadtree
//      - Point quadtrees, region quadtrees
//      - Insertion, point search, range query
//   3. R-Tree (brief overview and conceptual model)
//      - Bounding boxes, page structure, use cases
//   4. Comparison and selection guide
//
// KEY LEARNING POINTS:
//   - Spatial data structures organize multi-dimensional data for efficient
//     nearest-neighbor search, range search, and spatial queries
//   - KD-Tree: generalizes BST to k dimensions; best for exact NN and range search
//   - Quadtree: splits 2D space into 4 quadrants recursively; good for 2D
//   - R-Tree: groups nearby objects using bounding boxes; used in databases/GIS
//   - These are fundamental in: game engines, GPS navigation, machine learning
//     (k-NN algorithm), robotics, computer graphics, databases
// ================================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <string>
#include <memory>
using namespace std;

// ========================== PART A: KD-TREE ==================================

// =================== EXAMPLE 1: KD-TREE CONCEPT ============================
void example1_kdtree_idea() {
    cout << "======== Example 1: KD-Tree — The Core Idea ========\n";
    cout << "Problem: Find the nearest coffee shop to your location (x, y)\n";
    cout << "Naive: compare with all N shops → O(N) per query\n";
    cout << "KD-Tree: O(log N) average case by partitioning space\n\n";

    cout << "KD-Tree construction (2D example):\n";
    cout << "  Points: (2,3),(5,4),(9,6),(4,7),(8,1),(7,2)\n\n";
    cout << "  Depth 0: split on X (median X = 7 → left: x≤7, right: x>7)\n";
    cout << "         [7,2] is root\n";
    cout << "         LEFT subtree: (2,3),(5,4),(4,7) — all x ≤ 7\n";
    cout << "         RIGHT subtree: (9,6),(8,1) — all x > 7\n\n";
    cout << "  Depth 1: split on Y (alternate dimensions)\n";
    cout << "         Left's median Y = 4 → (5,4) is left's root\n";
    cout << "         etc...\n\n";
    cout << "  Key insight: At each level, we split on one dimension.\n";
    cout << "  Alternating dimensions ensures balanced partitioning.\n";
}

// =================== EXAMPLE 2: KD-TREE IMPLEMENTATION =====================
struct Point2D {
    double x, y;
    int id; // optional label
    Point2D(double x = 0, double y = 0, int id = -1) : x(x), y(y), id(id) {}
    double dist2(const Point2D& o) const { // squared distance (avoid sqrt)
        return (x-o.x)*(x-o.x) + (y-o.y)*(y-o.y);
    }
};

struct KDNode {
    Point2D point;
    KDNode *left, *right;
    KDNode(Point2D p) : point(p), left(nullptr), right(nullptr) {}
};

class KDTree2D {
    KDNode* root;

    // Build KD-tree from sorted points, alternating split dimension
    KDNode* build(vector<Point2D>& pts, int l, int r, int depth) {
        if (l > r) return nullptr;
        int mid = (l + r) / 2;

        // Sort on current dimension
        if (depth % 2 == 0)
            nth_element(pts.begin()+l, pts.begin()+mid, pts.begin()+r+1,
                        [](const Point2D& a, const Point2D& b){ return a.x < b.x; });
        else
            nth_element(pts.begin()+l, pts.begin()+mid, pts.begin()+r+1,
                        [](const Point2D& a, const Point2D& b){ return a.y < b.y; });

        KDNode* node = new KDNode(pts[mid]);
        node->left  = build(pts, l, mid - 1, depth + 1);
        node->right = build(pts, mid + 1, r, depth + 1);
        return node;
    }

    // Nearest neighbor search
    void nnSearch(KDNode* node, const Point2D& query, int depth,
                  KDNode*& best, double& bestDist) {
        if (!node) return;

        double d = query.dist2(node->point);
        if (d < bestDist) {
            bestDist = d;
            best = node;
        }

        // Determine which subtree to search first (the one query is in)
        double diff = (depth % 2 == 0) ? (query.x - node->point.x)
                                        : (query.y - node->point.y);
        KDNode* near  = diff < 0 ? node->left  : node->right;
        KDNode* far   = diff < 0 ? node->right : node->left;

        nnSearch(near, query, depth + 1, best, bestDist);

        // Only search far subtree if it could contain a closer point
        // (The splitting hyperplane is closer than current best)
        if (diff * diff < bestDist)
            nnSearch(far, query, depth + 1, best, bestDist);
    }

    // Range search: find all points within distance r of query
    void rangeSearch(KDNode* node, const Point2D& query, double r2,
                     int depth, vector<Point2D>& result) {
        if (!node) return;

        if (query.dist2(node->point) <= r2)
            result.push_back(node->point);

        double diff = (depth % 2 == 0) ? (query.x - node->point.x)
                                        : (query.y - node->point.y);

        // Visit the near subtree always
        KDNode* near = diff < 0 ? node->left  : node->right;
        KDNode* far  = diff < 0 ? node->right : node->left;
        rangeSearch(near, query, r2, depth + 1, result);

        // Visit far subtree only if splitting plane intersects search sphere
        if (diff * diff <= r2)
            rangeSearch(far, query, r2, depth + 1, result);
    }

    void destroy(KDNode* n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

public:
    KDTree2D(vector<Point2D> pts) : root(nullptr) {
        if (!pts.empty())
            root = build(pts, 0, pts.size() - 1, 0);
    }

    ~KDTree2D() { destroy(root); }

    // Find nearest neighbor to query point
    Point2D nearestNeighbor(const Point2D& query) {
        KDNode* best = nullptr;
        double bestDist = INT_MAX;
        nnSearch(root, query, 0, best, bestDist);
        return best ? best->point : Point2D();
    }

    // Find all points within radius r of query
    vector<Point2D> rangeQuery(const Point2D& query, double r) {
        vector<Point2D> result;
        rangeSearch(root, query, r * r, 0, result);
        return result;
    }
};

void example2_kdtree_operations() {
    cout << "\n======== Example 2: KD-Tree Build + Nearest Neighbor ========\n";

    // Coffee shop locations
    vector<Point2D> shops = {
        {2,3,0}, {5,4,1}, {9,6,2}, {4,7,3},
        {8,1,4}, {7,2,5}, {3,8,6}, {6,5,7}
    };

    KDTree2D tree(shops);

    Point2D myLocation = {5.0, 5.0};
    Point2D nearest = tree.nearestNeighbor(myLocation);
    cout << "My location: (5, 5)\n";
    cout << "Nearest shop: (" << nearest.x << ", " << nearest.y << ")\n";
    cout << "Distance: " << sqrt(myLocation.dist2(nearest)) << "\n";
    // Expected: (5,4) or (6,5) — both are close

    // Range search: shops within radius 3
    auto nearby = tree.rangeQuery(myLocation, 3.0);
    cout << "\nShops within radius 3 of (5,5):\n";
    for (auto& p : nearby)
        cout << "  (" << p.x << ", " << p.y << ") dist=" << sqrt(myLocation.dist2(p)) << "\n";
}

void example3_kdtree_complexity() {
    cout << "\n======== Example 3: KD-Tree Complexity Analysis ========\n";
    cout << "┌──────────────────┬───────────────┬─────────────────────────────────┐\n";
    cout << "│  Operation       │  Complexity   │  Notes                          │\n";
    cout << "├──────────────────┼───────────────┼─────────────────────────────────┤\n";
    cout << "│  Build           │  O(n log n)   │  Sort on each level              │\n";
    cout << "│  NN Search       │  O(log n) avg │  O(n) worst (bad distributions) │\n";
    cout << "│  Range Search    │  O(√n + k)    │  k = results; d=2 dimensions    │\n";
    cout << "│  Insert (online) │  O(log n)     │  May unbalance tree over time   │\n";
    cout << "│  Space           │  O(n)         │  One node per point             │\n";
    cout << "├──────────────────┴───────────────┴─────────────────────────────────┤\n";
    cout << "│  Best for: static point sets, low dimensions (d ≤ 20)             │\n";
    cout << "│  Curse of dimensionality: performance degrades for large d         │\n";
    cout << "│  Rule of thumb: n >> 2^d for KD-Tree to be useful                 │\n";
    cout << "└─────────────────────────────────────────────────────────────────────┘\n";
}

// ========================== PART B: QUADTREE =================================

// =================== EXAMPLE 4: QUADTREE CONCEPT ===========================
void example4_quadtree_idea() {
    cout << "\n======== Example 4: Quadtree — 2D Space Partitioning ========\n";
    cout << "Idea: Recursively divide a 2D region into 4 equal quadrants\n\n";
    cout << "        NW  |  NE\n";
    cout << "       ─────┼─────\n";
    cout << "        SW  |  SE\n\n";
    cout << "Each leaf holds a few points (capacity C, usually 1-4)\n";
    cout << "When a leaf overflows, split into 4 child quadrants\n\n";
    cout << "Complexity:\n";
    cout << "  Build:         O(n log n) average\n";
    cout << "  Point search:  O(log n) average\n";
    cout << "  Range search:  O(√n + k) for 2D (k = results)\n";
    cout << "  Nearest neighbor: O(log n) average\n\n";
    cout << "Applications:\n";
    cout << "  Game engines: collision detection, LOD (level of detail)\n";
    cout << "  GIS: spatial indexing for map data\n";
    cout << "  Image compression: region quadtrees for uniform-color regions\n";
    cout << "  N-body simulation (Barnes-Hut): O(n log n) vs O(n²)\n";
}

// =================== EXAMPLE 5: QUADTREE IMPLEMENTATION ====================
struct Rect {
    double cx, cy, hw, hh; // center x, center y, half-width, half-height

    bool contains(double x, double y) const {
        return x >= cx - hw && x <= cx + hw &&
               y >= cy - hh && y <= cy + hh;
    }

    bool intersects(const Rect& o) const {
        return !(o.cx - o.hw > cx + hw || o.cx + o.hw < cx - hw ||
                 o.cy - o.hh > cy + hh || o.cy + o.hh < cy - hh);
    }
};

class Quadtree {
    static const int CAPACITY = 4;

    Rect boundary;
    vector<Point2D> points;
    bool divided;
    Quadtree *ne, *nw, *se, *sw;

    void subdivide() {
        double hx = boundary.hw / 2, hy = boundary.hh / 2;
        double cx = boundary.cx, cy = boundary.cy;
        ne = new Quadtree({cx + hx, cy + hy, hx, hy});
        nw = new Quadtree({cx - hx, cy + hy, hx, hy});
        se = new Quadtree({cx + hx, cy - hy, hx, hy});
        sw = new Quadtree({cx - hx, cy - hy, hx, hy});
        divided = true;

        // Re-insert existing points into children
        for (auto& p : points) {
            ne->insert(p); nw->insert(p);
            se->insert(p); sw->insert(p);
        }
        points.clear();
    }

public:
    Quadtree(Rect b) : boundary(b), divided(false), ne(nullptr), nw(nullptr),
                       se(nullptr), sw(nullptr) {}

    ~Quadtree() {
        delete ne; delete nw; delete se; delete sw;
    }

    bool insert(const Point2D& p) {
        if (!boundary.contains(p.x, p.y)) return false; // out of bounds

        if (!divided) {
            if ((int)points.size() < CAPACITY) {
                points.push_back(p);
                return true;
            }
            subdivide();
        }
        return ne->insert(p) || nw->insert(p) ||
               se->insert(p) || sw->insert(p);
    }

    // Find all points within a rectangular range
    void queryRange(const Rect& range, vector<Point2D>& found) const {
        if (!boundary.intersects(range)) return; // prune subtrees out of range

        if (!divided) {
            for (auto& p : points)
                if (range.contains(p.x, p.y)) found.push_back(p);
        } else {
            ne->queryRange(range, found);
            nw->queryRange(range, found);
            se->queryRange(range, found);
            sw->queryRange(range, found);
        }
    }

    int countNodes() const {
        if (!divided) return 1;
        return 1 + ne->countNodes() + nw->countNodes()
                 + se->countNodes() + sw->countNodes();
    }
};

void example5_quadtree_operations() {
    cout << "\n======== Example 5: Quadtree Operations ========\n";

    // 100x100 grid
    Quadtree qt({50, 50, 50, 50});

    // Insert random-ish points
    vector<Point2D> pts = {
        {10,10},{20,20},{30,30},{40,40},{50,50},
        {60,60},{70,70},{80,80},{90,90},{15,85},
        {25,75},{35,65},{45,55},{55,45},{65,35}
    };

    for (auto& p : pts) qt.insert(p);

    cout << "Inserted " << pts.size() << " points\n";
    cout << "Quadtree nodes: " << qt.countNodes() << "\n\n";

    // Range query: points in rectangle [20,70] x [20,70]
    Rect searchArea = {45, 45, 25, 25}; // center (45,45), half-size 25 → [20,70]x[20,70]
    vector<Point2D> found;
    qt.queryRange(searchArea, found);

    cout << "Points in rectangle [20,70] x [20,70]:\n";
    for (auto& p : found)
        cout << "  (" << p.x << ", " << p.y << ")\n";
    cout << "Total found: " << found.size() << "\n";
}

// ========================== PART C: R-TREE (CONCEPTUAL) ======================
void example6_rtree_concept() {
    cout << "\n======== Example 6: R-Tree — Bounding Box Trees ========\n";
    cout << "R-Tree generalizes B-Tree to spatial data using Minimum Bounding Rectangles (MBRs)\n\n";

    cout << "Structure:\n";
    cout << "  - Each leaf stores actual objects (points, polygons, lines)\n";
    cout << "  - Each internal node stores MBRs of its children\n";
    cout << "  - Like B-Tree: all leaves at same depth, pages = disk blocks\n\n";

    cout << "Example (geographic data):\n";
    cout << "  Objects: parks, buildings, roads in a city\n";
    cout << "  L1: MBR of entire city\n";
    cout << "  L2: MBR of each district\n";
    cout << "  L3: MBR of each block\n";
    cout << "  Leaf: individual buildings/parks\n\n";

    cout << "Query 'what's near (lat, lon)?':\n";
    cout << "  - Start at root, only descend into MBRs that overlap query region\n";
    cout << "  - Prune entire subtrees whose MBR doesn't intersect query\n\n";

    cout << "┌──────────────┬───────────────────────────────────────────────────┐\n";
    cout << "│  Feature     │  R-Tree                                           │\n";
    cout << "├──────────────┼───────────────────────────────────────────────────┤\n";
    cout << "│  Best for    │  Spatial objects (polygons, MBRs) not just points │\n";
    cout << "│  Disk-based  │  YES — designed for disk pages (like B-Tree)      │\n";
    cout << "│  Used in     │  PostGIS, MySQL SPATIAL, SQLite R*Tree, MongoDB   │\n";
    cout << "│  Search      │  O(log n) typical (no worst-case guarantee)       │\n";
    cout << "│  Variants    │  R*-Tree (better splits), R+-Tree, Hilbert R-Tree │\n";
    cout << "└──────────────┴───────────────────────────────────────────────────┘\n\n";

    cout << "When to use R-Tree vs KD-Tree vs Quadtree:\n";
    cout << "  R-Tree:   Database/disk storage, polygon objects, production GIS\n";
    cout << "  KD-Tree:  In-memory, points only, ML (k-NN), computational geometry\n";
    cout << "  Quadtree: Game engines, 2D-only, dynamic insertion, Barnes-Hut\n";
}

// ========================== PART D: COMPARISON SUMMARY =====================
void example7_comparison() {
    cout << "\n======== Example 7: Spatial Data Structure Comparison ========\n";
    cout << "┌──────────────┬──────────┬──────────┬──────────┬────────────────┐\n";
    cout << "│              │  KD-Tree │ Quadtree │  R-Tree  │  Notes          │\n";
    cout << "├──────────────┼──────────┼──────────┼──────────┼────────────────┤\n";
    cout << "│  Build time  │ O(nlogn) │ O(nlogn) │ O(nlogn) │                 │\n";
    cout << "│  Space       │  O(n)    │  O(n)    │  O(n)    │                 │\n";
    cout << "│  NN search   │ O(log n) │ O(log n) │ O(log n) │  all avg case   │\n";
    cout << "│  Range       │ O(√n+k)  │ O(√n+k)  │ O(√n+k)  │  2D, k=results  │\n";
    cout << "│  Dimensions  │  Any k   │  2D/3D   │  Any k   │                 │\n";
    cout << "│  Disk-based  │  Poor    │  Poor    │ Excellent│ R-Tree=B-Tree  │\n";
    cout << "│  Polygons    │  No      │  No      │  YES     │                 │\n";
    cout << "│  Dynamic     │  Poor    │  Good    │ Good     │ KD-Tree = batch │\n";
    cout << "│  Impl. ease  │  Medium  │  Easy    │  Hard    │                 │\n";
    cout << "├──────────────┴──────────┴──────────┴──────────┴────────────────┤\n";
    cout << "│  Recommendation:                                                │\n";
    cout << "│  Competitive prog / ML: KD-Tree (simple, in-memory)            │\n";
    cout << "│  Game dev / simulations: Quadtree (easy, 2D, dynamic)          │\n";
    cout << "│  Databases / GIS:        R-Tree (spatial SQL, polygon support)  │\n";
    cout << "└─────────────────────────────────────────────────────────────────┘\n";
}

// =================== EXAMPLE 8: REAL-WORLD KD-TREE USE CASE ================
// k-Nearest Neighbors (k-NN) classification — the core of many ML algorithms

void example8_knn_with_kdtree() {
    cout << "\n======== Example 8: k-NN Classification with KD-Tree ========\n";

    // Training data: (x, y, class)
    // Class 0 = "cat" (clustered around top-left)
    // Class 1 = "dog" (clustered around bottom-right)
    vector<Point2D> training = {
        {1,8,0},{2,7,0},{1,6,0},{3,8,0},{2,9,0}, // cats
        {8,2,1},{9,1,1},{7,3,1},{8,1,1},{9,2,1}  // dogs
    };

    KDTree2D tree(training);

    // Classify new point (2, 7.5)
    Point2D query = {2.0, 7.5};
    Point2D nn = tree.nearestNeighbor(query);

    cout << "Classifying point (2.0, 7.5) using nearest neighbor:\n";
    cout << "  Nearest training point: (" << nn.x << ", " << nn.y << ") class=" << nn.id << "\n";
    cout << "  Prediction: " << (nn.id == 0 ? "cat" : "dog") << "\n\n";

    // For full k-NN, you'd find k nearest neighbors and vote
    auto nearby = tree.rangeQuery(query, 2.5);
    cout << "Points within radius 2.5 of query (for k-NN voting):\n";
    int votes[2] = {0, 0};
    for (auto& p : nearby) {
        if (p.id >= 0 && p.id <= 1) votes[p.id]++;
        cout << "  (" << p.x << ", " << p.y << ") class=" << p.id << "\n";
    }
    cout << "Votes — cat:" << votes[0] << " dog:" << votes[1] << "\n";
    cout << "k-NN Prediction: " << (votes[0] > votes[1] ? "cat" : "dog") << "\n";
}

// =================== EXAMPLE 9: BARNES-HUT QUADTREE SIMULATION ==============
// Famous O(n log n) algorithm for n-body gravity simulation using Quadtree
void example9_barnes_hut_overview() {
    cout << "\n======== Example 9: Barnes-Hut Simulation (Quadtree Application) ========\n";
    cout << "Problem: Simulate gravity between n stars — naive = O(n²) per step\n";
    cout << "Barnes-Hut: O(n log n) per step using Quadtree\n\n";

    cout << "Algorithm:\n";
    cout << "  1. Insert all stars into a Quadtree\n";
    cout << "  2. For each internal node, compute center of mass of its subtree\n";
    cout << "  3. For each star s, compute force from every node:\n";
    cout << "     - If node is a leaf: compute exact force\n";
    cout << "     - If node is far enough (d/w < θ, where θ≈0.5-1.0):\n";
    cout << "       Treat entire subtree as a single mass at center of mass\n";
    cout << "     - Otherwise: recurse into children\n\n";

    cout << "The θ threshold trades accuracy for speed:\n";
    cout << "  θ=0: exact (O(n²))\n";
    cout << "  θ=1: approximate but fast (O(n log n))\n\n";

    cout << "Used in: N-body simulators, SPH (smoothed particle hydrodynamics),\n";
    cout << "         galaxy formation simulations, molecular dynamics\n";
}

// ========================= KEY CONCEPTS BOX ==================================
/*
 ┌─────────────────────────────────────────────────────────────────┐
 │           SPATIAL DATA STRUCTURES KEY CONCEPTS SUMMARY          │
 ├─────────────────────────────────────────────────────────────────┤
 │ KD-Tree:                                                        │
 │   - BST generalized to k dimensions                            │
 │   - Split alternates across dimensions                         │
 │   - NN search: go near side first, check far side if needed    │
 │   - Best for: in-memory points, low dimensions (d ≤ 20)        │
 │                                                                 │
 │ Quadtree:                                                       │
 │   - Divide 2D space into 4 quadrants recursively               │
 │   - Each leaf holds ≤ C points; overflow triggers split        │
 │   - Best for: 2D dynamic data, game engines                    │
 │                                                                 │
 │ R-Tree:                                                         │
 │   - Group objects by Minimum Bounding Rectangles (MBRs)        │
 │   - Disk-based (B-Tree variant for spatial data)               │
 │   - Supports polygon objects, not just points                  │
 │   - Best for: databases, GIS, production spatial applications  │
 │                                                                 │
 │ Curse of Dimensionality:                                        │
 │   All spatial structures degrade for high dimensions (d > 20)  │
 │   Rule: n >> 2^d for good performance                          │
 │   Alternative: approximate NN (FLANN, FAISS for ML)            │
 └─────────────────────────────────────────────────────────────────┘
*/

// ========================= COMMON MISTAKES ===================================
/*
 MISTAKE 1: Checking dist (not dist²) in KD-Tree NN search
   WRONG: if (dist(q, node->point) < bestDist) ...   // sqrt is expensive
   RIGHT: if (dist2(q, node->point) < bestDist2) ... // compare squared distances

 MISTAKE 2: Not pruning the far subtree correctly in KD-Tree
   The pruning condition: only skip the far subtree if
   (splitting_plane_distance)² > bestDist²
   Forgetting this makes it O(n) instead of O(log n).

 MISTAKE 3: Building KD-Tree with points sorted globally (not per-split)
   Must sort/partition only the current subset at each level.
   Use nth_element (O(n)) not full sort (O(n log n)) for optimal build.

 MISTAKE 4: Using KD-Tree for high-dimensional data (d > 20)
   The curse of dimensionality makes KD-Tree degrade to O(n).
   Use FLANN, FAISS (approximate NN) or LSH for high dimensions.

 MISTAKE 5: Quadtree infinite subdivision
   If multiple points have the same coordinates, subdivision never stops.
   Solution: limit max depth OR allow multiple points at the same leaf.

 MISTAKE 6: Rebuilding KD-Tree after every insertion
   KD-Trees are not good for online insertions (they become unbalanced).
   If dynamic insertion is needed, use a KD-Tree with periodic rebuilds,
   or use a Quadtree/R-Tree instead.
*/

// ========================= PRACTICE EXERCISES ================================
/*
 EXERCISE 1:
   Extend the KD-Tree to 3D (x, y, z coordinates).
   Implement build() and nearestNeighbor() for 3D points.
   Test with robot arm positions in 3D workspace.

 EXERCISE 2:
   Implement k-NN search (k nearest neighbors, not just 1):
   Use a max-heap of size k to maintain the k closest points found so far.
   Prune when the splitting plane is farther than the k-th best distance.

 EXERCISE 3:
   Implement a Quadtree that counts how many points are in a circular
   search region (not just rectangular). What changes in the range check?

 EXERCISE 4:
   Implement the Barnes-Hut algorithm concept:
   Build a quadtree with center-of-mass in each internal node.
   For a given star s, compute the total force using the θ threshold.

 EXERCISE 5:
   Given 100,000 random 2D points, benchmark:
   (a) Linear scan nearest neighbor — O(n)
   (b) KD-Tree nearest neighbor — O(log n) expected
   Measure wall-clock time for 1000 queries each.

 EXERCISE 6:
   Implement a spatial hash (alternative to spatial trees):
   Divide space into a grid, hash each cell.
   insert(point), nearestNeighbor(query).
   Compare to KD-Tree: when does the spatial hash win?

 EXERCISE 7:
   Research and explain why R*-Tree is preferred over R-Tree in practice:
   What is the "forced reinsertion" technique in R*-Tree?
   How does it reduce MBR overlap during inserts?

 EXERCISE 8:
   Implement a collision detection system for a 2D game using a Quadtree:
   - 50 moving objects (circles) in a 1000x1000 world
   - Each frame: insert all objects into fresh quadtree
   - Query each object's region to find potential collisions
   Compare to O(n²) brute force for n=50 and n=1000.
*/

int main() {
    cout << "================================================================================\n";
    cout << "     TOPIC 27: ADVANCED DATA STRUCTURES — SPATIAL STRUCTURES                    \n";
    cout << "     KD-Trees, Quadtrees, R-Trees                                               \n";
    cout << "================================================================================\n\n";

    example1_kdtree_idea();
    example2_kdtree_operations();
    example3_kdtree_complexity();
    example4_quadtree_idea();
    example5_quadtree_operations();
    example6_rtree_concept();
    example7_comparison();
    example8_knn_with_kdtree();
    example9_barnes_hut_overview();

    cout << "\n================================================================================\n";
    cout << "                           ALL EXAMPLES COMPLETED                                \n";
    cout << "================================================================================\n";
    return 0;
}

/*
 * EXPECTED OUTPUT:
 * ================================================================================
 *      TOPIC 27: ADVANCED DATA STRUCTURES — SPATIAL STRUCTURES
 *      KD-Trees, Quadtrees, R-Trees
 * ================================================================================
 *
 * ======== Example 1: KD-Tree — The Core Idea ========
 * Problem: Find the nearest coffee shop to your location (x, y)
 * ...
 *
 * ======== Example 2: KD-Tree Build + Nearest Neighbor ========
 * My location: (5, 5)
 * Nearest shop: (5, 4) [or (6,5) depending on build order]
 * Distance: 1
 *
 * Shops within radius 3 of (5,5):
 *   (5, 4) dist=1
 *   (4, 7) dist=2.23607
 *   (6, 5) dist=1
 *   ...
 *
 * ======== Example 5: Quadtree Operations ========
 * Inserted 15 points
 * Quadtree nodes: 5 (varies)
 * Points in rectangle [20,70] x [20,70]:
 *   (20, 20)
 *   (30, 30)
 *   (40, 40)
 *   (50, 50)
 *   (60, 60)
 *   (35, 65)
 *   (45, 55)
 *   (55, 45)
 *   (65, 35)
 * Total found: 9
 *
 * ======== Example 8: k-NN Classification with KD-Tree ========
 * Classifying point (2.0, 7.5) using nearest neighbor:
 *   Nearest training point: (2, 7) class=0
 *   Prediction: cat
 * ...
 */
