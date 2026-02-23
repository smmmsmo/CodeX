/*
================================================================================
ENCAPSULATION BASICS - DATA HIDING AND ACCESS CONTROL
================================================================================
Part 2, Subtopic 10: Encapsulation (File 1/2)

CONCEPTS COVERED:
- What is encapsulation?
- Private, public, and protected access modifiers
- Getter and setter methods (accessors and mutators)
- Data hiding principles
- Basic class invariants
- Introduction to information hiding

KEY LEARNING POINTS:
1. Encapsulation bundles data and methods that operate on that data
2. Access control ensures controlled access to class members
3. Private members hide implementation details
4. Public interface defines what others can interact with
5. Setters provide validation before modifying data
6. Getters control how data is accessed and returned

================================================================================
*/

#include <cmath>
#include <iostream>
#include <string>

using namespace std;

/*
================================================================================
THEORY SECTION: WHAT IS ENCAPSULATION?
================================================================================

Encapsulation is one of the four pillars of OOP. It's the bundling of data
(attributes) and methods (functions) into a single unit, along with mechanisms
to control access to those members.

The main goal: Hide internal implementation details and expose only what's
necessary through a well-defined interface.

Analogy: A car - you interact with the steering wheel, pedals, and buttons
(public interface) but don't directly access the engine internals (private
implementation).

BENEFITS OF ENCAPSULATION:
1. Data Protection: Prevent invalid states
2. Flexibility: Change implementation without affecting external code
3. Maintainability: Easy to modify internal logic
4. Reusability: Clear interface makes code reusable
5. Predictability: Controlled access ensures predictable behavior

================================================================================
*/

/*
================================================================================
EXAMPLE 1: BASIC ENCAPSULATION - SIMPLE BANK ACCOUNT
================================================================================
*/

class BankAccount {
private:
  // Private member variables - hidden from outside
  double balance;
  string accountHolder;
  int accountNumber;

public:
  // Constructor - initialize the account
  BankAccount(string name, int accNum, double initialBalance) {
    accountHolder = name;
    accountNumber = accNum;
    balance = (initialBalance >= 0) ? initialBalance : 0;
  }

  // GETTER: Retrieve account holder name
  string getAccountHolder() const { return accountHolder; }

  // GETTER: Retrieve account number
  int getAccountNumber() const { return accountNumber; }

  // GETTER: Retrieve current balance
  double getBalance() const { return balance; }

  // SETTER: Deposit money (with validation)
  void deposit(double amount) {
    if (amount > 0) {
      balance += amount;
      cout << "Deposited: $" << amount << endl;
    } else {
      cout << "Error: Deposit amount must be positive!" << endl;
    }
  }

  // SETTER: Withdraw money (with validation)
  bool withdraw(double amount) {
    if (amount <= 0) {
      cout << "Error: Withdrawal amount must be positive!" << endl;
      return false;
    }
    if (amount > balance) {
      cout << "Error: Insufficient funds!" << endl;
      return false;
    }
    balance -= amount;
    cout << "Withdrawn: $" << amount << endl;
    return true;
  }
};

/*
OUTPUT:
--------
Account: Alice (123456), Balance: $1000
Deposited: $500
Withdrawn: $200
Current Balance: $1300

--------
*/

/*
================================================================================
EXAMPLE 2: ENCAPSULATION WITH VALIDATION - STUDENT GRADES
================================================================================
*/

class Student {
private:
  string name;
  int studentID;
  double gpa; // Must be between 0.0 and 4.0

  // Private helper method - validates GPA
  bool isValidGPA(double value) const { return (value >= 0.0 && value <= 4.0); }

public:
  Student(string n, int id, double g) : name(n), studentID(id), gpa(0.0) {
    setGPA(g); // Use setter to validate
  }

  // GETTER: Get student name
  string getName() const { return name; }

  // GETTER: Get student ID
  int getStudentID() const { return studentID; }

  // GETTER: Get GPA
  double getGPA() const { return gpa; }

  // SETTER: Set GPA with validation
  void setGPA(double newGPA) {
    if (isValidGPA(newGPA)) {
      gpa = newGPA;
      cout << "GPA updated to: " << gpa << endl;
    } else {
      cout << "Error: GPA must be between 0.0 and 4.0!" << endl;
    }
  }

  // GETTER: Get letter grade from GPA
  char getGradeFromGPA() const {
    if (gpa >= 3.7)
      return 'A';
    if (gpa >= 3.3)
      return 'A';
    if (gpa >= 3.0)
      return 'B';
    if (gpa >= 2.7)
      return 'B';
    if (gpa >= 2.3)
      return 'C';
    if (gpa >= 2.0)
      return 'C';
    return 'F';
  }

