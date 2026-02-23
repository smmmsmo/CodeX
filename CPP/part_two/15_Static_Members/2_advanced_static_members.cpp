/*
================================================================================
ADVANCED STATIC MEMBERS - PATTERNS, CONCURRENCY, AND BEST PRACTICES
================================================================================
Part 2, Subtopic 15: Static Members (File 2/2)

CONCEPTS COVERED:
- Advanced singleton patterns
- Thread-safe statics (C++11)
- Static factories
- Meyers singleton
- Static initialization fiasco
- Compile-time constants vs runtime
- Static polymorphism
- Advanced use cases

KEY LEARNING POINTS:
1. Thread-safe singleton initialization (C++11)
2. Meyers singleton uses function-local static
3. Static factories for object creation
4. Compile-time computation with constexpr
5. Double-checked locking (performance)
6. Type-safe alternatives to global variables
7. Static members in inheritance hierarchies

================================================================================
*/

#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std;

/*
================================================================================
THEORY SECTION: ADVANCED STATIC PATTERNS
================================================================================

THREAD-SAFE SINGLETON (C++11):
- Static local variable initialization is thread-safe
- Magic statics: Compiler handles synchronization
- No manual locks needed
- Most recommended approach

MEYERS SINGLETON:
- Named after Scott Meyers
- Uses function-local static
- Guaranteed thread-safe (C++11+)
- Clean and simple implementation
- Lazy initialization

STATIC FACTORY:
- Static method creates instances
- Controls object creation
- Can enforce constraints
- Track created objects
- Example: Object pool

DOUBLE-CHECKED LOCKING:
- Performance optimization
- First check without lock
- Second check with lock
- Reduces lock contention
- Requires careful implementation

CONSTEXPR STATIC:
- Compile-time computation
- Zero runtime overhead
- Values determined at compile-time
- Type-safe alternatives to macros
- Enables compile-time polymorphism

STATIC POLYMORPHISM:
- Templates instead of virtual functions
- No runtime overhead
- Type-safe
- Known at compile-time
- Curiously Recurring Template Pattern (CRTP)

INITIALIZATION FIASCO:
- Order of static initialization undefined (across files)
- Solution: Lazy initialization with functions
- Or use static_cast/singleton pattern
- Avoid static object dependencies

================================================================================
*/

/*
================================================================================
EXAMPLE 1: MEYERS SINGLETON - THREAD-SAFE
================================================================================
*/

class Configuration {
private:
  // Private constructor
  Configuration() { cout << "Configuration instance created" << endl; }

  // Delete copy operations
  Configuration(const Configuration &) = delete;
  Configuration &operator=(const Configuration &) = delete;

  // Delete move operations
  Configuration(Configuration &&) = delete;
  Configuration &operator=(Configuration &&) = delete;

  map<string, string> settings;

public:
  // Meyers singleton: thread-safe since C++11
  static Configuration &getInstance() {
    static Configuration instance; // Created once, thread-safe
    return instance;
  }

  void setSetting(const string &key, const string &value) {
    settings[key] = value;
  }

  string getSetting(const string &key) const {
    auto it = settings.find(key);
    if (it != settings.end()) {
      return it->second;
    }
    return "";
  }

  void displaySettings() const {
    cout << "Configuration Settings:" << endl;
    for (const auto &pair : settings) {
      cout << "  " << pair.first << ": " << pair.second << endl;
    }
  }
};

/*
ADVANTAGES:
- Thread-safe by default (C++11+)
- Lazy initialization
- Simple and clean
- No manual locking
- RAII compliant
--------
*/

/*
================================================================================
EXAMPLE 2: LOGGER SINGLETON WITH TIMESTAMPS
================================================================================
*/

class Logger {
private:
  vector<string> logs;

  Logger() { cout << "Logger instance created" << endl; }

  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  string getTimestamp() const {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    return ctime(&time);
  }

public:
  static Logger &getInstance() {
    static Logger instance;
    return instance;
  }

  void log(const string &level, const string &message) {
    string timestamp = getTimestamp();
    timestamp.pop_back(); // Remove newline from ctime
    string fullLog = "[" + timestamp + "] " + level + ": " + message;
    logs.push_back(fullLog);
    cout << fullLog << endl;
  }

  void info(const string &message) { log("INFO", message); }

  void warn(const string &message) { log("WARN", message); }

