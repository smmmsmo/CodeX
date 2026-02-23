/*
================================================================================
TOPIC 8: DYNAMIC MEMORY MANAGEMENT - PART 1: NEW, DELETE, DYNAMIC ARRAYS
================================================================================

MEMORY LAYOUT:
- Stack: automatic variables, function calls, parameters
- Heap: dynamically allocated memory
- Code/Text: program instructions
- Data: global/static variables

DYNAMIC ALLOCATION:
- Allocate memory at runtime
- Use 'new' operator
- Must free with 'delete' operator

STATIC VS DYNAMIC:
- Static: int arr[10]; - size known at compile time, stack allocated
- Dynamic: int* arr = new int[10]; - size at runtime, heap allocated

SYNTAX:
int *ptr = new int;           // Allocate single int
int *arr = new int[10];       // Allocate array of 10 ints
delete ptr;                   // Free single
delete[] arr;                 // Free array (note: delete[])

IMPORTANT: Every new needs matching delete!

================================================================================
*/

#include <iostream>
using namespace std;

int main() {
  cout << "=== DYNAMIC MEMORY ALLOCATION (NEW AND DELETE) ===" << endl << endl;

  // ======================= ALLOCATING SINGLE VARIABLE =======================
  cout << "1. ALLOCATING AND DEALLOCATING SINGLE VARIABLE:" << endl;

  int *ptr = new int; // Allocate int on heap
  *ptr = 50;          // Store value

  cout << "Value: " << *ptr << endl;
  cout << "Address: " << ptr << endl;
  cout << "Size: " << sizeof(int) << " bytes" << endl;

  delete ptr;    // Free memory
  ptr = nullptr; // Good practice
  cout << "Memory freed" << endl;

  // ======================= ALLOCATING WITH INITIALIZATION
  // =======================
  cout << endl << "2. ALLOCATION WITH INITIALIZATION:" << endl;

  int *num = new int(100); // Allocate and initialize with 100
  cout << "Value: " << *num << endl;

  double *pi = new double(3.14159);
  cout << "Pi: " << *pi << endl;

  delete num;
  delete pi;
  cout << "Freed num and pi" << endl;

  // ======================= ALLOCATING ARRAYS =======================
  cout << endl << "3. ALLOCATING DYNAMIC ARRAYS:" << endl;

  int size;
  cout << "Enter array size: ";
  size = 5; // Simulating input

  int *arr = new int[size]; // Allocate array

  cout << "Entered size: " << size << endl;
  cout << "Initializing array values..." << endl;

  for (int i = 0; i < size; i++) {
    arr[i] = (i + 1) * 10; // 10, 20, 30, 40, 50
  }

  cout << "Array contents: ";
  for (int i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  delete[] arr; // Important: use [] for arrays!
  arr = nullptr;
  cout << "Array freed" << endl;

  // ======================= DYNAMIC 2D ARRAYS =======================
  cout << endl << "4. DYNAMIC 2D ARRAYS:" << endl;

  int rows = 3, cols = 3;

  // Allocate 2D array (array of pointers)
  int **matrix = new int *[rows];
  for (int i = 0; i < rows; i++) {
    matrix[i] = new int[cols];
  }

  // Initialize
  int value = 1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = value++;
    }
  }

  // Display
  cout << "2D Array (3x3):" << endl;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }

  // Deallocate 2D array
  for (int i = 0; i < rows; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
  cout << "2D array freed" << endl;

  // ======================= MEMORY LEAK EXAMPLE =======================
  cout << endl << "5. MEMORY LEAK EXAMPLE (What NOT to do):" << endl;

  cout << "Creating pointers without deleting:" << endl;
  for (int i = 0; i < 3; i++) {
    int *leak = new int(i * 100);
    cout << "Allocated: " << *leak << " at " << leak << endl;
    // Forgot to delete leak!  <- MEMORY LEAK!
  }
  cout << "These allocations were not freed (memory leak!)" << endl;

  // ======================= MEMORY LEAK PREVENTION =======================
  cout << endl << "6. PREVENTING MEMORY LEAKS:" << endl;

  for (int i = 0; i < 3; i++) {
    int *safe = new int(i * 100);
    cout << "Allocated: " << *safe << endl;
    delete safe; // Always delete!
    safe = nullptr;
  }
  cout << "All memory properly freed" << endl;

  // ======================= DYNAMIC ARRAY OF STRUCTURES =======================
  cout << endl << "7. DYNAMIC ARRAY OF STRUCTURES:" << endl;

  struct Person {
    string name;
    int age;
  };

  // Note: This is simplified; using new with struct would need proper
  // initialization
  cout << "Person structure can be allocated dynamically" << endl;
  cout << "Example: Person *p = new Person();" << endl;

  // ======================= ACCESSING DYNAMIC ARRAY =======================
  cout << endl << "8. DIFFERENT WAYS TO ACCESS DYNAMIC ARRAYS:" << endl;

  int *dynamic_arr = new int[5];
  for (int i = 0; i < 5; i++) {
    dynamic_arr[i] = i * 2;
  }

  cout << "Using bracket notation: dynamic_arr[2] = " << dynamic_arr[2] << endl;
  cout << "Using pointer arithmetic: *(dynamic_arr + 2) = "
       << *(dynamic_arr + 2) << endl;

  delete[] dynamic_arr;

  // ======================= RESIZING ARRAYS (REALLOCATION)
  // =======================
  cout << endl << "9. RESIZING ARRAY (Reallocation):" << endl;

  int *original = new int[5];
  cout << "Original array size: 5" << endl;

  for (int i = 0; i < 5; i++) {
    original[i] = i + 1;
  }

  // Allocate larger array
  int *resized = new int[10];
  cout << "Resized array size: 10" << endl;

  // Copy old data
  for (int i = 0; i < 5; i++) {
    resized[i] = original[i];
  }

  // Initialize new cells
  for (int i = 5; i < 10; i++) {
    resized[i] = 0;
  }

  cout << "Array after resize: ";
  for (int i = 0; i < 10; i++) {
    cout << resized[i] << " ";
  }
  cout << endl;

  delete[] original;
  delete[] resized;
  cout << "Both arrays freed" << endl;

  // ======================= SIZE OF DYNAMICALLY ALLOCATED
  // =======================
  cout << endl << "10. LIMITATION: SIZEOF WITH DYNAMIC ARRAYS:" << endl;

  int *dyn_arr = new int[100];
  int static_arr[100];

  cout << "sizeof(dyn_arr) = " << sizeof(dyn_arr) << " bytes (pointer size!)"
       << endl;
  cout << "sizeof(static_arr) = " << sizeof(static_arr)
       << " bytes (actual array)" << endl;
  cout << "Must keep track of dynamic array size separately!" << endl;

  delete[] dyn_arr;

  return 0;
}

