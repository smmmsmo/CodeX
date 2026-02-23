#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
 * =====================================================================
 * TOPIC 7.2: REFERENCES AND FUNCTION POINTERS
 * =====================================================================
 *
 * WHAT ARE REFERENCES?
 * References are aliases - alternative names for existing variables.
 * Unlike pointers, references must be initialized and cannot be null.
 *
 * KEY CONCEPTS COVERED:
 * 1. Reference basics and declaration
 * 2. References vs Pointers comparison
 * 3. Pass by reference vs pass by value
 * 4. Reference parameters in functions
 * 5. Const references
 * 6. Returning references from functions
 * 7. Function pointers
 * 8. Applications and best practices
 *
 * =====================================================================
 * REFERENCE FUNDAMENTALS
 * =====================================================================
 *
 * SYNTAX:
 *   type& ref_name = variable;
 *
 * KEY PROPERTIES:
 * 1. Must be initialized at declaration
 * 2. Cannot be null
 * 3. Cannot be reassigned (always refers to same variable)
 * 4. No special syntax to access value (use like normal variable)
 *
 * WHEN TO USE REFERENCES VS POINTERS:
 * References:
 *   - Function parameters (avoid copying)
 *   - Return values from functions
 *   - When you need an alias that won't change
 *   - When null is not a valid state
 *
 * Pointers:
 *   - Need to reassign to different objects
 *   - Need null/optional state
 *   - Dynamic memory allocation
 *   - Arrays and pointer arithmetic
 *   - Complex data structures
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: REFERENCE BASICS ==============
void example1_reference_basics() {
  cout << "\n============== EXAMPLE 1: REFERENCE BASICS ==============" << endl;
  cout << "Understanding references as aliases\n" << endl;

  int original = 100;
  int &ref = original; // ref is alias for original

  cout << "original = " << original << endl;
  cout << "ref = " << ref << endl;

  // Modifying through reference
  ref = 200;

  cout << "\nAfter ref = 200:" << endl;
  cout << "original = " << original << endl;
  cout << "ref = " << ref << endl;

  // Modifying original
  original = 300;

  cout << "\nAfter original = 300:" << endl;
  cout << "original = " << original << endl;
  cout << "ref = " << ref << endl;

  cout << "\nref and original are the same variable!" << endl;
  cout << "Address of original: " << &original << endl;
  cout << "Address of ref: " << &ref << endl;
}

// ============== EXAMPLE 2: REFERENCES VS POINTERS ==============
void example2_references_vs_pointers() {
  cout << "\n============== EXAMPLE 2: REFERENCES VS POINTERS =============="
       << endl;

  int value = 42;

  // Pointer
  int *ptr = &value;
  cout << "POINTER:" << endl;
  cout << "  Declaration: int* ptr = &value;" << endl;
  cout << "  Access value: *ptr = " << *ptr << endl;
  cout << "  Modify: *ptr = 100;" << endl;
  *ptr = 100;
  cout << "  Result: value = " << value << endl;

  value = 42; // Reset

  // Reference
  int &ref = value;
  cout << "\nREFERENCE:" << endl;
  cout << "  Declaration: int& ref = value;" << endl;
  cout << "  Access value: ref = " << ref << endl;
  cout << "  Modify: ref = 100;" << endl;
  ref = 100;
  cout << "  Result: value = " << value << endl;

  cout << "\n┌────────────────┬──────────────┬──────────────┐" << endl;
  cout << "│ Feature        │ Pointer      │ Reference    │" << endl;
  cout << "├────────────────┼──────────────┼──────────────┤" << endl;
  cout << "│ Nullable       │ Yes (nullptr)│ No           │" << endl;
  cout << "│ Reassignable   │ Yes          │ No           │" << endl;
  cout << "│ Initialization │ Optional     │ Required     │" << endl;
  cout << "│ Dereference    │ Need *       │ Automatic    │" << endl;
  cout << "│ Arithmetic     │ Yes          │ No           │" << endl;
  cout << "└────────────────┴──────────────┴──────────────┘" << endl;
}

// ============== EXAMPLE 3: PASS BY VALUE VS REFERENCE ==============
void pass_by_value(int x) {
  x = 999; // Modifies copy only
}

void pass_by_reference(int &x) {
  x = 999; // Modifies original
}

