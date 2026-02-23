/*
================================================================================
ADVANCED POLYMORPHISM - RUNTIME POLYMORPHISM & DESIGN PATTERNS
================================================================================
Part 2, Subtopic 12: Polymorphism (File 2/2)

CONCEPTS COVERED:
- Runtime polymorphism in depth
- Virtual functions and dynamic dispatch
- Virtual destructors
- RTTI (Run-Time Type Information)
- typeid() and dynamic_cast
- Design patterns with polymorphism
- Policy-based design
- Visitor pattern
- Factory pattern

KEY LEARNING POINTS:
1. Runtime polymorphism enables flexible architecture
2. Virtual functions use dynamic dispatch (virtual table)
3. Virtual destructors prevent memory leaks
4. RTTI allows type checking and safe casting
5. Design patterns leverage polymorphism for extensibility
6. Visitor pattern separates operations from data structures
7. Factory pattern creates objects based on runtime conditions

================================================================================
*/

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;

/*
================================================================================
THEORY SECTION: RUNTIME POLYMORPHISM IN DEPTH
================================================================================

VIRTUAL FUNCTION MECHANISM:
1. Base class declares function as virtual
2. Derived classes override the function
3. When calling through base pointer/reference:
   - Runtime system checks actual object type
   - Calls the appropriate derived version
   - Achieved through virtual table (vtable)

VIRTUAL TABLE:
- Hidden table maintained by compiler
- Each class with virtual functions has a vtable
- Contains pointers to virtual functions
- Small memory overhead per object (one pointer)
- One vtable per class (shared by all instances)

PERFORMANCE:
- Virtual call: ~2-3x slower than non-virtual
- Usually acceptable for most applications
- Modern CPUs have branch prediction to help
- Inlining can sometimes optimize away virtual calls

BEST PRACTICES:
1. Always use virtual destructor in base classes
2. Use override keyword in derived classes
3. Prefer composition to deep inheritance hierarchies
4. Use pure virtual functions to define interfaces
5. Avoid dynamic_cast when possible (indicates design issue)

RTTI OVERHEAD:
- Slight memory and time overhead
- type_info objects created and compared
- dynamic_cast requires runtime type checking
- Only enable if needed (enabled by default)

================================================================================
*/

/*
================================================================================
EXAMPLE 1: VIRTUAL DESTRUCTORS - PREVENTING MEMORY LEAKS
================================================================================
*/

class ResourceBase {
protected:
  int *data;

public:
  ResourceBase(int size) {
    data = new int[size];
    cout << "ResourceBase allocated " << size << " integers" << endl;
  }

  // CORRECT: Virtual destructor
  virtual ~ResourceBase() {
    delete[] data;
    cout << "ResourceBase destructor: cleaned up memory" << endl;
  }

  virtual void display() const {
    cout << "Resource data[0]: " << data[0] << endl;
  }
};

class DerivedResource : public ResourceBase {
private:
  string name;
  vector<int> extra;

public:
  DerivedResource(int size, string n) : ResourceBase(size), name(n) {
    cout << "DerivedResource constructor: " << name << endl;
  }

  ~DerivedResource() {
    cout << "DerivedResource destructor: " << name << endl;
    extra.clear();
  }

  void display() const override {
    cout << "DerivedResource (" << name << ") data[0]: " << data[0] << endl;
  }
};

/*
OUTPUT:
--------
ResourceBase allocated 10 integers
DerivedResource constructor: myResource
DerivedResource destructor: myResource
ResourceBase destructor: cleaned up memory

--------
*/

/*
================================================================================
EXAMPLE 2: VIRTUAL FUNCTIONS WITH POINTERS AND REFERENCES
================================================================================
*/

class Vehicle {
public:
  virtual ~Vehicle() {}

  virtual void start() const { cout << "Vehicle starting" << endl; }

  virtual void stop() const { cout << "Vehicle stopping" << endl; }

  virtual int getMaxSpeed() const = 0;
};

