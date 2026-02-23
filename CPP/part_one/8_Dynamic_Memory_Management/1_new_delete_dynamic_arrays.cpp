#include <cstring>
#include <iostream>
using namespace std;

/*
 * =====================================================================
 * TOPIC 8.1: DYNAMIC MEMORY MANAGEMENT - NEW, DELETE, DYNAMIC ARRAYS
 * =====================================================================
 *
 * WHAT IS DYNAMIC MEMORY MANAGEMENT?
 * Dynamic memory allocation allows programs to request memory at runtime
 * from the heap. Unlike static/automatic storage (stack), heap memory
 * persists until explicitly deallocated, giving you control over lifetime.
 *
 * KEY CONCEPTS COVERED:
 * 1. Stack vs Heap memory
 * 2. new operator (single object & arrays)
 * 3. delete operator (single object & arrays)
 * 4. Dynamic memory allocation and deallocation
 * 5. Memory leaks and how to detect them
 * 6. Dangling pointers and null pointers
 * 7. Dynamic arrays (vs static arrays)
 * 8. 2D dynamic arrays
 * 9. Memory allocation failures
 * 10. Best practices for manual memory management
 * 11. RAII principle introduction
 * 12. Common pitfalls and debugging
 *
 * =====================================================================
 * MEMORY LAYOUT
 * =====================================================================
 *
 * PROGRAM MEMORY SECTIONS:
 *
 * High Address  ┌─────────────────┐
 *               │  Command Line   │  (Arguments & Environment)
 *               ├─────────────────┤
 *               │     STACK       │  ↓ Grows downward
 *               │  (Automatic)    │    Local variables, function calls
 *               ├─────────────────┤
 *               │       ↓         │
 *               │                 │
 *               │       ↑         │
 *               ├─────────────────┤
 *               │     HEAP        │  ↑ Grows upward
 *               │   (Dynamic)     │    new/delete, malloc/free
 *               ├─────────────────┤
 *               │  Uninitialized  │  (BSS segment)
 *               │      Data       │    Global/static uninitialized
 *               ├─────────────────┤
 *               │   Initialized   │  (Data segment)
 *               │      Data       │    Global/static initialized
 *               ├─────────────────┤
 * Low Address   │      Code       │  (Text segment)
 *               │   (Read-only)   │    Program instructions
 *               └─────────────────┘
 *
 * =====================================================================
 * STACK vs HEAP
 * =====================================================================
 *
 * STACK (Automatic Storage):
 *   - Fast allocation/deallocation
 *   - Limited size (typically 1-8 MB)
 *   - Automatic cleanup (LIFO)
 *   - Local variables, function parameters
 *   - Compiler-managed
 *
 * HEAP (Dynamic Storage):
 *   - Slower allocation/deallocation
 *   - Large size (limited by RAM)
 *   - Manual cleanup required
 *   - Objects persist beyond scope
 *   - Programmer-managed
 *
 * =====================================================================
 * NEW AND DELETE OPERATORS
 * =====================================================================
 *
 * SYNTAX:
 *   Type* ptr = new Type;          // Single object
 *   Type* arr = new Type[size];    // Array of objects
 *
 *   delete ptr;                     // Delete single object
 *   delete[] arr;                   // Delete array
 *
 * IMPORTANT:
 *   - Always match new with delete
 *   - Always match new[] with delete[]
 *   - Mismatching causes undefined behavior
 *   - Set pointers to nullptr after delete
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: STACK VS HEAP MEMORY ==============
void example1_stack_vs_heap() {
  cout << "\n============== EXAMPLE 1: STACK VS HEAP MEMORY =============="
       << endl;
  cout << "Understanding where variables are stored\n" << endl;

  // Stack allocation (automatic)
  int stack_var = 42;
  int stack_array[5] = {1, 2, 3, 4, 5};

  cout << "STACK ALLOCATION:" << endl;
  cout << "stack_var address: " << &stack_var << endl;
  cout << "stack_array address: " << stack_array << endl;
  cout << "Value: " << stack_var << endl;

  // Heap allocation (dynamic)
  int *heap_var = new int(42);
  int *heap_array = new int[5]{1, 2, 3, 4, 5};

  cout << "\nHEAP ALLOCATION:" << endl;
  cout << "heap_var address: " << heap_var << endl;
  cout << "heap_array address: " << heap_array << endl;
  cout << "Value: " << *heap_var << endl;

  cout << "\nKEY DIFFERENCES:" << endl;
  cout << "1. Stack: Automatically cleaned up at end of scope" << endl;
  cout << "2. Heap: Must manually delete to avoid memory leak" << endl;
  cout << "3. Stack: Fast, limited size" << endl;
  cout << "4. Heap: Slower, large size available" << endl;

  // Clean up heap memory
  delete heap_var;
  delete[] heap_array;

  cout << "\nHeap memory cleaned up with delete/delete[]" << endl;
}

// ============== EXAMPLE 2: NEW OPERATOR - SINGLE OBJECTS ==============
void example2_new_single_object() {
  cout << "\n============== EXAMPLE 2: NEW OPERATOR (SINGLE OBJECTS) "
          "=============="
       << endl;
  cout << "Allocating individual objects on heap\n" << endl;

  // Allocate uninitialized int
  int *p1 = new int;
  cout << "Uninitialized int: " << *p1 << " (garbage value)" << endl;
  delete p1;

  // Allocate initialized int
  int *p2 = new int(100);
  cout << "Initialized int: " << *p2 << endl;
  delete p2;

  // Allocate with uniform initialization (C++11)
  int *p3 = new int{200};
  cout << "Uniform init int: " << *p3 << endl;
  delete p3;

  // Allocate double
  double *p4 = new double(3.14159);
  cout << "Double: " << *p4 << endl;
  delete p4;

  // Allocate char
  char *p5 = new char('A');
  cout << "Char: " << *p5 << endl;
  delete p5;

  cout << "\nSyntax: Type* ptr = new Type(value);" << endl;
  cout << "Don't forget: delete ptr;" << endl;
}

// ============== EXAMPLE 3: DELETE OPERATOR ==============
void example3_delete_operator() {
  cout << "\n============== EXAMPLE 3: DELETE OPERATOR ==============" << endl;
  cout << "Properly deallocating memory\n" << endl;

  int *ptr = new int(42);
  cout << "Allocated int: " << *ptr << endl;
  cout << "Address: " << ptr << endl;

  delete ptr;
  cout << "\nAfter delete:" << endl;
  cout << "Pointer still has address: " << ptr << " (dangling!)" << endl;
  // cout << "Value: " << *ptr << endl;  // DANGEROUS! Undefined behavior

  // Best practice: set to nullptr after delete
  ptr = nullptr;
  cout << "After setting to nullptr: " << ptr << endl;

  // Safe to delete nullptr (does nothing)
  delete ptr; // OK, no effect
  cout << "Deleting nullptr is safe" << endl;

  cout << "\nBEST PRACTICES:" << endl;
  cout << "1. Always delete dynamically allocated memory" << endl;
  cout << "2. Set pointer to nullptr after delete" << endl;
  cout << "3. Never use pointer after delete (dangling pointer!)" << endl;
  cout << "4. Deleting nullptr is safe and does nothing" << endl;
}

// ============== EXAMPLE 4: DYNAMIC ARRAYS ==============
void example4_dynamic_arrays() {
  cout << "\n============== EXAMPLE 4: DYNAMIC ARRAYS ==============" << endl;
  cout << "Allocating arrays at runtime\n" << endl;

  int size = 5;

  // Allocate array
  int *arr = new int[size];

  // Initialize array
  for (int i = 0; i < size; i++) {
    arr[i] = (i + 1) * 10;
  }

  cout << "Dynamic array: ";
  for (int i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  // Clean up - MUST use delete[]
  delete[] arr;

  // Allocate with initialization (C++11)
  int *arr2 = new int[5]{1, 2, 3, 4, 5};
  cout << "\nInitialized array: ";
  for (int i = 0; i < 5; i++) {
    cout << arr2[i] << " ";
  }
  cout << endl;
  delete[] arr2;

  // Zero-initialized array
  int *arr3 = new int[5]();
  cout << "\nZero-initialized array: ";
  for (int i = 0; i < 5; i++) {
    cout << arr3[i] << " ";
  }
  cout << endl;
  delete[] arr3;

  cout << "\nCRITICAL: Use delete[] for arrays, not delete!" << endl;
  cout << "Syntax: delete[] arrayPtr;" << endl;
}

// ============== EXAMPLE 5: MEMORY LEAK DEMONSTRATION ==============
void example5_memory_leak() {
  cout << "\n============== EXAMPLE 5: MEMORY LEAKS ==============" << endl;
  cout << "What happens when you forget to delete\n" << endl;

  cout << "MEMORY LEAK EXAMPLE (commented out):" << endl;
  cout << "void bad_function() {" << endl;
  cout << "    int* ptr = new int(100);" << endl;
  cout << "    // Oops! Forgot to delete" << endl;
  cout << "    // Memory is leaked!" << endl;
  cout << "}" << endl;

  /*
  // DON'T DO THIS! (Memory leak)
  void leak_memory() {
      int* ptr = new int(100);
      // Function ends, ptr destroyed, but memory not freed!
  }
  */

  // Correct way
  auto good_function = []() {
    int *ptr = new int(100);
    cout << "\nAllocated: " << *ptr << endl;
    delete ptr;
    cout << "Properly deleted!" << endl;
  };

  good_function();

  cout << "\nMEMORY LEAK CAUSES:" << endl;
  cout << "1. Forgetting to call delete" << endl;
  cout << "2. Exception thrown before delete" << endl;
  cout << "3. Early return from function" << endl;
  cout << "4. Reassigning pointer without deleting" << endl;

  // Example of reassignment leak
  int *ptr = new int(10);
  cout << "\nOriginal allocation: " << *ptr << endl;
  // ptr = new int(20);  // LEAK! Lost reference to first allocation
  delete ptr; // This only deletes second allocation
  ptr = new int(20);
  cout << "New allocation: " << *ptr << endl;
  delete ptr; // Proper cleanup

  cout << "\nPREVENTION: Use smart pointers (covered in next file)!" << endl;
}

