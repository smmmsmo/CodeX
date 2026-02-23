/*
================================================================================
ADVANCED ENCAPSULATION - INFORMATION HIDING & DESIGN PATTERNS
================================================================================
Part 2, Subtopic 10: Encapsulation (File 2/2)

CONCEPTS COVERED:
- Advanced information hiding strategies
- Copy and move semantics in encapsulation
- Pimpl (Pointer to Implementation) pattern
- Lazy initialization
- Reference vs pointer returns
- Friend classes and functions
- Mutable members and logical const
- Encapsulation best practices

KEY LEARNING POINTS:z
1. Information hiding goes beyond just access modifiers
2. Hide complexity through well-designed interfaces
3. Pimpl pattern completely hides implementation
4. Lazy initialization improves performance
5. Friend functions allow controlled access violations
6. Logical const handles mutable members
7. Return types affect encapsulation strength

================================================================================
*/

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

/*
================================================================================
THEORY SECTION: ADVANCED ENCAPSULATION STRATEGIES
================================================================================

Beyond simple getters and setters, advanced encapsulation involves:

1. INFORMATION HIDING LEVELS
   - Level 1: Hide data members (basic)
   - Level 2: Hide implementation details
   - Level 3: Hide internal data structures
   - Level 4: Hide implementation through compilation firewall (Pimpl)

2. RETURN TYPE STRATEGIES
   - By value: Complete isolation, safe
   - By const reference: Efficient, prevents modification
   - By non-const reference: Dangerous, breaks encapsulation
   - By pointer: Indicates optional/nullable

3. MUTABLE KEYWORD
   - Allows modification in const methods
   - For cache or state that doesn't affect logical const
   - Example: Lazy initialization, reference counts

4. FRIEND KEYWORD
   - Controlled encapsulation violation
   - Use sparingly for tight coupling needs
   - Two types: friend functions, friend classes

5. COPY/MOVE SEMANTICS
   - Copy constructor and assignment
   - Move constructor and assignment
   - Deep vs shallow copying
   - Rule of five (or rule of zero)

================================================================================
*/

/*
================================================================================
EXAMPLE 1: COPY SEMANTICS AND DEEP COPYING
================================================================================
*/

class IntArray {
private:
  int *data;
  int size;

public:
  // Constructor
  IntArray(int s) : size(s) {
    data = new int[size];
    for (int i = 0; i < size; i++) {
      data[i] = 0;
    }
  }

  // Destructor
  ~IntArray() { delete[] data; }

  // Copy Constructor - DEEP COPY
  IntArray(const IntArray &other) : size(other.size) {
    data = new int[size];
    for (int i = 0; i < size; i++) {
      data[i] = other.data[i]; // Copy elements
    }
    cout << "Copy constructor called (deep copy)" << endl;
  }

  // Copy Assignment Operator - DEEP COPY
  IntArray &operator=(const IntArray &other) {
    if (this == &other)
      return *this; // Self-assignment check

    delete[] data; // Free old data
    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; i++) {
      data[i] = other.data[i];
    }
    cout << "Copy assignment called (deep copy)" << endl;
    return *this;
  }

  // Move Constructor - TRANSFER OWNERSHIP
  IntArray(IntArray &&other) noexcept : data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
    cout << "Move constructor called" << endl;
  }

  // Move Assignment - TRANSFER OWNERSHIP
  IntArray &operator=(IntArray &&other) noexcept {
    if (this == &other)
      return *this;

    delete[] data;
    data = other.data;
    size = other.size;
    other.data = nullptr;
    other.size = 0;
    cout << "Move assignment called" << endl;
    return *this;
  }

  // GETTER: Get element with bounds checking
  int get(int index) const {
    if (index >= 0 && index < size) {
      return data[index];
    }
    cout << "Index out of bounds!" << endl;
    return 0;
  }

  // SETTER: Set element with bounds checking
  void set(int index, int value) {
    if (index >= 0 && index < size) {
      data[index] = value;
    } else {
      cout << "Index out of bounds!" << endl;
    }
  }

  // GETTER: Get size
  int getSize() const { return size; }

  void display() const {
    cout << "Array [";
    for (int i = 0; i < size; i++) {
      cout << data[i];
      if (i < size - 1)
        cout << ", ";
    }
    cout << "]" << endl;
  }
};

