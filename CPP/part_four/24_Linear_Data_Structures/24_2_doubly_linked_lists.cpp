/*
================================================================================
                 TOPIC 24.2: LINKED LISTS - DOUBLY LINKED LISTS
                    Part 4: Data Structures - Linear Data Structures
================================================================================

CONCEPT BREAKDOWN:
1. Node structure with previous and next pointers
2. Doubly Linked List basics
3. Bidirectional traversal
4. Insertion and deletion operations
5. Forward and backward traversal
6. Comparison with single linked lists

KEY LEARNING POINTS:
- Each node has previous and next pointers
- Can traverse forward and backward
- More memory due to two pointers
- Better for operations requiring backward access
- Useful for deque implementations

================================================================================
                             SECTION 1: THEORY
================================================================================

1. WHAT IS A DOUBLY LINKED LIST?
   - Linked list where each node has TWO pointers
   - Pointer to next node
   - Pointer to previous node
   - Enables bidirectional traversal

2. NODE STRUCTURE:
   struct Node {
       int data;
       Node* next;
       Node* prev;
   };

3. ADVANTAGES OVER SINGLE LINKED LIST:
   Single LL:
   - Only forward traversal
   - O(n) to delete from end
   - Cannot go backward

   Doubly LL:
   - Forward and backward traversal
   - O(1) to delete if we have node pointer
   - Can traverse in both directions
   - Useful for LRU cache, deques

4. DISADVANTAGES:
   - Extra memory per node (for prev pointer)
   - More complex operations
   - O(2n) space for pointers vs O(n)

5. TIME COMPLEXITY:
   Operation              Time Complexity
   ─────────────────────────────────────
   insert_at_head         O(1)
   insert_at_tail         O(n)* or O(1) with tail pointer
   insert_at_middle       O(n)
   delete_from_head       O(1)
   delete_from_tail       O(1)* with tail pointer
   forward_traversal      O(n)
   backward_traversal     O(n)
   search                 O(n)

================================================================================
                         SECTION 2: CODE EXAMPLES
================================================================================

*/

#include <iostream>

using std::cout;
using std::endl;

// Node structure for doubly linked list
struct DNode {
  int data;
  DNode *next;
  DNode *prev;

  DNode(int value) : data(value), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
  DNode *head;
  DNode *tail;

public:
  DoublyLinkedList() : head(nullptr), tail(nullptr) {}

  ~DoublyLinkedList() {
    while (head != nullptr) {
      DNode *temp = head;
      head = head->next;
      delete temp;
    }
  }

  // ======================= INSERT AT HEAD =======================
  void insertAtHead(int value) {
    DNode *newNode = new DNode(value);

    if (head == nullptr) {
      head = tail = newNode;
    } else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
  }

  // ======================= INSERT AT END =======================
  void insertAtEnd(int value) {
    DNode *newNode = new DNode(value);

    if (tail == nullptr) {
      head = tail = newNode;
    } else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
  }

  // ======================= INSERT AT POSITION =======================
  void insertAtPosition(int value, int position) {
    if (position <= 0) {
      insertAtHead(value);
      return;
    }

    DNode *current = head;
    for (int i = 0; i < position - 1 && current != nullptr; i++) {
      current = current->next;
    }

    if (current == nullptr) {
      cout << "Position out of range" << endl;
      return;
    }

    DNode *newNode = new DNode(value);
    newNode->next = current->next;
    newNode->prev = current;

    if (current->next != nullptr) {
      current->next->prev = newNode;
    } else {
      tail = newNode;
    }
    current->next = newNode;
  }

  // ======================= DELETE FROM HEAD =======================
  void deleteFromHead() {
    if (head == nullptr) {
      cout << "List is empty" << endl;
      return;
    }

    if (head == tail) {
      delete head;
      head = tail = nullptr;
    } else {
      DNode *temp = head;
      head = head->next;
      head->prev = nullptr;
      delete temp;
    }
  }

  // ======================= DELETE FROM END =======================
  void deleteFromEnd() {
    if (tail == nullptr) {
      cout << "List is empty" << endl;
      return;
    }

    if (head == tail) {
      delete tail;
      head = tail = nullptr;
    } else {
      DNode *temp = tail;
      tail = tail->prev;
      tail->next = nullptr;
      delete temp;
    }
  }

  // ======================= FORWARD DISPLAY =======================
  void displayForward() {
    if (head == nullptr) {
      cout << "List is empty" << endl;
      return;
    }

    DNode *current = head;
    cout << "Forward: ";
    while (current != nullptr) {
      cout << current->data << " <-> ";
      current = current->next;
    }
    cout << "NULL" << endl;
  }