// ============== EXAMPLE 6: DANGLING POINTERS ==============
void example6_dangling_pointers() {
  cout << "\n============== EXAMPLE 6: DANGLING POINTERS =============="
       << endl;
  cout << "Avoiding pointers to deleted memory\n" << endl;

  int *ptr1 = new int(42);
  int *ptr2 = ptr1; // ptr2 points to same memory

  cout << "ptr1: " << *ptr1 << endl;
  cout << "ptr2: " << *ptr2 << endl;

  delete ptr1; // Memory freed
  ptr1 = nullptr;

  cout << "\nAfter deleting ptr1:" << endl;
  cout << "ptr1 is nullptr: " << (ptr1 == nullptr ? "yes" : "no") << endl;
  cout << "ptr2 is dangling: points to freed memory!" << endl;
  // cout << *ptr2 << endl;  // UNDEFINED BEHAVIOR!

  // Fix: set all pointers to nullptr
  ptr2 = nullptr;
  cout << "Set ptr2 to nullptr - now safe" << endl;

  cout << "\nDANGLING POINTER SCENARIOS:" << endl;
  cout << "1. Deleting memory but keeping pointer" << endl;
  cout << "2. Multiple pointers to same memory" << endl;
  cout << "3. Returning pointer to local variable" << endl;
  cout << "4. Using pointer after delete" << endl;
}

