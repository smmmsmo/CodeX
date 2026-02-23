/*
================================================================================
                          TOPIC 24.3: STACKS (LIFO)
                    Part 4: Data Structures - Linear Data Structures
================================================================================

CONCEPT BREAKDOWN:
1. Stack basics and LIFO principle
2. Stack implementation (array and linked list based)
3. Push, pop, peek operations
4. Applications: expression evaluation, backtracking, DFS
5. Time/Space complexity analysis
6. Stack problems and solutions

KEY LEARNING POINTS:
- LIFO: Last In First Out
- Two implementations: array-based and linked list-based
- O(1) push and pop operations
- Useful for recursive algorithms and expression parsing
- Common in compiler design and memory management

================================================================================
                             SECTION 1: THEORY
================================================================================

1. WHAT IS A STACK?
   - Abstract data type following LIFO principle
   - Last element added is first to be removed
   - Like stacking plates: add to top, remove from top
   - Two main operations: push (add) and pop (remove)

2. STACK OPERATIONS:
   push(x): Add element x to top
   pop(): Remove and return top element
   peek(): Return top element without removing
   isEmpty(): Check if stack is empty
   size(): Return number of elements

3. STACK STRUCTURE:
   Top of Stack: [E]
                 [D]
                 [C]
                 [B]
   Bottom:       [A]

   Push E, then push D, then pop = D

4. IMPLEMENTATION APPROACHES:
   Array-based:
   - Fixed size or dynamic (vector)
   - O(1) push, pop
   - Simple implementation

   Linked List-based:
   - Dynamic size naturally
   - O(1) push, pop (at head)
   - More memory overhead

5. TIME COMPLEXITY (Both implementations):
   Operation      Time Complexity
   ──────────────────────────────
   push()         O(1)
   pop()          O(1)
   peek()         O(1)
   isEmpty()      O(1)
   size()         O(1) or O(n)*

6. APPLICATIONS:
   - Function call stack (recursion)
   - Browser back button
   - Undo/Redo functionality
   - Expression evaluation
   - Depth-first search
   - Backtracking algorithms
   - Balanced parentheses checking

================================================================================
                         SECTION 2: CODE EXAMPLES
================================================================================

*/

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// ======================= STACK USING ARRAY (VECTOR) =======================
template <typename T> class ArrayStack {
private:
  vector<T> elements;

public:
  void push(T value) { elements.push_back(value); }

  T pop() {
    if (isEmpty()) {
      throw std::out_of_range("Stack is empty!");
    }
    T value = elements.back();
    elements.pop_back();
    return value;
  }

  T peek() const {
    if (isEmpty()) {
      throw std::out_of_range("Stack is empty!");
    }
    return elements.back();
  }

  bool isEmpty() const { return elements.empty(); }

  int size() const { return elements.size(); }

  void display() const {
    cout << "Stack (top to bottom): ";
    if (isEmpty()) {
      cout << "Empty";
    } else {
      for (int i = elements.size() - 1; i >= 0; i--) {
        cout << elements[i] << " ";
      }
    }
    cout << endl;
  }
};

// ======================= STACK USING LINKED LIST =======================
struct LLNode {
  int data;
  LLNode *next;

  LLNode(int value) : data(value), next(nullptr) {}
};

class LinkedListStack {
private:
  LLNode *top;
  int count;

public:
  LinkedListStack() : top(nullptr), count(0) {}

  ~LinkedListStack() {
    while (top != nullptr) {
      LLNode *temp = top;
      top = top->next;
      delete temp;
    }
  }

  void push(int value) {
    LLNode *newNode = new LLNode(value);
    newNode->next = top;
    top = newNode;
    count++;
  }

  int pop() {
    if (isEmpty()) {
      throw std::out_of_range("Stack is empty!");
    }
    LLNode *temp = top;
    int value = temp->data;
    top = top->next;
    delete temp;
    count--;
    return value;
  }

  int peek() const {
    if (isEmpty()) {
      throw std::out_of_range("Stack is empty!");
    }
    return top->data;
  }

  bool isEmpty() const { return top == nullptr; }

  int size() const { return count; }

  void display() const {
    cout << "Stack (top to bottom): ";
    if (isEmpty()) {
      cout << "Empty";
    } else {
      LLNode *current = top;
      while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
      }
    }
    cout << endl;
  }
};

// ======================= EXAMPLE 1: BASIC ARRAY STACK =======================
void example_1_array_stack() {
  cout << "\n===== EXAMPLE 1: Array-Based Stack =====" << endl;

  ArrayStack<int> stack;

  cout << "Pushing 10, 20, 30, 40, 50:" << endl;
  for (int i = 1; i <= 5; i++) {
    stack.push(i * 10);
  }
  stack.display();

  cout << "\nTop element (peek): " << stack.peek() << endl;
  cout << "Stack size: " << stack.size() << endl;

  cout << "\nPopping elements:" << endl;
  while (!stack.isEmpty()) {
    cout << "Popped: " << stack.pop() << ", ";
    stack.display();
  }
}

