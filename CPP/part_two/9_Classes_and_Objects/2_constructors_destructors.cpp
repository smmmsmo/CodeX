/*
================================================================================
TOPIC 9: CLASSES AND OBJECTS - PART 2: CONSTRUCTORS AND DESTRUCTORS
================================================================================

CONSTRUCTORS:
- Special member function that initializes objects
- Called automatically when object is created
- Name same as class name
- No return type (not even void)
- Can be overloaded (multiple constructors)

TYPES OF CONSTRUCTORS:
1. Default Constructor: No parameters
2. Parameterized Constructor: With parameters
3. Copy Constructor: Copies from another object

DESTRUCTORS:
- Special function that cleans up resources
- Called automatically when object is destroyed
- Name: ~ClassName
- No parameters, no return type
- Only one destructor per class
- Used to free dynamically allocated memory

CONSTRUCTOR SYNTAX:
class MyClass {
    MyClass() { }              // Default
    MyClass(int x) { }         // Parameterized
    MyClass(MyClass& obj) { }  // Copy
    ~MyClass() { }             // Destructor
};

INITIALIZATION ORDER:
1. Object creation
2. Constructor called
3. Object used
4. Destructor called (when scope ends or delete called)

================================================================================
*/

#include <iostream>
#include <string>
using namespace std;

// ======================= CLASS WITH DEFAULT CONSTRUCTOR
// =======================
class Circle {
private:
  double radius;

public:
  // Default constructor
  Circle() {
    cout << "Circle object created (default constructor)" << endl;
    radius = 1.0; // Default value
  }

  double getArea() { return 3.14159 * radius * radius; }

  void display() {
    cout << "Radius: " << radius << ", Area: " << getArea() << endl;
  }
};

// ======================= CLASS WITH PARAMETERIZED CONSTRUCTOR
// =======================
class Rectangle {
private:
  double length;
  double width;

public:
  // Parameterized constructor
  Rectangle(double l, double w) {
    cout << "Rectangle object created with parameters" << endl;
    length = l;
    width = w;
  }

  double getArea() { return length * width; }

  void display() {
    cout << "Length: " << length << ", Width: " << width
         << ", Area: " << getArea() << endl;
  }
};

// ======================= CLASS WITH MULTIPLE CONSTRUCTORS
// =======================
class Square {
private:
  double side;

public:
  // Default constructor
  Square() {
    cout << "Square created with default constructor" << endl;
    side = 1.0;
  }

  // Parameterized constructor
  Square(double s) {
    cout << "Square created with parameterized constructor" << endl;
    side = s;
  }

  double getArea() { return side * side; }

  void display() {
    cout << "Side: " << side << ", Area: " << getArea() << endl;
  }
};

// ======================= CLASS WITH DESTRUCTOR =======================
class Resource {
private:
  int *data;
  int size;

public:
  // Constructor - allocate memory
  Resource(int s) {
    cout << "Resource constructor: Allocating " << s << " integers" << endl;
    size = s;
    data = new int[size];

    // Initialize with values
    for (int i = 0; i < size; i++) {
      data[i] = i * 10;
    }
  }

  // Destructor - free memory
  ~Resource() {
    cout << "Resource destructor: Freeing memory" << endl;
    delete[] data;
  }

  void display() {
    cout << "Data: ";
    for (int i = 0; i < size; i++) {
      cout << data[i] << " ";
    }
    cout << endl;
  }
};

// ======================= CLASS WITH COPY CONSTRUCTOR =======================
class Student {
private:
  string name;
  int roll;
  double gpa;

public:
  // Parameterized constructor
  Student(string n, int r, double g) {
    cout << "Parameterized constructor: Creating " << n << endl;
    name = n;
    roll = r;
    gpa = g;
  }

  // Copy constructor
  Student(Student &other) {
    cout << "Copy constructor: Copying " << other.name << endl;
    name = other.name;
    roll = other.roll;
    gpa = other.gpa;
  }

  void display() {
    cout << "Name: " << name << ", Roll: " << roll << ", GPA: " << gpa << endl;
  }
};

// ======================= COMPLEX CLASS WITH CONSTRUCTOR
// =======================
class Person {
private:
  string first_name;
  string last_name;
  int age;

public:
  // Default constructor
  Person() {
    cout << "Person default constructor" << endl;
    first_name = "Unknown";
    last_name = "Unknown";
    age = 0;
  }

  // Parameterized constructor
  Person(string fname, string lname, int a) {
    cout << "Person parameterized constructor" << endl;
    first_name = fname;
    last_name = lname;
    age = a;
  }

  // Destructor
  ~Person() { cout << "Person destructor: Destroying " << first_name << endl; }

  void display() {
    cout << "Name: " << first_name << " " << last_name << ", Age: " << age
         << endl;
  }
};

// ======================= CLASS DEMONSTRATING OBJECT LIFETIME
// =======================
class Counter {
private:
  int count;
  string id;

public:
  Counter(string identifier) {
    cout << "Creating Counter: " << identifier << endl;
    id = identifier;
    count = 0;
  }

