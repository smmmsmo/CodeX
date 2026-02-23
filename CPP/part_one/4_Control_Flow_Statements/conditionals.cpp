/*
================================================================================
TOPIC 4: CONTROL FLOW STATEMENTS - PART 1: IF-ELSE AND SWITCH
================================================================================

1. IF STATEMENT:
   if (condition) { /* code */ }

2. IF - ELSE STATEMENT : if (condition) { /* code1 */ }
else { /* code2 */
}

3. IF - ELSE IF - ELSE STATEMENT : if (condition1) { /* code1 */ }
else if (condition2) { /* code2 */
}
else { /* code3 */
}

4. NESTED IF : if (condition1) {
  if (condition2) { /* code */
  }
}

5. SWITCH STATEMENT : switch (expression) {
case value1: /* code */;
  break;
case value2: /* code */;
  break;
default: /* code */;
}

== == == == == == == == == == == == == == == == == == == == == == == == == == ==
    == == == == == == == == == == == == ==
    */

#include <iostream>
        using namespace std;

int main() {
  cout << "=== IF-ELSE AND SWITCH STATEMENTS ===" << endl << endl;

  // ======================= SIMPLE IF =======================
  cout << "1. SIMPLE IF STATEMENT:" << endl;

  int age = 20;
  if (age >= 18) {
    cout << "You are an adult" << endl;
  }

  int score = 40;
  if (score >= 60) {
    cout << "You passed" << endl;
  }
  if (score < 60) {
    cout << "You failed" << endl;
  }

  // ======================= IF-ELSE =======================
  cout << endl << "2. IF-ELSE STATEMENT:" << endl;

  int number = 15;
  if (number % 2 == 0) {
    cout << number << " is even" << endl;
  } else {
    cout << number << " is odd" << endl;
  }

  // ======================= IF-ELSE IF-ELSE =======================
  cout << endl << "3. IF-ELSE IF-ELSE STATEMENT:" << endl;

  int marks = 85;
  if (marks >= 90) {
    cout << "Grade: A+" << endl;
  } else if (marks >= 80) {
    cout << "Grade: A" << endl;
  } else if (marks >= 70) {
    cout << "Grade: B" << endl;
  } else if (marks >= 60) {
    cout << "Grade: C" << endl;
  } else {
    cout << "Grade: F (Failed)" << endl;
  }

  // ======================= NESTED IF =======================
  cout << endl << "4. NESTED IF STATEMENTS:" << endl;

  int age2 = 25;
  bool has_license = true;

  if (age2 >= 18) {
    if (has_license) {
      cout << "You can drive" << endl;
    } else {
      cout << "You need a license to drive" << endl;
    }
  } else {
    cout << "You are too young to drive" << endl;
  }

  // ======================= SWITCH STATEMENT =======================
  cout << endl << "5. SWITCH STATEMENT:" << endl;

  int day = 3;
  string day_name;

  switch (day) {
  case 1:
    day_name = "Monday";
    break;
  case 2:
    day_name = "Tuesday";
    break;
  case 3:
    day_name = "Wednesday";
    break;
  case 4:
    day_name = "Thursday";
    break;
  case 5:
    day_name = "Friday";
    break;
  case 6:
    day_name = "Saturday";
    break;
  case 7:
    day_name = "Sunday";
    break;
  default:
    day_name = "Invalid day";
  }

  cout << "Day " << day << " is " << day_name << endl;

  // ======================= SWITCH WITH MULTIPLE CASES =======================
  cout << endl << "6. SWITCH WITH MULTIPLE CASES (Fall-through):" << endl;

  char grade = 'B';

  switch (grade) {
  case 'A':
  case 'B':
    cout << "Good grade!" << endl;
    break;
  case 'C':
    cout << "Average grade" << endl;
    break;
  case 'D':
  case 'F':
    cout << "Need improvement" << endl;
    break;
  default:
    cout << "Invalid grade" << endl;
  }

  // ======================= SWITCH WITH STRINGS =======================
  cout << endl << "7. SWITCH STATEMENT WITH STRINGS:" << endl;

  string fruit = "apple";

  if (fruit == "apple") {
    cout << "Price: $1.5" << endl;
  } else if (fruit == "banana") {
    cout << "Price: $0.5" << endl;
  } else if (fruit == "orange") {
    cout << "Price: $1.0" << endl;
  } else {
    cout << "Fruit not found" << endl;
  }

  // ======================= REAL-WORLD EXAMPLE: CALCULATOR
  // =======================
  cout << endl << "8. REAL-WORLD EXAMPLE (Calculator):" << endl;

  int num1 = 10, num2 = 5;
  char operation = '+';
  int result;

  switch (operation) {
  case '+':
    result = num1 + num2;
    cout << num1 << " + " << num2 << " = " << result << endl;
    break;
  case '-':
    result = num1 - num2;
    cout << num1 << " - " << num2 << " = " << result << endl;
    break;
  case '*':
    result = num1 * num2;
    cout << num1 << " * " << num2 << " = " << result << endl;
    break;
  case '/':
    if (num2 != 0) {
      result = num1 / num2;
      cout << num1 << " / " << num2 << " = " << result << endl;
    } else {
      cout << "Error: Division by zero" << endl;
    }
    break;
  default:
    cout << "Unknown operation" << endl;
  }

  // ======================= REAL-WORLD EXAMPLE: LOGIN SYSTEM
  // =======================
  cout << endl << "9. REAL-WORLD EXAMPLE (Login System):" << endl;

  string username = "admin";
  string password = "password123";
  string input_user = "admin";
  string input_pass = "password123";

  if (input_user == username) {
    if (input_pass == password) {
      cout << "Login successful!" << endl;
    } else {
      cout << "Wrong password" << endl;
    }
  } else {
    cout << "Username not found" << endl;
  }

  return 0;
}

/*
OUTPUT:
=== IF-ELSE AND SWITCH STATEMENTS ===

1. SIMPLE IF STATEMENT:
You are an adult
You failed

2. IF-ELSE STATEMENT:
15 is odd

3. IF-ELSE IF-ELSE STATEMENT:
Grade: A

4. NESTED IF STATEMENTS:
You can drive

5. SWITCH STATEMENT:
Day 3 is Wednesday

6. SWITCH WITH MULTIPLE CASES (Fall-through):
Good grade!

7. SWITCH STATEMENT WITH STRINGS:
Price: $1.5

8. REAL-WORLD EXAMPLE (Calculator):
10 + 5 = 15

9. REAL-WORLD EXAMPLE (Login System):
Login successful!

================================================================================
KEY CONCEPTS
================================================================================

1. IF-ELSE VS SWITCH:
   - Use IF-ELSE for range conditions (>, <, >=, <=)
   - Use SWITCH for specific values (==)

2. BREAK STATEMENT IN SWITCH:
   - Important to prevent fall-through
   - Without break, execution continues to next case

3. DEFAULT CASE:
   - Executed when no case matches
   - Similar to else in if-else

4. NESTED CONDITIONS:
   - One condition inside another
   - Use for complex logic
   - Too many levels makes code hard to read

5. CURLY BRACES:
   - Optional for single statement but recommended for clarity
   - Required for multiple statements

================================================================================
PRACTICE EXERCISES
================================================================================

1. Create a program to determine if a number is positive, negative, or zero

2. Create a system to check user eligibility for voting, driving, and drinking

3. Create a menu-driven program using switch statement

4. Create a program that shows ticket prices based on age group

5. Create a simple ATM menu system (Withdraw, Deposit, Check Balance, Exit)

================================================================================
*/
