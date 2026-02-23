# Topic 5: Functions

## Overview
This folder contains comprehensive learning materials for **Functions in C++**, covering everything from basic function concepts to advanced features like recursion, overloading, and lambda functions.

## 📚 File Structure

### 1. Function Basics
**File:** `function_basics.cpp`

**Topics Covered:**
- Function declaration (prototypes)
- Function definition and implementation
- Function parameters and arguments
- Return types and return statements
- Pass by value vs pass by reference
- Void functions
- Multiple return statements
- Const parameters
- Arrays as function parameters
- Boolean functions

**Key Examples:**
- Simple void functions
- Functions with return values
- Multiple parameter functions
- Different return types (int, double, char, bool, string)
- Pass by value demonstration
- Pass by reference demonstration
- Swap functions (value vs reference)
- Temperature conversion
- Array operations
- Input/output parameters

### 2. Advanced Functions
**File:** `advanced_functions.cpp`

**Topics Covered:**
- Default parameters
- Function overloading
- Inline functions
- Recursive functions
- Static variables in functions
- Function pointers (introduction)
- Lambda functions (C++11)
- Combining features

**Key Examples:**
- Default parameter usage
- Function overloading (by count and type)
- Inline function optimization
- Factorial (recursion)
- Fibonacci sequence (recursion)
- Array sum (recursion)
- Power calculation (recursion)
- String reversal (recursion)
- Static variable persistence
- Function pointers
- Lambda expressions
- Combined features

## 🎯 Learning Path

### Beginner Level (Start Here)
1. **Study `function_basics.cpp` first**
   - Understand what functions are and why we use them
   - Learn function declaration and definition
   - Practice pass by value vs pass by reference
   - Master return statements

### Intermediate Level
2. **Move to first half of `advanced_functions.cpp`**
   - Learn default parameters
   - Master function overloading
   - Understand inline functions

### Advanced Level
3. **Complete `advanced_functions.cpp`**
   - Master recursive functions
   - Learn static variables
   - Explore function pointers
   - Use lambda functions

## 💡 Key Concepts Summary

### Function Basics

#### Function Anatomy
```cpp
return_type function_name(parameter_list) {
    // Function body
    return value;
}
```

#### Parts of a Function
1. **Return Type**: What the function returns (int, void, etc.)
2. **Function Name**: Identifier to call it
3. **Parameters**: Input values (optional)
4. **Body**: Code to execute
5. **Return**: Value sent back (if not void)

### Declaration vs Definition

**Declaration (Prototype):**
```cpp
int add(int a, int b);  // Tells compiler function exists
```

**Definition:**
```cpp
int add(int a, int b) {  // Implementation
    return a + b;
}
```

### Pass by Value vs Pass by Reference

**Pass by Value (Copy):**
```cpp
void func(int x) {     // Gets copy
    x = 10;            // Modifies copy
}
// Original unchanged
```

**Pass by Reference (Original):**
```cpp
void func(int& x) {    // Gets reference
    x = 10;            // Modifies original
}
// Original changed!
```

**Pass by Const Reference (Efficient + Safe):**
```cpp
void func(const string& s) {  // No copy, can't modify
    cout << s;                 // Read-only
}
```

### Advanced Features

#### Default Parameters
```cpp
void print(string msg, int times = 1, char sep = '-') {
    // times and sep have defaults
}

print("Hi");           // Uses defaults
print("Hi", 3);        // Custom times
print("Hi", 3, '*');   // Custom both
```

**Rules:**
- Must be rightmost parameters
- Can't skip middle parameters
- Specified in declaration

#### Function Overloading
```cpp
int add(int a, int b);           // Two ints
int add(int a, int b, int c);    // Three ints
double add(double a, double b);  // Two doubles

// Compiler chooses based on arguments
add(5, 3);        // Calls int version
add(2.5, 3.7);    // Calls double version
```

**Requirements:**
- Must differ in parameter count or types
- Return type alone is NOT enough
- Compiler resolves at compile-time

#### Inline Functions
```cpp
inline int square(int x) {
    return x * x;
}

// Code inserted at call site (no overhead)
int result = square(5);  // Becomes: int result = 5 * 5;
```

**When to Use:**
- Small functions (1-5 lines)
- Frequently called
- Performance-critical

**When NOT to Use:**
- Large functions
- Recursive functions
- Complex logic

