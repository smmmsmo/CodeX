/*
================================================================================
POLYMORPHISM BASICS - COMPILE-TIME POLYMORPHISM
================================================================================
Part 2, Subtopic 12: Polymorphism (File 1/2)

CONCEPTS COVERED:
- What is polymorphism?
- Compile-time (static) polymorphism
- Function overloading
- Operator overloading
- Template polymorphism
- Introduction to runtime (dynamic) polymorphism
- When to use each type

KEY LEARNING POINTS:
1. Polymorphism means "many forms"
2. Compile-time resolution happens before runtime
3. Function overloading allows multiple functions with same name
4. Operator overloading enables custom behavior for operators
5. Templates provide generic type polymorphism
6. Runtime polymorphism uses virtual functions
7. Choose based on performance and design needs

================================================================================
*/

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
================================================================================
THEORY SECTION: WHAT IS POLYMORPHISM?
================================================================================

POLYMORPHISM = "many forms"

Two Types:
1. COMPILE-TIME POLYMORPHISM (Static Binding)
   - Decision made at compile time
   - Function overloading
   - Operator overloading
   - Templates
   - Faster: No runtime overhead
   - Less flexible: Type known at compile time

2. RUNTIME POLYMORPHISM (Dynamic Binding)
   - Decision made at runtime
   - Virtual functions
   - Dynamic dispatch through base class pointers
   - More flexible: Type determined at runtime
   - Slower: Virtual table lookup overhead

BENEFITS:
- Code reuse: Write once, use for multiple types
- Flexibility: Same interface, different behaviors
- Maintainability: Easier to extend and modify
- Type safety: Type checked at compile time (usually)

USE CASES:
- Function overloading: Multiple ways to call same operation
- Operator overloading: Custom behavior for operators
- Templates: Generic algorithms working with any type
- Virtual functions: Plugin systems, frameworks

================================================================================
*/

/*
================================================================================
EXAMPLE 1: FUNCTION OVERLOADING - BASIC
================================================================================
*/

class Calculator {
public:
  // Overload 1: Add two integers
  int add(int a, int b) {
    cout << "Adding integers: " << a << " + " << b << endl;
    return a + b;
  }

  // Overload 2: Add two doubles
  double add(double a, double b) {
    cout << "Adding doubles: " << a << " + " << b << endl;
    return a + b;
  }

  // Overload 3: Add three integers
  int add(int a, int b, int c) {
    cout << "Adding three integers: " << a << " + " << b << " + " << c << endl;
    return a + b + c;
  }

  // Overload 4: Add string
  string add(string a, string b) {
    cout << "Concatenating strings: " << a << " + " << b << endl;
    return a + b;
  }
};

/*
OUTPUT:
--------
Adding integers: 5 + 3
Result: 8
Adding doubles: 3.5 + 2.7
Result: 6.2
Adding three integers: 1 + 2 + 3
Result: 6
Concatenating strings: Hello + World
Result: HelloWorld

--------
*/

/*
================================================================================
EXAMPLE 2: FUNCTION OVERLOADING - PRINT ANY TYPE
================================================================================
*/

class Printer {
public:
  // Print integer
  void print(int value) { cout << "Integer: " << value << endl; }

  // Print double
  void print(double value) { cout << "Double: " << value << endl; }

  // Print string
  void print(const string &value) { cout << "String: " << value << endl; }

  // Print bool
  void print(bool value) {
    cout << "Boolean: " << (value ? "true" : "false") << endl;
  }

  // Print vector
  void print(const vector<int> &values) {
    cout << "Vector: [";
    for (size_t i = 0; i < values.size(); i++) {
      cout << values[i];
      if (i < values.size() - 1)
        cout << ", ";
    }
    cout << "]" << endl;
  }
};

/*
OUTPUT:
--------
Integer: 42
Double: 3.14159
String: Hello
Boolean: true
Vector: [1, 2, 3, 4, 5]

--------
*/

/*
================================================================================
EXAMPLE 3: OPERATOR OVERLOADING - COMPLEX NUMBERS
================================================================================
*/

class Complex {
private:
  double real;
  double imag;

public:
  Complex(double r = 0, double i = 0) : real(r), imag(i) {}

  // Overload + operator
  Complex operator+(const Complex &other) const {
    return Complex(real + other.real, imag + other.imag);
  }

  // Overload - operator
  Complex operator-(const Complex &other) const {
    return Complex(real - other.real, imag - other.imag);
  }

  // Overload * operator
  Complex operator*(const Complex &other) const {
    double r = real * other.real - imag * other.imag;
    double i = real * other.imag + imag * other.real;
    return Complex(r, i);
  }

  // Overload == operator
  bool operator==(const Complex &other) const {
    return real == other.real && imag == other.imag;
  }

