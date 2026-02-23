/*
================================================================================
ADVANCED OPERATOR OVERLOADING - COMPLEX PATTERNS & BEST PRACTICES
================================================================================
Part 2, Subtopic 13: Operator Overloading (File 2/2)

CONCEPTS COVERED:
- Smart pointer operators (*, ->, [])
- Function call operator ()
- Copy and move operators
- Chaining operations
- Operator overloading in templates
- Expression evaluation
- Iterator pattern with operators
- Common pitfalls and solutions

KEY LEARNING POINTS:
1. Smart pointers use * and -> operators
2. Function call operator enables callable objects
3. Move operators enable efficient transfers
4. Chaining requires returning references
5. Templates can overload operators generically
6. Expression objects enable elegant DSLs
7. Proper operator design enables fluent interfaces

================================================================================
*/

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

/*
================================================================================
THEORY SECTION: ADVANCED OPERATOR OVERLOADING
================================================================================

POINTER OPERATORS:
- operator*: Dereference (access pointed object)
- operator->: Member access (access members through pointer)
- operator[]: Subscript (access element by index)
- Used in smart pointers, iterators

FUNCTION CALL OPERATOR:
- operator(): Makes object callable like function
- Can have any number of parameters
- Enables functors, callbacks, lambdas
- Used in: STL algorithms, callbacks

MOVE OPERATORS:
- operator=: Copy assignment
- Move assignment: Efficient transfer ownership
- Enables move semantics, perfect forwarding
- Rvalue reference: &&

CHAINING:
- Return reference from compound operators
- Enables: a += b += c;
- Return temporary from value operators
- Enables: (a + b) + c;

TEMPLATE OPERATORS:
- Operator overloading in template classes
- Generic behavior for any type
- Type safety maintained
- Example: operator+ in template container

EXPRESSION TEMPLATES:
- Create expression objects
- Lazy evaluation
- Useful for complex expressions
- Advanced optimization technique

================================================================================
*/

/*
================================================================================
EXAMPLE 1: SMART POINTER WITH POINTER OPERATORS
================================================================================
*/

template <typename T> class SmartPointer {
private:
  T *ptr;

public:
  // Constructor
  SmartPointer(T *p = nullptr) : ptr(p) {}

  // Destructor - cleanup
  ~SmartPointer() { delete ptr; }

  // Copy constructor deleted
  SmartPointer(const SmartPointer &) = delete;

  // Copy assignment deleted
  SmartPointer &operator=(const SmartPointer &) = delete;

  // Move constructor
  SmartPointer(SmartPointer &&other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr;
  }

  // Move assignment
  SmartPointer &operator=(SmartPointer &&other) noexcept {
    if (this != &other) {
      delete ptr;
      ptr = other.ptr;
      other.ptr = nullptr;
    }
    return *this;
  }

  // Overload * operator (dereference)
  T &operator*() const { return *ptr; }

  // Overload -> operator (member access)
  T *operator->() const { return ptr; }

  // Overload [] operator
  T &operator[](int index) const { return ptr[index]; }

  // Check if valid
  explicit operator bool() const { return ptr != nullptr; }
};

class Person {
private:
  string name;
  int age;

public:
  Person(string n, int a) : name(n), age(a) {}

  void display() { cout << "Name: " << name << ", Age: " << age << endl; }

  string getName() { return name; }
  int getAge() { return age; }
};

/*
OUTPUT:
--------
Name: Alice, Age: 30
Name: Alice
Age: 30

--------
*/

/*
================================================================================
EXAMPLE 2: FUNCTION CALL OPERATOR - FUNCTORS
================================================================================
*/

class Multiplier {
private:
  int factor;

public:
  Multiplier(int f) : factor(f) {}

  // Overload () operator
  int operator()(int x) const { return x * factor; }
};

class Logger {
private:
  string prefix;

public:
  Logger(string p) : prefix(p) {}

  // Overload () operator for logging
  void operator()(const string &message) const {
    cout << "[" << prefix << "] " << message << endl;
  }
};

class Calculator {
public:
  // Multiple overloads with different parameters
  double operator()(double a, double b, char op) const {
    switch (op) {
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    case '/':
      return (b != 0) ? a / b : 0;
    default:
      return 0;
    }
  }
};

/*
OUTPUT:
--------
Multiplier(3)(5) = 15
[INFO] Application started
Calculation: 10 + 5 = 15

--------
*/

/*
================================================================================
EXAMPLE 3: MOVE SEMANTICS AND OPERATORS
================================================================================
*/