class Car : public Vehicle {
private:
  string model;

public:
  Car(string m) : model(m) {}

  void start() const override {
    cout << "Car " << model << " engine roaring" << endl;
  }

  void stop() const override {
    cout << "Car " << model << " braking smoothly" << endl;
  }

  int getMaxSpeed() const override {
    return 200; // km/h
  }
};

class Bicycle : public Vehicle {
public:
  void start() const override { cout << "Bicycle ready to ride" << endl; }

  void stop() const override { cout << "Bicycle stopped" << endl; }

  int getMaxSpeed() const override {
    return 40; // km/h
  }
};

void testVehicle(Vehicle *v) {
  v->start();
  cout << "Max speed: " << v->getMaxSpeed() << " km/h" << endl;
  v->stop();
}

/*
OUTPUT:
--------
Car Ferrari engine roaring
Max speed: 200 km/h
Car Ferrari braking smoothly

Bicycle ready to ride
Max speed: 40 km/h
Bicycle stopped

--------
*/

/*
================================================================================
EXAMPLE 3: RTTI - typeid() OPERATOR
================================================================================
*/

class Animal {
public:
  virtual ~Animal() {}
  virtual void speak() const = 0;
};

class Dog : public Animal {
public:
  void speak() const override { cout << "Woof!" << endl; }
};

class Cat : public Animal {
public:
  void speak() const override { cout << "Meow!" << endl; }
};

class Bird : public Animal {
public:
  void speak() const override { cout << "Tweet!" << endl; }
};

void identifyAnimal(Animal *animal) {
  // typeid returns type_info object
  const type_info &info = typeid(*animal);

  cout << "Type name: " << info.name() << endl;

  if (info == typeid(Dog)) {
    cout << "This is a Dog" << endl;
  } else if (info == typeid(Cat)) {
    cout << "This is a Cat" << endl;
  } else if (info == typeid(Bird)) {
    cout << "This is a Bird" << endl;
  } else {
    cout << "Unknown animal" << endl;
  }
}

/*
OUTPUT:
--------
Type name: class Dog
This is a Dog

Type name: class Cat
This is a Cat

--------
*/

/*
================================================================================
EXAMPLE 4: DYNAMIC_CAST - SAFE TYPE CASTING
================================================================================
*/

class Employee {
public:
  virtual ~Employee() {}
  virtual void work() const = 0;
};

class Manager : public Employee {
public:
  void work() const override { cout << "Manager delegating tasks" << endl; }

  void conductMeeting() { cout << "Manager conducting meeting" << endl; }
};

class Developer : public Employee {
public:
  void work() const override { cout << "Developer writing code" << endl; }

  void writeCode(string language) {
    cout << "Developer writing " << language << " code" << endl;
  }
};

void processEmployee(Employee *emp) {
  emp->work();

  // Safe cast to Manager
  Manager *mgr = dynamic_cast<Manager *>(emp);
  if (mgr != nullptr) {
    mgr->conductMeeting();
  }

  // Safe cast to Developer
  Developer *dev = dynamic_cast<Developer *>(emp);
  if (dev != nullptr) {
    dev->writeCode("C++");
  }
}

/*
OUTPUT:
--------
Manager delegating tasks
Manager conducting meeting

Developer writing code
Developer writing C++ code

--------
*/

/*
================================================================================
EXAMPLE 5: VISITOR PATTERN
================================================================================
*/

class Shape;

class ShapeVisitor {
public:
  virtual ~ShapeVisitor() {}

  virtual void visit(class Circle &c) = 0;
  virtual void visit(class Square &s) = 0;
  virtual void visit(class Triangle &t) = 0;
};

class Shape {
public:
  virtual ~Shape() {}
  virtual void accept(ShapeVisitor &visitor) = 0;
};

class Circle : public Shape {
private:
  double radius;

public:
  Circle(double r) : radius(r) {}

  double getRadius() const { return radius; }

  void accept(ShapeVisitor &visitor) override { visitor.visit(*this); }
};

