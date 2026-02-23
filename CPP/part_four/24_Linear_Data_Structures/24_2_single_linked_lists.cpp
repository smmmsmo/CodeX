/*
================================================================================
                 TOPIC 24.2: LINKED LISTS - SINGLE LINKED LISTS
                    Part 4: Data Structures - Linear Data Structures
================================================================================

CONCEPT BREAKDOWN:
1. Node structure and creation
2. Single Linked List basics
3. Insertion operations (beginning, end, middle)
4. Deletion operations
5. Traversal and searching
6. Reversal and advanced operations
7. Time/Space complexity analysis

KEY LEARNING POINTS:
- Linked lists use nodes with data and pointer
- No contiguous memory required
- O(1) insertion/deletion at known positions
- O(n) access time
- Dynamic size without reallocation
- Useful for frequent insertions/deletions

================================================================================
                             SECTION 1: THEORY
================================================================================

1. WHAT IS A LINKED LIST?
   - A linear data structure with nodes connected by pointers
   - Each node contains: data + pointer to next node
   - Grows/shrinks dynamically
   - Non-contiguous memory allocation

2. NODE STRUCTURE:
   struct Node {
       int data;           // Data stored
       Node* next;         // Pointer to next node
   };

3. SINGLE LINKED LIST vs ARRAYS:

   Array:
   - Contiguous memory
   - O(1) random access
   - O(n) insertion/deletion
   - Fixed size (vector: flexible)

   Single Linked List:
   - Non-contiguous memory
   - O(n) random access
   - O(1) insertion/deletion (if position known)
   - Dynamic size
   - Extra memory for pointers

4. TIME COMPLEXITY:
   Operation              Time Complexity
   ─────────────────────────────────────
   insert_at_head         O(1)
   insert_at_tail         O(n)* or O(1) with tail pointer
   insert_at_middle       O(n)
   delete_from_head       O(1)
   delete_from_tail       O(n)
   delete_from_middle     O(n)
   search                 O(n)
   traverse               O(n)
   reverse                O(n)

5. SPACE COMPLEXITY:
   - O(n) for storing n elements
   - Extra O(1) per node for pointer

================================================================================
                         SECTION 2: CODE EXAMPLES
================================================================================

*/

#include <iostream>
#include <vector>

using std::cout;
using std::endl;

// Node structure for linked list
struct Node {
  int data;
  Node *next;

  Node(int value) : data(value), next(nullptr) {}
};

class SingleLinkedList {
private:
  Node *head;

public:
  SingleLinkedList() : head(nullptr) {}

