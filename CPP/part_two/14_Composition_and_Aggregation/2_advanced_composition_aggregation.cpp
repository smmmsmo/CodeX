/*
================================================================================
ADVANCED COMPOSITION AND AGGREGATION - DESIGN PATTERNS & BEST PRACTICES
================================================================================
Part 2, Subtopic 14: Composition and Aggregation (File 2/2)

CONCEPTS COVERED:
- Advanced composition patterns
- Delegation and forwarding
- Decorator pattern
- Strategy pattern with composition
- Pimpl pattern (Pointer to Implementation)
- Component architecture
- Managing circular dependencies
- Composition vs inheritance tradeoffs

KEY LEARNING POINTS:
1. Delegation simplifies complex hierarchies
2. Decorator pattern adds behavior dynamically
3. Strategy pattern enables flexible algorithms
4. Pimpl pattern hides implementation
5. Component architecture enables modularity
6. Circular dependencies must be avoided
7. Composition offers better encapsulation

================================================================================
*/

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

/*
================================================================================
THEORY SECTION: ADVANCED COMPOSITION & AGGREGATION
================================================================================

DELEGATION PATTERN:
- Forward method calls to component
- Reduces code duplication
- Maintains loose coupling
- Component handles responsibility
- Example: Window delegates to Panel

DECORATOR PATTERN:
- Wrap object with additional behavior
- Add features at runtime
- Multiple decorators stack
- Better than inheritance for combinations
- Example: Coffee with sugar and milk

STRATEGY PATTERN:
- Compose algorithms
- Swap strategies at runtime
- Avoid multiple inheritance
- Type-safe alternatives
- Example: Different sorting algorithms

PIMPL (Pointer to Implementation):
- Hide implementation details
- Reduce compilation dependencies
- Binary compatibility across versions
- Separate interface from implementation
- Example: Native implementation hiding

COMPONENT ARCHITECTURE:
- Build systems from independent components
- Components communicate through interfaces
- Enables testing and reuse
- Scalable design
- Example: Game engine components

CIRCULAR DEPENDENCIES:
- A references B, B references A
- Breaks ownership hierarchy
- Use weak_ptr for cycles
- Or use interfaces/protocols
- Redesign if too many cycles

================================================================================
*/

/*
================================================================================
EXAMPLE 1: DELEGATION - WINDOW AND PANEL
================================================================================
*/

class Component {
public:
  virtual ~Component() = default;
  virtual void draw() = 0;
  virtual int getWidth() const = 0;
  virtual int getHeight() const = 0;
};

class Button : public Component {
private:
  string label;
  int width, height;

public:
  Button(string l) : label(l), width(80), height(30) {}

  void draw() override { cout << "[" << label << "]" << endl; }

  int getWidth() const override { return width; }
  int getHeight() const override { return height; }
};

class TextBox : public Component {
private:
  string placeholder;
  int width, height;

public:
  TextBox(string p) : placeholder(p), width(200), height(25) {}

  void draw() override { cout << "|" << placeholder << "|" << endl; }

  int getWidth() const override { return width; }
  int getHeight() const override { return height; }
};

class Panel {
private:
  vector<shared_ptr<Component>> components;

public:
  void addComponent(shared_ptr<Component> component) {
    components.push_back(component);
  }

  // Delegation: Panel forwards draw to all components
  void drawAll() {
    cout << "Panel contents:" << endl;
    for (auto &comp : components) {
      comp->draw();
    }
  }

  int getTotalHeight() const {
    int total = 0;
    for (const auto &comp : components) {
      total += comp->getHeight();
    }
    return total;
  }
};

class Window {
private:
  Panel panel; // COMPOSITION: Window owns Panel
  string title;

public:
  Window(string t) : title(t) {}

  void addComponent(shared_ptr<Component> component) {
    panel.addComponent(component);
  }

  // Delegation: Window forwards to Panel
  void display() {
    cout << "=== " << title << " ===" << endl;
    panel.drawAll();
  }
};

/*
OUTPUT:
--------
=== My Application ===
Panel contents:
[Click Me]
|Enter text|

--------
*/

/*
================================================================================
EXAMPLE 2: DECORATOR PATTERN - BEVERAGE
================================================================================
*/

class Beverage {
public:
  virtual ~Beverage() = default;
  virtual string getDescription() const = 0;
  virtual double getCost() const = 0;
};

class Coffee : public Beverage {
public:
  string getDescription() const override { return "Coffee"; }

