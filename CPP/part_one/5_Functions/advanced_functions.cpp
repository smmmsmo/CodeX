#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
 * =====================================================================
 * TOPIC 5.2: ADVANCED FUNCTIONS
 * =====================================================================
 *
 * ADVANCED FUNCTION CONCEPTS:
 * 1. Default parameters
 * 2. Function overloading
 * 3. Inline functions
 * 4. Recursive functions
 * 5. Function pointers (introduction)
 * 6. Lambda functions (introduction)
 * 7. Static variables in functions
 * 8. Function templates (introduction)
 *
 * =====================================================================
 * DEFAULT PARAMETERS
 * =====================================================================
 *
 * WHAT ARE DEFAULT PARAMETERS?
 * Parameters that have default values if not provided by caller.
 *
 * SYNTAX:
 *   return_type function_name(type param1, type param2 = default_value)
 *
 * RULES:
 * 1. Default parameters must be rightmost in parameter list
 * 2. Cannot skip middle parameters
 * 3. Specified in declaration, not definition (if separated)
 *
 * =====================================================================
 * FUNCTION OVERLOADING
 * =====================================================================
 *
 * WHAT IS OVERLOADING?
 * Multiple functions with same name but different parameters.
 *
 * RULES:
 * 1. Must differ in number or type of parameters
 * 2. Return type alone is NOT enough
 * 3. Compiler chooses based on arguments
 *
 * =====================================================================
 * INLINE FUNCTIONS
 * =====================================================================
 *
 * WHAT ARE INLINE FUNCTIONS?
 * Functions where code is inserted at call site (no function call overhead).
 *
 * SYNTAX: inline return_type function_name(parameters)
 *
 * WHEN TO USE:
 * - Small, frequently called functions
 * - Performance-critical code
 * - Compiler may ignore inline suggestion
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: DEFAULT PARAMETERS ==============
void print_message(string message, int times = 1, char separator = '-') {
  for (int i = 0; i < times; i++) {
    cout << message;
    if (i < times - 1)
      cout << separator;
  }
  cout << endl;
}

void example1_default_parameters() {
  cout << "\n============== EXAMPLE 1: DEFAULT PARAMETERS =============="
       << endl;
  cout << "Parameters can have default values\n" << endl;

  cout << "1. All parameters provided:" << endl;
  print_message("Hello", 3, '*');

  cout << "\n2. Using default separator (-):" << endl;
  print_message("World", 3);

  cout << "\n3. Using both defaults (times=1, separator=-):" << endl;
  print_message("C++");

  cout << "\nDefault parameters must be rightmost in parameter list" << endl;
}

// ============== EXAMPLE 2: MORE DEFAULT PARAMETER EXAMPLES ==============
double calculate_price(double base_price, double tax_rate = 0.08,
                       double discount = 0.0) {
  double price_with_tax = base_price * (1 + tax_rate);
  double final_price = price_with_tax * (1 - discount);
  return final_price;
}

void example2_default_params_calculation() {
  cout << "\n============== EXAMPLE 2: DEFAULT PARAMETERS IN CALCULATIONS "
          "=============="
       << endl;

  double base = 100.0;

  cout << "Base price: $" << base << endl;
  cout << "\n1. No tax, no discount:" << endl;
  cout << "   Final: $" << calculate_price(base, 0.0, 0.0) << endl;

  cout << "\n2. Default tax (8%), no discount:" << endl;
  cout << "   Final: $" << calculate_price(base) << endl;

  cout << "\n3. Custom tax (10%), no discount:" << endl;
  cout << "   Final: $" << calculate_price(base, 0.10) << endl;

  cout << "\n4. Custom tax (10%), 20% discount:" << endl;
  cout << "   Final: $" << calculate_price(base, 0.10, 0.20) << endl;
}

// ============== EXAMPLE 3: FUNCTION OVERLOADING - DIFFERENT NUMBER OF PARAMS
// ==============
int add(int a, int b) { return a + b; }

int add(int a, int b, int c) { return a + b + c; }

int add(int a, int b, int c, int d) { return a + b + c + d; }

