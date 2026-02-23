/*
================================================================================
STATIC MEMBERS - SHARED DATA AND BEHAVIOR ACROSS CLASS INSTANCES
================================================================================
Part 2, Subtopic 15: Static Members (File 1/2)

CONCEPTS COVERED:
- Static data members (class variables)
- Static member functions (class methods)
- Static initialization and storage
- Static local variables
- Const static members
- When to use static members
- Common patterns with statics

KEY LEARNING POINTS:
1. Static members belong to class, not instances
2. All instances share same static data
3. Static functions access only static members
4. Static variables persist during program
5. Initialization requires special syntax
6. Static useful for counters, shared resources
7. Thread safety important for statics

================================================================================
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
================================================================================
THEORY SECTION: STATIC MEMBERS
================================================================================

STATIC DATA MEMBERS:
- Declared in class with 'static' keyword
- Defined outside class with scope resolution
- Shared by all instances
- Initialized once at program start
- Class variable, not instance variable
- One copy regardless of instances

STATIC MEMBER FUNCTIONS:
- Declared with 'static' keyword
- Can access only static members
- Cannot access instance members
- No implicit 'this' pointer
- Called via class name or instance
- Class methods, not instance methods

STORAGE DURATION:
Static: Allocated once, lives entire program
Auto (local): Allocated on stack, freed when scope ends
Dynamic: Allocated on heap, freed when deleted

CONST STATIC MEMBERS:
- Can be initialized in class (C++11+)
- Integer types: in-class initialization
- Other types: defined outside class
- Values known at compile time for integers

STATIC LOCAL VARIABLES:
- Local to function
- Static duration (persists)
- Initialized once on first call
- Useful for counters, state

WHEN TO USE STATICS:
1. Counters (how many objects created)
2. Shared resources (connection pool)
3. Configuration (settings for class)
4. Utility functions (Math.sqrt, Arrays.sort)
5. Object registry/lookup tables
6. Singleton pattern implementation

WHEN NOT TO USE STATICS:
1. Instance-specific data
2. Tight coupling needed
3. Thread safety required without locks
4. Testability concerns
5. Global state causes bugs

================================================================================
*/

/*
================================================================================
EXAMPLE 1: STATIC DATA MEMBER - OBJECT COUNTER
================================================================================
*/

class Student {
private:
  string name;
  int studentId;
  static int nextId;     // STATIC: Shared by all Students
  static int totalCount; // STATIC: Count all instances

public:
  Student(string n) : name(n) {
    studentId = nextId++;
    totalCount++;
  }

  ~Student() { totalCount--; }

  string getName() const { return name; }
  int getId() const { return studentId; }

  // Static member function
  static int getStudentCount() { return totalCount; }

  static int getNextId() { return nextId; }

  void display() const {
    cout << "Student: " << name << " (ID: " << studentId << ")" << endl;
  }
};

// Define static members OUTSIDE the class
int Student::nextId = 1000;
int Student::totalCount = 0;

/*
OUTPUT:
--------
Student 1: Alice (ID: 1000)
Student 2: Bob (ID: 1001)
Total students: 2
Destroyed, Total students: 1

--------
*/

/*
================================================================================
EXAMPLE 2: STATIC MEMBER FUNCTION - UTILITY CLASS
================================================================================
*/

class Math {
public:
  // Static constant
  static constexpr double PI = 3.14159265359;

  // Static member functions (like Java static methods)
  static int absolute(int num) { return num < 0 ? -num : num; }

  static double squareRoot(double num) {
    if (num < 0)
      return 0;
    double result = num;
    for (int i = 0; i < 10; i++) {
      result = (result + num / result) / 2;
    }
    return result;
  }

  static int max(int a, int b) { return a > b ? a : b; }

  static int min(int a, int b) { return a < b ? a : b; }

  static double power(double base, int exp) {
    double result = 1;
    for (int i = 0; i < exp; i++) {
      result *= base;
    }
    return result;
  }
};

/*
OUTPUT:
--------
PI: 3.14159
abs(-5): 5
sqrt(16): 4
max(10, 20): 20
2^3: 8

--------
*/