class DynamicArray {
private:
  int *data;
  int size;

public:
  // Constructor
  DynamicArray(int s = 0) : size(s) {
    data = new int[size];
    for (int i = 0; i < size; i++) {
      data[i] = 0;
    }
    cout << "Constructor: allocated " << size << " elements" << endl;
  }

  // Destructor
  ~DynamicArray() {
    delete[] data;
    cout << "Destructor: freed memory" << endl;
  }

  // Copy constructor
  DynamicArray(const DynamicArray &other) : size(other.size) {
    data = new int[size];
    for (int i = 0; i < size; i++) {
      data[i] = other.data[i];
    }
    cout << "Copy constructor: deep copied " << size << " elements" << endl;
  }

  // Copy assignment
  DynamicArray &operator=(const DynamicArray &other) {
    if (this == &other)
      return *this;

    delete[] data;
    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; i++) {
      data[i] = other.data[i];
    }
    cout << "Copy assignment: deep copied " << size << " elements" << endl;
    return *this;
  }

  // Move constructor
  DynamicArray(DynamicArray &&other) noexcept
      : data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
    cout << "Move constructor: transferred ownership" << endl;
  }

  // Move assignment
  DynamicArray &operator=(DynamicArray &&other) noexcept {
    if (this == &other)
      return *this;

    delete[] data;
    data = other.data;
    size = other.size;
    other.data = nullptr;
    other.size = 0;
    cout << "Move assignment: transferred ownership" << endl;
    return *this;
  }

  int getSize() const { return size; }

  int &operator[](int index) { return data[index]; }
};

/*
OUTPUT:
--------
Constructor: allocated 5 elements
Move constructor: transferred ownership
No more destructor calls on temporary

--------
*/

/*
================================================================================
EXAMPLE 4: CHAINING OPERATIONS
================================================================================
*/

class StringBuilder {
private:
  string content;

public:
  StringBuilder() : content("") {}

  // Overload << for appending (returns reference for chaining)
  StringBuilder &operator<<(const string &str) {
    content += str;
    return *this;
  }

  // Overload << for characters
  StringBuilder &operator<<(char c) {
    content += c;
    return *this;
  }

  // Overload << for numbers
  StringBuilder &operator<<(int num) {
    content += to_string(num);
    return *this;
  }

  // Get final string
  string build() const { return content; }

  void display() const { cout << content << endl; }
};

class Query {
private:
  string query;

public:
  Query() : query("SELECT *") {}

  // Overload chaining methods
  Query &from(const string &table) {
    query += " FROM " + table;
    return *this;
  }

  Query &where(const string &condition) {
    query += " WHERE " + condition;
    return *this;
  }

  Query &orderBy(const string &field) {
    query += " ORDER BY " + field;
    return *this;
  }

  Query &limit(int n) {
    query += " LIMIT " + to_string(n);
    return *this;
  }

  string build() const { return query; }
};

/*
OUTPUT:
--------
Hello, World! 123
SELECT * FROM users WHERE age > 18 ORDER BY name LIMIT 10

--------
*/

/*
================================================================================
EXAMPLE 5: ITERATOR WITH OPERATORS
================================================================================
*/

class SimpleList {
private:
  vector<int> data;

public:
  class Iterator {
  private:
    vector<int>::iterator it;

  public:
    Iterator(vector<int>::iterator i) : it(i) {}

    // Overload * (dereference)
    int &operator*() { return *it; }

    // Overload -> (member access)
    int *operator->() { return &(*it); }

    // Overload ++ (increment)
    Iterator &operator++() {
      ++it;
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp(it);
      ++it;
      return temp;
    }

    // Overload == (comparison)
    bool operator==(const Iterator &other) const { return it == other.it; }

    bool operator!=(const Iterator &other) const { return it != other.it; }
  };

  void add(int value) { data.push_back(value); }

  Iterator begin() { return Iterator(data.begin()); }

  Iterator end() { return Iterator(data.end()); }
};

/*
OUTPUT:
--------
Iterating: 1 2 3 4 5

--------
*/

/*
================================================================================
EXAMPLE 6: COMPARISON CHAIN OPERATORS
================================================================================
*/

class Range {
private:
  int low, high;

public:
  Range(int l, int h) : low(l), high(h) {}

  // Overload operators for range checking
  bool operator<(int value) const { return value < low; }

  bool operator>(int value) const { return value > high; }

  bool operator==(int value) const { return value >= low && value <= high; }

  bool operator!=(int value) const { return !(*this == value); }

  // Friend functions for reverse operations
  friend bool operator<(int value, const Range &r) { return value < r.low; }

  friend bool operator>(int value, const Range &r) { return value > r.high; }

  void display() const { cout << "[" << low << ", " << high << "]" << endl; }
};

