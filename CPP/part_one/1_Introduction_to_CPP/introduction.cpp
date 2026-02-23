/*
================================================================================
TOPIC 1: INTRODUCTION TO C++
================================================================================

1. History and Evolution of C++
   - C++ was created by Bjarne Stroustrup in 1985
   - Originally called "C with Classes"
   - First standardized in 1998 (C++98)
   - Major versions: C++11, C++14, C++17, C++20, C++23
   - Combines procedural, object-oriented, and functional programming

2. Setting up Development Environment
   - Compilers: GCC (g++), Clang (clang++), MSVC (Visual Studio)
   - IDEs: Visual Studio, CLion, Code::Blocks, VS Code
   - Online: Replit, Godbolt, LeetCode

3. Basic Syntax and Structure
   - Include libraries at the top
   - Using namespace std or std:: prefix
   - Main function: entry point of program
   - Statements end with semicolon (;)
   - Curly braces {} for code blocks

4. Hello World Program
   - First program to learn any language
   - Demonstrates basic I/O

================================================================================
*/

#include <iostream>
using namespace std;

int main() {
  // Hello World - The simplest C++ program
  cout << "Hello, World!" << endl;

  return 0;
}

/*
OUTPUT:
Hello, World!

EXPLANATION:
- #include <iostream>: Includes input-output stream library
- using namespace std;: Allows us to use cout without std:: prefix
- int main(): Main function - starting point of program
- cout << "Hello, World!": Outputs text to console
- endl: Ends line and flushes buffer (equivalent to "\n")
- return 0;: Returns success status (0 = success)

================================================================================
KEY CONCEPTS
================================================================================

1. DIRECTIVES:
   #include <iostream>     // Include library
   using namespace std;    // Use standard namespace

2. IOSTREAM LIBRARY:
   - cin: Input stream (for reading input)
   - cout: Output stream (for printing output)
   - endl: Newline character

3. PROGRAM STRUCTURE:
   #include <necessary_headers>
   using namespace std;

   int main() {
       // Your code here
       return 0;
   }

4. COMMENTS:
   // Single line comment
   /* Multi-line
      comment */

== == == == == == == == == == == == == == == == == == == == == == == == == == ==
    == == == == == == == == == == == == == EXAMPLES OF BASIC I / O == == == ==
    == == == == == == == == == == == == == == == == == == == == == == == == ==
    == == == == == == == == == == ==
    */

        /*
        Example 1: Basic Input and Output
        */
        void example_basic_io() {
  cout << "Welcome to C++!" << endl;
  cout << "Learning is fun" << endl;

  // Multiple outputs in one line
  cout << "2 + 3 = " << (2 + 3) << endl;
}

/*
Example 2: Reading User Input
*/
void example_input() {
  int number;
  cout << "Enter a number: ";
  cin >> number; // Read integer from user
  cout << "You entered: " << number << endl;
}

/*
Example 3: Multiple Variables Input
*/
void example_multiple_input() {
  int age;
  double height;
  string name;

  cout << "Enter your name: ";
  cin >> name;

  cout << "Enter your age: ";
  cin >> age;

  cout << "Enter your height: ";
  cin >> height;

  cout << "\nYour Information:" << endl;
  cout << "Name: " << name << endl;
  cout << "Age: " << age << endl;
  cout << "Height: " << height << " cm" << endl;
}

/*
Example 4: Basic Calculation Program
*/
void example_calculation() {
  int a, b;

  cout << "Enter first number: ";
  cin >> a;

  cout << "Enter second number: ";
  cin >> b;

  cout << "\nResults:" << endl;
  cout << "Addition: " << (a + b) << endl;
  cout << "Subtraction: " << (a - b) << endl;
  cout << "Multiplication: " << (a * b) << endl;
  cout << "Division: " << (a / b) << endl;
}

/*
================================================================================
COMPILATION AND EXECUTION
================================================================================

On Linux/Mac:
    g++ introduction.cpp -o introduction
    ./introduction

On Windows (with MinGW):
    g++ introduction.cpp -o introduction.exe
    introduction.exe

On Windows (with Visual Studio):
    cl introduction.cpp
    introduction.exe

Using online compiler (Replit, Godbolt, etc.):
    - Paste code
    - Click Run
    - See output

================================================================================
BEST PRACTICES
================================================================================

1. Always include required headers
2. Use meaningful variable names
3. Add comments to explain code
4. Use proper indentation (4 spaces or 1 tab)
5. Return 0 from main() to indicate successful execution
6. Use endl or "\n" to print newlines
7. Always close opened resources (streams, files)

================================================================================
COMMON ERRORS AND SOLUTIONS
================================================================================

Error: "cout: command not found"
Solution: Use std::cout instead of cout, or use "using namespace std;"

Error: "expected primary-expression before 'int'"
Solution: Declare variables before using them

Error: "return type of 'main' is not 'int'"
Solution: Make sure main() returns int

Error: "undefined reference to 'main'"
Solution: You must have a main() function in your program

================================================================================
*/

/*
PRACTICE EXERCISES:

1. Create a program that prints "C++ is awesome!" on three separate lines

2. Create a program that asks user for their name and prints "Hello, [name]!"

3. Create a program that reads two numbers and prints their sum

4. Create a program that prints a simple ASCII art (like a triangle or pyramid)

5. Modify the Hello World program to include your name and date

================================================================================
*/
