/*
================================================================================
  TOPIC 25.1: ADVANCED TREES - TRIES, SEGMENT TREES, FENWICK TREES
        Part 4: Data Structures - Non-Linear Data Structures
================================================================================

CONCEPT BREAKDOWN:
1. Trie (Prefix Tree) structure and operations
2. Trie applications (autocomplete, spell check)
3. Segment Trees for range queries
4. Fenwick Trees (Binary Indexed Trees)
5. Use cases and performance comparison
6. Implementation patterns

KEY LEARNING POINTS:
- Tries efficient for prefix-based searching
- Segment trees excellent for range queries
- Fenwick trees memory-efficient for range queries
- Each has specific use cases and tradeoffs
- Foundation for competitive programming

================================================================================
                             SECTION 1: THEORY
================================================================================

1. TRIE (PREFIX TREE):
   - Tree structure for efficient prefix searches
   - Each path from root represents a string
   - Common for: autocomplete, spell check, IP routing
   - Time: O(k) where k = string length
   - Space: O(ALPHABET_SIZE * N)

2. SEGMENT TREE:
   - Binary tree for range queries
   - Each node represents range [l, r]
   - Supports: range sum, range min/max, updates
   - Time: O(log n) queries and updates
   - Space: O(n)
   - Applications: competitive programming, range queries

3. FENWICK TREE (Binary Indexed Tree):
   - Space-efficient alternative to segment tree
   - Uses bit manipulation for indexing
   - Time: O(log n) queries and updates
   - Space: O(n)
   - Better cache locality than segment trees
   - Simpler to implement

4. COMPARISON:
   Trie: String searching, prefix matching
   Segment Tree: General range queries, flexible operations
   Fenwick Tree: Range queries (sum, XOR), memory efficient

5. BIT (FENWICK) TREE STRUCTURE:
   - Array-based representation
   - Index i's responsibility: i & (i+1) elements
   - Update: Add i & (-i) to index
   - Query: Subtract i & (-i) from index

================================================================================
                         SECTION 2: CODE EXAMPLES
================================================================================

*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;

// ======================= TRIE NODE =======================
struct TrieNode {
  unordered_map<char, TrieNode *> children;
  bool isEndOfWord;

  TrieNode() : isEndOfWord(false) {}
};

// ======================= TRIE IMPLEMENTATION =======================
class Trie {
private:
  TrieNode *root;

public:
  Trie() { root = new TrieNode(); }

  // ======================= INSERT WORD =======================
  void insert(const string &word) {
    TrieNode *node = root;

    for (char ch : word) {
      if (node->children.find(ch) == node->children.end()) {
        node->children[ch] = new TrieNode();
      }
      node = node->children[ch];
    }

    node->isEndOfWord = true;
  }

  // ======================= SEARCH EXACT WORD =======================
  bool search(const string &word) {
    TrieNode *node = root;

    for (char ch : word) {
      if (node->children.find(ch) == node->children.end()) {
        return false;
      }
      node = node->children[ch];
    }

    return node->isEndOfWord;
  }

  // ======================= SEARCH PREFIX =======================
  bool startsWith(const string &prefix) {
    TrieNode *node = root;

    for (char ch : prefix) {
      if (node->children.find(ch) == node->children.end()) {
        return false;
      }
      node = node->children[ch];
    }

    return true;
  }

  // ======================= GET WORDS WITH PREFIX =======================
  void getWordsWithPrefix(const string &prefix, TrieNode *node,
                          string &current) {
    if (node == nullptr)
      return;

    if (node->isEndOfWord) {
      cout << current << " ";
    }

    for (auto &p : node->children) {
      current.push_back(p.first);
      getWordsWithPrefix(prefix, p.second, current);
      current.pop_back();
    }
  }

  void autocomplete(const string &prefix) {
    TrieNode *node = root;

    for (char ch : prefix) {
      if (node->children.find(ch) == node->children.end()) {
        cout << "No suggestions" << endl;
        return;
      }
      node = node->children[ch];
    }

    cout << "Suggestions for '" << prefix << "': ";
    string current = prefix;
    getWordsWithPrefix(prefix, node, current);
    cout << endl;
  }
};

// ======================= SEGMENT TREE =======================
class SegmentTree {
private:
  vector<int> tree;
  int n;

  void build(vector<int> &arr, int node, int start, int end) {
    if (start == end) {
      tree[node] = arr[start];
    } else {
      int mid = (start + end) / 2;
      build(arr, 2 * node, start, mid);
      build(arr, 2 * node + 1, mid + 1, end);
      tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
  }

  void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
      tree[node] = val;
    } else {
      int mid = (start + end) / 2;
      if (idx <= mid) {
        update(2 * node, start, mid, idx, val);
      } else {
        update(2 * node + 1, mid + 1, end, idx, val);
      }
      tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
  }

  int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
      return 0;
    }

    if (l <= start && end <= r) {
      return tree[node];
    }

    int mid = (start + end) / 2;
    return query(2 * node, start, mid, l, r) +
           query(2 * node + 1, mid + 1, end, l, r);
  }

public:
  SegmentTree(vector<int> &arr) {
    n = arr.size();
    tree.resize(4 * n);
    build(arr, 1, 0, n - 1);
  }

  void update(int idx, int val) { update(1, 0, n - 1, idx, val); }

  int rangeSum(int l, int r) { return query(1, 0, n - 1, l, r); }
};

// ======================= FENWICK TREE (BIT) =======================
class FenwickTree {
private:
  vector<int> tree;
  int n;

public:
  FenwickTree(int size) {
    n = size;
    tree.assign(n + 1, 0);
  }

  // ======================= UPDATE =======================
  void update(int idx, int val) {
    for (int i = idx; i <= n; i += i & (-i)) {
      tree[i] += val;
    }
  }

  // ======================= PREFIX SUM =======================
  int prefixSum(int idx) {
    int sum = 0;
    for (int i = idx; i > 0; i -= i & (-i)) {
      sum += tree[i];
    }
    return sum;
  }

  // ======================= RANGE SUM =======================
  int rangeSum(int l, int r) {
    return prefixSum(r) - (l > 1 ? prefixSum(l - 1) : 0);
  }
};

// ======================= EXAMPLE 1: TRIE INSERTION =======================
void example_1_trie_insertion() {
  cout << "\n===== EXAMPLE 1: Trie - Word Insertion =====" << endl;

  Trie trie;

  vector<string> words = {"cat", "car", "card", "care", "dog", "dodge"};

  cout << "Inserting: ";
  for (const auto &word : words) {
    cout << word << " ";
    trie.insert(word);
  }
  cout << endl;
}

// ======================= EXAMPLE 2: TRIE SEARCH =======================
void example_2_trie_search() {
  cout << "\n===== EXAMPLE 2: Trie - Word Search =====" << endl;

  Trie trie;

  vector<string> words = {"cat", "car", "card"};
  for (const auto &word : words) {
    trie.insert(word);
  }

  cout << "Dictionary: cat, car, card" << endl;

  cout << "\nSearching:" << endl;
  cout << "Search 'cat': " << (trie.search("cat") ? "Found" : "Not Found")
       << endl;
  cout << "Search 'car': " << (trie.search("car") ? "Found" : "Not Found")
       << endl;
  cout << "Search 'ca': " << (trie.search("ca") ? "Found" : "Not Found")
       << endl;
}

// ======================= EXAMPLE 3: TRIE PREFIX =======================
void example_3_trie_prefix() {
  cout << "\n===== EXAMPLE 3: Trie - Prefix Search =====" << endl;

  Trie trie;

  vector<string> words = {"cat", "car", "card", "care", "dog"};
  for (const auto &word : words) {
    trie.insert(word);
  }

  cout << "Checking prefixes:" << endl;
  cout << "Prefix 'ca': " << (trie.startsWith("ca") ? "Exists" : "Not Exists")
       << endl;
  cout << "Prefix 'car': " << (trie.startsWith("car") ? "Exists" : "Not Exists")
       << endl;
  cout << "Prefix 'do': " << (trie.startsWith("do") ? "Exists" : "Not Exists")
       << endl;
}

// ======================= EXAMPLE 4: TRIE AUTOCOMPLETE =======================
void example_4_trie_autocomplete() {
  cout << "\n===== EXAMPLE 4: Trie - Autocomplete =====" << endl;

  Trie trie;

  vector<string> words = {"cat", "car", "card", "care", "dog", "dodge", "door"};
  for (const auto &word : words) {
    trie.insert(word);
  }

  cout << "Dictionary: cat, car, card, care, dog, dodge, door" << endl;

  trie.autocomplete("ca");
  trie.autocomplete("car");
  trie.autocomplete("do");
  trie.autocomplete("xyz");
}

// ======================= EXAMPLE 5: SEGMENT TREE QUERIES
// =======================
void example_5_segment_tree() {
  cout << "\n===== EXAMPLE 5: Segment Tree - Range Sum Queries =====" << endl;

  vector<int> arr = {1, 2, 3, 4, 5};
  SegmentTree segTree(arr);

  cout << "Array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  cout << "\nRange sum queries:" << endl;
  cout << "Sum [0, 2]: " << segTree.rangeSum(0, 2) << " (1+2+3)" << endl;
  cout << "Sum [1, 3]: " << segTree.rangeSum(1, 3) << " (2+3+4)" << endl;
  cout << "Sum [0, 4]: " << segTree.rangeSum(0, 4) << " (1+2+3+4+5)" << endl;
}

// ======================= EXAMPLE 6: SEGMENT TREE UPDATE
// =======================
void example_6_segment_tree_update() {
  cout << "\n===== EXAMPLE 6: Segment Tree - Update and Query =====" << endl;

  vector<int> arr = {1, 2, 3, 4, 5};
  SegmentTree segTree(arr);

  cout << "Original sum [0, 4]: " << segTree.rangeSum(0, 4) << endl;

  cout << "Update index 2 to 10:" << endl;
  segTree.update(2, 10); // Set arr[2] = 10

  cout << "New sum [0, 4]: " << segTree.rangeSum(0, 4) << endl;
  cout << "Sum [0, 2]: " << segTree.rangeSum(0, 2) << endl;
}

// ======================= EXAMPLE 7: FENWICK TREE =======================
void example_7_fenwick_tree() {
  cout << "\n===== EXAMPLE 7: Fenwick Tree - Range Queries =====" << endl;

  FenwickTree fenwick(5);

  cout << "Building Fenwick tree from array: 1 2 3 4 5" << endl;
  fenwick.update(1, 1);
  fenwick.update(2, 2);
  fenwick.update(3, 3);
  fenwick.update(4, 4);
  fenwick.update(5, 5);

  cout << "\nRange sum queries (1-indexed):" << endl;
  cout << "Sum [1, 3]: " << fenwick.rangeSum(1, 3) << endl;
  cout << "Sum [2, 4]: " << fenwick.rangeSum(2, 4) << endl;
  cout << "Sum [1, 5]: " << fenwick.rangeSum(1, 5) << endl;
}

// ======================= EXAMPLE 8: COMPARISON =======================
void example_8_comparison() {
  cout << "\n===== EXAMPLE 8: Tree Types Comparison =====" << endl;

  cout << "TRIE:" << endl;
  cout << "- Best for: String prefix matching, autocomplete" << endl;
  cout << "- Time: O(k) where k = string length" << endl;
  cout << "- Space: O(ALPHABET * n)" << endl;

  cout << "\nSEGMENT TREE:" << endl;
  cout << "- Best for: General range queries, flexible operations" << endl;
  cout << "- Time: O(log n) per query/update" << endl;
  cout << "- Space: O(n)" << endl;

  cout << "\nFENWICK TREE:" << endl;
  cout << "- Best for: Range queries (sum, XOR), competitive programming"
       << endl;
  cout << "- Time: O(log n) per query/update" << endl;
  cout << "- Space: O(n), more cache-friendly" << endl;
}

int main() {
  cout << "╔════════════════════════════════════════════════════════════╗"
       << endl;
  cout << "║    ADVANCED TREES - TRIES, SEGMENT, FENWICK TREES         ║"
       << endl;
  cout << "║        Part 4, Topic 25.1: Non-Linear Data Structures     ║"
       << endl;
  cout << "╚════════════════════════════════════════════════════════════╝"
       << endl;

  example_1_trie_insertion();
  example_2_trie_search();
  example_3_trie_prefix();
  example_4_trie_autocomplete();
  example_5_segment_tree();
  example_6_segment_tree_update();
  example_7_fenwick_tree();
  example_8_comparison();

  cout << "\n╔════════════════════════════════════════════════════════════╗"
       << endl;
  cout << "║                    EXAMPLES COMPLETED                      ║"
       << endl;
  cout << "║     Explore these advanced tree structures further!        ║"
       << endl;
  cout << "╚════════════════════════════════════════════════════════════╝"
       << endl;

  return 0;
}
