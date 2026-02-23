// ================================================================================
// TOPIC 27: ADVANCED DATA STRUCTURES
// FILE 3: Treaps (Tree + Heap)
// ================================================================================
//
// CONCEPTS COVERED:
//   1. What is a Treap?
//   2. Dual invariants: BST on keys + Max-Heap on priorities
//   3. Why random priorities give expected O(log n) height
//   4. Rotation-based insert and delete
//   5. Split and Merge operations (functional style)
//   6. Treap applications: implicit treap, order statistics
//   7. Comparing Treap vs AVL vs Red-Black Tree
//
// KEY LEARNING POINTS:
//   - A Treap is a randomized BST that uses heap priorities to stay balanced
//   - Each node has: key (BST invariant) + priority (heap invariant)
//   - Priorities are assigned randomly → expected O(log n) height
//   - No explicit rebalancing rotations needed; structure emerges naturally
//   - Two implementation styles:
//       1. Rotation-based (simpler, like standard BST)
//       2. Split/Merge-based (more powerful, used in competitive programming)
//   - Implicit Treap (index as key) supports O(log n) array operations
// ================================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

// ========================== EXAMPLE 1: THE CORE IDEA =========================
void example1_treap_idea() {
    cout << "======== Example 1: The Treap Idea ========\n";
    cout << "Treap = BST on keys + Max-Heap on (random) priorities\n\n";
    cout << "Keys:      [3, 1, 4, 1, 5, 9, 2, 6]  ← BST ordering\n";
    cout << "Priorities:[91,29,65,44,88,73,55,82] ← random, heap ordering\n\n";
    cout << "Why does this work?\n";
    cout << "  - If priorities are random, the expected depth of any node = O(log n)\n";
    cout << "  - Theorem: Treap with random priorities has same distribution\n";
    cout << "    as a BST built by inserting keys in RANDOM order\n";
    cout << "  - Random BST has expected O(log n) height\n\n";
    cout << "Structure example (key/priority):\n";
    cout << "           (5, 88)\n";
    cout << "          /       \\\n";
    cout << "      (3, 65)    (9, 73)\n";
    cout << "      /    \\    /\n";
    cout << "   (1,29) (4,44)(6,82)\n";
    cout << "            ↑ Max-heap: parent priority > children priorities\n";
    cout << "            ↑ BST: left < parent < right on keys\n";
}

// ========================== EXAMPLE 2: NODE STRUCTURE ========================

struct TreapNode {
    int key, priority;
    TreapNode *left, *right;
    int size; // for order statistics

    TreapNode(int k) : key(k), priority(rand()), left(nullptr), right(nullptr), size(1) {}
};

int sz(TreapNode* t) { return t ? t->size : 0; }

void update(TreapNode* t) {
    if (t) t->size = 1 + sz(t->left) + sz(t->right);
}

// ========================== EXAMPLE 3: ROTATION-BASED TREAP ==================
// Classic approach: use rotations to fix heap property after BST insert

TreapNode* rotateRight(TreapNode* y) {
    TreapNode* x = y->left;
    y->left = x->right;
    x->right = y;
    update(y);
    update(x);
    return x;
}

TreapNode* rotateLeft(TreapNode* x) {
    TreapNode* y = x->right;
    x->right = y->left;
    y->left = x;
    update(x);
    update(y);
    return y;
}

// Insert: place as a BST leaf, then bubble up with rotations
TreapNode* insert_rotation(TreapNode* root, int key) {
    if (!root) return new TreapNode(key);

    if (key < root->key) {
        root->left = insert_rotation(root->left, key);
        if (root->left->priority > root->priority)
            root = rotateRight(root); // fix heap violation
    } else if (key > root->key) {
        root->right = insert_rotation(root->right, key);
        if (root->right->priority > root->priority)
            root = rotateLeft(root); // fix heap violation
    }
    // key == root->key: duplicate, do nothing
    update(root);
    return root;
}