  ~SingleLinkedList() {
    while (head != nullptr) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }
  }

  // ======================= INSERT AT HEAD =======================
  void insertAtHead(int value) {
    Node *newNode = new Node(value);
    newNode->next = head;
    head = newNode;
  }

  // ======================= INSERT AT END =======================
  void insertAtEnd(int value) {
    Node *newNode = new Node(value);

    if (head == nullptr) {
      head = newNode;
      return;
    }

    Node *current = head;
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = newNode;
  }

  // ======================= INSERT AT POSITION =======================
  void insertAtPosition(int value, int position) {
    if (position <= 0) {
      insertAtHead(value);
      return;
    }

    Node *current = head;
    for (int i = 0; i < position - 1 && current != nullptr; i++) {
      current = current->next;
    }

    if (current == nullptr) {
      cout << "Position out of range" << endl;
      return;
    }

    Node *newNode = new Node(value);
    newNode->next = current->next;
    current->next = newNode;
  }

  // ======================= DELETE FROM HEAD =======================
  void deleteFromHead() {
    if (head == nullptr) {
      cout << "List is empty" << endl;
      return;
    }

    Node *temp = head;
    head = head->next;
    delete temp;
  }

  // ======================= DELETE FROM END =======================
  void deleteFromEnd() {
    if (head == nullptr) {
      cout << "List is empty" << endl;
      return;
    }

    if (head->next == nullptr) {
      delete head;
      head = nullptr;
      return;
    }

    Node *current = head;
    while (current->next->next != nullptr) {
      current = current->next;
    }

    delete current->next;
    current->next = nullptr;
  }

  // ======================= DELETE AT POSITION =======================
  void deleteAtPosition(int position) {
    if (head == nullptr) {
      cout << "List is empty" << endl;
      return;
    }

    if (position == 0) {
      deleteFromHead();
      return;
    }

    Node *current = head;
    for (int i = 0; i < position - 1 && current != nullptr; i++) {
      current = current->next;
    }

    if (current == nullptr || current->next == nullptr) {
      cout << "Position out of range" << endl;
      return;
    }

    Node *temp = current->next;
    current->next = temp->next;
    delete temp;
  }

  // ======================= TRAVERSE AND PRINT =======================
  void display() {
    if (head == nullptr) {
      cout << "List is empty" << endl;
      return;
    }

    Node *current = head;
    cout << "List: ";
    while (current != nullptr) {
      cout << current->data << " -> ";
      current = current->next;
    }
    cout << "NULL" << endl;
  }

  // ======================= SEARCH =======================
  bool search(int value) {
    Node *current = head;
    while (current != nullptr) {
      if (current->data == value) {
        return true;
      }
      current = current->next;
    }
    return false;
  }

  // ======================= GET SIZE =======================
  int getSize() {
    int count = 0;
    Node *current = head;
    while (current != nullptr) {
      count++;
      current = current->next;
    }
    return count;
  }

  // ======================= REVERSE =======================
  void reverse() {
    Node *prev = nullptr;
    Node *current = head;
    Node *next = nullptr;

    while (current != nullptr) {
      next = current->next; // Save next
      current->next = prev; // Reverse the link
      prev = current;       // Move prev forward
      current = next;       // Move current forward
    }

    head = prev;
  }

  // ======================= FIND MIDDLE =======================
  int findMiddle() {
    if (head == nullptr) {
      cout << "List is empty" << endl;
      return -1;
    }

    Node *slow = head;
    Node *fast = head;

    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
    }

    return slow->data;
  }

  // ======================= DETECT CYCLE =======================
  bool hasCycle() {
    Node *slow = head;
    Node *fast = head;

    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;

      if (slow == fast) {
        return true; // Cycle detected
      }
    }

    return false;
  }
};

// ======================= EXAMPLE 1: BASIC OPERATIONS =======================
void example_1_basic_operations() {
  cout << "\n===== EXAMPLE 1: Basic Operations =====" << endl;

  SingleLinkedList list;

  cout << "Inserting 10, 20, 30 at head:" << endl;
  list.insertAtHead(10);
  list.insertAtHead(20);
  list.insertAtHead(30);
  list.display();

  cout << "\nSize: " << list.getSize() << endl;

  cout << "\nDeleting from head:" << endl;
  list.deleteFromHead();
  list.display();
}

// ======================= EXAMPLE 2: INSERT AT DIFFERENT POSITIONS
// =======================
void example_2_insert_positions() {
  cout << "\n===== EXAMPLE 2: Insert at Different Positions =====" << endl;

  SingleLinkedList list;

  list.insertAtEnd(10);
  list.insertAtEnd(30);
  list.insertAtEnd(40);
  cout << "Initial list: ";
  list.display();

  cout << "\nInsert 20 at position 1: ";
  list.insertAtPosition(20, 1);
  list.display();

  cout << "\nInsert 5 at position 0: ";
  list.insertAtPosition(5, 0);
  list.display();

  cout << "\nInsert 50 at position 5: ";
  list.insertAtPosition(50, 5);
  list.display();
}