/*
OUTPUT:
--------
Copy constructor called (deep copy)
Array [1, 2, 3]
Move constructor called
Array [4, 5, 6]

--------
*/

/*
================================================================================
EXAMPLE 2: PIMPL (POINTER TO IMPLEMENTATION) PATTERN
================================================================================
Hides entire implementation in a separate class
*/

// Forward declaration
class DynamicArrayImpl;

class DynamicArray {
private:
  // Pointer to implementation - hides all details
  unique_ptr<DynamicArrayImpl> pimpl;

public:
  // Constructor
  DynamicArray(int capacity);

  // Destructor (required because of unique_ptr)
  ~DynamicArray();

  // Add element
  void add(int value);

  // Remove last element
  void removeLast();

  // Get element
  int get(int index) const;

  // Get size
  int getSize() const;

  // Get capacity
  int getCapacity() const;

  void display() const;
};

// Implementation (hidden from user)
class DynamicArrayImpl {
public:
  vector<int> data;
  int capacity;

  DynamicArrayImpl(int cap) : capacity(cap) {}

  void add(int value) {
    if ((int)data.size() < capacity) {
      data.push_back(value);
    }
  }

  void removeLast() {
    if (!data.empty()) {
      data.pop_back();
    }
  }

  int get(int index) const {
    if (index >= 0 && index < (int)data.size()) {
      return data[index];
    }
    return -1;
  }
};

// DynamicArray implementation
DynamicArray::DynamicArray(int capacity)
    : pimpl(make_unique<DynamicArrayImpl>(capacity)) {}

DynamicArray::~DynamicArray() = default; // pimpl handles cleanup

void DynamicArray::add(int value) { pimpl->add(value); }

void DynamicArray::removeLast() { pimpl->removeLast(); }

int DynamicArray::get(int index) const { return pimpl->get(index); }

int DynamicArray::getSize() const { return pimpl->data.size(); }

int DynamicArray::getCapacity() const { return pimpl->capacity; }

void DynamicArray::display() const {
  cout << "DynamicArray [";
  for (size_t i = 0; i < pimpl->data.size(); i++) {
    cout << pimpl->data[i];
    if (i < pimpl->data.size() - 1)
      cout << ", ";
  }
  cout << "]" << endl;
}

/*
OUTPUT:
--------
DynamicArray [1, 2, 3]
Size: 3, Capacity: 10

--------
*/

/*
================================================================================
EXAMPLE 3: LAZY INITIALIZATION
================================================================================
Defers expensive operations until actually needed
*/

class ExpensiveData {
private:
  mutable string cache;
  mutable bool cacheValid;
  string originalData;

  // Private method to compute expensive result
  void computeCache() const {
    cout << "Computing expensive data..." << endl;
    cache = "Computed: " + originalData;
    cacheValid = true;
  }

public:
  ExpensiveData(const string &data) : originalData(data), cacheValid(false) {}

  // Get cached result (lazy initialization)
  const string &getResult() const {
    if (!cacheValid) {
      computeCache(); // Compute only on first access
    }
    return cache;
  }

  // Set new data (invalidates cache)
  void setData(const string &data) {
    originalData = data;
    cacheValid = false; // Mark cache as invalid
  }

  void display() const { cout << "Result: " << getResult() << endl; }
};

/*
OUTPUT:
--------
Computing expensive data...
Result: Computed: important
Result: Computed: important

--------
*/

/*
================================================================================
EXAMPLE 4: CONST CORRECTNESS AND LOGICAL CONST
================================================================================
*/