class Square : public Shape {
private:
  double side;

public:
  Square(double s) : side(s) {}

  double getSide() const { return side; }

  void accept(ShapeVisitor &visitor) override { visitor.visit(*this); }
};

class Triangle : public Shape {
private:
  double a, b, c;

public:
  Triangle(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}

  double getA() const { return a; }
  double getB() const { return b; }
  double getC() const { return c; }

  void accept(ShapeVisitor &visitor) override { visitor.visit(*this); }
};

class AreaCalculator : public ShapeVisitor {
public:
  void visit(Circle &c) override {
    double area = 3.14159 * c.getRadius() * c.getRadius();
    cout << "Circle area: " << area << endl;
  }

  void visit(Square &s) override {
    double area = s.getSide() * s.getSide();
    cout << "Square area: " << area << endl;
  }

  void visit(Triangle &t) override {
    // Heron's formula
    double s = (t.getA() + t.getB() + t.getC()) / 2;
    double area = sqrt(s * (s - t.getA()) * (s - t.getB()) * (s - t.getC()));
    cout << "Triangle area: " << area << endl;
  }
};

class PerimeterCalculator : public ShapeVisitor {
public:
  void visit(Circle &c) override {
    double perimeter = 2 * 3.14159 * c.getRadius();
    cout << "Circle perimeter: " << perimeter << endl;
  }

  void visit(Square &s) override {
    double perimeter = 4 * s.getSide();
    cout << "Square perimeter: " << perimeter << endl;
  }

  void visit(Triangle &t) override {
    double perimeter = t.getA() + t.getB() + t.getC();
    cout << "Triangle perimeter: " << perimeter << endl;
  }
};

/*
OUTPUT:
--------
Circle area: 78.5398
Square area: 100
Triangle area: 6

Circle perimeter: 31.4159
Square perimeter: 40
Triangle perimeter: 12

--------
*/

/*
================================================================================
EXAMPLE 6: FACTORY PATTERN
================================================================================
*/

class DatabaseConnection {
public:
  virtual ~DatabaseConnection() {}
  virtual void connect() = 0;
  virtual void query(string sql) = 0;
};

class MySQLConnection : public DatabaseConnection {
public:
  void connect() override { cout << "Connecting to MySQL database" << endl; }

  void query(string sql) override {
    cout << "Executing MySQL query: " << sql << endl;
  }
};

class PostgreSQLConnection : public DatabaseConnection {
public:
  void connect() override {
    cout << "Connecting to PostgreSQL database" << endl;
  }

  void query(string sql) override {
    cout << "Executing PostgreSQL query: " << sql << endl;
  }
};

class SQLiteConnection : public DatabaseConnection {
public:
  void connect() override { cout << "Connecting to SQLite database" << endl; }

  void query(string sql) override {
    cout << "Executing SQLite query: " << sql << endl;
  }
};

// Factory class
class DatabaseFactory {
public:
  static DatabaseConnection *createConnection(string dbType) {
    if (dbType == "mysql") {
      return new MySQLConnection();
    } else if (dbType == "postgresql") {
      return new PostgreSQLConnection();
    } else if (dbType == "sqlite") {
      return new SQLiteConnection();
    } else {
      throw runtime_error("Unknown database type: " + dbType);
    }
  }
};

/*
OUTPUT:
--------
Connecting to MySQL database
Executing MySQL query: SELECT * FROM users

Connecting to PostgreSQL database
Executing PostgreSQL query: SELECT * FROM products

--------
*/

/*
================================================================================
EXAMPLE 7: TEMPLATE METHOD PATTERN
================================================================================
*/

class DataProcessor {
public:
  virtual ~DataProcessor() {}

  // Template method
  void process() {
    loadData();
    validateData();
    transformData();
    saveData();
  }

private:
  // Template method steps
  virtual void loadData() = 0;
  virtual void validateData() = 0;
  virtual void transformData() = 0;
  virtual void saveData() = 0;
};

