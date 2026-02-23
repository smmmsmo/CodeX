// ================================================================================
// TOPIC 27: ADVANCED DATA STRUCTURES
// FILE 2: Skip Lists
// ================================================================================
//
// CONCEPTS COVERED:
//   1. What is a Skip List?
//   2. Motivation: limitations of sorted linked lists
//   3. Multi-level structure and probabilistic balancing
//   4. Search algorithm — O(log n) expected
//   5. Insertion with random level generation
//   6. Deletion
//   7. Skip list vs BST comparison
//   8. Concurrent skip lists (brief overview)
//
// KEY LEARNING POINTS:
//   - A skip list is a probabilistic data structure that allows O(log n)
//     search, insert, and delete on average without the complex rotations of BSTs
//   - It uses multiple "express lanes" (higher levels) to skip over many elements
//   - Each node is promoted to higher levels with probability p (typically 0.5)
//   - Expected height of a node: 1/(1-p) levels; max useful height ≈ log_{1/p}(n)
//   - Used in Redis (sorted sets), Java ConcurrentSkipListMap, LevelDB
// ================================================================================

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <string>
#include <iomanip>
using namespace std;

// ========================== EXAMPLE 1: MOTIVATION ============================
// Why not just a sorted linked list?
// - Search: O(n)  — must scan linearly
// - Insert: O(n)  — must find position
// - Delete: O(n)
// Skip lists solve this with "express lanes"

void example1_motivation() {
    cout << "======== Example 1: Motivation — Why Skip Lists? ========\n";
    cout << "Sorted Linked List: [1] -> [3] -> [7] -> [12] -> [19] -> [26] -> [37] -> [55]\n";
    cout << "Search for 37: must walk from 1, touching ALL 7 nodes before 37\n\n";

    cout << "Skip List with express lanes:\n";
    cout << "L2: [1] -----------------------> [19] -----------------------> [55]\n";
    cout << "L1: [1] --------> [7] --------> [19] --------> [37] --------> [55]\n";
    cout << "L0: [1] -> [3] -> [7] -> [12] -> [19] -> [26] -> [37] -> [55]\n\n";
    cout << "Search for 37:\n";
    cout << "  L2: 1 -> 19 (skip 2 nodes!), 19 < 37, continue\n";
    cout << "  L1: 19 -> 37 (found at L1, just 1 step)\n";
    cout << "  Total: 3 comparisons instead of 7\n";
}

// ========================== EXAMPLE 2: SKIP LIST NODE ========================
const int MAX_LEVEL = 16;
const double PROBABILITY = 0.5;

struct SkipNode {
    int key;
    int value;
    vector<SkipNode*> forward; // forward[i] = pointer to next node at level i

    SkipNode(int key, int val, int level)
        : key(key), value(val), forward(level + 1, nullptr) {}
};

// ========================== EXAMPLE 3: SKIP LIST CLASS =======================

class SkipList {
    SkipNode* header;  // sentinel head (key = INT_MIN)
    int level;         // current maximum level in use
    int nodeCount;