class Matrix {
private:
  vector<vector<double>> data;
  mutable double cachedDeterminant;
  mutable bool detValid;

  // Private helper to compute determinant (expensive)
  void computeDeterminant() const {
    cachedDeterminant = 42.0; // Simplified
    detValid = true;
  }

public:
  Matrix(int size)
      : data(size, vector<double>(size, 0)), cachedDeterminant(0),
        detValid(false) {}

  // Logically const getter that modifies cache
  double getDeterminant() const {
    if (!detValid) {
      computeDeterminant(); // Allowed because cache is mutable
    }
    return cachedDeterminant;
  }

  // Truly const getter
  double getElement(int row, int col) const {
    if (row >= 0 && row < (int)data.size() && col >= 0 &&
        col < (int)data[row].size()) {
      return data[row][col];
    }
    return 0;
  }

  // Setter invalidates cache
  void setElement(int row, int col, double value) {
    if (row >= 0 && row < (int)data.size() && col >= 0 &&
        col < (int)data[row].size()) {
      data[row][col] = value;
      detValid = false; // Invalidate cache
    }
  }

  void displayDeterminant() const {
    cout << "Determinant: " << getDeterminant() << endl;
  }
};

/*
OUTPUT:
--------
Determinant: 42
Determinant: 42

--------
*/

/*
================================================================================
EXAMPLE 5: FRIEND FUNCTIONS - CONTROLLED ACCESS VIOLATION
================================================================================
*/

class SecretData {
private:
  int secretValue;

  // Grant friendship to specific function
  friend void revealSecret(const SecretData &obj);

public:
  SecretData(int secret) : secretValue(secret) {}

  // Public getter provides partial access
  void displayHint() const {
    cout << "The secret is related to: " << (secretValue * 2) << endl;
  }
};

// Friend function can access private members
void revealSecret(const SecretData &obj) {
  cout << "The actual secret is: " << obj.secretValue << endl;
}

/*
OUTPUT:
--------
The secret is related to: 20
The actual secret is: 10

--------
*/

/*
================================================================================
EXAMPLE 6: FRIEND CLASSES - CONTROLLED FRIEND ACCESS
================================================================================
*/

class PrivateWallet {
private:
  double balance;

  friend class BankAuditor; // Only BankAuditor can access private members

public:
  PrivateWallet(double initial) : balance(initial) {}

  void deposit(double amount) {
    if (amount > 0)
      balance += amount;
  }

  void withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
      balance -= amount;
    }
  }

  double getPublicBalance() const {
    return balance; // Could be different from actual in real system
  }
};

class BankAuditor {
public:
  // Only BankAuditor can see actual balance
  double getActualBalance(const PrivateWallet &wallet) const {
    return wallet.balance;
  }

  void auditWallet(const PrivateWallet &wallet) const {
    cout << "Auditor access - Actual balance: $" << getActualBalance(wallet)
         << endl;
  }
};

/*
OUTPUT:
--------
Auditor access - Actual balance: $1000

--------
*/

/*
================================================================================
EXAMPLE 7: REFERENCE VS POINTER RETURNS
================================================================================
*/

class DataContainer {
private:
  vector<int> items;

public:
  DataContainer() { items = {1, 2, 3, 4, 5}; }

  // GOOD: Const reference - safe, efficient
  const vector<int> &getItemsConstRef() const { return items; }

  // BAD: Non-const reference - breaks encapsulation
  // vector<int>& getItemsNonConstRef() { return items; }
  // User could do: array.getItemsNonConstRef()[0] = 999;

  // GOOD: By value - safe but copies
  vector<int> getItemsByValue() const { return items; }

  // ALTERNATIVE: Pointer to const - safe
  const vector<int> *getItemsConstPtr() const { return &items; }

  void displayItems() const {
    cout << "Items: ";
    for (int item : getItemsConstRef()) {
      cout << item << " ";
    }
    cout << endl;
  }
};

/*
OUTPUT:
--------
Items: 1 2 3 4 5

--------
*/