  // Display student info
  void displayInfo() const {
    cout << "Name: " << name << " | ID: " << studentID << " | GPA: " << gpa
         << " | Grade: " << getGradeFromGPA() << endl;
  }
};

/*
OUTPUT:
--------
Name: John | ID: 1001 | GPA: 3.8 | Grade: A
GPA updated to: 3.5

--------
*/

/*
================================================================================
EXAMPLE 3: ENCAPSULATION WITH CLASS INVARIANTS - RECTANGLE
================================================================================
*/

class Rectangle {
private:
  double width;
  double height;
  // CLASS INVARIANT: width > 0 AND height > 0
  // These must ALWAYS be true

  // Private helper to validate dimensions
  bool isValidDimension(double dim) const { return dim > 0; }

public:
  // Constructor
  Rectangle(double w, double h) {
    if (isValidDimension(w) && isValidDimension(h)) {
      width = w;
      height = h;
    } else {
      // Ensure invariant is maintained
      width = 1.0;
      height = 1.0;
      cout << "Invalid dimensions. Set to default 1x1" << endl;
    }
  }

  // GETTER: Get width
  double getWidth() const { return width; }

  // GETTER: Get height
  double getHeight() const { return height; }

  // SETTER: Set width (maintains invariant)
  void setWidth(double w) {
    if (isValidDimension(w)) {
      width = w;
    } else {
      cout << "Error: Width must be positive!" << endl;
    }
  }

  // SETTER: Set height (maintains invariant)
  void setHeight(double h) {
    if (isValidDimension(h)) {
      height = h;
    } else {
      cout << "Error: Height must be positive!" << endl;
    }
  }

  // Calculate area
  double getArea() const { return width * height; }

  // Calculate perimeter
  double getPerimeter() const { return 2 * (width + height); }

  // Display properties
  void display() const {
    cout << "Rectangle: " << width << " x " << height
         << " | Area: " << getArea() << " | Perimeter: " << getPerimeter()
         << endl;
  }
};

/*
OUTPUT:
--------
Rectangle: 5 x 3 | Area: 15 | Perimeter: 16
Rectangle: 10 x 4 | Area: 40 | Perimeter: 28

--------
*/

/*
================================================================================
EXAMPLE 4: PRIVATE AND PUBLIC INTERFACE - TEMPERATURE CONVERTER
================================================================================
*/

class Temperature {
private:
  double celsius; // Internal storage

  // Private helper: Convert Fahrenheit to Celsius
  double fahrenheitToCelsius(double f) const { return (f - 32) * 5 / 9; }

  // Private helper: Convert Celsius to Fahrenheit
  double celsiusToFahrenheit(double c) const { return (c * 9 / 5) + 32; }

public:
  // Constructor - accepts Celsius
  Temperature(double c = 0) : celsius(c) {}

  // PUBLIC INTERFACE: Set temperature in Celsius
  void setCelsius(double c) { celsius = c; }

  // PUBLIC INTERFACE: Set temperature in Fahrenheit
  void setFahrenheit(double f) { celsius = fahrenheitToCelsius(f); }

  // PUBLIC INTERFACE: Get temperature in Celsius
  double getCelsius() const { return celsius; }

  // PUBLIC INTERFACE: Get temperature in Fahrenheit
  double getFahrenheit() const { return celsiusToFahrenheit(celsius); }

  // PUBLIC INTERFACE: Display both scales
  void display() const {
    cout << "Temperature: " << celsius << "°C = " << getFahrenheit() << "°F"
         << endl;
  }
};

/*
OUTPUT:
--------
Temperature: 25°C = 77°F
Temperature: 32°C = 89.6°F

--------
*/

/*
================================================================================
EXAMPLE 5: ENCAPSULATION WITH CONST GETTERS - PERSON CLASS
================================================================================
*/

class Person {
private:
  string firstName;
  string lastName;
  int age;
  double height; // in meters

public:
  Person(string first, string last, int a, double h)
      : firstName(first), lastName(last), age(a), height(h) {}

  // CONST GETTER: Returns const reference (more efficient)
  const string &getFirstName() const { return firstName; }

  // CONST GETTER: Returns const reference
  const string &getLastName() const { return lastName; }

  // GETTER: Returns by value (int is small)
  int getAge() const { return age; }

  // GETTER: Returns by value (double is small)
  double getHeight() const { return height; }