#### Recursion
```cpp
int factorial(int n) {
    if (n <= 1) return 1;         // BASE CASE
    return n * factorial(n - 1);  // RECURSIVE CASE
}
```

**Essential Elements:**
1. **Base Case**: Stopping condition
2. **Recursive Case**: Calls itself
3. **Progress**: Each call moves toward base case

**Common Recursive Patterns:**
- Factorial: `n * factorial(n-1)`
- Fibonacci: `fib(n-1) + fib(n-2)`
- Sum array: `arr[n-1] + sum(arr, n-1)`
- Tree traversal
- Divide and conquer

#### Static Variables
```cpp
void counter() {
    static int count = 0;  // Initialized ONCE
    count++;
    cout << count;
}

counter();  // Prints: 1
counter();  // Prints: 2
counter();  // Prints: 3
```

**Characteristics:**
- Initialized only once
- Retains value between calls
- Has function scope
- Exists for program lifetime

## 📊 Performance Characteristics

| Feature           | Performance Impact                   | When to Use                    |
| ----------------- | ------------------------------------ | ------------------------------ |
| Pass by value     | Copies data (slow for large objects) | Small types (int, double)      |
| Pass by reference | No copy (fast)                       | Modify original, large objects |
| Const reference   | No copy, safe                        | Read-only large objects        |
| Inline            | No call overhead                     | Small, frequent functions      |
| Recursion         | Stack overhead                       | Natural recursive problems     |
| Function pointer  | Indirect call (small overhead)       | Dynamic dispatch, callbacks    |
| Lambda            | Inline + capture                     | Short, one-time functions      |

## 🎓 Common Patterns

### Pattern 1: Input Validation
```cpp
bool is_valid_age(int age) {
    return age >= 0 && age <= 150;
}

if (is_valid_age(input)) {
    // Process
}
```

### Pattern 2: Data Transformation
```cpp
double celsius_to_fahrenheit(double c) {
    return c * 9.0/5.0 + 32.0;
}
```

### Pattern 3: Multiple Outputs
```cpp
void get_min_max(int arr[], int size, int& min, int& max) {
    // Use reference parameters as outputs
    min = arr[0];
    max = arr[0];
    // ...
}
```

### Pattern 4: Factory Functions
```cpp
Student create_student(string name, int id) {
    Student s;
    s.name = name;
    s.id = id;
    return s;
}
```

### Pattern 5: Predicate Functions
```cpp
bool is_even(int n) { return n % 2 == 0; }
bool is_prime(int n) { /* ... */ }

// Use with algorithms
if (is_even(x)) { /* ... */ }
```

## ⚠️ Common Mistakes to Avoid

### 1. Forgetting Return Statement
```cpp
❌ int add(int a, int b) { int sum = a + b; }  // No return!
✅ int add(int a, int b) { return a + b; }
```

### 2. Return Type Mismatch
```cpp
❌ int get_pi() { return 3.14; }  // Returns double!
✅ double get_pi() { return 3.14; }
```

### 3. Expecting Value Change (Pass by Value)
```cpp
❌ void change(int x) { x = 10; }  // Doesn't modify original
✅ void change(int& x) { x = 10; }  // Modifies original
```

### 4. Missing Base Case (Recursion)
```cpp
❌ int factorial(int n) { return n * factorial(n-1); }  // Infinite!
✅ int factorial(int n) {
    if (n <= 1) return 1;  // BASE CASE
    return n * factorial(n-1);
}
```

### 5. Default Parameters Not Rightmost
```cpp
❌ void func(int a = 5, int b);  // Error!
✅ void func(int a, int b = 5);
```

### 6. Returning Local Variable Reference
```cpp
❌ int& bad() { int x = 5; return x; }  // Dangling reference!
✅ int good() { return 5; }             // Return by value
```

### 7. Not Passing Array Size
```cpp
❌ void print(int arr[])              // Size unknown!
✅ void print(int arr[], int size)
```

## 🏆 Best Practices

### Naming Conventions
- **Verbs for actions**: `calculate_area()`, `print_report()`
- **is/has for booleans**: `is_prime()`, `has_element()`
- **Descriptive names**: `get_student_average()` not `gsa()`

### Function Size
- Keep functions focused (one task)
- Ideally under 50 lines
- If too long, split into smaller functions