  // ======================= BACKWARD DISPLAY =======================
  void displayBackward() {
    if (tail == nullptr) {
      cout << "List is empty" << endl;
      return;
    }

    DNode *current = tail;
    cout << "Backward: ";
    while (current != nullptr) {
      cout << current->data << " <-> ";
      current = current->prev;
    }
    cout << "NULL" << endl;
  }

  // ======================= GET SIZE =======================
  int getSize() {
    int count = 0;
    DNode *current = head;
    while (current != nullptr) {
      count++;
      current = current->next;
    }
    return count;
  }

  // ======================= SEARCH =======================
  bool search(int value) {
    DNode *current = head;
    while (current != nullptr) {
      if (current->data == value) {
        return true;
      }
      current = current->next;
    }
    return false;
  }

  // ======================= REVERSE TRAVERSAL =======================
  void traverseBackward() {
    if (tail == nullptr) {
      cout << "List is empty" << endl;
      return;
    }

    DNode *current = tail;
    cout << "Traversing backward: ";
    while (current != nullptr) {
      cout << current->data << " ";
      current = current->prev;
    }
    cout << endl;
  }
};

// ======================= EXAMPLE 1: BASIC OPERATIONS =======================
void example_1_basic_operations() {
  cout << "\n===== EXAMPLE 1: Basic Operations =====" << endl;

  DoublyLinkedList list;

  cout << "Inserting 10, 20, 30 at end:" << endl;
  list.insertAtEnd(10);
  list.insertAtEnd(20);
  list.insertAtEnd(30);
  list.displayForward();
  list.displayBackward();

  cout << "\nSize: " << list.getSize() << endl;
}

// ======================= EXAMPLE 2: INSERT AT HEAD =======================
void example_2_insert_head() {
  cout << "\n===== EXAMPLE 2: Insert at Head =====" << endl;

  DoublyLinkedList list;

  list.insertAtEnd(10);
  list.insertAtEnd(30);
  cout << "Initial: ";
  list.displayForward();

  cout << "\nInsert 5 at head: ";
  list.insertAtHead(5);
  list.displayForward();
  list.displayBackward();
}

// ======================= EXAMPLE 3: INSERT AT POSITION =======================
void example_3_insert_position() {
  cout << "\n===== EXAMPLE 3: Insert at Position =====" << endl;

  DoublyLinkedList list;

  for (int i = 0; i < 5; i++) {
    list.insertAtEnd(i * 10);
  }
  cout << "Initial: ";
  list.displayForward();

  cout << "\nInsert 25 at position 2: ";
  list.insertAtPosition(25, 2);
  list.displayForward();
  list.displayBackward();
}

// ======================= EXAMPLE 4: DELETE OPERATIONS =======================
void example_4_delete_operations() {
  cout << "\n===== EXAMPLE 4: Delete Operations =====" << endl;

  DoublyLinkedList list;

  for (int i = 1; i <= 5; i++) {
    list.insertAtEnd(i * 10);
  }
  cout << "Initial: ";
  list.displayForward();

  cout << "\nDelete from head:" << endl;
  list.deleteFromHead();
  list.displayForward();
  list.displayBackward();

  cout << "\nDelete from end:" << endl;
  list.deleteFromEnd();
  list.displayForward();
  list.displayBackward();
}

// ======================= EXAMPLE 5: BACKWARD TRAVERSAL =======================
void example_5_backward_traversal() {
  cout << "\n===== EXAMPLE 5: Backward Traversal =====" << endl;

  DoublyLinkedList list;

  for (int i = 1; i <= 6; i++) {
    list.insertAtEnd(i);
  }

  cout << "List created: 1 to 6" << endl;
  list.displayForward();
  list.traverseBackward();

  cout << "\nAccessing backward from tail:" << endl;
  list.displayBackward();
}

// ======================= EXAMPLE 6: FINDING MIDDLE =======================
void example_6_middle_element() {
  cout << "\n===== EXAMPLE 6: Finding Middle Element =====" << endl;

  DoublyLinkedList list;

  for (int i = 1; i <= 7; i++) {
    list.insertAtEnd(i);
  }
  list.displayForward();

  int size = list.getSize();
  int middle = (size / 2) + 1;
  cout << "Size: " << size << ", Middle position: " << middle << endl;

  cout << "For doubly linked list, we can traverse from both ends!" << endl;
}

