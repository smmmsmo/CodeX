/*
================================================================================
                 TOPIC 24.2: LINKED LISTS - CIRCULAR LINKED LISTS
                    Part 4: Data Structures - Linear Data Structures
================================================================================

CONCEPT BREAKDOWN:
1. Circular structure with no null termination
2. Tail points back to head
3. Insertion and deletion operations
4. Traversal and loop detection
5. Applications of circular linked lists
6. Memory considerations

KEY LEARNING POINTS:
- Last node points to first node (circular)
- No null pointer at the end
- Efficient for round-robin scheduling
- Good for representing circular buffers
- Can traverse indefinitely if not careful

================================================================================
                             SECTION 1: THEORY
================================================================================

1. WHAT IS A CIRCULAR LINKED LIST?
   - Linked list where last node points back to first node
   - No null pointer to mark the end
   - Forms a circle/cycle by design
   - Can be singly or doubly circular

2. NODE STRUCTURE (Same as single LL):
   struct Node {
       int data;
       Node* next;  // Points back to head when at end
   };

3. REPRESENTATION:
   Single Linked List: 1 -> 2 -> 3 -> NULL
   Circular Linked List: 1 -> 2 -> 3 -> (back to 1)

4. ADVANTAGES:
   - No need to check for NULL (be careful!)
   - Efficient for round-robin algorithms
   - Good for implementing circular buffers
   - Any node can be accessed as starting point

5. DISADVANTAGES:
   - Risk of infinite loop
   - Must use different loop conditions
   - Slightly more complex operations

6. TIME COMPLEXITY:
   Operation              Time Complexity
   ─────────────────────────────────────
   insert_at_head         O(1)
   insert_at_end          O(n)
   delete_at_head         O(1)
   delete_at_end          O(n)
   search                 O(n)
   traversal              O(n)

================================================================================
                         SECTION 2: CODE EXAMPLES
================================================================================

*/

#include <iostream>

using std::cout;
using std::endl;

// Node structure for circular linked list
struct CNode {
  int data;
  CNode *next;

  CNode(int value) : data(value), next(nullptr) {}
};

class CircularLinkedList {
private:
  CNode *head;

public:
  CircularLinkedList() : head(nullptr) {}

  ~CircularLinkedList() {
    if (head == nullptr)
      return;

    CNode *current = head->next;
    while (current != head) {
      CNode *temp = current;
      current = current->next;
      delete temp;
    }
    delete head;
  }

  // ======================= INSERT AT HEAD =======================
  void insertAtHead(int value) {
    CNode *newNode = new CNode(value);

    if (head == nullptr) {
      newNode->next = newNode; // Point to itself
      head = newNode;
    } else {
      CNode *tail = head;
      while (tail->next != head) {
        tail = tail->next;
      }
      newNode->next = head;
      tail->next = newNode;
      head = newNode;
    }
  }

  // ======================= INSERT AT END =======================
  void insertAtEnd(int value) {
    CNode *newNode = new CNode(value);

    if (head == nullptr) {
      newNode->next = newNode;
      head = newNode;
    } else {
      CNode *current = head;
      while (current->next != head) {
        current = current->next;
      }
      current->next = newNode;
      newNode->next = head;
    }
  }

  // ======================= DELETE FROM HEAD =======================
  void deleteFromHead() {
    if (head == nullptr) {
      cout << "List is empty" << endl;
      return;
    }

    if (head->next == head) {
      delete head;
      head = nullptr;
    } else {
      CNode *tail = head;
      while (tail->next != head) {
        tail = tail->next;
      }

      CNode *temp = head;
      head = head->next;
      tail->next = head;
      delete temp;
    }
  }

  // ======================= DISPLAY =======================
  void display() {
    if (head == nullptr) {
      cout << "List is empty" << endl;
      return;
    }

    CNode *current = head;
    cout << "List: ";

    // Traverse until we come back to head
    do {
      cout << current->data << " -> ";
      current = current->next;
    } while (current != head);

    cout << "(back to " << head->data << ")" << endl;
  }