// Delete: rotate the target down until it's a leaf, then remove
TreapNode* remove_rotation(TreapNode* root, int key) {
    if (!root) return nullptr;

    if (key < root->key)
        root->left = remove_rotation(root->left, key);
    else if (key > root->key)
        root->right = remove_rotation(root->right, key);
    else {
        // Found! Rotate down to leaf
        if (!root->left) {
            TreapNode* tmp = root->right;
            delete root;
            return tmp;
        } else if (!root->right) {
            TreapNode* tmp = root->left;
            delete root;
            return tmp;
        } else {
            // Push down toward lower-priority child
            if (root->left->priority > root->right->priority) {
                root = rotateRight(root);
                root->right = remove_rotation(root->right, key);
            } else {
                root = rotateLeft(root);
                root->left = remove_rotation(root->left, key);
            }
        }
    }
    update(root);
    return root;
}

bool search_treap(TreapNode* root, int key) {
    while (root) {
        if (key == root->key) return true;
        root = (key < root->key) ? root->left : root->right;
    }
    return false;
}

void inorder(TreapNode* root, vector<int>& keys) {
    if (!root) return;
    inorder(root->left, keys);
    keys.push_back(root->key);
    inorder(root->right, keys);
}

void example3_rotation_treap() {
    cout << "\n======== Example 3: Rotation-Based Treap ========\n";
    srand(42);
    TreapNode* root = nullptr;

    for (int x : {5, 3, 8, 1, 4, 7, 9, 2, 6}) {
        root = insert_rotation(root, x);
    }

    vector<int> sorted;
    inorder(root, sorted);
    cout << "Inorder (should be sorted): ";
    for (int x : sorted) cout << x << " ";
    cout << "\n";

    cout << "Search(4): " << (search_treap(root, 4) ? "FOUND" : "NOT FOUND") << "\n";
    cout << "Search(10): " << (search_treap(root, 10) ? "FOUND" : "NOT FOUND") << "\n";

    root = remove_rotation(root, 5);
    sorted.clear();
    inorder(root, sorted);
    cout << "After deleting 5: ";
    for (int x : sorted) cout << x << " ";
    cout << "\n";
}

// ====================== EXAMPLE 4: SPLIT/MERGE TREAP =========================
// More powerful approach used in competitive programming
// Split(t, k) → two treaps: all keys ≤ k, all keys > k
// Merge(L, R) → one treap (all keys in L < all keys in R)

// Split t into (left: keys ≤ key, right: keys > key)
pair<TreapNode*, TreapNode*> split(TreapNode* t, int key) {
    if (!t) return {nullptr, nullptr};

    if (t->key <= key) {
        auto [l, r] = split(t->right, key);
        t->right = l;
        update(t);
        return {t, r};
    } else {
        auto [l, r] = split(t->left, key);
        t->left = r;
        update(t);
        return {l, t};
    }
}

// Merge L and R (all keys in L < all keys in R)
TreapNode* merge(TreapNode* l, TreapNode* r) {
    if (!l) return r;
    if (!r) return l;

    if (l->priority > r->priority) {
        l->right = merge(l->right, r);
        update(l);
        return l;
    } else {
        r->left = merge(l, r->left);
        update(r);
        return r;
    }
}

// Insert using split/merge
TreapNode* insert_sm(TreapNode* t, int key) {
    auto [l, r] = split(t, key - 1);
    TreapNode* node = new TreapNode(key);
    return merge(merge(l, node), r);
}

// Delete using split/merge
TreapNode* remove_sm(TreapNode* t, int key) {
    auto [l, mr] = split(t, key - 1);
    auto [m, r] = split(mr, key);     // m contains exactly nodes with key == key
    delete m; // m is a single node (if key exists)
    return merge(l, r);
}

