/*
================================================================================
                           25.2: HEAPS
================================================================================
Comprehensive Learning Guide on Heap Data Structures

TOPIC BREAKDOWN:
• Min heaps and max heaps
• Heap property and structure
• Heapify operations
• Heap insertion and deletion
• Priority queue implementation using heaps
• Heap sort algorithm

KEY LEARNING POINTS:
✓ Understanding complete binary tree representation in arrays
✓ Maintaining heap property through percolation
✓ Efficient insertion and deletion in O(log n)
✓ Building heaps in O(n) time
✓ Using heaps for sorting and priority queues

================================================================================
                        PART 1: HEAP BASICS
================================================================================
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
======================= CONCEPT 1: WHAT IS A HEAP? =======================

A heap is a complete binary tree that satisfies the heap property:
- Max Heap: Parent node value >= child node values
- Min Heap: Parent node value <= child node values

IMPORTANT: A heap is NOT a Binary Search Tree (BST)
- BSTs order LEFT < PARENT < RIGHT
- Heaps only order PARENT and CHILDREN

Array Representation of a Complete Binary Tree:
                    Index layout for array [0, 1, 2, 3, 4, 5, 6]
                           0
                          / \
                         1   2
                        / \ / \
                       3  4 5  6

For node at index i:
- Parent index: (i - 1) / 2
- Left child: 2*i + 1
- Right child: 2*i + 2
*/

// ===== EXAMPLE 1: Basic Max Heap Operations =====
class MaxHeap {
private:
  vector<int> heap;

  // Helper: Get parent index
  int parentIndex(int i) { return (i - 1) / 2; }

  // Helper: Get left child index
  int leftChildIndex(int i) { return 2 * i + 1; }

  // Helper: Get right child index
  int rightChildIndex(int i) { return 2 * i + 1; }

  // Helper: Swap two elements
  void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
  }

  // Bubble up: Move element up to maintain heap property
  void percolateUp(int index) {
    while (index > 0 && heap[parentIndex(index)] < heap[index]) {
      swap(heap[parentIndex(index)], heap[index]);
      index = parentIndex(index);
    }
  }

  // Bubble down: Move element down to maintain heap property
  void percolateDown(int index) {
    int smallest = index;
    int left = leftChildIndex(index);
    int right = rightChildIndex(index);

    if (left < heap.size() && heap[left] > heap[smallest]) {
      smallest = left;
    }
    if (right < heap.size() && heap[right] > heap[smallest]) {
      smallest = right;
    }

    if (smallest != index) {
      swap(heap[index], heap[smallest]);
      percolateDown(smallest);
    }
  }

public:
  // Insert element
  void insert(int value) {
    heap.push_back(value);
    percolateUp(heap.size() - 1);
  }

  // Get maximum element (root)
  int getMax() {
    if (heap.empty()) {
      throw runtime_error("Heap is empty");
    }
    return heap[0];
  }

  // Remove maximum element
  int extractMax() {
    if (heap.empty()) {
      throw runtime_error("Heap is empty");
    }

    int max = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();

    if (!heap.empty()) {
      percolateDown(0);
    }
    return max;
  }

  // Print heap structure
  void print() {
    for (int val : heap) {
      cout << val << " ";
    }
    cout << endl;
  }

  bool isEmpty() { return heap.empty(); }

  int size() { return heap.size(); }
};

void example1_maxHeapBasics() {
  cout << "\n===== EXAMPLE 1: Max Heap Basics =====" << endl;

  MaxHeap maxHeap;

  // Insert elements
  int elements[] = {10, 5, 20, 2, 15, 30, 8};
  cout << "Inserting: 10, 5, 20, 2, 15, 30, 8" << endl;

  for (int elem : elements) {
    maxHeap.insert(elem);
  }

  cout << "Heap structure (array): ";
  maxHeap.print();

  cout << "\nExtracting elements (should be in descending order):" << endl;
  while (!maxHeap.isEmpty()) {
    cout << maxHeap.extractMax() << " ";
  }
  cout << endl;
}