/*
================================================================================
EXAMPLE 3: STATIC CONSTANT MEMBERS
================================================================================
*/

class Config {
private:
  // Static constant (can initialize in class C++11+)
  static constexpr int MAX_SIZE = 100;
  static const string DEFAULT_NAME; // Non-integral type

  // Regular static variable
  static int debugLevel;

public:
  // Access static constants
  static int getMaxSize() { return MAX_SIZE; }

  static string getDefaultName() { return DEFAULT_NAME; }

  static void setDebugLevel(int level) { debugLevel = level; }

  static int getDebugLevel() { return debugLevel; }

  // Static function that uses constants
  static bool isValidSize(int size) { return size > 0 && size <= MAX_SIZE; }

  static void displayConfig() {
    cout << "Max Size: " << MAX_SIZE << endl;
    cout << "Default Name: " << DEFAULT_NAME << endl;
    cout << "Debug Level: " << debugLevel << endl;
  }
};

// Define non-integral static constants outside class
const string Config::DEFAULT_NAME = "AppConfig";
int Config::debugLevel = 0;

/*
OUTPUT:
--------
Max Size: 100
Default Name: AppConfig
Valid size (50): true
Valid size (150): false

--------
*/

/*
================================================================================
EXAMPLE 4: STATIC LOCAL VARIABLES
================================================================================
*/

class Counter {
public:
  static int callCount() {
    static int count = 0; // Initialized once
    count++;
    return count;
  }

  static void resetCounter() {
    // Cannot directly reset static local variable
    // Design limitation of local statics
  }
};

class RequestHandler {
public:
  static void handleRequest(string request) {
    static int requestId = 0; // Persistent counter
    requestId++;
    cout << "Request #" << requestId << ": " << request << endl;
  }
};

/*
CHARACTERISTICS:
- Initialized once on first call
- Value persists between calls
- Scope limited to function
- Thread-safe initialization (C++11+)
- Useful for call counts, state

OUTPUT:
--------
Call 1, 2, 3... (persisting across calls)

--------
*/

/*
================================================================================
EXAMPLE 5: OBJECT REGISTRY WITH STATIC
================================================================================
*/

class DatabaseConnection {
private:
  int connectionId;
  string server;
  static vector<DatabaseConnection *> registry; // Object registry
  static int nextConnId;

public:
  DatabaseConnection(string s) : server(s) {
    connectionId = nextConnId++;
    registry.push_back(this);
    cout << "Connection #" << connectionId << " to " << server << endl;
  }

  ~DatabaseConnection() {
    auto it = find(registry.begin(), registry.end(), this);
    if (it != registry.end()) {
      registry.erase(it);
    }
    cout << "Connection #" << connectionId << " closed" << endl;
  }

  // Static: get all connections
  static int getConnectionCount() { return registry.size(); }

  // Static: find connection by ID
  static DatabaseConnection *findConnection(int id) {
    for (auto conn : registry) {
      if (conn->connectionId == id) {
        return conn;
      }
    }
    return nullptr;
  }

  // Static: display all connections
  static void displayAllConnections() {
    cout << "Active Connections: " << registry.size() << endl;
    for (auto conn : registry) {
      cout << "  - Connection #" << conn->connectionId << " to " << conn->server
           << endl;
    }
  }

  int getId() const { return connectionId; }
  string getServer() const { return server; }
};

// Define static members
vector<DatabaseConnection *> DatabaseConnection::registry;
int DatabaseConnection::nextConnId = 1;

/*
OUTPUT:
--------
Connection #1 to server1
Connection #2 to server2
Active Connections: 2
  - Connection #1 to server1
  - Connection #2 to server2

--------
*/

/*
================================================================================
EXAMPLE 6: SINGLETON PATTERN (BASIC FORM)
================================================================================
*/

class DatabasePool {
private:
  // Private constructor prevents instantiation
  DatabasePool() {
    cout << "DatabasePool created (should happen once)" << endl;
  }

  // Delete copy constructor and assignment
  DatabasePool(const DatabasePool &) = delete;
  DatabasePool &operator=(const DatabasePool &) = delete;

