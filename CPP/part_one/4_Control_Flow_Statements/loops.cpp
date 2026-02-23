/*
================================================================================
TOPIC 4: CONTROL FLOW STATEMENTS - PART 2: LOOPS
================================================================================

1. FOR LOOP:
   for (initialization; condition; increment/decrement) { /* code */ }

2. WHILE LOOP : while (condition) { /* code */ }

3. DO - WHILE LOOP : do { /* code */ }
while (condition)
  ;

4. BREAK STATEMENT : Exits the loop immediately

                     5. CONTINUE STATEMENT : Skips current iteration,
                                             goes to next iteration

                                                 6. NESTED LOOPS
    : Loop inside another loop

      == ==
      == == == == == == == == == == == == == == == == == == == == == == == == ==
      == == == == == == == == == == == == ==
      */

#include <iostream>
          using namespace std;

int main() {
  cout << "=== LOOP STATEMENTS ===" << endl << endl;

  // ======================= FOR LOOP =======================
  cout << "1. FOR LOOP - PRINTING NUMBERS 1 TO 5:" << endl;
  for (int i = 1; i <= 5; i++) {
    cout << i << " ";
  }
  cout << endl;

  // ======================= FOR LOOP - COUNTING DOWN =======================
  cout << endl << "2. FOR LOOP - COUNTING DOWN FROM 5 TO 1:" << endl;
  for (int i = 5; i >= 1; i--) {
    cout << i << " ";
  }
  cout << endl;

  // ======================= FOR LOOP - MULTIPLICATION TABLE
  // =======================
  cout << endl << "3. FOR LOOP - MULTIPLICATION TABLE OF 5:" << endl;
  for (int i = 1; i <= 10; i++) {
    cout << "5 * " << i << " = " << (5 * i) << endl;
  }

  // ======================= FOR LOOP - SUM OF NUMBERS =======================
  cout << endl << "4. FOR LOOP - SUM OF NUMBERS 1 TO 10:" << endl;
  int sum = 0;
  for (int i = 1; i <= 10; i++) {
    sum += i;
  }
  cout << "Sum = " << sum << endl;

  // ======================= WHILE LOOP =======================
  cout << endl << "5. WHILE LOOP - PRINTING NUMBERS 1 TO 5:" << endl;
  int counter = 1;
  while (counter <= 5) {
    cout << counter << " ";
    counter++;
  }
  cout << endl;

  // ======================= WHILE LOOP - USER INPUT =======================
  cout << endl << "6. WHILE LOOP - SUM UNTIL USER ENTERS 0:" << endl;
  int num = 1, total = 0, count = 0;
  cout << "Enter numbers (0 to stop): ";

  // Simulating input: 5, 10, 15, 0
  while (num != 0) {
    if (count == 0)
      num = 5;
    else if (count == 1)
      num = 10;
    else if (count == 2)
      num = 15;
    else
      num = 0;

    cout << num << " ";
    total += num;
    count++;
  }
  cout << endl << "Total = " << total << endl;

  // ======================= DO-WHILE LOOP =======================
  cout << endl << "7. DO-WHILE LOOP - PRINT NUMBERS 1 TO 5:" << endl;
  int i = 1;
  do {
    cout << i << " ";
    i++;
  } while (i <= 5);
  cout << endl;

  // ======================= DO-WHILE - MENU =======================
  cout << endl << "8. DO-WHILE LOOP - MENU (Simulated):" << endl;
  int choice = 1;
  int menu_iterations = 0;
  do {
    cout << "Menu: 1. Start  2. Stop  Enter choice: ";
    if (menu_iterations == 0)
      choice = 1;
    else if (menu_iterations == 1)
      choice = 1;
    else
      choice = 2;

    cout << choice << endl;

    switch (choice) {
    case 1:
      cout << "Game started!" << endl;
      break;
    case 2:
      cout << "Game stopped!" << endl;
      break;
    default:
      cout << "Invalid choice" << endl;
    }
    menu_iterations++;
  } while (choice != 2 && menu_iterations < 2);

  // ======================= BREAK STATEMENT =======================
  cout << endl << "9. BREAK STATEMENT - FIND NUMBER 7:" << endl;
  for (int i = 1; i <= 10; i++) {
    if (i == 7) {
      cout << "Found 7!" << endl;
      break;
    }
    cout << i << " ";
  }
  cout << endl;

  // ======================= CONTINUE STATEMENT =======================
  cout << endl << "10. CONTINUE STATEMENT - SKIP EVEN NUMBERS:" << endl;
  for (int i = 1; i <= 10; i++) {
    if (i % 2 == 0) {
      continue; // Skip even numbers
    }
    cout << i << " ";
  }
  cout << endl;

  // ======================= NESTED LOOPS - MULTIPLICATION TABLE
  // =======================
  cout << endl
       << "11. NESTED LOOPS - MULTIPLICATION TABLE (2x2 to 4x4):" << endl;
  for (int row = 2; row <= 4; row++) {
    for (int col = 2; col <= 4; col++) {
      cout << row << "*" << col << "=" << (row * col) << "  ";
    }
    cout << endl;
  }

  // ======================= NESTED LOOPS - PYRAMID =======================
  cout << endl << "12. NESTED LOOPS - PYRAMID PATTERN:" << endl;
  int n = 5;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      cout << "* ";
    }
    cout << endl;
  }

  // ======================= NESTED LOOPS - DIAMOND =======================
  cout << endl << "13. NESTED LOOPS - DIAMOND PATTERN:" << endl;
  int size = 3;
  for (int i = 1; i <= size; i++) {
    for (int j = 1; j <= size - i; j++)
      cout << " ";
    for (int j = 1; j <= 2 * i - 1; j++)
      cout << "*";
    cout << endl;
  }

  // ======================= REAL-WORLD EXAMPLE - FACTORIAL
  // =======================
  cout << endl << "14. REAL-WORLD EXAMPLE - FACTORIAL OF 5:" << endl;
  int num_fact = 5;
  int factorial = 1;
  for (int i = 1; i <= num_fact; i++) {
    factorial *= i;
  }
  cout << "5! = " << factorial << endl;

  // ======================= REAL-WORLD EXAMPLE - PRIME CHECK
  // =======================
  cout << endl << "15. REAL-WORLD EXAMPLE - CHECK IF NUMBER IS PRIME:" << endl;
  int num_check = 17;
  bool is_prime = true;

  if (num_check < 2) {
    is_prime = false;
  } else {
    for (int i = 2; i * i <= num_check; i++) {
      if (num_check % i == 0) {
        is_prime = false;
        break;
      }
    }
  }

  cout << num_check << " is " << (is_prime ? "Prime" : "Not Prime") << endl;

  return 0;
}

