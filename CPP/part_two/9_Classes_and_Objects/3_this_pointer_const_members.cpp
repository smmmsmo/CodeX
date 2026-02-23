/*
================================================================================
TOPIC 9: CLASSES AND OBJECTS - PART 3: THIS POINTER AND CONST MEMBERS
================================================================================

THIS POINTER:
- Points to the current object
- Used inside member functions
- Implicit parameter in all member functions
- Type: const pointer to the object

USE CASES FOR THIS:
1. Return reference to current object (for chaining)
2. Pass object to other functions
3. Distinguish between member and parameter with same name
4. Return pointer to object from member function

CONST MEMBER FUNCTIONS:
- Functions that don't modify member variables
- Syntax: returnType function() const
- Cannot modify data members
- Can call other const functions
- Should use const when appropriate

CONST OBJECTS:
- Objects declared with const keyword
- Can only call const member functions
- Member variables cannot be changed

CONST DATA MEMBERS:
- Must be initialized in constructor
- Cannot be modified after initialization
- Used for immutable properties

================================================================================
*/

#include <cmath>
#include <iostream>
#include <string>
using namespace std;

// ======================= CLASS DEMONSTRATING THIS POINTER
// =======================
class Point {
private:
  int x, y;

public:
  Point(int x = 0, int y = 0) {
    this->x = x; // Use this to distinguish
    this->y = y;
  }

  // Return reference to current object
  Point &addPoint(Point other) {
    this->x += other.x;
    this->y += other.y;
    return *this; // Return reference to self
  }

  // Method chaining
  Point &moveRight(int units) {
    this->x += units;
    return *this;
  }

  Point &moveUp(int units) {
    this->y += units;
    return *this;
  }

  void display() {
    cout << "Point(" << this->x << ", " << this->y << ")" << endl;
  }

  // Get pointer to self
  Point *getPointerToSelf() { return this; }
};

// ======================= CLASS WITH CONST MEMBER FUNCTIONS
// =======================
class Circle {
private:
  double radius;
  double x, y; // Center coordinates

public:
  Circle(double r, double cx, double cy) {
    radius = r;
    x = cx;
    y = cy;
  }

  // Const member function - doesn't modify data
  double getArea() const { return 3.14159 * radius * radius; }

  // Const member function
  double getPerimeter() const { return 2 * 3.14159 * radius; }

  // Const member function
  double getRadius() const { return radius; }

  // Const member function
  void display() const {
    cout << "Circle at (" << x << ", " << y << "), Radius: " << radius
         << ", Area: " << getArea() << endl;
  }

  // Non-const function - can modify data
  void setRadius(double r) {
    if (r > 0) {
      radius = r;
    }
  }
};

// ======================= CLASS WITH CONST DATA MEMBERS =======================
class Rectangle {
private:
  const double width;  // Const member - must be initialized
  const double height; // Const member - must be initialized
  string color;        // Non-const member

public:
  // Must initialize const members in initialization list
  Rectangle(double w, double h, string c) : width(w), height(h) { color = c; }

  // Const member function
  double getArea() const {
    return width * height; // Can read const members
  }

  // Const member function
  double getPerimeter() const { return 2 * (width + height); }

  // Non-const function
  void setColor(string c) {
    color = c;
    // width = 10;  // ERROR: Cannot modify const member
  }

  // Const member function
  void display() const {
    cout << "Rectangle: " << width << " x " << height << ", Color: " << color
         << endl;
  }
};

// ======================= CLASS WITH CONST OBJECTS =======================
class BankAccount {
private:
  string account_number;
  double balance;

public:
  BankAccount(string acc, double bal) : account_number(acc), balance(bal) {}

  // Const member function - safe to call on const objects
  double getBalance() const { return balance; }

  // Const member function
  string getAccountNumber() const { return account_number; }

  // Non-const function - cannot call on const objects
  void deposit(double amount) { balance += amount; }

  // Const member function
  void display() const {
    cout << "Account: " << account_number << ", Balance: $" << balance << endl;
  }
};

// ======================= COMPLEX CLASS WITH ALL FEATURES
// =======================
class Student {
private:
  string name;
  int roll_number;
  double gpa;
  const string university; // Const member

public:
  // Constructor with initialization list
  Student(string n, int r, double g, string u)
      : university(u), name(n), roll_number(r), gpa(g) {}

  // Non-const function - can modify members
  void updateGPA(double new_gpa) {
    if (new_gpa >= 0 && new_gpa <= 4.0) {
      gpa = new_gpa;
    }
  }

  // Const member function - cannot modify members
  double getGPA() const { return gpa; }

  // Const member function
  int getRoll() const { return roll_number; }

  // Const member function
  string getName() const { return name; }

  // Const member function
  string getUniversity() const {
    return this->university; // Can access const members
  }

  // Const member function
  void display() const {
    cout << "Name: " << name << ", Roll: " << roll_number << ", GPA: " << gpa
         << ", University: " << university << endl;
  }
};