/*
======================= CONCEPT 2: MIN HEAP =======================

Min Heap: Parent <= children
Every parent is smaller than its children
Useful for priority queues where smaller values have higher priority
*/

// ===== EXAMPLE 2: Min Heap Implementation =====
class MinHeap {
private:
  vector<int> heap;

  int parentIndex(int i) { return (i - 1) / 2; }
  int leftChildIndex(int i) { return 2 * i + 1; }
  int rightChildIndex(int i) { return 2 * i + 2; }

  void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
  }

  void percolateUp(int index) {
    while (index > 0 && heap[parentIndex(index)] > heap[index]) {
      swap(heap[parentIndex(index)], heap[index]);
      index = parentIndex(index);
    }
  }

  void percolateDown(int index) {
    int smallest = index;
    int left = leftChildIndex(index);
    int right = rightChildIndex(index);

    if (left < heap.size() && heap[left] < heap[smallest]) {
      smallest = left;
    }
    if (right < heap.size() && heap[right] < heap[smallest]) {
      smallest = right;
    }

    if (smallest != index) {
      swap(heap[index], heap[smallest]);
      percolateDown(smallest);
    }
  }

public:
  void insert(int value) {
    heap.push_back(value);
    percolateUp(heap.size() - 1);
  }

  int getMin() {
    if (heap.empty())
      throw runtime_error("Heap is empty");
    return heap[0];
  }

  int extractMin() {
    if (heap.empty())
      throw runtime_error("Heap is empty");

    int min = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();

    if (!heap.empty()) {
      percolateDown(0);
    }
    return min;
  }

  void print() {
    for (int val : heap) {
      cout << val << " ";
    }
    cout << endl;
  }

  bool isEmpty() { return heap.empty(); }
};

void example2_minHeap() {
  cout << "\n===== EXAMPLE 2: Min Heap =====" << endl;

  MinHeap minHeap;

  int elements[] = {15, 10, 20, 5, 12, 25, 8};
  cout << "Inserting: 15, 10, 20, 5, 12, 25, 8" << endl;

  for (int elem : elements) {
    minHeap.insert(elem);
  }

  cout << "Heap structure: ";
  minHeap.print();

  cout << "Extracting elements (should be in ascending order):" << endl;
  while (!minHeap.isEmpty()) {
    cout << minHeap.extractMin() << " ";
  }
  cout << endl;
}

/*
======================= CONCEPT 3: HEAPIFY =======================

Heapify: Convert an arbitrary array into a valid heap structure
Two approaches:
1. Bottom-up (Floyd's algorithm): O(n) - PREFERRED
2. Top-down: O(n log n) - Less efficient

Bottom-up heapify:
- Start from the last non-leaf node: index = (n-1)/2
- Call percolateDown on each node going backwards to root
*/

// ===== EXAMPLE 3: Building Heap with Heapify =====
class HeapBuilder {
private:
  vector<int> arr;

  int leftChildIndex(int i) { return 2 * i + 1; }
  int rightChildIndex(int i) { return 2 * i + 2; }

  void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
  }

  void percolateDown(int index, int size) {
    int smallest = index;
    int left = leftChildIndex(index);
    int right = rightChildIndex(index);

    if (left < size && arr[left] < arr[smallest]) {
      smallest = left;
    }
    if (right < size && arr[right] < arr[smallest]) {
      smallest = right;
    }

    if (smallest != index) {
      swap(arr[index], arr[smallest]);
      percolateDown(smallest, size);
    }
  }

public:
  // Floyd's Algorithm: O(n) heapify
  void buildMinHeap(vector<int> &input) {
    arr = input;
    int n = arr.size();

    // Start from last non-leaf node and percolate down
    for (int i = (n - 1) / 2; i >= 0; i--) {
      percolateDown(i, n);
    }
  }

  void print() {
    for (int val : arr) {
      cout << val << " ";
    }
    cout << endl;
  }

  vector<int> getHeap() { return arr; }
};