  void error(const string &message) { log("ERROR", message); }

  int getLogCount() const { return logs.size(); }

  void displayLogs() const {
    cout << "=== All Logs ===" << endl;
    for (const auto &log : logs) {
      cout << log << endl;
    }
  }
};

/*
OUTPUT:
--------
[2026-02-23 10:30:45] INFO: Application started
[2026-02-23 10:30:46] WARN: Low memory
[2026-02-23 10:30:47] ERROR: Connection failed

--------
*/

/*
================================================================================
EXAMPLE 3: STATIC FACTORY - POOL MANAGEMENT
================================================================================
*/

class DatabaseConnection {
private:
  int connectionId;
  bool inUse;

  // Private constructor - only factory can create
  DatabaseConnection(int id) : connectionId(id), inUse(false) {}

  // Static pool and counter
  static vector<shared_ptr<DatabaseConnection>> pool;
  static int nextId;
  static const int MAX_CONNECTIONS = 5;

public:
  // Delete copy operations
  DatabaseConnection(const DatabaseConnection &) = delete;
  DatabaseConnection &operator=(const DatabaseConnection &) = delete;

  // Static factory method
  static shared_ptr<DatabaseConnection> create() {
    if (pool.size() >= MAX_CONNECTIONS) {
      cout << "Connection pool full!" << endl;
      return nullptr;
    }

    auto conn =
        shared_ptr<DatabaseConnection>(new DatabaseConnection(nextId++));
    pool.push_back(conn);
    cout << "Created connection #" << conn->connectionId << endl;
    return conn;
  }

  // Get connection from pool
  static shared_ptr<DatabaseConnection> getFromPool() {
    for (auto &conn : pool) {
      if (!conn->inUse) {
        conn->inUse = true;
        cout << "Allocated connection #" << conn->connectionId << endl;
        return conn;
      }
    }
    cout << "No available connections" << endl;
    return nullptr;
  }

  void releaseToPool() {
    inUse = false;
    cout << "Released connection #" << connectionId << endl;
  }

  void execute(const string &query) {
    cout << "Executing on connection #" << connectionId << ": " << query
         << endl;
  }

  static int getPoolSize() { return pool.size(); }

  static void displayPoolStatus() {
    cout << "Pool Status (" << pool.size() << " connections):" << endl;
    for (const auto &conn : pool) {
      cout << "  #" << conn->connectionId << " - "
           << (conn->inUse ? "IN USE" : "AVAILABLE") << endl;
    }
  }

  ~DatabaseConnection() {
    cout << "Connection #" << connectionId << " destroyed" << endl;
  }
};

vector<shared_ptr<DatabaseConnection>> DatabaseConnection::pool;
int DatabaseConnection::nextId = 1;

/*
OUTPUT:
--------
Created connection #1
Created connection #2
Allocated connection #1
Allocated connection #2
Connection #1 query
Released connection #1
--------
*/

/*
================================================================================
EXAMPLE 4: COMPILE-TIME CONSTANTS WITH CONSTEXPR
================================================================================
*/

class Math {
public:
  // Compile-time constant
  static constexpr double PI = 3.14159265359;
  static constexpr double E = 2.71828182846;

  // Compile-time function
  static constexpr double square(double x) { return x * x; }

  // Compile-time factorial
  static constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
  }

  // Compile-time power
  static constexpr int power(int base, int exp) {
    return exp == 0 ? 1 : base * power(base, exp - 1);
  }

  // Compile-time Fibonacci
  static constexpr int fibonacci(int n) {
    return n <= 1 ? n : fibonacci(n - 1) + fibonacci(n - 2);
  }
};

/*
COMPILE-TIME COMPUTATION:
- Results computed during compilation
- Zero runtime overhead
- Values available as constants
- Type-safe replacement for macros
--------
*/

/*
================================================================================
EXAMPLE 5: CRTP - COMPILE-TIME POLYMORPHISM
================================================================================
*/

template <typename Derived> class Shape {
public:
  // CRTP: Derived as template parameter
  double area() const { return static_cast<const Derived *>(this)->getArea(); }

  void display() const { static_cast<const Derived *>(this)->show(); }
};

class Circle : public Shape<Circle> {
private:
  double radius;

public:
  Circle(double r) : radius(r) {}

  double getArea() const { return 3.14159 * radius * radius; }

