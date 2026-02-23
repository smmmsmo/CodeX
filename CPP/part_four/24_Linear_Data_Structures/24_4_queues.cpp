/*
================================================================================
                          TOPIC 24.4: QUEUES (FIFO)
                    Part 4: Data Structures - Linear Data Structures
================================================================================

CONCEPT BREAKDOWN:
1. Queue basics and FIFO principle
2. Queue implementation (array, circular, linked list)
3. Enqueue, dequeue, front operations
4. Circular queues and their benefits
5. Priority queues and deques
6. Applications: BFS, scheduling, buffering
7. Time/Space complexity analysis

KEY LEARNING POINTS:
- FIFO: First In First Out
- Multiple implementations with trade-offs
- O(1) enqueue and dequeue operations
- Used in BFS and level-order traversals
- Common in operating systems (task scheduling)
- Real-world analogy: grocery store queue

================================================================================
                             SECTION 1: THEORY
================================================================================

1. WHAT IS A QUEUE?
   - Abstract data type following FIFO principle
   - First element added is first to be removed
   - Like a real queue: first person in is first served
   - Add (enqueue) at rear, remove (dequeue) from front

2. QUEUE OPERATIONS:
   enqueue(x): Add x to rear
   dequeue(): Remove and return front element
   front(): Return front without removing
   isEmpty(): Check if queue is empty
   size(): Return number of elements

3. QUEUE STRUCTURE:
   Front                              Rear
   [A] -> [B] -> [C] -> [D] -> [E]
   Remove from front, add to rear

4. IMPLEMENTATIONS:
   Linear Array:
   - Simple but wasteful (front pointer moves)
   - Need to shift elements

   Circular Array:
   - Efficient space usage
   - front and rear pointers wrap around
   - Most practical array implementation

   Linked List:
   - Dynamic size
   - No shifting needed
   - Extra memory for pointers

5. TIME COMPLEXITY:

   Linear Array:          Circular Array:        Linked List:
   Enqueue: O(1)         Enqueue: O(1)          Enqueue: O(1)
   Dequeue: O(n)         Dequeue: O(1)          Dequeue: O(1)
   Front: O(1)           Front: O(1)            Front: O(1)

6. CIRCULAR QUEUE ADVANTAGE:
   Without circular:
   Enqueues: E1, E2, E3  | Dequeues D1, D2
   [E1][E2][E3][ ][ ]
               ↑rear    ↑front
   Wastage of front space!

   With circular:
   Enqueues wrap around to reuse space
   More efficient!

7. APPLICATIONS:
   - BFS graph traversal
   - Print queue in OS
   - CPU task scheduling
   - Message queues
   - Traffic flow
   - Website request handling

================================================================================
                         SECTION 2: CODE EXAMPLES
================================================================================

*/

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// ======================= CIRCULAR QUEUE =======================
template <typename T> class CircularQueue {
private:
  vector<T> elements;
  int front;
  int rear;
  int size;
  int capacity;

public:
  CircularQueue(int cap) : front(0), rear(-1), size(0), capacity(cap) {
    elements.resize(capacity);
  }

  void enqueue(T value) {
    if (size == capacity) {
      cout << "Queue is full!" << endl;
      return;
    }

    rear = (rear + 1) % capacity;
    elements[rear] = value;
    size++;
  }

  T dequeue() {
    if (isEmpty()) {
      throw std::out_of_range("Queue is empty!");
    }

    T value = elements[front];
    front = (front + 1) % capacity;
    size--;
    return value;
  }

  T getFront() const {
    if (isEmpty()) {
      throw std::out_of_range("Queue is empty!");
    }
    return elements[front];
  }

  bool isEmpty() const { return size == 0; }

  bool isFull() const { return size == capacity; }

  int getSize() const { return size; }

  void display() const {
    if (isEmpty()) {
      cout << "Queue is empty";
    } else {
      cout << "Queue (front to rear): ";
      int count = 0;
      int i = front;
      while (count < size) {
        cout << elements[i] << " ";
        i = (i + 1) % capacity;
        count++;
      }
    }
    cout << endl;
  }
};

// ======================= LINKED LIST QUEUE =======================
struct QNode {
  int data;
  QNode *next;

