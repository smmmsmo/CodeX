/*
================================================================================
            TOPIC 25.1: BINARY TREES - BASICS AND TRAVERSALS
              Part 4: Data Structures - Non-Linear Data Structures
================================================================================

CONCEPT BREAKDOWN:
1. Binary tree structure and properties
2. Node structure and tree terminology
3. Tree traversals (inorder, preorder, postorder, level-order)
4. Height and depth calculations
5. Tree construction from traversals
6. Perfect, complete, and full binary trees
7. Time/Space complexity analysis

KEY LEARNING POINTS:
- Binary tree has max 2 children per node
- Traversals are fundamental tree operations
- Different traversals reveal different information
- Height and depth are important properties
- Understanding tree structure is foundational

================================================================================
                             SECTION 1: THEORY
================================================================================

1. WHAT IS A BINARY TREE?
   - Hierarchical data structure
   - Each node has at most 2 children (left and right)
   - Has a root node and leaf nodes
   - Non-linear, non-contiguous structure

2. NODE STRUCTURE:
   struct Node {
       int data;
       Node* left;
       Node* right;
   };

3. TREE TERMINOLOGY:
   - Root: Top node with no parent
   - Leaf: Node with no children
   - Parent: Node with children
   - Children: Nodes below parent
   - Sibling: Nodes with same parent
   - Ancestor: Node on path to root
   - Descendant: Node in subtree below
   - Height: Distance from node to farthest leaf
   - Depth: Distance from root to node
   - Level: Depth + 1

4. TREE TYPES:
   Full Binary Tree: Every node has 0 or 2 children
   Complete Binary Tree: All levels filled except possibly last
   Perfect Binary Tree: All levels completely filled
   Balanced Binary Tree: Height difference of subtrees <= 1

5. TREE TRAVERSALS:

   Inorder (LNR):   Left -> Node -> Right
   (For BST, gives sorted order)

   Preorder (NLR):  Node -> Left -> Right
   (For tree reconstruction from traversals)

   Postorder (LRN): Left -> Right -> Node
   (For deleting trees)

   Level-order (BFS): Traverse level by level

6. TIME/SPACE COMPLEXITY:
   Operation          Time       Space
   ────────────────────────────────────
   Search (generic)   O(n)       O(h) recursive
   Insert             O(n)       O(h)
   Delete             O(n)       O(h)
   Traversal          O(n)       O(h)

   h = height, n = number of nodes

7. PROPERTIES:
   - Min nodes in height h: h + 1
   - Max nodes in height h: 2^(h+1) - 1
   - Max nodes at level k: 2^k
   - Perfect tree nodes: 2^(h+1) - 1

================================================================================
                         SECTION 2: CODE EXAMPLES
================================================================================

*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using std::cout;
using std::endl;
using std::queue;
using std::stack;
using std::vector;

// Node structure for binary tree
struct TreeNode {
  int data;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
  TreeNode *root;

  // Helper functions for recursive operations
  void inorderHelper(TreeNode *node) {
    if (node == nullptr)
      return;
    inorderHelper(node->left);
    cout << node->data << " ";
    inorderHelper(node->right);
  }

  void preorderHelper(TreeNode *node) {
    if (node == nullptr)
      return;
    cout << node->data << " ";
    preorderHelper(node->left);
    preorderHelper(node->right);
  }

  void postorderHelper(TreeNode *node) {
    if (node == nullptr)
      return;
    postorderHelper(node->left);
    postorderHelper(node->right);
    cout << node->data << " ";
  }

  int heightHelper(TreeNode *node) {
    if (node == nullptr)
      return -1;
    return 1 + std::max(heightHelper(node->left), heightHelper(node->right));
  }

  int countNodesHelper(TreeNode *node) {
    if (node == nullptr)
      return 0;
    return 1 + countNodesHelper(node->left) + countNodesHelper(node->right);
  }

  void deleteTreeHelper(TreeNode *node) {
    if (node == nullptr)
      return;
    deleteTreeHelper(node->left);
    deleteTreeHelper(node->right);
    delete node;
  }

public:
  BinaryTree() : root(nullptr) {}

  ~BinaryTree() { deleteTreeHelper(root); }

  // ======================= CREATE SAMPLE TREE =======================
  void createSampleTree() {
    root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
  }

  // ======================= INORDER TRAVERSAL =======================
  void inorder() {
    cout << "Inorder: ";
    inorderHelper(root);
    cout << endl;
  }

  // ======================= PREORDER TRAVERSAL =======================
  void preorder() {
    cout << "Preorder: ";
    preorderHelper(root);
    cout << endl;
  }

  // ======================= POSTORDER TRAVERSAL =======================
  void postorder() {
    cout << "Postorder: ";
    postorderHelper(root);
    cout << endl;
  }

  // ======================= LEVEL-ORDER TRAVERSAL =======================
  void levelOrder() {
    if (root == nullptr) {
      cout << "Tree is empty" << endl;
      return;
    }

    queue<TreeNode *> q;
    q.push(root);

    cout << "Level-order: ";
    while (!q.empty()) {
      TreeNode *node = q.front();
      q.pop();

      cout << node->data << " ";

      if (node->left != nullptr)
        q.push(node->left);
      if (node->right != nullptr)
        q.push(node->right);
    }
    cout << endl;
  }

  // ======================= GET HEIGHT =======================
  int getHeight() { return heightHelper(root); }

  // ======================= COUNT NODES =======================
  int countNodes() { return countNodesHelper(root); }

  // ======================= LEVEL-ORDER BY LEVELS =======================
  void levelOrderByLevels() {
    if (root == nullptr) {
      cout << "Tree is empty" << endl;
      return;
    }

    queue<TreeNode *> q;
    q.push(root);

    int level = 0;
    while (!q.empty()) {
      int levelSize = q.size();
      cout << "Level " << level << ": ";

      for (int i = 0; i < levelSize; i++) {
        TreeNode *node = q.front();
        q.pop();

        cout << node->data << " ";

        if (node->left != nullptr)
          q.push(node->left);
        if (node->right != nullptr)
          q.push(node->right);
      }
      cout << endl;
      level++;
    }
  }

  // ======================= ITERATIVE INORDER =======================
  void inorderIterative() {
    if (root == nullptr)
      return;

    cout << "Iterative Inorder: ";
    stack<TreeNode *> st;
    TreeNode *current = root;

    while (current != nullptr || !st.empty()) {
      while (current != nullptr) {
        st.push(current);
        current = current->left;
      }

      current = st.top();
      st.pop();

      cout << current->data << " ";
      current = current->right;
    }
    cout << endl;
  }

  // ======================= MORRIS INORDER TRAVERSAL =======================
  void morrisInorder() {
    cout << "Morris Inorder: ";
    TreeNode *current = root;

    while (current != nullptr) {
      if (current->left == nullptr) {
        cout << current->data << " ";
        current = current->right;
      } else {
        TreeNode *pre = current->left;
        while (pre->right != nullptr && pre->right != current) {
          pre = pre->right;
        }

        if (pre->right == nullptr) {
          pre->right = current;
          current = current->left;
        } else {
          pre->right = nullptr;
          cout << current->data << " ";
          current = current->right;
        }
      }
    }
    cout << endl;
  }

  // ======================= SEARCH =======================
  bool search(int value) {
    if (root == nullptr)
      return false;

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
      TreeNode *node = q.front();
      q.pop();

      if (node->data == value)
        return true;

      if (node->left != nullptr)
        q.push(node->left);
      if (node->right != nullptr)
        q.push(node->right);
    }
    return false;
  }

  // ======================= IS BALANCED =======================
  bool isBalanced() {
    int height = 0;
    return isBalancedHelper(root, height);
  }

private:
  bool isBalancedHelper(TreeNode *node, int &height) {
    if (node == nullptr) {
      height = -1;
      return true;
    }

    int leftHeight = 0, rightHeight = 0;

    if (!isBalancedHelper(node->left, leftHeight))
      return false;
    if (!isBalancedHelper(node->right, rightHeight))
      return false;

    if (std::abs(leftHeight - rightHeight) > 1) {
      return false;
    }

    height = 1 + std::max(leftHeight, rightHeight);
    return true;
  }
};

// ======================= EXAMPLE 1: CREATE AND DISPLAY =======================
void example_1_create_display() {
  cout << "\n===== EXAMPLE 1: Create and Display Tree =====" << endl;

  BinaryTree tree;
  tree.createSampleTree();

  cout << "Tree created:" << endl;
  cout << "         1" << endl;
  cout << "       /   \\" << endl;
  cout << "      2     3" << endl;
  cout << "     / \\   / \\" << endl;
  cout << "    4   5 6   7" << endl;

  cout << "\nTree Statistics:" << endl;
  cout << "Height: " << tree.getHeight() << endl;
  cout << "Number of nodes: " << tree.countNodes() << endl;
}

// ======================= EXAMPLE 2: ALL TRAVERSALS =======================
void example_2_all_traversals() {
  cout << "\n===== EXAMPLE 2: All Traversal Methods =====" << endl;

  BinaryTree tree;
  tree.createSampleTree();

  tree.inorder();
  tree.preorder();
  tree.postorder();
  tree.levelOrder();
}

// ======================= EXAMPLE 3: LEVEL-ORDER BY LEVELS
// =======================
void example_3_level_order_levels() {
  cout << "\n===== EXAMPLE 3: Level-Order Traversal By Levels =====" << endl;

  BinaryTree tree;
  tree.createSampleTree();

  tree.levelOrderByLevels();
}

// ======================= EXAMPLE 4: ITERATIVE TRAVERSALS
// =======================
void example_4_iterative_traversals() {
  cout << "\n===== EXAMPLE 4: Iterative Traversals =====" << endl;

  BinaryTree tree;
  tree.createSampleTree();

  tree.inorderIterative();
  tree.morrisInorder();
}

// ======================= EXAMPLE 5: SEARCHING =======================
void example_5_searching() {
  cout << "\n===== EXAMPLE 5: Searching in Tree =====" << endl;

  BinaryTree tree;
  tree.createSampleTree();

  vector<int> searchValues = {5, 7, 10, 1};

  for (int val : searchValues) {
    cout << "Search " << val << ": "
         << (tree.search(val) ? "Found" : "Not Found") << endl;
  }
}

// ======================= EXAMPLE 6: TREE PROPERTIES =======================
void example_6_tree_properties() {
  cout << "\n===== EXAMPLE 6: Tree Properties =====" << endl;

  BinaryTree tree;
  tree.createSampleTree();

  int height = tree.getHeight();
  int nodes = tree.countNodes();

  cout << "Height: " << height << endl;
  cout << "Number of nodes: " << nodes << endl;
  cout << "Max possible nodes in height " << height << ": "
       << (1 << (height + 1)) - 1 << endl;
  cout << "Is tree balanced: " << (tree.isBalanced() ? "Yes" : "No") << endl;
}

// ======================= EXAMPLE 7: TREE RECONSTRUCTION
// =======================
void example_7_tree_construction() {
  cout << "\n===== EXAMPLE 7: Tree Construction =====" << endl;

  cout << "Given:" << endl;
  cout << "Inorder:   4 2 5 1 6 3 7" << endl;
  cout << "Preorder:  1 2 4 5 3 6 7" << endl;

  cout << "\nReconstruction process:" << endl;
  cout << "1. Preorder[0] = 1 (root)" << endl;
  cout << "2. Find 1 in inorder -> left: {4,2,5}, right: {6,3,7}" << endl;
  cout << "3. Recursively build left and right subtrees" << endl;

  cout << "\nResult is the same tree as in Example 1" << endl;
}

// ======================= EXAMPLE 8: PERFECT VS COMPLETE TREE
// =======================
void example_8_tree_types() {
  cout << "\n===== EXAMPLE 8: Tree Types =====" << endl;

  cout << "Perfect Binary Tree (all levels filled):" << endl;
  cout << "         1" << endl;
  cout << "       /   \\" << endl;
  cout << "      2     3" << endl;
  cout << "     / \\   / \\" << endl;
  cout << "    4   5 6   7" << endl;
  cout << "Nodes: " << (1 << 3) - 1 << " (2^height - 1)" << endl;

  cout << "\nComplete Binary Tree (all levels filled, last level "
          "left-justified):"
       << endl;
  cout << "         1" << endl;
  cout << "       /   \\" << endl;
  cout << "      2     3" << endl;
  cout << "     / \\   /" << endl;
  cout << "    4   5 6" << endl;
  cout << "Used in heap implementations" << endl;
}

/*
================================================================================
                            KEY CONCEPTS SUMMARY
================================================================================

BINARY TREE PROPERTIES:
✓ At most 2 children per node
✓ n nodes have n-1 edges
✓ Tree is connected and acyclic
✓ Unique path between any two nodes

TRAVERSAL COMPLEXITY:
- Time: O(n) for all traversals
- Space: O(h) for recursive, O(n) for iterative level-order

TREE PROPERTIES:
- Height of tree: longest path from root to leaf
- Depth of node: distance from root
- Balanced tree: height difference of subtrees ≤ 1

TRAVERSAL APPLICATIONS:
- Inorder: For BST gives sorted output
- Preorder: Tree reconstruction, copy tree
- Postorder: Delete tree, evaluate expressions
- Level-order: BFS, shortest path

TREE TYPES:
Full:      Every node has 0 or 2 children
Complete:  All levels filled except possibly last
Perfect:   All levels completely filled
Balanced:  Height-balanced property

================================================================================
*/

