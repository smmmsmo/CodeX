/*
================================================================================
INHERITANCE BASICS - BASE AND DERIVED CLASSES
================================================================================
Part 2, Subtopic 11: Inheritance (File 1/2)

CONCEPTS COVERED:
- What is inheritance?
- Base classes and derived classes
- Access modifiers in inheritance (public, private, protected)
- Constructor and destructor in inheritance
- Function overriding
- Using base class members in derived class
- Object slicing and dynamic binding

KEY LEARNING POINTS:
1. Inheritance creates "is-a" relationships between classes
2. Derived classes inherit members from base classes
3. Access modifiers control visibility in inheritance
4. Constructors initialize base class members first
5. Destructors are called in reverse order
6. Function overriding replaces base class behavior
7. Protected members are accessible in derived classes

================================================================================
*/

#include <cmath>
#include <iostream>
#include <string>

using namespace std;

/*
================================================================================
THEORY SECTION: WHAT IS INHERITANCE?
================================================================================

Inheritance is a mechanism to reuse code and establish "is-a" relationships.

CONCEPT:
A derived class (child) inherits members and methods from a base class (parent).
This allows code reuse and creates a hierarchy of classes.

EXAMPLE HIERARCHY:
        Vehicle (Base)
         /      \
      Car      Motorcycle
      (Derived) (Derived)

BENEFITS:
1. Code Reuse: Don't repeat common functionality
2. Logical Organization: Creates class hierarchies
3. Polymorphism: Enables runtime behavior changes
4. Extensibility: Easy to add new derived classes

ACCESS MODIFIERS IN INHERITANCE:
- public inheritance: Public members stay public in derived class
- private inheritance: All inherited members become private
- protected inheritance: Public becomes protected, protected stays protected

================================================================================
*/

/*
================================================================================
EXAMPLE 1: SIMPLE INHERITANCE - ANIMAL AND DOG
================================================================================
*/

class Animal {
private:
  string name; // Private - not directly accessible in derived class

protected:
  int age; // Protected - accessible in derived class

public:
  // Constructor
  Animal(string n, int a) : name(n), age(a) {
    cout << "Animal constructor called for " << name << endl;
  }

  // Virtual destructor (good practice)
  virtual ~Animal() { cout << "Animal destructor called for " << name << endl; }

  // Public getter
  string getName() const { return name; }

  // Member function (can be overridden)
  virtual void makeSound() const {
    cout << name << " makes a generic animal sound" << endl;
  }

  // Function to display info
  void displayInfo() const {
    cout << "Name: " << name << " | Age: " << age << endl;
  }
};

// Dog is derived from Animal using public inheritance
class Dog : public Animal {
private:
  string breed;

public:
  // Constructor - must call base class constructor
  Dog(string n, int a, string b) : Animal(n, a), breed(b) {
    cout << "Dog constructor called" << endl;
  }

  // Destructor
  ~Dog() { cout << "Dog destructor called" << endl; }

  // Getter
  string getBreed() const { return breed; }

  // Override base class function
  void makeSound() const override {
    cout << getName() << " barks: Woof! Woof!" << endl;
  }

  // Derived class specific method
  void fetch() { cout << getName() << " is fetching the ball!" << endl; }

  // Display dog info
  void displayInfo() const {
    Animal::displayInfo(); // Call base class method
    cout << "Breed: " << breed << endl;
  }
};

/*
OUTPUT:
--------
Animal constructor called for Buddy
Dog constructor called
Name: Buddy | Age: 5
Breed: Golden Retriever
Buddy barks: Woof! Woof!
Dog destructor called
Animal destructor called for Buddy

--------
*/

/*
================================================================================
EXAMPLE 2: MULTIPLE ACCESS MODIFIERS - INHERITANCE VISIBILITY
================================================================================
*/

class Vehicle {
public:
  string brand;

protected:
  int wheels;

private:
  int engineCode;

public:
  Vehicle(string b, int w) : brand(b), wheels(w), engineCode(12345) {}

  void drive() {
    cout << brand << " is driving with " << wheels << " wheels" << endl;
  }
};

class Car : public Vehicle {
  // brand is public (public inheritance)
  // wheels is protected (public inheritance)
  // engineCode is NOT accessible (private in base)

public:
  Car(string b) : Vehicle(b, 4) {}

  void carSpecific() {
    cout << "Car brand: " << brand << endl;   // OK: public
    cout << "Car wheels: " << wheels << endl; // OK: protected
    // cout << engineCode << endl;                   // ERROR: private
  }
};

/*
OUTPUT:
--------
Car brand: Toyota
Car wheels: 4

--------
*/

/*
================================================================================
EXAMPLE 3: PROTECTED INHERITANCE
================================================================================
*/