class CSVProcessor : public DataProcessor {
private:
  void loadData() override { cout << "Loading CSV data from file" << endl; }

  void validateData() override { cout << "Validating CSV format" << endl; }

  void transformData() override {
    cout << "Transforming CSV to objects" << endl;
  }

  void saveData() override { cout << "Saving to database" << endl; }
};

class JSONProcessor : public DataProcessor {
private:
  void loadData() override { cout << "Loading JSON data from API" << endl; }

  void validateData() override { cout << "Validating JSON schema" << endl; }

  void transformData() override {
    cout << "Transforming JSON to objects" << endl;
  }

  void saveData() override { cout << "Saving to database" << endl; }
};

/*
OUTPUT:
--------
Loading CSV data from file
Validating CSV format
Transforming CSV to objects
Saving to database

Loading JSON data from API
Validating JSON schema
Transforming JSON to objects
Saving to database

--------
*/

/*
================================================================================
EXAMPLE 8: STRATEGY PATTERN
================================================================================
*/

class SortingStrategy {
public:
  virtual ~SortingStrategy() {}
  virtual void sort(vector<int> &data) = 0;
};

class BubbleSortStrategy : public SortingStrategy {
public:
  void sort(vector<int> &data) override {
    cout << "Sorting using Bubble Sort" << endl;
    for (size_t i = 0; i < data.size(); i++) {
      for (size_t j = 0; j < data.size() - 1 - i; j++) {
        if (data[j] > data[j + 1]) {
          swap(data[j], data[j + 1]);
        }
      }
    }
  }
};

class QuickSortStrategy : public SortingStrategy {
public:
  void sort(vector<int> &data) override {
    cout << "Sorting using Quick Sort" << endl;
    quickSort(data, 0, data.size() - 1);
  }

private:
  void quickSort(vector<int> &data, int low, int high) {
    if (low < high) {
      int pi = partition(data, low, high);
      quickSort(data, low, pi - 1);
      quickSort(data, pi + 1, high);
    }
  }

  int partition(vector<int> &data, int low, int high) {
    int pivot = data[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
      if (data[j] < pivot) {
        i++;
        swap(data[i], data[j]);
      }
    }
    swap(data[i + 1], data[high]);
    return i + 1;
  }
};

class DataSorter {
private:
  SortingStrategy *strategy;

public:
  DataSorter(SortingStrategy *s) : strategy(s) {}

  void setSortingStrategy(SortingStrategy *s) { strategy = s; }

  void sortData(vector<int> &data) { strategy->sort(data); }
};

/*
OUTPUT:
--------
Sorting using Bubble Sort
Sorted: [1, 2, 3, 4, 5]
Sorting using Quick Sort
Sorted: [1, 2, 3, 4, 5]

--------
*/

/*
================================================================================
KEY CONCEPTS SUMMARY BOX
================================================================================

RUNTIME POLYMORPHISM MECHANISMS:

VIRTUAL FUNCTIONS:
- Dynamic dispatch: Function called based on actual object type
- Virtual table: Hidden table of function pointers
- Slight overhead: ~2-3x slower than non-virtual
- Modern CPUs can predict and optimize virtual calls

VIRTUAL DESTRUCTORS:
- ALWAYS use virtual destructor in base classes
- Ensures all destructors in hierarchy are called
- Prevents memory leaks
- Small overhead (one virtual function)

RTTI (Run-Time Type Information):
- typeid(object): Get type information
- dynamic_cast: Safe downcasting
- Useful for: Type checking, safe casting
- Overhead: Small memory and performance cost

DESIGN PATTERNS:

FACTORY PATTERN:
- Encapsulates object creation
- Creates correct type based on parameters
- Decouples creation from usage

VISITOR PATTERN:
- Separates operations from data structures
- Add new operations without modifying classes
- Good for: Complex operations on object hierarchies

TEMPLATE METHOD PATTERN:
- Base class defines algorithm structure
- Derived classes implement specific steps
- Enforces structure while allowing customization

STRATEGY PATTERN:
- Encapsulates interchangeable algorithms
- Client can switch strategies at runtime
- Good for: Multiple algorithms for same problem

================================================================================
*/