// ======================= EXAMPLE 3: DELETE OPERATIONS =======================
void example_3_delete_operations() {
  cout << "\n===== EXAMPLE 3: Delete Operations =====" << endl;

  SingleLinkedList list;

  for (int i = 1; i <= 5; i++) {
    list.insertAtEnd(i * 10);
  }
  cout << "Initial list: ";
  list.display();

  cout << "\nDelete from head: ";
  list.deleteFromHead();
  list.display();

  cout << "\nDelete from end: ";
  list.deleteFromEnd();
  list.display();

  cout << "\nDelete at position 1: ";
  list.deleteAtPosition(1);
  list.display();
}

// ======================= EXAMPLE 4: SEARCHING =======================
void example_4_searching() {
  cout << "\n===== EXAMPLE 4: Searching =====" << endl;

  SingleLinkedList list;

  for (int i = 1; i <= 5; i++) {
    list.insertAtEnd(i * 10);
  }
  list.display();

  cout << "\nSearching for 30: " << (list.search(30) ? "Found" : "Not Found")
       << endl;
  cout << "Searching for 25: " << (list.search(25) ? "Found" : "Not Found")
       << endl;
  cout << "Searching for 50: " << (list.search(50) ? "Found" : "Not Found")
       << endl;
}

// ======================= EXAMPLE 5: REVERSE =======================
void example_5_reverse() {
  cout << "\n===== EXAMPLE 5: Reverse =====" << endl;

  SingleLinkedList list;

  for (int i = 1; i <= 5; i++) {
    list.insertAtEnd(i);
  }
  cout << "Original list: ";
  list.display();

  cout << "After reverse: ";
  list.reverse();
  list.display();

  cout << "Reverse again: ";
  list.reverse();
  list.display();
}

// ======================= EXAMPLE 6: FIND MIDDLE =======================
void example_6_find_middle() {
  cout << "\n===== EXAMPLE 6: Find Middle =====" << endl;

  SingleLinkedList list;

  for (int i = 1; i <= 5; i++) {
    list.insertAtEnd(i);
  }
  cout << "List with 5 elements: ";
  list.display();
  cout << "Middle element: " << list.findMiddle() << endl;

  SingleLinkedList list2;
  for (int i = 1; i <= 6; i++) {
    list2.insertAtEnd(i);
  }
  cout << "\nList with 6 elements: ";
  list2.display();
  cout << "Middle element: " << list2.findMiddle() << endl;
}

// ======================= EXAMPLE 7: LINKED LIST PERFORMANCE
// =======================
void example_7_performance() {
  cout << "\n===== EXAMPLE 7: Linked List Performance =====" << endl;

  SingleLinkedList list;

  cout << "Adding 1000 elements at beginning:" << endl;
  for (int i = 0; i < 1000; i++) {
    list.insertAtHead(i);
  }
  cout << "Size: " << list.getSize() << endl;

  cout << "\nAdding 1000 elements at end:" << endl;
  for (int i = 1000; i < 2000; i++) {
    list.insertAtEnd(i);
  }
  cout << "Size: " << list.getSize() << endl;
  cout << "Note: insertAtEnd is O(n) because we traverse to end each time!"
       << endl;
}

// ======================= EXAMPLE 8: CLEAR AND REBUILD =======================
void example_8_operations() {
  cout << "\n===== EXAMPLE 8: Creating and Modifying Lists =====" << endl;

  SingleLinkedList list;

  cout << "Building list: 5 -> 4 -> 3 -> 2 -> 1" << endl;
  for (int i = 5; i >= 1; i--) {
    list.insertAtHead(i);
  }
  list.display();

  cout << "\nRemoving middle 3 elements:" << endl;
  list.deleteAtPosition(2);
  list.deleteAtPosition(2);
  list.deleteAtPosition(2);
  list.display();

  cout << "\nReversing list:" << endl;
  list.reverse();
  list.display();
}

