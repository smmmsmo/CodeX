/*
================================================================================
TOPIC 3: OPERATORS - PART 2: BITWISE, ASSIGNMENT, AND TERNARY
================================================================================

1. BITWISE OPERATORS (operate on individual bits):
   &   : Bitwise AND
   |   : Bitwise OR
   ^   : Bitwise XOR (exclusive or)
   ~   : Bitwise NOT (complement)
   <<  : Left shift
   >>  : Right shift

2. ASSIGNMENT OPERATORS:
   =   : Simple assignment
   +=  : Add and assign
   -=  : Subtract and assign
   *=  : Multiply and assign
   /=  : Divide and assign
   %=  : Modulus and assign
   &=, |=, ^=, <<=, >>= : Bitwise assignment

3. TERNARY OPERATOR:
   condition ? true_value : false_value
   (Returns true_value if condition is true, else false_value)

================================================================================
*/

#include <bitset>
#include <iostream>
using namespace std;

int main() {
  cout << "=== BITWISE, ASSIGNMENT, AND TERNARY OPERATORS ===" << endl << endl;

  // ======================= BITWISE OPERATORS =======================
  cout << "1. BITWISE OPERATORS:" << endl;

  int num1 = 12; // 1100 in binary
  int num2 = 10; // 1010 in binary

  cout << "num1 = " << num1 << " (binary: " << bitset<8>(num1) << ")" << endl;
  cout << "num2 = " << num2 << " (binary: " << bitset<8>(num2) << ")" << endl;

  cout << "\nBitwise AND (&):" << endl;
  cout << "num1 & num2 = " << (num1 & num2)
       << " (binary: " << bitset<8>(num1 & num2) << ")" << endl;

  cout << "\nBitwise OR (|):" << endl;
  cout << "num1 | num2 = " << (num1 | num2)
       << " (binary: " << bitset<8>(num1 | num2) << ")" << endl;

  cout << "\nBitwise XOR (^):" << endl;
  cout << "num1 ^ num2 = " << (num1 ^ num2)
       << " (binary: " << bitset<8>(num1 ^ num2) << ")" << endl;

  cout << "\nBitwise NOT (~):" << endl;
  cout << "~num1 = " << ~num1 << " (binary: " << bitset<8>(~num1) << ")"
       << endl;

  cout << "\nLeft Shift (<<):" << endl;
  cout << "num1 << 1 = " << (num1 << 1) << " (binary: " << bitset<8>(num1 << 1)
       << ")" << endl;
  cout << "num1 << 2 = " << (num1 << 2) << " (binary: " << bitset<8>(num1 << 2)
       << ")" << endl;

  cout << "\nRight Shift (>>):" << endl;
  cout << "num1 >> 1 = " << (num1 >> 1) << " (binary: " << bitset<8>(num1 >> 1)
       << ")" << endl;
  cout << "num1 >> 2 = " << (num1 >> 2) << " (binary: " << bitset<8>(num1 >> 2)
       << ")" << endl;

  // ======================= ASSIGNMENT OPERATORS =======================
  cout << endl << "2. ASSIGNMENT OPERATORS:" << endl;

  int x = 10;
  cout << "x = " << x << endl;

  x += 5;
  cout << "x += 5  ->  x = " << x << endl;

  x -= 3;
  cout << "x -= 3  ->  x = " << x << endl;

  x *= 2;
  cout << "x *= 2  ->  x = " << x << endl;

  x /= 4;
  cout << "x /= 4  ->  x = " << x << endl;

  x %= 3;
  cout << "x %= 3  ->  x = " << x << endl;

  // ======================= BITWISE ASSIGNMENT =======================
  cout << endl << "3. BITWISE ASSIGNMENT OPERATORS:" << endl;

  int bits = 5; // 0101
  cout << "bits = " << bits << " (binary: " << bitset<8>(bits) << ")" << endl;

  bits &= 3; // 0101 & 0011 = 0001
  cout << "bits &= 3  ->  bits = " << bits << " (binary: " << bitset<8>(bits)
       << ")" << endl;

  bits |= 6; // 0001 | 0110 = 0111
  cout << "bits |= 6  ->  bits = " << bits << " (binary: " << bitset<8>(bits)
       << ")" << endl;

  bits ^= 3; // 0111 ^ 0011 = 0100
  cout << "bits ^= 3  ->  bits = " << bits << " (binary: " << bitset<8>(bits)
       << ")" << endl;

  // ======================= TERNARY OPERATOR =======================
  cout << endl << "4. TERNARY OPERATOR (? :):" << endl;

  int age = 20;
  string status = (age >= 18) ? "Adult" : "Minor";
  cout << "age = " << age << endl;
  cout << "status = " << status << endl;

  int score = 75;
  string result = (score >= 60) ? "Pass" : "Fail";
  cout << "\nscore = " << score << endl;
  cout << "result = " << result << endl;

  // Nested ternary
  int marks = 85;
  string grade = (marks >= 80)   ? "A"
                 : (marks >= 70) ? "B"
                 : (marks >= 60) ? "C"
                                 : "F";
  cout << "\nmarks = " << marks << endl;
  cout << "grade = " << grade << endl;

  // ======================= TERNARY FOR CALCULATIONS =======================
  cout << endl << "5. TERNARY OPERATOR FOR CALCULATIONS:" << endl;

  int num = 7;
  int max_value = (num > 10) ? num : 10;
  cout << "num = " << num << endl;
  cout << "max_value (greater of num and 10) = " << max_value << endl;

  int a = 15, b = 20;
  int larger = (a > b) ? a : b;
  cout << "\na = " << a << ", b = " << b << endl;
  cout << "larger = " << larger << endl;

  // ======================= SHIFT OPERATIONS (PRACTICAL USES)
  // =======================
  cout << endl << "6. PRACTICAL USES OF SHIFT OPERATORS:" << endl;

  int value = 5;
  cout << "value = " << value << endl;
  cout << "value << 1 (multiply by 2) = " << (value << 1) << endl;
  cout << "value << 2 (multiply by 4) = " << (value << 2) << endl;
  cout << "value << 3 (multiply by 8) = " << (value << 3) << endl;

  int value2 = 40;
  cout << "\nvalue2 = " << value2 << endl;
  cout << "value2 >> 1 (divide by 2) = " << (value2 >> 1) << endl;
  cout << "value2 >> 2 (divide by 4) = " << (value2 >> 2) << endl;

  // ======================= REAL-WORLD EXAMPLE =======================
  cout << endl << "7. REAL-WORLD EXAMPLE (Discount Calculation):" << endl;

  double price = 100.0;
  int discount_percent = 20;
  bool is_member = true;

  cout << "Original price: $" << price << endl;

  double discount = (is_member) ? (price * discount_percent / 100) : 0;
  double final_price = price - discount;

  cout << "Is member: " << (is_member ? "Yes" : "No") << endl;
  cout << "Discount: $" << discount << endl;
  cout << "Final price: $" << final_price << endl;

  return 0;
}

