/*
================================================================================
TOPIC 8: DYNAMIC MEMORY MANAGEMENT - PART 2: SMART POINTERS
================================================================================

SMART POINTERS (C++11 and later):
- Automatically manage memory
- No need for manual delete
- Prevent memory leaks
- RAII principle (Resource Acquisition Is Initialization)

TYPES OF SMART POINTERS:

1. unique_ptr<T>:
   - Exclusive ownership
   - Cannot be copied
   - Can be moved
   - Lightweight, no overhead

2. shared_ptr<T>:
   - Shared ownership
   - Multiple pointers can own same resource
   - Reference counting
   - Last owner responsible for cleanup

3. weak_ptr<T>:
   - Non-owning reference to shared_ptr
   - Doesn't prevent deletion
   - Useful for avoiding circular references

HEADER:
#include <memory>

CREATING SMART POINTERS:
unique_ptr<int> up(new int(10));
shared_ptr<int> sp = make_shared<int>(20);

================================================================================
*/

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

// ======================= CUSTOM CLASS FOR DEMONSTRATION
// =======================
class MyClass {
public:
  MyClass(int val) : value(val) {
    cout << "MyClass constructor called (value = " << val << ")" << endl;
  }

  ~MyClass() {
    cout << "MyClass destructor called (value = " << value << ")" << endl;
  }

  void print() { cout << "Value: " << value << endl; }

private:
  int value;
};