class Shape {
public:
  virtual void draw() const { cout << "Drawing a generic shape" << endl; }
};

class Circle : protected Shape {
  // Shape::draw() is now protected (not public)
public:
  void display() {
    draw(); // OK: can call protected member inside derived class
  }
};

class SmallCircle : public Circle {
public:
  void show() {
    // draw();  // ERROR: inherited as protected from Circle
    display(); // OK: can call public method of Circle
  }
};

/*
OUTPUT:
--------
Drawing a generic shape

--------
*/

/*
================================================================================
EXAMPLE 4: CONSTRUCTOR AND DESTRUCTOR CHAIN
================================================================================
*/

class GrandParent {
public:
  string gpName;

  GrandParent(string name) : gpName(name) {
    cout << "1. GrandParent constructor: " << gpName << endl;
  }

  ~GrandParent() { cout << "6. GrandParent destructor" << endl; }
};

class Parent : public GrandParent {
public:
  string pName;

  Parent(string gp, string p) : GrandParent(gp), pName(p) {
    cout << "2. Parent constructor: " << pName << endl;
  }

  ~Parent() { cout << "5. Parent destructor" << endl; }
};

class Child : public Parent {
public:
  string cName;

  Child(string gp, string p, string c) : Parent(gp, p), cName(c) {
    cout << "3. Child constructor: " << cName << endl;
  }

  ~Child() { cout << "4. Child destructor" << endl; }
};

/*
OUTPUT:
--------
1. GrandParent constructor: John
2. Parent constructor: Jane
3. Child constructor: Bob
4. Child destructor
5. Parent destructor
6. GrandParent destructor

--------
*/

/*
================================================================================
EXAMPLE 5: FUNCTION OVERRIDING
================================================================================
*/

class Animal5 {
public:
  virtual ~Animal5() {}

  virtual void eat() const { cout << "Animal is eating" << endl; }

  virtual void sleep() const { cout << "Animal is sleeping" << endl; }

  // Non-virtual function (cannot be overridden)
  void breathe() const { cout << "Animal is breathing" << endl; }
};

class Cat : public Animal5 {
public:
  void eat() const override { cout << "Cat is eating fish" << endl; }

  void sleep() const override { cout << "Cat is sleeping in the sun" << endl; }

  // breathe() is inherited as-is (not overridden)
};

class Bird : public Animal5 {
public:
  void eat() const override { cout << "Bird is eating seeds" << endl; }

  void sleep() const override {
    cout << "Bird is sleeping on a branch" << endl;
  }
};

/*
OUTPUT:
--------
Cat is eating fish
Cat is sleeping in the sun
Animal is breathing
Bird is eating seeds

--------
*/

/*
================================================================================
EXAMPLE 6: EMPLOYEE HIERARCHY
================================================================================
*/

class Employee {
protected:
  string name;
  double salary;
  string position;

public:
  Employee(string n, double s, string p) : name(n), salary(s), position(p) {}

  virtual ~Employee() {}

  virtual void displayInfo() const {
    cout << "Name: " << name << " | Position: " << position << " | Salary: $"
         << salary << endl;
  }

  virtual double calculateBonus() const {
    return salary * 0.05; // 5% bonus
  }

  virtual void work() const { cout << name << " is working" << endl; }
};

class Manager : public Employee {
private:
  int teamSize;

public:
  Manager(string n, double s, int t) : Employee(n, s, "Manager"), teamSize(t) {}

  void displayInfo() const override {
    Employee::displayInfo();
    cout << "Team Size: " << teamSize << endl;
  }

  double calculateBonus() const override {
    return salary * 0.10; // 10% bonus
  }

  void work() const override {
    cout << name << " is managing the team" << endl;
  }
};

class Developer : public Employee {
private:
  string programmingLanguage;

public:
  Developer(string n, double s, string lang)
      : Employee(n, s, "Developer"), programmingLanguage(lang) {}

  void displayInfo() const override {
    Employee::displayInfo();
    cout << "Language: " << programmingLanguage << endl;
  }

  double calculateBonus() const override {
    return salary * 0.08; // 8% bonus
  }

  void work() const override {
    cout << name << " is coding in " << programmingLanguage << endl;
  }
};

/*
OUTPUT:
--------
Name: John | Position: Manager | Salary: $50000
Team Size: 5
Bonus: $5000
John is managing the team

--------
*/

/*
================================================================================
EXAMPLE 7: POLYMORPHISM WITH POINTERS AND REFERENCES
================================================================================
*/

class Shape7 {
public:
  virtual ~Shape7() {}

  virtual void draw() const { cout << "Drawing shape" << endl; }