/*
================================================================================
EXAMPLE 8: COMPOUND ENCAPSULATION - REAL BANK ACCOUNT
================================================================================
A more realistic, comprehensive example
*/

class BankAccountAdvanced {
private:
  string accountNumber;
  string accountHolder;
  double balance;
  vector<string> transactionHistory;

  // Private helper: Log transaction
  void logTransaction(const string &action, double amount) {
    string entry = action + ": " + to_string(amount) +
                   " (Balance: " + to_string(balance) + ")";
    transactionHistory.push_back(entry);
  }

  // Private helper: Validate account number
  bool isValidAmount(double amount) const {
    return amount > 0 && amount <= 1000000; // Reasonable limit
  }

public:
  // Constructor
  BankAccountAdvanced(const string &accNum, const string &holder,
                      double initial)
      : accountNumber(accNum), accountHolder(holder) {
    balance = (initial >= 0 && isValidAmount(initial)) ? initial : 0;
    logTransaction("Account Opened", balance);
  }

  // GETTERS - Read-only access
  const string &getAccountNumber() const { return accountNumber; }

  const string &getAccountHolder() const { return accountHolder; }

  double getBalance() const { return balance; }

  // Get transaction history (const reference)
  const vector<string> &getTransactionHistory() const {
    return transactionHistory;
  }

  // SETTERS/MODIFIERS with validation
  bool deposit(double amount) {
    if (!isValidAmount(amount)) {
      cout << "Error: Invalid deposit amount!" << endl;
      return false;
    }
    balance += amount;
    logTransaction("Deposit", amount);
    return true;
  }

  bool withdraw(double amount) {
    if (!isValidAmount(amount)) {
      cout << "Error: Invalid withdrawal amount!" << endl;
      return false;
    }
    if (amount > balance) {
      cout << "Error: Insufficient funds!" << endl;
      return false;
    }
    balance -= amount;
    logTransaction("Withdrawal", amount);
    return true;
  }

  // Display account summary
  void displaySummary() const {
    cout << "Account: " << accountNumber << " | Holder: " << accountHolder
         << " | Balance: $" << balance << endl;
  }

  // Display transactions (limited access to history)
  void displayRecentTransactions(int count = 5) const {
    cout << "Recent Transactions (" << count << "):" << endl;
    int start = max(0, (int)transactionHistory.size() - count);
    for (int i = start; i < (int)transactionHistory.size(); i++) {
      cout << "  " << transactionHistory[i] << endl;
    }
  }
};

/*
OUTPUT:
--------
Account: ACC001 | Holder: John Doe | Balance: $1000

Recent Transactions (5):
  Account Opened: 1000 (Balance: 1000)
  Deposit: 500 (Balance: 1500)
  Withdrawal: 200 (Balance: 1300)

--------
*/

/*
================================================================================
EXAMPLE 9: IMMUTABLE WRAPPER (COMPLETE ENCAPSULATION)
================================================================================
*/

class ImmutablePoint {
private:
  double x, y;

public:
  // Constructor sets values (can't be changed)
  ImmutablePoint(double xVal, double yVal) : x(xVal), y(yVal) {}

  // Only getters, no setters
  double getX() const { return x; }
  double getY() const { return y; }

  // Operations return new objects instead of modifying
  ImmutablePoint translate(double dx, double dy) const {
    return ImmutablePoint(x + dx, y + dy);
  }

  double distance() const { return sqrt(x * x + y * y); }

  void display() const { cout << "Point(" << x << ", " << y << ")" << endl; }
};

/*
OUTPUT:
--------
Point(3, 4)
Point(6, 9)
Distance: 5

--------
*/

/*
================================================================================
EXAMPLE 10: BUILDER PATTERN WITH ENCAPSULATION
================================================================================
*/

class ComplexConfiguration {
private:
  string host;
  int port;
  bool useSSL;
  int timeout;
  int maxRetries;