void example3_overloading_by_count() {
  cout << "\n============== EXAMPLE 3: OVERLOADING (DIFFERENT PARAM COUNT) "
          "=============="
       << endl;
  cout << "Same function name, different number of parameters\n" << endl;

  cout << "add(5, 3) = " << add(5, 3) << endl;
  cout << "add(5, 3, 2) = " << add(5, 3, 2) << endl;
  cout << "add(5, 3, 2, 1) = " << add(5, 3, 2, 1) << endl;

  cout << "\nCompiler chooses correct function based on arguments" << endl;
}

// ============== EXAMPLE 4: FUNCTION OVERLOADING - DIFFERENT TYPES
// ==============
int multiply(int a, int b) {
  cout << "  (int version called)" << endl;
  return a * b;
}

double multiply(double a, double b) {
  cout << "  (double version called)" << endl;
  return a * b;
}

string multiply(string str, int times) {
  cout << "  (string version called)" << endl;
  string result = "";
  for (int i = 0; i < times; i++) {
    result += str;
  }
  return result;
}

void example4_overloading_by_type() {
  cout << "\n============== EXAMPLE 4: OVERLOADING (DIFFERENT TYPES) "
          "=============="
       << endl;
  cout << "Same name, different parameter types\n" << endl;

  cout << "multiply(5, 3) = " << multiply(5, 3) << endl;
  cout << "multiply(2.5, 4.0) = " << multiply(2.5, 4.0) << endl;
  cout << "multiply(\"Hi\", 3) = " << multiply("Hi", 3) << endl;

  cout << "\nDifferent behavior based on parameter types!" << endl;
}

// ============== EXAMPLE 5: OVERLOADING WITH DIFFERENT BEHAVIORS ==============
void print(int num) { cout << "Integer: " << num << endl; }

void print(double num) { cout << "Double: " << num << endl; }

void print(string str) { cout << "String: " << str << endl; }

void print(int arr[], int size) {
  cout << "Array: [";
  for (int i = 0; i < size; i++) {
    cout << arr[i];
    if (i < size - 1)
      cout << ", ";
  }
  cout << "]" << endl;
}

void example5_overloading_print() {
  cout << "\n============== EXAMPLE 5: OVERLOADED PRINT FUNCTION =============="
       << endl;
  cout << "One print() function handles different types\n" << endl;

  print(42);
  print(3.14);
  print("Hello, C++!");

  int arr[] = {1, 2, 3, 4, 5};
  print(arr, 5);

  cout << "\nPolymorphism at compile-time!" << endl;
}

// ============== EXAMPLE 6: INLINE FUNCTIONS ==============
inline int square(int x) { return x * x; }

inline int cube(int x) { return x * x * x; }

inline int max_of_two(int a, int b) { return (a > b) ? a : b; }

void example6_inline_functions() {
  cout << "\n============== EXAMPLE 6: INLINE FUNCTIONS ==============" << endl;
  cout << "Code inserted at call site for efficiency\n" << endl;

  cout << "square(5) = " << square(5) << endl;
  cout << "cube(3) = " << cube(3) << endl;
  cout << "max_of_two(10, 20) = " << max_of_two(10, 20) << endl;

  cout << "\nInline eliminates function call overhead" << endl;
  cout << "Best for small, frequently called functions" << endl;
  cout << "Compiler may ignore 'inline' if function is too complex" << endl;
}

// ============== EXAMPLE 7: RECURSIVE FUNCTIONS - FACTORIAL ==============
int factorial(int n) {
  // Base case
  if (n <= 1) {
    return 1;
  }
  // Recursive case
  return n * factorial(n - 1);
}

void example7_recursion_factorial() {
  cout << "\n============== EXAMPLE 7: RECURSION - FACTORIAL =============="
       << endl;
  cout << "Function calls itself\n" << endl;

  for (int i = 0; i <= 6; i++) {
    cout << i << "! = " << factorial(i) << endl;
  }

  cout << "\nRecursion: Function calls itself until base case reached" << endl;
}

// ============== EXAMPLE 8: RECURSIVE FUNCTIONS - FIBONACCI ==============
int fibonacci(int n) {
  if (n <= 1) {
    return n;
  }
  return fibonacci(n - 1) + fibonacci(n - 2);
}

