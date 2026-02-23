/*
================================================================================
ADVANCED INHERITANCE - VIRTUAL FUNCTIONS & MULTIPLE INHERITANCE
================================================================================
Part 2, Subtopic 11: Inheritance (File 2/2)

CONCEPTS COVERED:
- Virtual functions and dynamic binding
- Pure virtual functions and abstract classes
- Multiple inheritance
- Diamond problem and virtual inheritance
- Virtual constructors (Clone pattern)
- RTTI (Run-Time Type Information)
- Interface design patterns

KEY LEARNING POINTS:
1. Virtual functions enable runtime polymorphism
2. Pure virtual functions define contracts
3. Abstract classes cannot be instantiated
4. Multiple inheritance can create the diamond problem
5. Virtual inheritance resolves the diamond problem
6. RTTI allows checking types at runtime
7. Design interfaces using abstract classes

================================================================================
*/

#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;

/*
================================================================================
THEORY SECTION: VIRTUAL FUNCTIONS AND ABSTRACT CLASSES
================================================================================

VIRTUAL FUNCTIONS:
- Declared with "virtual" keyword
- Resolution happens at RUNTIME (dynamic binding)
- Allow derived classes to override behavior
- Requires virtual table (vtable) lookup
- Slower than non-virtual but enables polymorphism

PURE VIRTUAL FUNCTIONS:
- Declared with "= 0"
- No implementation in base class
- Derived class MUST provide implementation
- Class with pure virtual = abstract class

ABSTRACT CLASSES:
- Cannot instantiate directly
- Used to define interface/contract
- All subclasses must implement pure virtuals
- Good for plugin architectures and templates

MULTIPLE INHERITANCE:
- Class can inherit from multiple base classes
- Allows combining interfaces
- Can lead to diamond problem

DIAMOND PROBLEM:
       Base
       /  \
      A    B
       \  /
        C
Problem: C inherits Base twice (through A and B)
Solution: Virtual inheritance

================================================================================
*/

/*
================================================================================
EXAMPLE 1: VIRTUAL FUNCTIONS AND DYNAMIC BINDING
================================================================================
*/

class PaymentMethod {
public:
  virtual ~PaymentMethod() {}

  // Virtual function - resolved at runtime
  virtual void processPayment(double amount) const {
    cout << "Processing payment of $" << amount << endl;
  }

  virtual void refund(double amount) const {
    cout << "Refunding $" << amount << endl;
  }

  virtual string getMethodName() const = 0; // Pure virtual
};

class CreditCard : public PaymentMethod {
private:
  string cardNumber;

public:
  CreditCard(string cn) : cardNumber(cn) {}

  void processPayment(double amount) const override {
    cout << "Processing credit card payment: $" << amount
         << " (Card: " << cardNumber << ")" << endl;
  }

  void refund(double amount) const override {
    cout << "Credit card refund: $" << amount << endl;
  }

  string getMethodName() const override { return "Credit Card"; }
};

class PayPal : public PaymentMethod {
private:
  string email;

public:
  PayPal(string e) : email(e) {}

  void processPayment(double amount) const override {
    cout << "Processing PayPal payment: $" << amount << " (Email: " << email
         << ")" << endl;
  }

  void refund(double amount) const override {
    cout << "PayPal refund: $" << amount << endl;
  }

  string getMethodName() const override { return "PayPal"; }
};

class Bitcoin : public PaymentMethod {
private:
  string walletAddress;

public:
  Bitcoin(string wa) : walletAddress(wa) {}

  void processPayment(double amount) const override {
    cout << "Processing Bitcoin payment: " << amount << " BTC"
         << " (Wallet: " << walletAddress << ")" << endl;
  }

  void refund(double amount) const override {
    cout << "Bitcoin refund: " << amount << " BTC" << endl;
  }

  string getMethodName() const override { return "Bitcoin"; }
};

/*
OUTPUT:
--------
Processing credit card payment: $99.99 (Card: 1234-5678)
Credit card refund: $99.99
Processing PayPal payment: $50.00 (Email: user@example.com)
PayPal refund: $50.00

--------
*/

/*
================================================================================
EXAMPLE 2: ABSTRACT CLASSES AND PURE VIRTUAL FUNCTIONS
================================================================================
*/

// Abstract base class
class Shape {
public:
  virtual ~Shape() {}

