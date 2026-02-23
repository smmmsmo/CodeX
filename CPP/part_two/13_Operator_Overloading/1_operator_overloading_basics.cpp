/*
================================================================================
OPERATOR OVERLOADING BASICS - MAKING CLASSES BEHAVE LIKE BUILT-IN TYPES
================================================================================
Part 2, Subtopic 13: Operator Overloading (File 1/2)

CONCEPTS COVERED:
- What is operator overloading?
- Arithmetic operator overloading (+, -, *, /)
- Comparison operator overloading (==, !=, <, >, <=, >=)
- Assignment operator overloading (=)
- Unary operator overloading (++, --, !, -)
- Subscript operator [] overloading
- Stream operators (<<, >>) overloading

KEY LEARNING POINTS:
1. Operator overloading makes classes intuitive to use
2. Most operators can be overloaded as member or friend functions
3. Some operators must be members (=, [], (), ->)
4. Maintain consistency with expected behavior
5. Use assignment operator for deep copying
6. Stream operators allow printing and input
7. Operator precedence cannot be changed

================================================================================
*/

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
================================================================================
THEORY SECTION: OPERATOR OVERLOADING
================================================================================

WHAT IS OPERATOR OVERLOADING?
- Defining custom behavior for operators
- Makes user-defined types work like built-in types
- Makes code more readable and intuitive
- Enables "natural" object manipulation

WHY OVERLOAD OPERATORS?
1. Intuitive Interface: Vector a + Vector b feels natural
2. Code Readability: Complex(3,4) + Complex(1,2) is clearer
3. Consistency: Objects behave similarly to built-in types
4. Less Code: No need for add(), subtract() methods

OPERATORS THAT CAN BE OVERLOADED:
- Arithmetic: +, -, *, /, %, +=, -=, *=, /=
- Comparison: ==, !=, <, >, <=, >=
- Unary: ++, --, +, -, !, ~
- Assignment: =
- Subscript: []
- Function call: ()
- Member access: ., ->
- Stream: <<, >>
- Pointer: *, &
- Type cast: (type)
- new, delete

OPERATORS THAT CANNOT BE OVERLOADED:
- Scope resolution: ::
- Member access: .
- Ternary: ?:
- Sizeof: sizeof
- Typeid: typeid

OVERLOADING AS MEMBER VS FRIEND:
Member function:
- Can access private/protected members
- this pointer automatically available
- Defined inside class

Friend function:
- Needs explicit parameter for left operand
- Good for symmetric operations
- Declared in class, defined outside

================================================================================
*/

/*
================================================================================
EXAMPLE 1: ARITHMETIC OPERATORS - VECTOR CLASS
================================================================================
*/

class Vector {
private:
  double x, y, z;

public:
  Vector(double x_ = 0, double y_ = 0, double z_ = 0) : x(x_), y(y_), z(z_) {}

  // Overload + operator (addition)
  Vector operator+(const Vector &other) const {
    return Vector(x + other.x, y + other.y, z + other.z);
  }

  // Overload - operator (subtraction)
  Vector operator-(const Vector &other) const {
    return Vector(x - other.x, y - other.y, z - other.z);
  }

  // Overload * operator (scalar multiplication)
  Vector operator*(double scalar) const {
    return Vector(x * scalar, y * scalar, z * scalar);
  }

  // Overload * operator (dot product) - friend version
  friend double operator*(const Vector &a, const Vector &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }

  // Overload / operator (scalar division)
  Vector operator/(double scalar) const {
    if (scalar != 0) {
      return Vector(x / scalar, y / scalar, z / scalar);
    }
    return Vector(0, 0, 0);
  }

  double magnitude() const { return sqrt(x * x + y * y + z * z); }

  void display() const { cout << "(" << x << ", " << y << ", " << z << ")"; }
};

/*
OUTPUT:
--------
V1: (3, 4, 0)
V2: (1, 2, 0)
V1 + V2: (4, 6, 0)
V1 - V2: (2, 2, 0)
V1 * 2: (6, 8, 0)
V1 . V2: 11
V1 / 2: (1.5, 2, 0)

--------
*/