  double getCost() const override { return 2.50; }
};

class Tea : public Beverage {
public:
  string getDescription() const override { return "Tea"; }

  double getCost() const override { return 1.50; }
};

// Decorator base class
class BeverageDecorator : public Beverage {
protected:
  shared_ptr<Beverage> beverage;

public:
  BeverageDecorator(shared_ptr<Beverage> b) : beverage(b) {}
};

class MilkDecorator : public BeverageDecorator {
public:
  MilkDecorator(shared_ptr<Beverage> b) : BeverageDecorator(b) {}

  string getDescription() const override {
    return beverage->getDescription() + " with Milk";
  }

  double getCost() const override { return beverage->getCost() + 0.50; }
};

class SugarDecorator : public BeverageDecorator {
public:
  SugarDecorator(shared_ptr<Beverage> b) : BeverageDecorator(b) {}

  string getDescription() const override {
    return beverage->getDescription() + " with Sugar";
  }

  double getCost() const override { return beverage->getCost() + 0.20; }
};

class WhippedCreamDecorator : public BeverageDecorator {
public:
  WhippedCreamDecorator(shared_ptr<Beverage> b) : BeverageDecorator(b) {}

  string getDescription() const override {
    return beverage->getDescription() + " with Whipped Cream";
  }

  double getCost() const override { return beverage->getCost() + 0.75; }
};

/*
OUTPUT:
--------
Coffee: $2.50
Coffee with Milk: $3.00
Coffee with Milk and Sugar: $3.20
Coffee with Milk and Whipped Cream: $3.95

--------
*/

/*
================================================================================
EXAMPLE 3: STRATEGY PATTERN - PAYMENT
================================================================================
*/

class PaymentStrategy {
public:
  virtual ~PaymentStrategy() = default;
  virtual void pay(double amount) = 0;
};

class CreditCardPayment : public PaymentStrategy {
private:
  string cardNumber;
  string name;

public:
  CreditCardPayment(string card, string n) : cardNumber(card), name(n) {}

  void pay(double amount) override {
    cout << "Paid $" << amount << " using Credit Card "
         << cardNumber.substr(cardNumber.length() - 4) << endl;
  }
};

class PayPalPayment : public PaymentStrategy {
private:
  string email;

public:
  PayPalPayment(string e) : email(e) {}

  void pay(double amount) override {
    cout << "Paid $" << amount << " via PayPal to " << email << endl;
  }
};

class BitcoinPayment : public PaymentStrategy {
private:
  string walletAddress;

public:
  BitcoinPayment(string addr) : walletAddress(addr) {}

  void pay(double amount) override {
    cout << "Paid $" << amount << " in Bitcoin to " << walletAddress << endl;
  }
};

class Order {
private:
  double totalAmount;
  shared_ptr<PaymentStrategy> paymentMethod;

public:
  Order(double amount) : totalAmount(amount) {}

  void setPaymentMethod(shared_ptr<PaymentStrategy> method) {
    paymentMethod = method;
  }

  void checkout() {
    if (paymentMethod) {
      paymentMethod->pay(totalAmount);
    } else {
      cout << "No payment method set!" << endl;
    }
  }
};

/*
OUTPUT:
--------
Paid $99.99 using Credit Card 1234
Paid $99.99 via PayPal to user@email.com
Paid $99.99 in Bitcoin to 1A1z7agoat

--------
*/

/*
================================================================================
EXAMPLE 4: PIMPL PATTERN - HIDE IMPLEMENTATION
================================================================================
*/

class DatabaseImpl {
public:
  void connect() { cout << "Connected to database" << endl; }
  void disconnect() { cout << "Disconnected from database" << endl; }
  int executeQuery(string query) {
    cout << "Executing: " << query << endl;
    return 1;
  }
};

class Database {
private:
  unique_ptr<DatabaseImpl> impl;

public:
  Database() : impl(make_unique<DatabaseImpl>()) {}

  // Forward interface methods to implementation
  void connect() { impl->connect(); }

  void disconnect() { impl->disconnect(); }

  int executeQuery(string query) { return impl->executeQuery(query); }

  ~Database() {} // impl automatically destroyed
};

/*
BENEFITS OF PIMPL:
- Hide DatabaseImpl completely
- Change DatabaseImpl without recompiling clients
- Reduce compilation dependencies
- Binary compatible updates
- Private data hidden from header file
--------
*/

