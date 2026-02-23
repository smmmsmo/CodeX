/*
================================================================================
TOPIC 7: POINTERS AND REFERENCES - PART 2: REFERENCES AND FUNCTION POINTERS
================================================================================

REFERENCES:
- Alias to an existing variable
- Cannot be null or reassigned
- Automatically dereferenced
- Created with & operator in declaration

REFERENCES VS POINTERS:
- References: safer, cannot be null, always valid
- Pointers: flexible, can be null, can be reassigned
- References: preferred for modern C++

FUNCTION POINTERS:
- Pointer to a function
- Can be passed as argument
- Used for callbacks, function arrays

SYNTAX:
int& ref = x;                    // Reference
int (*func_ptr)(int, int);       // Function pointer
func_ptr = &add;                 // Assign function address

================================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

// Forward declarations for function pointers
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);

int main() {
  cout << "=== REFERENCES AND FUNCTION POINTERS ===" << endl << endl;

  // ======================= REFERENCES BASICS =======================
  cout << "1. REFERENCE BASICS:" << endl;

  int x = 10;
  int &ref = x; // Reference to x

  cout << "x = " << x << endl;
  cout << "ref = " << ref << endl;
  cout << "x and ref refer to same variable" << endl;

  ref = 20; // Modify through reference
  cout << "After ref = 20:" << endl;
  cout << "x = " << x << endl;
  cout << "ref = " << ref << endl;

  // ======================= REFERENCE AS ALIAS =======================
  cout << endl << "2. REFERENCES AS ALIAS:" << endl;

  int value = 100;
  int &alias1 = value;
  int &alias2 = value;

  cout << "value = " << value << endl;
  cout << "alias1 = " << alias1 << endl;
  cout << "alias2 = " << alias2 << endl;

  alias1 = 200;
  cout << "After alias1 = 200:" << endl;
  cout << "value = " << value << endl;
  cout << "alias2 = " << alias2 << endl;

  // ======================= REFERENCE AND POINTER SIZES =======================
  cout << endl << "3. REFERENCE VS POINTER SIZE:" << endl;

  int number = 5;
  int &num_ref = number;
  int *num_ptr = &number;

  cout << "sizeof(number) = " << sizeof(number) << " bytes" << endl;
  cout << "sizeof(num_ref) = " << sizeof(num_ref) << " bytes (same as original)"
       << endl;
  cout << "sizeof(num_ptr) = " << sizeof(num_ptr) << " bytes" << endl;

  // ======================= FUNCTION WITH REFERENCE PARAMETERS
  // =======================
  cout << endl << "4. FUNCTION WITH REFERENCE PARAMETERS:" << endl;

  void increment_by_ref(int &x); // Forward declaration

  int count = 5;
  cout << "Before: count = " << count << endl;
  increment_by_ref(count);
  cout << "After: count = " << count << endl;

  // ======================= SWAP USING REFERENCES =======================
  cout << endl << "5. SWAP USING REFERENCES:" << endl;

  void swap_ref(int &a, int &b); // Forward declaration

  int a = 10, b = 20;
  cout << "Before swap: a = " << a << ", b = " << b << endl;
  swap_ref(a, b);
  cout << "After swap: a = " << a << ", b = " << b << endl;

  // ======================= FUNCTION POINTERS BASICS =======================
  cout << endl << "6. FUNCTION POINTER BASICS:" << endl;

  int (*calc_ptr)(int, int); // Declare function pointer

  calc_ptr = &add;               // Assign address of add function
  int result1 = calc_ptr(10, 5); // Call through pointer
  cout << "10 + 5 = " << result1 << endl;

  calc_ptr = &subtract; // Change to subtract function
  int result2 = calc_ptr(10, 5);
  cout << "10 - 5 = " << result2 << endl;

  calc_ptr = &multiply; // Change to multiply function
  int result3 = calc_ptr(10, 5);
  cout << "10 * 5 = " << result3 << endl;

  // ======================= FUNCTION POINTER WITHOUT & =======================
  cout << endl << "7. FUNCTION POINTER (Function Name as Address):" << endl;

  int (*func_ptr2)(int, int); // Without & is also OK
  func_ptr2 = add;            // Function name decays to pointer
  cout << "Using func_ptr2: 7 + 3 = " << func_ptr2(7, 3) << endl;

  // ======================= CALLING THROUGH POINTER =======================
  cout << endl << "8. CALLING THROUGH POINTER (Both Methods):" << endl;

  int (*op_ptr)(int, int) = &multiply;

  cout << "Method 1: op_ptr(4, 5) = " << op_ptr(4, 5) << endl;
  cout << "Method 2: (*op_ptr)(4, 5) = " << (*op_ptr)(4, 5) << endl;

  // ======================= ARRAY OF FUNCTION POINTERS =======================
  cout << endl << "9. ARRAY OF FUNCTION POINTERS:" << endl;

  int (*operations[3])(int, int) = {add, subtract, multiply};

  int x_val = 20, y_val = 4;
  cout << "Using function pointer array:" << endl;
  cout << operations[0](x_val, y_val) << " (add)" << endl;
  cout << operations[1](x_val, y_val) << " (subtract)" << endl;
  cout << operations[2](x_val, y_val) << " (multiply)" << endl;

  // ======================= CONST REFERENCE =======================
  cout << endl << "10. CONST REFERENCE:" << endl;

  int const_value = 50;
  const int &const_ref = const_value;

  cout << "const_value = " << const_value << endl;
  cout << "const_ref = " << const_ref << endl;
  cout << "Can read but not modify through const_ref" << endl;

  // ======================= REFERENCE TO CONST PARAMETER
  // =======================
  cout << endl << "11. PASS BY CONST REFERENCE:" << endl;

  void print_array(const int &arr_size,
                   const vector<int> &arr); // Forward declaration
  vector<int> vec = {1, 2, 3, 4, 5};
  int size = vec.size();
  print_array(size, vec);

  return 0;
}

// ======================= FUNCTION IMPLEMENTATIONS =======================

int add(int a, int b) { return a + b; }

int subtract(int a, int b) { return a - b; }

int multiply(int a, int b) { return a * b; }

void increment_by_ref(int &x) { x++; }

void swap_ref(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

void print_array(const int &size, const vector<int> &arr) {
  cout << "Array elements (";
  for (int i = 0; i < size; i++) {
    cout << arr[i];
    if (i < size - 1)
      cout << ", ";
  }
  cout << ")" << endl;
}

/*
OUTPUT:
=== REFERENCES AND FUNCTION POINTERS ===

1. REFERENCE BASICS:
x = 10
ref = 10
x and ref refer to same variable
After ref = 20:
x = 20
ref = 20

2. REFERENCES AS ALIAS:
value = 100
alias1 = 100
alias2 = 100
After alias1 = 200:
value = 200
alias2 = 200

3. REFERENCE VS POINTER SIZE:
sizeof(number) = 4 bytes
sizeof(num_ref) = 4 bytes (same as original)
sizeof(num_ptr) = 8 bytes

4. FUNCTION WITH REFERENCE PARAMETERS:
Before: count = 5
After: count = 6

5. SWAP USING REFERENCES:
Before swap: a = 10, b = 20
After swap: a = 20, b = 10

6. FUNCTION POINTER BASICS:
10 + 5 = 15
10 - 5 = 5
10 * 5 = 50

7. FUNCTION POINTER (Function Name as Address):
Using func_ptr2: 7 + 3 = 10

8. CALLING THROUGH POINTER (Both Methods):
Method 1: op_ptr(4, 5) = 20
Method 2: (*op_ptr)(4, 5) = 20

9. ARRAY OF FUNCTION POINTERS:
Using function pointer array:
20 (add)
16 (subtract)
80 (multiply)

10. CONST REFERENCE:
const_value = 50
const_ref = 50
Can read but not modify through const_ref

11. PASS BY CONST REFERENCE:
Array elements (1, 2, 3, 4, 5)

================================================================================
KEY CONCEPTS
================================================================================

1. REFERENCES:
   - Safer than pointers
   - Cannot be null
   - Cannot be reassigned
   - No special operator needed to dereference
   - Great for function parameters

2. WHEN TO USE REFERENCES:
   - Function parameters (pass by reference)
   - Return references (careful with local vars!)
   - Simpler, safer code

3. WHEN TO USE POINTERS:
   - Pointer arithmetic needed
   - Dynamic memory (new/delete)
   - Pointer containers
   - Need null possibility

4. FUNCTION POINTERS:
   - Signature must match: return type and parameters
   - Array of function pointers for callbacks
   - Useful for strategy pattern, callbacks

5. CONST WITH REFERENCES:
   - const int& : reference to const int (data is const)
   - Good for preventing modifications
   - Enables passing temporaries

================================================================================
PRACTICE EXERCISES
================================================================================

1. Create higher-order function taking function pointer

2. Implement callback system using function pointers

3. Create generic function using function pointers

4. Pass 2D array using references

5. Implement custom sort with function pointer comparator

================================================================================
*/