  // Pure virtual functions - must be implemented by derived classes
  virtual void draw() const = 0;
  virtual double getArea() const = 0;
  virtual double getPerimeter() const = 0;

  // Non-pure virtual - has default implementation
  virtual void describe() const {
    cout << "This is a shape with area: " << getArea()
         << " and perimeter: " << getPerimeter() << endl;
  }
};

class Circle : public Shape {
private:
  double radius;
  static const double PI;

public:
  Circle(double r) : radius(r) {}

  void draw() const override {
    cout << "Drawing circle with radius " << radius << endl;
  }

  double getArea() const override { return PI * radius * radius; }

  double getPerimeter() const override { return 2 * PI * radius; }
};

const double Circle::PI = 3.14159265359;

class Rectangle : public Shape {
private:
  double width, height;

public:
  Rectangle(double w, double h) : width(w), height(h) {}

  void draw() const override {
    cout << "Drawing rectangle " << width << " x " << height << endl;
  }

  double getArea() const override { return width * height; }

  double getPerimeter() const override { return 2 * (width + height); }
};

/*
OUTPUT:
--------
Drawing circle with radius 5
Area: 78.54, Perimeter: 31.42
Drawing rectangle 4 x 6
Area: 24, Perimeter: 20

--------
*/

/*
================================================================================
EXAMPLE 3: MULTIPLE INHERITANCE - SIMPLE CASE
================================================================================
*/

class Drawable {
public:
  virtual ~Drawable() {}
  virtual void draw() const = 0;
};

class Serializable {
public:
  virtual ~Serializable() {}
  virtual string serialize() const = 0;
  virtual void deserialize(const string &data) = 0;
};

class Button : public Drawable, public Serializable {
private:
  string label;
  bool enabled;

public:
  Button(string l) : label(l), enabled(true) {}

  void draw() const override {
    cout << "Drawing button: " << label
         << (enabled ? " [enabled]" : " [disabled]") << endl;
  }

  string serialize() const override {
    return "Button:" + label + ":" + (enabled ? "1" : "0");
  }

  void deserialize(const string &data) override {
    cout << "Deserializing button from: " << data << endl;
  }
};

/*
OUTPUT:
--------
Drawing button: OK [enabled]
Serialized: Button:OK:1

--------
*/

/*
================================================================================
EXAMPLE 4: DIAMOND PROBLEM
================================================================================
*/

class Base4 {
public:
  Base4() { cout << "Base constructor" << endl; }

  virtual ~Base4() {}

  virtual void display() { cout << "Base display" << endl; }
};

// Without virtual inheritance - causes duplication
class Left : public Base4 {
public:
  Left() { cout << "Left constructor" << endl; }
};

class Right : public Base4 {
public:
  Right() { cout << "Right constructor" << endl; }
};

class Diamond : public Left, public Right {
public:
  Diamond() { cout << "Diamond constructor" << endl; }
  // ERROR: ambiguous - which Base4 to call?
  // void display() { Base4::display(); }  // Compiler error!
};

/*
OUTPUT:
--------
Base constructor (from Left)
Left constructor
Base constructor (from Right)
Right constructor
Diamond constructor

Problem: Base is constructed twice!
Diamond object has TWO copies of Base members

--------
*/

/*
================================================================================
EXAMPLE 5: DIAMOND PROBLEM SOLVED - VIRTUAL INHERITANCE
================================================================================
*/

class BaseV {
public:
  BaseV() { cout << "BaseV constructor" << endl; }

  virtual ~BaseV() {}

  virtual void display() { cout << "BaseV display" << endl; }
};

// Use virtual inheritance
class LeftV : virtual public BaseV {
public:
  LeftV() { cout << "LeftV constructor" << endl; }
};

class RightV : virtual public BaseV {
public:
  RightV() { cout << "RightV constructor" << endl; }
};

class DiamondV : public LeftV, public RightV {
public:
  DiamondV() { cout << "DiamondV constructor" << endl; }

  void display() override {
    BaseV::display(); // No ambiguity now!
  }
};

/*
OUTPUT:
--------
BaseV constructor (called once!)
LeftV constructor
RightV constructor
DiamondV constructor

Solution: Base is constructed only once!
Diamond object has ONE copy of BaseV members

--------
*/