/*
================================================================================
                        SECTION 3: PRACTICE EXERCISES
================================================================================

1. MIRROR TREE:
   Create a mirror image of the tree (swap left and right).

2. TREE HEIGHT:
   Find the height of the tree.

3. LOWEST COMMON ANCESTOR (LCA):
   Find the LCA of two nodes.

4. DIAMETER:
   Find diameter (longest path between any two nodes).

5. MAXIMUM PATH SUM:
   Find path with maximum sum of node values.

6. SERIALIZE/DESERIALIZE:
   Convert tree to string and back.

7. VERTICAL ORDER TRAVERSAL:
   Print nodes in vertical order.

8. BOUNDARY TRAVERSAL:
   Print boundary nodes of tree.

================================================================================
*/

int main() {
  cout << "╔════════════════════════════════════════════════════════════╗"
       << endl;
  cout << "║    BINARY TREES - BASICS AND TRAVERSALS                   ║"
       << endl;
  cout << "║        Part 4, Topic 25.1: Non-Linear Data Structures     ║"
       << endl;
  cout << "╚════════════════════════════════════════════════════════════╝"
       << endl;

  example_1_create_display();
  example_2_all_traversals();
  example_3_level_order_levels();
  example_4_iterative_traversals();
  example_5_searching();
  example_6_tree_properties();
  example_7_tree_construction();
  example_8_tree_types();

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
