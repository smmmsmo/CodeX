/*
================================================================================
     TOPIC 25.1: BALANCED TREES - AVL TREES AND SELF-BALANCING
        Part 4: Data Structures - Non-Linear Data Structures
================================================================================

CONCEPT BREAKDOWN:
1. AVL tree basics and balance factor
2. Rotations (single and double)
3. Insertion with automatic balancing
4. Deletion with automatic balancing
5. Red-Black tree introduction
6. Time complexity maintenance
7. When to use balanced trees

KEY LEARNING POINTS:
- AVL maintains balance factor ≤ 1
- Rotations restore balance after insertion/deletion
- Guarantees O(log n) operations
- More complex than BST but predictable performance
- Used in databases and file systems
- Red-Black trees trade balance strictness for simpler operations

================================================================================
                             SECTION 1: THEORY
================================================================================

1. WHY BALANCE?
   Problem: BST can become skewed (O(n) operations)
   Solution: Keep tree balanced (O(log n) guaranteed)

2. AVL TREE DEFINITION:
   - BST with additional balance property
   - Balance factor = height(left) - height(right)
   - For every node: |balance factor| ≤ 1
   - All operations maintain this property

3. ROTATIONS:
   Single Right Rotation: Left-heavy situation
   Single Left Rotation: Right-heavy situation
   Left-Right Rotation: Left child right-heavy
   Right-Left Rotation: Right child left-heavy

4. BALANCE FACTOR:
   +2 or -2: Tree unbalanced, need rotation
   -1, 0, +1: Tree balanced

5. INSERTION:
   1. Insert like BST
   2. Update heights
   3. Check balance factor
   4. Perform rotation if needed

6. DELETION:
   1. Delete like BST
   2. Update heights
   3. Check balance factor
   4. Perform rotation if needed

7. RED-BLACK TREE:
   - Alternative to AVL
   - Nodes colored red or black
   - Looser balance requirement
   - Fewer rotations, simpler implementation

8. COMPLEXITY:
   All operations: O(log n) guaranteed
   Height: log n (not height of unbalanced tree)

================================================================================
                         SECTION 2: CODE EXAMPLES
================================================================================

*/

#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;
using std::max;

struct AVLNode {
  int data;
  AVLNode *left;
  AVLNode *right;
  int height;