// ======================= EXAMPLE 2: LINKED LIST STACK =======================
void example_2_ll_stack() {
  cout << "\n===== EXAMPLE 2: Linked List-Based Stack =====" << endl;

  LinkedListStack stack;

  cout << "Pushing 100, 200, 300:" << endl;
  stack.push(100);
  stack.push(200);
  stack.push(300);
  stack.display();

  cout << "\nPeek: " << stack.peek() << endl;
  cout << "Size: " << stack.size() << endl;

  cout << "\nPopping all:" << endl;
  cout << stack.pop() << " " << stack.pop() << " " << stack.pop() << endl;
  cout << "Is empty: " << (stack.isEmpty() ? "Yes" : "No") << endl;
}

// ======================= EXAMPLE 3: BALANCED PARENTHESES
// =======================
bool isBalanced(string expr) {
  ArrayStack<char> stack;

  for (char ch : expr) {
    if (ch == '(' || ch == '{' || ch == '[') {
      stack.push(ch);
    } else if (ch == ')' || ch == '}' || ch == ']') {
      if (stack.isEmpty()) {
        return false;
      }
      char top = stack.pop();

      if ((ch == ')' && top != '(') || (ch == '}' && top != '{') ||
          (ch == ']' && top != '[')) {
        return false;
      }
    }
  }

  return stack.isEmpty();
}

void example_3_balanced_parentheses() {
  cout << "\n===== EXAMPLE 3: Balanced Parentheses =====" << endl;

  vector<string> expressions = {"{[()]}", "{[(])}", "((()))", "[{]}"};

  for (const auto &expr : expressions) {
    cout << expr << ": " << (isBalanced(expr) ? "Balanced" : "Not Balanced")
         << endl;
  }
}

// ======================= EXAMPLE 4: DECIMAL TO BINARY =======================
string decimalToBinary(int num) {
  ArrayStack<int> stack;

  if (num == 0)
    return "0";

  while (num > 0) {
    stack.push(num % 2);
    num /= 2;
  }

  string binary = "";
  while (!stack.isEmpty()) {
    binary += std::to_string(stack.pop());
  }

  return binary;
}

void example_4_decimal_to_binary() {
  cout << "\n===== EXAMPLE 4: Decimal to Binary Conversion =====" << endl;

  vector<int> numbers = {5, 10, 25, 100, 255};

  for (int num : numbers) {
    cout << num << " -> " << decimalToBinary(num) << endl;
  }
}

// ======================= EXAMPLE 5: UNDO FUNCTIONALITY =======================
void example_5_undo_redo() {
  cout << "\n===== EXAMPLE 5: Undo Functionality (Stack) =====" << endl;

  ArrayStack<string> undoStack;
  ArrayStack<string> redoStack;

  string document = "";

  cout << "Initial document: \"" << document << "\"" << endl;

  // Add text
  cout << "\nTyping 'Hello':" << endl;
  undoStack.push(document);
  document = "Hello";
  cout << "Document: \"" << document << "\"" << endl;

  cout << "\nTyping ' World':" << endl;
  undoStack.push(document);
  document = "Hello World";
  cout << "Document: \"" << document << "\"" << endl;

  cout << "\nUndo:" << endl;
  redoStack.push(document);
  document = undoStack.pop();
  cout << "Document: \"" << document << "\"" << endl;

  cout << "\nUndo again:" << endl;
  redoStack.push(document);
  document = undoStack.pop();
  cout << "Document: \"" << document << "\"" << endl;

  cout << "\nRedo:" << endl;
  undoStack.push(document);
  document = redoStack.pop();
  cout << "Document: \"" << document << "\"" << endl;
}

// ======================= EXAMPLE 6: DEPTH FIRST SEARCH SIMULATION
// =======================
void example_6_dfs_simulation() {
  cout << "\n===== EXAMPLE 6: DFS Using Stack =====" << endl;

  ArrayStack<int> stack;
  bool visited[6] = {false};

  cout << "Graph adjacency: 0->[1,2], 1->[3], 2->[4], 3->[5]" << endl;
  cout << "Starting DFS from 0:" << endl;

  stack.push(0);

  while (!stack.isEmpty()) {
    int node = stack.pop();

    if (!visited[node]) {
      cout << "Visiting node: " << node << endl;
      visited[node] = true;

      // Add adjacent nodes (in reverse for proper DFS order)
      if (node == 0) {
        stack.push(2);
        stack.push(1);
      } else if (node == 1) {
        stack.push(3);
      } else if (node == 2) {
        stack.push(4);
      } else if (node == 3) {
        stack.push(5);
      }
    }
  }
}