  // ======================= TRAVERSE WITH LIMIT =======================
  void traverseWithLimit(int limit) {
    if (head == nullptr) {
      cout << "List is empty" << endl;
      return;
    }

    CNode *current = head;
    cout << "First " << limit << " elements: ";

    for (int i = 0; i < limit && current != nullptr; i++) {
      cout << current->data << " ";
      current = current->next;
    }
    cout << endl;
  }

  // ======================= GET SIZE =======================
  int getSize() {
    if (head == nullptr)
      return 0;

    int count = 1;
    CNode *current = head->next;

    while (current != head) {
      count++;
      current = current->next;
    }
    return count;
  }

  // ======================= SEARCH =======================
  bool search(int value) {
    if (head == nullptr)
      return false;

    CNode *current = head;

    do {
      if (current->data == value) {
        return true;
      }
      current = current->next;
    } while (current != head);

    return false;
  }

  // ======================= ROTATE CLOCKWISE =======================
  void rotateClockwise(int k) {
    if (head == nullptr || k <= 0)
      return;

    int size = getSize();
    k = k % size; // Normalize rotation

    if (k == 0)
      return;

    // Move head pointer k steps forward
    CNode *current = head;
    for (int i = 0; i < k; i++) {
      current = current->next;
    }
    head = current;
  }
};

// ======================= EXAMPLE 1: BASIC OPERATIONS =======================
void example_1_basic_operations() {
  cout << "\n===== EXAMPLE 1: Basic Operations =====" << endl;

  CircularLinkedList list;

  cout << "Inserting 10, 20, 30, 40 at end:" << endl;
  list.insertAtEnd(10);
  list.insertAtEnd(20);
  list.insertAtEnd(30);
  list.insertAtEnd(40);
  list.display();

  cout << "\nSize: " << list.getSize() << endl;
}

// ======================= EXAMPLE 2: INSERT AT HEAD =======================
void example_2_insert_head() {
  cout << "\n===== EXAMPLE 2: Insert at Head =====" << endl;

  CircularLinkedList list;

  list.insertAtEnd(10);
  list.insertAtEnd(30);
  cout << "Initial: ";
  list.display();

  cout << "\nInsert 5 at head: ";
  list.insertAtHead(5);
  list.display();

  cout << "\nInsert 1 at head: ";
  list.insertAtHead(1);
  list.display();
}

// ======================= EXAMPLE 3: DELETE OPERATIONS =======================
void example_3_delete_operations() {
  cout << "\n===== EXAMPLE 3: Delete Operations =====" << endl;

  CircularLinkedList list;

  for (int i = 1; i <= 5; i++) {
    list.insertAtEnd(i);
  }
  cout << "Initial: ";
  list.display();

  cout << "\nDelete from head: ";
  list.deleteFromHead();
  list.display();

  cout << "\nDelete from head again: ";
  list.deleteFromHead();
  list.display();
}

// ======================= EXAMPLE 4: SEARCHING =======================
void example_4_searching() {
  cout << "\n===== EXAMPLE 4: Searching =====" << endl;

  CircularLinkedList list;

  for (int i = 1; i <= 5; i++) {
    list.insertAtEnd(i * 10);
  }
  list.display();

  cout << "\nSearching for 30: " << (list.search(30) ? "Found" : "Not Found")
       << endl;
  cout << "Searching for 55: " << (list.search(55) ? "Found" : "Not Found")
       << endl;
}

// ======================= EXAMPLE 5: TRAVERSAL WITH LIMIT
// =======================
void example_5_traversal_limit() {
  cout << "\n===== EXAMPLE 5: Traversal with Limit =====" << endl;

  CircularLinkedList list;

  for (int i = 1; i <= 4; i++) {
    list.insertAtEnd(i);
  }
  list.display();

  cout << "\nTraversing 5 elements (more than list size):" << endl;
  list.traverseWithLimit(5);

  cout << "\nTraversing 10 elements (much more than list size):" << endl;
  list.traverseWithLimit(10);

  cout << "\nNote: Without limit, we would have infinite loop!" << endl;
}

