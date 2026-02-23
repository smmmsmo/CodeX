/*
================================================================================
TOPIC 5: FUNCTIONS - PART 2: FUNCTION OVERLOADING, PASS BY REFERENCE, RECURSION
================================================================================

1. FUNCTION OVERLOADING:
   - Same function name with different parameters
   - Parameters differ in type, number, or order
   - Compiler chooses correct version based on arguments

2. PASS BY VALUE vs PASS BY REFERENCE:
   - Value: function gets a copy (changes don't affect original)
   - Reference (&): function gets reference to original (changes affect
original)

3. RECURSION:
   - Function calling itself
   - Must have base case (stopping condition)
   - Each call uses stack memory

================================================================================
*/

#include <iostream>
using namespace std;

// ======================= FUNCTION OVERLOADING =======================
// Function to add two integers
int add(int a, int b) { return a + b; }

// Function to add three integers
int add(int a, int b, int c) { return a + b + c; }

// Function to add two doubles
double add(double a, double b) { return a + b; }

// ======================= PASS BY VALUE =======================
void increment_by_value(int num) {
  num++;
  cout << "Inside function (by value): " << num << endl;
}

// ======================= PASS BY REFERENCE =======================
void increment_by_reference(int &num) {
  num++;
  cout << "Inside function (by reference): " << num << endl;
}