/*
================================================================================
EXAMPLE 6: RTTI - RUN TIME TYPE INFORMATION
================================================================================
*/

class Animal6 {
public:
  virtual ~Animal6() {}
  virtual void makeSound() const = 0;
};

class Dog6 : public Animal6 {
public:
  void makeSound() const override { cout << "Woof!" << endl; }
};

class Cat6 : public Animal6 {
public:
  void makeSound() const override { cout << "Meow!" << endl; }
};

class Bird6 : public Animal6 {
public:
  void makeSound() const override { cout << "Tweet!" << endl; }
};

void processAnimal(Animal6 *animal) {
  // Use typeid to check actual type
  cout << "Type: " << typeid(*animal).name() << endl;

  // Use dynamic_cast to safely cast
  Dog6 *dog = dynamic_cast<Dog6 *>(animal);
  if (dog != nullptr) {
    cout << "This is a dog!" << endl;
    dog->makeSound();
    return;
  }

  Cat6 *cat = dynamic_cast<Cat6 *>(animal);
  if (cat != nullptr) {
    cout << "This is a cat!" << endl;
    cat->makeSound();
    return;
  }

  Bird6 *bird = dynamic_cast<Bird6 *>(animal);
  if (bird != nullptr) {
    cout << "This is a bird!" << endl;
    bird->makeSound();
    return;
  }

  cout << "Unknown animal!" << endl;
}

/*
OUTPUT:
--------
Type: class Dog6
This is a dog!
Woof!
Type: class Cat6
This is a cat!
Meow!

--------
*/

/*
================================================================================
EXAMPLE 7: VIRTUAL CONSTRUCTOR (CLONE PATTERN)
================================================================================
*/

class Document {
public:
  virtual ~Document() {}

  // Virtual constructor - creates a copy
  virtual Document *clone() const = 0;

  virtual void display() const = 0;

  virtual string getType() const = 0;
};

class PDFDocument : public Document {
private:
  string fileName;
  int pageCount;

public:
  PDFDocument(string fn, int pc) : fileName(fn), pageCount(pc) {}

  Document *clone() const override {
    return new PDFDocument(fileName, pageCount);
  }

  void display() const override {
    cout << "PDF: " << fileName << " (" << pageCount << " pages)" << endl;
  }

  string getType() const override { return "PDF"; }
};

class WordDocument : public Document {
private:
  string fileName;
  int wordCount;

public:
  WordDocument(string fn, int wc) : fileName(fn), wordCount(wc) {}

  Document *clone() const override {
    return new WordDocument(fileName, wordCount);
  }

  void display() const override {
    cout << "DOCX: " << fileName << " (" << wordCount << " words)" << endl;
  }

  string getType() const override { return "DOCX"; }
};

/*
OUTPUT:
--------
PDF: report.pdf (50 pages)
Cloned PDF: report.pdf (50 pages)

--------
*/

/*
================================================================================
EXAMPLE 8: LOGGER HIERARCHY - ADVANCED POLYMORPHISM
================================================================================
*/

class Logger {
public:
  virtual ~Logger() {}

  virtual void log(const string &message) = 0;
  virtual void error(const string &message) = 0;
  virtual void warning(const string &message) = 0;
};

class ConsoleLogger : public Logger {
public:
  void log(const string &message) override {
    cout << "[INFO] " << message << endl;
  }

  void error(const string &message) override {
    cout << "[ERROR] " << message << endl;
  }

  void warning(const string &message) override {
    cout << "[WARNING] " << message << endl;
  }
};

class FileLogger : public Logger {
private:
  string filename;

public:
  FileLogger(string fn) : filename(fn) {}

  void log(const string &message) override {
    cout << "[FILE][INFO] Writing to " << filename << ": " << message << endl;
  }

  void error(const string &message) override {
    cout << "[FILE][ERROR] Writing to " << filename << ": " << message << endl;
  }

  void warning(const string &message) override {
    cout << "[FILE][WARNING] Writing to " << filename << ": " << message
         << endl;
  }
};

class Application {
private:
  Logger *logger;

public:
  Application(Logger *l) : logger(l) {}

  void run() {
    logger->log("Application started");
    logger->warning("Low memory");
    logger->error("Connection failed");
    logger->log("Application stopped");
  }
};

/*
OUTPUT:
--------
[INFO] Application started
[WARNING] Low memory
[ERROR] Connection failed
[INFO] Application stopped

--------
*/