  static DatabasePool *instance;

public:
  // Static method to get singleton instance
  static DatabasePool *getInstance() {
    if (instance == nullptr) {
      instance = new DatabasePool();
    }
    return instance;
  }

  void executeQuery(string query) { cout << "Executing: " << query << endl; }

  static void destroy() {
    if (instance != nullptr) {
      delete instance;
      instance = nullptr;
    }
  }
};

DatabasePool *DatabasePool::instance = nullptr;

/*
OUTPUT:
--------
First call creates instance
Second call reuses same instance
Same pool used throughout app

--------
*/

/*
================================================================================
EXAMPLE 7: STATIC STATISTICS TRACKER
================================================================================
*/

class Performance {
private:
  static int totalRequests;
  static int successfulRequests;
  static int failedRequests;
  static double totalTime;

public:
  static void recordRequest(bool success, double time) {
    totalRequests++;
    if (success) {
      successfulRequests++;
    } else {
      failedRequests++;
    }
    totalTime += time;
  }

  static void displayStatistics() {
    cout << "=== Performance Statistics ===" << endl;
    cout << "Total Requests: " << totalRequests << endl;
    cout << "Successful: " << successfulRequests << endl;
    cout << "Failed: " << failedRequests << endl;
    cout << "Success Rate: "
         << (totalRequests > 0 ? (100.0 * successfulRequests / totalRequests)
                               : 0)
         << "%" << endl;
    cout << "Total Time: " << totalTime << "ms" << endl;
    cout << "Average Time: "
         << (totalRequests > 0 ? (totalTime / totalRequests) : 0) << "ms"
         << endl;
  }

  static void reset() {
    totalRequests = 0;
    successfulRequests = 0;
    failedRequests = 0;
    totalTime = 0;
  }
};

int Performance::totalRequests = 0;
int Performance::successfulRequests = 0;
int Performance::failedRequests = 0;
double Performance::totalTime = 0;

/*
OUTPUT:
--------
=== Performance Statistics ===
Total Requests: 10
Successful: 8
Failed: 2
Success Rate: 80%
Total Time: 145.5ms
Average Time: 14.55ms

--------
*/

/*
================================================================================
EXAMPLE 8: STATIC VS INSTANCE MEMBERS
================================================================================
*/

class BankAccount {
private:
  string accountNumber;
  double balance;

  // Static: shared by all accounts
  static double interestRate;
  static int totalAccounts;
  static double totalBalance;

public:
  BankAccount(string account, double initial)
      : accountNumber(account), balance(initial) {
    totalAccounts++;
    totalBalance += initial;
  }

  // Instance method: operates on instance data
  void deposit(double amount) {
    balance += amount;
    totalBalance += amount;
  }

  // Instance method
  double getBalance() const { return balance; }

  // Instance method using static
  double calculateInterest() const { return balance * interestRate; }

  // Static method: operates on class data
  static void setInterestRate(double rate) { interestRate = rate; }

  // Static method
  static double getInterestRate() { return interestRate; }

  // Static method
  static int getAccountCount() { return totalAccounts; }

  // Static method
  static double getTotalBalance() { return totalBalance; }

  static void displayStatistics() {
    cout << "=== Bank Statistics ===" << endl;
    cout << "Total Accounts: " << totalAccounts << endl;
    cout << "Total Balance: $" << fixed << setprecision(2) << totalBalance
         << endl;
    cout << "Interest Rate: " << (interestRate * 100) << "%" << endl;
  }
};

double BankAccount::interestRate = 0.03;
int BankAccount::totalAccounts = 0;
double BankAccount::totalBalance = 0;

/*
OUTPUT:
--------
Account 1: $1000
Account 2: $2000
Total Accounts: 2
Total Balance: $3000
Interest Rate: 3%

--------
*/