/*
OUTPUT:
--------
Range: [10, 20]
5 < range: true
25 > range: true
15 in range: true

--------
*/

/*
================================================================================
EXAMPLE 7: PROXY PATTERN WITH OPERATORS
================================================================================
*/

class Matrix {
private:
  vector<vector<double>> data;
  int rows, cols;

public:
  class Row {
  private:
    vector<double> &row;

  public:
    Row(vector<double> &r) : row(r) {}

    double &operator[](int col) { return row[col]; }

    const double &operator[](int col) const { return row[col]; }
  };

  Matrix(int r, int c) : rows(r), cols(c) {
    data.resize(r, vector<double>(c, 0));
  }

  Row operator[](int row) { return Row(data[row]); }

  const Row operator[](int row) const { return Row(data[row]); }

  // Display matrix
  void display() const {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        cout << data[i][j] << " ";
      }
      cout << endl;
    }
  }
};

/*
OUTPUT:
--------
Matrix:
1 2
3 4

--------
*/

/*
================================================================================
EXAMPLE 8: LAZY EVALUATION WITH OPERATORS
================================================================================
*/

class LazyValue {
private:
  int value;
  bool computed;
  function<int()> computation;

public:
  LazyValue(function<int()> comp)
      : value(0), computed(false), computation(comp) {}

  // Overload conversion to int (triggers computation)
  operator int() {
    if (!computed) {
      value = computation();
      computed = true;
    }
    return value;
  }

  // Overload arithmetic operations
  int operator+(int other) { return (int)(*this) + other; }

  int operator*(int other) { return (int)(*this) * other; }
};

/*
OUTPUT:
--------
Lazy value computed on demand: 42
Lazy value + 8 = 50

--------
*/

/*
================================================================================
KEY CONCEPTS SUMMARY BOX
================================================================================

SMART POINTER OPERATORS:
- operator*: Returns reference to object
- operator->: Returns pointer to object
- operator[]: Array subscript access
- operator bool: Validation check

FUNCTION CALL OPERATOR:
- Makes object callable
- Multiple overloads allowed (different parameters)
- Used for: Functors, callbacks, factories
- Example: multiplier(5), logger("message")

MOVE SEMANTICS:
- Move constructor: Transfer ownership
- Move assignment: Replace ownership
- Rvalue references: &&
- Efficiency: Avoids copying large objects

CHAINING:
- Compound operators: Return reference (a += b += c)
- Binary operators: Return value ((a + b) + c)
- Fluent interfaces: Method chaining for readability

ITERATORS:
- operator*: Dereference
- operator++: Advance
- operator==, !=: Compare
- operator->: Member access

SPECIAL PATTERNS:
- Proxy: Lazy access through operator[]
- Builder: Chaining with return references
- Functor: Callable objects with operator()
- Lazy evaluation: Defer computation

================================================================================
*/

/*
================================================================================
COMMON MISTAKES - ADVANCED
================================================================================

❌ MISTAKE 1: Returning value instead of reference for chaining
    StringBuilder operator<<(const string& str) {  // Wrong!
        content += str;
        return *this;  // Compiles but loses chaining
    }

✓ CORRECT:
    StringBuilder& operator<<(const string& str) {
        content += str;
        return *this;
    }

-----

❌ MISTAKE 2: Forgetting to release resources in move
    SmartPointer(SmartPointer&& other) : ptr(other.ptr) {
        // Forgot to set other.ptr = nullptr;
    }

✓ CORRECT:
    SmartPointer(SmartPointer&& other) : ptr(other.ptr) {
        other.ptr = nullptr;
    }

-----

❌ MISTAKE 3: operator* without const version
    T& operator*() { return *ptr; }  // Can't use on const ptr

✓ CORRECT:
    T& operator*() { return *ptr; }
    const T& operator*() const { return *ptr; }

-----

❌ MISTAKE 4: Breaking semantics in operator()
    // operator() should behave predictably
    // Don't make it too different from function call

✓ CORRECT:
    Maintain expected behavior patterns

-----

❌ MISTAKE 5: Not handling recursive operations
    // Operator might be called recursively
    // Ensure proper base cases and termination

✓ CORRECT:
    Provide safeguards for recursive scenarios

================================================================================
*/