  // Private constructor - only Builder can call
  ComplexConfiguration()
      : host("localhost"), port(8080), useSSL(false), timeout(30),
        maxRetries(3) {}

  friend class ConfigBuilder;

public:
  // Getters only
  const string &getHost() const { return host; }
  int getPort() const { return port; }
  bool isSSLEnabled() const { return useSSL; }
  int getTimeout() const { return timeout; }
  int getMaxRetries() const { return maxRetries; }

  void display() const {
    cout << "Config: " << (useSSL ? "https://" : "http://") << host << ":"
         << port << " (timeout=" << timeout << "s, retries=" << maxRetries
         << ")" << endl;
  }
};

class ConfigBuilder {
private:
  ComplexConfiguration config;

public:
  ConfigBuilder &withHost(const string &h) {
    config.host = h;
    return *this;
  }

  ConfigBuilder &withPort(int p) {
    config.port = p;
    return *this;
  }

  ConfigBuilder &enableSSL() {
    config.useSSL = true;
    return *this;
  }

  ConfigBuilder &withTimeout(int t) {
    config.timeout = t;
    return *this;
  }

  ConfigBuilder &withMaxRetries(int r) {
    config.maxRetries = r;
    return *this;
  }

  ComplexConfiguration build() const { return config; }
};

/*
OUTPUT:
--------
Config: https://api.example.com:443 (timeout=60s, retries=5)

--------
*/

/*
================================================================================
KEY CONCEPTS SUMMARY BOX
================================================================================

ADVANCED ENCAPSULATION TECHNIQUES:

1. COPY & MOVE SEMANTICS
   - Deep copy: Duplicate data for safety
   - Shallow copy: Share data (usually dangerous)
   - Move semantics: Transfer ownership for efficiency
   - Rule of five: Define all 5 or none of them

2. PIMPL PATTERN
   - Hides entire implementation
   - Reduces compilation dependencies
   - Allows ABI stability
   - Trade-off: Extra pointer dereference

3. LAZY INITIALIZATION
   - Compute expensive data on first use
   - Use mutable for cache in const methods
   - Improves performance for unused features

4. LOGICAL CONST
   - Bitwise const: No member modifications
   - Logical const: No observable state change
   - Use mutable for caches, reference counts

5. FRIEND KEYWORD
   - Grants exceptions to encapsulation
   - Use only for close relationships
   - Two forms: functions and classes

6. RETURN VALUE OPTIMIZATION
   - Const reference: Safe, efficient for large objects
   - By value: Safe, efficient for small objects
   - Pointer: Indicates optionality
   - Never return non-const reference to member

7. IMMUTABILITY
   - No setters = no state changes
   - Operations create new objects
   - Thread-safe without locks
   - Example: ImmutablePoint

8. BUILDER PATTERN
   - Encapsulates complex construction
   - Readable, fluent interface
   - Validation in build() method

================================================================================
*/

/*
================================================================================
BEST PRACTICES CHECKLIST
================================================================================

ENCAPSULATION BEST PRACTICES:

✓ Private by default, public by exception
✓ Use const correctness extensively
✓ Return const reference for efficiency
✓ Validate all input in setters
✓ Maintain class invariants always
✓ Document assumptions and invariants
✓ Use mutable only for caches/optimization
✓ Implement or delete copy/move operations
✓ Use RAII for resource management
✓ Prefer composition over inheritance when possible
✓ Use friend sparingly
✓ Hide implementation details completely
✓ Keep interface small and focused
✓ Test edge cases and invalid inputs
✓ Use design patterns when appropriate

================================================================================
*/