  void show() const { cout << "Circle with radius " << radius << endl; }
};

class Rectangle : public Shape<Rectangle> {
private:
  double width, height;

public:
  Rectangle(double w, double h) : width(w), height(h) {}

  double getArea() const { return width * height; }

  void show() const { cout << "Rectangle " << width << "x" << height << endl; }
};

/*
ADVANTAGES:
- No virtual functions
- Type-safe
- Compile-time resolution
- Zero runtime overhead
- Better performance
--------
*/

/*
================================================================================
EXAMPLE 6: RESOURCE MANAGER SINGLETON
================================================================================
*/

class ResourcePool {
private:
  vector<shared_ptr<string>> resources;
  int allocatedCount;

  ResourcePool() : allocatedCount(0) {
    cout << "Resource pool created" << endl;
  }

  ResourcePool(const ResourcePool &) = delete;
  ResourcePool &operator=(const ResourcePool &) = delete;

public:
  static ResourcePool &getInstance() {
    static ResourcePool instance;
    return instance;
  }

  shared_ptr<string> allocateResource(const string &name) {
    auto resource = make_shared<string>(name);
    resources.push_back(resource);
    allocatedCount++;
    cout << "Allocated resource: " << name << endl;
    return resource;
  }

  int getAllocatedCount() const { return allocatedCount; }

  int getActiveCount() const { return resources.size(); }

  void displayStatus() const {
    cout << "Resource Pool Status:" << endl;
    cout << "  Allocated: " << allocatedCount << endl;
    cout << "  Active: " << getActiveCount() << endl;
    cout << "  Resources:" << endl;
    for (const auto &res : resources) {
      cout << "    - " << *res << " (refs: " << res.use_count() << ")" << endl;
    }
  }

  ~ResourcePool() { cout << "Resource pool destroyed" << endl; }
};

/*
OUTPUT:
--------
Resource pool created
Allocated resource: file1
Allocated resource: file2
Resource Pool Status:
  Allocated: 2
  Active: 2

--------
*/

/*
================================================================================
EXAMPLE 7: OBJECT REGISTRY WITH STATIC
================================================================================
*/

class RegisteredObject {
protected:
  string objectName;
  static map<string, RegisteredObject *> registry;

public:
  RegisteredObject(string name) : objectName(name) {
    registry[name] = this;
    cout << "Registered: " << name << endl;
  }

  virtual ~RegisteredObject() { registry.erase(objectName); }

  virtual void display() const = 0;

  static RegisteredObject *find(const string &name) {
    auto it = registry.find(name);
    return (it != registry.end()) ? it->second : nullptr;
  }

  static void displayAll() {
    cout << "Registered Objects:" << endl;
    for (const auto &pair : registry) {
      cout << "  - " << pair.first << endl;
    }
  }

  static int getCount() { return registry.size(); }
};

map<string, RegisteredObject *> RegisteredObject::registry;

class Player : public RegisteredObject {
private:
  int level;

public:
  Player(string name, int lv) : RegisteredObject(name), level(lv) {}

  void display() const override {
    cout << "Player " << objectName << " Level " << level << endl;
  }
};

class Enemy : public RegisteredObject {
private:
  int health;

public:
  Enemy(string name, int hp) : RegisteredObject(name), health(hp) {}

  void display() const override {
    cout << "Enemy " << objectName << " Health " << health << endl;
  }
};

/*
OUTPUT:
--------
Registered: player1
Registered: enemy1
Total registered: 2
--------
*/

/*
================================================================================
EXAMPLE 8: STATIC INITIALIZATION SAFE PATTERN
================================================================================
*/

class Unsafe {
public:
  static Unsafe &getInstance() {
    static Unsafe *instance = nullptr;
    if (instance == nullptr) {
      instance = new Unsafe();
    }
    return *instance;
  }
};

class Safe {
public:
  // This is the safe pattern - doesn't need null check
  static Safe &getInstance() {
    static Safe instance; // Created once, destroyed at exit
    return instance;
  }
};

/*
WHY SAFE IS BETTER:
- Instance created on first call
- Guaranteed to be destroyed
- No memory leak
- Thread-safe in C++11+
- RAII principle followed
--------
*/