// ======================= EXAMPLE 7: ADVANTAGE: DELETE WITHOUT TRAVERSING
// =======================
void example_7_delete_advantage() {
  cout << "\n===== EXAMPLE 7: Delete Advantage =====" << endl;

  DoublyLinkedList list;

  for (int i = 1; i <= 5; i++) {
    list.insertAtEnd(i * 10);
  }
  cout << "Initial: ";
  list.displayForward();

  cout << "\nWith doubly linked list:" << endl;
  cout << "- Can delete from end in O(1)" << endl;
  cout << "- Can traverse backward efficiently" << endl;
  cout << "- Better for applications like undo/redo" << endl;

  cout << "\nDeleting from end multiple times:" << endl;
  list.deleteFromEnd();
  list.displayForward();

  list.deleteFromEnd();
  list.displayForward();
}

// ======================= EXAMPLE 8: PALINDROME-LIKE CHECK
// =======================
void example_8_bidirectional_check() {
  cout << "\n===== EXAMPLE 8: Bidirectional Access =====" << endl;

  DoublyLinkedList list;

  for (int i = 1; i <= 5; i++) {
    list.insertAtEnd(i);
  }

  cout << "List: 1 -> 2 -> 3 -> 4 -> 5" << endl;
  cout << "\nForward traversal from head: ";
  list.displayForward();

  cout << "Backward traversal from tail: ";
  list.displayBackward();

  cout << "\nThis unique feature allows:" << endl;
  cout << "- Efficient deletion from both ends" << endl;
  cout << "- Palindrome checking" << endl;
  cout << "- LRU cache implementation" << endl;
}

/*
================================================================================
                            KEY CONCEPTS SUMMARY
================================================================================

DOUBLY LINKED LIST PROPERTIES:
✓ Bidirectional access
✓ O(1) deletion at both ends (with tail pointer)
✓ Forward and backward traversal
✓ More memory than single linked list
✓ Better for certain applications

COMPARISON TABLE:
┌────────────────────┬──────────────────┬──────────────────┐
│ Operation          │ Single LL        │ Doubly LL        │
├────────────────────┼──────────────────┼──────────────────┤
│ Insert at head     │ O(1)             │ O(1)             │
│ Insert at tail     │ O(n)             │ O(1) with tail   │
│ Delete at head     │ O(1)             │ O(1)             │
│ Delete at tail     │ O(n)             │ O(1)             │
│ Search forward     │ O(n)             │ O(n)             │
│ Search backward    │ X                │ O(n)             │
│ Memory per node    │ 8 bytes (ptr)    │ 16 bytes (2 ptr) │
└────────────────────┴──────────────────┴──────────────────┘

ADVANTAGES OF DOUBLY LINKED LIST:
✓ Efficient insertion/deletion at both ends
✓ Bidirectional traversal
✓ Can implement deques efficiently
✓ Good for LRU cache

DISADVANTAGES:
✗ Extra memory for previous pointer
✗ More complex operations
✗ Still O(n) to search from middle

USE CASES:
- Deques (double-ended queues)
- LRU cache implementation
- Undo/Redo functionality
- Browser history (forward/backward)

================================================================================
*/

/*
================================================================================
                        SECTION 3: PRACTICE EXERCISES
================================================================================

1. IMPLEMENT DEQUE:
   Use doubly linked list to implement a deque with:
   - insertFront(), insertRear()
   - deleteFront(), deleteRear()
   - getFront(), getRear()

2. PALINDROME CHECK:
   Check if a doubly linked list values form a palindrome.

3. LRU CACHE:
   Implement LRU cache using doubly linked list and hash map.

4. REVERSE IN PAIRS:
   Reverse pairs of nodes: 1->2->3->4 becomes 2->1->4->3

5. ROTATE LIST:
   Rotate doubly linked list by k positions.

================================================================================
*/

int main() {
  cout << "╔════════════════════════════════════════════════════════════╗"
       << endl;
  cout << "║      DOUBLY LINKED LIST - COMPREHENSIVE GUIDE              ║"
       << endl;
  cout << "║          Part 4, Topic 24.2: Linear Data Structures        ║"
       << endl;
  cout << "╚════════════════════════════════════════════════════════════╝"
       << endl;

  example_1_basic_operations();
  example_2_insert_head();
  example_3_insert_position();
  example_4_delete_operations();
  example_5_backward_traversal();
  example_6_middle_element();
  example_7_delete_advantage();
  example_8_bidirectional_check();

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