  // SETTER: Update age with validation
  void setAge(int newAge) {
    if (newAge > 0 && newAge < 150) {
      age = newAge;
      cout << "Age updated to: " << age << endl;
    } else {
      cout << "Error: Invalid age!" << endl;
    }
  }

  // SETTER: Update height with validation
  void setHeight(double newHeight) {
    if (newHeight > 0 && newHeight < 3.0) {
      height = newHeight;
      cout << "Height updated to: " << height << "m" << endl;
    } else {
      cout << "Error: Invalid height!" << endl;
    }
  }

  // Display full information
  void displayInfo() const {
    cout << "Person: " << firstName << " " << lastName << " | Age: " << age
         << " | Height: " << height << "m" << endl;
  }
};

/*
OUTPUT:
--------
Person: John Doe | Age: 30 | Height: 1.75m
Age updated to: 31

--------
*/

/*
================================================================================
EXAMPLE 6: ENCAPSULATION IN COUNTER CLASS - PREVENTING INVALID STATES
================================================================================
*/

class Counter {
private:
  int value;
  int minValue;
  int maxValue;

public:
  Counter(int min = 0, int max = 100)
      : minValue(min), maxValue(max), value(min) {}

  // GETTER: Get current value
  int getValue() const { return value; }

  // Increment (with boundary check)
  void increment() {
    if (value < maxValue) {
      value++;
    } else {
      cout << "Counter at maximum!" << endl;
    }
  }

  // Decrement (with boundary check)
  void decrement() {
    if (value > minValue) {
      value--;
    } else {
      cout << "Counter at minimum!" << endl;
    }
  }

  // SETTER: Set value (with validation)
  void setValue(int newValue) {
    if (newValue >= minValue && newValue <= maxValue) {
      value = newValue;
    } else {
      cout << "Error: Value must be between " << minValue << " and " << maxValue
           << "!" << endl;
    }
  }

  // Display state
  void display() const {
    cout << "Counter: " << value << " [" << minValue << "-" << maxValue << "]"
         << endl;
  }
};

/*
OUTPUT:
--------
Counter: 0 [0-100]
Counter: 5 [0-100]
Counter at maximum!
Counter: 100 [0-100]

--------
*/

/*
================================================================================
EXAMPLE 7: READ-ONLY PROPERTIES
================================================================================
*/

class Circle {
private:
  double radius;
  static const double PI; // = 3.14159265359

public:
  Circle(double r) : radius(r) {}

  // GETTER: Get radius
  double getRadius() const { return radius; }

  // SETTER: Set radius with validation
  void setRadius(double r) {
    if (r > 0) {
      radius = r;
    } else {
      cout << "Error: Radius must be positive!" << endl;
    }
  }

  // READ-ONLY: Area (computed, no setter)
  double getArea() const { return PI * radius * radius; }

  // READ-ONLY: Circumference (computed, no setter)
  double getCircumference() const { return 2 * PI * radius; }

  void display() const {
    cout << "Circle: radius=" << radius << " | area=" << getArea()
         << " | circumference=" << getCircumference() << endl;
  }
};

// Static member definition
const double Circle::PI = 3.14159265359;

/*
OUTPUT:
--------
Circle: radius=5 | area=78.5397 | circumference=31.4159

--------
*/

/*
================================================================================
EXAMPLE 8: ENCAPSULATION WITH TIME CLASS
================================================================================
*/

class Time {
private:
  int hours;
  int minutes;
  int seconds;

  // Private helper: Validate time
  bool isValidTime(int h, int m, int s) const {
    return (h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60);
  }

public:
  Time(int h = 0, int m = 0, int s = 0) {
    if (isValidTime(h, m, s)) {
      hours = h;
      minutes = m;
      seconds = s;
    } else {
      hours = 0;
      minutes = 0;
      seconds = 0;
      cout << "Invalid time. Set to 00:00:00" << endl;
    }
  }

  // GETTERS
  int getHours() const { return hours; }
  int getMinutes() const { return minutes; }
  int getSeconds() const { return seconds; }

  // SETTERS with validation
  void setHours(int h) {
    if (h >= 0 && h < 24) {
      hours = h;
    } else {
      cout << "Invalid hours!" << endl;
    }
  }

  void setMinutes(int m) {
    if (m >= 0 && m < 60) {
      minutes = m;
    } else {
      cout << "Invalid minutes!" << endl;
    }
  }

  void setSeconds(int s) {
    if (s >= 0 && s < 60) {
      seconds = s;
    } else {
      cout << "Invalid seconds!" << endl;
    }
  }

