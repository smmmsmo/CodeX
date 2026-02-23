/*
================================================================================
TOPIC 9: CLASSES AND OBJECTS - PART 1: CLASS BASICS AND ACCESS MODIFIERS
================================================================================

WHAT IS A CLASS?
- A blueprint for creating objects
- Groups related data and functions together
- Enables Object-Oriented Programming (OOP)
- User-defined data type

KEY CONCEPTS:
- CLASS: Template/blueprint
- OBJECT: Instance of a class
- MEMBER VARIABLES: Data members (attributes)
- MEMBER FUNCTIONS: Methods (behaviors)
- ACCESS MODIFIERS: Control visibility

CLASS DECLARATION SYNTAX:
class ClassName {
    access_modifier:
        data_members;
        member_functions();
};

ACCESS MODIFIERS:
- public: Accessible from outside the class
- private: Only accessible within the class
- protected: Accessible in class and derived classes (inheritance)

DEFAULT: private (for classes)

================================================================================
*/

#include <iostream>
#include <string>
using namespace std;

// ======================= SIMPLE CLASS EXAMPLE =======================
class Student {
public:
  // Member variables (attributes)
  string name;
  int roll_number;
  double gpa;

  // Member function (method)
  void display() {
    cout << "Name: " << name << endl;
    cout << "Roll: " << roll_number << endl;
    cout << "GPA: " << gpa << endl;
  }
};

// ======================= CLASS WITH PRIVATE MEMBERS =======================
class BankAccount {
private:
  string account_number;
  double balance;
  string password;

public:
  // Public methods to access private data
  void setAccountNumber(string acc_no) { account_number = acc_no; }

  string getAccountNumber() { return account_number; }

  void setBalance(double bal) {
    if (bal >= 0) {
      balance = bal;
    } else {
      cout << "Invalid balance!" << endl;
    }
  }

  double getBalance() { return balance; }

  void displayInfo() {
    cout << "Account: " << account_number << endl;
    cout << "Balance: $" << balance << endl;
  }
};

// ======================= RECTANGLE CLASS =======================
class Rectangle {
private:
  double length;
  double width;

public:
  // Public methods
  void setDimensions(double l, double w) {
    if (l > 0 && w > 0) {
      length = l;
      width = w;
    } else {
      cout << "Invalid dimensions!" << endl;
    }
  }

  double getArea() { return length * width; }

  double getPerimeter() { return 2 * (length + width); }

  void display() {
    cout << "Length: " << length << ", Width: " << width << endl;
    cout << "Area: " << getArea() << ", Perimeter: " << getPerimeter() << endl;
  }
};

// ======================= CAR CLASS =======================
class Car {
private:
  string brand;
  string model;
  int year;
  double mileage;

public:
  // Public methods
  void initialize(string b, string m, int y, double mi) {
    brand = b;
    model = m;
    year = y;
    mileage = mi;
  }

  void drive(double distance) {
    mileage += distance;
    cout << "Drove " << distance << " km. Total mileage: " << mileage << " km"
         << endl;
  }

  void showInfo() {
    cout << "Car: " << year << " " << brand << " " << model << endl;
    cout << "Mileage: " << mileage << " km" << endl;
  }
};

// ======================= PERSON CLASS =======================
class Person {
private:
  string first_name;
  string last_name;
  int age;
  string email;

public:
  // Setters with validation
  void setFirstName(string fname) {
    if (!fname.empty()) {
      first_name = fname;
    }
  }

  void setLastName(string lname) {
    if (!lname.empty()) {
      last_name = lname;
    }
  }

  void setAge(int a) {
    if (a > 0 && a < 150) {
      age = a;
    } else {
      cout << "Invalid age!" << endl;
    }
  }

  void setEmail(string e) {
    if (!e.empty() && e.find('@') != string::npos) {
      email = e;
    } else {
      cout << "Invalid email!" << endl;
    }
  }

  // Getters
  string getFirstName() { return first_name; }
  string getLastName() { return last_name; }
  int getAge() { return age; }
  string getEmail() { return email; }

  // Display method
  void displayInfo() {
    cout << "Name: " << first_name << " " << last_name << endl;
    cout << "Age: " << age << endl;
    cout << "Email: " << email << endl;
  }
};