/*
================================================================================
EXAMPLE 5: COMPOSITE WITH FORWARDING
================================================================================
*/

class Logger {
public:
  virtual ~Logger() = default;
  virtual void log(const string &message) = 0;
};

class FileLogger : public Logger {
public:
  void log(const string &message) override {
    cout << "[FILE] " << message << endl;
  }
};

class ConsoleLogger : public Logger {
public:
  void log(const string &message) override {
    cout << "[CONSOLE] " << message << endl;
  }
};

class MultiLogger : public Logger {
private:
  vector<shared_ptr<Logger>> loggers;

public:
  void addLogger(shared_ptr<Logger> logger) { loggers.push_back(logger); }

  void log(const string &message) override {
    for (auto &logger : loggers) {
      logger->log(message);
    }
  }
};

/*
OUTPUT:
--------
[FILE] Database connected
[CONSOLE] Database connected

--------
*/

/*
================================================================================
EXAMPLE 6: PLUGIN ARCHITECTURE
================================================================================
*/

class Plugin {
public:
  virtual ~Plugin() = default;
  virtual void initialize() = 0;
  virtual void execute() = 0;
  virtual void cleanup() = 0;
  virtual string getName() const = 0;
};

class ImagePlugin : public Plugin {
public:
  void initialize() override { cout << "Image plugin initialized" << endl; }

  void execute() override { cout << "Processing image..." << endl; }

  void cleanup() override { cout << "Image plugin cleaned up" << endl; }

  string getName() const override { return "Image Plugin"; }
};

class VideoPlugin : public Plugin {
public:
  void initialize() override { cout << "Video plugin initialized" << endl; }

  void execute() override { cout << "Processing video..." << endl; }

  void cleanup() override { cout << "Video plugin cleaned up" << endl; }

  string getName() const override { return "Video Plugin"; }
};

class PluginManager {
private:
  vector<shared_ptr<Plugin>> plugins;

public:
  void loadPlugin(shared_ptr<Plugin> plugin) {
    plugins.push_back(plugin);
    cout << "Loaded: " << plugin->getName() << endl;
  }

  void initializeAll() {
    for (auto &p : plugins) {
      p->initialize();
    }
  }

  void executeAll() {
    for (auto &p : plugins) {
      p->execute();
    }
  }

  void cleanupAll() {
    for (auto &p : plugins) {
      p->cleanup();
    }
  }
};

/*
OUTPUT:
--------
Loaded: Image Plugin
Loaded: Video Plugin
Image plugin initialized
Video plugin initialized
Processing image...
Processing video...

--------
*/

/*
================================================================================
EXAMPLE 7: AVOIDING CIRCULAR DEPENDENCIES WITH WEAK_PTR
================================================================================
*/

class GraphNodeB; // Forward declaration

class GraphNodeA {
private:
  string name;
  shared_ptr<GraphNodeB> childB;
  weak_ptr<GraphNodeA> parentRef; // weak_ptr to avoid cycle

public:
  GraphNodeA(string n) : name(n) {}

  void setChild(shared_ptr<GraphNodeB> child) { childB = child; }

  void setParent(shared_ptr<GraphNodeA> parent) { parentRef = parent; }

  string getName() const { return name; }

  void display() { cout << "Node: " << name << endl; }
};

class GraphNodeB {
private:
  string name;
  weak_ptr<GraphNodeA> parentRef; // weak_ptr breaks cycle

public:
  GraphNodeB(string n) : name(n) {}

  void setParent(shared_ptr<GraphNodeA> parent) { parentRef = parent; }

  string getName() const { return name; }

  void display() { cout << "Node: " << name << endl; }
};

/*
WHY WEAK_PTR?
- A holds shared_ptr to B
- B holds weak_ptr to A
- When A is destroyed, weak_ptr doesn't prevent destruction
- No reference cycle, automatic cleanup
--------
*/

/*
================================================================================
EXAMPLE 8: COMPOSITION VS INHERITANCE COMPARISON
================================================================================
*/

// BAD: Deep inheritance hierarchy
class Shape {};
class Polygon : public Shape {};
class Quadrilateral : public Polygon {};
class Rectangle : public Quadrilateral {};

// BETTER: Composition approach
class Color {
private:
  int r, g, b;

public:
  Color(int r, int g, int b) : r(r), g(g), b(b) {}
};

class FillStyle {
private:
  Color color;

public:
  FillStyle(Color c) : color(c) {}
};