// ======================= SWAP BY REFERENCE =======================
void swap_values(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

// ======================= RECURSION - FACTORIAL =======================
int factorial_recursive(int n) {
  if (n <= 1)
    return 1;                            // Base case
  return n * factorial_recursive(n - 1); // Recursive case
}

// ======================= RECURSION - FIBONACCI =======================
int fibonacci(int n) {
  if (n <= 1)
    return n;                                 // Base case
  return fibonacci(n - 1) + fibonacci(n - 2); // Recursive case
}

// ======================= RECURSION - POWER =======================
int power(int base, int exponent) {
  if (exponent == 0)
    return 1;                              // Base case
  return base * power(base, exponent - 1); // Recursive case
}

// ======================= RECURSION - SUM OF DIGITS =======================
int sum_of_digits(int num) {
  if (num == 0)
    return 0;                                  // Base case
  return (num % 10) + sum_of_digits(num / 10); // Recursive case
}

int main() {
  cout << "=== FUNCTION OVERLOADING, REFERENCE, AND RECURSION ===" << endl
       << endl;

  // ======================= FUNCTION OVERLOADING =======================
  cout << "1. FUNCTION OVERLOADING:" << endl;
  cout << "add(10, 20) = " << add(10, 20) << endl;
  cout << "add(10, 20, 30) = " << add(10, 20, 30) << endl;
  cout << "add(10.5, 20.3) = " << add(10.5, 20.3) << endl;

  // ======================= PASS BY VALUE =======================
  cout << endl << "2. PASS BY VALUE:" << endl;
  int value = 5;
  cout << "Before function: " << value << endl;
  increment_by_value(value);
  cout << "After function: " << value << " (unchanged)" << endl;

  // ======================= PASS BY REFERENCE =======================
  cout << endl << "3. PASS BY REFERENCE:" << endl;
  int ref_value = 5;
  cout << "Before function: " << ref_value << endl;
  increment_by_reference(ref_value);
  cout << "After function: " << ref_value << " (changed!)" << endl;

  // ======================= SWAP FUNCTION =======================
  cout << endl << "4. SWAP USING REFERENCE:" << endl;
  int x = 10, y = 20;
  cout << "Before swap: x = " << x << ", y = " << y << endl;
  swap_values(x, y);
  cout << "After swap: x = " << x << ", y = " << y << endl;

  // ======================= RECURSION - FACTORIAL =======================
  cout << endl << "5. RECURSION - FACTORIAL:" << endl;
  cout << "5! = " << factorial_recursive(5) << endl;
  cout << "7! = " << factorial_recursive(7) << endl;
  cout << "10! = " << factorial_recursive(10) << endl;

  // ======================= RECURSION - FIBONACCI =======================
  cout << endl << "6. RECURSION - FIBONACCI SEQUENCE:" << endl;
  cout << "First 10 Fibonacci numbers:" << endl;
  for (int i = 0; i < 10; i++) {
    cout << fibonacci(i) << " ";
  }
  cout << endl;

  // ======================= RECURSION - POWER =======================
  cout << endl << "7. RECURSION - POWER (Base^Exponent):" << endl;
  cout << "2^5 = " << power(2, 5) << endl;
  cout << "3^4 = " << power(3, 4) << endl;
  cout << "10^3 = " << power(10, 3) << endl;

  // ======================= RECURSION - SUM OF DIGITS =======================
  cout << endl << "8. RECURSION - SUM OF DIGITS:" << endl;
  cout << "Sum of digits of 1234 = " << sum_of_digits(1234) << endl;
  cout << "Sum of digits of 9876 = " << sum_of_digits(9876) << endl;
  cout << "Sum of digits of 555 = " << sum_of_digits(555) << endl;

  // ======================= RECURSION - BINARY REPRESENTATION
  // =======================
  cout << endl << "9. RECURSION - PRINT BINARY REPRESENTATION:" << endl;
  print_binary(5);
  cout << endl;
  print_binary(10);
  cout << endl;
  print_binary(15);
  cout << endl;

  // ======================= RECURSION - PALINDROME CHECK
  // =======================
  cout << endl << "10. RECURSION - CHECK PALINDROME:" << endl;
  string str1 = "racecar";
  string str2 = "hello";
  cout << "Is '" << str1 << "' palindrome? "
       << (is_palindrome(str1) ? "Yes" : "No") << endl;
  cout << "Is '" << str2 << "' palindrome? "
       << (is_palindrome(str2) ? "Yes" : "No") << endl;

  return 0;
}

// ======================= ADDITIONAL RECURSIVE FUNCTIONS
// =======================

// Print binary representation recursively
void print_binary(int num) {
  if (num > 1) {
    print_binary(num / 2);
  }
  cout << (num % 2);
}

// Check if string is palindrome recursively
bool is_palindrome(string str) {
  if (str.length() <= 1)
    return true; // Base case
  if (str[0] != str[str.length() - 1])
    return false;
  return is_palindrome(str.substr(1, str.length() - 2)); // Recursive case
}

/*
OUTPUT:
=== FUNCTION OVERLOADING, REFERENCE, AND RECURSION ===

1. FUNCTION OVERLOADING:
add(10, 20) = 30
add(10, 20, 30) = 60
add(10.5, 20.3) = 30.8

2. PASS BY VALUE:
Before function: 5
Inside function (by value): 6
After function: 5 (unchanged)

3. PASS BY REFERENCE:
Before function: 5
Inside function (by reference): 6
After function: 6 (changed!)

4. SWAP USING REFERENCE:
Before swap: x = 10, y = 20
After swap: x = 20, y = 10

5. RECURSION - FACTORIAL:
5! = 120
7! = 5040
10! = 3628800

6. RECURSION - FIBONACCI SEQUENCE:
First 10 Fibonacci numbers:
0 1 1 2 3 5 8 13 21 34

7. RECURSION - POWER (Base^Exponent):
2^5 = 32
3^4 = 81
10^3 = 1000

8. RECURSION - SUM OF DIGITS:
Sum of digits of 1234 = 10
Sum of digits of 9876 = 30
Sum of digits of 555 = 15

9. RECURSION - PRINT BINARY REPRESENTATION:
101
1010
1111

10. RECURSION - CHECK PALINDROME:
Is 'racecar' palindrome? Yes
Is 'hello' palindrome? No

================================================================================
KEY CONCEPTS
================================================================================

1. FUNCTION OVERLOADING:
   - Different functions share same name
   - Compiler determines which to call based on arguments
   - Improves code readability

2. PASS BY VALUE:
   - Default parameter passing method
   - Function receives copy of argument
   - Original variable unaffected

3. PASS BY REFERENCE:
   - Use & in parameter declaration
   - Function receives reference to original
   - Changes in function affect original
   - Useful for output parameters
   - More efficient for large objects

4. RECURSION BASICS:
   - Function calls itself
   - Must have BASE CASE (stopping condition)
   - Each call adds to call stack
   - Can cause stack overflow if not careful

5. WHEN TO USE RECURSION:
   - Tree/graph traversal
   - Divide and conquer problems
   - Mathematical sequences (factorial, Fibonacci)
   - Backtracking problems

6. RECURSION VS ITERATION:
   - Recursion: elegant, but slower and uses more memory
   - Iteration: faster, efficient, but sometimes less intuitive

================================================================================
PRACTICE EXERCISES
================================================================================

1. Create overloaded subtract function for int, double, and three parameters

2. Create function to reverse array using reference parameter

3. Write recursive function to print digits in reverse

4. Write recursive function to find GCD (Euclidean algorithm)

5. Write recursive function to count occurrences of element in array

6. Create recursive function to generate all permutations

7. Write recursive solution to Tower of Hanoi problem

================================================================================
*/