void example3_heapify() {
  cout << "\n===== EXAMPLE 3: Building Heap with Heapify (Floyd's) ====="
       << endl;

  vector<int> unsorted = {9, 5, 6, 2, 3, 7, 1, 4, 8};
  cout << "Original array: ";
  for (int val : unsorted)
    cout << val << " ";
  cout << endl;

  HeapBuilder builder;
  builder.buildMinHeap(unsorted);

  cout << "Min heap (via heapify): ";
  builder.print();

  cout << "\nNote: This creates valid heap in O(n) time" << endl;
  cout << "Much faster than inserting each element individually O(n log n)"
       << endl;
}

/*
======================= CONCEPT 4: HEAP SORT =======================

Heap Sort Algorithm:
1. Build a max heap from the array O(n)
2. Repeatedly extract max and place at end O(n log n)
3. Result: Sorted array in ascending order

Time: O(n log n) | Space: O(1) if done in-place
*/

// ===== EXAMPLE 4: Heap Sort Implementation =====
class HeapSorter {
private:
  void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
  }

  void maxHeapify(vector<int> &arr, int index, int size) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && arr[left] > arr[largest]) {
      largest = left;
    }
    if (right < size && arr[right] > arr[largest]) {
      largest = right;
    }

    if (largest != index) {
      swap(arr[index], arr[largest]);
      maxHeapify(arr, largest, size);
    }
  }

public:
  void heapSort(vector<int> &arr) {
    int n = arr.size();

    // Build max heap: O(n)
    for (int i = (n - 1) / 2; i >= 0; i--) {
      maxHeapify(arr, i, n);
    }

    // Extract elements one by one: O(n log n)
    for (int i = n - 1; i > 0; i--) {
      swap(arr[0], arr[i]);  // Move current max to end
      maxHeapify(arr, 0, i); // Maintain heap property
    }
  }
};

void example4_heapSort() {
  cout << "\n===== EXAMPLE 4: Heap Sort =====" << endl;

  vector<int> arr = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50};

  cout << "Original array: ";
  for (int val : arr)
    cout << val << " ";
  cout << endl;

  HeapSorter sorter;
  sorter.heapSort(arr);

  cout << "Sorted array: ";
  for (int val : arr)
    cout << val << " ";
  cout << endl;

  cout << "\nHeap Sort: O(n log n) time, O(1) space (in-place)" << endl;
}

/*
======================= CONCEPT 5: PRIORITY QUEUE =======================

Priority Queue: Abstract data type where elements have associated priorities
Can be efficiently implemented using heaps

Two types:
1. Max Priority Queue: Highest priority element removed first
2. Min Priority Queue: Lowest priority element removed first

Operations:
- enqueue(element, priority): Insert with priority
- dequeue(): Remove highest/lowest priority element
- peek(): View highest/lowest priority without removal
*/

// ===== EXAMPLE 5: Priority Queue using Min Heap =====
struct Element {
  int value;
  int priority; // Lower number = higher priority (0 is highest)
};

class PriorityQueue {
private:
  vector<Element> heap;

  int parentIndex(int i) { return (i - 1) / 2; }
  int leftChildIndex(int i) { return 2 * i + 1; }
  int rightChildIndex(int i) { return 2 * i + 2; }

  void swap(Element &a, Element &b) {
    Element temp = a;
    a = b;
    b = temp;
  }

  void percolateUp(int index) {
    while (index > 0 &&
           heap[parentIndex(index)].priority > heap[index].priority) {
      swap(heap[parentIndex(index)], heap[index]);
      index = parentIndex(index);
    }
  }