class ShapeComposed {
private:
  FillStyle fillStyle;

public:
  ShapeComposed(Color c) : fillStyle(c) {}
};

/*
ADVANTAGES OF COMPOSITION:
1. Flexibility - change behavior at runtime
2. Simplicity - fewer inheritance levels
3. Reusability - components used in different contexts
4. Maintainability - easier to understand
5. Testability - components can be mocked

WHEN INHERITANCE IS BETTER:
1. True "is-a" relationship
2. Need polymorphic behavior
3. Small, stable hierarchy
4. Template method pattern
--------
*/

/*
================================================================================
KEY CONCEPTS SUMMARY BOX
================================================================================

DELEGATION:
- Forward calls to composed object
- Maintains loose coupling
- Simplifies interfaces
- Example: Window -> Panel -> Components

DECORATOR PATTERN:
- Runtime behavior modification
- Stack multiple decorators
- More flexible than inheritance
- Example: Coffee + Milk + Sugar

STRATEGY PATTERN:
- Swap algorithms dynamically
- Encapsulate algorithm families
- Client-independent algorithm changes
- Example: Different payment methods

PIMPL PATTERN:
- Hide implementation in private pointer
- Reduce compilation dependencies
- Enable binary compatibility
- Example: Database interface

PLUGIN ARCHITECTURE:
- Dynamic loading of components
- Extensibility without modification
- Loose coupling between plugins
- Example: Media player plugins

WEAK_PTR FOR CYCLES:
- Breaks circular ownership
- Parent owns child
- Child weakly references parent
- Automatic cleanup when parent destroyed

COMPOSITION ADVANTAGES:
- Runtime flexibility
- Better encapsulation
- Reduced complexity
- No fragile base class problem

================================================================================
*/

/*
================================================================================
COMMON MISTAKES - ADVANCED
================================================================================

❌ MISTAKE 1: Strong reference cycle
    class A {
        shared_ptr<B> b;
    };
    class B {
        shared_ptr<A> a;  // Both hold strong refs!
    };

✓ CORRECT:
    class B {
        weak_ptr<A> a;  // B uses weak_ptr
    };

-----

❌ MISTAKE 2: Too many delegations obscuring logic
    Window -> Panel -> Layout -> Widget
    // Too many indirections

✓ CORRECT:
    Keep delegation 2-3 levels max

-----

❌ MISTAKE 3: Inconsistent decorator behavior
    Decorators should be stackable and composable
    Avoid decorator-specific logic

✓ CORRECT:
    Each decorator is independent and stackable

-----

❌ MISTAKE 4: Exposing implementation in PIMPL
    class Database {
        DatabaseImpl* impl;  // MISTAKE: exposed
    };

✓ CORRECT:
    class Database {
        unique_ptr<DatabaseImpl> impl;  // Private
    };

-----

❌ MISTAKE 5: Not managing plugin lifetimes
    // Plugins not cleaned up in reverse order
    // Memory leaks possible

✓ CORRECT:
    Proper initialization/cleanup order

================================================================================
*/

/*
================================================================================
PRACTICE EXERCISES
================================================================================

Exercise 1: Text Editor with Decorators
Text with Bold, Italic, Underline decorators
Stack multiple decorators
Calculate rendering properties

Exercise 2: Game Component System
Entity with composable components
Health, Physics, Rendering components
Update all components

Exercise 3: Configuration with PIMPL
Hide configuration implementation
Change backend without affecting API
Support XML, JSON, INI backends

Exercise 4: Logger with Multiple Outputs
Log to file, console, network simultaneously
Composable logger architecture
Add/remove loggers dynamically

Exercise 5: Weapon System with Strategies
Different attack strategies
Switch at runtime
Damage calculation varies by strategy

Exercise 6: UI Framework with Delegates
Window delegates to panel
Panel delegates to components
Efficient event propagation

Exercise 7: Notification System
Multiple notification channels (Email, SMS, Push)
Compose multiple notifiers
Send to all simultaneously

Exercise 8: Document Processor
Processors for parsing, validation, formatting
Compose processors
Chain processing pipeline

Exercise 9: Cache with Strategies
Different cache policies (LRU, FIFO, Random)
Strategy pattern for eviction
Switch policies without code change

Exercise 10: Event System with Composite Listeners
Multiple listeners for single event
Listener groups
Efficient event distribution

================================================================================
*/