// ======================= CLASS DEMONSTRATING THIS =======================
class Vector {
private:
  int *arr;
  int size;

public:
  Vector(int s) {
    size = s;
    arr = new int[size];
    for (int i = 0; i < size; i++) {
      arr[i] = 0;
    }
  }

  ~Vector() { delete[] arr; }

  // Use this to return reference for chaining
  Vector &set(int index, int value) {
    if (index >= 0 && index < size) {
      arr[index] = value;
    }
    return *this; // Return self for chaining
  }

  // Const member function
  int get(int index) const {
    if (index >= 0 && index < size) {
      return arr[index];
    }
    return -1;
  }

  // Const member function
  int getSize() const { return size; }

  // Const member function
  void display() const {
    cout << "Vector: [";
    for (int i = 0; i < size; i++) {
      cout << arr[i];
      if (i < size - 1)
        cout << ", ";
    }
    cout << "]" << endl;
  }
};

int main() {
  cout << "=== THIS POINTER AND CONST MEMBERS ===" << endl << endl;

  // ======================= THIS POINTER BASICS =======================
  cout << "1. THIS POINTER BASICS:" << endl;

  Point p1(3, 4);
  cout << "Original point: ";
  p1.display();

  cout << "This pointer value: " << p1.getPointerToSelf() << endl;

  // ======================= METHOD CHAINING WITH THIS =======================
  cout << endl << "2. METHOD CHAINING WITH THIS POINTER:" << endl;

  Point p2(0, 0);
  cout << "Starting point: ";
  p2.display();

  cout << endl << "Chaining operations:" << endl;
  p2.moveRight(5).moveUp(3);
  cout << "After chain: ";
  p2.display();

  cout << endl << "Another chain:" << endl;
  p2.moveRight(2).moveUp(2).moveRight(1);
  cout << "After another chain: ";
  p2.display();

  // ======================= CONST MEMBER FUNCTIONS =======================
  cout << endl << "3. CONST MEMBER FUNCTIONS:" << endl;

  Circle c1(5, 0, 0);
  cout << "Circle created with radius 5" << endl;
  cout << "Area: " << c1.getArea() << endl;
  cout << "Perimeter: " << c1.getPerimeter() << endl;
  cout << "Radius: " << c1.getRadius() << endl;
  c1.display();

  // ======================= CONST OBJECTS =======================
  cout << endl << "4. CONST OBJECTS (Can only call const functions):" << endl;

  const Circle c2(7, 10, 10); // Const object
  cout << "Const circle created" << endl;
  cout << "Area: " << c2.getArea() << endl;     // OK - const function
  cout << "Radius: " << c2.getRadius() << endl; // OK - const function
  c2.display();                                 // OK - const function
  // c2.setRadius(8);  // ERROR: Cannot call non-const on const object

  // ======================= CONST DATA MEMBERS =======================
  cout << endl << "5. CONST DATA MEMBERS:" << endl;

  Rectangle rect1(10, 20, "Blue");
  cout << "Rectangle created:" << endl;
  rect1.display();

  cout << "Area: " << rect1.getArea() << endl;
  cout << "Perimeter: " << rect1.getPerimeter() << endl;

  rect1.setColor("Red");
  cout << "After changing color:" << endl;
  rect1.display();

  // ======================= CONST OBJECT WITH CONST MEMBERS
  // =======================
  cout << endl << "6. CONST OBJECT WITH CONST DATA MEMBERS:" << endl;

  const Rectangle rect2(5, 8, "Green");
  cout << "Const rectangle:" << endl;
  rect2.display();
  cout << "Area: " << rect2.getArea() << endl;
  // rect2.setColor("Yellow");  // ERROR: Cannot call non-const

  // ======================= BANK ACCOUNT CONST EXAMPLE =======================
  cout << endl << "7. BANK ACCOUNT (CONST FUNCTIONS):" << endl;

  BankAccount acc1("ACC123", 1000);
  cout << "Account details:" << endl;
  acc1.display();

  cout << "Current balance: $" << acc1.getBalance() << endl;
  acc1.deposit(500);
  acc1.display();

  // Const account can only call const functions
  const BankAccount acc2("ACC456", 2000);
  cout << endl << "Const account:" << endl;
  acc2.display();
  cout << "Balance: $" << acc2.getBalance() << endl;
  // acc2.deposit(100);  // ERROR: Non-const function on const object

  // ======================= STUDENT CLASS =======================
  cout << endl << "8. STUDENT CLASS (ALL FEATURES):" << endl;

  Student s1("Alice", 101, 3.8, "XYZ University");
  cout << "Student created:" << endl;
  s1.display();

  cout << "Name: " << s1.getName() << endl;
  cout << "GPA: " << s1.getGPA() << endl;

  cout << "\nUpdating GPA:" << endl;
  s1.updateGPA(3.9);
  s1.display();

  // Const student
  const Student s2("Bob", 102, 3.5, "XYZ University");
  cout << endl << "Const student:" << endl;
  s2.display();
  cout << "GPA: " << s2.getGPA() << endl;
  // s2.updateGPA(3.6);  // ERROR: Non-const function

  // ======================= VECTOR WITH THIS POINTER =======================
  cout << endl << "9. VECTOR WITH THIS POINTER (METHOD CHAINING):" << endl;

  Vector v1(5);
  cout << "Initial vector:" << endl;
  v1.display();

  cout << "\nChaining set operations:" << endl;
  v1.set(0, 10).set(1, 20).set(2, 30).set(3, 40).set(4, 50);
  v1.display();

  cout << "\nReading values:" << endl;
  for (int i = 0; i < v1.getSize(); i++) {
    cout << "v1[" << i << "] = " << v1.get(i) << endl;
  }

  // ======================= THIS IN DIFFERENT CONTEXTS =======================
  cout << endl << "10. THIS POINTER IN DIFFERENT CONTEXTS:" << endl;

  Point p3(2, 3);
  Point p4(1, 1);

  cout << "p3 before: ";
  p3.display();

  cout << "Adding p4 to p3:" << endl;
  p3.addPoint(p4);

  cout << "p3 after: ";
  p3.display();

  return 0;
}