  QNode(int value) : data(value), next(nullptr) {}
};

class LinkedListQueue {
private:
  QNode *front;
  QNode *rear;
  int count;

public:
  LinkedListQueue() : front(nullptr), rear(nullptr), count(0) {}

  ~LinkedListQueue() {
    while (front != nullptr) {
      QNode *temp = front;
      front = front->next;
      delete temp;
    }
  }

  void enqueue(int value) {
    QNode *newNode = new QNode(value);

    if (rear == nullptr) {
      front = rear = newNode;
    } else {
      rear->next = newNode;
      rear = newNode;
    }
    count++;
  }

  int dequeue() {
    if (isEmpty()) {
      throw std::out_of_range("Queue is empty!");
    }

    QNode *temp = front;
    int value = temp->data;
    front = front->next;
    delete temp;

    if (front == nullptr) {
      rear = nullptr;
    }
    count--;
    return value;
  }

  int getFront() const {
    if (isEmpty()) {
      throw std::out_of_range("Queue is empty!");
    }
    return front->data;
  }

  bool isEmpty() const { return front == nullptr; }

  int getSize() const { return count; }

  void display() const {
    if (isEmpty()) {
      cout << "Queue is empty";
    } else {
      cout << "Queue (front to rear): ";
      QNode *current = front;
      while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
      }
    }
    cout << endl;
  }
};

// ======================= EXAMPLE 1: CIRCULAR QUEUE =======================
void example_1_circular_queue() {
  cout << "\n===== EXAMPLE 1: Circular Queue =====" << endl;

  CircularQueue<int> queue(5);

  cout << "Enqueuing 10, 20, 30, 40:" << endl;
  queue.enqueue(10);
  queue.enqueue(20);
  queue.enqueue(30);
  queue.enqueue(40);
  queue.display();

  cout << "\nFront element: " << queue.getFront() << endl;
  cout << "Size: " << queue.getSize() << endl;

  cout << "\nDequeuing 2 elements:" << endl;
  cout << queue.dequeue() << " " << queue.dequeue() << endl;
  queue.display();

  cout << "\nEnqueuing 50, 60:" << endl;
  queue.enqueue(50);
  queue.enqueue(60);
  queue.display();
}

// ======================= EXAMPLE 2: LINKED LIST QUEUE =======================
void example_2_ll_queue() {
  cout << "\n===== EXAMPLE 2: Linked List Queue =====" << endl;

  LinkedListQueue queue;

  cout << "Enqueuing 100, 200, 300, 400:" << endl;
  queue.enqueue(100);
  queue.enqueue(200);
  queue.enqueue(300);
  queue.enqueue(400);
  queue.display();

  cout << "\nFront: " << queue.getFront() << endl;
  cout << "Size: " << queue.getSize() << endl;

  cout << "\nDequeuing 3 elements:" << endl;
  cout << queue.dequeue() << " ";
  cout << queue.dequeue() << " ";
  cout << queue.dequeue() << endl;
  queue.display();
}

// ======================= EXAMPLE 3: BFS USING QUEUE =======================
void example_3_bfs() {
  cout << "\n===== EXAMPLE 3: BFS (Breadth-First Search) =====" << endl;

  LinkedListQueue queue;
  bool visited[7] = {false};

  cout << "Graph: 0->[1,2], 1->[3,4], 2->[5,6]" << endl;
  cout << "BFS starting from 0:" << endl;

  queue.enqueue(0);
  visited[0] = true;

  while (!queue.isEmpty()) {
    int node = queue.dequeue();
    cout << "Visit: " << node << " | Queue: ";

    vector<vector<int>> adj = {{1, 2}, {3, 4}, {5, 6}, {}, {}, {}, {}};

    for (int neighbor : adj[node]) {
      if (!visited[neighbor]) {
        queue.enqueue(neighbor);
        visited[neighbor] = true;
      }
    }

    queue.display();
  }
}