  ~Counter() {
    cout << "Destroying Counter: " << id << " (Final count: " << count << ")"
         << endl;
  }

  void increment() {
    count++;
    cout << id << " count: " << count << endl;
  }
};

// ======================= BANK ACCOUNT WITH CONSTRUCTOR =======================
class BankAccount {
private:
  string account_holder;
  string account_number;
  double balance;

public:
  // Constructor
  BankAccount(string holder, string acc_no, double initial_balance) {
    cout << "Creating account for " << holder << endl;
    account_holder = holder;
    account_number = acc_no;
    balance = initial_balance;
  }

  ~BankAccount() { cout << "Account closed for " << account_holder << endl; }

  void deposit(double amount) {
    balance += amount;
    cout << "Deposited: $" << amount << ", New balance: $" << balance << endl;
  }

  void withdraw(double amount) {
    if (amount <= balance) {
      balance -= amount;
      cout << "Withdrawn: $" << amount << ", New balance: $" << balance << endl;
    } else {
      cout << "Insufficient funds!" << endl;
    }
  }

  void display() {
    cout << "Account: " << account_number << ", Holder: " << account_holder
         << ", Balance: $" << balance << endl;
  }
};

int main() {
  cout << "=== CONSTRUCTORS AND DESTRUCTORS ===" << endl << endl;

  // ======================= DEFAULT CONSTRUCTOR =======================
  cout << "1. DEFAULT CONSTRUCTOR:" << endl;

  Circle c1;
  c1.display();

  cout << endl;
  Circle c2;
  c2.display();

  // ======================= PARAMETERIZED CONSTRUCTOR =======================
  cout << endl << "2. PARAMETERIZED CONSTRUCTOR:" << endl;

  Rectangle rect1(5, 10);
  rect1.display();

  cout << endl;
  Rectangle rect2(3, 7);
  rect2.display();

  // ======================= CONSTRUCTOR OVERLOADING =======================
  cout << endl << "3. CONSTRUCTOR OVERLOADING:" << endl;

  Square sq1; // Calls default constructor
  sq1.display();

  cout << endl;
  Square sq2(5); // Calls parameterized constructor
  sq2.display();

  cout << endl;
  Square sq3(3.5); // Also calls parameterized constructor
  sq3.display();

  // ======================= DESTRUCTORS AND MEMORY =======================
  cout << endl << "4. CONSTRUCTORS AND DESTRUCTORS (Dynamic Memory):" << endl;

  {
    cout << "Creating Resource object:" << endl;
    Resource res1(5);
    res1.display();
    cout << "Resource object will be destroyed now:" << endl;
  }
  cout << "Resource object destroyed" << endl;

  // ======================= COPY CONSTRUCTOR =======================
  cout << endl << "5. COPY CONSTRUCTOR:" << endl;

  Student s1("Alice", 101, 3.8);
  cout << "Original student:" << endl;
  s1.display();

  cout << endl << "Copying student:" << endl;
  Student s2 = s1; // Calls copy constructor
  cout << "Copied student:" << endl;
  s2.display();

  // ======================= OBJECT LIFETIME =======================
  cout << endl << "6. OBJECT LIFETIME DEMONSTRATION:" << endl;

  {
    cout << "Block 1 starts:" << endl;
    Counter c1("Counter-1");
    c1.increment();
    c1.increment();
    cout << "Block 1 ends (destructor called):" << endl;
  }

  cout << endl << "Block 1 has ended" << endl;

  {
    cout << "Block 2 starts:" << endl;
    Counter c2("Counter-2");
    c2.increment();
    cout << "Block 2 ends (destructor called):" << endl;
  }

  // ======================= MULTIPLE CONSTRUCTORS =======================
  cout << endl << "7. MULTIPLE CONSTRUCTORS IN SEQUENCE:" << endl;

  Person p1; // Default constructor
  p1.display();

  cout << endl;
  Person p2("Bob", "Smith", 25); // Parameterized constructor
  p2.display();

  cout << endl;
  Person p3("Carol", "Davis", 30); // Another parameterized constructor
  p3.display();

  cout << endl << "Destructors will be called for p1, p2, p3:" << endl;

  // ======================= BANK ACCOUNT EXAMPLE =======================
  cout << endl << "8. BANK ACCOUNT WITH CONSTRUCTOR:" << endl;

  BankAccount acc1("John Doe", "ACC123456", 1000);
  acc1.display();

  cout << endl << "Transactions:" << endl;
  acc1.deposit(500);
  acc1.withdraw(200);
  acc1.display();

  cout << endl << "Account closing:" << endl;

  // ======================= ARRAY OF OBJECTS =======================
  cout << endl << "9. ARRAY OF OBJECTS WITH CONSTRUCTOR:" << endl;

  cout << "Creating array of 3 squares:" << endl;
  Square squares[3] = {Square(2), Square(4), Square(5)};

  cout << endl << "Displaying squares:" << endl;
  for (int i = 0; i < 3; i++) {
    cout << "Square " << (i + 1) << ": ";
    squares[i].display();
  }

  cout << endl << "Array destructors will be called now" << endl;

  return 0;
}

