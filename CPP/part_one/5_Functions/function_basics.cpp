#include <cmath>
#include <iostream>
#include <string>
using namespace std;

/*
 * =====================================================================
 * TOPIC 5.1: FUNCTION BASICS
 * =====================================================================
 *
 * WHAT ARE FUNCTIONS?
 * Functions are self-contained blocks of code that perform a specific task.
 * They help organize code, promote reusability, and make programs modular.
 *
 * KEY CONCEPTS COVERED:
 * 1. Function declaration (prototype)
 * 2. Function definition
 * 3. Function parameters and arguments
 * 4. Return types and return statements
 * 5. Function calling
 * 6. Pass by value vs pass by reference
 * 7. Void functions
 * 8. Multiple return statements
 *
 * =====================================================================
 * FUNCTION ANATOMY
 * =====================================================================
 *
 * return_type function_name(parameter_list) {
 *     // Function body
 *     // Statements
 *     return value;  // If return_type is not void
 * }
 *
 * PARTS:
 * 1. Return Type: Type of value function returns (int, double, void, etc.)
 * 2. Function Name: Identifier to call the function
 * 3. Parameters: Input values (optional)
 * 4. Function Body: Code to execute
 * 5. Return Statement: Value to return (if not void)
 *
 * =====================================================================
 * FUNCTION DECLARATION vs DEFINITION
 * =====================================================================
 *
 * DECLARATION (Prototype):
 *    - Tells compiler function exists
 *    - Usually placed before main() or in header files
 *    - Syntax: return_type function_name(parameter_types);
 *
 * DEFINITION:
 *    - Actual implementation of the function
 *    - Contains the function body
 *    - Can be placed after main() if declared first
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: SIMPLE FUNCTION WITH NO PARAMETERS ==============
void greet() {
  cout << "Hello, World!" << endl;
  cout << "Welcome to C++ Functions!" << endl;
}

void example1_simple_function() {
  cout << "\n============== EXAMPLE 1: SIMPLE FUNCTION ==============" << endl;
  cout << "Function with no parameters and void return type\n" << endl;

  cout << "Calling greet() function:" << endl;
  greet();
  greet(); // Can call multiple times

  cout << "\nThis function doesn't return any value (void)" << endl;
}

// ============== EXAMPLE 2: FUNCTION WITH RETURN VALUE ==============
int add(int a, int b) {
  int sum = a + b;
  return sum;
}

void example2_return_value() {
  cout
      << "\n============== EXAMPLE 2: FUNCTION WITH RETURN VALUE =============="
      << endl;
  cout << "Function that returns an integer\n" << endl;

  int result = add(5, 3);
  cout << "add(5, 3) = " << result << endl;

  result = add(10, 20);
  cout << "add(10, 20) = " << result << endl;

  // Can use directly in expressions
  cout << "add(7, 8) * 2 = " << add(7, 8) * 2 << endl;

  cout << "\nReturn type: int" << endl;
  cout << "The 'return' statement sends value back to caller" << endl;
}

// ============== EXAMPLE 3: FUNCTION WITH MULTIPLE PARAMETERS ==============
double calculate_area(double length, double width) { return length * width; }

double calculate_perimeter(double length, double width) {
  return 2 * (length + width);
}

void example3_multiple_parameters() {
  cout << "\n============== EXAMPLE 3: MULTIPLE PARAMETERS =============="
       << endl;
  cout << "Functions can take multiple inputs\n" << endl;

  double len = 5.5, wid = 3.2;

  cout << "Rectangle: length = " << len << ", width = " << wid << endl;
  cout << "Area = " << calculate_area(len, wid) << endl;
  cout << "Perimeter = " << calculate_perimeter(len, wid) << endl;

  cout << "\nParameters are separated by commas" << endl;
  cout << "Order matters when calling the function!" << endl;
}

// ============== EXAMPLE 4: DIFFERENT RETURN TYPES ==============
int get_integer() { return 42; }

double get_double() { return 3.14159; }

char get_character() { return 'A'; }

bool is_positive(int num) { return num > 0; }

string get_greeting() { return "Hello from function!"; }

void example4_return_types() {
  cout << "\n============== EXAMPLE 4: DIFFERENT RETURN TYPES =============="
       << endl;
  cout << "Functions can return various data types\n" << endl;

  cout << "int function: " << get_integer() << endl;
  cout << "double function: " << get_double() << endl;
  cout << "char function: " << get_character() << endl;
  cout << "bool function: " << (is_positive(5) ? "true" : "false") << endl;
  cout << "string function: " << get_greeting() << endl;

  cout << "\nReturn type must match what function returns!" << endl;
}

// ============== EXAMPLE 5: PASS BY VALUE ==============
void modify_value(int x) {
  cout << "  Inside function, before: x = " << x << endl;
  x = x + 10;
  cout << "  Inside function, after: x = " << x << endl;
}

void example5_pass_by_value() {
  cout << "\n============== EXAMPLE 5: PASS BY VALUE ==============" << endl;
  cout << "Default in C++: arguments passed by value (copy)\n" << endl;

  int num = 5;
  cout << "Before function call: num = " << num << endl;

  modify_value(num);

  cout << "After function call: num = " << num << endl;
  cout << "\nOriginal variable unchanged! Function got a copy." << endl;
}

// ============== EXAMPLE 6: PASS BY REFERENCE ==============
void modify_by_reference(int &x) {
  cout << "  Inside function, before: x = " << x << endl;
  x = x + 10;
  cout << "  Inside function, after: x = " << x << endl;
}

void example6_pass_by_reference() {
  cout << "\n============== EXAMPLE 6: PASS BY REFERENCE =============="
       << endl;
  cout << "Using & to pass by reference (modify original)\n" << endl;

  int num = 5;
  cout << "Before function call: num = " << num << endl;

  modify_by_reference(num);

  cout << "After function call: num = " << num << endl;
  cout << "\nOriginal variable CHANGED! Function modified the original."
       << endl;
}

// ============== EXAMPLE 7: MULTIPLE RETURN POINTS ==============
string check_grade(int score) {
  if (score >= 90) {
    return "A"; // Early return
  }
  if (score >= 80) {
    return "B";
  }
  if (score >= 70) {
    return "C";
  }
  if (score >= 60) {
    return "D";
  }
  return "F"; // Default return
}

void example7_multiple_returns() {
  cout
      << "\n============== EXAMPLE 7: MULTIPLE RETURN STATEMENTS =============="
      << endl;
  cout << "Function can have multiple return points\n" << endl;

  int scores[] = {95, 85, 72, 65, 50};

  for (int score : scores) {
    cout << "Score " << score << " = Grade " << check_grade(score) << endl;
  }

  cout << "\nFirst matching condition returns and exits function" << endl;
}

// ============== EXAMPLE 8: VOID FUNCTION WITH PARAMETERS ==============
void print_box(int width, int height, char symbol) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      cout << symbol;
    }
    cout << endl;
  }
}

void example8_void_with_params() {
  cout << "\n============== EXAMPLE 8: VOID FUNCTION WITH PARAMETERS "
          "=============="
       << endl;
  cout << "Void functions can take parameters\n" << endl;

  cout << "Box 1 (5x3, *):" << endl;
  print_box(5, 3, '*');

  cout << "\nBox 2 (8x2, #):" << endl;
  print_box(8, 2, '#');

  cout << "\nVoid functions perform actions but don't return values" << endl;
}

// ============== EXAMPLE 9: FUNCTION RETURNING CALCULATED VALUE ==============
double celsius_to_fahrenheit(double celsius) {
  return (celsius * 9.0 / 5.0) + 32.0;
}

double fahrenheit_to_celsius(double fahrenheit) {
  return (fahrenheit - 32.0) * 5.0 / 9.0;
}

void example9_temperature_conversion() {
  cout << "\n============== EXAMPLE 9: TEMPERATURE CONVERSION =============="
       << endl;
  cout << "Functions for calculations\n" << endl;

  double temp_c = 25.0;
  double temp_f = celsius_to_fahrenheit(temp_c);

  cout << temp_c << "°C = " << temp_f << "°F" << endl;

  temp_f = 77.0;
  temp_c = fahrenheit_to_celsius(temp_f);

  cout << temp_f << "°F = " << temp_c << "°C" << endl;

  cout << "\nFunctions encapsulate formulas for reusability" << endl;
}

// ============== EXAMPLE 10: FUNCTION WITH CONST PARAMETERS ==============
void print_info(const string &name, int age) {
  cout << "Name: " << name << ", Age: " << age << endl;
  // name = "New Name";  // ERROR! Can't modify const reference
}

void example10_const_parameters() {
  cout << "\n============== EXAMPLE 10: CONST REFERENCE PARAMETERS "
          "=============="
       << endl;
  cout << "Use const& for read-only parameters (efficient + safe)\n" << endl;

  string person = "Alice";
  print_info(person, 25);

  print_info("Bob", 30); // Can pass temporary strings

  cout << "\nconst& prevents modification AND avoids copying large objects"
       << endl;
}

// ============== EXAMPLE 11: SWAP FUNCTION ==============
void swap_by_value(int a, int b) {
  int temp = a;
  a = b;
  b = temp;
  cout << "  Inside swap_by_value: a = " << a << ", b = " << b << endl;
}

void swap_by_reference(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
  cout << "  Inside swap_by_reference: a = " << a << ", b = " << b << endl;
}

void example11_swap_comparison() {
  cout << "\n============== EXAMPLE 11: SWAP FUNCTION (VALUE vs REFERENCE) "
          "=============="
       << endl;

  cout << "Pass by value (doesn't work):" << endl;
  int x = 10, y = 20;
  cout << "Before: x = " << x << ", y = " << y << endl;
  swap_by_value(x, y);
  cout << "After: x = " << x << ", y = " << y << " (unchanged!)\n" << endl;

  cout << "Pass by reference (works!):" << endl;
  x = 10;
  y = 20;
  cout << "Before: x = " << x << ", y = " << y << endl;
  swap_by_reference(x, y);
  cout << "After: x = " << x << ", y = " << y << " (swapped!)" << endl;

  cout << "\nUse references when you need to modify arguments" << endl;
}

// ============== EXAMPLE 12: FUNCTION DECLARATION AND DEFINITION ==============
// Declaration (prototype) - tells compiler function exists
int multiply(int a, int b);
double power(double base, int exponent);

void example12_declaration_definition() {
  cout
      << "\n============== EXAMPLE 12: DECLARATION vs DEFINITION =============="
      << endl;
  cout << "Declarations at top, definitions can be after main()\n" << endl;

  cout << "multiply(6, 7) = " << multiply(6, 7) << endl;
  cout << "power(2, 8) = " << power(2, 8) << endl;

  cout << "\nDeclaration tells compiler: 'This function exists'" << endl;
  cout << "Definition provides: 'This is what it does'" << endl;
}

// Definitions (implementations)
int multiply(int a, int b) { return a * b; }

double power(double base, int exponent) {
  double result = 1.0;
  for (int i = 0; i < exponent; i++) {
    result *= base;
  }
  return result;
}

// ============== EXAMPLE 13: RETURNING MULTIPLE VALUES (USING REFERENCES)
// ==============
void get_min_max(int arr[], int size, int &min_val, int &max_val) {
  min_val = arr[0];
  max_val = arr[0];

  for (int i = 1; i < size; i++) {
    if (arr[i] < min_val)
      min_val = arr[i];
    if (arr[i] > max_val)
      max_val = arr[i];
  }
}

void example13_multiple_outputs() {
  cout
      << "\n============== EXAMPLE 13: RETURNING MULTIPLE VALUES =============="
      << endl;
  cout << "Use reference parameters as 'output' parameters\n" << endl;

  int numbers[] = {5, 2, 8, 1, 9, 3, 7};
  int min, max;

  get_min_max(numbers, 7, min, max);

  cout << "Array: ";
  for (int n : numbers)
    cout << n << " ";
  cout << endl;

  cout << "Minimum: " << min << endl;
  cout << "Maximum: " << max << endl;

  cout << "\nReference parameters let functions 'return' multiple values"
       << endl;
}

// ============== EXAMPLE 14: FUNCTION WITH ARRAY PARAMETER ==============
double calculate_average(int arr[], int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }
  return static_cast<double>(sum) / size;
}

void print_array(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    cout << arr[i];
    if (i < size - 1)
      cout << ", ";
  }
  cout << endl;
}

void example14_array_parameters() {
  cout << "\n============== EXAMPLE 14: ARRAY PARAMETERS =============="
       << endl;
  cout << "Passing arrays to functions\n" << endl;

  int scores[] = {85, 92, 78, 95, 88};
  int size = 5;

  cout << "Scores: ";
  print_array(scores, size);

  double avg = calculate_average(scores, size);
  cout << "Average: " << avg << endl;

  cout << "\nArrays are always passed by reference (pointer)" << endl;
  cout << "Must pass size separately!" << endl;
}

// ============== EXAMPLE 15: BOOLEAN FUNCTIONS ==============
bool is_even(int num) { return num % 2 == 0; }

bool is_prime(int num) {
  if (num < 2)
    return false;
  for (int i = 2; i * i <= num; i++) {
    if (num % i == 0)
      return false;
  }
  return true;
}

bool is_in_range(int value, int min, int max) {
  return value >= min && value <= max;
}

void example15_boolean_functions() {
  cout << "\n============== EXAMPLE 15: BOOLEAN FUNCTIONS =============="
       << endl;
  cout << "Functions that return true/false\n" << endl;

  int num = 17;

  cout << num << " is even? " << (is_even(num) ? "Yes" : "No") << endl;
  cout << num << " is prime? " << (is_prime(num) ? "Yes" : "No") << endl;
  cout << num << " in range [10, 20]? "
       << (is_in_range(num, 10, 20) ? "Yes" : "No") << endl;

  cout << "\nBoolean functions great for conditions and validation" << endl;
}

int main() {
  cout << "\n======================================================" << endl;
  cout << "              FUNCTION BASICS TUTORIAL               " << endl;
  cout << "======================================================" << endl;

  example1_simple_function();
  example2_return_value();
  example3_multiple_parameters();
  example4_return_types();
  example5_pass_by_value();
  example6_pass_by_reference();
  example7_multiple_returns();
  example8_void_with_params();
  example9_temperature_conversion();
  example10_const_parameters();
  example11_swap_comparison();
  example12_declaration_definition();
  example13_multiple_outputs();
  example14_array_parameters();
  example15_boolean_functions();

  cout << "\n======================================================" << endl;
  cout << "                   KEY TAKEAWAYS                      " << endl;
  cout << "======================================================" << endl;
  cout << "✓ Functions organize code into reusable blocks" << endl;
  cout << "✓ Declaration tells compiler function exists" << endl;
  cout << "✓ Definition provides implementation" << endl;
  cout << "✓ Pass by value creates copy (safe, but can be slow)" << endl;
  cout << "✓ Pass by reference modifies original (use &)" << endl;
  cout << "✓ const& for read-only parameters (efficient)" << endl;
  cout << "✓ void functions don't return values" << endl;
  cout << "✓ Multiple returns allowed (first one executes)" << endl;
  cout << "✓ Arrays always passed by reference" << endl;
  cout << "✓ Boolean functions useful for conditions" << endl;
  cout << "======================================================\n" << endl;

  return 0;
}

/*
 * =====================================================================
 * COMMON MISTAKES TO AVOID
 * =====================================================================
 *
 * 1. FORGETTING RETURN STATEMENT
 *    ✗ BAD: int add(int a, int b) { int sum = a + b; }  // No return!
 *    ✓ GOOD: int add(int a, int b) { return a + b; }
 *
 * 2. RETURN TYPE MISMATCH
 *    ✗ BAD: int get_value() { return 3.14; }  // Returns double!
 *    ✓ GOOD: double get_value() { return 3.14; }
 *
 * 3. MODIFYING PASS-BY-VALUE EXPECTING CHANGE
 *    ✗ BAD: void change(int x) { x = 10; }  // Doesn't modify original
 *    ✓ GOOD: void change(int& x) { x = 10; }  // Use reference
 *
 * 4. NOT PASSING ARRAY SIZE
 *    ✗ BAD: void print(int arr[])  // Size unknown!
 *    ✓ GOOD: void print(int arr[], int size)
 *
 * 5. RETURNING LOCAL VARIABLE REFERENCE
 *    ✗ BAD: int& get_value() { int x = 5; return x; }  // Dangling reference!
 *    ✓ GOOD: int get_value() { return 5; }  // Return by value
 *
 * 6. VOID FUNCTION WITH RETURN VALUE
 *    ✗ BAD: void print() { return 42; }  // void can't return value!
 *    ✓ GOOD: int get_value() { return 42; }
 *
 * 7. WRONG NUMBER OF ARGUMENTS
 *    ✗ BAD: add(5);  // If add expects 2 parameters
 *    ✓ GOOD: add(5, 3);
 *
 * 8. FORGETTING FUNCTION DECLARATION
 *    ✗ BAD: Calling function before it's declared/defined
 *    ✓ GOOD: Declare before use or define before main()
 *
 * =====================================================================
 * PRACTICE EXERCISES
 * =====================================================================
 *
 * 1. Write a function that finds maximum of three numbers
 * 2. Create a function to check if a year is leap year
 * 3. Write a function to reverse an array (modify original)
 * 4. Create a function to count vowels in a string
 * 5. Write a function to calculate factorial of a number
 * 6. Create a function that returns both quotient and remainder
 * 7. Write a function to find sum of array elements
 * 8. Create a function to check if string is palindrome
 * 9. Write a function to convert string to uppercase
 * 10. Create a function to find GCD of two numbers
 *
 * =====================================================================
 * BEST PRACTICES
 * =====================================================================
 *
 * 1. NAMING CONVENTIONS
 *    - Use descriptive names: calculate_area() not ca()
 *    - Verb for actions: print(), calculate(), validate()
 *    - is/has for booleans: is_prime(), has_element()
 *
 * 2. FUNCTION LENGTH
 *    - Keep functions focused on one task
 *    - Ideally under 50 lines
 *    - If too long, break into smaller functions
 *
 * 3. PARAMETERS
 *    - Limit to 3-4 parameters
 *    - Too many? Consider a struct/class
 *    - Use const& for large objects (strings, vectors)
 *
 * 4. RETURN VALUES
 *    - Prefer return values over output parameters
 *    - Use output parameters only when multiple returns needed
 *    - Be consistent with return types
 *
 * 5. DOCUMENTATION
 *    - Comment complex functions
 *    - Describe parameters and return value
 *    - Explain any non-obvious behavior
 *
 * =====================================================================
 * COMPILATION AND EXECUTION
 * =====================================================================
 *
 * To compile and run:
 *   g++ -std=c++17 function_basics.cpp -o function_basics
 *   ./function_basics
 *
 * =====================================================================
 */