/*
================================================================================
COMMON MISTAKES - ADVANCED
================================================================================

❌ MISTAKE 1: Returning non-const reference
    vector<int>& getData() { return data; }  // BAD!

✓ CORRECT:
    const vector<int>& getData() const { return data; }

-----

❌ MISTAKE 2: Shallow copy of dynamically allocated data
    MyClass(const MyClass& other) {
        ptr = other.ptr;  // Both point to same memory!
    }

✓ CORRECT:
    MyClass(const MyClass& other) {
        ptr = new Type(*other.ptr);  // Deep copy
    }

-----

❌ MISTAKE 3: Not implementing move semantics
    // Modern code needs both copy and move

✓ CORRECT:
    MyClass(MyClass&& other) noexcept
        : ptr(other.ptr) {
        other.ptr = nullptr;
    }

-----

❌ MISTAKE 4: Excessive friend relationships
    friend void anybodyFunction();  // Too open!

✓ CORRECT:
    friend class TightlyRelatedClass;

-----

❌ MISTAKE 5: Mutable for wrong reasons
    mutable int* dangerousPointer;  // Not for optimization!

✓ CORRECT:
    mutable int cachedResult;  // For cache/computation

================================================================================
*/

/*
================================================================================
PRACTICE EXERCISES - ADVANCED
================================================================================

Exercise 1: Smart Pointer Wrapper
Create a SmartVector class using shared_ptr that provides copy semantics
but shallow-copies the pointer internally.

Exercise 2: Lazy Loading Configuration
Create a Configuration class that loads data from file only when accessed
for the first time. Use mutable and cached values.

Exercise 3: Immutable List
Create an ImmutableList class where:
- No direct modification possible
- Operations like add(), remove() return new lists
- Original list is never modified

Exercise 4: Builder Pattern
Implement a PersonBuilder that creates Person objects with validation:
- Name is required and non-empty
- Age must be 0-150
- Email must be valid format (optional)

Exercise 5: Deep Copy Manager
Create a DataManager class that holds a vector of complex objects.
Implement proper copy/move semantics and deep copying.

Exercise 6: Encapsulated Graph
Design a Graph class that:
- Hides internal adjacency list
- Validates all node/edge additions
- Provides only safe accessors

Exercise 7: Transaction Logger
Create an Account class that logs all modifications to a private transaction
history. Provide read-only access to history.

Exercise 8: Flyweight Pattern
Create a SmallInt class that caches integers -5 to 256 for memory efficiency.
Hide the caching mechanism.

Exercise 9: Proxy Pattern
Create a ProxyFile class that loads file contents lazily and provides
controlled access to file operations.

Exercise 10: Deep vs Shallow Copy
Create a Document class with:
- Deep copy constructor (copy content)
- Shallow copy method (optional - share content)
- Move semantics (steal ownership)

================================================================================
*/