/*
OUTPUT:
=== CONSTRUCTORS AND DESTRUCTORS ===

1. DEFAULT CONSTRUCTOR:
Circle object created (default constructor)
Radius: 1, Area: 3.14159

Circle object created (default constructor)
Radius: 1, Area: 3.14159

2. PARAMETERIZED CONSTRUCTOR:
Rectangle object created with parameters
Length: 5, Width: 10, Area: 50

Rectangle object created with parameters
Length: 3, Width: 7, Area: 21

3. CONSTRUCTOR OVERLOADING:
Square created with default constructor
Side: 1, Area: 1

Square created with parameterized constructor
Side: 5, Area: 25

Square created with parameterized constructor
Side: 3.5, Area: 12.25

4. CONSTRUCTORS AND DESTRUCTORS (Dynamic Memory):
Creating Resource object:
Resource constructor: Allocating 5 integers
Data: 0 10 20 30 40
Resource object will be destroyed now:
Resource destructor: Freeing memory
Resource object destroyed

5. COPY CONSTRUCTOR:
Parameterized constructor: Creating Alice
Original student:
Name: Alice, Roll: 101, GPA: 3.8

Copying student:
Copy constructor: Copying Alice
Copied student:
Name: Alice, Roll: 101, GPA: 3.8

6. OBJECT LIFETIME DEMONSTRATION:
Block 1 starts:
Creating Counter: Counter-1
Counter-1 count: 1
Counter-1 count: 2
Block 1 ends (destructor called):
Destroying Counter: Counter-1 (Final count: 2)
Block 1 has ended

Block 2 starts:
Creating Counter: Counter-2
Counter-2 count: 1
Block 2 ends (destructor called):
Destroying Counter: Counter-2 (Final count: 1)

7. MULTIPLE CONSTRUCTORS IN SEQUENCE:
Person default constructor
Name: Unknown Unknown, Age: 0

Person parameterized constructor
Name: Bob Smith, Age: 25

Person parameterized constructor
Name: Carol Davis, Age: 30

Destructors will be called for p1, p2, p3:
Person destructor: Destroying Unknown
Person destructor: Destroying Bob
Person destructor: Destroying Carol

8. BANK ACCOUNT WITH CONSTRUCTOR:
Creating account for John Doe
Account: ACC123456, Holder: John Doe, Balance: $1000

Transactions:
Deposited: $500, New balance: $1000.5
Withdrawn: $200, New balance: $800.5
Account: ACC123456, Holder: John Doe, Balance: $800.5

Account closing:

9. ARRAY OF OBJECTS WITH CONSTRUCTOR:
Creating array of 3 squares:
Square created with parameterized constructor
Square created with parameterized constructor
Square created with parameterized constructor

Displaying squares:
Square 1: Side: 2, Area: 4
Square 2: Side: 4, Area: 16
Square 3: Side: 5, Area: 25

Array destructors will be called now

================================================================================
KEY CONCEPTS
================================================================================

1. CONSTRUCTOR:
   - Called automatically on object creation
   - Initialize member variables
   - Can validate data on creation
   - Multiple constructors possible (overloading)

2. TYPES OF CONSTRUCTORS:
   - Default: No parameters, default initialization
   - Parameterized: Takes parameters for custom initialization
   - Copy: Creates object from existing object

3. DESTRUCTOR:
   - Called automatically on object destruction
   - One per class (not overloadable)
   - Clean up resources (memory, files, etc.)
   - Essential for dynamic memory management

4. INITIALIZATION LISTS:
   - Initialize const/reference members
   - More efficient than body assignment
   - Will cover in next part

5. OBJECT LIFETIME:
   - Created when constructor called
   - Destroyed when destructor called
   - Local objects: destroyed at end of scope
   - Dynamic objects: destroyed when delete called

6. DEFAULT BEHAVIOR:
   - If no constructor defined: compiler generates default
   - If no destructor defined: compiler generates default
   - Default versions may not handle dynamic memory

================================================================================
INITIALIZATION LIST PREVIEW
================================================================================

Can be more efficient:

class Point {
private:
    int x, y;

public:
    // Without initialization list:
    Point(int a, int b) {
        x = a;
        y = b;
    }

    // With initialization list (better):
    Point(int a, int b) : x(a), y(b) {
        // Body
    }
};

Benefits:
- Required for const members
- Required for reference members
- More efficient for complex objects
- Can call other constructors

================================================================================
PRACTICE EXERCISES
================================================================================

1. Create Point class with constructor
   - Initialize x, y coordinates
   - Calculate distance from origin

2. Create Book class
   - Constructor initializes title, author, price
   - Destructor prints "Book destroyed"

3. Create Temperature class
   - Constructor takes Celsius
   - Convert/display in Fahrenheit

4. Create LinkedListNode with constructor
   - Store data and next pointer
   - Initialize in constructor

5. Create ComplexNumber class
   - Constructor for real and imaginary parts
   - Add operation between two complex numbers

================================================================================
*/