// ============== EXAMPLE 7: 2D DYNAMIC ARRAYS ==============
void example7_2d_dynamic_arrays() {
  cout << "\n============== EXAMPLE 7: 2D DYNAMIC ARRAYS =============="
       << endl;
  cout << "Creating matrices with dynamic allocation\n" << endl;

  int rows = 3, cols = 4;

  // Allocate array of pointers
  int **matrix = new int *[rows];

  // Allocate each row
  for (int i = 0; i < rows; i++) {
    matrix[i] = new int[cols];
  }

  // Initialize matrix
  int value = 1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = value++;
    }
  }

  // Display matrix
  cout << "Dynamic 2D array (" << rows << "x" << cols << "):" << endl;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << matrix[i][j] << "\t";
    }
    cout << endl;
  }

  // IMPORTANT: Delete in reverse order
  for (int i = 0; i < rows; i++) {
    delete[] matrix[i]; // Delete each row
  }
  delete[] matrix; // Delete array of pointers

  cout << "\nDeletion order:" << endl;
  cout << "1. Delete each row: delete[] matrix[i]" << endl;
  cout << "2. Delete row pointers: delete[] matrix" << endl;
  cout << "\nNote: Consider using vector<vector<int>> for easier management!"
       << endl;
}

// ============== EXAMPLE 8: ALLOCATION FAILURES ==============
void example8_allocation_failures() {
  cout << "\n============== EXAMPLE 8: HANDLING ALLOCATION FAILURES "
          "=============="
       << endl;
  cout << "What happens when allocation fails\n" << endl;

  cout << "DEFAULT BEHAVIOR: new throws std::bad_alloc exception" << endl;

  try {
    // Try to allocate huge amount (likely to fail on some systems)
    // long long huge = 1000000000000LL;
    // int* ptr = new int[huge];  // May throw bad_alloc

    cout << "Normal allocation:" << endl;
    int *ptr = new int(42);
    cout << "Success! Value: " << *ptr << endl;
    delete ptr;

  } catch (const bad_alloc &e) {
    cout << "Allocation failed: " << e.what() << endl;
  }

  // nothrow version - returns nullptr instead of throwing
  cout << "\nNOTHROW VERSION: new (nothrow)" << endl;
  int *ptr = new (nothrow) int(100);

  if (ptr != nullptr) {
    cout << "Allocation succeeded: " << *ptr << endl;
    delete ptr;
  } else {
    cout << "Allocation failed, ptr is nullptr" << endl;
  }

  cout << "\nBEST PRACTICE:" << endl;
  cout << "1. Use try-catch for critical allocations" << endl;
  cout << "2. Or use new(nothrow) and check for nullptr" << endl;
  cout << "3. Consider using smart pointers (safer!)" << endl;
}

