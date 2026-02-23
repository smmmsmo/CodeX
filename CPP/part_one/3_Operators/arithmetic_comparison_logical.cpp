/*
================================================================================
TOPIC 3: OPERATORS - PART 1: ARITHMETIC, COMPARISON, AND LOGICAL
================================================================================

1. ARITHMETIC OPERATORS:
   +  : Addition
   -  : Subtraction
   *  : Multiplication
   /  : Division
   %  : Modulus (remainder)

2. COMPARISON OPERATORS:
   ==  : Equal to
   !=  : Not equal to
   <   : Less than
   >   : Greater than
   <=  : Less than or equal to
   >=  : Greater than or equal to
   (Returns true or false)

3. LOGICAL OPERATORS:
   &&  : AND (both conditions must be true)
   ||  : OR (at least one condition must be true)
   !   : NOT (negates condition)

================================================================================
*/

#include <iostream>
using namespace std;

int main() {
  cout << "=== ARITHMETIC, COMPARISON, AND LOGICAL OPERATORS ===" << endl
       << endl;

  // ======================= ARITHMETIC OPERATORS =======================
  cout << "1. ARITHMETIC OPERATORS:" << endl;

  int a = 15, b = 4;
  cout << "a = " << a << ", b = " << b << endl;
  cout << "a + b = " << (a + b) << endl;
  cout << "a - b = " << (a - b) << endl;
  cout << "a * b = " << (a * b) << endl;
  cout << "a / b = " << (a / b) << endl;
  cout << "a % b = " << (a % b) << " (remainder)" << endl;

  // ======================= COMPARISON OPERATORS =======================
  cout << endl << "2. COMPARISON OPERATORS:" << endl;

  int x = 10, y = 20;
  cout << "x = " << x << ", y = " << y << endl;
  cout << "x == y : " << (x == y) << endl;
  cout << "x != y : " << (x != y) << endl;
  cout << "x < y  : " << (x < y) << endl;
  cout << "x > y  : " << (x > y) << endl;
  cout << "x <= y : " << (x <= y) << endl;
  cout << "x >= y : " << (x >= y) << endl;

  // ======================= LOGICAL OPERATORS =======================
  cout << endl << "3. LOGICAL OPERATORS:" << endl;

  bool condition1 = (x < y);  // true
  bool condition2 = (x > 5);  // true
  bool condition3 = (y < 15); // false

  cout << "condition1 (x < y) = " << condition1 << endl;
  cout << "condition2 (x > 5) = " << condition2 << endl;
  cout << "condition3 (y < 15) = " << condition3 << endl;

  cout << endl << "AND (&&) operation:" << endl;
  cout << "condition1 && condition2 = " << (condition1 && condition2)
       << " (both true)" << endl;
  cout << "condition1 && condition3 = " << (condition1 && condition3)
       << " (one false)" << endl;

  cout << endl << "OR (||) operation:" << endl;
  cout << "condition1 || condition2 = " << (condition1 || condition2)
       << " (both true)" << endl;
  cout << "condition2 || condition3 = " << (condition2 || condition3)
       << " (one true)" << endl;
  cout << "condition3 || condition3 = " << (condition3 || condition3)
       << " (both false)" << endl;

  cout << endl << "NOT (!) operation:" << endl;
  cout << "!condition1 = " << !condition1 << " (NOT true)" << endl;
  cout << "!condition3 = " << !condition3 << " (NOT false)" << endl;

  // ======================= COMPLEX LOGICAL EXPRESSIONS =======================
  cout << endl << "4. COMPLEX LOGICAL EXPRESSIONS:" << endl;

  int age = 25, income = 50000;
  cout << "age = " << age << ", income = " << income << endl;

  bool can_vote = (age >= 18);
  bool can_loan = (income >= 40000);
  bool eligible = (age >= 18) && (income >= 40000);

  cout << "can_vote (age >= 18) = " << can_vote << endl;
  cout << "can_loan (income >= 40000) = " << can_loan << endl;
  cout << "eligible for all benefits (age >= 18 AND income >= 40000) = "
       << eligible << endl;

  // ======================= OPERATOR PRECEDENCE =======================
  cout << endl << "5. OPERATOR PRECEDENCE:" << endl;

  int result1 = 2 + 3 * 4;   // 2 + (3*4) = 14
  int result2 = (2 + 3) * 4; // (2+3)*4 = 20

  cout << "2 + 3 * 4 = " << result1 << endl;
  cout << "(2 + 3) * 4 = " << result2 << endl;

  // ======================= MODULUS OPERATOR USES =======================
  cout << endl << "6. MODULUS OPERATOR USES:" << endl;

  int num = 17;
  cout << "num = " << num << endl;
  cout << "num % 2 = " << (num % 2) << " (check if odd: 1=odd, 0=even)" << endl;
  cout << "num % 5 = " << (num % 5) << endl;

  // ======================= REAL-WORLD EXAMPLE =======================
  cout << endl << "7. REAL-WORLD EXAMPLE (Grade Evaluation):" << endl;

  int score = 85;
  cout << "Student score: " << score << endl;
  cout << "Score >= 80 AND Score < 90: " << ((score >= 80) && (score < 90))
       << " (Grade B)" << endl;
  cout << "Score >= 60 OR Score >= 80: " << ((score >= 60) || (score >= 80))
       << " (Passed)" << endl;
  cout << "NOT (Score < 60): " << !((score < 60)) << " (Not failed)" << endl;

  return 0;
}