/*
================================================================================
EXAMPLE 2: COMPARISON OPERATORS - STUDENT CLASS
================================================================================
*/

class Student {
private:
  string name;
  int rollNo;
  double gpa;

public:
  Student(string n = "", int r = 0, double g = 0.0)
      : name(n), rollNo(r), gpa(g) {}

  // Overload == operator
  bool operator==(const Student &other) const { return rollNo == other.rollNo; }

  // Overload != operator
  bool operator!=(const Student &other) const { return !(*this == other); }

  // Overload < operator (compare by GPA)
  bool operator<(const Student &other) const { return gpa < other.gpa; }

  // Overload > operator
  bool operator>(const Student &other) const { return gpa > other.gpa; }

  // Overload <= operator
  bool operator<=(const Student &other) const { return gpa <= other.gpa; }

  // Overload >= operator
  bool operator>=(const Student &other) const { return gpa >= other.gpa; }

  void display() const {
    cout << "Name: " << name << ", Roll: " << rollNo << ", GPA: " << gpa
         << endl;
  }
};

/*
OUTPUT:
--------
s1 == s2: 0 (false)
s1 < s2: 1 (true)
s2 > s1: 1 (true)

--------
*/

/*
================================================================================
EXAMPLE 3: ASSIGNMENT OPERATOR - PROPER DEEP COPYING
================================================================================
*/

class String {
private:
  char *data;
  int length;

public:
  // Constructor
  String(const char *str = "") {
    if (str == nullptr) {
      length = 0;
      data = new char[1];
      data[0] = '\0';
    } else {
      length = strlen(str);
      data = new char[length + 1];
      strcpy(data, str);
    }
  }

  // Copy constructor
  String(const String &other) : length(other.length) {
    data = new char[length + 1];
    strcpy(data, other.data);
  }

  // Destructor
  ~String() { delete[] data; }

  // Copy assignment operator
  String &operator=(const String &other) {
    if (this == &other)
      return *this; // Self-assignment check

    delete[] data; // Free old data
    length = other.length;
    data = new char[length + 1];
    strcpy(data, other.data);
    return *this;
  }

  int getLength() const { return length; }

  void display() const { cout << data << endl; }
};

/*
OUTPUT:
--------
String 1: Hello
String 2: Hello
After assignment, modified String 2: World
String 1: Hello (unchanged)

--------
*/

/*
================================================================================
EXAMPLE 4: UNARY OPERATORS - COUNTER CLASS
================================================================================
*/

class Counter {
private:
  int value;

public:
  Counter(int v = 0) : value(v) {}

  // Pre-increment ++counter
  Counter &operator++() {
    value++;
    return *this;
  }

  // Post-increment counter++
  Counter operator++(int) {
    Counter temp(value);
    value++;
    return temp;
  }

  // Pre-decrement --counter
  Counter &operator--() {
    value--;
    return *this;
  }

  // Post-decrement counter--
  Counter operator--(int) {
    Counter temp(value);
    value--;
    return temp;
  }

  // Unary minus -counter
  Counter operator-() const { return Counter(-value); }

  // Unary plus +counter
  Counter operator+() const { return Counter(value); }

  // Logical NOT !counter
  bool operator!() const { return value == 0; }

  int getValue() const { return value; }

  void display() const { cout << value << endl; }
};

/*
OUTPUT:
--------
Counter: 5
After ++counter: 6
After counter++: 6 (returns 6)
After --counter: 5
After counter--: 5 (returns 5)
-Counter: -5

--------
*/

/*
================================================================================
EXAMPLE 5: SUBSCRIPT OPERATOR [] - ARRAY CLASS
================================================================================
*/

class Array {
private:
  vector<int> elements;

public:
  Array(int size = 0) : elements(size, 0) {}

  // Overload [] operator (non-const version - for modification)
  int &operator[](int index) {
    if (index >= 0 && index < (int)elements.size()) {
      return elements[index];
    }
    throw out_of_range("Index out of bounds!");
  }