  AVLNode(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
  AVLNode *root;

  int getHeight(AVLNode *node) { return node == nullptr ? 0 : node->height; }

  int getBalanceFactor(AVLNode *node) {
    return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
  }

  void updateHeight(AVLNode *node) {
    if (node != nullptr) {
      node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
  }

  // ======================= ROTATIONS =======================
  AVLNode *rotateRight(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
  }

  AVLNode *rotateLeft(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
  }

  AVLNode *insertHelper(AVLNode *node, int value) {
    if (node == nullptr) {
      return new AVLNode(value);
    }

    if (value < node->data) {
      node->left = insertHelper(node->left, value);
    } else if (value > node->data) {
      node->right = insertHelper(node->right, value);
    } else {
      return node; // Duplicate
    }

    updateHeight(node);
    int balance = getBalanceFactor(node);

    // Left-Left case
    if (balance > 1 && value < node->left->data) {
      return rotateRight(node);
    }

    // Left-Right case
    if (balance > 1 && value > node->left->data) {
      node->left = rotateLeft(node->left);
      return rotateRight(node);
    }

    // Right-Right case
    if (balance < -1 && value > node->right->data) {
      return rotateLeft(node);
    }

    // Right-Left case
    if (balance < -1 && value < node->right->data) {
      node->right = rotateRight(node->right);
      return rotateLeft(node);
    }

    return node;
  }

  void inorderHelper(AVLNode *node) {
    if (node == nullptr)
      return;
    inorderHelper(node->left);
    cout << node->data << " ";
    inorderHelper(node->right);
  }

  void deleteTreeHelper(AVLNode *node) {
    if (node == nullptr)
      return;
    deleteTreeHelper(node->left);
    deleteTreeHelper(node->right);
    delete node;
  }

public:
  AVLTree() : root(nullptr) {}

  ~AVLTree() { deleteTreeHelper(root); }

  void insert(int value) { root = insertHelper(root, value); }

  void inorder() {
    cout << "Inorder: ";
    inorderHelper(root);
    cout << endl;
  }

  int getHeight() { return getHeight(root); }
};

// ======================= EXAMPLE 1: BALANCE FACTOR =======================
void example_1_balance_factor() {
  cout << "\n===== EXAMPLE 1: Balance Factor Concept =====" << endl;

  cout << "Balance Factor = Height(Left) - Height(Right)" << endl;
  cout << "\nExamples:" << endl;
  cout << "   10           BF = 0 (balanced)" << endl;
  cout << "  /  \\" << endl;
  cout << " 5    15" << endl;

  cout << "\n   10           BF = 1 (balanced)" << endl;
  cout << "  /  \\" << endl;
  cout << " 5    15" << endl;
  cout << "/   " << endl;
  cout << "3   " << endl;

  cout << "\n   10           BF = 2 (UNBALANCED!)" << endl;
  cout << "  /  " << endl;
  cout << " 5   " << endl;
  cout << "/   " << endl;
  cout << "3   " << endl;
  cout << "(Need rotation)" << endl;
}

// ======================= EXAMPLE 2: INSERTION AND BALANCING
// =======================
void example_2_insertion() {
  cout << "\n===== EXAMPLE 2: Insertion with Automatic Balancing =====" << endl;

  AVLTree tree;

  cout << "Inserting: 10, 5, 15, 2, 7, 12, 20" << endl;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(2);
  tree.insert(7);
  tree.insert(12);
  tree.insert(20);

  tree.inorder();
  cout << "Tree height: " << tree.getHeight() << " (balanced log n)" << endl;
}

// ======================= EXAMPLE 3: LEFT-LEFT CASE =======================
void example_3_left_left() {
  cout << "\n===== EXAMPLE 3: Left-Left Case (Right Rotation) =====" << endl;

  cout << "Inserting 10, 5, 3 (creates unbalance):" << endl;
  cout << "    10              5" << endl;
  cout << "   /              /   \\" << endl;
  cout << "  5   ->         3     10" << endl;
  cout << " /" << endl;
  cout << "3 (Right rotation performed)" << endl;

  AVLTree tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(3);

  tree.inorder();
  cout << "Height: " << tree.getHeight() << endl;
}

// ======================= EXAMPLE 4: RIGHT-RIGHT CASE =======================
void example_4_right_right() {
  cout << "\n===== EXAMPLE 4: Right-Right Case (Left Rotation) =====" << endl;

  cout << "Inserting 10, 15, 20 (creates unbalance):" << endl;
  cout << "10              15" << endl;
  cout << "  \\            /  \\" << endl;
  cout << "   15   ->    10   20" << endl;
  cout << "    \\" << endl;
  cout << "     20 (Left rotation performed)" << endl;

  AVLTree tree;
  tree.insert(10);
  tree.insert(15);
  tree.insert(20);

  tree.inorder();
  cout << "Height: " << tree.getHeight() << endl;
}

// ======================= EXAMPLE 5: LEFT-RIGHT CASE =======================
void example_5_left_right() {
  cout << "\n===== EXAMPLE 5: Left-Right Case (LR Rotation) =====" << endl;

  cout << "Inserting 10, 5, 7 (creates unbalance):" << endl;
  cout << "    10            10            7" << endl;
  cout << "   /             /            /   \\" << endl;
  cout << "  5     ->      7     ->     5     10" << endl;
  cout << "   \\" / " << endl;
              cout
       << "    7          5" << endl;
  cout << "(Left-Right rotation: rotate left then right)" << endl;

  AVLTree tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(7);

  tree.inorder();
  cout << "Height: " << tree.getHeight() << endl;
}

// ======================= EXAMPLE 6: RIGHT-LEFT CASE =======================
void example_6_right_left() {
  cout << "\n===== EXAMPLE 6: Right-Left Case (RL Rotation) =====" << endl;

  cout << "Inserting 10, 15, 12 (creates unbalance):" << endl;
  cout << "10                10               12" << endl;
  cout << "  \\                \\              /   \\" << endl;
  cout << "   15     ->       12     ->     10    15" << endl;
  cout << "  /                  \\" << endl;
  cout << "12                    15" << endl;
  cout << "(Right-Left rotation: rotate right then left)" << endl;

  AVLTree tree;
  tree.insert(10);
  tree.insert(15);
  tree.insert(12);

  tree.inorder();
  cout << "Height: " << tree.getHeight() << endl;
}

// ======================= EXAMPLE 7: COMPLEXITY GUARANTEE
// =======================
void example_7_complexity() {
  cout << "\n===== EXAMPLE 7: Time Complexity Guarantee =====" << endl;

  cout << "AVL Tree guarantees O(log n) for all operations" << endl;
  cout << "\nComparing height for n = 1000 elements:" << endl;

  cout << "Unbalanced BST (worst case): ~1000 operations" << endl;
  cout << "AVL Tree (guaranteed): ~10 operations" << endl;

  cout << "\nFor n = 1,000,000:" << endl;
  cout << "Unbalanced BST (worst case): ~1,000,000 operations" << endl;
  cout << "AVL Tree (guaranteed): ~20 operations" << endl;

  cout << "\nFormula: max_height = 1.44 * log2(n+2)" << endl;
}

// ======================= EXAMPLE 8: WHEN TO USE =======================
void example_8_use_cases() {
  cout << "\n===== EXAMPLE 8: When to Use AVL Trees =====" << endl;

  cout << "USE AVL TREES WHEN:" << endl;
  cout << "✓ Predictable O(log n) needed" << endl;
  cout << "✓ More searches than insertions/deletions" << endl;
  cout << "✓ Database indexes" << endl;
  cout << "✓ File system directories" << endl;

  cout << "\nALTERNATIVES:" << endl;
  cout << "✓ Red-Black Trees: Fewer rotations, slightly taller" << endl;
  cout << "✓ B-Trees: Better for disk access patterns" << endl;
  cout << "✓ Splay Trees: Recently accessed elements faster" << endl;
}

/*
================================================================================
                            KEY CONCEPTS SUMMARY
================================================================================

AVL TREE PROPERTIES:
✓ BST with balance factor ≤ 1
✓ All operations O(log n) guaranteed
✓ Height ≤ 1.44 * log(n+2)
✓ Automatic balancing via rotations

BALANCE FACTOR:
- BF = Height(Left) - Height(Right)
- Valid range: -1, 0, +1
- Outside range triggers rotation

ROTATION CASES:
1. Left-Left: Single right rotation
2. Right-Right: Single left rotation
3. Left-Right: Rotate left then right
4. Right-Left: Rotate right then left

ADVANTAGES:
✓ O(log n) guaranteed for all operations
✓ Better than unbalanced BST
✓ Deterministic performance

DISADVANTAGES:
✗ More complex implementation
✗ More rotations than Red-Black
✗ Stricter balance requirement

RED-BLACK VS AVL:
Red-Black: Easier to implement, fewer rotations
AVL: Stricter balancing, faster lookups

================================================================================
*/

int main() {
  cout << "╔════════════════════════════════════════════════════════════╗"
       << endl;
  cout << "║    BALANCED TREES - AVL TREES                             ║"
       << endl;
  cout << "║        Part 4, Topic 25.1: Non-Linear Data Structures     ║"
       << endl;
  cout << "╚════════════════════════════════════════════════════════════╝"
       << endl;

  example_1_balance_factor();
  example_2_insertion();
  example_3_left_left();
  example_4_right_right();
  example_5_left_right();
  example_6_right_left();
  example_7_complexity();
  example_8_use_cases();

  cout << "\n╔════════════════════════════════════════════════════════════╗"
       << endl;
  cout << "║                    EXAMPLES COMPLETED                      ║"
       << endl;
  cout << "║          Now try implementing full AVL operations!         ║"
       << endl;
  cout << "╚════════════════════════════════════════════════════════════╝"
       << endl;

  return 0;
}