  virtual double getArea() const = 0; // Pure virtual
};

class Rectangle7 : public Shape7 {
private:
  double width, height;

public:
  Rectangle7(double w, double h) : width(w), height(h) {}

  void draw() const override { cout << "Drawing rectangle" << endl; }

  double getArea() const override { return width * height; }
};

class Triangle7 : public Shape7 {
private:
  double base, height;

public:
  Triangle7(double b, double h) : base(b), height(h) {}

  void draw() const override { cout << "Drawing triangle" << endl; }

  double getArea() const override { return 0.5 * base * height; }
};

/*
OUTPUT:
--------
Drawing rectangle
Area: 50
Drawing triangle
Area: 15

--------
*/

/*
================================================================================
EXAMPLE 8: SCOPE RESOLUTION - CALLING BASE CLASS METHODS
================================================================================
*/

class Base8 {
public:
  virtual void display() const { cout << "Base display" << endl; }

  void info() { cout << "This is base class" << endl; }
};

class Derived8 : public Base8 {
public:
  void display() const override {
    cout << "Derived display (before base)" << endl;
    Base8::display(); // Call base class method
    cout << "Derived display (after base)" << endl;
  }

  void callBaseInfo() {
    Base8::info(); // Can call base class methods
  }
};

/*
OUTPUT:
--------
Derived display (before base)
Base display
Derived display (after base)
This is base class

--------
*/

/*
================================================================================
KEY CONCEPTS SUMMARY BOX
================================================================================

INHERITANCE FUNDAMENTALS:

WHAT IS INHERITANCE?
- Code reuse mechanism
- "is-a" relationship between classes
- Derived class inherits base class members

CLASS HIERARCHY:
- Base class (parent): Provides common functionality
- Derived class (child): Extends base class
- Can have multiple levels (grandchild, etc.)

ACCESS MODIFIERS IN INHERITANCE:
┌─────────────────────────────────────────────────────┐
│ Base Member │ Public Inheritance │ Protected │ Private │
├─────────────┼───────────────────┼──────────┼─────────┤
│ public      │ public            │ protected│ private │
│ protected   │ protected         │ protected│ private │
│ private     │ not accessible    │ not acc. │ not acc.│
└─────────────────────────────────────────────────────┘

CONSTRUCTOR CALL ORDER:
1. Base class constructor executes
2. Member initialization list
3. Derived class constructor body

DESTRUCTOR CALL ORDER:
1. Derived class destructor body
2. Member destructors
3. Base class destructor

VIRTUAL FUNCTIONS:
- Override: Replace base class behavior
- Dynamic dispatch: Decision made at runtime
- Use override keyword (C++11+) for clarity

================================================================================
*/

/*
================================================================================
COMMON MISTAKES
================================================================================

❌ MISTAKE 1: Not calling base class constructor
    Derived(int x) { value = x; }  // Base not initialized!

✓ CORRECT:
    Derived(int x) : Base(x) { }

-----

❌ MISTAKE 2: Non-virtual destructor in base class
    ~Base() { }  // Will cause memory leaks!

✓ CORRECT:
    virtual ~Base() { }

-----

❌ MISTAKE 3: Not using override keyword
    void display() { }  // Hard to spot if signature differs

✓ CORRECT:
    void display() override { }

-----

❌ MISTAKE 4: Accessing private base members
    cout << engineCode;  // ERROR: private in base!

✓ CORRECT:
    Use protected or public getters

-----

❌ MISTAKE 5: Slicing when copying derived to base
    Dog d;
    Animal a = d;  // Slices! Loses derived data

✓ CORRECT:
    Use pointers or references to avoid slicing

-----

❌ MISTAKE 6: Forgetting base class initialization
    Child() : Parent() { }  // Must initialize parent

✓ CORRECT:
    Child(int p, int c) : Parent(p), childMember(c) { }

================================================================================
*/

/*
================================================================================
PRACTICE EXERCISES
================================================================================

Exercise 1: Vehicle Hierarchy
Create classes: Vehicle (base), Car, Truck, Motorcycle
Each should override move() and show specific behavior

Exercise 2: Shape Hierarchy
Create classes: Shape (base), Rectangle, Circle, Triangle
Each should calculate area and perimeter differently

Exercise 3: Bank Account Inheritance
Create: BankAccount (base), SavingsAccount, CheckingAccount
Different interest rates and fees

Exercise 4: Person and Professions
Create: Person (base), Teacher, Engineer, Doctor
Each has different salary calculations and work() behavior

Exercise 5: Game Characters
Create: Character (base), Warrior, Mage, Archer
Different attack() and defense() methods

Exercise 6: Animal Sound Generator
Create: Animal (base), Dog, Cat, Cow, Duck
Each overrides makeSound() and has unique behavior

Exercise 7: Student and Courses
Create: Student (base), UndergraduateStudent, GraduateStudent
Different tuition calculations and course requirements

Exercise 8: Building Types
Create: Building (base), Office, Apartment, School
Different calculate maintenance costs

Exercise 9: Computer Components
Create: Component (base), CPU, RAM, Disk
Different power consumption calculations

Exercise 10: Transport System
Create: Transport (base), Bus, Train, Airplane
Different speed, capacity, and cost calculations

================================================================================
*/