  // Overload [] operator (const version - for access)
  const int &operator[](int index) const {
    if (index >= 0 && index < (int)elements.size()) {
      return elements[index];
    }
    throw out_of_range("Index out of bounds!");
  }

  int size() const { return elements.size(); }

  void display() const {
    cout << "[";
    for (int i = 0; i < (int)elements.size(); i++) {
      cout << elements[i];
      if (i < (int)elements.size() - 1)
        cout << ", ";
    }
    cout << "]" << endl;
  }
};

/*
OUTPUT:
--------
Array: [1, 2, 3, 4, 5]
Element at index 0: 1
Element at index 2: 3
After modification: [1, 20, 3, 4, 5]

--------
*/

/*
================================================================================
EXAMPLE 6: STREAM OPERATORS - OUTPUT AND INPUT
================================================================================
*/

class Fraction {
private:
  int numerator;
  int denominator;

  int gcd(int a, int b) const { return (b == 0) ? a : gcd(b, a % b); }

  void simplify() {
    int g = gcd(abs(numerator), abs(denominator));
    numerator /= g;
    denominator /= g;
  }

public:
  Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
    simplify();
  }

  // Friend function for output operator
  friend ostream &operator<<(ostream &os, const Fraction &frac) {
    os << frac.numerator << "/" << frac.denominator;
    return os;
  }

  // Friend function for input operator
  friend istream &operator>>(istream &is, Fraction &frac) {
    cout << "Enter numerator: ";
    is >> frac.numerator;
    cout << "Enter denominator: ";
    is >> frac.denominator;
    frac.simplify();
    return is;
  }

  // Arithmetic operations
  Fraction operator+(const Fraction &other) const {
    int num = numerator * other.denominator + other.numerator * denominator;
    int den = denominator * other.denominator;
    return Fraction(num, den);
  }
};

/*
OUTPUT:
--------
Fraction 1: 3/4
Fraction 2: 1/2
Sum: 5/4

--------
*/

/*
================================================================================
EXAMPLE 7: COMPOUND ASSIGNMENT OPERATORS
================================================================================
*/

