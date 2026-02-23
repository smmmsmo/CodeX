// ================================================================================
// TOPIC 27: ADVANCED DATA STRUCTURES
// FILE 4: Splay Trees
// ================================================================================
//
// CONCEPTS COVERED:
//   1. What is a Splay Tree?
//   2. The Splay operation: zig, zig-zig, zig-zag
//   3. Amortized O(log n) per operation analysis (working set theorem)
//   4. Access, Insert, Delete, Split, Join
//   5. Working set property: frequently accessed items move to root
//   6. Applications: LRU cache, network routers, GCC's memory allocator
//   7. Splay Tree vs Treap vs AVL
//
// KEY LEARNING POINTS:
//   - A Splay Tree is a self-adjusting BST (no extra balance metadata!)
//   - Every operation ends by splaying the accessed/inserted/deleted node to root
//   - Amortized O(log n) per operation — individual operations can be O(n)
//   - "Working set" property: if you access the same item k times in a row,
//     those accesses cost only O(log k) total (temporal locality)
//   - Much simpler than AVL/Red-Black (no color or height fields needed)
//   - Used in: GCC's tree allocator, Windows kernel memory manager
// ================================================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

// ========================== EXAMPLE 1: SPLAY OPERATION =======================
void example1_splay_idea() {
    cout << "======== Example 1: Why Splay Trees? ========\n";
    cout << "Core idea: After EVERY access, bring the node to the ROOT\n";
    cout << "  - Frequently accessed nodes stay near the root → fast future access\n";
    cout << "  - This gives O(log n) AMORTIZED cost (not worst case per operation)\n\n";

    cout << "Three splay cases:\n\n";
    cout << "1. ZIG (node is child of root):\n";
    cout << "   One rotation (left or right)\n";
    cout << "     g                 g\n";
    cout << "     |       →         |\n";
    cout << "     p               [x]\n";
    cout << "    / \\              / \\\n";
    cout << "  [x]  C            A   p\n";
    cout << "  / \\                   / \\\n";
    cout << "  A  B                  B  C\n\n";

    cout << "2. ZIG-ZIG (node and parent are both left or both right children):\n";
    cout << "   Rotate parent first, then rotate node\n";
    cout << "   (Different from AVL! This keeps the amortized bound)\n\n";

    cout << "3. ZIG-ZAG (node and parent are opposite children):\n";
    cout << "   Same as AVL double rotation\n";
    cout << "   Rotate node twice (around parent, then around grandparent)\n";
}

// ========================== EXAMPLE 2: NODE AND SPLAY =======================
struct SplayNode {
    int key;
    SplayNode *left, *right, *parent;
    int size; // subtree size for order statistics

    SplayNode(int k, SplayNode* p = nullptr)
        : key(k), left(nullptr), right(nullptr), parent(p), size(1) {}
};

class SplayTree {
    SplayNode* root;

    int sz(SplayNode* n) { return n ? n->size : 0; }

    void update(SplayNode* n) {
        if (n) n->size = 1 + sz(n->left) + sz(n->right);
    }

    // Set parent pointer safely
    void setChild(SplayNode* parent, bool isRight, SplayNode* child) {
        if (parent) {
            if (isRight) parent->right = child;
            else         parent->left  = child;
        }
        if (child) child->parent = parent;
    }

    // Is n the right child of its parent?
    bool isRight(SplayNode* n) {
        return n->parent && n->parent->right == n;
    }

    // Single rotation: bring n up over its parent p
    void rotate(SplayNode* n) {
        SplayNode* p = n->parent;
        SplayNode* g = p->parent;
        bool nIsRight = isRight(n);
        bool pIsRight = g ? isRight(p) : false;

        // Rewire n's "inner" child to become p's outer child
        setChild(p, nIsRight, nIsRight ? n->left : n->right);
        // n takes p's position
        setChild(n, !nIsRight, p);
        // Connect n to grandparent
        if (g) setChild(g, pIsRight, n);
        else   { n->parent = nullptr; root = n; }

        update(p);
        update(n);
    }