void example8_recursion_fibonacci() {
  cout << "\n============== EXAMPLE 8: RECURSION - FIBONACCI =============="
       << endl;
  cout << "Classic recursive example\n" << endl;

  cout << "Fibonacci sequence:" << endl;
  for (int i = 0; i < 10; i++) {
    cout << "F(" << i << ") = " << fibonacci(i) << endl;
  }

  cout << "\nNote: This is inefficient (many repeated calculations)" << endl;
  cout << "Better with memoization or iteration" << endl;
}

// ============== EXAMPLE 9: RECURSION - SUM OF ARRAY ==============
int sum_array(int arr[], int size) {
  // Base case
  if (size <= 0) {
    return 0;
  }
  // Recursive case
  return arr[size - 1] + sum_array(arr, size - 1);
}

void example9_recursion_array() {
  cout << "\n============== EXAMPLE 9: RECURSION - ARRAY SUM =============="
       << endl;

  int numbers[] = {1, 2, 3, 4, 5};
  int size = 5;

  cout << "Array: ";
  for (int n : numbers)
    cout << n << " ";
  cout << endl;

  cout << "Sum (recursive) = " << sum_array(numbers, size) << endl;

  cout << "\nRecursion works on arrays too!" << endl;
}

// ============== EXAMPLE 10: RECURSION - POWER ==============
double power_recursive(double base, int exp) {
  if (exp == 0) {
    return 1;
  }
  if (exp < 0) {
    return 1.0 / power_recursive(base, -exp);
  }
  return base * power_recursive(base, exp - 1);
}

void example10_recursion_power() {
  cout << "\n============== EXAMPLE 10: RECURSION - POWER CALCULATION "
          "=============="
       << endl;

  cout << "2^5 = " << power_recursive(2, 5) << endl;
  cout << "3^4 = " << power_recursive(3, 4) << endl;
  cout << "2^(-3) = " << power_recursive(2, -3) << endl;

  cout << "\nRecursion handles negative exponents too" << endl;
}

// ============== EXAMPLE 11: RECURSION - STRING REVERSAL ==============
void reverse_string(string &str, int start, int end) {
  if (start >= end) {
    return; // Base case
  }

  // Swap characters
  char temp = str[start];
  str[start] = str[end];
  str[end] = temp;

  // Recursive call
  reverse_string(str, start + 1, end - 1);
}

void example11_recursion_string() {
  cout << "\n============== EXAMPLE 11: RECURSION - STRING REVERSAL "
          "=============="
       << endl;

  string text = "Hello";
  cout << "Original: " << text << endl;

  reverse_string(text, 0, text.length() - 1);
  cout << "Reversed: " << text << endl;

  cout << "\nRecursion modifies string in-place" << endl;
}

// ============== EXAMPLE 12: STATIC VARIABLES IN FUNCTIONS ==============
void counter() {
  static int count = 0; // Initialized only once
  count++;
  cout << "Function called " << count << " time(s)" << endl;
}

int generate_id() {
  static int id = 1000;
  return id++;
}

void example12_static_variables() {
  cout << "\n============== EXAMPLE 12: STATIC VARIABLES IN FUNCTIONS "
          "=============="
       << endl;
  cout << "Static variables persist between function calls\n" << endl;

  cout << "Calling counter() multiple times:" << endl;
  counter();
  counter();
  counter();

  cout << "\nGenerating unique IDs:" << endl;
  cout << "ID 1: " << generate_id() << endl;
  cout << "ID 2: " << generate_id() << endl;
  cout << "ID 3: " << generate_id() << endl;

  cout << "\nStatic variables retain value across calls!" << endl;
}

// ============== EXAMPLE 13: FUNCTION POINTERS (BASICS) ==============
int add_func(int a, int b) { return a + b; }

int subtract_func(int a, int b) { return a - b; }

int multiply_func(int a, int b) { return a * b; }

void example13_function_pointers() {
  cout << "\n============== EXAMPLE 13: FUNCTION POINTERS =============="
       << endl;
  cout << "Pointers can point to functions!\n" << endl;

  // Declare function pointer
  int (*operation)(int, int);

  operation = add_func;
  cout << "Using add: 5 + 3 = " << operation(5, 3) << endl;

  operation = subtract_func;
  cout << "Using subtract: 5 - 3 = " << operation(5, 3) << endl;

  operation = multiply_func;
  cout << "Using multiply: 5 * 3 = " << operation(5, 3) << endl;

  cout << "\nFunction pointers enable dynamic function selection" << endl;
}