int main() {
  cout << "=== CLASSES AND OBJECTS - BASICS ===" << endl << endl;

  // ======================= CREATING AND USING OBJECTS =======================
  cout << "1. CREATING AND USING OBJECTS:" << endl;

  Student s1;
  s1.name = "Alice";
  s1.roll_number = 101;
  s1.gpa = 3.8;

  cout << "Student 1:" << endl;
  s1.display();

  Student s2;
  s2.name = "Bob";
  s2.roll_number = 102;
  s2.gpa = 3.5;

  cout << endl << "Student 2:" << endl;
  s2.display();

  // ======================= PRIVATE MEMBERS AND ENCAPSULATION
  // =======================
  cout << endl << "2. ENCAPSULATION WITH PRIVATE MEMBERS:" << endl;

  BankAccount account1;
  account1.setAccountNumber("ACC123456");
  account1.setBalance(5000);

  cout << "Account created:" << endl;
  account1.displayInfo();

  cout << endl << "Attempting to set invalid balance:" << endl;
  account1.setBalance(-100);

  cout << endl << "Setting valid balance:" << endl;
  account1.setBalance(7500);
  account1.displayInfo();

  // ======================= RECTANGLE CLASS =======================
  cout << endl << "3. RECTANGLE CLASS:" << endl;

  Rectangle rect1;
  rect1.setDimensions(5, 10);
  cout << "Rectangle 1:" << endl;
  rect1.display();

  Rectangle rect2;
  rect2.setDimensions(3.5, 7.2);
  cout << endl << "Rectangle 2:" << endl;
  rect2.display();

  // ======================= CAR CLASS =======================
  cout << endl << "4. CAR CLASS WITH OBJECT STATE:" << endl;

  Car car1;
  car1.initialize("Toyota", "Camry", 2022, 15000);
  car1.showInfo();

  cout << endl << "After driving:" << endl;
  car1.drive(150);
  car1.drive(75);
  car1.showInfo();

  // ======================= PERSON CLASS =======================
  cout << endl << "5. PERSON CLASS WITH VALIDATION:" << endl;

  Person person1;
  person1.setFirstName("Charlie");
  person1.setLastName("Brown");
  person1.setAge(25);
  person1.setEmail("charlie@example.com");

  cout << "Valid person created:" << endl;
  person1.displayInfo();

  cout << endl << "Attempting invalid age:" << endl;
  person1.setAge(-5);

  cout << endl << "Attempting invalid email:" << endl;
  person1.setEmail("invalid-email");

  // ======================= MULTIPLE OBJECTS =======================
  cout << endl << "6. MULTIPLE OBJECTS OF SAME CLASS:" << endl;

  Person p1, p2, p3;

  p1.setFirstName("Diana");
  p1.setLastName("Prince");
  p1.setAge(30);
  p1.setEmail("diana@example.com");

  p2.setFirstName("Evan");
  p2.setLastName("Evans");
  p2.setAge(28);
  p2.setEmail("evan@example.com");

  cout << "Person 1:" << endl;
  p1.displayInfo();

  cout << endl << "Person 2:" << endl;
  p2.displayInfo();

  // ======================= COMPARING OBJECTS =======================
  cout << endl << "7. MEMBER FUNCTION CALLS:" << endl;

  Rectangle rect3, rect4;
  rect3.setDimensions(4, 6);
  rect4.setDimensions(5, 5);

  cout << "Rectangle 3 area: " << rect3.getArea() << endl;
  cout << "Rectangle 4 area: " << rect4.getArea() << endl;

  if (rect3.getArea() > rect4.getArea()) {
    cout << "Rectangle 3 is larger" << endl;
  } else if (rect4.getArea() > rect3.getArea()) {
    cout << "Rectangle 4 is larger" << endl;
  } else {
    cout << "Both rectangles are equal in area" << endl;
  }

  // ======================= OBJECT ARRAY =======================
  cout << endl << "8. ARRAY OF OBJECTS:" << endl;

  Car fleet[3];
  fleet[0].initialize("Honda", "Civic", 2023, 5000);
  fleet[1].initialize("Ford", "Focus", 2022, 12000);
  fleet[2].initialize("BMW", "3 Series", 2021, 25000);

  cout << "Car Fleet:" << endl;
  for (int i = 0; i < 3; i++) {
    cout << "Car " << (i + 1) << ":" << endl;
    fleet[i].showInfo();
    cout << endl;
  }

  return 0;
}