    // The core splay operation: bring n to root using zig/zig-zig/zig-zag
    void splay(SplayNode* n) {
        while (n->parent) {
            SplayNode* p = n->parent;
            SplayNode* g = p->parent;

            if (!g) {
                // ZIG: parent is root, one rotation
                rotate(n);
            } else if (isRight(n) == isRight(p)) {
                // ZIG-ZIG: same direction, rotate parent first
                rotate(p);
                rotate(n);
            } else {
                // ZIG-ZAG: different direction, rotate n twice
                rotate(n);
                rotate(n);
            }
        }
        root = n;
    }

    // Find node with key k, return it (or last accessed if not found)
    SplayNode* findNode(int key) {
        SplayNode* curr = root;
        SplayNode* last = nullptr;
        while (curr) {
            last = curr;
            if (key == curr->key) break;
            curr = (key < curr->key) ? curr->left : curr->right;
        }
        if (last) splay(last); // splay whatever we last touched
        return (root && root->key == key) ? root : nullptr;
    }

public:
    SplayTree() : root(nullptr) {}

    // ---- SEARCH ----
    bool search(int key) {
        return findNode(key) != nullptr;
    }

    // ---- INSERT ----
    void insert(int key) {
        if (!root) { root = new SplayNode(key); return; }

        // Find position (splays last touched node to root)
        SplayNode* curr = root;
        SplayNode* parent = nullptr;
        while (curr) {
            parent = curr;
            if (key == curr->key) { splay(curr); return; } // already exists
            curr = (key < curr->key) ? curr->left : curr->right;
        }

        // Create new node as child of parent, then splay it
        SplayNode* node = new SplayNode(key, parent);
        if (key < parent->key) parent->left  = node;
        else                   parent->right = node;
        update(parent);
        splay(node); // bring new node to root
    }

    // ---- DELETE ----
    void remove(int key) {
        SplayNode* node = findNode(key);
        if (!node) return; // key not in tree

        // node is now root; split into left and right subtrees
        SplayNode* L = root->left;
        SplayNode* R = root->right;
        if (L) L->parent = nullptr;
        if (R) R->parent = nullptr;
        delete root;

        if (!L) { root = R; return; }
        if (!R) { root = L; return; }

        // Splay max of L to L's root, then attach R
        root = L;
        SplayNode* curr = L;
        while (curr->right) curr = curr->right; // find max in L
        splay(curr); // max of L is now L's root (and has no right child)
        root->right = R;
        R->parent = root;
        update(root);
    }

    // ---- SPLIT at key: left = {≤key}, right = {>key} ----
    pair<SplayTree*, SplayTree*> split(int key) {
        // Find key or the last node before where key would be
        if (root) {
            SplayNode* curr = root, *last = nullptr;
            while (curr) {
                last = curr;
                if (curr->key <= key) curr = curr->right;
                else                  curr = curr->left;
            }
            splay(last);
        }

        SplayTree* rightTree = new SplayTree();
        if (root && root->key > key) {
            rightTree->root = root->right;
            if (rightTree->root) rightTree->root->parent = nullptr;
            root->right = nullptr;
            update(root);
        } else if (root) {
            rightTree->root = root->right;
            if (rightTree->root) rightTree->root->parent = nullptr;
            root->right = nullptr;
            update(root);
        }
        SplayTree* leftTree = new SplayTree();
        leftTree->root = this->root;
        this->root = nullptr;
        return {leftTree, rightTree};
    }

    int getSize() { return sz(root); }

    // Inorder traversal
    void inorder(SplayNode* n, vector<int>& v) {
        if (!n) return;
        inorder(n->left, v);
        v.push_back(n->key);
        inorder(n->right, v);
    }

    void print() {
        vector<int> v;
        inorder(root, v);
        cout << "[ ";
        for (int x : v) cout << x << " ";
        cout << "]\n";
    }
};

