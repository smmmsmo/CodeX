/*
================================================================================
TOPIC 2: VARIABLES AND DATA TYPES - PART 2: CONSTANTS, TYPE CASTING, SCOPE
================================================================================

1. CONSTANTS:
   - Values that cannot be changed after initialization
   - Declared with 'const' keyword
   - Helps prevent accidental modifications

2. TYPE CASTING (CONVERSION):
   - Implicit: automatic conversion by compiler
   - Explicit: forced conversion by programmer
   - C-style cast: (type) value
   - C++ style cast: static_cast<type>(value)

3. VARIABLE SCOPE:
   - Global scope: entire program
   - Local scope: within block/function
   - Block scope: within {brackets}

================================================================================
*/

#include <iostream>
using namespace std;

// ======================= GLOBAL VARIABLE =======================
int global_var = 100;       // Accessible from anywhere
const int MAX_USERS = 1000; // Global constant

int main() {
  cout << "=== CONSTANTS, TYPE CASTING, AND SCOPE ===" << endl << endl;

  // ======================= CONSTANTS =======================
  cout << "1. CONSTANTS:" << endl;

  const int birth_year = 1990; // Cannot be changed
  const float PI = 3.14159f;
  const char status = 'A';

  cout << "birth_year = " << birth_year << endl;
  cout << "PI = " << PI << endl;
  cout << "status = " << status << endl;
  cout << "MAX_USERS (global) = " << MAX_USERS << endl;

  // birth_year = 1991;  // ERROR: cannot assign to const variable

  // ======================= LOCAL VARIABLES =======================
  cout << endl << "2. LOCAL VARIABLES AND SCOPE:" << endl;

  int local_var = 50; // Local to main()
  cout << "local_var in main = " << local_var << endl;
  cout << "global_var = " << global_var << endl;

  // ======================= BLOCK SCOPE =======================
  cout << endl << "3. BLOCK SCOPE:" << endl;

  {
    int block_var = 200; // Only exists within this block
    cout << "block_var inside block = " << block_var << endl;
  }
  // cout << block_var << endl;  // ERROR: block_var not accessible here

  // ======================= IMPLICIT TYPE CASTING =======================
  cout << endl << "4. IMPLICIT TYPE CASTING:" << endl;

  int num1 = 10;
  double result1 = num1; // int automatically converted to double
  cout << "int num1 = " << num1 << endl;
  cout << "double result1 = num1 = " << result1 << endl;

  double num2 = 10.7;
  int result2 = num2; // double truncated to int (loses decimal part)
  cout << "double num2 = " << num2 << endl;
  cout << "int result2 = num2 = " << result2 << endl;

  // ======================= EXPLICIT TYPE CASTING (C-style)
  // =======================
  cout << endl << "5. EXPLICIT TYPE CASTING (C-style):" << endl;

  double value = 9.9;
  int cast_result = (int)value; // Force convert double to int
  cout << "double value = " << value << endl;
  cout << "int cast_result = (int)value = " << cast_result << endl;

  // ======================= EXPLICIT TYPE CASTING (C++ style)
  // =======================
  cout << endl << "6. EXPLICIT TYPE CASTING (C++ style):" << endl;

  double pi_value = 3.14159;
  int pi_int = static_cast<int>(pi_value);
  float pi_float = static_cast<float>(pi_value);

  cout << "double pi_value = " << pi_value << endl;
  cout << "int pi_int = static_cast<int>(pi_value) = " << pi_int << endl;
  cout << "float pi_float = static_cast<float>(pi_value) = " << pi_float
       << endl;

  // ======================= INTEGER DIVISION vs FLOAT DIVISION
  // =======================
  cout << endl << "7. DIVISION OPERATIONS:" << endl;

  int a = 10, b = 3;
  cout << "int a = " << a << ", int b = " << b << endl;
  cout << "a / b (integer division) = " << (a / b) << endl;
  cout << "(double)a / b (float division) = " << ((double)a / b) << endl;

  // ======================= VARIABLE SHADOWING =======================
  cout << endl << "8. VARIABLE SHADOWING:" << endl;

  int x = 5;
  cout << "x in main = " << x << endl;

  {
    int x = 10; // This shadows outer x
    cout << "x inside block = " << x << endl;
  }

  cout << "x after block = " << x << endl; // Back to original x

  return 0;
}

/*
OUTPUT:
=== CONSTANTS, TYPE CASTING, AND SCOPE ===

1. CONSTANTS:
birth_year = 1990
PI = 3.14159
status = A
MAX_USERS (global) = 1000

2. LOCAL VARIABLES AND SCOPE:
local_var in main = 50
global_var = 100

3. BLOCK SCOPE:
block_var inside block = 200

4. IMPLICIT TYPE CASTING:
int num1 = 10
double result1 = num1 = 10
double num2 = 10.7
int result2 = num2 = 10

5. EXPLICIT TYPE CASTING (C-style):
double value = 9.9
int cast_result = (int)value = 9

6. EXPLICIT TYPE CASTING (C++ style):
double pi_value = 3.14159
int pi_int = static_cast<int>(pi_value) = 3
float pi_float = static_cast<float>(pi_value) = 3.14159

7. DIVISION OPERATIONS:
int a = 10, int b = 3
a / b (integer division) = 3
(double)a / b (float division) = 3.33333

8. VARIABLE SHADOWING:
x in main = 5
x inside block = 10
x after block = 5

================================================================================
KEY CONCEPTS
================================================================================

1. CONST KEYWORD:
   - Used to declare constants
   - Value cannot be changed after initialization
   - Often used for global configuration values

2. SCOPE RULES:
   - Global: declared outside all functions, accessible everywhere
   - Local: declared inside function, accessible only in that function
   - Block: declared inside {}, accessible only in that block
   - Variable shadowing: inner scope hides outer scope variable

3. IMPLICIT CASTING RULES:
   - bool to int/float/double
   - char to int/float/double
   - int to float/double
   - float to double
   - (Reverse conversions lose precision/data)

4. EXPLICIT CASTING:
   - C-style: (type) value
   - C++ style: static_cast<type>(value)  (safer, more readable)

5. TYPE COERCION:
   - In operations, narrower type promoted to wider type
   - Example: int + double = double

================================================================================
COMMON MISTAKES
================================================================================

1. Trying to modify a const variable
   const int x = 5;
   x = 10;  // ERROR!

2. Using variable outside its scope
   {
       int x = 5;
   }
   cout << x;  // ERROR: x not in scope

3. Precision loss in casting
   double d = 3.14;
   int i = d;  // WARNING: d becomes 3, loss of decimal

4. Integer division giving unexpected results
   int result = 5 / 2;  // Result is 2, not 2.5

================================================================================
PRACTICE EXERCISES
================================================================================

1. Create a const PI and use it to calculate circle area

2. Create global and local variables with same name and print both

3. Write a program that reads float and prints as integer after casting

4. Compare integer division vs float division with 7/2

5. Create variables in nested blocks and observe shadowing behavior

================================================================================
*/