// ============== EXAMPLE 9: DYNAMIC C-STRING ==============
void example9_dynamic_cstring() {
  cout << "\n============== EXAMPLE 9: DYNAMIC C-STRINGS =============="
       << endl;
  cout << "Working with dynamically allocated character arrays\n" << endl;

  // Allocate string
  const char *source = "Hello, World!";
  int length = strlen(source);

  char *str = new char[length + 1]; // +1 for null terminator
  strcpy(str, source);

  cout << "Dynamic string: " << str << endl;
  cout << "Length: " << length << endl;

  // Modify string
  str[0] = 'h';
  cout << "Modified: " << str << endl;

  delete[] str;

  // Concatenation example
  const char *str1 = "Hello";
  const char *str2 = " World";

  char *result = new char[strlen(str1) + strlen(str2) + 1];
  strcpy(result, str1);
  strcat(result, str2);

  cout << "\nConcatenated: " << result << endl;
  delete[] result;

  cout << "\nNOTE: Prefer std::string over char* for easier management!"
       << endl;
}

// ============== EXAMPLE 10: RESIZING DYNAMIC ARRAYS ==============
void example10_resizing_arrays() {
  cout << "\n============== EXAMPLE 10: RESIZING DYNAMIC ARRAYS =============="
       << endl;
  cout << "Growing arrays (manual approach)\n" << endl;

  int old_size = 5;
  int *old_array = new int[old_size]{1, 2, 3, 4, 5};

  cout << "Original array: ";
  for (int i = 0; i < old_size; i++) {
    cout << old_array[i] << " ";
  }
  cout << endl;

  // Resize to larger array
  int new_size = 10;
  int *new_array = new int[new_size];

  // Copy old data
  for (int i = 0; i < old_size; i++) {
    new_array[i] = old_array[i];
  }

  // Initialize new elements
  for (int i = old_size; i < new_size; i++) {
    new_array[i] = 0;
  }

  // Delete old array
  delete[] old_array;

  cout << "Resized array: ";
  for (int i = 0; i < new_size; i++) {
    cout << new_array[i] << " ";
  }
  cout << endl;

  delete[] new_array;

  cout << "\nPROBLEMS WITH MANUAL RESIZING:" << endl;
  cout << "1. Need to allocate new array" << endl;
  cout << "2. Copy all elements" << endl;
  cout << "3. Delete old array" << endl;
  cout << "4. Update pointer" << endl;
  cout << "\nSOLUTION: Use std::vector (automatic resizing)!" << endl;
}