class Point {
private:
  double x, y;

public:
  Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}

  // Overload += operator
  Point &operator+=(const Point &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  // Overload -= operator
  Point &operator-=(const Point &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  // Overload *= operator (scalar multiplication)
  Point &operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  // Overload /= operator (scalar division)
  Point &operator/=(double scalar) {
    if (scalar != 0) {
      x /= scalar;
      y /= scalar;
    }
    return *this;
  }

  void display() const { cout << "(" << x << ", " << y << ")" << endl; }
};

/*
OUTPUT:
--------
Point: (5, 10)
After += (2, 3): (7, 13)
After -= (1, 2): (6, 11)
After *= 2: (12, 22)

--------
*/

/*
================================================================================
EXAMPLE 8: TYPE CONVERSION OPERATORS
================================================================================
*/

class Temperature {
private:
  double kelvin;

public:
  Temperature(double k = 273.15) : kelvin(k) {}

  // Convert to Celsius
  operator double() const { return kelvin - 273.15; }

  // Convert to int (rounded)
  operator int() const { return (int)(kelvin - 273.15); }

  // Convert to string
  operator string() const { return to_string(kelvin) + " K"; }

  double getKelvin() const { return kelvin; }
};

/*
OUTPUT:
--------
Temperature: 298.15 K
As double (Celsius): 25
As int (Celsius): 25
As string: 298.150000 K

--------
*/

/*
================================================================================
KEY CONCEPTS SUMMARY BOX
================================================================================

OPERATOR OVERLOADING RULES:

OPERATORS OVERLOADABLE AS MEMBER FUNCTIONS:
- Must be: =, [], (), ->
- Can be: +, -, *, /, %, +=, -=, etc.
- Unary: ++, --, +, -, !, ~

OPERATORS OVERLOADABLE AS FRIEND FUNCTIONS:
- Good for: +, -, *, /, ==, <, >, etc.
- Must be: <<, >> (stream operators)
- Allows: Left operand of different type

OPERATORS CANNOT BE OVERLOADED:
- Scope: ::
- Member selection: .
- Ternary: ?:
- Sizeof, typeid

BEST PRACTICES:
1. Binary operators: Often as friend functions (symmetric)
2. Assignment operator: Must be member function
3. Subscript operator: Must be member function
4. Unary operators: Can be either member or friend
5. Maintain consistency with expected behavior
6. Preserve operator precedence
7. Deep copy in assignment operator
8. Always return const for subscript in const version

PRE vs POST INCREMENT/DECREMENT:
- Pre (++i): Returns reference, modifies before return
- Post (i++): Takes dummy int parameter, modifies after return
- Pre is slightly more efficient (no temporary)

================================================================================
*/

/*
================================================================================
COMMON MISTAKES
================================================================================

❌ MISTAKE 1: Forgetting self-assignment check in operator=
    String& operator=(const String& other) {
        delete[] data;  // Might delete other's data!
        ...
    }

✓ CORRECT:
    String& operator=(const String& other) {
        if (this == &other) return *this;
        delete[] data;
        ...
    }

-----

❌ MISTAKE 2: Not returning reference from assignment
    void operator=(const Vector& other) {  // Wrong return type!
        ...
    }

✓ CORRECT:
    Vector& operator=(const Vector& other) {
        ...
        return *this;
    }

-----

❌ MISTAKE 3: Changing operator precedence
    // Operators have fixed precedence, cannot be changed

✓ CORRECT:
    Use parentheses for clarity: (a + b) * c

-----

❌ MISTAKE 4: Not differentiating pre vs post increment
    Counter operator++() {  // Should be reference for pre!
        ...
    }

✓ CORRECT:
    Counter& operator++() { ... }        // Pre
    Counter operator++(int) { ... }     // Post

-----

❌ MISTAKE 5: Shallow copy in assignment
    String& operator=(const String& other) {
        data = other.data;  // Both point to same memory!
        ...
    }

✓ CORRECT:
    String& operator=(const String& other) {
        delete[] data;
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
        ...
    }

================================================================================
*/

/*
================================================================================
PRACTICE EXERCISES
================================================================================

Exercise 1: Complex Number Class
Overload +, -, *, / operators
Overload ==, < operators for comparison
Overload << for output

Exercise 2: Matrix Class
Overload +, - for matrix addition/subtraction
Overload * for matrix multiplication
Overload [] for element access

Exercise 3: Rational Number Class
Overload +, -, *, / for arithmetic
Overload <, >, ==, <= operators
Overload << and >> for I/O

Exercise 4: Time Class
Overload + to add seconds
Overload - to subtract times
Overload ==, < for comparison
Overload ++ for increment

Exercise 5: Money Class
Overload +, -, *, / operators
Overload << for output
Overload +, -, *, /= for compound operations

Exercise 6: Polynomial Class
Overload + to add polynomials
Overload * for multiplication
Overload [] to access coefficients
Overload << for printing

Exercise 7: SmartPointer Class
Overload * to dereference
Overload -> for member access
Overload = for assignment
Overload [] for array access

Exercise 8: String Class
Overload + for concatenation
Overload +=  for append
Overload [] for character access
Overload ==, < for comparison

Exercise 9: Set Class
Overload + for union
Overload - for difference
Overload * for intersection
Overload == for equality

Exercise 10: Custom Iterator
Overload ++ and -- for navigation
Overload * for dereferencing
Overload == and != for comparison

================================================================================
*/

// Main demonstration
int main() {
  cout << "================== OPERATOR OVERLOADING BASICS "
          "==================\n\n";

  // Example 1: Arithmetic Operators
  cout << "--- EXAMPLE 1: ARITHMETIC OPERATORS ---\n";
  Vector v1(3, 4, 0);
  Vector v2(1, 2, 0);
  cout << "V1: ";
  v1.display();
  cout << ", V2: ";
  v2.display();
  cout << endl;

  Vector v3 = v1 + v2;
  cout << "V1 + V2: ";
  v3.display();
  cout << endl;

  Vector v4 = v1 * 2;
  cout << "V1 * 2: ";
  v4.display();
  cout << endl;
  cout << "\n";

  // Example 2: Comparison Operators
  cout << "--- EXAMPLE 2: COMPARISON OPERATORS ---\n";
  Student s1("Alice", 1, 3.8);
  Student s2("Bob", 2, 3.5);
  s1.display();
  s2.display();
  cout << "s1 > s2: " << (s1 > s2 ? "true" : "false") << endl;
  cout << "s1 == s2: " << (s1 == s2 ? "true" : "false") << endl;
  cout << "\n";

  // Example 3: Assignment Operator
  cout << "--- EXAMPLE 3: ASSIGNMENT OPERATOR ---\n";
  String str1("Hello");
  String str2 = str1;
  cout << "String 1: ";
  str1.display();
  cout << "String 2: ";
  str2.display();
  cout << "\n";

  // Example 4: Unary Operators
  cout << "--- EXAMPLE 4: UNARY OPERATORS ---\n";
  Counter c(5);
  cout << "Counter: ";
  c.display();
  ++c;
  cout << "After ++c: ";
  c.display();
  c++;
  cout << "After c++: ";
  c.display();
  cout << "\n";

  // Example 5: Subscript Operator
  cout << "--- EXAMPLE 5: SUBSCRIPT OPERATOR ---\n";
  Array arr(5);
  for (int i = 0; i < arr.size(); i++) {
    arr[i] = (i + 1) * 10;
  }
  cout << "Array: ";
  arr.display();
  cout << "Element at index 2: " << arr[2] << endl;
  cout << "\n";

  // Example 6: Stream Operators
  cout << "--- EXAMPLE 6: STREAM OPERATORS ---\n";
  Fraction f1(3, 4);
  Fraction f2(1, 2);
  cout << "Fraction 1: " << f1 << endl;
  cout << "Fraction 2: " << f2 << endl;
  Fraction f3 = f1 + f2;
  cout << "Sum: " << f3 << endl;
  cout << "\n";

  // Example 7: Compound Assignment
  cout << "--- EXAMPLE 7: COMPOUND ASSIGNMENT ---\n";
  Point p(5, 10);
  cout << "Point: ";
  p.display();
  p += Point(2, 3);
  cout << "After += (2,3): ";
  p.display();
  p *= 2;
  cout << "After *= 2: ";
  p.display();
  cout << "\n";

  // Example 8: Type Conversion
  cout << "--- EXAMPLE 8: TYPE CONVERSION ---\n";
  Temperature temp(298.15);
  cout << "Temperature: " << (string)temp << endl;
  cout << "As Celsius: " << (double)temp << endl;
  cout << "As int: " << (int)temp << endl;
  cout << "\n";

  return 0;
}

/*
================================================================================
FULL PROGRAM OUTPUT:
================================================================================

================== OPERATOR OVERLOADING BASICS ==================

--- EXAMPLE 1: ARITHMETIC OPERATORS ---
V1: (3, 4, 0), V2: (1, 2, 0)
V1 + V2: (4, 6, 0)
V1 * 2: (6, 8, 0)

--- EXAMPLE 2: COMPARISON OPERATORS ---
Name: Alice, Roll: 1, GPA: 3.8
Name: Bob, Roll: 2, GPA: 3.5
s1 > s2: true
s1 == s2: false

--- EXAMPLE 3: ASSIGNMENT OPERATOR ---
String 1: Hello
String 2: Hello

--- EXAMPLE 4: UNARY OPERATORS ---
Counter: 5
After ++c: 6
After c++: 7

--- EXAMPLE 5: SUBSCRIPT OPERATOR ---
Array: [10, 20, 30, 40, 50]
Element at index 2: 30

--- EXAMPLE 6: STREAM OPERATORS ---
Fraction 1: 3/4
Fraction 2: 1/2
Sum: 5/4

--- EXAMPLE 7: COMPOUND ASSIGNMENT ---
Point: (5, 10)
After += (2,3): (7, 13)
After *= 2: (14, 26)

--- EXAMPLE 8: TYPE CONVERSION ---
Temperature: 298.150000 K
As Celsius: 25
As int: 25

================================================================================
*/