// ============== EXAMPLE 14: LAMBDA FUNCTIONS (INTRODUCTION) ==============
void example14_lambda_functions() {
  cout << "\n============== EXAMPLE 14: LAMBDA FUNCTIONS (C++11) =============="
       << endl;
  cout << "Anonymous inline functions\n" << endl;

  // Simple lambda
  auto greet = []() { cout << "Hello from lambda!" << endl; };
  greet();

  // Lambda with parameters
  auto add_lambda = [](int a, int b) { return a + b; };
  cout << "5 + 3 = " << add_lambda(5, 3) << endl;

  // Lambda with capture
  int multiplier = 10;
  auto multiply_by = [multiplier](int x) { return x * multiplier; };
  cout << "7 * " << multiplier << " = " << multiply_by(7) << endl;

  cout << "\nLambdas are convenient for short, one-time functions" << endl;
}

// ============== EXAMPLE 15: COMBINING OVERLOADING AND DEFAULT PARAMS
// ==============
void display_info(string name, int age = 0, string city = "Unknown") {
  cout << "Name: " << name;
  if (age > 0)
    cout << ", Age: " << age;
  if (city != "Unknown")
    cout << ", City: " << city;
  cout << endl;
}

void display_info(int id, string department) {
  cout << "Employee ID: " << id << ", Department: " << department << endl;
}

void example15_combined_features() {
  cout << "\n============== EXAMPLE 15: COMBINING FEATURES =============="
       << endl;
  cout << "Overloading + Default parameters\n" << endl;

  cout << "Person info (various defaults):" << endl;
  display_info("Alice");
  display_info("Bob", 30);
  display_info("Charlie", 25, "NYC");

  cout << "\nEmployee info (overloaded version):" << endl;
  display_info(12345, "Engineering");

  cout << "\nDifferent overloads can have different default parameters" << endl;
}

int main() {
  cout << "\n======================================================" << endl;
  cout << "            ADVANCED FUNCTIONS TUTORIAL              " << endl;
  cout << "======================================================" << endl;

  example1_default_parameters();
  example2_default_params_calculation();
  example3_overloading_by_count();
  example4_overloading_by_type();
  example5_overloading_print();
  example6_inline_functions();
  example7_recursion_factorial();
  example8_recursion_fibonacci();
  example9_recursion_array();
  example10_recursion_power();
  example11_recursion_string();
  example12_static_variables();
  example13_function_pointers();
  example14_lambda_functions();
  example15_combined_features();

  cout << "\n======================================================" << endl;
  cout << "                   KEY TAKEAWAYS                      " << endl;
  cout << "======================================================" << endl;
  cout << "✓ Default parameters provide flexibility" << endl;
  cout << "✓ Overloading enables same name, different signatures" << endl;
  cout << "✓ Inline functions reduce call overhead" << endl;
  cout << "✓ Recursion: function calls itself" << endl;
  cout << "✓ Always have base case in recursion" << endl;
  cout << "✓ Static variables persist across calls" << endl;
  cout << "✓ Function pointers enable dynamic behavior" << endl;
  cout << "✓ Lambdas are convenient for short functions" << endl;
  cout << "✓ Can combine features for powerful abstractions" << endl;
  cout << "======================================================\n" << endl;

  return 0;
}