void example4_split_merge_treap() {
    cout << "\n======== Example 4: Split/Merge Treap ========\n";
    srand(99);
    TreapNode* root = nullptr;

    for (int x : {5, 3, 8, 1, 4, 7, 9}) {
        root = insert_sm(root, x);
    }

    vector<int> keys;
    inorder(root, keys);
    cout << "Inorder: ";
    for (int k : keys) cout << k << " ";
    cout << "\n"; // 1 3 4 5 7 8 9

    // Split at 5: left = {1,3,4,5}, right = {7,8,9}
    auto [left, right] = split(root, 5);

    vector<int> lkeys, rkeys;
    inorder(left, lkeys);
    inorder(right, rkeys);

    cout << "Split at 5:\n";
    cout << "  Left  (≤5): ";
    for (int k : lkeys) cout << k << " ";
    cout << "\n";

    cout << "  Right (>5): ";
    for (int k : rkeys) cout << k << " ";
    cout << "\n";

    // Merge back
    root = merge(left, right);
    keys.clear();
    inorder(root, keys);
    cout << "After merging back: ";
    for (int k : keys) cout << k << " ";
    cout << "\n"; // 1 3 4 5 7 8 9
}

// ==================== EXAMPLE 5: ORDER STATISTICS TREAP ======================
// kth smallest element and rank of a key — O(log n)

int kthSmallest(TreapNode* t, int k) {
    if (!t) return -1;
    int leftSize = sz(t->left);
    if (k == leftSize + 1) return t->key;
    if (k <= leftSize) return kthSmallest(t->left, k);
    return kthSmallest(t->right, k - leftSize - 1);
}

int rank_of(TreapNode* t, int key) {
    if (!t) return 0;
    if (key == t->key) return sz(t->left) + 1;
    if (key < t->key)  return rank_of(t->left, key);
    return sz(t->left) + 1 + rank_of(t->right, key);
}

void example5_order_statistics() {
    cout << "\n======== Example 5: Order Statistics ========\n";
    srand(77);
    TreapNode* root = nullptr;
    for (int x : {10, 20, 30, 40, 50, 60, 70}) root = insert_sm(root, x);

    cout << "Tree (sorted): 10 20 30 40 50 60 70\n";
    cout << "3rd smallest:  " << kthSmallest(root, 3) << "\n"; // 30
    cout << "5th smallest:  " << kthSmallest(root, 5) << "\n"; // 50
    cout << "Rank of 40:    " << rank_of(root, 40) << "\n";     // 4
    cout << "Rank of 10:    " << rank_of(root, 10) << "\n";     // 1
    cout << "Rank of 70:    " << rank_of(root, 70) << "\n";     // 7
}

// ==================== EXAMPLE 6: IMPLICIT TREAP ==============================
// Use index (position) as key instead of actual key values
// Supports O(log n) array operations: insert at position, delete at position,
// reverse a range, sum a range, etc.

struct ImplicitNode {
    int val, priority, size;
    bool rev; // lazy reversal flag
    ImplicitNode *left, *right;
    ImplicitNode(int v) : val(v), priority(rand()), size(1), rev(false),
                          left(nullptr), right(nullptr) {}
};

int isz(ImplicitNode* t) { return t ? t->size : 0; }

void iupdate(ImplicitNode* t) {
    if (t) t->size = 1 + isz(t->left) + isz(t->right);
}

void push(ImplicitNode* t) {
    if (t && t->rev) {
        swap(t->left, t->right);
        if (t->left)  t->left->rev  ^= 1;
        if (t->right) t->right->rev ^= 1;
        t->rev = false;
    }
}

// Split by position: left has first k elements
pair<ImplicitNode*, ImplicitNode*> isplit(ImplicitNode* t, int k) {
    if (!t) return {nullptr, nullptr};
    push(t);
    int leftSize = isz(t->left);
    if (leftSize >= k) {
        auto [l, r] = isplit(t->left, k);
        t->left = r;
        iupdate(t);
        return {l, t};
    } else {
        auto [l, r] = isplit(t->right, k - leftSize - 1);
        t->right = l;
        iupdate(t);
        return {t, r};
    }
}

ImplicitNode* imerge(ImplicitNode* l, ImplicitNode* r) {
    if (!l) return r;
    if (!r) return l;
    push(l); push(r);
    if (l->priority > r->priority) {
        l->right = imerge(l->right, r);
        iupdate(l);
        return l;
    } else {
        r->left = imerge(l, r->left);
        iupdate(r);
        return r;
    }
}