  // Tick: increment by one second
  void tick() {
    seconds++;
    if (seconds == 60) {
      seconds = 0;
      minutes++;
      if (minutes == 60) {
        minutes = 0;
        hours++;
        if (hours == 24) {
          hours = 0;
        }
      }
    }
  }

  void display() const {
    cout << (hours < 10 ? "0" : "") << hours << ":" << (minutes < 10 ? "0" : "")
         << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << endl;
  }
};

/*
OUTPUT:
--------
12:30:45
12:30:46

--------
*/

/*
================================================================================
KEY CONCEPTS SUMMARY BOX
================================================================================

WHAT IS ENCAPSULATION?
- Bundling data and methods into a class
- Hiding internal implementation details
- Exposing only necessary interface to users
- Controlling access through public, private, protected

WHY USE ENCAPSULATION?
✓ Data Protection: Prevent invalid states
✓ Flexibility: Change implementation without affecting users
✓ Maintainability: Easy to modify internal logic
✓ Clear Interface: Users know what they can interact with
✓ Validation: Setters ensure valid data

ACCESS MODIFIERS:
- private: Only accessible within the class
- public: Accessible from outside the class
- protected: Accessible in derived classes (inheritance)

GETTERS & SETTERS:
- Getter (accessor): Returns value of private member
- Setter (mutator): Modifies value with validation
- Keep setters in sync with getters
- Return const reference for efficiency

CLASS INVARIANTS:
- Conditions that must ALWAYS be true
- Example: "balance >= 0", "width > 0"
- Constructor establishes invariants
- Methods maintain invariants

================================================================================
*/

/*
================================================================================
TRUTH TABLE: ACCESS MODIFIERS
================================================================================

Member Type     | Same Class | Derived Class | Outside Class
===============================================================
public          |    YES     |     YES       |     YES
protected       |    YES     |     YES       |      NO
private         |    YES     |      NO       |      NO

Usage Example:
- public: Interface for users
- private: Implementation details
- protected: Shared with derived classes

================================================================================
*/

/*
================================================================================
COMMON MISTAKES
================================================================================

❌ MISTAKE 1: Returning private data by non-const reference
    vector<int>& getData() { return data; }  // BAD!

✓ CORRECT:
    const vector<int>& getData() const { return data; }

-----

❌ MISTAKE 2: Making everything public (no encapsulation)
    class BadClass {
    public:
        int balance;  // Anyone can modify!
        void withdraw(int amt) { balance -= amt; }
    };

✓ CORRECT:
    class GoodClass {
    private:
        int balance;
    public:
        void withdraw(int amt) {
            if (amt > 0 && amt <= balance) balance -= amt;
        }
    };

-----

❌ MISTAKE 3: Getters modifying state
    int getValue() { count++; return value; }  // BAD!

✓ CORRECT:
    int getValue() const { return value; }

-----

❌ MISTAKE 4: Not validating in setters
    void setAge(int a) { age = a; }  // No validation!

✓ CORRECT:
    void setAge(int a) {
        if (a > 0 && a < 150) age = a;
    }

-----

❌ MISTAKE 5: Breaking encapsulation for "convenience"
    void giveDirectAccess() { return &balance; }

✓ CORRECT: Provide only necessary getters/setters

================================================================================
*/

/*
================================================================================
PRACTICE EXERCISES
================================================================================

Exercise 1: Create a Date class with private date, month, year
- Validate that month is 1-12, day is valid for that month
- Provide getters and setters
- Add method to advance by one day

Exercise 2: Create a Money class with private amount and currency
- Validate that amount is non-negative
- Provide getters and setters
- Add method to add money to this amount

Exercise 3: Create a TemperatureRange class
- Private: minTemp, maxTemp, currentTemp
- Validate that minTemp < maxTemp
- Setters should keep current temp within range
- Provide getters for all

Exercise 4: Create an Employee class
- Private: name, salary, employeeID
- Salary must be positive
- Salary changes should be logged
- No direct access to any member

Exercise 5: Create a Book class
- Private: title, author, ISBN, pages, currentPage
- currentPage must be <= pages and >= 0
- Provide method to turn page (respects max pages)
- Provide getter for progress percentage

Exercise 6: Create a Password class
- Private: password string
- Setter validates: min 8 chars, at least 1 uppercase, 1 digit
- Getter never returns the password (returns "*" count instead)
- Provide verify() method to check password

Exercise 7: Create a BankingAccount that maintains balance
- Can't directly access balance
- Deposit always adds (with validation)
- Withdraw always checks balance
- Maintains class invariant: balance >= 0

Exercise 8: Create a Library class
- Private: list of books, max capacity
- Can't directly access book list
- Provide addBook() and removeBook() methods
- Maintain class invariant: book count <= capacity

================================================================================
*/