/*
OUTPUT:
=== BITWISE, ASSIGNMENT, AND TERNARY OPERATORS ===

1. BITWISE OPERATORS:
num1 = 12 (binary: 00001100)
num2 = 10 (binary: 00001010)

Bitwise AND (&):
num1 & num2 = 8 (binary: 00001000)

Bitwise OR (|):
num1 | num2 = 14 (binary: 00001110)

Bitwise XOR (^):
num1 ^ num2 = 6 (binary: 00000110)

Bitwise NOT (~):
~num1 = -13 (binary: 11110011)

Left Shift (<<):
num1 << 1 = 24 (binary: 00011000)
num1 << 2 = 48 (binary: 00110000)

Right Shift (>>):
num1 >> 1 = 6 (binary: 00000110)
num1 >> 2 = 3 (binary: 00000011)

2. ASSIGNMENT OPERATORS:
x = 10
x += 5  ->  x = 15
x -= 3  ->  x = 12
x *= 2  ->  x = 24
x /= 4  ->  x = 6
x %= 3  ->  x = 0

3. BITWISE ASSIGNMENT OPERATORS:
bits = 5 (binary: 00000101)
bits &= 3  ->  bits = 1 (binary: 00000001)
bits |= 6  ->  bits = 7 (binary: 00000111)
bits ^= 3  ->  bits = 4 (binary: 00000100)

4. TERNARY OPERATOR (? :):
age = 20
status = Adult

score = 75
result = Pass

marks = 85
grade = A

5. TERNARY OPERATOR FOR CALCULATIONS:
num = 7
max_value (greater of num and 10) = 10

a = 15, b = 20
larger = 20

6. PRACTICAL USES OF SHIFT OPERATORS:
value = 5
value << 1 (multiply by 2) = 10
value << 2 (multiply by 4) = 20
value << 3 (multiply by 8) = 40

value2 = 40
value2 >> 1 (divide by 2) = 20
value2 >> 2 (divide by 4) = 10

7. REAL-WORLD EXAMPLE (Discount Calculation):
Original price: $100
Is member: Yes
Discount: $20
Final price: $80

================================================================================
BITWISE OPERATIONS TRUTH TABLES
================================================================================

AND (&):
0 & 0 = 0,  0 & 1 = 0,  1 & 0 = 0,  1 & 1 = 1

OR (|):
0 | 0 = 0,  0 | 1 = 1,  1 | 0 = 1,  1 | 1 = 1

XOR (^):
0 ^ 0 = 0,  0 ^ 1 = 1,  1 ^ 0 = 1,  1 ^ 1 = 0

NOT (~):
~0 = 1,  ~1 = 0

================================================================================
PRACTICE EXERCISES
================================================================================

1. Check if a number is power of 2 using bitwise AND

2. Check if specific bit is set in a number

3. Find maximum of three numbers using ternary operator

4. Calculate fast multiplication/division using shift operators

5. Swap two numbers using XOR operator (a ^= b; b ^= a; a ^= b;)

================================================================================
*/