/*
================================================================================
KEY CONCEPTS SUMMARY BOX
================================================================================

MEYERS SINGLETON:
- Static function-local variable
- Thread-safe since C++11
- Lazy initialization
- Simple and clean code
- No manual synchronization needed

FACTORY PATTERN WITH STATIC:
- Static method creates objects
- Enforces creation rules
- Tracks created objects
- Can return shared_ptr
- Useful for pools and registries

COMPILE-TIME CONSTANTS:
- constexpr keyword
- Computed at compile-time
- Zero runtime overhead
- Type-safe
- Enable static polymorphism

CRTP PATTERN:
- Compile-time polymorphism
- No virtual functions
- No runtime cost
- Type-safe
- C++ template technique

THREAD-SAFE STATICS:
- C++11: Automatic thread-safe initialization
- Magic statics: Compiler handles locking
- Function-local statics safest
- Class statics also thread-safe

OBJECT REGISTRY:
- Track all created objects
- Static storage for registry
- Find by name/ID
- Useful for plugin systems
- Enables introspection

ADVANTAGES OF STATICS:
1. Enforce single instance
2. Global access point
3. Lazy initialization
4. No namespace pollution
5. Thread-safe (C++11+)

================================================================================
*/

/*
================================================================================
COMMON MISTAKES - ADVANCED
================================================================================

❌ MISTAKE 1: Not thread-safe manual singleton
    class Singleton {
        static Singleton* instance;
        static Singleton* getInstance() {
            if (instance == nullptr)
                instance = new Singleton();
            return instance;
        }
    };

✓ CORRECT:
    static Singleton& getInstance() {
        static Singleton instance;  // Thread-safe
        return instance;
    }

-----

❌ MISTAKE 2: Static initialization fiasco
    static ConfigFile config("file.cfg");  // Order undefined!
    static Logger logger(config);          // Depends on above

✓ CORRECT:
    ConfigFile& getConfig() {
        static ConfigFile config("file.cfg");
        return config;
    }

-----

❌ MISTAKE 3: Circular static dependencies
    // file1.cpp
    static ObjectA a;

    // file2.cpp
    static ObjectB b(a);  // Undefined order!

✓ CORRECT:
    Use functions returning references (lazy init)

-----

❌ MISTAKE 4: Modifying static in destructor
    ~MyClass() {
        staticCounter--;  // Race condition potential
    }

✓ CORRECT:
    Use thread-safe locks for modification

-----

❌ MISTAKE 5: Ignoring copy/move in singleton
    class Singleton {
        // Forgot to delete copy/move
    };
    Singleton s2 = Singleton::getInstance();  // ERROR!

✓ CORRECT:
    Delete copy and move operations

================================================================================
*/

/*
================================================================================
PRACTICE EXERCISES
================================================================================

Exercise 1: Thread-Safe Logger
Singleton logger with thread-safe logging
Multiple threads logging simultaneously
No race conditions

Exercise 2: Object Pool
Factory creates limited objects
Reuse objects from pool
Track usage statistics

Exercise 3: Configuration Manager
Meyers singleton for configuration
Load from file
Type-safe access

Exercise 4: Event System
Static registry of event handlers
Subscribe/publish pattern
Multiple listeners per event

Exercise 5: Plugin Registry
Register plugins at startup
Load plugins dynamically
Factory method to create plugins

Exercise 6: Cache System
Singleton cache with LRU eviction
Thread-safe access
Statistics tracking

Exercise 7: Service Locator
Register services globally
Find by type/name
Type-safe service lookup

Exercise 8: Resource Manager
Allocate/deallocate resources
Track resource usage
Prevent resource leaks

Exercise 9: State Machine
Static states and transitions
Registry of states
Safe state changes

Exercise 10: Command Factory
Create commands from registry
Undo/redo with static storage
Macro command composition

================================================================================
*/