/*
================================================================================
KEY CONCEPTS SUMMARY BOX
================================================================================

VIRTUAL FUNCTIONS:
- Declared with "virtual" keyword
- Resolved at runtime (dynamic binding)
- Requires virtual table (overhead)
- Use override keyword for clarity
- Always use virtual destructors in base classes

PURE VIRTUAL FUNCTIONS:
- Declared with "= 0"
- No implementation in base
- Derived class MUST implement
- Makes class abstract

ABSTRACT CLASSES:
- Has one or more pure virtual functions
- Cannot instantiate directly
- Used to define interfaces
- Suitable for plugins, frameworks

MULTIPLE INHERITANCE:
- Inherit from multiple bases
- Combines multiple interfaces
- Can cause diamond problem

DIAMOND PROBLEM:
        Base
        / \
       A   B
       \ /
        C
Solution: Use virtual inheritance
Syntax: class A : virtual public Base

VIRTUAL INHERITANCE:
- Base appears only once in derived object
- Resolves ambiguity in diamond problem
- Adds complexity and overhead
- Use when necessary

RTTI (Run-Time Type Information):
- typeid(object): Get type name
- dynamic_cast<DerivedType*>(basePtr): Safe casting
- Returns nullptr if cast fails (pointers)
- Throws bad_cast if cast fails (references)

CLONE PATTERN:
- Virtual copy constructor
- Allows cloning without knowing exact type
- Useful for document systems, UI elements

================================================================================
*/

/*
================================================================================
COMMON MISTAKES - ADVANCED
================================================================================

❌ MISTAKE 1: Non-virtual destructor with virtual functions
    class Base { ~Base() {} };  // Will leak!

✓ CORRECT:
    class Base { virtual ~Base() {} };

-----

❌ MISTAKE 2: Hiding virtual function (wrong signature)
    class Base { virtual void func(int); };
    class Derived { void func(double); };  // Hides, doesn't override!

✓ CORRECT:
    class Derived { void func(int) override; };

-----

❌ MISTAKE 3: Multiple inheritance without virtual base
    class C : public A, public B { };  // Diamond not solved!

✓ CORRECT:
    class A : virtual public Base { };
    class B : virtual public Base { };
    class C : public A, public B { };

-----

❌ MISTAKE 4: Using dynamic_cast without null check
    Dog* d = dynamic_cast<Dog*>(animal);
    d->bark();  // Crashes if not a dog!

✓ CORRECT:
    Dog* d = dynamic_cast<Dog*>(animal);
    if (d != nullptr) d->bark();

-----

❌ MISTAKE 5: Instantiating abstract class
    Shape s;  // ERROR: cannot instantiate!

✓ CORRECT:
    Circle c;  // OK: concrete class

-----

❌ MISTAKE 6: Forgetting virtual in derived class
    void display();  // Doesn't override! Hides instead!

✓ CORRECT:
    void display() override;

================================================================================
*/

/*
================================================================================
PRACTICE EXERCISES
================================================================================

Exercise 1: Multimedia Player
Create abstract Player class. Implement: AudioPlayer, VideoPlayer, ImageViewer
Each has different display() and play() logic

Exercise 2: Banking System
Create Account (abstract). Implement: SavingsAccount, CheckingAccount
Each calculates interest differently

Exercise 3: Transportation Network
Create Vehicle (abstract). Multiple inheritance: Drivable, Refuelable
Implement: Car, Bus, Truck with different behaviors

Exercise 4: Game Entities
Create Entity (abstract) with pure virtual update() and render()
Implement: Player, Enemy, Projectile, Obstacle

Exercise 5: Data Storage
Create DataStore (abstract). Implement: MemoryStore, FileStore, DatabaseStore
Different save() and load() implementations

Exercise 6: Event System
Create EventHandler (abstract). Implement: MouseHandler, KeyboardHandler
Create EventDispatcher that manages multiple handlers

Exercise 7: Plugin System
Create Plugin (abstract). Implement various plugins
Use clone() pattern to create plugin instances

Exercise 8: UI Framework
Create Widget (abstract) with draw(), update(), handleInput()
Implement: Button, TextBox, Panel with different behaviors

Exercise 9: Database Connection
Create Connection (abstract). Implement: MySQLConnection, PostgreSQLConnection
Different connect() and execute() logic

Exercise 10: Animal Sanctuary
Create Animal (abstract). Implement multiple animal types
Use RTTI to identify and handle animals differently

================================================================================
*/