    // Coin-flip: returns a random level for a new node
    int randomLevel() {
        int lvl = 0;
        while ((double)rand() / RAND_MAX < PROBABILITY && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }

public:
    SkipList() : level(0), nodeCount(0) {
        header = new SkipNode(INT_MIN, 0, MAX_LEVEL);
    }

    ~SkipList() {
        SkipNode* curr = header;
        while (curr) {
            SkipNode* next = curr->forward[0];
            delete curr;
            curr = next;
        }
    }

    // ---- SEARCH: O(log n) expected ----
    // Start at top level, move right while next key < target,
    // then drop down one level. Repeat until level 0.
    bool search(int key) {
        SkipNode* curr = header;
        for (int i = level; i >= 0; i--) {
            while (curr->forward[i] && curr->forward[i]->key < key)
                curr = curr->forward[i]; // advance right
        }
        curr = curr->forward[0]; // move to actual candidate
        return curr && curr->key == key;
    }

    int getValue(int key) {
        SkipNode* curr = header;
        for (int i = level; i >= 0; i--)
            while (curr->forward[i] && curr->forward[i]->key < key)
                curr = curr->forward[i];
        curr = curr->forward[0];
        if (curr && curr->key == key) return curr->value;
        return -1; // not found
    }

    // ---- INSERT: O(log n) expected ----
    // Find update[] = nodes that need their forward pointers updated
    void insert(int key, int value) {
        vector<SkipNode*> update(MAX_LEVEL + 1, nullptr);
        SkipNode* curr = header;

        // Find insert position at each level, record predecessors
        for (int i = level; i >= 0; i--) {
            while (curr->forward[i] && curr->forward[i]->key < key)
                curr = curr->forward[i];
            update[i] = curr;
        }

        curr = curr->forward[0];

        // Update value if key already exists
        if (curr && curr->key == key) {
            curr->value = value;
            return;
        }

        int newLevel = randomLevel();

        // If new level exceeds current max, extend update[] with header
        if (newLevel > level) {
            for (int i = level + 1; i <= newLevel; i++)
                update[i] = header;
            level = newLevel;
        }

        // Create new node and splice into the list at each level
        SkipNode* newNode = new SkipNode(key, value, newLevel);
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
        nodeCount++;
    }

    // ---- DELETE: O(log n) expected ----
    void remove(int key) {
        vector<SkipNode*> update(MAX_LEVEL + 1, nullptr);
        SkipNode* curr = header;

        for (int i = level; i >= 0; i--) {
            while (curr->forward[i] && curr->forward[i]->key < key)
                curr = curr->forward[i];
            update[i] = curr;
        }

        curr = curr->forward[0];
        if (!curr || curr->key != key) return; // not found

        // Unlink the node at each level
        for (int i = 0; i <= level; i++) {
            if (update[i]->forward[i] != curr) break;
            update[i]->forward[i] = curr->forward[i];
        }

        // Shrink level if top levels are now empty
        while (level > 0 && header->forward[level] == nullptr)
            level--;

        delete curr;
        nodeCount--;
    }

    // ---- RANGE QUERY: O(log n + k) ----
    // Find all keys in [lo, hi]
    vector<pair<int,int>> rangeQuery(int lo, int hi) {
        vector<pair<int,int>> result;
        SkipNode* curr = header;

        for (int i = level; i >= 0; i--)
            while (curr->forward[i] && curr->forward[i]->key < lo)
                curr = curr->forward[i];

        curr = curr->forward[0];
        while (curr && curr->key <= hi) {
            result.push_back({curr->key, curr->value});
            curr = curr->forward[0];
        }
        return result;
    }

    // Print the skip list structure (for visualization)
    void print() {
        cout << "Skip List Structure:\n";
        for (int i = level; i >= 0; i--) {
            cout << "L" << i << ": ";
            SkipNode* curr = header->forward[i];
            while (curr) {
                cout << "[" << curr->key << "] -> ";
                curr = curr->forward[i];
            }
            cout << "NULL\n";
        }
        cout << "Total nodes: " << nodeCount << "\n";
    }

    int size() const { return nodeCount; }
};

void example2_skip_list_operations() {
    cout << "\n======== Example 2: Skip List Operations ========\n";
    srand(42); // fixed seed for reproducibility

    SkipList sl;
    sl.insert(3, 30);
    sl.insert(6, 60);
    sl.insert(7, 70);
    sl.insert(9, 90);
    sl.insert(12, 120);
    sl.insert(19, 190);
    sl.insert(17, 170);
    sl.insert(26, 260);

    sl.print();

    cout << "\nSearch(6):  " << (sl.search(6)  ? "FOUND" : "NOT FOUND") << "\n";
    cout << "Search(10): " << (sl.search(10) ? "FOUND" : "NOT FOUND") << "\n";
    cout << "Value(19):  " << sl.getValue(19) << "\n"; // 190
}

void example3_skip_list_delete() {
    cout << "\n======== Example 3: Skip List Delete ========\n";
    srand(123);

    SkipList sl;
    for (int x : {5, 10, 15, 20, 25, 30}) sl.insert(x, x * 10);

    cout << "Before deletion:\n";
    sl.print();

    sl.remove(15);
    sl.remove(25);

    cout << "\nAfter deleting 15 and 25:\n";
    sl.print();
    cout << "Search(15): " << (sl.search(15) ? "FOUND" : "NOT FOUND") << "\n"; // NOT FOUND
}

void example4_range_query() {
    cout << "\n======== Example 4: Range Query [lo, hi] ========\n";
    srand(7);
    SkipList sl;
    for (int i = 1; i <= 20; i++) sl.insert(i * 3, i); // 3,6,9,...,60

    auto result = sl.rangeQuery(10, 30);
    cout << "Keys in range [10, 30]: ";
    for (auto [k, v] : result)
        cout << k << "(" << v << ") ";
    cout << "\n"; // 12(4) 15(5) 18(6) 21(7) 24(8) 27(9) 30(10)
}

// ========================== EXAMPLE 5: PERFORMANCE PROFILE ===================
void example5_performance() {
    cout << "\n======== Example 5: Performance Characteristics ========\n";
    cout << "┌──────────────┬────────────────┬────────────────┬────────────────┐\n";
    cout << "│  Operation   │  Skip List     │  Sorted Array  │  BST (avg)     │\n";
    cout << "├──────────────┼────────────────┼────────────────┼────────────────┤\n";
    cout << "│  Search      │  O(log n)      │  O(log n)      │  O(log n)      │\n";
    cout << "│  Insert      │  O(log n)      │  O(n)          │  O(log n)      │\n";
    cout << "│  Delete      │  O(log n)      │  O(n)          │  O(log n)      │\n";
    cout << "│  Range Query │  O(log n + k)  │  O(log n + k)  │  O(log n + k)  │\n";
    cout << "│  Space       │  O(n) expected │  O(n)          │  O(n)          │\n";
    cout << "│  Worst Case  │  O(n)*         │  -             │  O(n)          │\n";
    cout << "│  Lock-free   │  YES (natural) │  Difficult     │  Difficult     │\n";
    cout << "└──────────────┴────────────────┴────────────────┴────────────────┘\n";
    cout << "* Extremely rare — same probability as all coin flips being heads\n";
    cout << "\nReal-world usage:\n";
    cout << "  Redis ZSET (sorted sets)          → skip list\n";
    cout << "  Java ConcurrentSkipListMap         → skip list (lock-free)\n";
    cout << "  LevelDB (Google's key-value store) → skip list for memtable\n";
}

// ========================== EXAMPLE 6: STL ALTERNATIVE ======================
// In practice, use std::map or std::set (Red-Black Tree internally)
// Skip lists shine when:
//   1. You need concurrent access (lock-free skip lists > lock-based BSTs)
//   2. You want simpler implementation than AVL/Red-Black trees
//   3. You need cache-friendly sequential access (L0 is a plain linked list)

#include <map>
#include <set>

void example6_stl_alternative() {
    cout << "\n======== Example 6: STL Equivalent (std::map) ========\n";

    map<int, int> m;
    for (int i : {5, 3, 9, 1, 7}) m[i] = i * 10;

    cout << "map contents (sorted): ";
    for (auto [k, v] : m) cout << k << ":" << v << " ";
    cout << "\n";

    // Range query equivalent
    cout << "Keys in [3, 7]: ";
    auto lo = m.lower_bound(3);
    auto hi = m.upper_bound(7);
    for (auto it = lo; it != hi; ++it)
        cout << it->first << " ";
    cout << "\n";
    // std::map uses Red-Black Tree, not skip list
    // But semantics are identical to a skip list map
}

// ========================== KEY CONCEPTS BOX ==================================
/*
 ┌─────────────────────────────────────────────────────────────────┐
 │               SKIP LIST KEY CONCEPTS SUMMARY                    │
 ├─────────────────────────────────────────────────────────────────┤
 │ Structure: Multiple levels of linked lists                      │
 │   L0: complete sorted linked list (all elements)               │
 │   L1: ~n/2 elements (promoted with probability p=0.5)          │
 │   L2: ~n/4 elements                                            │
 │   ...                                                           │
 │   Lk: ~n/2^k elements                                          │
 │                                                                 │
 │ Node structure:                                                 │
 │   key, value, forward[MAX_LEVEL]                               │
 │                                                                 │
 │ Algorithm: Start high, go right, drop down                      │
 │                                                                 │
 │ Complexity (expected):                                          │
 │   Search / Insert / Delete → O(log n)                          │
 │   Space → O(n) expected (each node has avg 2 pointers)        │
 │                                                                 │
 │ Advantages over BSTs:                                           │
 │   ✓ Simpler implementation                                     │
 │   ✓ Better cache performance for range queries                 │
 │   ✓ Easy lock-free concurrent implementation                   │
 │   ✓ No rotations needed                                        │
 │                                                                 │
 │ Disadvantages:                                                  │
 │   ✗ Probabilistic (not guaranteed O(log n))                    │
 │   ✗ Higher memory per node than balanced BST                   │
 │   ✗ Random number generation overhead                          │
 └─────────────────────────────────────────────────────────────────┘
*/

// ========================= COMMON MISTAKES ===================================
/*
 MISTAKE 1: Forgetting to update forward pointers at ALL levels
   During insert/delete, must update pointers at every level
   where the predecessor changes.

 MISTAKE 2: Setting MAX_LEVEL too low or too high
   Recommended: MAX_LEVEL = ceil(log_{1/p}(n))
   For p=0.5, n=10^6: MAX_LEVEL = 20
   Too low → long chains, poor performance
   Too high → wasted memory, no benefit

 MISTAKE 3: Not handling the header sentinel correctly
   Header key must be less than all real keys (INT_MIN)
   so that the while-loop terminates correctly

 MISTAKE 4: Searching from level 0 instead of current max level
   Always start from the CURRENT level, not MAX_LEVEL:
   for (int i = level; i >= 0; i--) // not MAX_LEVEL
*/

// ========================= PRACTICE EXERCISES ================================
/*
 EXERCISE 1:
   Implement a skip list that stores strings as keys.
   Add an iterator that traverses all elements in sorted order.

 EXERCISE 2:
   Implement findMin() and findMax() operations in O(1).
   Hint: L0's first/last nodes.

 EXERCISE 3:
   Implement floor(x) — largest key ≤ x
   and ceil(x) — smallest key ≥ x

 EXERCISE 4:
   Implement countRange(lo, hi) — number of elements in [lo, hi]
   in O(log n + k) time.

 EXERCISE 5:
   Modify the skip list to support duplicate keys (multimap behavior).

 EXERCISE 6:
   Implement rank(key) — return the position (1-indexed) of key
   in sorted order. Hint: Store "span" in each forward pointer.
   This is how Redis implements ZRANK.

 EXERCISE 7:
   Profile your skip list against std::map for 10^5 operations.
   Measure insertion time and search time.
*/

int main() {
    cout << "================================================================================\n";
    cout << "              TOPIC 27: ADVANCED DATA STRUCTURES — SKIP LISTS                   \n";
    cout << "================================================================================\n\n";

    example1_motivation();
    example2_skip_list_operations();
    example3_skip_list_delete();
    example4_range_query();
    example5_performance();
    example6_stl_alternative();

    cout << "\n================================================================================\n";
    cout << "                           ALL EXAMPLES COMPLETED                                \n";
    cout << "================================================================================\n";
    return 0;
}

/*
 * EXPECTED OUTPUT (structure varies by random seed):
 * ================================================================================
 *               TOPIC 27: ADVANCED DATA STRUCTURES — SKIP LISTS
 * ================================================================================
 *
 * ======== Example 1: Motivation — Why Skip Lists? ========
 * Sorted Linked List: [1] -> [3] -> [7] -> [12] -> [19] -> [26] -> [37] -> [55]
 * Search for 37: must walk from 1, touching ALL 7 nodes before 37
 *
 * Skip List with express lanes:
 * L2: [1] -----------------------> [19] -----------------------> [55]
 * ...
 *
 * ======== Example 2: Skip List Operations ========
 * Skip List Structure:
 * L1: [3] -> [6] -> [17] -> NULL
 * L0: [3] -> [6] -> [7] -> [9] -> [12] -> [17] -> [19] -> [26] -> NULL
 * Total nodes: 8
 *
 * Search(6):  FOUND
 * Search(10): NOT FOUND
 * Value(19):  190
 * ...
 */