void reverseRange(ImplicitNode*& t, int l, int r) { // 0-indexed, [l, r]
    auto [left, mr] = isplit(t, l);
    auto [mid, right] = isplit(mr, r - l + 1);
    mid->rev ^= 1; // mark entire segment for lazy reversal
    t = imerge(imerge(left, mid), right);
}

void printTree(ImplicitNode* t) {
    if (!t) return;
    push(t);
    printTree(t->left);
    cout << t->val << " ";
    printTree(t->right);
}

void example6_implicit_treap() {
    cout << "\n======== Example 6: Implicit Treap (Rope) ========\n";
    srand(55);
    ImplicitNode* root = nullptr;

    // Build array [1, 2, 3, 4, 5, 6, 7]
    for (int i = 1; i <= 7; i++) {
        ImplicitNode* node = new ImplicitNode(i);
        root = imerge(root, node);
    }

    cout << "Initial: ";
    printTree(root);
    cout << "\n"; // 1 2 3 4 5 6 7

    // Reverse range [1, 4] (0-indexed) → positions 1..4 reversed
    reverseRange(root, 1, 4);
    cout << "After reverse [1,4]: ";
    printTree(root);
    cout << "\n"; // 1 5 4 3 2 6 7
}

// ==================== EXAMPLE 7: COMPLEXITY SUMMARY =========================
void example7_complexity() {
    cout << "\n======== Example 7: Treap vs Other BSTs ========\n";
    cout << "┌────────────────┬──────────┬──────────┬──────────┬──────────────┐\n";
    cout << "│  Tree Type     │  Search  │  Insert  │  Delete  │  Notes       │\n";
    cout << "├────────────────┼──────────┼──────────┼──────────┼──────────────┤\n";
    cout << "│  Plain BST     │  O(n)*   │  O(n)*   │  O(n)*   │  Unbalanced  │\n";
    cout << "│  AVL Tree      │  O(log n)│  O(log n)│  O(log n)│  Strict bal  │\n";
    cout << "│  Red-Black     │  O(log n)│  O(log n)│  O(log n)│  Loose bal   │\n";
    cout << "│  Treap         │  O(log n)│  O(log n)│  O(log n)│  Probabilist │\n";
    cout << "│  Skip List     │  O(log n)│  O(log n)│  O(log n)│  Probabilist │\n";
    cout << "├────────────────┴──────────┴──────────┴──────────┴──────────────┤\n";
    cout << "│  * = expected/average (worst case O(n) for Treap is negligible) │\n";
    cout << "│  Treap advantages: simpler code, no rebalancing case analysis   │\n";
    cout << "│  Split/Merge enables range operations that other BSTs can't do  │\n";
    cout << "└─────────────────────────────────────────────────────────────────┘\n";
}

// ========================= KEY CONCEPTS BOX ==================================
/*
 ┌─────────────────────────────────────────────────────────────────┐
 │                 TREAP KEY CONCEPTS SUMMARY                      │
 ├─────────────────────────────────────────────────────────────────┤
 │ Node: (key, random_priority, left, right)                       │
 │                                                                 │
 │ Invariants:                                                     │
 │   BST: left->key < node->key < right->key                      │
 │   Heap: node->priority > left->priority                        │
 │          node->priority > right->priority                      │
 │                                                                 │
 │ Two styles:                                                     │
 │   Rotation-based: insert/delete with up/down rotations         │
 │   Split/Merge: more flexible, enables range operations         │
 │                                                                 │
 │ Power of Split/Merge:                                           │
 │   insert(t, k) = merge(merge(split(t,k-1).left, new_node),    │
 │                        split(t,k-1).right)                     │
 │   delete(t, k) = merge(split(t,k-1).left,                     │
 │                        split(split(t,k).right).right)          │
 │   reverse [l,r] = lazy flag on subtree                        │
 │   sum [l,r] = subtree aggregate                                │
 │                                                                 │
 │ Implicit Treap (Rope):                                          │
 │   Position = key → dynamic array with O(log n) ops            │
 │   Used in text editors, competitive programming                │
 └─────────────────────────────────────────────────────────────────┘
*/

