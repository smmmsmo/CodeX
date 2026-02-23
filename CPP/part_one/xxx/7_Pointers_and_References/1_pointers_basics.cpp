/*
================================================================================
TOPIC 7: POINTERS AND REFERENCES - PART 1: POINTERS BASICS
================================================================================

POINTER:
- Variable that stores memory address of another variable
- Declared with * operator
- Accessed with & (address-of) operator
- Dereferenced with * (dereference) operator

BENEFITS:
- Dynamic memory allocation
- Pass by reference to functions
- Creating complex data structures (linked lists, trees, graphs)
- Function pointers for callbacks

SYNTAX:
int *ptr;           // Pointer declaration
int *ptr = &x;      // Pointer initialized to address of x
int value = *ptr;   // Dereference: get value pointed to

MEMORY:
- Pointer stores address (typically 8 bytes on 64-bit system)
- Pointed variable stored at that address
- Address is hexadecimal value (0x...)

================================================================================
*/

#include <iostream>
using namespace std;

int main() {
  cout << "=== POINTERS - BASICS ===" << endl << endl;

  // ======================= ADDRESS-OF OPERATOR =======================
  cout << "1. ADDRESS-OF OPERATOR (&):" << endl;

  int x = 10;
  cout << "Variable x = " << x << endl;
  cout << "Address of x (&x) = " << &x << endl;
  cout << "Size of int: " << sizeof(int) << " bytes" << endl;

  // ======================= POINTER DECLARATION AND INITIALIZATION
  // =======================
  cout << endl << "2. POINTER DECLARATION AND INITIALIZATION:" << endl;

  int value = 25;
  int *ptr;     // Pointer declaration (uninitialized, dangerous!)
  ptr = &value; // Initialize pointer with address

  cout << "value = " << value << endl;
  cout << "ptr (contains address) = " << ptr << endl;
  cout << "Address of value (&value) = " << &value << endl;

  // ======================= DEREFERENCE OPERATOR =======================
  cout << endl << "3. DEREFERENCE OPERATOR (*):" << endl;

  int num = 50;
  int *num_ptr = &num;

  cout << "num = " << num << endl;
  cout << "num_ptr = " << num_ptr << " (address)" << endl;
  cout << "*num_ptr = " << *num_ptr << " (value at address)" << endl;

  // ======================= MODIFYING VALUE THROUGH POINTER
  // =======================
  cout << endl << "4. MODIFYING VALUE THROUGH POINTER:" << endl;

  int original = 100;
  int *modify_ptr = &original;

  cout << "Before: original = " << original << endl;
  *modify_ptr = 200; // Modify through pointer
  cout << "After: original = " << original << endl;
  cout << "After: *modify_ptr = " << *modify_ptr << endl;

  // ======================= POINTER TO POINTER =======================
  cout << endl << "5. POINTER TO POINTER:" << endl;

  int var = 5;
  int *ptr1 = &var;
  int **ptr2 = &ptr1; // Pointer to pointer

  cout << "var = " << var << endl;
  cout << "ptr1 = " << ptr1 << " (address of var)" << endl;
  cout << "ptr2 = " << ptr2 << " (address of ptr1)" << endl;
  cout << "*ptr1 = " << *ptr1 << " (value of var)" << endl;
  cout << "**ptr2 = " << **ptr2 << " (value through ptr2)" << endl;

  // ======================= NULL POINTER =======================
  cout << endl << "6. NULL POINTER AND NULLPTR:" << endl;

  int *null_ptr = NULL;     // Old style
  int *null_ptr2 = nullptr; // C++11 style (preferred)

  cout << "null_ptr = " << null_ptr << endl;
  cout << "null_ptr2 = " << null_ptr2 << endl;
  cout << "Checking: null_ptr == nullptr: "
       << (null_ptr == nullptr ? "true" : "false") << endl;

  // ======================= POINTER ARITHMETIC =======================
  cout << endl << "7. POINTER ARITHMETIC:" << endl;

  int arr[5] = {10, 20, 30, 40, 50};
  int *arr_ptr = arr; // Pointer to first element

  cout << "Array: ";
  for (int i = 0; i < 5; i++)
    cout << arr[i] << " ";
  cout << endl;

  cout << "*arr_ptr = " << *arr_ptr << " (first element)" << endl;
  cout << "*(arr_ptr + 1) = " << *(arr_ptr + 1) << " (second element)" << endl;
  cout << "*(arr_ptr + 4) = " << *(arr_ptr + 4) << " (fifth element)" << endl;

  arr_ptr++; // Move pointer to next element
  cout << "After arr_ptr++: *arr_ptr = " << *arr_ptr << endl;

  arr_ptr += 2; // Move pointer 2 positions forward
  cout << "After arr_ptr += 2: *arr_ptr = " << *arr_ptr << endl;

  // ======================= POINTER AND ARRAY RELATIONSHIP
  // =======================
  cout << endl << "8. POINTER AND ARRAY RELATIONSHIP:" << endl;

  int numbers[5] = {1, 2, 3, 4, 5};

  cout << "numbers[0] = " << numbers[0] << endl;
  cout << "*numbers = " << *numbers << endl;
  cout << "arr[2] = " << numbers[2] << endl;
  cout << "*(numbers + 2) = " << *(numbers + 2) << endl;
  cout << "Address of numbers: " << numbers << endl;
  cout << "Address of &numbers[0]: " << &numbers[0] << endl;

  // ======================= DANGLING POINTER =======================
  cout << endl << "9. DANGLING POINTER (WARNING!):" << endl;

  int *danger_ptr;
  {
    int temp = 100;
    danger_ptr = &temp; // Points to local variable
    cout << "Inside block: *danger_ptr = " << *danger_ptr << endl;
  }
  // After block, temp is destroyed, danger_ptr is dangling!
  cout << "Outside block: Don't use danger_ptr (dangling!)" << endl;

  // ======================= CONST POINTER =======================
  cout << endl << "10. CONST POINTER (const DATA):" << endl;

  int const_value = 50;
  const int *const_ptr = &const_value; // Pointer to const int

  cout << "const_value = " << const_value << endl;
  cout << "*const_ptr = " << *const_ptr << endl;
  // *const_ptr = 100;  // ERROR: Cannot modify const data

  // ======================= POINTER TO CONST =======================
  cout << endl << "11. POINTER CONSTANT:" << endl;

  int mutable_value = 75;
  int *const ptr_const = &mutable_value; // Const pointer to int

  cout << "mutable_value = " << mutable_value << endl;
  cout << "*ptr_const = " << *ptr_const << endl;
  *ptr_const = 100; // OK: Can modify data
  cout << "After *ptr_const = 100: mutable_value = " << mutable_value << endl;
  // ptr_const = &x;  // ERROR: Cannot change pointer itself

  // ======================= SIZEOF POINTERS =======================
  cout << endl << "12. POINTER SIZES:" << endl;

  cout << "sizeof(int) = " << sizeof(int) << " bytes" << endl;
  cout << "sizeof(int*) = " << sizeof(int *) << " bytes" << endl;
  cout << "sizeof(double) = " << sizeof(double) << " bytes" << endl;
  cout << "sizeof(double*) = " << sizeof(double *) << " bytes" << endl;

  return 0;
}