/*
OUTPUT:
=== ARITHMETIC, COMPARISON, AND LOGICAL OPERATORS ===

1. ARITHMETIC OPERATORS:
a = 15, b = 4
a + b = 19
a - b = 11
a * b = 60
a / b = 3
a % b = 3 (remainder)

2. COMPARISON OPERATORS:
x = 10, y = 20
x == y : 0
x != y : 1
x < y  : 1
x > y  : 0
x <= y : 1
x >= y : 0

3. LOGICAL OPERATORS:
condition1 (x < y) = 1
condition2 (x > 5) = 1
condition3 (y < 15) = 0

AND (&&) operation:
condition1 && condition2 = 1 (both true)
condition1 && condition3 = 0 (one false)

OR (||) operation:
condition1 || condition2 = 1 (both true)
condition2 || condition3 = 1 (one true)
condition3 || condition3 = 0 (both false)

NOT (!) operation:
!condition1 = 0 (NOT true)
!condition3 = 1 (NOT false)

4. COMPLEX LOGICAL EXPRESSIONS:
age = 25, income = 50000
can_vote (age >= 18) = 1
can_loan (income >= 40000) = 1
eligible for all benefits (age >= 18 AND income >= 40000) = 1

5. OPERATOR PRECEDENCE:
2 + 3 * 4 = 14
(2 + 3) * 4 = 20

6. MODULUS OPERATOR USES:
num = 17
num % 2 = 1 (check if odd: 1=odd, 0=even)
num % 5 = 2

7. REAL-WORLD EXAMPLE (Grade Evaluation):
Student score: 85
Score >= 80 AND Score < 90: 1 (Grade B)
Score >= 60 OR Score >= 80: 1 (Passed)
NOT (Score < 60): 1 (Not failed)

================================================================================
OPERATOR PRECEDENCE (High to Low)
================================================================================

1. Arithmetic: * / % (Higher)
2. Arithmetic: + -
3. Comparison: < > <= >=
4. Comparison: == !=
5. Logical: &&
6. Logical: ||
7. Assignment: = (Lower)

Use parentheses () to override precedence and make code clearer!

================================================================================
TRUTH TABLES
================================================================================

AND (&&):
true && true = true
true && false = false
false && true = false
false && false = false

OR (||):
true || true = true
true || false = true
false || true = true
false || false = false

NOT (!):
!true = false
!false = true

================================================================================
PRACTICE EXERCISES
================================================================================

1. Calculate area and perimeter of rectangle given length and width

2. Check if a number is even or odd using modulus

3. Check if a student passed (score >= 60) AND is in top class (score >= 80)

4. Create age verification: 18 <= age <= 65 for employment

5. Calculate salary with 10% bonus if performance >= 8 AND attendance >= 90%

================================================================================
*/