/*
================================================================================
COMMON MISTAKES - ADVANCED POLYMORPHISM
================================================================================

❌ MISTAKE 1: Non-virtual destructor in polymorphic base class
    class Base { ~Base() {} };  // WRONG!

✓ CORRECT:
    class Base { virtual ~Base() {} };

-----

❌ MISTAKE 2: Using dynamic_cast indiscriminately
    Dog* d = dynamic_cast<Dog*>(animal);  // Always check!
    d->bark();  // Can crash if nullptr!

✓ CORRECT:
    Dog* d = dynamic_cast<Dog*>(animal);
    if (d != nullptr) d->bark();

-----

❌ MISTAKE 3: Slicing with assignment
    Dog dog;
    Animal animal = dog;  // Sliced! Loses Dog data

✓ CORRECT:
    Animal* animal = &dog;  // Use pointer/reference

-----

❌ MISTAKE 4: Breaking Liskov Substitution Principle
    class Base { virtual void func(int); };
    class Derived { virtual void func(int) override { } };  // Wrong behavior!

✓ CORRECT:
    Override should maintain expected behavior

-----

❌ MISTAKE 5: Over-engineering with virtual functions
    // Every function is virtual (unnecessary!)
    class Base {
        virtual void simple() { }
        virtual void small() { }
    };

✓ CORRECT:
    Only make functions virtual if they need to be overridden

-----

❌ MISTAKE 6: Forgetting override keyword
    void display() { }  // Is this intentional or a typo?

✓ CORRECT:
    void display() override { }  // Clear intent!

================================================================================
*/

/*
================================================================================
PRACTICE EXERCISES
================================================================================

Exercise 1: Observer Pattern
Create Subject class that notifies multiple Observer objects
Observers react differently to updates

Exercise 2: Adapter Pattern
Create adapter to make incompatible interfaces work together
Use virtual functions for adaptation

Exercise 3: Decorator Pattern
Add responsibilities to objects dynamically
Use polymorphism to wrap objects

Exercise 4: Command Pattern
Encapsulate requests as objects
Execute different commands polymorphically

Exercise 5: State Pattern
Object changes behavior when internal state changes
Use virtual functions for state behavior

Exercise 6: Proxy Pattern
Create proxy that controls access to another object
Use virtual functions for delayed loading

Exercise 7: Chain of Responsibility
Pass requests along a chain of handlers
Each handler decides to process or pass

Exercise 8: Template Method with Callbacks
Framework class defines algorithm
Concrete classes override specific steps

Exercise 9: Multiple Polymorphic Hierarchies
Two separate inheritance hierarchies working together
Dynamic dispatch in both hierarchies

Exercise 10: Safe Type Checking System
Create type-safe system using RTTI
Dynamic_cast with error handling

================================================================================
*/