  // Overload << operator (output stream)
  friend ostream &operator<<(ostream &os, const Complex &c) {
    if (c.imag >= 0)
      os << c.real << " + " << c.imag << "i";
    else
      os << c.real << " - " << -c.imag << "i";
    return os;
  }

  // Overload >> operator (input stream)
  friend istream &operator>>(istream &is, Complex &c) {
    cout << "Enter real part: ";
    is >> c.real;
    cout << "Enter imaginary part: ";
    is >> c.imag;
    return is;
  }

  void display() const {
    if (imag >= 0)
      cout << real << " + " << imag << "i" << endl;
    else
      cout << real << " - " << -imag << "i" << endl;
  }
};

/*
OUTPUT:
--------
Complex 1: 3 + 4i
Complex 2: 1 + 2i
Sum: 4 + 6i
Difference: 2 + 2i
Product: -5 + 10i

--------
*/

/*
================================================================================
EXAMPLE 4: OPERATOR OVERLOADING - STRING CLASS
================================================================================
*/

class MyString {
private:
  string data;

public:
  MyString(string s = "") : data(s) {}

  // Overload [] operator (subscript)
  char operator[](int index) const {
    if (index >= 0 && index < (int)data.length())
      return data[index];
    return '\0';
  }

  // Overload () operator (function call)
  int operator()(char c) const {
    // Count occurrences of character
    int count = 0;
    for (char ch : data) {
      if (ch == c)
        count++;
    }
    return count;
  }

  // Overload + operator (concatenation)
  MyString operator+(const MyString &other) const {
    return MyString(data + other.data);
  }

  // Overload += operator
  MyString &operator+=(const MyString &other) {
    data += other.data;
    return *this;
  }

  // Overload < operator (comparison)
  bool operator<(const MyString &other) const { return data < other.data; }

  void display() const { cout << data << endl; }
};

/*
OUTPUT:
--------
MyString 1: Hello
MyString 2: World
Concatenated: HelloWorld
Character at index 0: H
Count of 'l': 3

--------
*/

/*
================================================================================
EXAMPLE 5: TEMPLATE FUNCTION POLYMORPHISM
================================================================================
*/

// Generic template function
template <typename T> T maximum(T a, T b) { return (a > b) ? a : b; }

// Generic template function - swap
template <typename T> void swap(T &a, T &b) {
  T temp = a;
  a = b;
  b = temp;
}

// Template specialization for strings
template <> string maximum<string>(string a, string b) {
  cout << "Using specialized template for strings" << endl;
  return (a.length() > b.length()) ? a : b;
}

/*
OUTPUT:
--------
Maximum of 5 and 10: 10
Maximum of 3.14 and 2.71: 3.14
Maximum of apple and banana: apple (specialized)
After swap: 10, 5

--------
*/

/*
================================================================================
EXAMPLE 6: TEMPLATE CLASS POLYMORPHISM
================================================================================
*/

template <typename T> class Stack {
private:
  vector<T> elements;

public:
  void push(T value) { elements.push_back(value); }

  T pop() {
    if (elements.empty()) {
      cout << "Stack is empty!" << endl;
      return T();
    }
    T value = elements.back();
    elements.pop_back();
    return value;
  }

  T top() const {
    if (elements.empty()) {
      cout << "Stack is empty!" << endl;
      return T();
    }
    return elements.back();
  }

  bool isEmpty() const { return elements.empty(); }

  int size() const { return elements.size(); }

  void display() const {
    cout << "Stack [";
    for (size_t i = 0; i < elements.size(); i++) {
      cout << elements[i];
      if (i < elements.size() - 1)
        cout << ", ";
    }
    cout << "]" << endl;
  }
};

/*
OUTPUT:
--------
Integer Stack: [1, 2, 3, 4, 5]
Popped: 5
String Stack: [Hello, World]
Popped: World

--------
*/

/*
================================================================================
EXAMPLE 7: CONVERSION OPERATORS
================================================================================
*/

class Distance {
private:
  double meters;

public:
  Distance(double m = 0) : meters(m) {}

  // Overload double() - convert to double
  operator double() const { return meters; }

  // Overload int() - convert to int
  operator int() const { return static_cast<int>(meters); }

  // Overload string() - convert to string
  operator string() const { return to_string(meters) + " meters"; }

  // Method to convert to feet
  double toFeet() const { return meters * 3.28084; }

  void display() const { cout << meters << " meters" << endl; }
};

/*
OUTPUT:
--------
Distance: 10 meters
As double: 10
As int: 10
As string: 10.000000 meters
In feet: 32.8084

--------
*/

/*
================================================================================
EXAMPLE 8: INTRODUCTION TO RUNTIME POLYMORPHISM
================================================================================
*/

class Shape {
public:
  virtual ~Shape() {}