/*
OUTPUT:
=== POINTERS - BASICS ===

1. ADDRESS-OF OPERATOR (&):
Variable x = 10
Address of x (&x) = 0x7ffee56e8a8c
Size of int: 4 bytes

2. POINTER DECLARATION AND INITIALIZATION:
value = 25
ptr (contains address) = 0x7ffee56e8a88
Address of value (&value) = 0x7ffee56e8a88

3. DEREFERENCE OPERATOR (*):
num = 50
num_ptr = 0x7ffee56e8a84 (address)
*num_ptr = 50 (value at address)

4. MODIFYING VALUE THROUGH POINTER:
Before: original = 100
After: original = 200
After: *modify_ptr = 200

5. POINTER TO POINTER:
var = 5
ptr1 = 0x7ffee56e8a80 (address of var)
ptr2 = 0x7ffee56e8a78 (address of ptr1)
*ptr1 = 5 (value of var)
**ptr2 = 5 (value through ptr2)

6. NULL POINTER AND NULLPTR:
null_ptr = 0
null_ptr2 = 0
Checking: null_ptr == nullptr: true

7. POINTER ARITHMETIC:
Array: 10 20 30 40 50
*arr_ptr = 10 (first element)
*(arr_ptr + 1) = 20 (second element)
*(arr_ptr + 4) = 50 (fifth element)
After arr_ptr++: *arr_ptr = 20
After arr_ptr += 2: *arr_ptr = 40

8. POINTER AND ARRAY RELATIONSHIP:
numbers[0] = 1
*numbers = 1
arr[2] = 3
*(numbers + 2) = 3
Address of numbers: 0x7ffee56e8a64
Address of &numbers[0]: 0x7ffee56e8a64

9. DANGLING POINTER (WARNING!):
Inside block: *danger_ptr = 100
Outside block: Don't use danger_ptr (dangling!)

10. CONST POINTER (const DATA):
const_value = 50
*const_ptr = 50

11. POINTER CONSTANT:
mutable_value = 75
*ptr_const = 75
After *ptr_const = 100: mutable_value = 100

12. POINTER SIZES:
sizeof(int) = 4 bytes
sizeof(int*) = 8 bytes
sizeof(double) = 8 bytes
sizeof(double*) = 8 bytes

================================================================================
KEY CONCEPTS
================================================================================

1. & OPERATOR:
   - Address-of operator
   - Returns address of variable

2. * OPERATOR:
   - Dereference operator (in usage)
   - Pointer declaration (in declaration)

3. POINTER ARITHMETIC:
   - ptr + n : moves n elements forward
   - ptr - n : moves n elements backward
   - ptr++ : increment, then can dereference
   - *ptr++ : dereference, then increment (due to precedence)
   - Arithmetic scaled by data type size

4. CONST AND POINTERS:
   - const int *ptr : pointer to const int (data is const)
   - int * const ptr : const pointer to int (pointer is const)
   - const int * const ptr : const pointer to const int (both const)

5. COMMON MISTAKES:
   - Uninitialized pointer (undefined behavior)
   - Dangling pointer (after variable destroyed)
   - Dereferencing null pointer (crash)
   - Buffer overflow with pointer arithmetic

================================================================================
PRACTICE EXERCISES
================================================================================

1. Create function to swap two integers using pointers

2. Implement array traversal using pointers

3. Find sum of array using pointer arithmetic

4. Create pointer to function and call it

5. Implement simple dynamic array using pointers

================================================================================
*/