### Parameter Guidelines
- Limit to 3-4 parameters
- Use struct/class if you need more
- Use `const&` for large objects (strings, vectors)
- Order: required first, optional (defaults) last

### Return Guidelines
- Prefer return values over output parameters
- Use output parameters when multiple returns needed
- Be consistent with return types

### Documentation
```cpp
/**
 * Calculates the area of a circle
 * @param radius The radius of the circle
 * @return The area (pi * r^2)
 */
double circle_area(double radius) {
    return 3.14159 * radius * radius;
}
```

## 📝 Practice Exercises

### Basic Level
1. Write function to find maximum of three numbers
2. Create function to check if year is leap year
3. Write function to calculate average of array
4. Create function to count vowels in string
5. Write function to check if number is perfect square

### Intermediate Level
6. Create overloaded `print()` for int, double, string, array
7. Write function with defaults for printing formatted box
8. Implement recursive function to reverse string
9. Create function to find GCD using recursion
10. Write function with static variable to generate unique IDs

### Advanced Level
11. Implement Tower of Hanoi using recursion
12. Create memoized Fibonacci using static map
13. Write function pointer-based calculator
14. Use lambda to sort vector by custom criteria
15. Implement recursive directory traversal

## 🔧 Compilation and Usage

### Compile Individual Files
```bash
# Function Basics
g++ -std=c++17 function_basics.cpp -o basics
./basics

# Advanced Functions
g++ -std=c++17 advanced_functions.cpp -o advanced
./advanced
```

### Compile Both
```bash
g++ -std=c++17 function_basics.cpp -o basics && ./basics
g++ -std=c++17 advanced_functions.cpp -o advanced && ./advanced
```

### Enable Optimizations
```bash
g++ -std=c++17 -O2 advanced_functions.cpp -o advanced
# -O2 enables optimizations (inline functions work better)
```

## 🚀 Real-World Applications

1. **Input Validation**: `is_valid_email()`, `check_password_strength()`
2. **Data Processing**: `filter_data()`, `transform_records()`
3. **Calculations**: `calculate_tax()`, `compute_distance()`
4. **File Operations**: `read_file()`, `write_log()`
5. **String Manipulation**: `trim()`, `split()`, `join()`
6. **Mathematical**: `factorial()`, `gcd()`, `is_prime()`
7. **Sorting/Searching**: `binary_search()`, `quick_sort()`
8. **Callbacks**: Event handlers, API callbacks
9. **Utilities**: `swap()`, `min()`, `max()`, `clamp()`
10. **Algorithms**: Recursive tree/graph traversal

## 📖 Additional Resources

### Books
- "C++ Primer" - Chapter on Functions
- "Effective C++" - Item 20: Prefer pass-by-reference-to-const
- "Clean Code" - Chapter on Functions

### Online
- [cppreference.com - Functions](https://en.cppreference.com/w/cpp/language/functions)
- [LearnCpp.com - Functions](https://www.learncpp.com/)
- [GeeksforGeeks - Functions in C++](https://www.geeksforgeeks.org/functions-in-cpp/)

### Topics to Explore Next
After mastering functions:
1. **Topic 6**: Arrays and Strings (use functions with arrays)
2. **Topic 7**: Pointers and References (deeper understanding)
3. **Topic 9**: Classes (member functions)
4. **Topic 16**: Templates (function templates)
5. **Topic 19**: STL Algorithms (using function objects, lambdas)

## ✅ Mastery Checklist

After completing this topic, you should be able to:

- [ ] Write function declarations and definitions
- [ ] Use appropriate return types
- [ ] Pass parameters by value, reference, and const reference
- [ ] Implement void functions
- [ ] Use multiple return statements effectively
- [ ] Apply default parameters
- [ ] Overload functions correctly
- [ ] Write inline functions
- [ ] Create recursive functions with proper base cases
- [ ] Use static variables in functions
- [ ] Work with function pointers
- [ ] Write and use lambda functions
- [ ] Choose appropriate function features for each situation
- [ ] Avoid common function mistakes
- [ ] Write clean, maintainable function code

## 🎯 Next Steps

1. **Practice**: Solve 20+ function problems on LeetCode/HackerRank
2. **Build**: Create a calculator using functions
3. **Refactor**: Take old code and organize into functions
4. **Explore**: Learn about member functions in classes
5. **Advanced**: Study function templates and generic programming

---

**Happy Learning! 🚀**

*Last Updated: February 23, 2026*
