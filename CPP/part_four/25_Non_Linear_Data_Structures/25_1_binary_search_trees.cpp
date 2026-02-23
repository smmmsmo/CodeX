/*
================================================================================
       TOPIC 25.1: BINARY SEARCH TREES (BST) - OPERATIONS AND PROPERTIES
          Part 4: Data Structures - Non-Linear Data Structures
================================================================================

CONCEPT BREAKDOWN:
1. BST structure and ordering property
2. Insertion operations maintaining BST property
3. Deletion operations (3 cases)
4. Searching and traversals
5. Validation of BST
6. Time/Space complexity analysis
7. Common BST problems

KEY LEARNING POINTS:
- Left subtree < node < Right subtree
- Inorder traversal gives sorted output
- Efficient searching, insertion, deletion
- Average O(log n), worst O(n)
- Foundation for balanced trees (AVL, Red-Black)
- Core structure for many database implementations

================================================================================
                             SECTION 1: THEORY
================================================================================

1. WHAT IS A BINARY SEARCH TREE?
   - Binary tree with ordering property
   - Left subtree values < node value
   - Right subtree values > node value
   - No duplicate values (typically)
   - Inorder traversal gives sorted sequence

2. BST PROPERTY:
   Example valid BST:
           50
          /  \
        30    70
       / \   /  \
      20 40 60  80

   Each subtree is also a valid BST

3. BST OPERATIONS:
   Search: O(log n) avg, O(n) worst
   Insert: O(log n) avg, O(n) worst
   Delete: O(log n) avg, O(n) worst

4. SEARCH PROCESS:
   - Compare with current node
   - If equal, found
   - If less, go left
   - If greater, go right
   - Repeat until found or nullptr

5. INSERTION PROCESS:
   - Find correct position maintaining BST property
   - Create new node and insert

6. DELETION CASES:
   Case 1: Node is leaf -> Remove directly
   Case 2: Node has 1 child -> Replace with child
   Case 3: Node has 2 children -> Replace with inorder successor

7. TIME COMPLEXITY:
   Balanced BST:    O(log n)
   Skewed BST:      O(n)

   Worst case: Elements inserted in sorted order
   Tree becomes like linked list

================================================================================
                         SECTION 2: CODE EXAMPLES
================================================================================

*/

#include <algorithm>
#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::queue;

struct BSTNode {
  int data;
  BSTNode *left;
  BSTNode *right;

  BSTNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
  BSTNode *root;

  BSTNode *insertHelper(BSTNode *node, int value) {
    if (node == nullptr) {
      return new BSTNode(value);
    }

    if (value < node->data) {
      node->left = insertHelper(node->left, value);
    } else if (value > node->data) {
      node->right = insertHelper(node->right, value);
    }
    return node;
  }

  BSTNode *searchHelper(BSTNode *node, int value) {
    if (node == nullptr)
      return nullptr;

    if (value == node->data) {
      return node;
    } else if (value < node->data) {
      return searchHelper(node->left, value);
    } else {
      return searchHelper(node->right, value);
    }
  }