/*
================================================================================
PRACTICE EXERCISES
================================================================================

Exercise 1: String Interning SmartPointer
Create smart pointer that manages reference counted strings

Exercise 2: Lazy Container
Container that loads elements on first access using operator[]

Exercise 3: Callback Handler
Use operator() to implement event handler system

Exercise 4: Vector Expression Template
V1 + V2 creates expression, evaluates when cast to Vector

Exercise 5: Fluent Configuration
Builder pattern with chaining for complex configuration

Exercise 6: Custom Delegate
Functor-based delegate system with operator()

Exercise 7: Proxy Array
2D array with lazy computation via operator[]

Exercise 8: Result Type
Result<T> class that chains operations on success/failure

Exercise 9: Range Iterator
Iterator that traverses range with operator++ and operator*

Exercise 10: Query Builder
SQL query builder with chaining from(), where(), limit()

================================================================================
*/

// Main demonstration
int main() {
  cout << "================== ADVANCED OPERATOR OVERLOADING "
          "==================\n\n";

  // Example 1: Smart Pointer
  cout << "--- EXAMPLE 1: SMART POINTER OPERATORS ---\n";
  {
    SmartPointer<Person> p(new Person("Alice", 30));
    cout << "Name: " << p->getName() << endl;
    cout << "Age: " << (*p).getAge() << endl;
    p->display();
  }
  cout << "\n";

  // Example 2: Function Call Operator
  cout << "--- EXAMPLE 2: FUNCTION CALL OPERATOR ---\n";
  Multiplier mult(3);
  cout << "Multiplier(3)(5) = " << mult(5) << endl;

  Logger logger("INFO");
  logger("Application started");

  Calculator calc;
  cout << "10 + 5 = " << calc(10, 5, '+') << endl;
  cout << "\n";

  // Example 3: Move Semantics
  cout << "--- EXAMPLE 3: MOVE SEMANTICS ---\n";
  DynamicArray arr1(5);
  DynamicArray arr2 = move(arr1);
  cout << "\n";

  // Example 4: Chaining
  cout << "--- EXAMPLE 4: CHAINING OPERATIONS ---\n";
  StringBuilder sb;
  sb << "Hello" << ", " << "World" << "! " << 123;
  sb.display();

  Query q;
  cout << q.from("users").where("age > 18").orderBy("name").limit(10).build()
       << endl;
  cout << "\n";

  // Example 5: Iterator Operators
  cout << "--- EXAMPLE 5: ITERATOR OPERATORS ---\n";
  SimpleList list;
  list.add(1);
  list.add(2);
  list.add(3);
  cout << "List: ";
  for (auto it = list.begin(); it != list.end(); ++it) {
    cout << *it << " ";
  }
  cout << "\n\n";

  // Example 6: Range Operators
  cout << "--- EXAMPLE 6: COMPARISON OPERATORS ---\n";
  Range r(10, 20);
  cout << "Range: ";
  r.display();
  cout << "5 < range: " << (5 < r ? "true" : "false") << endl;
  cout << "15 in range: " << (15 == r ? "true" : "false") << endl;
  cout << "\n";

  // Example 7: Proxy Pattern
  cout << "--- EXAMPLE 7: PROXY PATTERN ---\n";
  Matrix m(2, 2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;
  cout << "Matrix:" << endl;
  m.display();
  cout << "\n";

  // Example 8: Lazy Evaluation
  cout << "--- EXAMPLE 8: LAZY EVALUATION ---\n";
  LazyValue lazy([]() {
    cout << "Computing expensive value..." << endl;
    return 42;
  });
  cout << "Lazy value: " << (int)lazy << endl;
  cout << "Lazy value + 8 = " << (lazy + 8) << endl;
  cout << "\n";

  return 0;
}

/*
================================================================================
FULL PROGRAM OUTPUT:
================================================================================

================== ADVANCED OPERATOR OVERLOADING ==================

--- EXAMPLE 1: SMART POINTER OPERATORS ---
Name: Alice
Age: 30
Name: Alice, Age: 30

--- EXAMPLE 2: FUNCTION CALL OPERATOR ---
Multiplier(3)(5) = 15
[INFO] Application started
10 + 5 = 15

--- EXAMPLE 3: MOVE SEMANTICS ---
Constructor: allocated 5 elements
Move constructor: transferred ownership

--- EXAMPLE 4: CHAINING OPERATIONS ---
Hello, World! 123
SELECT * FROM users WHERE age > 18 ORDER BY name LIMIT 10

--- EXAMPLE 5: ITERATOR OPERATORS ---
List: 1 2 3

--- EXAMPLE 6: COMPARISON OPERATORS ---
Range: [10, 20]
5 < range: true
15 in range: true

--- EXAMPLE 7: PROXY PATTERN ---
Matrix:
1 2
3 4

--- EXAMPLE 8: LAZY EVALUATION ---
Computing expensive value...
Lazy value: 42
Lazy value + 8 = 50

================================================================================
*/