/*
OUTPUT:
=== LOOP STATEMENTS ===

1. FOR LOOP - PRINTING NUMBERS 1 TO 5:
1 2 3 4 5

2. FOR LOOP - COUNTING DOWN FROM 5 TO 1:
5 4 3 2 1

3. FOR LOOP - MULTIPLICATION TABLE OF 5:
5 * 1 = 5
5 * 2 = 10
5 * 3 = 15
5 * 4 = 20
5 * 5 = 25
5 * 6 = 30
5 * 7 = 35
5 * 8 = 40
5 * 9 = 45
5 * 10 = 50

4. FOR LOOP - SUM OF NUMBERS 1 TO 10:
Sum = 55

5. WHILE LOOP - PRINTING NUMBERS 1 TO 5:
1 2 3 4 5

6. WHILE LOOP - SUM UNTIL USER ENTERS 0:
Enter numbers (0 to stop): 5 10 15 0
Total = 30

7. DO-WHILE LOOP - PRINT NUMBERS 1 TO 5:
1 2 3 4 5

8. DO-WHILE LOOP - MENU (Simulated):
Menu: 1. Start  2. Stop  Enter choice: 1
Game started!
Menu: 1. Start  2. Stop  Enter choice: 2
Game stopped!

9. BREAK STATEMENT - FIND NUMBER 7:
1 2 3 4 5 6 Found 7!

10. CONTINUE STATEMENT - SKIP EVEN NUMBERS:
1 3 5 7 9

11. NESTED LOOPS - MULTIPLICATION TABLE (2x2 to 4x4):
2*2=4  2*3=6  2*4=8
3*2=6  3*3=9  3*4=12
4*2=8  4*3=12  4*4=16

12. NESTED LOOPS - PYRAMID PATTERN:
*
* *
* * *
* * * *
* * * * *

13. NESTED LOOPS - DIAMOND PATTERN:
  *
 ***
*****

14. REAL-WORLD EXAMPLE - FACTORIAL OF 5:
5! = 120

15. REAL-WORLD EXAMPLE - CHECK IF NUMBER IS PRIME:
17 is Prime

================================================================================
LOOP COMPARISON
================================================================================

FOR LOOP:
- When you know exact number of iterations
- Counter-based repetition
- Example: Print 1 to 10

WHILE LOOP:
- When condition is unknown initially
- Checks condition before execution
- Example: User input until sentinel value

DO-WHILE LOOP:
- Executes at least once
- Checks condition after execution
- Example: Menu systems

================================================================================
PRACTICE EXERCISES
================================================================================

1. Print all even numbers from 1 to 20

2. Find sum of first 15 natural numbers

3. Create multiplication table for any number

4. Find factorial of a number

5. Print first 10 Fibonacci numbers

6. Create a number guessing game with loops

7. Print pattern of stars

8. Find GCD of two numbers

9. Count digits in a number

10. Reverse digits of a number

================================================================================
*/