/*
================================================================================
KEY CONCEPTS SUMMARY BOX
================================================================================

STATIC DATA MEMBER:
- Declared with 'static' keyword in class
- Defined outside class with scope resolution (::)
- Shared by all instances
- One copy regardless of object count
- Initialization happens once at start

STATIC MEMBER FUNCTION:
- Called via ClassName::function() or instance.function()
- Can access only static members
- No implicit 'this' pointer
- Cannot be virtual
- Useful for utility functions

STATIC CONSTANT:
- constexpr: Compile-time constant (integral types)
- const: Runtime initialization (any type)
- In-class initialization (C++11+)

STATIC LOCAL VARIABLE:
- Declared inside function with 'static'
- Initialized once on first call
- Persists across function calls
- Useful for counters, caches

LIFETIME & SCOPE:
- Lifetime: Entire program execution
- Scope: Class (static member) or Function (local static)
- Initialized before main() called
- Destroyed after main() ends

COMMON USE CASES:
1. Counters (object creation count)
2. Registries (track all objects)
3. Utility functions (Math::sqrt)
4. Configuration (shared settings)
5. Singleton pattern
6. Statistics (global tracking)

THREAD SAFETY:
- C++11: Static initialization is thread-safe
- Statics modified concurrently: NOT thread-safe
- Use mutex for concurrent access

================================================================================
*/

/*
================================================================================
COMMON MISTAKES
================================================================================

❌ MISTAKE 1: Forgetting to define static member
    class MyClass {
        static int count;  // Declared
    };
    // Forgot: int MyClass::count = 0;  // Definition

✓ CORRECT:
    class MyClass {
        static int count;
    };
    int MyClass::count = 0;  // Must define outside

-----

❌ MISTAKE 2: Accessing static in instance method incorrectly
    void method() {
        int x = count;  // Missing scope for clarity
    }

✓ CORRECT:
    void method() {
        int x = MyClass::count;  // Clearer
        int y = this->count;     // Also works
    }

-----

❌ MISTAKE 3: Modifying static in const method
    void display() const {
        counter++;  // ERROR: modifying static in const
    }

✓ CORRECT:
    void display() const {
        // Can only read statics
        cout << counter;
    }

-----

❌ MISTAKE 4: Initialization order fiasco
    static Config config = Config();
    // Static order of initialization across files undefined

✓ CORRECT:
    Use getter with lazy initialization

-----

❌ MISTAKE 5: Overusing static for everything
    // Everything static = global variables in disguise
    // Hard to test, tight coupling

✓ CORRECT:
    Use static judiciously for class-level data only

================================================================================
*/

/*
================================================================================
PRACTICE EXERCISES
================================================================================

Exercise 1: Employee Class Counter
Track total employees created/destroyed
Display statistics

Exercise 2: Utility Math Class
Static functions: GCD, LCM, factorial
Static PI constant
Pure static utility class

Exercise 3: Configuration Manager
Static configuration settings
Get/set methods
Load from file

Exercise 4: Connection Pool
Track active connections
Find connection by ID
Limit max connections

Exercise 5: Transaction Logger
Log all transactions (static)
Get transaction count
Search transaction history

Exercise 6: Game State Manager
Player count tracking
Score statistics
Reset game state

Exercise 7: Memory Allocator
Track allocated memory
Display memory statistics
Limit maximum memory

Exercise 8: ID Generator
Generate unique IDs
Track used IDs
Reset generator

Exercise 9: Service Registry
Register services
Find service by name
List all services

Exercise 10: Statistics Collector
Collect metrics
Calculate mean, median, std dev
Display statistics

================================================================================
*/