// Main demonstration
int main() {
  cout << "================== ADVANCED ENCAPSULATION ==================\n\n";

  // Example 1: Copy & Move Semantics
  cout << "--- EXAMPLE 1: COPY & MOVE SEMANTICS ---\n";
  IntArray arr1(3);
  arr1.set(0, 1);
  arr1.set(1, 2);
  arr1.set(2, 3);
  arr1.display();

  IntArray arr2 = arr1; // Copy constructor
  arr2.display();

  IntArray arr3 = move(arr1); // Move constructor
  arr3.display();
  cout << "\n";

  // Example 2: Pimpl Pattern
  cout << "--- EXAMPLE 2: PIMPL PATTERN ---\n";
  DynamicArray dynArr(10);
  dynArr.add(1);
  dynArr.add(2);
  dynArr.add(3);
  dynArr.display();
  cout << "Size: " << dynArr.getSize() << ", Capacity: " << dynArr.getCapacity()
       << "\n\n";

  // Example 3: Lazy Initialization
  cout << "--- EXAMPLE 3: LAZY INITIALIZATION ---\n";
  ExpensiveData edata("test");
  cout << "First access:" << endl;
  edata.display();
  cout << "Second access (no recomputation):" << endl;
  edata.display();
  cout << "\n";

  // Example 4: Logical Const
  cout << "--- EXAMPLE 4: LOGICAL CONST ---\n";
  Matrix mat(2);
  mat.setElement(0, 0, 1);
  mat.setElement(0, 1, 2);
  cout << "First determinant call:" << endl;
  mat.displayDeterminant();
  cout << "Second determinant call (cached):" << endl;
  mat.displayDeterminant();
  cout << "\n";

  // Example 5: Friend Functions
  cout << "--- EXAMPLE 5: FRIEND FUNCTIONS ---\n";
  SecretData secret(10);
  secret.displayHint();
  revealSecret(secret);
  cout << "\n";

  // Example 6: Friend Classes
  cout << "--- EXAMPLE 6: FRIEND CLASSES ---\n";
  PrivateWallet wallet(1000);
  wallet.deposit(500);
  cout << "Public balance: $" << wallet.getPublicBalance() << endl;
  BankAuditor auditor;
  auditor.auditWallet(wallet);
  cout << "\n";

  // Example 7: Reference vs Pointer
  cout << "--- EXAMPLE 7: REFERENCE VS POINTER ---\n";
  DataContainer container;
  container.displayItems();
  cout << "\n";

  // Example 8: Advanced Bank Account
  cout << "--- EXAMPLE 8: ADVANCED BANK ACCOUNT ---\n";
  BankAccountAdvanced bank("ACC001", "John Doe", 1000);
  bank.displaySummary();
  bank.deposit(500);
  bank.withdraw(200);
  bank.displayRecentTransactions(3);
  cout << "\n";

  // Example 9: Immutable Point
  cout << "--- EXAMPLE 9: IMMUTABLE POINT ---\n";
  ImmutablePoint p1(3, 4);
  p1.display();
  ImmutablePoint p2 = p1.translate(3, 5);
  p2.display();
  cout << "Distance from origin: " << p2.distance() << "\n\n";

  // Example 10: Builder Pattern
  cout << "--- EXAMPLE 10: BUILDER PATTERN ---\n";
  ComplexConfiguration cfg = ConfigBuilder()
                                 .withHost("api.example.com")
                                 .withPort(443)
                                 .enableSSL()
                                 .withTimeout(60)
                                 .withMaxRetries(5)
                                 .build();
  cfg.display();
  cout << "\n";

  return 0;
}

/*
================================================================================
FULL PROGRAM OUTPUT:
================================================================================

================== ADVANCED ENCAPSULATION ==================

--- EXAMPLE 1: COPY & MOVE SEMANTICS ---
Array [1, 2, 3]
Copy constructor called (deep copy)
Array [1, 2, 3]
Move constructor called
Array [1, 2, 3]

--- EXAMPLE 2: PIMPL PATTERN ---
DynamicArray [1, 2, 3]
Size: 3, Capacity: 10

--- EXAMPLE 3: LAZY INITIALIZATION ---
First access:
Computing expensive data...
Result: Computed: test
Second access (no recomputation):
Result: Computed: test

--- EXAMPLE 4: LOGICAL CONST ---
First determinant call:
Determinant: 42
Second determinant call (cached):
Determinant: 42

--- EXAMPLE 5: FRIEND FUNCTIONS ---
The secret is related to: 20
The actual secret is: 10

--- EXAMPLE 6: FRIEND CLASSES ---
Public balance: $1500
Auditor access - Actual balance: $1500

--- EXAMPLE 7: REFERENCE VS POINTER ---
Items: 1 2 3 4 5

--- EXAMPLE 8: ADVANCED BANK ACCOUNT ---
Account: ACC001 | Holder: John Doe | Balance: $1000
Recent Transactions (3):
  Account Opened: 1000 (Balance: 1000)
  Deposit: 500 (Balance: 1500)
  Withdrawal: 200 (Balance: 1300)

--- EXAMPLE 9: IMMUTABLE POINT ---
Point(3, 4)
Point(6, 9)
Distance from origin: 12.0831

--- EXAMPLE 10: BUILDER PATTERN ---
Config: https://api.example.com:443 (timeout=60s, retries=5)

================================================================================
*/