// Main demonstration
int main() {
  cout << "================== ADVANCED INHERITANCE ==================\n\n";

  // Example 1: Virtual Functions
  cout << "--- EXAMPLE 1: VIRTUAL FUNCTIONS ---\n";
  CreditCard cc("1234-5678-9012-3456");
  PayPal pp("user@example.com");
  Bitcoin btc("1A1z7agoat4LWND6Z56k6h5HexF9expfqd");

  vector<PaymentMethod *> payments = {&cc, &pp, &btc};
  for (auto payment : payments) {
    payment->processPayment(100);
    cout << endl;
  }

  // Example 2: Abstract Classes
  cout << "--- EXAMPLE 2: ABSTRACT CLASSES ---\n";
  Circle circle(5);
  Rectangle rectangle(4, 6);
  circle.draw();
  circle.describe();
  rectangle.draw();
  rectangle.describe();
  cout << "\n";

  // Example 3: Multiple Inheritance
  cout << "--- EXAMPLE 3: MULTIPLE INHERITANCE ---\n";
  Button button("Submit");
  button.draw();
  cout << button.serialize() << endl;
  cout << "\n";

  // Example 4: Diamond Problem
  cout << "--- EXAMPLE 4: DIAMOND PROBLEM ---\n";
  // Diamond d;  // Causes ambiguity
  cout << "\n";

  // Example 5: Virtual Inheritance
  cout << "--- EXAMPLE 5: VIRTUAL INHERITANCE SOLUTION ---\n";
  DiamondV dv;
  dv.display();
  cout << "\n";

  // Example 6: RTTI
  cout << "--- EXAMPLE 6: RTTI ---\n";
  Dog6 dog;
  Cat6 cat;
  Bird6 bird;
  processAnimal(&dog);
  cout << "\n";
  processAnimal(&cat);
  cout << "\n";
  processAnimal(&bird);
  cout << "\n";

  // Example 7: Clone Pattern
  cout << "--- EXAMPLE 7: CLONE PATTERN ---\n";
  PDFDocument pdf("report.pdf", 50);
  pdf.display();
  Document *cloned = pdf.clone();
  cloned->display();
  delete cloned;
  cout << "\n";

  // Example 8: Logger Hierarchy
  cout << "--- EXAMPLE 8: LOGGER HIERARCHY ---\n";
  ConsoleLogger consoleLogger;
  Application app(&consoleLogger);
  app.run();
  cout << "\n";

  return 0;
}

/*
================================================================================
FULL PROGRAM OUTPUT:
================================================================================

================== ADVANCED INHERITANCE ==================

--- EXAMPLE 1: VIRTUAL FUNCTIONS ---
Processing credit card payment: $100 (Card: 1234-5678-9012-3456)

Processing PayPal payment: $100 (Email: user@example.com)

Processing Bitcoin payment: 100 BTC (Wallet: 1A1z7agoat4LWND6Z56k6h5HexF9expfqd)

--- EXAMPLE 2: ABSTRACT CLASSES ---
Drawing circle with radius 5
Area: 78.54, Perimeter: 31.42
Drawing rectangle 4 x 6
Area: 24, Perimeter: 20

--- EXAMPLE 3: MULTIPLE INHERITANCE ---
Drawing button: Submit [enabled]
Button:Submit:1

--- EXAMPLE 4: DIAMOND PROBLEM ---

--- EXAMPLE 5: VIRTUAL INHERITANCE SOLUTION ---
BaseV constructor
LeftV constructor
RightV constructor
DiamondV constructor
BaseV display

--- EXAMPLE 6: RTTI ---
Type: class Dog6
This is a dog!
Woof!

Type: class Cat6
This is a cat!
Meow!

Type: class Bird6
This is a bird!
Tweet!

--- EXAMPLE 7: CLONE PATTERN ---
PDF: report.pdf (50 pages)
PDF: report.pdf (50 pages)

--- EXAMPLE 8: LOGGER HIERARCHY ---
[INFO] Application started
[WARNING] Low memory
[ERROR] Connection failed
[INFO] Application stopped

================================================================================
*/