void pass_by_pointer(int *x) {
  *x = 999; // Modifies original through pointer
}

void example3_pass_by_value_reference() {
  cout
      << "\n============== EXAMPLE 3: PASS BY VALUE VS REFERENCE =============="
      << endl;

  int num1 = 10, num2 = 20, num3 = 30;

  cout << "Initial values: num1=" << num1 << " num2=" << num2
       << " num3=" << num3 << endl;

  pass_by_value(num1);
  cout << "After pass_by_value(num1): num1 = " << num1 << " (unchanged)"
       << endl;

  pass_by_reference(num2);
  cout << "After pass_by_reference(num2): num2 = " << num2 << " (changed!)"
       << endl;

  pass_by_pointer(&num3);
  cout << "After pass_by_pointer(&num3): num3 = " << num3 << " (changed!)"
       << endl;

  cout << "\nUse references to modify original variables!" << endl;
}

// ============== EXAMPLE 4: REFERENCE PARAMETERS FOR EFFICIENCY ==============
struct LargeData {
  int data[1000];
  string name;
};

void process_by_value(LargeData obj) {
  // Copies entire object (expensive!)
  cout << "  Processing (by value): " << obj.name << endl;
}

void process_by_reference(LargeData &obj) {
  // No copy (efficient!)
  cout << "  Processing (by reference): " << obj.name << endl;
}

void process_by_const_reference(const LargeData &obj) {
  // No copy, but cannot modify (safe and efficient!)
  cout << "  Processing (by const reference): " << obj.name << endl;
  // obj.name = "new";  // ERROR! Cannot modify const reference
}

void example4_reference_efficiency() {
  cout << "\n============== EXAMPLE 4: REFERENCE PARAMETERS FOR EFFICIENCY "
          "=============="
       << endl;

  LargeData large;
  large.name = "BigObject";

  cout << "sizeof(LargeData) = " << sizeof(LargeData) << " bytes" << endl;
  cout << "sizeof(reference) = " << sizeof(LargeData &) << " bytes" << endl;

  cout << "\nPassing to functions:" << endl;
  process_by_value(large);           // Slow: copies 4000+ bytes
  process_by_reference(large);       // Fast: passes 8 bytes (address)
  process_by_const_reference(large); // Fast + safe

  cout << "\nBest Practice: Use const reference for large objects!" << endl;
}