// ======================= EXAMPLE 6: ROUND ROBIN SCHEDULING
// =======================
void example_6_round_robin() {
  cout << "\n===== EXAMPLE 6: Round Robin Scheduling =====" << endl;

  CircularLinkedList queue;

  // Add processes
  for (int i = 1; i <= 3; i++) {
    queue.insertAtEnd(i);
  }
  cout << "Process queue: ";
  queue.display();

  cout << "\nRound Robin with time slice 2:" << endl;
  cout << "Initial: Process at head" << endl;

  for (int round = 1; round <= 6; round++) {
    queue.rotateClockwise(1); // Move to next process
    cout << "Round " << round << ": ";
    queue.traverseWithLimit(1);
  }
}

// ======================= EXAMPLE 7: CIRCULAR BUFFER =======================
void example_7_circular_buffer() {
  cout << "\n===== EXAMPLE 7: Circular Buffer Application =====" << endl;

  CircularLinkedList buffer;

  cout << "Adding elements to circular buffer: " << endl;
  for (int i = 1; i <= 6; i++) {
    buffer.insertAtEnd(i);
  }
  buffer.display();

  cout << "\nAccessing buffer in circular manner:" << endl;
  for (int i = 0; i < 10; i++) {
    buffer.traverseWithLimit(1);
    buffer.rotateClockwise(1);
  }
}

// ======================= EXAMPLE 8: CIRCULAR PROPERTIES
// =======================
void example_8_circular_properties() {
  cout << "\n===== EXAMPLE 8: Circular List Properties =====" << endl;

  CircularLinkedList list;

  list.insertAtEnd(1);
  list.insertAtEnd(2);
  list.insertAtEnd(3);

  cout << "Circular linked list: ";
  list.display();

  cout << "\nKey differences from linear linked list:" << endl;
  cout << "1. No NULL at the end" << endl;
  cout << "2. Last node points to first node" << endl;
  cout << "3. Can traverse indefinitely (need careful loop condition)" << endl;
  cout << "4. Good for round-robin and circular buffers" << endl;
  cout << "5. Size must be tracked or calculated differently" << endl;
}

/*
================================================================================
                            KEY CONCEPTS SUMMARY
================================================================================

CIRCULAR LINKED LIST PROPERTIES:
✓ No NULL pointer (forms cycle)
✓ Good for round-robin algorithms
✓ Efficient circular buffer implementation
✓ Dynamic size
✓ O(1) insertion/deletion at head

CRITICAL POINTS:
! Loop conditions must check against head, not nullptr
! Risk of infinite loops if not careful
! Useful for applications requiring circular access

COMPARISON WITH LINEAR LINKED LIST:
Linear: 1 -> 2 -> 3 -> NULL
Circular: 1 -> 2 -> 3 -> (back to 1)

TRAVERSAL DIFFERENCE:
Linear:
  for (Node* p = head; p != NULL; p = p->next) { }

Circular:
  for (Node* p = head; ; p = p->next) {
    // Must break manually or use different condition
    if (p->next == head) break;
  }

USE CASES:
✓ Round-robin CPU scheduling
✓ Circular buffer/queue
✓ Media player playlists (repeat/shuffle)
✓ Board games with circular turns

================================================================================
*/

/*
================================================================================
                        SECTION 3: PRACTICE EXERCISES
================================================================================

1. ROTATE COUNTER-CLOCKWISE:
   Rotate the circular list counter-clockwise by k positions.

2. SPLIT CIRCULAR LIST:
   Split circular list into two circular lists at position k.

3. CHECK IF CIRCULAR:
   Given a linked list, determine if it's circular or linear.

4. FIND MIDDLE:
   Find the middle element of a circular linked list.

5. MERGE TWO CIRCULAR LISTS:
   Merge two circular linked lists into one.

6. JOSEPHUS PROBLEM:
   Classic problem using circular linked list.

================================================================================
*/

int main() {
  cout << "╔════════════════════════════════════════════════════════════╗"
       << endl;
  cout << "║      CIRCULAR LINKED LIST - COMPREHENSIVE GUIDE            ║"
       << endl;
  cout << "║          Part 4, Topic 24.2: Linear Data Structures        ║"
       << endl;
  cout << "╚════════════════════════════════════════════════════════════╝"
       << endl;

  example_1_basic_operations();
  example_2_insert_head();
  example_3_delete_operations();
  example_4_searching();
  example_5_traversal_limit();
  example_6_round_robin();
  example_7_circular_buffer();
  example_8_circular_properties();

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