/*
OUTPUT:
=== THIS POINTER AND CONST MEMBERS ===

1. THIS POINTER BASICS:
Original point: Point(3, 4)
This pointer value: 0x7fff5fbff8d0

2. METHOD CHAINING WITH THIS POINTER:
Starting point: Point(0, 0)

Chaining operations:
After chain: Point(5, 3)

Another chain:
After another chain: Point(8, 5)

3. CONST MEMBER FUNCTIONS:
Circle created with radius 5
Area: 78.5398
Perimeter: 31.4159
Radius: 5
Circle at (0, 0), Radius: 5, Area: 78.5398

4. CONST OBJECTS (Can only call const functions):
Const circle created
Area: 153.94
Radius: 7
Circle at (10, 10), Radius: 7, Area: 153.94

5. CONST DATA MEMBERS:
Rectangle created:
Rectangle: 10 x 20, Color: Blue
Area: 200
Perimeter: 60
After changing color:
Rectangle: 10 x 20, Color: Red

6. CONST OBJECT WITH CONST DATA MEMBERS:
Const rectangle:
Rectangle: 5 x 8, Color: Green
Area: 40

7. BANK ACCOUNT (CONST FUNCTIONS):
Account details:
Account: ACC123, Balance: $1000
Current balance: $1000
Account: ACC123, Balance: $1500

Const account:
Account: ACC456, Balance: $2000
Balance: $2000

8. STUDENT CLASS (ALL FEATURES):
Student created:
Name: Alice, Roll: 101, GPA: 3.8, University: XYZ University
Name: Alice
GPA: 3.8

Updating GPA:
Name: Alice, Roll: 101, GPA: 3.9, University: XYZ University

Const student:
Name: Bob, Roll: 102, GPA: 3.5, University: XYZ University
GPA: 3.5

9. VECTOR WITH THIS POINTER (METHOD CHAINING):
Initial vector:
Vector: [0, 0, 0, 0, 0]

Chaining set operations:
Vector: [10, 20, 30, 40, 50]

Reading values:
v1[0] = 10
v1[1] = 20
v1[2] = 30
v1[3] = 40
v1[4] = 50

10. THIS POINTER IN DIFFERENT CONTEXTS:
p3 before: Point(2, 3)
Adding p4 to p3:
p3 after: Point(3, 4)

================================================================================
KEY CONCEPTS
================================================================================

1. THIS POINTER:
   - Implicit pointer to current object
   - Available in all member functions
   - Type: ClassName* const (const pointer, not const object)
   - Used for method chaining (return *this)

2. THIS USAGE:
   - Disambiguate member from parameter: this->x = x;
   - Return reference to self for chaining
   - Pass object to other functions
   - Get pointer to current object

3. CONST MEMBER FUNCTIONS:
   - Cannot modify member variables
   - Can be called on const objects
   - Can call other const functions
   - Use const when function doesn't modify state

4. CONST OBJECTS:
   - Declared with const keyword
   - Can only call const member functions
   - Member variables are constant (cannot change)
   - Cannot call non-const functions

5. CONST DATA MEMBERS:
   - Must be initialized (usually in initialization list)
   - Cannot be modified after initialization
   - Useful for immutable properties
   - Initialization list: Point(int x) : const_x(x) { }

6. METHOD CHAINING:
   - Return reference to *this
   - Allows: obj.method1().method2().method3();
   - Common in builder patterns

================================================================================
PRACTICE EXERCISES
================================================================================

1. Create StringBuilder class with method chaining

2. Create Person class with const members (SSN, date of birth)

3. Create Square class:
   - Const member for side length
   - Const functions to get area, perimeter
   - Use this pointer in operations

4. Create DynamicArray class
   - Use this pointer for chaining
   - Const functions to access elements

5. Create Time class
   - Const functions to get hour, minute, second
   - Non-const functions to modify time
   - Method chaining for operations

================================================================================
*/