// Main demonstration
int main() {
  cout << "================== ENCAPSULATION EXAMPLES ==================\n\n";

  // Example 1: Bank Account
  cout << "--- EXAMPLE 1: BANK ACCOUNT ---\n";
  BankAccount acc1("Alice", 123456, 1000);
  cout << "Account: " << acc1.getAccountHolder() << " | Balance: $"
       << acc1.getBalance() << endl;
  acc1.deposit(500);
  acc1.withdraw(200);
  cout << "New Balance: $" << acc1.getBalance() << "\n\n";

  // Example 2: Student Grades
  cout << "--- EXAMPLE 2: STUDENT GRADES ---\n";
  Student student1("John", 1001, 3.8);
  student1.displayInfo();
  student1.setGPA(3.5);
  student1.displayInfo();
  student1.setGPA(5.0); // Invalid
  cout << "\n";

  // Example 3: Rectangle
  cout << "--- EXAMPLE 3: RECTANGLE ---\n";
  Rectangle rect1(5, 3);
  rect1.display();
  rect1.setWidth(10);
  rect1.setHeight(4);
  rect1.display();
  cout << "\n";

  // Example 4: Temperature Converter
  cout << "--- EXAMPLE 4: TEMPERATURE CONVERTER ---\n";
  Temperature temp1(25);
  temp1.display();
  temp1.setFahrenheit(77);
  temp1.display();
  cout << "\n";

  // Example 5: Person
  cout << "--- EXAMPLE 5: PERSON CLASS ---\n";
  Person person1("John", "Doe", 30, 1.75);
  person1.displayInfo();
  person1.setAge(31);
  person1.displayInfo();
  cout << "\n";

  // Example 6: Counter
  cout << "--- EXAMPLE 6: COUNTER ---\n";
  Counter counter1(0, 100);
  counter1.display();
  counter1.setValue(50);
  counter1.display();
  counter1.increment();
  counter1.display();
  cout << "\n";

  // Example 7: Circle
  cout << "--- EXAMPLE 7: CIRCLE (READ-ONLY PROPERTIES) ---\n";
  Circle circle1(5);
  circle1.display();
  circle1.setRadius(10);
  circle1.display();
  cout << "\n";

  // Example 8: Time
  cout << "--- EXAMPLE 8: TIME CLASS ---\n";
  Time time1(23, 59, 58);
  cout << "Time: ";
  time1.display();
  time1.tick();
  cout << "After tick: ";
  time1.display();
  time1.tick();
  cout << "After tick: ";
  time1.display();
  cout << "\n";

  return 0;
}

/*
================================================================================
FULL PROGRAM OUTPUT:
================================================================================

================== ENCAPSULATION EXAMPLES ==================

--- EXAMPLE 1: BANK ACCOUNT ---
Account: Alice | Balance: $1000
Deposited: $500
Withdrawn: $200
New Balance: $1300

--- EXAMPLE 2: STUDENT GRADES ---
Name: John | ID: 1001 | GPA: 3.8 | Grade: A
GPA updated to: 3.5
Name: John | ID: 1001 | GPA: 3.5 | Grade: A
Error: GPA must be between 0.0 and 4.0!

--- EXAMPLE 3: RECTANGLE ---
Rectangle: 5 x 3 | Area: 15 | Perimeter: 16
Rectangle: 10 x 4 | Area: 40 | Perimeter: 28

--- EXAMPLE 4: TEMPERATURE CONVERTER ---
Temperature: 25°C = 77°F
Temperature: 25°C = 77°F

--- EXAMPLE 5: PERSON CLASS ---
Person: John Doe | Age: 30 | Height: 1.75m
Age updated to: 31
Person: John Doe | Age: 31 | Height: 1.75m

--- EXAMPLE 6: COUNTER ---
Counter: 0 [0-100]
Counter: 50 [0-100]
Counter: 51 [0-100]

--- EXAMPLE 7: CIRCLE (READ-ONLY PROPERTIES) ---
Circle: radius=5 | area=78.5397 | circumference=31.4159
Circle: radius=10 | area=314.159 | circumference=62.8319

--- EXAMPLE 8: TIME CLASS ---
Time: 23:59:58
After tick: 23:59:59
After tick: 00:00:00

================================================================================
*/