// Main demonstration
int main() {
  cout << "================== ADVANCED POLYMORPHISM ==================\n\n";

  // Example 1: Virtual Destructors
  cout << "--- EXAMPLE 1: VIRTUAL DESTRUCTORS ---\n";
  {
    ResourceBase *res = new DerivedResource(10, "myResource");
    res->display();
    delete res;
  }
  cout << "\n";

  // Example 2: Virtual Functions with Polymorphism
  cout << "--- EXAMPLE 2: VIRTUAL FUNCTIONS ---\n";
  Car car("Ferrari");
  Bicycle bike;
  testVehicle(&car);
  cout << "\n";
  testVehicle(&bike);
  cout << "\n";

  // Example 3: typeid()
  cout << "--- EXAMPLE 3: RTTI - typeid() ---\n";
  Dog dog;
  Cat cat;
  Bird bird;
  identifyAnimal(&dog);
  identifyAnimal(&cat);
  cout << "\n";

  // Example 4: dynamic_cast
  cout << "--- EXAMPLE 4: DYNAMIC_CAST ---\n";
  Manager manager;
  Developer developer;
  processEmployee(&manager);
  cout << "\n";
  processEmployee(&developer);
  cout << "\n";

  // Example 5: Visitor Pattern
  cout << "--- EXAMPLE 5: VISITOR PATTERN ---\n";
  vector<unique_ptr<Shape>> shapes;
  shapes.push_back(make_unique<Circle>(5));
  shapes.push_back(make_unique<Square>(10));
  shapes.push_back(make_unique<Triangle>(3, 4, 5));

  AreaCalculator areaCalc;
  PerimeterCalculator perimCalc;

  for (auto &shape : shapes) {
    shape->accept(areaCalc);
  }
  cout << "\n";

  for (auto &shape : shapes) {
    shape->accept(perimCalc);
  }
  cout << "\n";

  // Example 6: Factory Pattern
  cout << "--- EXAMPLE 6: FACTORY PATTERN ---\n";
  DatabaseConnection *db1 = DatabaseFactory::createConnection("mysql");
  db1->connect();
  db1->query("SELECT * FROM users");
  delete db1;
  cout << "\n";

  // Example 7: Template Method Pattern
  cout << "--- EXAMPLE 7: TEMPLATE METHOD PATTERN ---\n";
  CSVProcessor csvProc;
  csvProc.process();
  cout << "\n";

  JSONProcessor jsonProc;
  jsonProc.process();
  cout << "\n";

  // Example 8: Strategy Pattern
  cout << "--- EXAMPLE 8: STRATEGY PATTERN ---\n";
  vector<int> data = {5, 2, 8, 1, 9, 3};
  BubbleSortStrategy bubbleSort;
  QuickSortStrategy quickSort;

  DataSorter sorter(&bubbleSort);
  vector<int> data1 = data;
  sorter.sortData(data1);
  cout << "Sorted: ";
  for (int n : data1)
    cout << n << " ";
  cout << "\n\n";

  sorter.setSortingStrategy(&quickSort);
  vector<int> data2 = data;
  sorter.sortData(data2);
  cout << "Sorted: ";
  for (int n : data2)
    cout << n << " ";
  cout << "\n\n";

  return 0;
}

/*
================================================================================
FULL PROGRAM OUTPUT:
================================================================================

================== ADVANCED POLYMORPHISM ==================

--- EXAMPLE 1: VIRTUAL DESTRUCTORS ---
ResourceBase allocated 10 integers
DerivedResource constructor: myResource
DerivedResource destructor: myResource
ResourceBase destructor: cleaned up memory

--- EXAMPLE 2: VIRTUAL FUNCTIONS ---
Car Ferrari engine roaring
Max speed: 200 km/h
Car Ferrari braking smoothly

Bicycle ready to ride
Max speed: 40 km/h
Bicycle stopped

--- EXAMPLE 3: RTTI - typeid() ---
Type name: class Dog
This is a Dog
Type name: class Cat
This is a Cat

--- EXAMPLE 4: DYNAMIC_CAST ---
Manager delegating tasks
Manager conducting meeting

Developer writing code
Developer writing C++ code

--- EXAMPLE 5: VISITOR PATTERN ---
Circle area: 78.5398
Square area: 100
Triangle area: 6

Circle perimeter: 31.4159
Square perimeter: 40
Triangle perimeter: 12

--- EXAMPLE 6: FACTORY PATTERN ---
Connecting to MySQL database
Executing MySQL query: SELECT * FROM users

--- EXAMPLE 7: TEMPLATE METHOD PATTERN ---
Loading CSV data from file
Validating CSV format
Transforming CSV to objects
Saving to database

Loading JSON data from API
Validating JSON schema
Transforming JSON to objects
Saving to database

--- EXAMPLE 8: STRATEGY PATTERN ---
Sorting using Bubble Sort
Sorted: 1 2 3 5 8 9

Sorting using Quick Sort
Sorted: 1 2 3 5 8 9

================================================================================
*/