// ======================= EXAMPLE 4: TASK SCHEDULING =======================
void example_4_task_scheduling() {
  cout << "\n===== EXAMPLE 4: Task Scheduling (Round Robin) =====" << endl;

  CircularQueue<int> taskQueue(10);
  int timeSlice = 3;

  cout << "Tasks with burst time:" << endl;
  vector<int> tasks = {8, 4, 2, 1, 5};

  for (int i = 0; i < tasks.size(); i++) {
    taskQueue.enqueue(tasks[i]);
    cout << "Task " << i << " (burst: " << tasks[i] << ")" << endl;
  }

  cout << "\nRound-Robin with time slice " << timeSlice << ":" << endl;
  int totalTime = 0;

  while (!taskQueue.isEmpty()) {
    int burstTime = taskQueue.dequeue();
    int executeTime = (burstTime <= timeSlice) ? burstTime : timeSlice;
    totalTime += executeTime;

    cout << "Execute " << executeTime << " units (Total: " << totalTime << ")";

    if (burstTime > timeSlice) {
      int remaining = burstTime - timeSlice;
      cout << " | Remaining: " << remaining << " (re-queue)";
      taskQueue.enqueue(remaining);
    }
    cout << endl;
  }
}

// ======================= EXAMPLE 5: QUEUE SPACE EFFICIENCY
// =======================
void example_5_space_efficiency() {
  cout << "\n===== EXAMPLE 5: Circular Queue Space Efficiency =====" << endl;

  cout << "Scenario: Array of size 5" << endl;

  cout << "\nLinear Queue (problematic):" << endl;
  vector<int> linear = {0, 0, 10, 20, 30};
  cout << "After dequeuing 2 elements: ";
  for (int x : linear)
    cout << x << " ";
  cout << endl;
  cout << "Wasted space at front!" << endl;

  cout << "\nCircular Queue (efficient):" << endl;
  CircularQueue<int> circ(5);
  circ.enqueue(10);
  circ.enqueue(20);
  circ.enqueue(30);
  cout << "After enqueue 10, 20, 30: ";
  circ.display();

  circ.dequeue();
  circ.dequeue();
  cout << "After dequeue 2: ";
  circ.display();

  circ.enqueue(40);
  circ.enqueue(50);
  cout << "After enqueue 40, 50: ";
  circ.display();
  cout << "No wasted space! Elements wrap around." << endl;
}

// ======================= EXAMPLE 6: PRINTER QUEUE =======================
void example_6_printer_queue() {
  cout << "\n===== EXAMPLE 6: Printer Queue Simulation =====" << endl;

  CircularQueue<int> printerQueue(10);

  cout << "Jobs submitted (with number of pages):" << endl;
  vector<int> jobs = {5, 3, 8, 2, 6};

  for (int i = 0; i < jobs.size(); i++) {
    printerQueue.enqueue(jobs[i]);
    cout << "Job " << i << ": " << jobs[i] << " pages" << endl;
  }

  cout << "\nPrinting jobs (FIFO order):" << endl;
  int jobNum = 0;
  while (!printerQueue.isEmpty()) {
    int pages = printerQueue.dequeue();
    cout << "Printing Job " << jobNum << " (" << pages << " pages)" << endl;
    jobNum++;
  }
}

// ======================= EXAMPLE 7: TRAFFIC LIGHT INTERSECTION
// =======================
void example_7_traffic_light() {
  cout << "\n===== EXAMPLE 7: Traffic Light Queue =====" << endl;

  CircularQueue<string> carQueue(10);

  cout << "Cars arriving at intersection:" << endl;
  vector<string> cars = {"Car1", "Car2", "Car3", "Car4", "Car5"};

  for (const auto &car : cars) {
    carQueue.enqueue(car);
    cout << car << " arrived" << endl;
  }

  cout << "\nLight turns GREEN (30 seconds):" << endl;
  int secondsPassed = 0;
  while (!carQueue.isEmpty() && secondsPassed < 30) {
    string car = carQueue.dequeue();
    cout << car << " passed (time: " << (secondsPassed + 5) << "s)" << endl;
    secondsPassed += 5;
  }

  if (!carQueue.isEmpty()) {
    cout << "\nLight turns RED, queue waiting: ";
    carQueue.display();
  }
}