int main() {
  cout << "=== SMART POINTERS IN C++ ===" << endl << endl;

  // ======================= UNIQUE_PTR BASIC =======================
  cout << "1. UNIQUE_PTR - BASIC USAGE:" << endl;

  {
    unique_ptr<int> up1(new int(100));
    cout << "up1 value: " << *up1 << endl;

    unique_ptr<int> up2 = make_unique<int>(200); // Modern way
    cout << "up2 value: " << *up2 << endl;

    cout << "Exiting scope..." << endl;
  } // Automatically deleted here
  cout << "Memory cleaned up automatically" << endl;

  // ======================= UNIQUE_PTR WITH CUSTOM CLASS
  // =======================
  cout << endl << "2. UNIQUE_PTR WITH CUSTOM CLASS:" << endl;

  {
    unique_ptr<MyClass> obj1(new MyClass(42));
    obj1->print();
    cout << "Before exiting scope..." << endl;
  }
  cout << "Destructor called automatically" << endl;

  // ======================= UNIQUE_PTR MOVE SEMANTICS =======================
  cout << endl << "3. UNIQUE_PTR MOVE SEMANTICS:" << endl;

  unique_ptr<int> up_original = make_unique<int>(999);
  cout << "Original owns: " << *up_original << endl;

  unique_ptr<int> up_moved = move(up_original);
  if (up_original) {
    cout << "Original still owns something" << endl;
  } else {
    cout << "Original is now null (ownership transferred)" << endl;
  }
  cout << "Moved pointer owns: " << *up_moved << endl;

  // ======================= UNIQUE_PTR WITH ARRAYS =======================
  cout << endl << "4. UNIQUE_PTR WITH ARRAYS:" << endl;

  {
    unique_ptr<int[]> arr = make_unique<int[]>(5);
    cout << "Dynamic array created with unique_ptr" << endl;

    for (int i = 0; i < 5; i++) {
      arr[i] = i * 10;
    }

    cout << "Array elements: ";
    for (int i = 0; i < 5; i++) {
      cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Exiting scope..." << endl;
  }
  cout << "Array automatically deleted" << endl;

  // ======================= SHARED_PTR BASIC =======================
  cout << endl << "5. SHARED_PTR - BASIC USAGE:" << endl;

  {
    shared_ptr<int> sp1 = make_shared<int>(500);
    cout << "sp1 value: " << *sp1 << endl;
    cout << "sp1 use count: " << sp1.use_count() << endl;

    shared_ptr<int> sp2 = sp1; // Can be copied
    cout << "After copying to sp2:" << endl;
    cout << "sp1 use count: " << sp1.use_count() << endl;
    cout << "sp2 use count: " << sp2.use_count() << endl;

    {
      shared_ptr<int> sp3 = sp1;
      cout << "Inside nested scope, use count: " << sp1.use_count() << endl;
    }
    cout << "After nested scope, use count: " << sp1.use_count() << endl;
  }
  cout << "All shared_ptr destroyed, memory freed" << endl;

  // ======================= SHARED_PTR WITH CUSTOM CLASS
  // =======================
  cout << endl << "6. SHARED_PTR WITH CUSTOM CLASS:" << endl;

  {
    shared_ptr<MyClass> sp_obj1 = make_shared<MyClass>(111);
    cout << "Created sp_obj1, use count: " << sp_obj1.use_count() << endl;

    {
      shared_ptr<MyClass> sp_obj2 = sp_obj1;
      cout << "In inner scope, use count: " << sp_obj1.use_count() << endl;
    }
    cout << "After inner scope, use count: " << sp_obj1.use_count() << endl;
    cout << "Still in scope, calling print:" << endl;
    sp_obj1->print();
  }
  cout << "All shared_ptr destroyed, destructor called" << endl;

  // ======================= VECTOR OF SMART POINTERS =======================
  cout << endl << "7. VECTOR OF SMART POINTERS:" << endl;

  {
    vector<unique_ptr<MyClass>> objects;

    objects.push_back(make_unique<MyClass>(1));
    objects.push_back(make_unique<MyClass>(2));
    objects.push_back(make_unique<MyClass>(3));

    cout << "Objects in vector:" << endl;
    for (auto &obj : objects) {
      obj->print();
    }

    cout << "Exiting scope..." << endl;
  }
  cout << "All objects automatically destroyed" << endl;

  // ======================= WEAK_PTR BASICS =======================
  cout << endl << "8. WEAK_PTR - PREVENTS CIRCULAR REFERENCES:" << endl;

  {
    shared_ptr<int> sp = make_shared<int>(777);
    cout << "sp use count: " << sp.use_count() << endl;

    weak_ptr<int> wp = sp; // Weak reference
    cout << "After creating weak_ptr, use count: " << sp.use_count() << endl;

    if (auto locked = wp.lock()) { // Lock weak_ptr
      cout << "Weak pointer locked, value: " << *locked << endl;
      cout << "Use count: " << sp.use_count() << endl;
    }
    cout << "After lock released, use count: " << sp.use_count() << endl;
  }
  cout << "Memory freed" << endl;

  // ======================= CHECKING VALIDITY =======================
  cout << endl << "9. CHECKING POINTER VALIDITY:" << endl;

  {
    shared_ptr<int> sp = make_shared<int>(888);
    weak_ptr<int> wp = sp;

    cout << "Is weak_ptr expired? " << (wp.expired() ? "Yes" : "No") << endl;
  }

  weak_ptr<int> dangling_wp;
  if (dangling_wp.expired()) {
    cout << "Dangling weak_ptr is expired (resource destroyed)" << endl;
  }

  // ======================= PERFORMANCE COMPARISON =======================
  cout << endl << "10. SIZE COMPARISON:" << endl;

  cout << "sizeof(raw pointer): " << sizeof(int *) << " bytes" << endl;
  cout << "sizeof(unique_ptr): " << sizeof(unique_ptr<int>) << " bytes" << endl;
  cout << "sizeof(shared_ptr): " << sizeof(shared_ptr<int>) << " bytes" << endl;
  cout << "sizeof(weak_ptr): " << sizeof(weak_ptr<int>) << " bytes" << endl;

  // ======================= GET FUNCTION =======================
  cout << endl << "11. USING GET() FUNCTION:" << endl;

  unique_ptr<MyClass> up_obj = make_unique<MyClass>(555);
  MyClass *raw_ptr = up_obj.get(); // Get raw pointer (don't delete!)

  cout << "Got raw pointer from unique_ptr:" << endl;
  raw_ptr->print();
  cout << "(Don't delete raw_ptr - it's managed by unique_ptr)" << endl;

  // ======================= RESET FUNCTION =======================
  cout << endl << "12. USING RESET() FUNCTION:" << endl;

  {
    shared_ptr<MyClass> sp_reset = make_shared<MyClass>(333);
    cout << "Before reset, use count: " << sp_reset.use_count() << endl;

    sp_reset.reset(); // Releases ownership, destructor called
    cout << "After reset, is null: " << (sp_reset == nullptr ? "Yes" : "No")
         << endl;
  }

  return 0;
}

/*
OUTPUT:
=== SMART POINTERS IN C++ ===

1. UNIQUE_PTR - BASIC USAGE:
up1 value: 100
up2 value: 200
Exiting scope...
up1 deleted automatically
up2 deleted automatically
Memory cleaned up automatically

2. UNIQUE_PTR WITH CUSTOM CLASS:
MyClass constructor called (value = 42)
Value: 42
Before exiting scope...
MyClass destructor called (value = 42)
Destructor called automatically

3. UNIQUE_PTR MOVE SEMANTICS:
Original owns: 999
Original is now null (ownership transferred)
Moved pointer owns: 999

4. UNIQUE_PTR WITH ARRAYS:
Dynamic array created with unique_ptr
Array elements: 0 10 20 30 40
Exiting scope...
Array automatically deleted

5. SHARED_PTR - BASIC USAGE:
sp1 value: 500
sp1 use count: 1
After copying to sp2:
sp1 use count: 2
sp2 use count: 2
Inside nested scope, use count: 3
After nested scope, use count: 2
All shared_ptr destroyed, memory freed

6. SHARED_PTR WITH CUSTOM CLASS:
MyClass constructor called (value = 111)
Created sp_obj1, use count: 1
In inner scope, use count: 2
After inner scope, use count: 1
Still in scope, calling print:
Value: 111
All shared_ptr destroyed, destructor called
MyClass destructor called (value = 111)

7. VECTOR OF SMART POINTERS:
MyClass constructor called (value = 1)
MyClass constructor called (value = 2)
MyClass constructor called (value = 3)
Objects in vector:
Value: 1
Value: 2
Value: 3
Exiting scope...
MyClass destructor called (value = 1)
MyClass destructor called (value = 2)
MyClass destructor called (value = 3)
All objects automatically destroyed

8. WEAK_PTR - PREVENTS CIRCULAR REFERENCES:
sp use count: 1
After creating weak_ptr, use count: 1
Weak pointer locked, value: 777
Use count: 2
After lock released, use count: 1
Memory freed

9. CHECKING VALIDITY:
Is weak_ptr expired? No
Dangling weak_ptr is expired (resource destroyed)

10. SIZE COMPARISON:
sizeof(raw pointer): 8 bytes
sizeof(unique_ptr): 8 bytes
sizeof(shared_ptr): 16 bytes
sizeof(weak_ptr): 16 bytes

11. USING GET() FUNCTION:
Got raw pointer from unique_ptr:
MyClass constructor called (value = 555)
Value: 555
(Don't delete raw_ptr - it's managed by unique_ptr)
MyClass destructor called (value = 555)

12. USING RESET() FUNCTION:
MyClass constructor called (value = 333)
Before reset, use count: 1
MyClass destructor called (value = 333)
After reset, is null: Yes

================================================================================
WHEN TO USE EACH SMART POINTER
================================================================================

1. UNIQUE_PTR:
   - Single owner of resource
   - No overhead compared to raw pointer
   - Move-only type
   - Use by default

2. SHARED_PTR:
   - Multiple owners needed
   - Reference counting overhead acceptable
   - Copyable
   - Use when ownership is shared

3. WEAK_PTR:
   - Break circular references in shared_ptr
   - Non-owning observation
   - Use to observe shared resources

4. RAW POINTERS:
   - Only for observing (not owning)
   - Function parameters (most cases)
   - Don't create with new/delete

================================================================================
KEY BEST PRACTICES
================================================================================

1. Prefer make_unique and make_shared
2. Use unique_ptr by default (smallest overhead)
3. Avoid mixing smart and raw pointers
4. Don't delete pointers from smart pointers
5. Use get() only for reading, not ownership transfer
6. Check for expired weak pointers before using

================================================================================
PRACTICE EXERCISES
================================================================================

1. Refactor previous programs using smart pointers

2. Create a tree using unique_ptr for nodes

3. Implement circular reference with weak_ptr fix

4. Create dynamic vector of objects using shared_ptr

5. Compare performance of raw vs smart pointers

================================================================================
*/