// Main demonstration
int main() {
  cout << "================== STATIC MEMBERS BASICS ==================\n\n";

  // Example 1: Object Counter
  cout << "--- EXAMPLE 1: STATIC COUNTER ---\n";
  {
    Student s1("Alice");
    s1.display();
    cout << "Total: " << Student::getStudentCount() << endl;

    Student s2("Bob");
    s2.display();
    cout << "Total: " << Student::getStudentCount() << endl;
  }
  cout << "After scope, Total: " << Student::getStudentCount() << "\n\n";

  // Example 2: Utility Class
  cout << "--- EXAMPLE 2: STATIC UTILITY FUNCTIONS ---\n";
  cout << "PI: " << Math::PI << endl;
  cout << "abs(-5): " << Math::absolute(-5) << endl;
  cout << "sqrt(16): " << Math::squareRoot(16) << endl;
  cout << "max(10, 20): " << Math::max(10, 20) << endl;
  cout << "2^3: " << Math::power(2, 3) << "\n\n";

  // Example 3: Static Constants
  cout << "--- EXAMPLE 3: STATIC CONSTANTS ---\n";
  cout << "Max Size: " << Config::getMaxSize() << endl;
  cout << "Default Name: " << Config::getDefaultName() << endl;
  cout << "Valid size 50: " << (Config::isValidSize(50) ? "true" : "false")
       << endl;
  cout << "Valid size 150: " << (Config::isValidSize(150) ? "true" : "false")
       << "\n\n";

  // Example 4: Static Local Variables
  cout << "--- EXAMPLE 4: STATIC LOCAL VARIABLES ---\n";
  cout << "Call 1: " << Counter::callCount() << endl;
  cout << "Call 2: " << Counter::callCount() << endl;
  cout << "Call 3: " << Counter::callCount() << "\n\n";

  // Example 5: Object Registry
  cout << "--- EXAMPLE 5: OBJECT REGISTRY ---\n";
  {
    DatabaseConnection conn1("database1.local");
    DatabaseConnection conn2("database2.local");
    DatabaseConnection::displayAllConnections();
  }
  cout << "Connections after scope: "
       << DatabaseConnection::getConnectionCount() << "\n\n";

  // Example 6: Singleton Pattern
  cout << "--- EXAMPLE 6: SINGLETON PATTERN ---\n";
  DatabasePool *pool1 = DatabasePool::getInstance();
  pool1->executeQuery("SELECT * FROM users");

  DatabasePool *pool2 = DatabasePool::getInstance();
  cout << "pool1 == pool2: " << (pool1 == pool2 ? "true" : "false") << "\n\n";

  // Example 7: Statistics Tracker
  cout << "--- EXAMPLE 7: STATISTICS TRACKER ---\n";
  Performance::recordRequest(true, 10.5);
  Performance::recordRequest(true, 12.3);
  Performance::recordRequest(false, 8.2);
  Performance::recordRequest(true, 11.1);
  Performance::displayStatistics();
  cout << "\n";

  // Example 8: Bank Account Statistics
  cout << "--- EXAMPLE 8: BANK ACCOUNT STATISTICS ---\n";
  {
    BankAccount account1("12345", 1000);
    BankAccount account2("12346", 2000);
    BankAccount account3("12347", 1500);

    BankAccount::setInterestRate(0.05);
    BankAccount::displayStatistics();
  }
  cout << "\n";

  DatabasePool::destroy();
  return 0;
}

/*
================================================================================
FULL PROGRAM OUTPUT:
================================================================================

================== STATIC MEMBERS BASICS ==================

--- EXAMPLE 1: STATIC COUNTER ---
Student: Alice (ID: 1000)
Total: 1
Student: Bob (ID: 1001)
Total: 2
After scope, Total: 0

--- EXAMPLE 2: STATIC UTILITY FUNCTIONS ---
PI: 3.14159
abs(-5): 5
sqrt(16): 4
max(10, 20): 20
2^3: 8

--- EXAMPLE 3: STATIC CONSTANTS ---
Max Size: 100
Default Name: AppConfig
Valid size 50: true
Valid size 150: false

--- EXAMPLE 4: STATIC LOCAL VARIABLES ---
Call 1: 1
Call 2: 2
Call 3: 3

--- EXAMPLE 5: OBJECT REGISTRY ---
Connection #1 to database1.local
Connection #2 to database2.local
Active Connections: 2
  - Connection #1 to database1.local
  - Connection #2 to database2.local
Connections after scope: 0

--- EXAMPLE 6: SINGLETON PATTERN ---
DatabasePool created (should happen once)
Executing: SELECT * FROM users
pool1 == pool2: true

--- EXAMPLE 7: STATISTICS TRACKER ---
=== Performance Statistics ===
Total Requests: 4
Successful: 3
Failed: 1
Success Rate: 75%
Total Time: 42.1ms
Average Time: 10.525ms

--- EXAMPLE 8: BANK ACCOUNT STATISTICS ===
=== Bank Statistics ===
Total Accounts: 3
Total Balance: $4500.00
Interest Rate: 5%

================================================================================
*/