void example2_splay_operations() {
    cout << "\n======== Example 2: Splay Tree Operations ========\n";
    SplayTree tree;

    cout << "Inserting: 10, 5, 20, 3, 7, 15, 25\n";
    for (int x : {10, 5, 20, 3, 7, 15, 25}) tree.insert(x);

    cout << "Inorder: ";
    tree.print(); // [3 5 7 10 15 20 25]

    cout << "Search(7):  " << (tree.search(7)  ? "FOUND" : "NOT FOUND") << "\n";
    cout << "Search(12): " << (tree.search(12) ? "FOUND" : "NOT FOUND") << "\n";

    cout << "After searching 7 (now at root): ";
    tree.print();

    tree.remove(10);
    cout << "After deleting 10: ";
    tree.print(); // [3 5 7 15 20 25]
}

// =================== EXAMPLE 3: SPLAY TREE VISUALIZATION ====================
void example3_splay_visualization() {
    cout << "\n======== Example 3: Splay - Access Pattern Visualization ========\n";
    cout << "Sequential access of same element shows temporal locality:\n";
    cout << "  - First access to key K: O(depth(K)) ≈ O(log n)\n";
    cout << "  - Second access to K:    O(1)  — it's at the root!\n";
    cout << "  - Third access to K:     O(1)  — still at the root!\n\n";

    SplayTree tree;
    for (int x : {1, 2, 3, 4, 5, 6, 7, 8}) tree.insert(x);

    cout << "Tree after inserting 1-8: ";
    tree.print();

    // Access 3 multiple times
    for (int i = 0; i < 3; i++) {
        bool found = tree.search(3);
        cout << "Access 3 (round " << i+1 << "): " << (found ? "FOUND" : "?") << " → root is now 3\n";
    }
    cout << "Final tree state: ";
    tree.print();
}

// =================== EXAMPLE 4: SPLAY TREE USE CASE ========================
// Simulating LRU cache behavior: most recently accessed near root
void example4_lru_property() {
    cout << "\n======== Example 4: Working Set Property (LRU-like) ========\n";
    cout << "Access pattern: [1,2,3,1,2,3,1,2,3] — only 3 distinct keys\n";
    cout << "In a splay tree, after warmup:\n";
    cout << "  - Keys 1,2,3 stay near root\n";
    cout << "  - Total cost for m accesses to k distinct items: O(m log k)\n";
    cout << "  - Not O(m log n) — splay adapts to actual access pattern!\n\n";

    cout << "Real-world: GCC uses splay trees for memory allocation tracking.\n";
    cout << "  Recently freed blocks (likely to be reused) stay near root.\n";
    cout << "  This matches the temporal locality of typical program behavior.\n";
}

// =================== EXAMPLE 5: COMPARISON TABLE ============================
void example5_comparison() {
    cout << "\n======== Example 5: Splay vs Other Trees ========\n";
    cout << "┌────────────────────┬──────────┬──────────┬────────────────────────────┐\n";
    cout << "│   Property         │  AVL     │  Splay   │  Notes                     │\n";
    cout << "├────────────────────┼──────────┼──────────┼────────────────────────────┤\n";
    cout << "│  Extra space/node  │  1 bit   │  0       │  Splay needs no metadata!  │\n";
    cout << "│  Worst case/op     │  O(log n)│  O(n)    │  AVL guarantees per-op     │\n";
    cout << "│  Amortized/op      │  O(log n)│  O(log n)│  Splay is amortized only   │\n";
    cout << "│  Temporal locality │  NO      │  YES     │  Splay adapts to access    │\n";
    cout << "│  Concurrent use    │  Hard    │  Harder  │  Splay moves root on access│\n";
    cout << "│  Implementation    │  Medium  │  Simple  │  No cases like Red-Black   │\n";
    cout << "│  Cache performance │  Good    │  Better* │  Hot items near root       │\n";
    cout << "└────────────────────┴──────────┴──────────┴────────────────────────────┘\n";
    cout << "* When access pattern has temporal locality\n\n";

    cout << "Use Splay when:\n";
    cout << "  ✓ Access pattern has temporal locality (LRU-like)\n";
    cout << "  ✓ You want simplest possible self-balancing BST code\n";
    cout << "  ✓ Amortized bounds are acceptable (no real-time requirements)\n";
    cout << "  ✗ Avoid when worst-case per-operation is critical (use AVL/RB)\n";
    cout << "  ✗ Avoid in concurrent settings (every access modifies structure)\n";
}