// ========================= COMMON MISTAKES ===================================
/*
 MISTAKE 1: Using the same priority for all nodes
   Priority MUST be random! Otherwise heap property gives no balancing benefit.
   Each priority should be drawn uniformly at random.

 MISTAKE 2: Forgetting to update sizes after rotations/splits/merges
   Always call update(node) after modifying children.
   Missing this breaks order statistics (kth, rank).

 MISTAKE 3: Forgetting push() before accessing children in implicit treap
   Lazy reversal only works if you push down the flag BEFORE accessing children.

 MISTAKE 4: Split boundary off-by-one
   "split(t, k)" should clearly define: does it split into (≤k, >k)?
   Or (first k elements, rest)? Be consistent and document clearly.

 MISTAKE 5: Memory leaks during delete
   Both rotation-based and split/merge delete must free the removed node.
*/

// ========================= PRACTICE EXERCISES ================================
/*
 EXERCISE 1:
   Implement a Treap that supports:
   - insert(key)
   - delete(key)
   - kthSmallest(k) — return k-th smallest key
   Test with: insert 10,20,30,40,50 → kthSmallest(3) = 30

 EXERCISE 2:
   Implement countLess(key) — number of keys strictly less than key.
   Use the size field. Time complexity: O(log n).

 EXERCISE 3:
   Using Implicit Treap, implement:
   - insertAt(pos, val)   — insert val at 0-indexed position pos
   - deleteAt(pos)        — delete element at position pos
   - getAt(pos)           — retrieve element at position pos
   - reverseRange(l, r)   — reverse elements in [l, r]

 EXERCISE 4:
   Solve "K-th Largest Element in a Stream" using a Treap.
   For each new element, insert it and return the k-th largest.

 EXERCISE 5:
   Implement a Treap supporting:
   - rangeSum(l, r) — sum of all values in [l, r]
   Use a sum aggregate field in each node, updated like size.

 EXERCISE 6:
   Show that the expected depth of any key in a treap with random priorities
   is O(log n). Hint: Think about the probability that key i is an ancestor of key j.
*/

int main() {
    cout << "================================================================================\n";
    cout << "              TOPIC 27: ADVANCED DATA STRUCTURES — TREAPS                       \n";
    cout << "================================================================================\n\n";

    example1_treap_idea();
    example3_rotation_treap();
    example4_split_merge_treap();
    example5_order_statistics();
    example6_implicit_treap();
    example7_complexity();

    cout << "\n================================================================================\n";
    cout << "                           ALL EXAMPLES COMPLETED                                \n";
    cout << "================================================================================\n";
    return 0;
}

/*
 * EXPECTED OUTPUT:
 * ================================================================================
 *               TOPIC 27: ADVANCED DATA STRUCTURES — TREAPS
 * ================================================================================
 *
 * ======== Example 1: The Treap Idea ========
 * Treap = BST on keys + Max-Heap on (random) priorities
 * ...
 *
 * ======== Example 3: Rotation-Based Treap ========
 * Inorder (should be sorted): 1 2 3 4 5 6 7 8 9
 * Search(4): FOUND
 * Search(10): NOT FOUND
 * After deleting 5: 1 2 3 4 6 7 8 9
 *
 * ======== Example 4: Split/Merge Treap ========
 * Inorder: 1 3 4 5 7 8 9
 * Split at 5:
 *   Left  (≤5): 1 3 4 5
 *   Right (>5): 7 8 9
 * After merging back: 1 3 4 5 7 8 9
 *
 * ======== Example 5: Order Statistics ========
 * Tree (sorted): 10 20 30 40 50 60 70
 * 3rd smallest:  30
 * 5th smallest:  50
 * Rank of 40:    4
 * Rank of 10:    1
 * Rank of 70:    7
 *
 * ======== Example 6: Implicit Treap (Rope) ========
 * Initial: 1 2 3 4 5 6 7
 * After reverse [1,4]: 1 5 4 3 2 6 7
 */