// ============== EXAMPLE 5: SWAP USING REFERENCES ==============
void swap_by_reference(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

void example5_swap_references() {
  cout << "\n============== EXAMPLE 5: SWAP USING REFERENCES =============="
       << endl;

  int x = 10, y = 20;

  cout << "Before swap: x = " << x << ", y = " << y << endl;

  swap_by_reference(x, y);

  cout << "After swap: x = " << x << ", y = " << y << endl;

  cout << "\nCleaner syntax than pointers (no & or *)!" << endl;
}

// ============== EXAMPLE 6: MULTIPLE RETURN VALUES ==============
void get_min_max(const vector<int> &nums, int &min_val, int &max_val) {
  min_val = nums[0];
  max_val = nums[0];

  for (int num : nums) {
    if (num < min_val)
      min_val = num;
    if (num > max_val)
      max_val = num;
  }
}

void example6_multiple_returns() {
  cout << "\n============== EXAMPLE 6: MULTIPLE RETURN VALUES =============="
       << endl;

  vector<int> numbers = {5, 2, 9, 1, 7, 3};
  int min, max;

  get_min_max(numbers, min, max);

  cout << "Array: ";
  for (int n : numbers)
    cout << n << " ";
  cout << endl;

  cout << "Min: " << min << endl;
  cout << "Max: " << max << endl;

  cout << "\nUse references to return multiple values!" << endl;
}

// ============== EXAMPLE 7: CONST REFERENCES ==============
void print_value(const int &val) {
  cout << "  Value: " << val << endl;
  // val = 100;  // ERROR! Cannot modify const reference
}

void example7_const_references() {
  cout << "\n============== EXAMPLE 7: CONST REFERENCES ==============" << endl;

  int num = 42;
  const int &const_ref = num;

  cout << "num = " << num << endl;
  cout << "const_ref = " << const_ref << endl;

  num = 100; // OK: can modify original
  cout << "\nAfter num = 100:" << endl;
  cout << "num = " << num << endl;
  cout << "const_ref = " << const_ref << endl;

  // const_ref = 200;  // ERROR! Cannot modify through const reference

  cout << "\nPassing to function:" << endl;
  print_value(num);

  cout << "\nconst reference prevents accidental modification!" << endl;
}

// ============== EXAMPLE 8: RETURNING REFERENCES ==============
int global_value = 100;

int &get_global() {
  return global_value; // OK: global variable persists
}

// WARNING: Never return reference to local variable!
// int& bad_function() {
//     int local = 42;
//     return local;  // DANGER! local destroyed after function ends
// }

void example8_returning_references() {
  cout << "\n============== EXAMPLE 8: RETURNING REFERENCES =============="
       << endl;

  cout << "global_value = " << global_value << endl;

  get_global() = 200; // Can assign to reference!

  cout << "After get_global() = 200:" << endl;
  cout << "global_value = " << global_value << endl;

  cout << "\nWARNING: Never return reference to local variable!" << endl;
  cout << "Only return references to:" << endl;
  cout << "  - Global variables" << endl;
  cout << "  - Static variables" << endl;
  cout << "  - Member variables of objects" << endl;
  cout << "  - Function parameters" << endl;
}

// ============== EXAMPLE 9: REFERENCE IN RANGE-BASED FOR LOOP ==============
void example9_range_for_references() {
  cout << "\n============== EXAMPLE 9: REFERENCES IN RANGE-BASED FOR "
          "=============="
       << endl;

  vector<int> numbers = {1, 2, 3, 4, 5};

  cout << "Original: ";
  for (int n : numbers)
    cout << n << " ";
  cout << endl;

  // Modify using reference
  cout << "\nDoubling each element (using reference):" << endl;
  for (int &n : numbers) {
    n *= 2;
  }

  cout << "After: ";
  for (int n : numbers)
    cout << n << " ";
  cout << endl;

  // Read-only with const reference (efficient for large objects)
  cout << "\nUsing const reference (no copy, read-only):" << endl;
  for (const int &n : numbers) {
    cout << n << " ";
    // n *= 2;  // ERROR! Cannot modify const reference
  }
  cout << endl;

  cout << "\nUse reference in loops to modify elements!" << endl;
}

// ============== EXAMPLE 10: FUNCTION POINTERS BASICS ==============
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

void example10_function_pointers() {
  cout << "\n============== EXAMPLE 10: FUNCTION POINTERS BASICS =============="
       << endl;

  // Declare function pointer
  int (*operation)(int, int);

  cout << "Using function pointers:\n" << endl;

  operation = add;
  cout << "add(5, 3) = " << operation(5, 3) << endl;

  operation = subtract;
  cout << "subtract(5, 3) = " << operation(5, 3) << endl;

  operation = multiply;
  cout << "multiply(5, 3) = " << operation(5, 3) << endl;

  cout << "\nFunction pointers enable dynamic function selection!" << endl;
}

// ============== EXAMPLE 11: FUNCTION POINTERS IN ARRAYS ==============
double circle_area(double r) { return 3.14159 * r * r; }
double square_area(double s) { return s * s; }
double triangle_area(double b) { return 0.5 * b * b; }

void example11_function_pointer_array() {
  cout << "\n============== EXAMPLE 11: FUNCTION POINTERS IN ARRAYS "
          "=============="
       << endl;

  // Array of function pointers
  double (*area_calculators[])(double) = {circle_area, square_area,
                                          triangle_area};
  const char *shapes[] = {"Circle", "Square", "Triangle"};

  double value = 5.0;

  cout << "Calculating areas for value " << value << ":\n" << endl;

  for (int i = 0; i < 3; i++) {
    cout << shapes[i] << ": " << area_calculators[i](value) << endl;
  }

  cout << "\nStore related functions in arrays!" << endl;
}

// ============== EXAMPLE 12: CALLBACK FUNCTIONS ==============
void process_array(int arr[], int size, void (*callback)(int)) {
  for (int i = 0; i < size; i++) {
    callback(arr[i]);
  }
}

void print_number(int n) { cout << n << " "; }

void print_square(int n) { cout << n * n << " "; }

void example12_callbacks() {
  cout << "\n============== EXAMPLE 12: CALLBACK FUNCTIONS =============="
       << endl;

  int numbers[] = {1, 2, 3, 4, 5};

  cout << "Original numbers: ";
  process_array(numbers, 5, print_number);
  cout << endl;

  cout << "Squares: ";
  process_array(numbers, 5, print_square);
  cout << endl;

  cout << "\nCallbacks allow customizable behavior!" << endl;
}

// ============== EXAMPLE 13: SORTING WITH FUNCTION POINTERS ==============
bool ascending(int a, int b) { return a < b; }
bool descending(int a, int b) { return a > b; }

void bubble_sort(int arr[], int size, bool (*compare)(int, int)) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (compare(arr[j + 1], arr[j])) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void example13_sorting_callbacks() {
  cout << "\n============== EXAMPLE 13: SORTING WITH CALLBACKS =============="
       << endl;

  int arr1[] = {5, 2, 8, 1, 9};
  int arr2[] = {5, 2, 8, 1, 9};
  int size = 5;

  bubble_sort(arr1, size, ascending);
  cout << "Ascending: ";
  for (int i = 0; i < size; i++)
    cout << arr1[i] << " ";
  cout << endl;

  bubble_sort(arr2, size, descending);
  cout << "Descending: ";
  for (int i = 0; i < size; i++)
    cout << arr2[i] << " ";
  cout << endl;

  cout << "\nCustomizable sorting with function pointers!" << endl;
}

// ============== EXAMPLE 14: TYPEDEF FOR FUNCTION POINTERS ==============
typedef int (*MathOperation)(int, int);

int apply_operation(int a, int b, MathOperation op) { return op(a, b); }

void example14_typedef_function_pointers() {
  cout << "\n============== EXAMPLE 14: TYPEDEF FOR FUNCTION POINTERS "
          "=============="
       << endl;

  cout << "Using typedef for cleaner syntax:\n" << endl;

  cout << "5 + 3 = " << apply_operation(5, 3, add) << endl;
  cout << "5 - 3 = " << apply_operation(5, 3, subtract) << endl;
  cout << "5 * 3 = " << apply_operation(5, 3, multiply) << endl;

  cout << "\ntypedef makes function pointers easier to use!" << endl;
}

// ============== EXAMPLE 15: PRACTICAL COMPARISON ==============
class Student {
public:
  string name;
  int score;

  Student(string n, int s) : name(n), score(s) {}
};

void update_score_pointer(Student *s, int new_score) { s->score = new_score; }

void update_score_reference(Student &s, int new_score) { s.score = new_score; }

void example15_practical_comparison() {
  cout << "\n============== EXAMPLE 15: PRACTICAL COMPARISON =============="
       << endl;

  Student alice("Alice", 85);

  cout << "Initial: " << alice.name << " - " << alice.score << endl;

  // Using pointer
  update_score_pointer(&alice, 90);
  cout << "After pointer update: " << alice.score << endl;

  // Using reference
  update_score_reference(alice, 95);
  cout << "After reference update: " << alice.score << endl;

  cout << "\nREFERENCE BENEFITS:" << endl;
  cout << "  ✓ Cleaner syntax (no & or * needed)" << endl;
  cout << "  ✓ Cannot be null (safer)" << endl;
  cout << "  ✓ Cannot be reassigned (prevents bugs)" << endl;

  cout << "\nPOINTER BENEFITS:" << endl;
  cout << "  ✓ Can represent 'no value' (nullptr)" << endl;
  cout << "  ✓ Can be reassigned" << endl;
  cout << "  ✓ Required for dynamic memory" << endl;
  cout << "  ✓ Support arithmetic operations" << endl;
}

int main() {
  cout << "\n======================================================" << endl;
  cout << "       REFERENCES & FUNCTION POINTERS TUTORIAL        " << endl;
  cout << "======================================================" << endl;

  example1_reference_basics();
  example2_references_vs_pointers();
  example3_pass_by_value_reference();
  example4_reference_efficiency();
  example5_swap_references();
  example6_multiple_returns();
  example7_const_references();
  example8_returning_references();
  example9_range_for_references();
  example10_function_pointers();
  example11_function_pointer_array();
  example12_callbacks();
  example13_sorting_callbacks();
  example14_typedef_function_pointers();
  example15_practical_comparison();

  cout << "\n======================================================" << endl;
  cout << "                   KEY TAKEAWAYS                      " << endl;
  cout << "======================================================" << endl;
  cout << "REFERENCES:" << endl;
  cout << "✓ Aliases for variables (same memory location)" << endl;
  cout << "✓ Must be initialized, cannot be null" << endl;
  cout << "✓ Cannot be reassigned" << endl;
  cout << "✓ Use for function parameters (efficiency)" << endl;
  cout << "✓ Use const& for read-only large objects" << endl;
  cout << "✓ Cleaner syntax than pointers" << endl;

  cout << "\nFUNCTION POINTERS:" << endl;
  cout << "✓ Store addresses of functions" << endl;
  cout << "✓ Enable callbacks and dynamic dispatch" << endl;
  cout << "✓ Syntax: return_type (*name)(params)" << endl;
  cout << "✓ Use typedef for cleaner code" << endl;
  cout << "✓ Useful for customizable algorithms" << endl;

  cout << "\nWHEN TO USE WHAT:" << endl;
  cout << "Reference: Function params, return values, aliases" << endl;
  cout << "Pointer: Nullable, reassignable, arrays, dynamic memory" << endl;
  cout << "======================================================\n" << endl;

  return 0;
}

/*
 * =====================================================================
 * REFERENCES VS POINTERS: DETAILED COMPARISON
 * =====================================================================
 *
 * ┌─────────────────────┬──────────────────┬────────────────────┐
 * │ Feature             │ Reference        │ Pointer            │
 * ├─────────────────────┼──────────────────┼────────────────────┤
 * │ Syntax              │ type& name       │ type* name         │
 * │ Initialization      │ Required         │ Optional           │
 * │ Null value          │ No               │ Yes (nullptr)      │
 * │ Reassignment        │ No               │ Yes                │
 * │ Access value        │ Direct (name)    │ Dereference (*ptr) │
 * │ Memory overhead     │ None (alias)     │ Size of pointer    │
 * │ Arithmetic          │ No               │ Yes                │
 * │ Array access        │ Limited          │ Full support       │
 * │ Dynamic memory      │ No               │ Yes (new/delete)   │
 * │ Can be member       │ Yes              │ Yes                │
 * │ Can be in array     │ No               │ Yes                │
 * │ Multilevel          │ No               │ Yes (**, ***, etc.)│
 * └─────────────────────┴──────────────────┴────────────────────┘
 *
 * =====================================================================
 * WHEN TO USE REFERENCES
 * =====================================================================
 *
 * 1. FUNCTION PARAMETERS (avoid copying)
 *    void process(const LargeObject& obj);
 *
 * 2. RETURN VALUES (enable chaining)
 *    ostream& operator<<(ostream& os, const T& obj);
 *
 * 3. RANGE-BASED FOR LOOPS (modify elements)
 *    for (auto& element : container) { element *= 2; }
 *
 * 4. OPERATOR OVERLOADING
 *    MyClass& operator=(const MyClass& other);
 *
 * 5. ALIASES (cleaner code)
 *    auto& config = app.getConfiguration();
 *
 * =====================================================================
 * WHEN TO USE POINTERS
 * =====================================================================
 *
 * 1. OPTIONAL VALUES (can be null)
 *    Student* findStudent(int id);  // Returns nullptr if not found
 *
 * 2. DYNAMIC MEMORY
 *    int* arr = new int[size];
 *
 * 3. POLYMORPHISM (with inheritance)
 *    Base* ptr = new Derived();
 *
 * 4. DATA STRUCTURES (linked lists, trees)
 *    struct Node { int data; Node* next; };
 *
 * 5. ARRAYS AND POINTER ARITHMETIC
 *    for (int* p = arr; p < arr + size; ++p)
 *
 * 6. REASSIGNMENT NEEDED
 *    ptr = &another_object;
 *
 * =====================================================================
 * FUNCTION POINTER SYNTAX
 * =====================================================================
 *
 * BASIC DECLARATION:
 *   int (*func_ptr)(int, int);
 *
 *   Read as: "func_ptr is a pointer to a function that takes
 *            two ints and returns an int"
 *
 * ASSIGNMENT:
 *   func_ptr = &function_name;  // Explicit
 *   func_ptr = function_name;   // Implicit (preferred)
 *
 * CALLING:
 *   result = (*func_ptr)(5, 3);  // Explicit dereference
 *   result = func_ptr(5, 3);     // Implicit (preferred)
 *
 * TYPEDEF FOR CLARITY:
 *   typedef int (*BinaryOp)(int, int);
 *   BinaryOp op = add;
 *
 * USING (C++11):
 *   using BinaryOp = int(*)(int, int);
 *
 * =====================================================================
 * COMMON MISTAKES
 * =====================================================================
 *
 * 1. UNINITIALIZED REFERENCE
 *    ✗ BAD: int& ref;  // ERROR! Must initialize
 *    ✓ GOOD: int& ref = variable;
 *
 * 2. REFERENCE TO TEMPORARY
 *    ✗ BAD: int& ref = 42;  // ERROR! (non-const reference)
 *    ✓ GOOD: const int& ref = 42;  // OK (const reference)
 *
 * 3. RETURNING REFERENCE TO LOCAL
 *    ✗ BAD: int& func() { int x = 10; return x; }  // DANGER!
 *    ✓ GOOD: int& func() { static int x = 10; return x; }
 *
 * 4. MODIFYING CONST REFERENCE
 *    ✗ BAD: void f(const int& x) { x = 10; }  // ERROR!
 *    ✓ GOOD: void f(int& x) { x = 10; }
 *
 * 5. CONFUSING FUNCTION POINTER SYNTAX
 *    ✗ BAD: int* func(int, int);  // Function returning int*
 *    ✓ GOOD: int (*func)(int, int);  // Pointer to function
 *
 * 6. FORGETTING & WHEN PASSING TO REFERENCE PARAMETER
 *    void swap(int& a, int& b);
 *    ✗ BAD: swap(&x, &y);  // Wrong! Passing addresses
 *    ✓ GOOD: swap(x, y);   // Correct!
 *
 * =====================================================================
 * BEST PRACTICES
 * =====================================================================
 *
 * REFERENCES:
 * ☑ Prefer const references for function parameters (large objects)
 * ☑ Use references for operator overloading
 * ☑ Use references in range-for when modifying elements
 * ☑ Never return reference to local variable
 * ☑ Initialize references immediately
 *
 * POINTERS:
 * ☑ Initialize to nullptr if no immediate value
 * ☑ Check for nullptr before dereferencing
 * ☑ Use smart pointers for dynamic memory (modern C++)
 * ☑ Prefer references when pointer won't be null/reassigned
 *
 * FUNCTION POINTERS:
 * ☑ Use typedef/using for complex function pointer types
 * ☑ Consider std::function<> for more flexibility (C++11)
 * ☑ Consider lambdas for simple callbacks (C++11)
 *
 * =====================================================================
 * PRACTICE EXERCISES
 * =====================================================================
 *
 * REFERENCES:
 * 1. Write swap function using references
 * 2. Create function returning multiple values via references
 * 3. Implement function taking const reference to avoid copying
 * 4. Write range-for loop modifying vector elements
 * 5. Create function that increments value via reference
 * 6. Implement reference-based array rotation
 * 7. Write function to find min/max using output references
 * 8. Create alias for complex nested structure
 * 9. Implement operator<< using reference return
 * 10. Practice const vs non-const references
 *
 * FUNCTION POINTERS:
 * 11. Create calculator using function pointers
 * 12. Implement custom sort with comparison callback
 * 13. Write menu system using function pointer array
 * 14. Create event system with callback functions
 * 15. Implement strategy pattern with function pointers
 * 16. Write filter function with predicate callback
 * 17. Create simple state machine using function pointers
 * 18. Implement map/reduce using callbacks
 * 19. Write plugin system using function pointers
 * 20. Practice typedef/using with complex function signatures
 *
 * =====================================================================
 * COMPILATION AND EXECUTION
 * =====================================================================
 *
 * To compile and run:
 *   g++ -std=c++17 2_references_func_pointers.cpp -o references
 *   ./references
 *
 * With warnings:
 *   g++ -std=c++17 -Wall -Wextra 2_references_func_pointers.cpp -o references
 *
 * =====================================================================
 */