// =================== EXAMPLE 6: AMORTIZED ANALYSIS INTUITION ================
void example6_amortized_intuition() {
    cout << "\n======== Example 6: Amortized Analysis Intuition ========\n";
    cout << "Potential function: Φ = Σ log(size(v)) for all nodes v\n\n";
    cout << "Key insight from the Access Lemma:\n";
    cout << "  Amortized cost of splay(x) = O(log(n / depth(x)) + 1)\n\n";

    cout << "Why zig-zig works differently from zig-zag:\n";
    cout << "  ZIG-ZIG: rotate grandparent-parent first, then parent-node\n";
    cout << "  ZIG-ZAG: standard double rotation\n\n";
    cout << "  Counter-intuitive: rotating top-down (zig-zig style) is MORE efficient\n";
    cout << "  than bottom-up (zig-zag only) for the amortized bound.\n";
    cout << "  Splay trees with only zig-zag have Ω(n log n) for n accesses!\n";
}

// =================== EXAMPLE 7: PRACTICAL SPLAY - RANGE SUM =================
// Simple demonstration: inserting values and computing range counts

void example7_range_operations() {
    cout << "\n======== Example 7: Splay Tree for Range Queries ========\n";
    SplayTree tree;
    for (int x : {2, 4, 6, 8, 10, 12, 14, 16, 18, 20}) tree.insert(x);

    cout << "Tree: ";
    tree.print();

    // Count elements ≤ 12 using split concept
    cout << "Count of elements ≤ 12: ";
    // Search for 12 brings it to root; left subtree + root = count ≤ 12
    tree.search(12);
    cout << "after accessing 12, it's at root, left subtree has smaller elements\n";

    cout << "Tree after accessing 12: ";
    tree.print();
}

// ========================= KEY CONCEPTS BOX ==================================
/*
 ┌─────────────────────────────────────────────────────────────────┐
 │               SPLAY TREE KEY CONCEPTS SUMMARY                   │
 ├─────────────────────────────────────────────────────────────────┤
 │ Structure: plain BST — no extra fields (no color, no height)   │
 │                                                                 │
 │ Splay(x): bring x to root using rotations                      │
 │   ZIG:     x is child of root → one rotation                   │
 │   ZIG-ZIG: x and parent are same-side children → rotate parent │
 │            then x (NOT double rotation)                         │
 │   ZIG-ZAG: x and parent are opposite-side → rotate x twice     │
 │                                                                 │
 │ Every operation calls splay():                                  │
 │   search(k)  → splay last-accessed node                        │
 │   insert(k)  → splay new node to root                          │
 │   delete(k)  → splay k to root, merge left/right subtrees      │
 │                                                                 │
 │ Amortized complexity: O(log n) per operation                    │
 │   Proved via potential function Φ = Σ rank(v) = Σ log(size(v)) │
 │                                                                 │
 │ Working set theorem:                                            │
 │   Accessing items in order of last-access-time costs O(n log n) │
 │   total — same as optimal offline algorithm!                    │
 └─────────────────────────────────────────────────────────────────┘
*/