// ============== EXAMPLE 11: RAII PRINCIPLE INTRODUCTION ==============
class IntArray {
private:
  int *data;
  int size;

public:
  IntArray(int s) : size(s) {
    data = new int[size];
    cout << "  IntArray allocated (" << size << " ints)" << endl;
  }

  ~IntArray() {
    delete[] data;
    cout << "  IntArray deallocated" << endl;
  }

  int &operator[](int index) { return data[index]; }

  int getSize() const { return size; }
};

void example11_raii_introduction() {
  cout << "\n============== EXAMPLE 11: RAII PRINCIPLE ==============" << endl;
  cout << "Resource Acquisition Is Initialization\n" << endl;

  cout << "Creating IntArray object:" << endl;
  {
    IntArray arr(5);

    // Use the array
    for (int i = 0; i < arr.getSize(); i++) {
      arr[i] = i * 10;
    }

    cout << "Array contents: ";
    for (int i = 0; i < arr.getSize(); i++) {
      cout << arr[i] << " ";
    }
    cout << endl;

    cout << "End of scope - destructor will be called automatically" << endl;
  } // Destructor called here!

  cout << "\nRAII PRINCIPLES:" << endl;
  cout << "1. Acquire resource in constructor" << endl;
  cout << "2. Release resource in destructor" << endl;
  cout << "3. Automatic cleanup when object goes out of scope" << endl;
  cout << "4. Exception-safe (destructor always called)" << endl;
  cout << "\nThis is the foundation of smart pointers!" << endl;
}

// ============== EXAMPLE 12: COMMON MISTAKES ==============
void example12_common_mistakes() {
  cout << "\n============== EXAMPLE 12: COMMON MISTAKES ==============" << endl;
  cout << "Avoiding typical dynamic memory errors\n" << endl;

  cout << "MISTAKE 1: Double delete" << endl;
  {
    int *ptr = new int(10);
    delete ptr;
    // delete ptr;  // ERROR! Double delete - undefined behavior
    ptr = nullptr; // Fix: set to nullptr
    delete ptr;    // OK - deleting nullptr is safe
    cout << "  Fixed by setting to nullptr after delete" << endl;
  }

  cout << "\nMISTAKE 2: delete vs delete[] mismatch" << endl;
  {
    int *arr = new int[5];
    // delete arr;  // ERROR! Should be delete[]
    delete[] arr; // Correct
    cout << "  Use delete[] for arrays" << endl;
  }

  cout << "\nMISTAKE 3: Memory leak from exception" << endl;
  cout << "  void risky() {" << endl;
  cout << "    int* p = new int(10);" << endl;
  cout << "    throw exception();  // LEAK! p never deleted" << endl;
  cout << "  }" << endl;
  cout << "  Fix: Use smart pointers or RAII" << endl;

  cout << "\nMISTAKE 4: Returning pointer to local variable" << endl;
  cout << "  int* bad() {" << endl;
  cout << "    int x = 10;" << endl;
  cout << "    return &x;  // DANGLING! x destroyed" << endl;
  cout << "  }" << endl;
  cout << "  Fix: Return by value or use dynamic allocation" << endl;

  cout << "\nMISTAKE 5: Not checking allocation result (with nothrow)" << endl;
  {
    int *ptr = new (nothrow) int(42);
    // Using ptr without checking  // ERROR if allocation failed!
    if (ptr != nullptr) {
      cout << "  Always check: " << *ptr << endl;
      delete ptr;
    }
  }

  cout << "\nPREVENTION: Use smart pointers (next file)!" << endl;
}