// Main demonstration
int main() {
  cout << "================== ADVANCED STATIC MEMBERS ==================\n\n";

  // Example 1: Meyers Singleton
  cout << "--- EXAMPLE 1: MEYERS SINGLETON ---\n";
  {
    Configuration &config1 = Configuration::getInstance();
    config1.setSetting("database", "localhost");
    config1.setSetting("port", "5432");

    Configuration &config2 = Configuration::getInstance();
    config2.displaySettings();
    cout << "config1 == config2: " << (&config1 == &config2 ? "true" : "false")
         << "\n\n";
  }

  // Example 2: Logger Singleton
  cout << "--- EXAMPLE 2: LOGGER SINGLETON ---\n";
  {
    Logger &logger = Logger::getInstance();
    logger.info("Application started");
    logger.warn("Low memory warning");
    logger.error("Connection failed");
    cout << "Total logs: " << logger.getLogCount() << "\n\n";
  }

  // Example 3: Static Factory
  cout << "--- EXAMPLE 3: STATIC FACTORY PATTERN ---\n";
  {
    auto conn1 = DatabaseConnection::create();
    auto conn2 = DatabaseConnection::create();
    auto conn3 = DatabaseConnection::create();

    auto allocated1 = DatabaseConnection::getFromPool();
    allocated1->execute("SELECT * FROM users");
    allocated1->releaseToPool();

    DatabaseConnection::displayPoolStatus();
  }
  cout << "\n";

  // Example 4: Compile-time constants
  cout << "--- EXAMPLE 4: CONSTEXPR COMPILE-TIME CONSTANTS ---\n";
  cout << "PI: " << Math::PI << endl;
  cout << "E: " << Math::E << endl;
  cout << "square(5): " << Math::square(5) << endl;
  cout << "factorial(5): " << Math::factorial(5) << endl;
  cout << "2^8: " << Math::power(2, 8) << endl;
  cout << "fibonacci(10): " << Math::fibonacci(10) << "\n\n";

  // Example 5: CRTP
  cout << "--- EXAMPLE 5: CRTP STATIC POLYMORPHISM ---\n";
  {
    Circle circle(5.0);
    circle.display();
    cout << "Area: " << circle.area() << endl;

    Rectangle rect(4.0, 6.0);
    rect.display();
    cout << "Area: " << rect.area() << "\n\n";
  }

  // Example 6: Resource Pool
  cout << "--- EXAMPLE 6: RESOURCE POOL SINGLETON ---\n";
  {
    ResourcePool &pool = ResourcePool::getInstance();
    auto res1 = pool.allocateResource("db_connection");
    auto res2 = pool.allocateResource("file_handle");
    pool.displayStatus();
  }
  cout << "\n";

  // Example 7: Object Registry
  cout << "--- EXAMPLE 7: OBJECT REGISTRY ---\n";
  {
    Player p1("Hero", 10);
    Enemy e1("Goblin", 50);
    Player p2("Mage", 8);

    RegisteredObject::displayAll();
    cout << "Total registered: " << RegisteredObject::getCount() << "\n\n";
  }

  return 0;
}

/*
================================================================================
FULL PROGRAM OUTPUT:
================================================================================

================== ADVANCED STATIC MEMBERS ==================

--- EXAMPLE 1: MEYERS SINGLETON ---
Configuration instance created
Configuration Settings:
  database: localhost
  port: 5432
config1 == config2: true

--- EXAMPLE 2: LOGGER SINGLETON ---
Logger instance created
[current timestamp] INFO: Application started
[current timestamp] WARN: Low memory warning
[current timestamp] ERROR: Connection failed
Total logs: 3

--- EXAMPLE 3: STATIC FACTORY PATTERN ---
Created connection #1
Created connection #2
Created connection #3
Allocated connection #1
Executing on connection #1: SELECT * FROM users
Released connection #1
Pool Status (3 connections):
  #1 - AVAILABLE
  #2 - AVAILABLE
  #3 - AVAILABLE

--- EXAMPLE 4: CONSTEXPR COMPILE-TIME CONSTANTS ---
PI: 3.14159
E: 2.71828
square(5): 25
factorial(5): 120
2^8: 256
fibonacci(10): 55

--- EXAMPLE 5: CRTP STATIC POLYMORPHISM ---
Circle with radius 5
Area: 78.5398
Rectangle 4x6
Area: 24

--- EXAMPLE 6: RESOURCE POOL SINGLETON ---
Resource pool created
Allocated resource: db_connection
Allocated resource: file_handle
Resource Pool Status:
  Allocated: 2
  Active: 2
  Resources:
    - db_connection (refs: 2)
    - file_handle (refs: 2)

--- EXAMPLE 7: OBJECT REGISTRY ---
Registered: Hero
Registered: Goblin
Registered: Mage
Registered Objects:
  - Goblin
  - Hero
  - Mage
Total registered: 3

================================================================================
*/