// Main demonstration
int main() {
  cout << "================== INHERITANCE BASICS ==================\n\n";

  // Example 1: Simple Inheritance
  cout << "--- EXAMPLE 1: SIMPLE INHERITANCE ---\n";
  Dog dog1("Buddy", 5, "Golden Retriever");
  dog1.displayInfo();
  dog1.makeSound();
  dog1.fetch();
  cout << "\n";

  // Example 2: Access Modifiers
  cout << "--- EXAMPLE 2: ACCESS MODIFIERS ---\n";
  Car car1("Toyota");
  car1.carSpecific();
  cout << "\n";

  // Example 3: Protected Inheritance
  cout << "--- EXAMPLE 3: PROTECTED INHERITANCE ---\n";
  SmallCircle sc;
  sc.show();
  cout << "\n";

  // Example 4: Constructor/Destructor Chain
  cout << "--- EXAMPLE 4: CONSTRUCTOR/DESTRUCTOR CHAIN ---\n";
  {
    Child child("John", "Jane", "Bob");
  }
  cout << "\n";

  // Example 5: Function Overriding
  cout << "--- EXAMPLE 5: FUNCTION OVERRIDING ---\n";
  Cat cat;
  cat.eat();
  cat.sleep();
  cat.breathe();
  cout << "\n";

  // Example 6: Employee Hierarchy
  cout << "--- EXAMPLE 6: EMPLOYEE HIERARCHY ---\n";
  Manager mgr("John", 50000, 5);
  mgr.displayInfo();
  cout << "Bonus: $" << mgr.calculateBonus() << endl;
  mgr.work();
  cout << "\n";

  Developer dev("Alice", 40000, "C++");
  dev.displayInfo();
  cout << "Bonus: $" << dev.calculateBonus() << endl;
  dev.work();
  cout << "\n";

  // Example 7: Polymorphism with pointers
  cout << "--- EXAMPLE 7: POLYMORPHISM ---\n";
  Rectangle7 rect(10, 5);
  Triangle7 tri(6, 5);

  Shape7 *shape1 = &rect;
  Shape7 *shape2 = &tri;

  shape1->draw();
  cout << "Area: " << shape1->getArea() << endl;

  shape2->draw();
  cout << "Area: " << shape2->getArea() << endl;
  cout << "\n";

  // Example 8: Scope Resolution
  cout << "--- EXAMPLE 8: SCOPE RESOLUTION ---\n";
  Derived8 derived;
  derived.display();
  derived.callBaseInfo();
  cout << "\n";

  return 0;
}

/*
================================================================================
FULL PROGRAM OUTPUT:
================================================================================

================== INHERITANCE BASICS ==================

--- EXAMPLE 1: SIMPLE INHERITANCE ---
Animal constructor called for Buddy
Dog constructor called
Name: Buddy | Age: 5
Breed: Golden Retriever
Buddy barks: Woof! Woof!
Buddy is fetching the ball!

--- EXAMPLE 2: ACCESS MODIFIERS ---
Car brand: Toyota
Car wheels: 4

--- EXAMPLE 3: PROTECTED INHERITANCE ---
Drawing a generic shape

--- EXAMPLE 4: CONSTRUCTOR/DESTRUCTOR CHAIN ---
1. GrandParent constructor: John
2. Parent constructor: Jane
3. Child constructor: Bob
4. Child destructor
5. Parent destructor
6. GrandParent destructor

--- EXAMPLE 5: FUNCTION OVERRIDING ---
Cat is eating fish
Cat is sleeping in the sun
Animal is breathing

--- EXAMPLE 6: EMPLOYEE HIERARCHY ---
Name: John | Position: Manager | Salary: $50000
Team Size: 5
Bonus: $5000
John is managing the team

Name: Alice | Position: Developer | Salary: $40000
Language: C++
Bonus: $3200
Alice is coding in C++

--- EXAMPLE 7: POLYMORPHISM ---
Drawing rectangle
Area: 50
Drawing triangle
Area: 15

--- EXAMPLE 8: SCOPE RESOLUTION ---
Derived display (before base)
Base display
Derived display (after base)
This is base class

================================================================================
*/