  void percolateDown(int index) {
    int smallest = index;
    int left = leftChildIndex(index);
    int right = rightChildIndex(index);

    if (left < heap.size() && heap[left].priority < heap[smallest].priority) {
      smallest = left;
    }
    if (right < heap.size() && heap[right].priority < heap[smallest].priority) {
      smallest = right;
    }

    if (smallest != index) {
      swap(heap[index], heap[smallest]);
      percolateDown(smallest);
    }
  }

public:
  void enqueue(int value, int priority) {
    heap.push_back({value, priority});
    percolateUp(heap.size() - 1);
  }

  Element dequeue() {
    if (heap.empty())
      throw runtime_error("Queue is empty");

    Element front = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();

    if (!heap.empty()) {
      percolateDown(0);
    }
    return front;
  }

  Element peek() {
    if (heap.empty())
      throw runtime_error("Queue is empty");
    return heap[0];
  }

  bool isEmpty() { return heap.empty(); }

  void printQueue() {
    cout << "Queue contents (priority order):" << endl;
    for (const auto &elem : heap) {
      cout << "  Value: " << elem.value << ", Priority: " << elem.priority
           << endl;
    }
  }
};

void example5_priorityQueue() {
  cout << "\n===== EXAMPLE 5: Priority Queue =====" << endl;

  PriorityQueue pq;

  cout << "Enqueuing elements with priorities:" << endl;
  pq.enqueue(10, 3); // value=10, priority=3
  cout << "  10 (priority 3)" << endl;
  pq.enqueue(20, 1); // value=20, priority=1
  cout << "  20 (priority 1)" << endl;
  pq.enqueue(15, 2); // value=15, priority=2
  cout << "  15 (priority 2)" << endl;
  pq.enqueue(30, 0); // value=30, priority=0
  cout << "  30 (priority 0)" << endl;
  pq.enqueue(5, 4); // value=5, priority=4
  cout << "  5 (priority 4)" << endl;

  pq.printQueue();

  cout << "\nDequeuing (removes highest priority first):" << endl;
  while (!pq.isEmpty()) {
    Element elem = pq.dequeue();
    cout << "Removed: value=" << elem.value << ", priority=" << elem.priority
         << endl;
  }
}

/*
================================================================================
                        KEY CONCEPTS SUMMARY
================================================================================

1. HEAP PROPERTY:
   ✓ Max Heap: parent >= children
   ✓ Min Heap: parent <= children
   ✓ Heap is NOT ordered like BST

2. ARRAY REPRESENTATION:
   ✓ Complete binary tree in array
   ✓ For index i:
     - Parent: (i-1)/2
     - Left child: 2i+1
     - Right child: 2i+2

3. OPERATIONS:
   ✓ Insert: O(log n) - add at end, percolate up
   ✓ DeleteMin/Max: O(log n) - remove root, move last, percolate down
   ✓ BuildHeap: O(n) - use heapify (Floyd's algorithm)
   ✓ Heapify: O(n) - convert array to heap

4. HEAP SORT:
   ✓ Time: O(n log n)
   ✓ Space: O(1) - in place
   ✓ Not stable but always optimal

5. APPLICATIONS:
   ✓ Priority queues
   ✓ Heap sort
   ✓ Finding k smallest/largest elements
   ✓ Dijkstra's algorithm
   ✓ Huffman coding
   ✓ Prim's algorithm

6. COMPARISON:
   ┌─────────────┬─────────┬────────┬─────────┬─────────┐
   │ Operation   │ Array   │ BST    │ Balanced│ Heap    │
   ├─────────────┼─────────┼────────┼─────────┼─────────┤
   │ Insert      │ O(n)    │ O(log) │ O(log)  │ O(log)  │
   │ Delete Min  │ O(n)    │ O(log) │ O(log)  │ O(log)  │
   │ Find Min    │ O(n)    │ O(log) │ O(log)  │ O(1)    │
   │ Build       │ O(n log)│ O(nlog)│ O(nlog) │ O(n)    │
   └─────────────┴─────────┴────────┴─────────┴─────────┘

================================================================================
                        COMMON MISTAKES TO AVOID
================================================================================

❌ MISTAKE 1: Confusing heap with BST
✓ CORRECT: Heaps only maintain parent-child order, not sorted order
          Use BST if you need full sorting capability

❌ MISTAKE 2: Not maintaining complete binary tree structure
✓ CORRECT: Always add/remove from bottom-right to keep tree complete

❌ MISTAKE 3: Using wrong child indices
✓ CORRECT: Left = 2i+1, Right = 2i+2 (0-indexed array)

❌ MISTAKE 4: Not percolating after modifications
✓ CORRECT: After any insertion/deletion, restore heap property

❌ MISTAKE 5: Using insertion to build heap from array
✓ CORRECT: Use heapify/Floyd's for O(n) instead of O(n log n)

❌ MISTAKE 6: Assuming heap is sorted
✓ CORRECT: Heap only guarantees parent-child relationship
          Use heap sort if you need sorted output

================================================================================
                        PRACTICE EXERCISES
================================================================================

Exercise 1: Implement a max heap with following methods:
  - insert(value)
  - extractMax()
  - getMax()
  - heapSize()

Exercise 2: Given an array, find the k largest elements efficiently

Exercise 3: Implement heap sort for both ascending and descending order

Exercise 4: Create a dynamic median finder using two heaps (min and max)

Exercise 5: Implement a frequency-based priority queue

Exercise 6: Find the kth smallest element in an unsorted array

Exercise 7: Merge k sorted arrays efficiently using heaps

Exercise 8: Implement a scheduler using priority queue

Exercise 9: Convert min heap to max heap in-place

Exercise 10: Implement heap operations using recursion

================================================================================
*/