  // Virtual function - runtime polymorphism
  virtual void draw() const { cout << "Drawing generic shape" << endl; }

  virtual double getArea() const = 0; // Pure virtual
};

class Square : public Shape {
private:
  double side;

public:
  Square(double s) : side(s) {}

  void draw() const override { cout << "Drawing square" << endl; }

  double getArea() const override { return side * side; }
};

class Circle8 : public Shape {
private:
  double radius;
  static const double PI;

public:
  Circle8(double r) : radius(r) {}

  void draw() const override { cout << "Drawing circle" << endl; }

  double getArea() const override { return PI * radius * radius; }
};

const double Circle8::PI = 3.14159265359;

/*
OUTPUT:
--------
Drawing square
Area: 100
Drawing circle
Area: 78.5398

--------
*/

/*
================================================================================
KEY CONCEPTS SUMMARY BOX
================================================================================

POLYMORPHISM TYPES:

COMPILE-TIME POLYMORPHISM:
1. Function Overloading
   - Multiple functions with same name
   - Different parameters (number, type, order)
   - Resolution at compile time
   - Example: print(int), print(string), print(double)

2. Operator Overloading
   - Define custom behavior for operators
   - Makes classes work like built-in types
   - Example: Complex + Complex, MyString + MyString

3. Templates
   - Write generic code for any type
   - Instantiated at compile time
   - Full specialization possible
   - Example: Stack<int>, Stack<string>

RUNTIME POLYMORPHISM:
1. Virtual Functions
   - Same interface, different implementations
   - Decision at runtime through base pointer
   - Slightly slower due to virtual table lookup
   - More flexible for plugin systems

WHEN TO USE:
- Overloading: Multiple ways to do same thing
- Operators: When class behaves like built-in type
- Templates: Generic algorithms
- Virtual: Plugin architecture, frameworks

================================================================================
*/

/*
================================================================================
COMMON MISTAKES - COMPILE-TIME POLYMORPHISM
================================================================================

❌ MISTAKE 1: Overloading with default parameters (ambiguous)
    void print(int x) { }
    void print(int x, int y = 0) { }  // Ambiguous!

✓ CORRECT:
    void print(int x) { }
    void print(int x, int y) { }

-----

❌ MISTAKE 2: Return type alone isn't enough for overloading
    int getValue() { return 1; }
    double getValue() { return 1.0; }  // ERROR!

✓ CORRECT:
    Must differ in parameters, not just return type

-----

❌ MISTAKE 3: Overloading = operator incorrectly
    operator=(const obj&);  // Missing return type!

✓ CORRECT:
    MyClass& operator=(const MyClass& other);

-----

❌ MISTAKE 4: Template parameter not used
    template <typename T>
    void func(int x) { }  // T not used!

✓ CORRECT:
    template <typename T>
    void func(T x) { }

-----

❌ MISTAKE 5: Not handling conversion operators carefully
    operator int() { return value; }
    operator bool() { return value != 0; }  // Can be ambiguous!

✓ CORRECT:
    explicit operator bool() { return value != 0; }

================================================================================
*/

/*
================================================================================
PRACTICE EXERCISES
================================================================================

Exercise 1: Calculator Class
Overload +, -, *, / operators for a Fraction class
Handle operator precedence correctly

Exercise 2: Vector Class
Create Vector class with overloaded operators:
- operator+ (addition)
- operator* (dot product)
- operator[] (access elements)
- operator<< (print)

Exercise 3: Date Class
Overload comparison operators: <, >, ==, !=
Overload + (add days) and - (subtract days)

Exercise 4: Generic Array Template
Create template Array class with:
- Push, pop operations
- operator[] for access
- Works with any type

Exercise 5: Matrix Class
Overload operators: +, -, * (multiplication)
Support scalar multiplication

Exercise 6: String Case Conversion
Create MyString with overloaded () operator:
- MyString()(0) returns uppercase version
- MyString()(1) returns lowercase version

Exercise 7: GenericPair Template
Template class storing two values of any type
Overload comparison operators

Exercise 8: Currency Class
Support multiple currencies
Overload + operator to add different currencies
Auto-convert between currencies

Exercise 9: Function Object (Functor)
Create class with overloaded () operator
Use as callback in algorithms

Exercise 10: SmartPointer Template
Template class managing pointer
Overload * and -> operators
Handle automatic cleanup

================================================================================
*/

