#include <iostream>
#include <string>
using namespace std;

/*
 * =====================================================================
 * TOPIC 7.1: POINTER BASICS
 * =====================================================================
 *
 * WHAT ARE POINTERS?
 * Pointers are variables that store memory addresses of other variables.
 * They are one of the most powerful and fundamental features in C++.
 *
 * KEY CONCEPTS COVERED:
 * 1. Pointer declaration and initialization
 * 2. Address-of operator (&)
 * 3. Dereference operator (*)
 * 4. Pointer arithmetic
 * 5. Pointers and arrays relationship
 * 6. Null pointers and nullptr
 * 7. Pointer to pointer
 * 8. Common pointer pitfalls
 *
 * =====================================================================
 * POINTER FUNDAMENTALS
 * =====================================================================
 *
 * MEMORY CONCEPTS:
 * Every variable occupies a location in memory
 * Each memory location has a unique address
 * Pointers store these addresses
 *
 * SYNTAX:
 *   type* pointer_name;        // Pointer declaration
 *   pointer_name = &variable;  // Get address of variable
 *   value = *pointer_name;     // Dereference (get value at address)
 *
 * OPERATORS:
 *   & (address-of): Returns memory address of variable
 *   * (dereference): Accesses value at memory address
 *
 * WHY USE POINTERS?
 * 1. Dynamic memory allocation
 * 2. Efficient passing of large data structures
 * 3. Building complex data structures (linked lists, trees)
 * 4. Low-level memory manipulation
 * 5. Function pointers for callbacks
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: BASIC POINTER DECLARATION ==============
void example1_pointer_basics() {
  cout << "\n============== EXAMPLE 1: POINTER BASICS ==============" << endl;
  cout << "Understanding pointers, addresses, and values\n" << endl;

  int num = 42;
  int *ptr; // Declare pointer to int

  ptr = &num; // Store address of num in ptr

  cout << "Variable num:" << endl;
  cout << "  Value: " << num << endl;
  cout << "  Address: " << &num << endl;

  cout << "\nPointer ptr:" << endl;
  cout << "  Stores address: " << ptr << endl;
  cout << "  Value at address (*ptr): " << *ptr << endl;
  cout << "  Address of ptr itself: " << &ptr << endl;

  cout << "\n& = address-of operator" << endl;
  cout << "* = dereference operator (get value)" << endl;
}

// ============== EXAMPLE 2: ADDRESS-OF OPERATOR (&) ==============
void example2_address_of() {
  cout << "\n============== EXAMPLE 2: ADDRESS-OF OPERATOR (&) =============="
       << endl;
  cout << "Getting addresses of variables\n" << endl;

  int a = 10;
  double b = 3.14;
  char c = 'A';

  cout << "Variable addresses:" << endl;
  cout << "  int a = " << a << " at address " << &a << endl;
  cout << "  double b = " << b << " at address " << &b << endl;
  cout << "  char c = " << c << " at address " << (void *)&c << endl;

  cout << "\nNote: Addresses are in hexadecimal" << endl;
  cout << "Each variable has unique memory location" << endl;
}

// ============== EXAMPLE 3: DEREFERENCE OPERATOR (*) ==============
void example3_dereference() {
  cout << "\n============== EXAMPLE 3: DEREFERENCE OPERATOR (*) =============="
       << endl;
  cout << "Accessing and modifying values through pointers\n" << endl;

  int number = 100;
  int *ptr = &number;

  cout << "Original value: " << number << endl;
  cout << "Value via pointer: " << *ptr << endl;

  // Modify through pointer
  *ptr = 200;

  cout << "\nAfter *ptr = 200:" << endl;
  cout << "  number = " << number << endl;
  cout << "  *ptr = " << *ptr << endl;

  cout << "\nModifying *ptr changes the original variable!" << endl;
}

// ============== EXAMPLE 4: POINTER INITIALIZATION ==============
void example4_pointer_initialization() {
  cout << "\n============== EXAMPLE 4: POINTER INITIALIZATION =============="
       << endl;
  cout << "Different ways to initialize pointers\n" << endl;

  int value = 50;

  // Method 1: Declare then assign
  int *ptr1;
  ptr1 = &value;

  // Method 2: Initialize at declaration
  int *ptr2 = &value;

  // Method 3: Initialize to nullptr
  int *ptr3 = nullptr;

  cout << "ptr1 points to: " << *ptr1 << endl;
  cout << "ptr2 points to: " << *ptr2 << endl;
  cout << "ptr3 is: " << (ptr3 == nullptr ? "nullptr" : "valid") << endl;

  // Now point ptr3 to value
  ptr3 = &value;
  cout << "\nAfter ptr3 = &value:" << endl;
  cout << "ptr3 points to: " << *ptr3 << endl;
}

// ============== EXAMPLE 5: NULL POINTERS AND NULLPTR ==============
void example5_null_pointers() {
  cout << "\n============== EXAMPLE 5: NULL POINTERS AND NULLPTR =============="
       << endl;
  cout << "Safe pointer initialization\n" << endl;

  int *ptr1 = nullptr; // Modern C++ (C++11)
  int *ptr2 = NULL;    // Old C style
  int *ptr3 = 0;       // Also old style

  cout << "Checking if pointers are null:" << endl;
  cout << "  ptr1 == nullptr: " << (ptr1 == nullptr ? "true" : "false") << endl;
  cout << "  ptr2 == nullptr: " << (ptr2 == nullptr ? "true" : "false") << endl;
  cout << "  ptr3 == nullptr: " << (ptr3 == nullptr ? "true" : "false") << endl;

  // Always check before dereferencing!
  if (ptr1 != nullptr) {
    cout << "ptr1 value: " << *ptr1 << endl;
  } else {
    cout << "\nptr1 is null, cannot dereference!" << endl;
  }

  cout << "\nBest Practice: Use nullptr (C++11 and later)" << endl;
}

// ============== EXAMPLE 6: POINTER ARITHMETIC ==============
void example6_pointer_arithmetic() {
  cout << "\n============== EXAMPLE 6: POINTER ARITHMETIC =============="
       << endl;
  cout << "Moving pointers through memory\n" << endl;

  int arr[] = {10, 20, 30, 40, 50};
  int *ptr = arr; // Points to first element

  cout << "Array: ";
  for (int i = 0; i < 5; i++)
    cout << arr[i] << " ";
  cout << endl << endl;

  cout << "Using pointer arithmetic:" << endl;
  cout << "  *ptr = " << *ptr << " (element 0)" << endl;

  ptr++; // Move to next element
  cout << "  After ptr++, *ptr = " << *ptr << " (element 1)" << endl;

  ptr += 2; // Move forward 2 elements
  cout << "  After ptr += 2, *ptr = " << *ptr << " (element 3)" << endl;

  ptr--; // Move back one element
  cout << "  After ptr--, *ptr = " << *ptr << " (element 2)" << endl;

  cout << "\nPointer arithmetic moves by sizeof(type) bytes" << endl;
}

// ============== EXAMPLE 7: POINTERS AND ARRAYS ==============
void example7_pointers_arrays() {
  cout << "\n============== EXAMPLE 7: POINTERS AND ARRAYS =============="
       << endl;
  cout << "Arrays are closely related to pointers\n" << endl;

  int numbers[] = {1, 2, 3, 4, 5};
  int *ptr = numbers; // Array name is pointer to first element

  cout << "Array name as pointer:" << endl;
  cout << "  numbers = " << numbers << endl;
  cout << "  &numbers[0] = " << &numbers[0] << endl;
  cout << "  (Same address!)" << endl;

  cout << "\nAccessing elements:" << endl;
  for (int i = 0; i < 5; i++) {
    cout << "  numbers[" << i << "] = " << numbers[i];
    cout << " = *(numbers + " << i << ") = " << *(numbers + i);
    cout << " = ptr[" << i << "] = " << ptr[i] << endl;
  }

  cout << "\nArray notation and pointer notation are interchangeable!" << endl;
}

// ============== EXAMPLE 8: POINTER DEREFERENCING IN DETAIL ==============
void example8_dereference_details() {
  cout << "\n============== EXAMPLE 8: DEREFERENCING IN DETAIL =============="
       << endl;

  int x = 100;
  int *p = &x;

  cout << "int x = 100;" << endl;
  cout << "int* p = &x;" << endl << endl;

  cout << "Expression | Result | Meaning" << endl;
  cout << "-----------|--------|--------" << endl;
  cout << "x          | " << x << "    | Value of x" << endl;
  cout << "&x         | " << &x << " | Address of x" << endl;
  cout << "p          | " << p << " | Value of p (address)" << endl;
  cout << "*p         | " << *p << "    | Value at address p" << endl;
  cout << "&p         | " << &p << " | Address of p itself" << endl;

  cout << "\n*p and x refer to the same value!" << endl;
}

// ============== EXAMPLE 9: MODIFYING VALUES THROUGH POINTERS ==============
void example9_modifying_values() {
  cout << "\n============== EXAMPLE 9: MODIFYING VALUES THROUGH POINTERS "
          "=============="
       << endl;

  int balance = 1000;
  int *account = &balance;

  cout << "Initial balance: $" << balance << endl;

  // Deposit via pointer
  *account += 500;
  cout << "After deposit (*account += 500): $" << balance << endl;

  // Withdrawal via pointer
  *account -= 200;
  cout << "After withdrawal (*account -= 200): $" << balance << endl;

  cout << "\nChanges through pointer affect original variable!" << endl;
}

// ============== EXAMPLE 10: SWAPPING USING POINTERS ==============
void swap_with_pointers(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void example10_swap_pointers() {
  cout << "\n============== EXAMPLE 10: SWAPPING USING POINTERS =============="
       << endl;

  int x = 10, y = 20;

  cout << "Before swap: x = " << x << ", y = " << y << endl;

  swap_with_pointers(&x, &y);

  cout << "After swap: x = " << x << ", y = " << y << endl;

  cout << "\nPass addresses to function to modify originals" << endl;
}

// ============== EXAMPLE 11: POINTER TO POINTER ==============
void example11_pointer_to_pointer() {
  cout << "\n============== EXAMPLE 11: POINTER TO POINTER =============="
       << endl;
  cout << "Pointers can point to other pointers\n" << endl;

  int value = 42;
  int *ptr = &value;
  int **pptr = &ptr; // Pointer to pointer

  cout << "value = " << value << endl;
  cout << "*ptr = " << *ptr << endl;
  cout << "**pptr = " << **pptr << endl;

  cout << "\nAddresses:" << endl;
  cout << "  &value = " << &value << endl;
  cout << "  ptr = " << ptr << " (points to value)" << endl;
  cout << "  &ptr = " << &ptr << endl;
  cout << "  pptr = " << pptr << " (points to ptr)" << endl;

  cout << "\n** = double dereference" << endl;
}

// ============== EXAMPLE 12: ARRAY TRAVERSAL WITH POINTERS ==============
void example12_array_traversal() {
  cout << "\n============== EXAMPLE 12: ARRAY TRAVERSAL WITH POINTERS "
          "=============="
       << endl;

  int scores[] = {85, 92, 78, 95, 88};
  int size = 5;

  cout << "Method 1: Index notation" << endl;
  for (int i = 0; i < size; i++) {
    cout << "  scores[" << i << "] = " << scores[i] << endl;
  }

  cout << "\nMethod 2: Pointer arithmetic" << endl;
  for (int *p = scores; p < scores + size; p++) {
    cout << "  *p = " << *p << " at " << p << endl;
  }

  cout << "\nBoth methods access same data!" << endl;
}

// ============== EXAMPLE 13: CONST POINTERS ==============
void example13_const_pointers() {
  cout << "\n============== EXAMPLE 13: CONST POINTERS ==============" << endl;
  cout << "Different ways to use const with pointers\n" << endl;

  int a = 10, b = 20;

  // Pointer to const (can't change value)
  const int *ptr1 = &a;
  cout << "1. const int* ptr1 (pointer to const):" << endl;
  cout << "   *ptr1 = " << *ptr1 << endl;
  // *ptr1 = 30;  // ERROR! Can't modify value
  ptr1 = &b; // OK! Can change pointer
  cout << "   After ptr1 = &b: *ptr1 = " << *ptr1 << endl;

  // Const pointer (can't change pointer)
  int *const ptr2 = &a;
  cout << "\n2. int* const ptr2 (const pointer):" << endl;
  cout << "   *ptr2 = " << *ptr2 << endl;
  *ptr2 = 30; // OK! Can modify value
  // ptr2 = &b;   // ERROR! Can't change pointer
  cout << "   After *ptr2 = 30: a = " << a << endl;

  // Const pointer to const
  const int *const ptr3 = &a;
  cout << "\n3. const int* const ptr3 (const pointer to const):" << endl;
  cout << "   *ptr3 = " << *ptr3 << endl;
  // *ptr3 = 40;  // ERROR! Can't modify value
  // ptr3 = &b;   // ERROR! Can't change pointer

  cout << "\nRead right-to-left for const declarations!" << endl;
}

// ============== EXAMPLE 14: POINTER SIZE ==============
void example14_pointer_size() {
  cout << "\n============== EXAMPLE 14: POINTER SIZE ==============" << endl;
  cout << "All pointers have same size (on same architecture)\n" << endl;

  int *p1;
  double *p2;
  char *p3;
  void *p4;

  cout << "Pointer sizes (in bytes):" << endl;
  cout << "  sizeof(int*) = " << sizeof(p1) << endl;
  cout << "  sizeof(double*) = " << sizeof(p2) << endl;
  cout << "  sizeof(char*) = " << sizeof(p3) << endl;
  cout << "  sizeof(void*) = " << sizeof(p4) << endl;

  cout << "\nVariable sizes (in bytes):" << endl;
  cout << "  sizeof(int) = " << sizeof(int) << endl;
  cout << "  sizeof(double) = " << sizeof(double) << endl;
  cout << "  sizeof(char) = " << sizeof(char) << endl;

  cout << "\nPointer size depends on architecture (32-bit vs 64-bit)" << endl;
}

// ============== EXAMPLE 15: COMMON POINTER ERRORS ==============
void example15_common_errors() {
  cout << "\n============== EXAMPLE 15: COMMON POINTER ERRORS =============="
       << endl;
  cout << "Understanding pointer pitfalls\n" << endl;

  // 1. Uninitialized pointer (dangerous!)
  cout << "1. Uninitialized pointer:" << endl;
  int *bad_ptr; // Contains garbage address
  cout << "   int* bad_ptr; // DANGEROUS! Points to random memory" << endl;
  // cout << *bad_ptr;  // CRASH! Undefined behavior

  // 2. Null pointer dereference
  cout << "\n2. Null pointer dereference:" << endl;
  int *null_ptr = nullptr;
  cout << "   int* null_ptr = nullptr;" << endl;
  // cout << *null_ptr;  // CRASH! Segmentation fault

  // Safe way:
  if (null_ptr != nullptr) {
    cout << "   Safe: " << *null_ptr << endl;
  } else {
    cout << "   Checked: pointer is null, not dereferencing" << endl;
  }

  // 3. Dangling pointer (pointing to freed/out-of-scope memory)
  cout << "\n3. Dangling pointer:" << endl;
  int *dangling_ptr;
  {
    int temp = 100;
    dangling_ptr = &temp;
    cout << "   Inside scope: *dangling_ptr = " << *dangling_ptr << endl;
  } // temp destroyed here!
  cout << "   Outside scope: dangling_ptr now invalid!" << endl;
  // cout << *dangling_ptr;  // UNDEFINED BEHAVIOR!

  cout << "\nAlways initialize pointers to nullptr!" << endl;
  cout << "Always check before dereferencing!" << endl;
}

int main() {
  cout << "\n======================================================" << endl;
  cout << "              POINTER BASICS TUTORIAL                " << endl;
  cout << "======================================================" << endl;

  example1_pointer_basics();
  example2_address_of();
  example3_dereference();
  example4_pointer_initialization();
  example5_null_pointers();
  example6_pointer_arithmetic();
  example7_pointers_arrays();
  example8_dereference_details();
  example9_modifying_values();
  example10_swap_pointers();
  example11_pointer_to_pointer();
  example12_array_traversal();
  example13_const_pointers();
  example14_pointer_size();
  example15_common_errors();

  cout << "\n======================================================" << endl;
  cout << "                   KEY TAKEAWAYS                      " << endl;
  cout << "======================================================" << endl;
  cout << "✓ Pointers store memory addresses" << endl;
  cout << "✓ & gets address, * dereferences (gets value)" << endl;
  cout << "✓ Always initialize pointers (use nullptr)" << endl;
  cout << "✓ Check for nullptr before dereferencing" << endl;
  cout << "✓ Array name is pointer to first element" << endl;
  cout << "✓ Pointer arithmetic moves by sizeof(type)" << endl;
  cout << "✓ Use const for safety (const int*, int* const)" << endl;
  cout << "✓ All pointers same size (platform-dependent)" << endl;
  cout << "✓ Avoid: uninitialized, null deref, dangling pointers" << endl;
  cout << "======================================================\n" << endl;

  return 0;
}

/*
 * =====================================================================
 * COMMON MISTAKES TO AVOID
 * =====================================================================
 *
 * 1. UNINITIALIZED POINTERS
 *    ✗ BAD: int* ptr;  // Points to random memory!
 *    ✓ GOOD: int* ptr = nullptr;
 *
 * 2. DEREFERENCING NULL POINTER
 *    ✗ BAD: int* ptr = nullptr; cout << *ptr;  // CRASH!
 *    ✓ GOOD: if (ptr != nullptr) cout << *ptr;
 *
 * 3. FORGETTING & WHEN ASSIGNING ADDRESS
 *    ✗ BAD: int* ptr = x;  // Wrong! x is value, not address
 *    ✓ GOOD: int* ptr = &x;
 *
 * 4. CONFUSING * IN DECLARATION VS DEREFERENCE
 *    int* ptr;    // * means "pointer to int" (declaration)
 *    *ptr = 10;   // * means "value at" (dereference)
 *
 * 5. DANGLING POINTERS
 *    ✗ BAD: { int x = 5; ptr = &x; } *ptr = 10;  // x destroyed!
 *    ✓ GOOD: Ensure pointed-to object is still valid
 *
 * 6. MEMORY LEAK (with dynamic allocation)
 *    ✗ BAD: int* p = new int(5); p = nullptr;  // Lost memory!
 *    ✓ GOOD: delete p; p = nullptr;
 *
 * 7. ARRAY BOUNDS WITH POINTERS
 *    ✗ BAD: int arr[5]; *(arr + 10) = 0;  // Out of bounds!
 *    ✓ GOOD: Stay within array bounds
 *
 * 8. COMPARING POINTERS INCORRECTLY
 *    ✗ BAD: if (ptr == 0) ...  // Old style
 *    ✓ GOOD: if (ptr == nullptr) ...
 *
 * =====================================================================
 * POINTER SAFETY CHECKLIST
 * =====================================================================
 *
 * ☐ Initialize all pointers (to nullptr or valid address)
 * ☐ Check for nullptr before dereferencing
 * ☐ Don't dereference uninitialized pointers
 * ☐ Don't create dangling pointers
 * ☐ Match new/delete (covered in dynamic memory)
 * ☐ Use const when pointer shouldn't modify data
 * ☐ Don't return pointers to local variables
 * ☐ Be careful with pointer arithmetic (stay in bounds)
 *
 * =====================================================================
 * PRACTICE EXERCISES
 * =====================================================================
 *
 * 1. Declare pointer to int, assign address, print value
 * 2. Write function that swaps two integers using pointers
 * 3. Find sum of array using pointer arithmetic
 * 4. Find max element in array using pointers
 * 5. Reverse array in-place using two pointers
 * 6. Copy one array to another using pointers
 * 7. Count occurrences of value in array using pointers
 * 8. Implement pointer-based string length function
 * 9. Create function that returns min and max via pointers
 * 10. Practice const pointer variations
 * 11. Find element in array using pointer traversal
 * 12. Implement pointer-based array rotation
 * 13. Use pointer arithmetic to access 2D array
 * 14. Write function to merge two arrays using pointers
 * 15. Practice pointer to pointer operations
 *
 * =====================================================================
 * MEMORY VISUALIZATION
 * =====================================================================
 *
 * Example: int x = 42; int* ptr = &x;
 *
 * Memory Layout:
 * ┌──────────┬────────────┬───────┐
 * │ Address  │ Variable   │ Value │
 * ├──────────┼────────────┼───────┤
 * │ 0x1000   │ x          │ 42    │
 * │ 0x2000   │ ptr        │ 0x1000│
 * └──────────┴────────────┴───────┘
 *
 * Expressions:
 *   x      → 42 (value of x)
 *   &x     → 0x1000 (address of x)
 *   ptr    → 0x1000 (value of ptr = address)
 *   *ptr   → 42 (value at address 0x1000)
 *   &ptr   → 0x2000 (address of ptr)
 *
 * =====================================================================
 * POINTER DECLARATION STYLES
 * =====================================================================
 *
 * All equivalent:
 *   int* ptr;    // Pointer to int (preferred by many)
 *   int *ptr;    // Also correct
 *   int * ptr;   // Less common
 *
 * Multiple declarations:
 *   int* p1, p2;     // p1 is pointer, p2 is int! (confusing)
 *   int *p1, *p2;    // Both are pointers (clearer)
 *   int* p1; int* p2; // Safest (separate lines)
 *
 * =====================================================================
 * COMPILATION AND EXECUTION
 * =====================================================================
 *
 * To compile and run:
 *   g++ -std=c++17 1_pointers_basics.cpp -o pointers
 *   ./pointers
 *
 * With warnings:
 *   g++ -std=c++17 -Wall -Wextra 1_pointers_basics.cpp -o pointers
 *
 * =====================================================================
 */