// ===== MAIN FUNCTION =====
int main() {
  cout << "\n" << string(80, '=') << endl;
  cout << "         25.2: HEAPS - COMPREHENSIVE LEARNING GUIDE" << endl;
  cout << string(80, '=') << endl;

  try {
    example1_maxHeapBasics();
    example2_minHeap();
    example3_heapify();
    example4_heapSort();
    example5_priorityQueue();

    cout << "\n" << string(80, '=') << endl;
    cout << "All examples completed successfully!" << endl;
    cout << string(80, '=') << endl;
  } catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
  }

  return 0;
}

/*
================================================================================
EXPECTED OUTPUT:
================================================================================

===== EXAMPLE 1: Max Heap Basics =====
Inserting: 10, 5, 20, 2, 15, 30, 8
Heap structure (array): 30 15 20 2 5 10 8
Extracting elements (should be in descending order):
30 20 15 10 8 5 2

===== EXAMPLE 2: Min Heap =====
Inserting: 15, 10, 20, 5, 12, 25, 8
Heap structure: 5 10 8 15 12 25 20
Extracting elements (should be in ascending order):
5 8 10 12 15 20 25

===== EXAMPLE 3: Building Heap with Heapify (Floyd's) =====
Original array: 9 5 6 2 3 7 1 4 8
Min heap (via heapify): 1 2 6 4 3 7 5 9 8
Note: This creates valid heap in O(n) time
Much faster than inserting each element individually O(n log n)

===== EXAMPLE 4: Heap Sort =====
Original array: 64 34 25 12 22 11 90 88 45 50
Sorted array: 11 12 22 25 34 45 50 64 88 90
Heap Sort: O(n log n) time, O(1) space (in-place)

===== EXAMPLE 5: Priority Queue =====
Enqueuing elements with priorities:
  10 (priority 3)
  20 (priority 1)
  15 (priority 2)
  30 (priority 0)
  5 (priority 4)
Queue contents (priority order):
  Value: 30, Priority: 0
  Value: 20, Priority: 1
  Value: 15, Priority: 2
  Value: 10, Priority: 3
  Value: 5, Priority: 4
Dequeuing (removes highest priority first):
Removed: value=30, priority=0
Removed: value=20, priority=1
Removed: value=15, priority=2
Removed: value=10, priority=3
Removed: value=5, priority=4

================================================================================
                         ALL EXAMPLES COMPLETED
================================================================================

*/