/*
OUTPUT:
=== CLASSES AND OBJECTS - BASICS ===

1. CREATING AND USING OBJECTS:
Student 1:
Name: Alice
Roll: 101
GPA: 3.8

Student 2:
Name: Bob
Roll: 102
GPA: 3.5

2. ENCAPSULATION WITH PRIVATE MEMBERS:
Account created:
Account: ACC123456
Balance: $5000

Attempting to set invalid balance:
Invalid balance!

Setting valid balance:
Account: ACC123456
Balance: $7500

3. RECTANGLE CLASS:
Rectangle 1:
Length: 5, Width: 10
Area: 50, Perimeter: 30

Rectangle 2:
Length: 3.5, Width: 7.2
Area: 25.2, Perimeter: 21.4

4. CAR CLASS WITH OBJECT STATE:
Car: 2022 Toyota Camry
Mileage: 15000 km

After driving:
Drove 150 km. Total mileage: 15150 km
Drove 75 km. Total mileage: 15225 km
Car: 2022 Toyota Camry
Mileage: 15225 km

5. PERSON CLASS WITH VALIDATION:
Valid person created:
Name: Charlie Brown
Age: 25
Email: charlie@example.com

Attempting invalid age:
Invalid age!

Attempting invalid email:
Invalid email!

6. MULTIPLE OBJECTS OF SAME CLASS:
Person 1:
Name: Diana Prince
Age: 30
Email: diana@example.com

Person 2:
Name: Evan Evans
Age: 28
Email: evan@example.com

7. MEMBER FUNCTION CALLS:
Rectangle 3 area: 24
Rectangle 4 area: 25
Rectangle 4 is larger

8. ARRAY OF OBJECTS:
Car Fleet:
Car 1:
Car: 2023 Honda Civic
Mileage: 5000 km

Car 2:
Car: 2022 Ford Focus
Mileage: 12000 km

Car 3:
Car: 2021 BMW 3 Series
Mileage: 25000 km

================================================================================
KEY CONCEPTS
================================================================================

1. CLASS vs OBJECT:
   - CLASS: Blueprint/template (defines structure)
   - OBJECT: Instance of class (actual data)
   - One class can have many objects

2. MEMBER VARIABLES:
   - Store data/state for each object
   - Each object has its own copy
   - Can be public, private, protected

3. MEMBER FUNCTIONS:
   - Define behavior/operations
   - Operate on member variables
   - Can be public, private, protected

4. ACCESS MODIFIERS:
   - public: Accessible from anywhere
   - private: Only within class
   - protected: Class + derived classes (later)
   - Default for class: private

5. ENCAPSULATION:
   - Hide internal details (private)
   - Provide controlled access (public methods)
   - Enables data validation

6. GETTER/SETTER METHODS:
   - getters: Return member variable values
   - setters: Modify member variables (with validation)

================================================================================
CLASS STRUCTURE SUMMARY
================================================================================

class ClassName {
public:
    // Public members - accessible from outside
    int public_var;
    void public_method() { }

private:
    // Private members - only accessible inside
    int private_var;
    void private_method() { }

protected:
    // Protected - for inheritance
    int protected_var;
};

Object Creation:
ClassName obj;              // Stack allocation
ClassName* ptr = new ClassName();  // Heap allocation

Accessing members:
obj.public_var;            // Dot operator
obj.public_method();

ptr->public_var;           // Arrow operator
ptr->public_method();

================================================================================
PRACTICE EXERCISES
================================================================================

1. Create a Book class with title, author, pages, price
   - Use getters/setters with validation
   - Add method to calculate rental cost

2. Create a Temperature class
   - Store temperature in Celsius
   - Provide methods to convert to Fahrenheit
   - Add methods to compare temperatures

3. Create a Time class
   - Store hours, minutes, seconds
   - Add method to display time
   - Add method to increment time

4. Create a BankAccount class (improved)
   - Deposit and withdrawal methods
   - Transaction history
   - Interest calculation

5. Create an Employee class
   - Store name, ID, salary, department
   - Add method to calculate bonus
   - Add method to give raise

================================================================================
*/
