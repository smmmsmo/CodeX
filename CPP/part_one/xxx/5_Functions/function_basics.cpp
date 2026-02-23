/*
================================================================================
TOPIC 5: FUNCTIONS - PART 1: BASICS, DECLARATION, DEFINITION, AND PARAMETERS
================================================================================

A FUNCTION is a reusable block of code that performs a specific task.

BENEFITS:
- Code reusability
- Better organization
- Easier debugging
- Modularity
- Easier to maintain and test

FUNCTION DECLARATION (PROTOTYPE):
return_type function_name(parameter_list);

FUNCTION DEFINITION:
return_type function_name(parameter_list) {
    // function body
    return return_value;
}

FUNCTION CALL:
function_name(arguments);

PARAMETERS vs ARGUMENTS:
- Parameters: variables in function definition
- Arguments: actual values passed to function

================================================================================
*/

#include <cmath>
#include <iostream>
using namespace std;

// ======================= FUNCTION DECLARATIONS (PROTOTYPES)
// =======================
void greet();
void greet_person(string name);
int add(int a, int b);
double circle_area(double radius);
void print_pattern(int n);
int factorial(int num);
bool is_even(int number);

// ======================= MAIN FUNCTION =======================
int main() {
  cout << "=== FUNCTIONS IN C++ ===" << endl << endl;

  // ======================= FUNCTION WITH NO PARAMETERS, NO RETURN
  // =======================
  cout << "1. FUNCTION WITH NO PARAMETERS AND NO RETURN:" << endl;
  greet();
  greet();

  // ======================= FUNCTION WITH PARAMETERS, NO RETURN
  // =======================
  cout << endl << "2. FUNCTION WITH PARAMETERS AND NO RETURN:" << endl;
  greet_person("Alice");
  greet_person("Bob");
  greet_person("Charlie");

  // ======================= FUNCTION WITH PARAMETERS AND RETURN
  // =======================
  cout << endl << "3. FUNCTION WITH PARAMETERS AND RETURN VALUE:" << endl;
  int result = add(10, 20);
  cout << "10 + 20 = " << result << endl;
  cout << "30 + 40 = " << add(30, 40) << endl;

  // ======================= FUNCTION USING MATH =======================
  cout << endl << "4. FUNCTION CALCULATING CIRCLE AREA:" << endl;
  double area1 = circle_area(5);
  double area2 = circle_area(10);
  cout << "Circle with radius 5: Area = " << area1 << endl;
  cout << "Circle with radius 10: Area = " << area2 << endl;

  // ======================= FUNCTION WITH PATTERN =======================
  cout << endl << "5. FUNCTION PRINTING TRIANGLE PATTERN:" << endl;
  print_pattern(4);

  // ======================= FUNCTION RETURNING BOOLEAN =======================
  cout << endl << "6. FUNCTION RETURNING BOOLEAN:" << endl;
  cout << "Is 4 even? " << (is_even(4) ? "Yes" : "No") << endl;
  cout << "Is 7 even? " << (is_even(7) ? "Yes" : "No") << endl;
  cout << "Is 10 even? " << (is_even(10) ? "Yes" : "No") << endl;

  // ======================= FACTORIAL FUNCTION =======================
  cout << endl << "7. FACTORIAL FUNCTION:" << endl;
  cout << "5! = " << factorial(5) << endl;
  cout << "6! = " << factorial(6) << endl;
  cout << "10! = " << factorial(10) << endl;

  // ======================= DEFAULT PARAMETERS =======================
  cout << endl << "8. FUNCTION WITH DEFAULT PARAMETERS:" << endl;
  multiply(5);    // Uses default b = 1
  multiply(5, 3); // Uses provided b = 3
  multiply(10, 2);

  return 0;
}

// ======================= FUNCTION DEFINITIONS =======================

// Function with no parameters, no return
void greet() { cout << "Hello! Welcome to C++ functions." << endl; }

// Function with parameters, no return
void greet_person(string name) { cout << "Hello, " << name << "!" << endl; }

// Function with parameters and return
int add(int a, int b) { return a + b; }

// Function calculating circle area
double circle_area(double radius) {
  const double PI = 3.14159;
  return PI * radius * radius;
}

// Function printing pattern
void print_pattern(int n) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      cout << "* ";
    }
    cout << endl;
  }
}

// Function returning boolean
bool is_even(int number) { return (number % 2 == 0); }

// Factorial function
int factorial(int num) {
  if (num <= 1)
    return 1;
  return num * factorial(num - 1); // Recursive call
}

// Function with default parameter
void multiply(int a, int b = 1) {
  cout << a << " * " << b << " = " << (a * b) << endl;
}

/*
OUTPUT:
=== FUNCTIONS IN C++ ===

1. FUNCTION WITH NO PARAMETERS AND NO RETURN:
Hello! Welcome to C++ functions.
Hello! Welcome to C++ functions.

2. FUNCTION WITH PARAMETERS AND NO RETURN:
Hello, Alice!
Hello, Bob!
Hello, Charlie!

3. FUNCTION WITH PARAMETERS AND RETURN VALUE:
10 + 20 = 30
30 + 40 = 70

4. FUNCTION CALCULATING CIRCLE AREA:
Circle with radius 5: Area = 78.5394
Circle with radius 10: Area = 314.159

5. FUNCTION PRINTING TRIANGLE PATTERN:
*
* *
* * *
* * * *

6. FUNCTION RETURNING BOOLEAN:
Is 4 even? Yes
Is 7 even? No
Is 10 even? Yes

7. FACTORIAL FUNCTION:
5! = 120
6! = 720
10! = 3628800

8. FUNCTION WITH DEFAULT PARAMETERS:
5 * 1 = 5
5 * 3 = 15
10 * 2 = 20

================================================================================
KEY CONCEPTS
================================================================================

1. VOID RETURN TYPE:
   - Function doesn't return a value
   - Uses 'void' keyword

2. RETURN STATEMENT:
   - Exits function immediately
   - Passes value back to caller
   - Type must match return type

3. PARAMETERS:
   - Define what data function needs
   - Passed by value (copy) by default
   - Multiple parameters separated by comma

4. DEFAULT PARAMETERS:
   - Provide default values
   - Must be at end of parameter list
   - multiply(int a, int b = 1)

5. FUNCTION DECLARATIONS:
   - Tell compiler about function before definition
   - Also called 'prototypes'
   - Enables forward referencing

================================================================================
PRACTICE EXERCISES
================================================================================

1. Create function to find maximum of two numbers

2. Create function to check if number is prime

3. Create function to calculate power (x^n)

4. Create function to find GCD of two numbers

5. Create function that takes array and returns sum

================================================================================
*/