/*
 * =====================================================================
 * KEY CONCEPTS SUMMARY
 * =====================================================================
 *
 * 1. MEMORY ALLOCATION:
 *    - new Type: Allocate single object
 *    - new Type[size]: Allocate array
 *    - Returns pointer to allocated memory
 *    - Can throw bad_alloc on failure
 *
 * 2. MEMORY DEALLOCATION:
 *    - delete ptr: Deallocate single object
 *    - delete[] arr: Deallocate array
 *    - Set pointer to nullptr after delete
 *    - Deleting nullptr is safe
 *
 * 3. STACK VS HEAP:
 *    - Stack: Fast, automatic, limited size
 *    - Heap: Slower, manual, large size
 *    - Stack: Function scope
 *    - Heap: Program scope (until deleted)
 *
 * 4. MEMORY LEAKS:
 *    - Occur when allocated memory not freed
 *    - Lost pointer references
 *    - Exceptions before delete
 *    - Detection: Valgrind, AddressSanitizer
 *
 * 5. DANGLING POINTERS:
 *    - Pointer to freed memory
 *    - Using after delete
 *    - Multiple pointers to same memory
 *    - Prevention: Set to nullptr
 *
 * 6. BEST PRACTICES:
 *    - Always match new with delete
 *    - Always match new[] with delete[]
 *    - Set pointers to nullptr after delete
 *    - Use RAII principle
 *    - Prefer smart pointers (next topic!)
 *    - Check allocation success
 *
 * =====================================================================
 * WHEN TO USE DYNAMIC MEMORY
 * =====================================================================
 *
 * USE DYNAMIC ALLOCATION WHEN:
 *   - Size unknown at compile time
 *   - Size too large for stack
 *   - Lifetime must exceed function scope
 *   - Building data structures (linked lists, trees)
 *   - Implementing containers
 *
 * AVOID DYNAMIC ALLOCATION WHEN:
 *   - Size known at compile time
 *   - Size fits on stack
 *   - Can use std::vector or std::array
 *   - Can pass by reference
 *
 * =====================================================================
 * DEBUGGING TOOLS
 * =====================================================================
 *
 * DETECT MEMORY ERRORS:
 *   1. Valgrind (Linux/Mac): valgrind --leak-check=full ./program
 *   2. AddressSanitizer: g++ -fsanitize=address program.cpp
 *   3. Visual Studio: Memory diagnostics tools
 *   4. Dr. Memory (Windows)
 *
 * COMMON ERRORS DETECTED:
 *   - Memory leaks
 *   - Use after free
 *   - Double free
 *   - Invalid reads/writes
 *   - Buffer overflows
 *
 * =====================================================================
 * COMMON MISTAKES TO AVOID
 * =====================================================================
 *
 * 1. Forgetting to delete (memory leak)
 * 2. Double delete (undefined behavior)
 * 3. Using delete instead of delete[] for arrays
 * 4. Using pointer after delete (dangling pointer)
 * 5. Not setting pointer to nullptr after delete
 * 6. Returning pointer to local variable
 * 7. Memory leak from exceptions
 * 8. Not checking allocation success
 * 9. Shallow copy instead of deep copy
 * 10. Mixing malloc/free with new/delete
 *
 * =====================================================================
 */

int main() {
  cout << "=========================================================" << endl;
  cout << "  DYNAMIC MEMORY MANAGEMENT - NEW, DELETE, DYNAMIC ARRAYS " << endl;
  cout << "=========================================================" << endl;

  example1_stack_vs_heap();
  example2_new_single_object();
  example3_delete_operator();
  example4_dynamic_arrays();
  example5_memory_leak();
  example6_dangling_pointers();
  example7_2d_dynamic_arrays();
  example8_allocation_failures();
  example9_dynamic_cstring();
  example10_resizing_arrays();
  example11_raii_introduction();
  example12_common_mistakes();

  cout << "\n=========================================================" << endl;
  cout << "         PRACTICE EXERCISES" << endl;
  cout << "=========================================================" << endl;
  cout << "\n1. Create dynamic array, populate, find max, clean up" << endl;
  cout << "2. Implement dynamic string concatenation function" << endl;
  cout << "3. Create and merge two dynamic sorted arrays" << endl;
  cout << "4. Implement dynamic 2D array transpose function" << endl;
  cout << "5. Write function that resizes dynamic array safely" << endl;
  cout << "6. Implement simple dynamic stack using arrays" << endl;
  cout << "7. Create deep copy function for dynamic array" << endl;
  cout << "8. Detect and fix memory leaks in given code" << endl;
  cout << "9. Implement dynamic circular buffer" << endl;
  cout << "10. Write RAII class for dynamic array management" << endl;

  cout << "\n=========================================================" << endl;
  cout << "         NEXT: Smart Pointers (Modern C++ Solution)" << endl;
  cout << "=========================================================" << endl;

  return 0;
}