/*
OUTPUT:
=== DYNAMIC MEMORY ALLOCATION (NEW AND DELETE) ===

1. ALLOCATING AND DEALLOCATING SINGLE VARIABLE:
Value: 50
Address: 0x7f8b2b500000
Size: 4 bytes
Memory freed

2. ALLOCATION WITH INITIALIZATION:
Value: 100
Pi: 3.14159
Freed num and pi

3. ALLOCATING DYNAMIC ARRAYS:
Entered size: 5
Initializing array values...
Array contents: 10 20 30 40 50
Array freed

4. DYNAMIC 2D ARRAYS:
2D Array (3x3):
1 2 3
4 5 6
7 8 9
2D array freed

5. MEMORY LEAK EXAMPLE (What NOT to do):
Creating pointers without deleting:
Allocated: 0 at 0x7f8b2b501000
Allocated: 100 at 0x7f8b2b501008
Allocated: 200 at 0x7f8b2b501010
These allocations were not freed (memory leak!)

6. PREVENTING MEMORY LEAKS:
Allocated: 0
Allocated: 100
Allocated: 200
All memory properly freed

7. DYNAMIC ARRAY OF STRUCTURES:
Person structure can be allocated dynamically
Example: Person *p = new Person();

8. DIFFERENT WAYS TO ACCESS DYNAMIC ARRAYS:
Using bracket notation: dynamic_arr[2] = 4
Using pointer arithmetic: *(dynamic_arr + 2) = 4

9. RESIZING ARRAY (Reallocation):
Original array size: 5
Resized array size: 10
Array after resize: 1 2 3 4 5 0 0 0 0 0
Both arrays freed

10. LIMITATION: SIZEOF WITH DYNAMIC ARRAYS:
sizeof(dyn_arr) = 8 bytes (pointer size!)
sizeof(static_arr) = 400 bytes (actual array)
Must keep track of dynamic array size separately!

================================================================================
MEMORY ALLOCATION RULES
================================================================================

1. PAIRING RULES:
   - new → delete (single)
   - new[] → delete[] (array)
   - MISMATCH CAUSES UNDEFINED BEHAVIOR!

2. INITIALIZATION:
   - new int; → uninitialized (garbage value)
   - new int(); → zero-initialized
   - new int(100); → initialized to 100

3. CHECKING ALLOCATION:
   - In C++, new throws std::bad_alloc if allocation fails
   - Rarely need null checks (unlike C's malloc)

4. BEST PRACTICES:
   - Set pointer to nullptr after delete
   - Use smart pointers (unique_ptr, shared_ptr) instead
   - Avoid manual new/delete in production code

5. 2D ARRAY ALLOCATION:
   - Allocate array of pointers
   - Then allocate each row
   - Deallocate rows first, then row pointers

================================================================================
COMMON MISTAKES
================================================================================

1. MEMORY LEAK:
   int *p = new int;
   // forgot delete p;

2. DOUBLE DELETE:
   delete p;
   delete p;  // Undefined behavior!

3. WRONG OPERATOR:
   int *arr = new int[10];
   delete arr;  // Should be delete[]

4. USE AFTER DELETE:
   int *p = new int(5);
   delete p;
   cout << *p;  // Undefined behavior!

5. DANGLING POINTER:
   int *p = new int(10);
   delete p;
   p;  // Still points to freed memory

================================================================================
PRACTICE EXERCISES
================================================================================

1. Create dynamic array and implement insertion

2. Implement dynamic array that doubles when full

3. Create dynamic 3D array

4. Implement dynamic matrix multiplication

5. Create simple dynamic string class

================================================================================
*/