/*
 * =====================================================================
 * COMMON MISTAKES TO AVOID
 * =====================================================================
 *
 * 1. DEFAULT PARAMETERS NOT RIGHTMOST
 *    ✗ BAD: void func(int a = 5, int b);  // Error!
 *    ✓ GOOD: void func(int a, int b = 5);
 *
 * 2. OVERLOADING BY RETURN TYPE ONLY
 *    ✗ BAD: int get() {...}  and  double get() {...}  // Error!
 *    ✓ GOOD: Differ in parameters, not just return type
 *
 * 3. MISSING BASE CASE IN RECURSION
 *    ✗ BAD: int factorial(int n) { return n * factorial(n-1); }  // Infinite!
 *    ✓ GOOD: if (n <= 1) return 1;  // Base case
 *
 * 4. INLINE FOR LARGE FUNCTIONS
 *    ✗ BAD: inline void process_huge_data() { ...100 lines... }
 *    ✓ GOOD: Use inline only for small functions (1-5 lines)
 *
 * 5. TOO DEEP RECURSION
 *    ✗ BAD: fibonacci(50) without memoization  // Stack overflow!
 *    ✓ GOOD: Use iteration or memoization for deep recursion
 *
 * 6. STATIC WITHOUT INITIALIZATION
 *    ✗ BAD: static int x;  // Uninitialized in function
 *    ✓ GOOD: static int x = 0;  // Always initialize
 *
 * 7. CONFUSING OVERLOAD RESOLUTION
 *    ✗ BAD: func(5.5) with func(int) and func(long)  // Ambiguous!
 *    ✓ GOOD: Make overloads distinct
 *
 * 8. FORGETTING CAPTURE IN LAMBDA
 *    ✗ BAD: int x = 5; auto f = []() { return x; };  // Error!
 *    ✓ GOOD: auto f = [x]() { return x; };  // Capture x
 *
 * =====================================================================
 * PRACTICE EXERCISES
 * =====================================================================
 *
 * 1. Write overloaded max() for 2, 3, and 4 parameters
 * 2. Create print() with default parameters for formatting
 * 3. Write recursive function to print numbers 1 to n
 * 4. Implement binary search using recursion
 * 5. Create function with static variable to track max value seen
 * 6. Write overloaded area() for circle, rectangle, triangle
 * 7. Implement recursive greatest common divisor (GCD)
 * 8. Create inline functions for common math operations
 * 9. Write recursive function to check if string is palindrome
 * 10. Use function pointers to create simple calculator
 * 11. Implement Tower of Hanoi using recursion
 * 12. Create overloaded search() for different data types
 * 13. Write recursive function to generate permutations
 * 14. Use lambdas to sort vector with custom comparison
 * 15. Implement memoized Fibonacci using static variables
 *
 * =====================================================================
 * RECURSION BEST PRACTICES
 * =====================================================================
 *
 * 1. ALWAYS HAVE BASE CASE
 *    - Condition that stops recursion
 *    - Usually simplest input (n=0, empty array, etc.)
 *
 * 2. ENSURE PROGRESS TOWARD BASE CASE
 *    - Each call should get closer to base case
 *    - factorial(n-1), not factorial(n)
 *
 * 3. TRUST THE RECURSION
 *    - Assume recursive call works correctly
 *    - Focus on current level
 *
 * 4. WATCH STACK DEPTH
 *    - Deep recursion can cause stack overflow
 *    - Consider iteration for large inputs
 *
 * 5. CONSIDER MEMOIZATION
 *    - Cache results to avoid recalculation
 *    - Crucial for problems like Fibonacci
 *
 * =====================================================================
 * WHEN TO USE EACH FEATURE
 * =====================================================================
 *
 * DEFAULT PARAMETERS:
 *   ✓ Optional configuration (logging level, precision)
 *   ✓ Backward compatibility
 *   ✗ When all parameters equally important
 *
 * OVERLOADING:
 *   ✓ Same operation on different types
 *   ✓ Different parameter counts for same concept
 *   ✗ When behavior is completely different
 *
 * INLINE:
 *   ✓ Small, frequently called functions
 *   ✓ Performance-critical code
 *   ✗ Large functions, recursive functions
 *
 * RECURSION:
 *   ✓ Tree/graph traversal
 *   ✓ Divide and conquer algorithms
 *   ✓ Mathematical definitions (factorial, Fibonacci)
 *   ✗ Simple loops, memory-constrained environments
 *
 * STATIC VARIABLES:
 *   ✓ Counters, caches
 *   ✓ Unique ID generation
 *   ✗ Multi-threaded code (without synchronization)
 *
 * FUNCTION POINTERS:
 *   ✓ Callbacks
 *   ✓ Strategy pattern
 *   ✓ Plugin systems
 *
 * LAMBDAS:
 *   ✓ Short, one-time functions
 *   ✓ STL algorithms (sort, find_if)
 *   ✓ Callbacks
 *
 * =====================================================================
 * COMPILATION AND EXECUTION
 * =====================================================================
 *
 * To compile and run:
 *   g++ -std=c++17 advanced_functions.cpp -o advanced_functions
 *   ./advanced_functions
 *
 * For C++11 features (lambdas):
 *   g++ -std=c++11 advanced_functions.cpp -o advanced_functions
 *
 * =====================================================================
 */