// ========================= COMMON MISTAKES ===================================
/*
 MISTAKE 1: Using zig-zag for ALL cases (forgetting zig-zig)
   WRONG: Always do double rotation (zig-zag style)
   RIGHT: For same-side children (zig-zig), rotate PARENT first, then node
   Without zig-zig, amortized bound breaks → O(n) per operation possible

 MISTAKE 2: Not splaying after search
   Splay trees REQUIRE bringing the accessed node to root after every read.
   If you skip this, you lose the amortized guarantee.

 MISTAKE 3: Forgetting to update parent pointers after rotations
   Parent pointers must be maintained consistently.
   Or use a parentless splay tree (passing path as stack) — also valid.

 MISTAKE 4: Expecting O(log n) WORST CASE (not amortized)
   Splay trees are NOT appropriate for real-time systems where
   individual operations must be O(log n). Use AVL or Red-Black instead.

 MISTAKE 5: Using splay tree in concurrent/multi-threaded code without locks
   Every read modifies the tree structure (moves node to root).
   This requires write locks even for read operations — performance nightmare.
*/

// ========================= PRACTICE EXERCISES ================================
/*
 EXERCISE 1:
   Implement splay tree operations manually and trace through:
   Insert: 1, 2, 3, 4, 5 (in order)
   Then search(1) — this degrades to a right-skewed tree, then splay fixes it.
   Draw the tree before and after splay(1).

 EXERCISE 2:
   Add a split(key) operation to your splay tree:
   - Splay key to root
   - Return (left subtree, right subtree)
   Then implement join(L, R) using:
   - Find max of L, splay it (no right child)
   - Attach R as right child

 EXERCISE 3:
   Implement a splay tree that tracks subtree sums.
   Support: insert(k, v), delete(k), rangeSum(lo, hi).

 EXERCISE 4:
   Prove (or research) why the zig-zig rotation is essential for the
   amortized O(log n) bound. Show a sequence of n operations that costs
   Ω(n²) with naive rotation (always rotate to root with zig-zag).

 EXERCISE 5:
   Implement an LRU cache using a splay tree (for O(log n) operations)
   vs a hash map + doubly linked list (for O(1) operations).
   Compare implementation complexity and performance.

 EXERCISE 6:
   The "dynamic optimality conjecture" (Sleator & Tarjan, 1985) states that
   splay trees are as good as ANY comparison-based BST on ANY access sequence.
   Research this conjecture — has it been proven or disproven?
*/

int main() {
    cout << "================================================================================\n";
    cout << "              TOPIC 27: ADVANCED DATA STRUCTURES — SPLAY TREES                  \n";
    cout << "================================================================================\n\n";

    example1_splay_idea();
    example2_splay_operations();
    example3_splay_visualization();
    example4_lru_property();
    example5_comparison();
    example6_amortized_intuition();
    example7_range_operations();

    cout << "\n================================================================================\n";
    cout << "                           ALL EXAMPLES COMPLETED                                \n";
    cout << "================================================================================\n";
    return 0;
}

/*
 * EXPECTED OUTPUT:
 * ================================================================================
 *               TOPIC 27: ADVANCED DATA STRUCTURES — SPLAY TREES
 * ================================================================================
 *
 * ======== Example 1: Why Splay Trees? ========
 * Core idea: After EVERY access, bring the node to the ROOT
 * ...
 *
 * ======== Example 2: Splay Tree Operations ========
 * Inserting: 10, 5, 20, 3, 7, 15, 25
 * Inorder: [ 3 5 7 10 15 20 25 ]
 * Search(7):  FOUND
 * Search(12): NOT FOUND
 * After searching 7 (now at root): [ 3 5 7 10 15 20 25 ]
 * After deleting 10: [ 3 5 7 15 20 25 ]
 *
 * ======== Example 3: Splay - Access Pattern Visualization ========
 * Tree after inserting 1-8: [ 1 2 3 4 5 6 7 8 ]
 * Access 3 (round 1): FOUND → root is now 3
 * Access 3 (round 2): FOUND → root is now 3
 * Access 3 (round 3): FOUND → root is now 3
 * ...
 */