// ======================= EXAMPLE 8: DEQUE (DOUBLE-ENDED QUEUE)
// =======================
template <typename T> class Deque {
private:
  vector<T> elements;

public:
  void pushFront(T value) { elements.insert(elements.begin(), value); }

  void pushBack(T value) { elements.push_back(value); }

  T popFront() {
    if (isEmpty())
      throw std::out_of_range("Deque is empty!");
    T value = elements.front();
    elements.erase(elements.begin());
    return value;
  }

  T popBack() {
    if (isEmpty())
      throw std::out_of_range("Deque is empty!");
    T value = elements.back();
    elements.pop_back();
    return value;
  }

  bool isEmpty() const { return elements.empty(); }

  void display() const {
    cout << "Deque: ";
    for (const auto &e : elements) {
      cout << e << " ";
    }
    cout << endl;
  }
};

void example_8_deque() {
  cout << "\n===== EXAMPLE 8: Deque (Double-Ended Queue) =====" << endl;

  Deque<int> dq;

  cout << "Operations on Deque:" << endl;
  dq.pushBack(10);
  dq.pushBack(20);
  dq.pushFront(5);
  dq.display();

  cout << "\nPush 15 at front:" << endl;
  dq.pushFront(15);
  dq.display();

  cout << "\nPop from front:" << endl;
  cout << "Popped: " << dq.popFront() << endl;
  dq.display();

  cout << "\nPop from back:" << endl;
  cout << "Popped: " << dq.popBack() << endl;
  dq.display();
}

/*
================================================================================
                            KEY CONCEPTS SUMMARY
================================================================================

QUEUE PROPERTIES:
✓ FIFO principle
✓ O(1) enqueue and dequeue (with proper implementation)
✓ Useful for level-order traversals
✓ Common in OS and real-world applications

QUEUE IMPLEMENTATIONS:
1. Linear Array: Simple but inefficient (wastes space)
2. Circular Array: Efficient, reuses space
3. Linked List: Dynamic, no shifting needed

COMPARISON TABLE:
┌──────────┬──────────────┬────────────────┬─────────────┐
│ Operation│ Circular Arr │ Linked List    │ Priority Q  │
├──────────┼──────────────┼────────────────┼─────────────┤
│ Enqueue  │ O(1)         │ O(1)           │ O(log n)    │
│ Dequeue  │ O(1)         │ O(1)           │ O(log n)    │
│ Space    │ Fixed        │ Dynamic        │ Dynamic     │
└──────────┴──────────────┴────────────────┴─────────────┘

QUEUE vs STACK vs DEQUE:
Queue:  Front [FIFO] Rear     - First in, first out
Stack:  Top [LIFO]            - Last in, first out
Deque:  Front [flexible] Rear - Can add/remove from both ends

APPLICATIONS:
✓ BFS graph traversal
✓ Task scheduling (OS)
✓ Print queue
✓ Traffic flow simulation
✓ Message queue systems
✓ Breadth-first search
✓ Level-order tree traversal

CIRCULAR QUEUE ADVANTAGES:
✓ Efficient space utilization
✓ No element shifting
✓ O(1) operations
✓ Wrap-around capability

================================================================================
*/

/*
================================================================================
                        SECTION 3: PRACTICE EXERCISES
================================================================================

1. IMPLEMENT PRIORITY QUEUE:
   Dequeue elements based on priority, not insertion order.

2. SLIDING WINDOW MAXIMUM:
   Find maximum in sliding window using deque.

3. GENERATE NUMBERS:
   Generate n-digit numbers using BFS and queue.

4. ROTTING ORANGES:
   Simulate orange rot spread using BFS queue.

5. BINARY TREE LEVEL ORDER:
   Level-order traversal with queue.

6. QUEUE USING STACKS:
   Implement queue using two stacks.

7. FIRST NON-REPEATING CHARACTER:
   Find first non-repeating character using queue.

================================================================================
*/

int main() {
  cout << "╔════════════════════════════════════════════════════════════╗"
       << endl;
  cout << "║             QUEUES - COMPREHENSIVE GUIDE                   ║"
       << endl;
  cout << "║          Part 4, Topic 24.4: Linear Data Structures        ║"
       << endl;
  cout << "╚════════════════════════════════════════════════════════════╝"
       << endl;

  example_1_circular_queue();
  example_2_ll_queue();
  example_3_bfs();
  example_4_task_scheduling();
  example_5_space_efficiency();
  example_6_printer_queue();
  example_7_traffic_light();
  example_8_deque();

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