// ======================= EXAMPLE 7: INFIX TO POSTFIX =======================
int precedence(char op) {
  if (op == '+' || op == '-')
    return 1;
  if (op == '*' || op == '/')
    return 2;
  return 0;
}

string infixToPostfix(string infix) {
  ArrayStack<char> stack;
  string postfix = "";

  for (char ch : infix) {
    if (ch >= '0' && ch <= '9') {
      postfix += ch;
    } else if (ch == '(') {
      stack.push(ch);
    } else if (ch == ')') {
      while (!stack.isEmpty() && stack.peek() != '(') {
        postfix += stack.pop();
      }
      if (!stack.isEmpty()) {
        stack.pop(); // Remove '('
      }
    } else {
      while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(ch)) {
        postfix += stack.pop();
      }
      stack.push(ch);
    }
  }

  while (!stack.isEmpty()) {
    postfix += stack.pop();
  }

  return postfix;
}

void example_7_infix_postfix() {
  cout << "\n===== EXAMPLE 7: Infix to Postfix Conversion =====" << endl;

  vector<string> expressions = {"1+2", "(1+2)*3", "1+2*3", "((1+2)*3)"};

  for (const auto &expr : expressions) {
    cout << "Infix: " << expr << " -> Postfix: " << infixToPostfix(expr)
         << endl;
  }
}

// ======================= EXAMPLE 8: RECURSIVE FUNCTION SIMULATION
// =======================
void example_8_recursion_simulation() {
  cout << "\n===== EXAMPLE 8: Simulating Recursion with Stack =====" << endl;

  cout << "Simulating factorial(5) using stack:" << endl;
  cout << "(Instead of actual recursion, stack stores state)" << endl;

  ArrayStack<int> callStack;

  cout << "\nPush calls:" << endl;
  for (int i = 5; i >= 1; i--) {
    callStack.push(i);
    cout << "Push " << i << ", Stack size: " << callStack.size() << endl;
  }

  cout << "\nPop calls (unwinding recursion):" << endl;
  int factorial = 1;
  while (!callStack.isEmpty()) {
    int val = callStack.pop();
    factorial *= val;
    cout << "Pop " << val << ", Factorial so far: " << factorial << endl;
  }
}

/*
================================================================================
                            KEY CONCEPTS SUMMARY
================================================================================

STACK PROPERTIES:
✓ LIFO principle
✓ O(1) push, pop, peek
✓ Simple to implement
✓ Very useful in practice

STACK vs QUEUE:
Stack (LIFO):    Last in -> First out   [Push/Pop at same end]
Queue (FIFO):    First in -> First out  [Push at rear, Pop at front]

IMPLEMENTATION COMPARISON:
┌──────────┬─────────────────┬──────────────────┐
│ Operation│ Array-Based     │ Linked List      │
├──────────┼─────────────────┼──────────────────┤
│ Push     │ O(1) amortized  │ O(1)             │
│ Pop      │ O(1)            │ O(1)             │
│ Space    │ O(n) + wastage  │ O(n) + pointers  │
├──────────┼─────────────────┼──────────────────┤
│ Pros     │ Cache friendly  │ No capacity      │
│ Cons     │ Fixed size      │ Extra memory     │
└──────────┴─────────────────┴──────────────────┘

APPLICATIONS:
✓ Function call stack (recursion)
✓ Expression evaluation
✓ Undo/Redo
✓ DFS traversal
✓ Backtracking
✓ Browser history
✓ Parentheses matching
✓ Tower of Hanoi

================================================================================
*/

/*
================================================================================
                        SECTION 3: PRACTICE EXERCISES
================================================================================

1. NEXT GREATER ELEMENT:
   Given array, find next greater element for each using stack.

2. STOCK SPAN:
   Find consecutive days with price <= current day.

3. LARGEST RECTANGLE IN HISTOGRAM:
   Use stack to find largest rectangle area.

4. POSTFIX EVALUATION:
   Evaluate postfix expression using stack.

5. REVERSE WORDS:
   Use stack to reverse order of words.

6. MINIMUM ELEMENT IN O(1):
   Design stack that supports getMin() in O(1).

================================================================================
*/

int main() {
  cout << "╔════════════════════════════════════════════════════════════╗"
       << endl;
  cout << "║             STACKS - COMPREHENSIVE GUIDE                   ║"
       << endl;
  cout << "║          Part 4, Topic 24.3: Linear Data Structures        ║"
       << endl;
  cout << "╚════════════════════════════════════════════════════════════╝"
       << endl;

  example_1_array_stack();
  example_2_ll_stack();
  example_3_balanced_parentheses();
  example_4_decimal_to_binary();
  example_5_undo_redo();
  example_6_dfs_simulation();
  example_7_infix_postfix();
  example_8_recursion_simulation();

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