/*
================================================================================
                            KEY CONCEPTS SUMMARY
================================================================================

SINGLE LINKED LIST PROPERTIES:
✓ Dynamic size
✓ No random access (must traverse)
✓ O(1) insertion/deletion if position known
✓ O(n) traversal
✓ Non-contiguous memory

TIME COMPLEXITY ANALYSIS:
┌──────────────────┬────────────┐
│ Operation        │ Complexity │
├──────────────────┼────────────┤
│ Insert at head   │ O(1)       │
│ Insert at end    │ O(n)       │
│ Insert at mid    │ O(n)       │
│ Delete at head   │ O(1)       │
│ Delete at end    │ O(n)       │
│ Delete at mid    │ O(n)       │
│ Search           │ O(n)       │
│ Traverse         │ O(n)       │
│ Reverse          │ O(n)       │
│ Find middle      │ O(n)       │
└──────────────────┴────────────┘

SPACE COMPLEXITY:
- O(n) for data
- O(n) for pointers
- Total: O(n)

ADVANTAGES:
✓ Dynamic size
✓ Efficient insertion/deletion at known position
✓ No memory waste from capacity allocation
✓ Good for problems requiring frequent modifications

DISADVANTAGES:
✗ No random access
✗ Extra memory for pointers
✗ Cache unfriendly (scattered memory)
✗ Finding middle/tail requires traversal

================================================================================
*/

/*
================================================================================
                        SECTION 3: PRACTICE EXERCISES
================================================================================

1. REVERSE K NODES:
   Reverse groups of K nodes in the linked list.
   Example: 1->2->3->4->5, K=2 becomes 2->1->4->3->5

2. MERGE TWO SORTED LISTS:
   Merge two sorted linked lists into one sorted list.

3. PALINDROME CHECK:
   Check if a linked list is a palindrome.

4. REMOVE NTH NODE:
   Remove the nth node from the end of the list.

5. DUPLICATE REMOVAL:
   Remove duplicate nodes from a sorted linked list.

6. INTERSECTION POINT:
   Find the intersection point of two linked lists (if they merge).

7. LOOP REMOVAL:
   Detect a cycle and remove it.

8. PARTITION LIST:
   Partition list around a value (like quicksort partition).

================================================================================
*/

/*
================================================================================
                         COMMON MISTAKES TO AVOID
================================================================================

MISTAKE 1: Memory Leak - Not Deleting Nodes
❌ WRONG:
   void deleteList(Node* head) {
       head = nullptr;  // Memory still allocated!
   }

✓ RIGHT:
   void deleteList(Node*& head) {
       while (head != nullptr) {
           Node* temp = head;
           head = head->next;
           delete temp;
       }
   }

────────────────────────────────────────────────────────────────────

MISTAKE 2: Null Pointer Dereference
❌ WRONG:
   void deleteAtPosition(int pos) {
       Node* current = head;
       for (int i = 0; i < pos - 1; i++) {
           current = current->next;  // May be nullptr!
       }
       current->next = current->next->next;  // Crash!
   }

✓ RIGHT:
   void deleteAtPosition(int pos) {
       Node* current = head;
       for (int i = 0; i < pos - 1 && current != nullptr; i++) {
           current = current->next;
       }
       if (current != nullptr && current->next != nullptr) {
           current->next = current->next->next;
       }
   }

────────────────────────────────────────────────────────────────────

MISTAKE 3: Lost Reference to Head
❌ WRONG:
   Node* head = new Node(10);
   head = head->next;  // Lost reference to first node!

✓ RIGHT:
   Node* head = new Node(10);
   Node* current = head;
   current = current->next;  // head still points to first

════════════════════════════════════════════════════════════════════════

================================================================================
*/

int main() {
  cout << "╔════════════════════════════════════════════════════════════╗"
       << endl;
  cout << "║       SINGLE LINKED LIST - COMPREHENSIVE GUIDE              ║"
       << endl;
  cout << "║          Part 4, Topic 24.2: Linear Data Structures        ║"
       << endl;
  cout << "╚════════════════════════════════════════════════════════════╝"
       << endl;

  example_1_basic_operations();
  example_2_insert_positions();
  example_3_delete_operations();
  example_4_searching();
  example_5_reverse();
  example_6_find_middle();
  example_7_performance();
  example_8_operations();

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