// Main demonstration
int main() {
  cout << "================== ADVANCED COMPOSITION & AGGREGATION "
          "==================\n\n";

  // Example 1: Delegation
  cout << "--- EXAMPLE 1: DELEGATION PATTERN ---\n";
  {
    Window window("My App");
    window.addComponent(make_shared<Button>("Click Me"));
    window.addComponent(make_shared<TextBox>("Enter text"));
    window.display();
  }
  cout << "\n";

  // Example 2: Decorator
  cout << "--- EXAMPLE 2: DECORATOR PATTERN ---\n";
  {
    auto coffee = make_shared<Coffee>();
    cout << "Base: " << coffee->getDescription() << " - $" << coffee->getCost()
         << endl;

    auto withMilk = make_shared<MilkDecorator>(coffee);
    cout << "With Milk: " << withMilk->getDescription() << " - $"
         << withMilk->getCost() << endl;

    auto full = make_shared<WhippedCreamDecorator>(
        make_shared<SugarDecorator>(withMilk));
    cout << "Full: " << full->getDescription() << " - $" << full->getCost()
         << endl;
  }
  cout << "\n";

  // Example 3: Strategy
  cout << "--- EXAMPLE 3: STRATEGY PATTERN ---\n";
  {
    Order order(99.99);

    cout << "Payment with Credit Card:\n";
    order.setPaymentMethod(
        make_shared<CreditCardPayment>("1234-5678-9012-3456", "John"));
    order.checkout();

    cout << "Payment with PayPal:\n";
    order.setPaymentMethod(make_shared<PayPalPayment>("john@email.com"));
    order.checkout();
  }
  cout << "\n";

  // Example 4: PIMPL
  cout << "--- EXAMPLE 4: PIMPL PATTERN ---\n";
  {
    Database db;
    db.connect();
    db.executeQuery("SELECT * FROM users");
    db.disconnect();
  }
  cout << "\n";

  // Example 5: Composite Forwarding
  cout << "--- EXAMPLE 5: COMPOSITE FORWARDING ---\n";
  {
    auto multiLogger = make_shared<MultiLogger>();
    multiLogger->addLogger(make_shared<FileLogger>());
    multiLogger->addLogger(make_shared<ConsoleLogger>());
    multiLogger->log("System started");
  }
  cout << "\n";

  // Example 6: Plugin Architecture
  cout << "--- EXAMPLE 6: PLUGIN ARCHITECTURE ---\n";
  {
    PluginManager manager;
    manager.loadPlugin(make_shared<ImagePlugin>());
    manager.loadPlugin(make_shared<VideoPlugin>());
    manager.initializeAll();
    manager.executeAll();
    manager.cleanupAll();
  }
  cout << "\n";

  // Example 7: Weak Ptr
  cout << "--- EXAMPLE 7: WEAK_PTR FOR CYCLES ---\n";
  {
    auto nodeA = make_shared<GraphNodeA>("A");
    auto nodeB = make_shared<GraphNodeB>("B");
    nodeA->setChild(nodeB);
    nodeB->setParent(nodeA);
    cout << "Graph created with weak_ptr cycle breaking" << endl;
  }
  cout << "\n";

  return 0;
}

/*
================================================================================
FULL PROGRAM OUTPUT:
================================================================================

================== ADVANCED COMPOSITION & AGGREGATION ==================

--- EXAMPLE 1: DELEGATION PATTERN ---
=== My App ===
Panel contents:
[Click Me]
|Enter text|

--- EXAMPLE 2: DECORATOR PATTERN ---
Base: Coffee - $2.5
With Milk: Coffee with Milk - $3
Full: Coffee with Milk and Sugar with Whipped Cream - $3.95

--- EXAMPLE 3: STRATEGY PATTERN ---
Payment with Credit Card:
Paid $99.99 using Credit Card 3456
Payment with PayPal:
Paid $99.99 via PayPal to john@email.com

--- EXAMPLE 4: PIMPL PATTERN ---
Connected to database
Executing: SELECT * FROM users
Disconnected from database

--- EXAMPLE 5: COMPOSITE FORWARDING ---
[FILE] System started
[CONSOLE] System started

--- EXAMPLE 6: PLUGIN ARCHITECTURE ---
Loaded: Image Plugin
Loaded: Video Plugin
Image plugin initialized
Video plugin initialized
Processing image...
Processing video...
Image plugin cleaned up
Video plugin cleaned up

--- EXAMPLE 7: WEAK_PTR FOR CYCLES ---
Graph created with weak_ptr cycle breaking

================================================================================
*/