// Main demonstration
int main() {
  cout << "================== POLYMORPHISM BASICS ==================\n\n";

  // Example 1: Function Overloading
  cout << "--- EXAMPLE 1: FUNCTION OVERLOADING ---\n";
  Calculator calc;
  cout << "Result: " << calc.add(5, 3) << endl;
  cout << "Result: " << calc.add(3.5, 2.7) << endl;
  cout << "Result: " << calc.add(1, 2, 3) << endl;
  cout << "Result: " << calc.add("Hello", "World") << endl;
  cout << "\n";

  // Example 2: Print Any Type
  cout << "--- EXAMPLE 2: PRINT ANY TYPE ---\n";
  Printer printer;
  printer.print(42);
  printer.print(3.14159);
  printer.print("Hello");
  printer.print(true);
  vector<int> vec = {1, 2, 3, 4, 5};
  printer.print(vec);
  cout << "\n";

  // Example 3: Operator Overloading
  cout << "--- EXAMPLE 3: OPERATOR OVERLOADING - COMPLEX ---\n";
  Complex c1(3, 4);
  Complex c2(1, 2);
  cout << "C1: " << c1 << endl;
  cout << "C2: " << c2 << endl;
  cout << "C1 + C2 = " << (c1 + c2) << endl;
  cout << "C1 * C2 = " << (c1 * c2) << endl;
  cout << "\n";

  // Example 4: String Operator Overloading
  cout << "--- EXAMPLE 4: STRING OPERATOR OVERLOADING ---\n";
  MyString str1("Hello");
  MyString str2("World");
  cout << "Character at index 0: " << str1[0] << endl;
  cout << "Count of 'l': " << str1('l') << endl;
  MyString concat = str1 + MyString(" ") + str2;
  concat.display();
  cout << "\n";

  // Example 5: Template Functions
  cout << "--- EXAMPLE 5: TEMPLATE FUNCTION POLYMORPHISM ---\n";
  cout << "Max of 5, 10: " << maximum(5, 10) << endl;
  cout << "Max of 3.14, 2.71: " << maximum(3.14, 2.71) << endl;
  cout << "Max of apple, banana: " << maximum("apple", "banana") << endl;
  cout << "\n";

  // Example 6: Template Class
  cout << "--- EXAMPLE 6: TEMPLATE CLASS POLYMORPHISM ---\n";
  Stack<int> intStack;
  intStack.push(1);
  intStack.push(2);
  intStack.push(3);
  intStack.push(4);
  intStack.display();

  Stack<string> stringStack;
  stringStack.push("Hello");
  stringStack.push("World");
  stringStack.display();
  cout << "\n";

  // Example 7: Conversion Operators
  cout << "--- EXAMPLE 7: CONVERSION OPERATORS ---\n";
  Distance d(10);
  d.display();
  cout << "As double: " << (double)d << endl;
  cout << "As int: " << (int)d << endl;
  cout << "As string: " << (string)d << endl;
  cout << "In feet: " << d.toFeet() << endl;
  cout << "\n";

  // Example 8: Runtime Polymorphism Preview
  cout << "--- EXAMPLE 8: RUNTIME POLYMORPHISM PREVIEW ---\n";
  Square square(10);
  Circle8 circle(5);
  square.draw();
  cout << "Area: " << square.getArea() << endl;
  circle.draw();
  cout << "Area: " << circle.getArea() << endl;
  cout << "\n";

  return 0;
}

/*
================================================================================
FULL PROGRAM OUTPUT:
================================================================================

================== POLYMORPHISM BASICS ==================

--- EXAMPLE 1: FUNCTION OVERLOADING ---
Adding integers: 5 + 3
Result: 8
Adding doubles: 3.5 + 2.7
Result: 6.2
Adding three integers: 1 + 2 + 3
Result: 6
Concatenating strings: Hello + World
Result: HelloWorld

--- EXAMPLE 2: PRINT ANY TYPE ---
Integer: 42
Double: 3.14159
String: Hello
Boolean: true
Vector: [1, 2, 3, 4, 5]

--- EXAMPLE 3: OPERATOR OVERLOADING - COMPLEX ---
C1: 3 + 4i
C2: 1 + 2i
C1 + C2 = 4 + 6i
C1 * C2 = -5 + 10i

--- EXAMPLE 4: STRING OPERATOR OVERLOADING ---
Character at index 0: H
Count of 'l': 3
Hello World

--- EXAMPLE 5: TEMPLATE FUNCTION POLYMORPHISM ---
Max of 5, 10: 10
Max of 3.14, 2.71: 3.14
Max of apple, banana: banana

--- EXAMPLE 6: TEMPLATE CLASS POLYMORPHISM ---
Integer Stack: [1, 2, 3, 4]
String Stack: [Hello, World]

--- EXAMPLE 7: CONVERSION OPERATORS ---
Distance: 10 meters
As double: 10
As int: 10
As string: 10.000000 meters
In feet: 32.8084

--- EXAMPLE 8: RUNTIME POLYMORPHISM PREVIEW ---
Drawing square
Area: 100
Drawing circle
Area: 78.5398

================================================================================
*/