  BSTNode *findMin(BSTNode *node) {
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  BSTNode *deleteHelper(BSTNode *node, int value) {
    if (node == nullptr)
      return nullptr;

    if (value < node->data) {
      node->left = deleteHelper(node->left, value);
    } else if (value > node->data) {
      node->right = deleteHelper(node->right, value);
    } else {
      // Node to delete found
      // Case 1: No children (leaf)
      if (node->left == nullptr && node->right == nullptr) {
        delete node;
        return nullptr;
      }
      // Case 2: One child
      else if (node->left == nullptr) {
        BSTNode *temp = node->right;
        delete node;
        return temp;
      } else if (node->right == nullptr) {
        BSTNode *temp = node->left;
        delete node;
        return temp;
      }
      // Case 3: Two children
      else {
        BSTNode *successor = findMin(node->right);
        node->data = successor->data;
        node->right = deleteHelper(node->right, successor->data);
      }
    }
    return node;
  }

  void inorderHelper(BSTNode *node) {
    if (node == nullptr)
      return;
    inorderHelper(node->left);
    cout << node->data << " ";
    inorderHelper(node->right);
  }

  bool isValidBSTHelper(BSTNode *node, int minVal, int maxVal) {
    if (node == nullptr)
      return true;

    if (node->data <= minVal || node->data >= maxVal) {
      return false;
    }

    return isValidBSTHelper(node->left, minVal, node->data) &&
           isValidBSTHelper(node->right, node->data, maxVal);
  }

  int heightHelper(BSTNode *node) {
    if (node == nullptr)
      return -1;
    return 1 + std::max(heightHelper(node->left), heightHelper(node->right));
  }

  void deleteTreeHelper(BSTNode *node) {
    if (node == nullptr)
      return;
    deleteTreeHelper(node->left);
    deleteTreeHelper(node->right);
    delete node;
  }

public:
  BinarySearchTree() : root(nullptr) {}

  ~BinarySearchTree() { deleteTreeHelper(root); }

  // ======================= INSERT =======================
  void insert(int value) { root = insertHelper(root, value); }

  // ======================= SEARCH =======================
  bool search(int value) { return searchHelper(root, value) != nullptr; }

  // ======================= DELETE =======================
  void deleteValue(int value) { root = deleteHelper(root, value); }

  // ======================= INORDER TRAVERSAL =======================
  void inorder() {
    cout << "Inorder: ";
    inorderHelper(root);
    cout << endl;
  }

  // ======================= IS VALID BST =======================
  bool isValidBST() { return isValidBSTHelper(root, INT_MIN, INT_MAX); }

  // ======================= GET HEIGHT =======================
  int getHeight() { return heightHelper(root); }

  // ======================= FIND MIN =======================
  int findMin() {
    if (root == nullptr)
      throw std::out_of_range("Tree is empty!");
    return findMin(root)->data;
  }

  // ======================= FIND MAX =======================
  int findMax() {
    if (root == nullptr)
      throw std::out_of_range("Tree is empty!");
    BSTNode *node = root;
    while (node->right != nullptr) {
      node = node->right;
    }
    return node->data;
  }

  // ======================= FIND INORDER SUCCESSOR =======================
  int findInorderSuccessor(int value) {
    BSTNode *node = searchHelper(root, value);
    if (node == nullptr)
      return -1;

    if (node->right != nullptr) {
      return findMin(node->right)->data;
    }

    BSTNode *successor = nullptr;
    BSTNode *current = root;

    while (current != nullptr) {
      if (value < current->data) {
        successor = current;
        current = current->left;
      } else if (value > current->data) {
        current = current->right;
      } else {
        break;
      }
    }

    return successor ? successor->data : -1;
  }
};

// ======================= EXAMPLE 1: BASIC INSERTION AND SEARCH
// =======================
void example_1_insert_search() {
  cout << "\n===== EXAMPLE 1: Insert and Search =====" << endl;

  BinarySearchTree bst;

  cout << "Inserting: 50, 30, 70, 20, 40, 60, 80" << endl;
  bst.insert(50);
  bst.insert(30);
  bst.insert(70);
  bst.insert(20);
  bst.insert(40);
  bst.insert(60);
  bst.insert(80);

  bst.inorder();

  cout << "\nSearching:" << endl;
  cout << "Search 40: " << (bst.search(40) ? "Found" : "Not Found") << endl;
  cout << "Search 25: " << (bst.search(25) ? "Found" : "Not Found") << endl;
  cout << "Search 70: " << (bst.search(70) ? "Found" : "Not Found") << endl;
}

// ======================= EXAMPLE 2: MIN AND MAX =======================
void example_2_min_max() {
  cout << "\n===== EXAMPLE 2: Find Min and Max =====" << endl;

  BinarySearchTree bst;

  vector<int> values = {50, 30, 70, 20, 40, 60, 80};
  for (int val : values) {
    bst.insert(val);
  }

  cout << "Tree (inorder): ";
  bst.inorder();

  cout << "Minimum: " << bst.findMin() << endl;
  cout << "Maximum: " << bst.findMax() << endl;
  cout << "Height: " << bst.getHeight() << endl;
}

// ======================= EXAMPLE 3: DELETION - LEAF NODE
// =======================
void example_3_delete_leaf() {
  cout << "\n===== EXAMPLE 3: Delete Leaf Node =====" << endl;

  BinarySearchTree bst;

  vector<int> values = {50, 30, 70, 20, 40, 60, 80};
  for (int val : values) {
    bst.insert(val);
  }

  cout << "Original: ";
  bst.inorder();

  cout << "Delete leaf node 20:" << endl;
  bst.deleteValue(20);
  cout << "After delete: ";
  bst.inorder();
}

// ======================= EXAMPLE 4: DELETION - ONE CHILD
// =======================
void example_4_delete_one_child() {
  cout << "\n===== EXAMPLE 4: Delete Node with One Child =====" << endl;

  BinarySearchTree bst;

  vector<int> values = {50, 30, 70, 20, 40, 60, 80};
  for (int val : values) {
    bst.insert(val);
  }

  cout << "Original: ";
  bst.inorder();

  cout << "Delete node 30 (has one child):" << endl;
  bst.deleteValue(30);
  cout << "After delete: ";
  bst.inorder();
}

// ======================= EXAMPLE 5: DELETION - TWO CHILDREN
// =======================
void example_5_delete_two_children() {
  cout << "\n===== EXAMPLE 5: Delete Node with Two Children =====" << endl;

  BinarySearchTree bst;

  vector<int> values = {50, 30, 70, 20, 40, 60, 80};
  for (int val : values) {
    bst.insert(val);
  }

  cout << "Original: ";
  bst.inorder();

  cout << "Delete root 50 (has two children, use inorder successor):" << endl;
  bst.deleteValue(50);
  cout << "After delete: ";
  bst.inorder();
}

// ======================= EXAMPLE 6: INORDER SUCCESSOR =======================
void example_6_inorder_successor() {
  cout << "\n===== EXAMPLE 6: Find Inorder Successor =====" << endl;

  BinarySearchTree bst;

  vector<int> values = {50, 30, 70, 20, 40, 60, 80};
  for (int val : values) {
    bst.insert(val);
  }

  bst.inorder();

  cout << "\nInorder successors:" << endl;
  cout << "Successor of 20: " << bst.findInorderSuccessor(20) << endl;
  cout << "Successor of 30: " << bst.findInorderSuccessor(30) << endl;
  cout << "Successor of 50: " << bst.findInorderSuccessor(50) << endl;
  cout << "Successor of 70: " << bst.findInorderSuccessor(70) << endl;
}

// ======================= EXAMPLE 7: BALANCED VS SKEWED =======================
void example_7_balanced_vs_skewed() {
  cout << "\n===== EXAMPLE 7: Balanced vs Skewed BST =====" << endl;

  cout << "Balanced BST:" << endl;
  BinarySearchTree bst1;
  vector<int> values1 = {50, 30, 70, 20, 40, 60, 80};
  for (int val : values1) {
    bst1.insert(val);
  }
  bst1.inorder();
  cout << "Height: " << bst1.getHeight() << " (log n ≈ 2.8)" << endl;

  cout << "\nSkewed BST (sorted insertion):" << endl;
  BinarySearchTree bst2;
  vector<int> values2 = {1, 2, 3, 4, 5, 6, 7};
  for (int val : values2) {
    bst2.insert(val);
  }
  bst2.inorder();
  cout << "Height: " << bst2.getHeight() << " (n-1 = 6)" << endl;

  cout << "\nNote: Skewed tree loses efficiency! O(n) instead of O(log n)"
       << endl;
}

// ======================= EXAMPLE 8: VALIDATION =======================
void example_8_validation() {
  cout << "\n===== EXAMPLE 8: BST Validation =====" << endl;

  cout << "Valid BST: ";
  BinarySearchTree bst1;
  vector<int> values1 = {50, 30, 70, 20, 40, 60, 80};
  for (int val : values1) {
    bst1.insert(val);
  }
  cout << (bst1.isValidBST() ? "Valid" : "Invalid") << endl;

  cout << "\nAny properly constructed BST should be valid!" << endl;
}

/*
================================================================================
                            KEY CONCEPTS SUMMARY
================================================================================

BST PROPERTIES:
✓ Left subtree < Node < Right subtree
✓ Each subtree is also a BST
✓ Inorder gives sorted sequence
✓ O(log n) average, O(n) worst case

OPERATIONS COMPLEXITY:
┌──────────┬──────────┬──────────┐
│ Operation│ Average  │ Worst    │
├──────────┼──────────┼──────────┤
│ Search   │ O(log n) │ O(n)     │
│ Insert   │ O(log n) │ O(n)     │
│ Delete   │ O(log n) │ O(n)     │
└──────────┴──────────┴──────────┘

DELETION CASES:
1. Leaf node: Remove directly
2. One child: Replace with child
3. Two children: Replace with inorder successor

INORDER SUCCESSOR:
- Right-most node in right subtree
- Or first ancestor where node is in left subtree

ADVANTAGES:
✓ Efficient searching
✓ Sorted output with inorder
✓ Simple insertion/deletion

DISADVANTAGES:
✗ Can become skewed (O(n))
✗ Worst case with sorted input
✗ Need balancing (AVL, Red-Black)

================================================================================
*/

/*
================================================================================
                        SECTION 3: PRACTICE EXERCISES
================================================================================

1. VERIFY BST:
   Check if binary tree is valid BST.

2. CLOSEST VALUE:
   Find node with value closest to target.

3. RANGE SUM:
   Sum all values in range [L, R].

4. KTH SMALLEST:
   Find kth smallest element (use inorder).

5. REBUILD FROM INORDER:
   Given inorder, reconstruct BST.

6. VALIDATE SEQUENCE:
   Check if array can represent BST preorder.

7. SERIALIZE TO ARRAY:
   Convert BST to array (level-order).

================================================================================
*/

int main() {
  cout << "╔════════════════════════════════════════════════════════════╗"
       << endl;
  cout << "║    BINARY SEARCH TREES - OPERATIONS                       ║"
       << endl;
  cout << "║        Part 4, Topic 25.1: Non-Linear Data Structures     ║"
       << endl;
  cout << "╚════════════════════════════════════════════════════════════╝"
       << endl;

  example_1_insert_search();
  example_2_min_max();
  example_3_delete_leaf();
  example_4_delete_one_child();
  example_5_delete_two_children();
  example_6_inorder_successor();
  example_7_balanced_vs_skewed();
  example_8_validation();

  cout << "\n╔════════════════════════════════════════════════════════════╗"
       << endl;
  cout << "║                    EXAMPLES COMPLETED                      ║"
       << endl;
  cout << "║          Now try the practice exercises above!             ║"
       << endl;
  cout << "╚════════════════════════════════════════════════════════════╝"
       << endl;

  return 0;
}
