#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

/*
 * =====================================================================
 * TOPIC 8.2: SMART POINTERS - MODERN C++ MEMORY MANAGEMENT
 * =====================================================================
 *
 * WHAT ARE SMART POINTERS?
 * Smart pointers are template classes that manage dynamically allocated
 * memory automatically. They use RAII (Resource Acquisition Is Initialization)
 * to guarantee proper cleanup, preventing memory leaks and dangling pointers.
 *
 * KEY CONCEPTS COVERED:
 * 1. RAII (Resource Acquisition Is Initialization)
 * 2. unique_ptr - Exclusive ownership
 * 3. shared_ptr - Shared ownership (reference counting)
 * 4. weak_ptr - Non-owning reference
 * 5. make_unique and make_shared
 * 6. Custom deleters
 * 7. Smart pointers with arrays
 * 8. Circular reference problem
 * 9. Performance considerations
 * 10. When to use each type
 * 11. Converting between smart pointers
 * 12. Smart pointers in containers
 *
 * =====================================================================
 * WHY SMART POINTERS?
 * =====================================================================
 *
 * PROBLEMS WITH RAW POINTERS:
 *   - Manual memory management (error-prone)
 *   - Memory leaks (forgot to delete)
 *   - Double deletion
 *   - Dangling pointers
 *   - Exception safety issues
 *
 * SMART POINTER BENEFITS:
 *   - Automatic memory management
 *   - Exception-safe
 *   - Clear ownership semantics
 *   - No memory leaks
 *   - No dangling pointers
 *   - Minimal performance overhead
 *
 * THREE TYPES:
 *   1. unique_ptr<T> - Exclusive ownership (most common)
 *   2. shared_ptr<T> - Shared ownership (reference counting)
 *   3. weak_ptr<T> - Non-owning observer (breaks cycles)
 *
 * INCLUDE HEADER:
 *   #include <memory>
 *
 * =====================================================================
 * OWNERSHIP SEMANTICS
 * =====================================================================
 *
 * UNIQUE OWNERSHIP (unique_ptr):
 *   - Only one owner at a time
 *   - Can't be copied, only moved
 *   - Destroyed when owner goes out of scope
 *   - Zero overhead vs raw pointer
 *
 * SHARED OWNERSHIP (shared_ptr):
 *   - Multiple owners allowed
 *   - Can be copied
 *   - Destroyed when last owner destroyed
 *   - Small overhead (reference count)
 *
 * NON-OWNING (weak_ptr):
 *   - Doesn't own the object
 *   - Doesn't prevent destruction
 *   - Must lock() to access
 *   - Breaks circular dependencies
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: UNIQUE_PTR BASICS ==============
void example1_unique_ptr_basics() {
  cout << "\n============== EXAMPLE 1: UNIQUE_PTR BASICS =============="
       << endl;
  cout << "Exclusive ownership smart pointer\n" << endl;

  // Create unique_ptr (OLD WAY - C++11)
  unique_ptr<int> ptr1(new int(42));
  cout << "Value: " << *ptr1 << endl;
  cout << "Address: " << ptr1.get() << endl;

  // Create unique_ptr (MODERN WAY - C++14+)
  auto ptr2 = make_unique<int>(100);
  cout << "Value: " << *ptr2 << endl;

  // Create with string
  auto str_ptr = make_unique<string>("Hello, Smart Pointers!");
  cout << "String: " << *str_ptr << endl;
  cout << "Length: " << str_ptr->length() << endl;

  // No need to delete! Automatic cleanup when scope ends
  cout << "\nNo manual delete needed - automatic cleanup!" << endl;

  cout << "\nKEY POINTS:" << endl;
  cout << "1. Exclusive ownership - only one owner" << endl;
  cout << "2. Cannot be copied (compiler error)" << endl;
  cout << "3. Can be moved (transfer ownership)" << endl;
  cout << "4. Automatically deletes on destruction" << endl;
  cout << "5. Use make_unique<T>(args) (preferred)" << endl;
}

// ============== EXAMPLE 2: UNIQUE_PTR OWNERSHIP TRANSFER ==============
void example2_unique_ptr_move() {
  cout << "\n============== EXAMPLE 2: UNIQUE_PTR MOVE SEMANTICS =============="
       << endl;
  cout << "Transferring ownership with move\n" << endl;

  auto ptr1 = make_unique<int>(42);
  cout << "ptr1: " << *ptr1 << " at " << ptr1.get() << endl;

  // Transfer ownership using move
  auto ptr2 = std::move(ptr1);

  cout << "\nAfter move(ptr1) to ptr2:" << endl;
  cout << "ptr1 is nullptr: " << (ptr1 == nullptr ? "yes" : "no") << endl;
  cout << "ptr2: " << *ptr2 << " at " << ptr2.get() << endl;

  // Can't copy unique_ptr
  // unique_ptr<int> ptr3 = ptr2;  // ERROR! Deleted copy constructor

  // But can move again
  auto ptr3 = std::move(ptr2);
  cout << "\nAfter move(ptr2) to ptr3:" << endl;
  cout << "ptr2 is nullptr: " << (ptr2 == nullptr ? "yes" : "no") << endl;
  cout << "ptr3: " << *ptr3 << " at " << ptr3.get() << endl;

  cout << "\nOWNERSHIP RULES:" << endl;
  cout << "1. Only one owner at any time" << endl;
  cout << "2. Source becomes nullptr after move" << endl;
  cout << "3. Use std::move() for explicit transfer" << endl;
  cout << "4. Move is cheap (just pointer assignment)" << endl;
}

// ============== EXAMPLE 3: UNIQUE_PTR WITH FUNCTIONS ==============
unique_ptr<int> create_unique() {
  auto ptr = make_unique<int>(999);
  cout << "  Created in function: " << *ptr << endl;
  return ptr; // Ownership transferred to caller
}

void process_unique(unique_ptr<int> ptr) {
  cout << "  Processing (ownership transferred): " << *ptr << endl;
  // ptr destroyed here, memory freed
}

void observe_unique(const int *ptr) {
  cout << "  Observing (no ownership): " << *ptr << endl;
}

void example3_unique_ptr_functions() {
  cout << "\n============== EXAMPLE 3: UNIQUE_PTR WITH FUNCTIONS =============="
       << endl;
  cout << "Passing unique_ptr to and from functions\n" << endl;

  // Return unique_ptr (move ownership to caller)
  cout << "1. Returning unique_ptr:" << endl;
  auto ptr1 = create_unique();
  cout << "  Received: " << *ptr1 << endl;

  // Pass by value (transfer ownership)
  cout << "\n2. Passing by value (transfer ownership):" << endl;
  auto ptr2 = make_unique<int>(777);
  process_unique(std::move(ptr2)); // Must use move
  cout << "  ptr2 is now nullptr: " << (ptr2 == nullptr ? "yes" : "no") << endl;

  // Pass raw pointer (no ownership transfer)
  cout << "\n3. Passing raw pointer (observe only):" << endl;
  auto ptr3 = make_unique<int>(555);
  observe_unique(ptr3.get());
  cout << "  ptr3 still owns: " << *ptr3 << endl;

  cout << "\nFUNCTION GUIDELINES:" << endl;
  cout << "1. Return unique_ptr to transfer ownership" << endl;
  cout << "2. Pass by value with move() to transfer ownership" << endl;
  cout << "3. Pass raw pointer (get()) to observe only" << endl;
  cout << "4. Pass by reference to modify without transfer" << endl;
}

// ============== EXAMPLE 4: SHARED_PTR BASICS ==============
void example4_shared_ptr_basics() {
  cout << "\n============== EXAMPLE 4: SHARED_PTR BASICS =============="
       << endl;
  cout << "Shared ownership with reference counting\n" << endl;

  // Create shared_ptr (PREFERRED WAY)
  auto ptr1 = make_shared<int>(42);
  cout << "Value: " << *ptr1 << endl;
  cout << "Reference count: " << ptr1.use_count() << endl;

  {
    // Copy shared_ptr (increases ref count)
    auto ptr2 = ptr1;
    cout << "\nAfter copy to ptr2:" << endl;
    cout << "ptr1 count: " << ptr1.use_count() << endl;
    cout << "ptr2 count: " << ptr2.use_count() << endl;
    cout << "Both point to same object: "
         << (ptr1.get() == ptr2.get() ? "yes" : "no") << endl;

    {
      auto ptr3 = ptr1;
      cout << "\nAfter copy to ptr3:" << endl;
      cout << "Reference count: " << ptr1.use_count() << endl;
    } // ptr3 destroyed, count decreases

    cout << "After ptr3 destroyed:" << endl;
    cout << "Reference count: " << ptr1.use_count() << endl;
  } // ptr2 destroyed, count decreases

  cout << "\nAfter ptr2 destroyed:" << endl;
  cout << "Reference count: " << ptr1.use_count() << endl;
  cout << "\nWhen count reaches 0, object is automatically deleted!" << endl;

  cout << "\nKEY POINTS:" << endl;
  cout << "1. Multiple owners allowed" << endl;
  cout << "2. Can be copied freely" << endl;
  cout << "3. Reference counting tracks owners" << endl;
  cout << "4. Object deleted when count reaches 0" << endl;
  cout << "5. Use make_shared<T>(args) (preferred)" << endl;
}

// ============== EXAMPLE 5: SHARED_PTR COPYING VS MOVING ==============
void example5_shared_ptr_copy_vs_move() {
  cout << "\n============== EXAMPLE 5: SHARED_PTR COPY VS MOVE =============="
       << endl;
  cout << "Understanding copy and move semantics\n" << endl;

  auto ptr1 = make_shared<int>(42);
  cout << "Initial count: " << ptr1.use_count() << endl;

  // COPY: Increases reference count
  auto ptr2 = ptr1;
  cout << "\nAfter copy:" << endl;
  cout << "ptr1 count: " << ptr1.use_count() << endl;
  cout << "ptr2 count: " << ptr2.use_count() << endl;

  // MOVE: Doesn't increase reference count
  auto ptr3 = std::move(ptr1);
  cout << "\nAfter move(ptr1) to ptr3:" << endl;
  cout << "ptr1 is nullptr: " << (ptr1 == nullptr ? "yes" : "no") << endl;
  cout << "ptr2 count: " << ptr2.use_count() << endl;
  cout << "ptr3 count: " << ptr3.use_count() << endl;

  cout << "\nCOPY vs MOVE:" << endl;
  cout << "COPY: Shares ownership, increases ref count" << endl;
  cout << "MOVE: Transfers ownership, same ref count" << endl;
  cout << "TIP: Move when you don't need the source anymore" << endl;
}

// ============== EXAMPLE 6: WEAK_PTR BASICS ==============
void example6_weak_ptr_basics() {
  cout << "\n============== EXAMPLE 6: WEAK_PTR BASICS ==============" << endl;
  cout << "Non-owning observer pointer\n" << endl;

  shared_ptr<int> shared = make_shared<int>(42);
  cout << "shared_ptr count: " << shared.use_count() << endl;

  // Create weak_ptr from shared_ptr
  weak_ptr<int> weak = shared;
  cout << "After creating weak_ptr:" << endl;
  cout << "shared_ptr count: " << shared.use_count() << " (unchanged!)" << endl;
  cout << "weak_ptr expired: " << (weak.expired() ? "yes" : "no") << endl;

  // Access object through weak_ptr
  if (auto locked = weak.lock()) { // Returns shared_ptr
    cout << "\nAccessing via weak_ptr:" << endl;
    cout << "Value: " << *locked << endl;
    cout << "Count during access: " << locked.use_count() << endl;
  }

  // Reset shared_ptr
  shared.reset();
  cout << "\nAfter shared_ptr reset:" << endl;
  cout << "weak_ptr expired: " << (weak.expired() ? "yes" : "no") << endl;

  if (auto locked = weak.lock()) {
    cout << "Object still exists" << endl;
  } else {
    cout << "Object has been destroyed (lock() returns nullptr)" << endl;
  }

  cout << "\nKEY POINTS:" << endl;
  cout << "1. Doesn't increase reference count" << endl;
  cout << "2. Doesn't prevent object destruction" << endl;
  cout << "3. Must lock() to get shared_ptr for access" << endl;
  cout << "4. Check expired() or lock() result" << endl;
  cout << "5. Used to break circular references" << endl;
}

// ============== EXAMPLE 7: CIRCULAR REFERENCE PROBLEM ==============
class Node {
public:
  int value;
  shared_ptr<Node> next; // BAD: Creates circular reference

  Node(int v) : value(v) { cout << "  Node(" << value << ") created" << endl; }

  ~Node() { cout << "  Node(" << value << ") destroyed" << endl; }
};

class SafeNode {
public:
  int value;
  shared_ptr<SafeNode> next;
  weak_ptr<SafeNode> prev; // GOOD: Use weak_ptr for back reference

  SafeNode(int v) : value(v) {
    cout << "  SafeNode(" << value << ") created" << endl;
  }

  ~SafeNode() { cout << "  SafeNode(" << value << ") destroyed" << endl; }
};

void example7_circular_reference() {
  cout
      << "\n============== EXAMPLE 7: CIRCULAR REFERENCE PROBLEM =============="
      << endl;
  cout << "Breaking circular dependencies with weak_ptr\n" << endl;

  cout << "BAD: Circular reference with shared_ptr (MEMORY LEAK):" << endl;
  {
    auto node1 = make_shared<Node>(1);
    auto node2 = make_shared<Node>(2);
    node1->next = node2;
    node2->next = node1; // Circular reference!

    cout << "  node1 count: " << node1.use_count() << endl; // 2
    cout << "  node2 count: " << node2.use_count() << endl; // 2
    cout << "  Scope ends..." << endl;
  } // LEAK! Nodes keep each other alive
  cout << "  (Nodes NOT destroyed - memory leak!)" << endl;

  cout << "\nGOOD: Breaking cycle with weak_ptr:" << endl;
  {
    auto safe1 = make_shared<SafeNode>(1);
    auto safe2 = make_shared<SafeNode>(2);
    safe1->next = safe2;
    safe2->prev = safe1; // weak_ptr doesn't increase count

    cout << "  safe1 count: " << safe1.use_count() << endl; // 1
    cout << "  safe2 count: " << safe2.use_count()
         << endl; // 2 (owned by safe1->next and safe1)
    cout << "  Scope ends..." << endl;
  } // Proper cleanup!

  cout << "\nSOLUTION:" << endl;
  cout << "1. Use weak_ptr for back-references" << endl;
  cout << "2. Use weak_ptr for observer patterns" << endl;
  cout << "3. Avoid shared_ptr cycles" << endl;
}

// ============== EXAMPLE 8: SMART POINTERS WITH ARRAYS ==============
void example8_smart_ptr_arrays() {
  cout
      << "\n============== EXAMPLE 8: SMART POINTERS WITH ARRAYS =============="
      << endl;
  cout << "Managing dynamic arrays\n" << endl;

  // unique_ptr with array (C++11+)
  unique_ptr<int[]> arr1(new int[5]{1, 2, 3, 4, 5});
  cout << "unique_ptr array: ";
  for (int i = 0; i < 5; i++) {
    cout << arr1[i] << " ";
  }
  cout << endl;

  // unique_ptr with make_unique (C++14+)
  auto arr2 = make_unique<int[]>(5);
  for (int i = 0; i < 5; i++) {
    arr2[i] = (i + 1) * 10;
  }
  cout << "make_unique array: ";
  for (int i = 0; i < 5; i++) {
    cout << arr2[i] << " ";
  }
  cout << endl;

  // shared_ptr with array (need custom deleter pre-C++17)
  shared_ptr<int> arr3(new int[5]{10, 20, 30, 40, 50},
                       [](int *p) { delete[] p; });
  cout << "shared_ptr array: ";
  for (int i = 0; i < 5; i++) {
    cout << arr3.get()[i] << " ";
  }
  cout << endl;

  cout << "\nBEST PRACTICE:" << endl;
  cout << "1. Use std::vector instead of smart pointer arrays" << endl;
  cout << "2. If you must use arrays, unique_ptr<T[]> is cleanest" << endl;
  cout << "3. unique_ptr<T[]> automatically uses delete[]" << endl;
}

// ============== EXAMPLE 9: CUSTOM DELETERS ==============
class File {
public:
  string filename;
  File(const string &name) : filename(name) {
    cout << "  Opening file: " << filename << endl;
  }
  ~File() { cout << "  Closing file: " << filename << endl; }
};

void custom_deleter(File *f) {
  cout << "  Custom deleter called for: " << f->filename << endl;
  delete f;
}

void example9_custom_deleters() {
  cout << "\n============== EXAMPLE 9: CUSTOM DELETERS ==============" << endl;
  cout << "Using custom cleanup functions\n" << endl;

  // Lambda deleter
  cout << "Lambda deleter:" << endl;
  {
    unique_ptr<File, decltype(&custom_deleter)> file1(new File("data.txt"),
                                                      custom_deleter);
  }

  // More common: lambda deleter
  cout << "\nLambda deleter (simpler):" << endl;
  {
    auto deleter = [](File *f) {
      cout << "  Lambda deleter for: " << f->filename << endl;
      delete f;
    };
    unique_ptr<File, decltype(deleter)> file2(new File("log.txt"), deleter);
  }

  // shared_ptr with custom deleter (easier syntax)
  cout << "\nshared_ptr with custom deleter:" << endl;
  {
    shared_ptr<File> file3(new File("config.ini"), [](File *f) {
      cout << "  shared_ptr deleter for: " << f->filename << endl;
      delete f;
    });
  }

  cout << "\nUSE CASES:" << endl;
  cout << "1. File handles (close instead of delete)" << endl;
  cout << "2. Database connections" << endl;
  cout << "3. Network sockets" << endl;
  cout << "4. Custom resource management" << endl;
}

// ============== EXAMPLE 10: SMART POINTERS IN CONTAINERS ==============
class Widget {
public:
  int id;
  Widget(int i) : id(i) { cout << "  Widget(" << id << ") created" << endl; }
  ~Widget() { cout << "  Widget(" << id << ") destroyed" << endl; }
};

void example10_smart_ptr_containers() {
  cout << "\n============== EXAMPLE 10: SMART POINTERS IN CONTAINERS "
          "=============="
       << endl;
  cout << "Storing smart pointers in STL containers\n" << endl;

  cout << "Vector of unique_ptr:" << endl;
  {
    vector<unique_ptr<Widget>> widgets;

    widgets.push_back(make_unique<Widget>(1));
    widgets.push_back(make_unique<Widget>(2));
    widgets.push_back(make_unique<Widget>(3));

    cout << "  Vector has " << widgets.size() << " widgets" << endl;

    // Access widgets
    for (const auto &w : widgets) {
      cout << "  Widget ID: " << w->id << endl;
    }

    cout << "  Vector going out of scope..." << endl;
  } // All widgets automatically destroyed

  cout << "\nVector of shared_ptr:" << endl;
  {
    vector<shared_ptr<Widget>> widgets;

    auto w1 = make_shared<Widget>(10);
    auto w2 = make_shared<Widget>(20);

    widgets.push_back(w1);
    widgets.push_back(w2);
    widgets.push_back(w1); // Can share!

    cout << "  Widget 10 count: " << w1.use_count() << endl;
    cout << "  Widget 20 count: " << w2.use_count() << endl;

    cout << "  Vector going out of scope..." << endl;
  }

  cout << "\nBENEFITS:" << endl;
  cout << "1. No manual cleanup needed" << endl;
  cout << "2. Exception-safe" << endl;
  cout << "3. Clear ownership semantics" << endl;
  cout << "4. No memory leaks" << endl;
}

// ============== EXAMPLE 11: CONVERTING BETWEEN SMART POINTERS ==============
void example11_converting_smart_ptrs() {
  cout
      << "\n============== EXAMPLE 11: CONVERTING SMART POINTERS =============="
      << endl;
  cout << "Moving between different smart pointer types\n" << endl;

  // unique_ptr to shared_ptr (move)
  cout << "unique_ptr -> shared_ptr:" << endl;
  auto unique = make_unique<int>(42);
  shared_ptr<int> shared = std::move(unique);
  cout << "  Converted successfully" << endl;
  cout << "  unique is nullptr: " << (unique == nullptr ? "yes" : "no") << endl;
  cout << "  shared count: " << shared.use_count() << endl;

  // shared_ptr to weak_ptr
  cout << "\nshared_ptr -> weak_ptr:" << endl;
  weak_ptr<int> weak = shared;
  cout << "  Created weak_ptr" << endl;
  cout << "  shared count: " << shared.use_count() << " (unchanged)" << endl;

  // weak_ptr to shared_ptr (lock)
  cout << "\nweak_ptr -> shared_ptr (lock):" << endl;
  if (auto locked = weak.lock()) {
    cout << "  Locked successfully" << endl;
    cout << "  Count during lock: " << locked.use_count() << endl;
  }

  // shared_ptr to raw pointer (get)
  cout << "\nshared_ptr -> raw pointer (observe only):" << endl;
  int *raw = shared.get();
  cout << "  Raw pointer: " << raw << endl;
  cout << "  Value: " << *raw << endl;
  cout << "  WARNING: Don't delete raw pointer!" << endl;

  cout << "\nCONVERSION RULES:" << endl;
  cout << "1. unique -> shared: Use move()" << endl;
  cout << "2. shared -> weak: Direct assignment" << endl;
  cout << "3. weak -> shared: Use lock()" << endl;
  cout << "4. shared -> raw: Use get() (observe only!)" << endl;
  cout << "5. Never delete raw pointer from get()" << endl;
}

// ============== EXAMPLE 12: PERFORMANCE CONSIDERATIONS ==============
void example12_performance() {
  cout << "\n============== EXAMPLE 12: PERFORMANCE CONSIDERATIONS "
          "=============="
       << endl;
  cout << "Understanding overhead and optimization\n" << endl;

  cout << "SIZE COMPARISON:" << endl;
  cout << "sizeof(int*):        " << sizeof(int *) << " bytes" << endl;
  cout << "sizeof(unique_ptr<int>): " << sizeof(unique_ptr<int>) << " bytes"
       << endl;
  cout << "sizeof(shared_ptr<int>): " << sizeof(shared_ptr<int>) << " bytes"
       << endl;
  cout << "sizeof(weak_ptr<int>):   " << sizeof(weak_ptr<int>) << " bytes"
       << endl;

  cout << "\nOVERHEAD ANALYSIS:" << endl;
  cout << "unique_ptr:" << endl;
  cout << "  - Same size as raw pointer" << endl;
  cout << "  - Zero runtime overhead" << endl;
  cout << "  - Perfect for most cases" << endl;

  cout << "\nshared_ptr:" << endl;
  cout << "  - Stores pointer + control block pointer" << endl;
  cout << "  - Control block: ref count + weak count + deleter" << endl;
  cout << "  - Atomic operations for thread safety" << endl;
  cout << "  - Small overhead, but worth it for shared ownership" << endl;

  cout << "\nweak_ptr:" << endl;
  cout << "  - Similar to shared_ptr" << endl;
  cout << "  - No ownership overhead" << endl;
  cout << "  - Lock operation has small cost" << endl;

  cout << "\nOPTIMIZATION TIPS:" << endl;
  cout << "1. Prefer unique_ptr (fastest)" << endl;
  cout << "2. Use shared_ptr only when needed" << endl;
  cout << "3. Pass by reference to avoid copies" << endl;
  cout << "4. Use make_unique/make_shared (single allocation)" << endl;
  cout << "5. Move instead of copy when possible" << endl;
}

/*
 * =====================================================================
 * KEY CONCEPTS SUMMARY
 * =====================================================================
 *
 * 1. UNIQUE_PTR:
 *    - Exclusive ownership
 *    - Cannot be copied, only moved
 *    - Zero overhead vs raw pointer
 *    - Use for most cases
 *    - Syntax: auto ptr = make_unique<T>(args);
 *
 * 2. SHARED_PTR:
 *    - Shared ownership
 *    - Reference counting
 *    - Can be copied
 *    - Automatic cleanup when count reaches 0
 *    - Syntax: auto ptr = make_shared<T>(args);
 *
 * 3. WEAK_PTR:
 *    - Non-owning observer
 *    - Doesn't prevent destruction
 *    - Breaks circular references
 *    - Must lock() to access
 *    - Check expired() before use
 *
 * 4. RAII PRINCIPLE:
 *    - Resource Acquisition Is Initialization
 *    - Acquire in constructor, release in destructor
 *    - Automatic cleanup
 *    - Exception-safe
 *
 * 5. BEST PRACTICES:
 *    - Prefer unique_ptr by default
 *    - Use shared_ptr for shared ownership
 *    - Use weak_ptr to break cycles
 *    - Always use make_unique/make_shared
 *    - Pass by reference when possible
 *    - Never manually delete smart pointers
 *
 * =====================================================================
 * WHEN TO USE WHICH SMART POINTER
 * =====================================================================
 *
 * USE UNIQUE_PTR WHEN:
 *   - Single ownership
 *   - Transferring ownership
 *   - Factory functions
 *   - Replacing new/delete
 *   - Most common case (default choice)
 *
 * USE SHARED_PTR WHEN:
 *   - Multiple owners needed
 *   - Unclear ownership lifetime
 *   - Callbacks outlive creator
 *   - Shared resources
 *   - Multiple containers share same object
 *
 * USE WEAK_PTR WHEN:
 *   - Observer pattern
 *   - Breaking circular references
 *   - Cache implementations
 *   - Parent-child relationships (child holds weak_ptr to parent)
 *   - Temporary access to shared resource
 *
 * AVOID RAW POINTERS WHEN:
 *   - Ownership is involved
 *   - Managing lifetime
 *   - Can use smart pointers instead
 *
 * USE RAW POINTERS FOR:
 *   - Non-owning parameters
 *   - Performance-critical code (after profiling)
 *   - C APIs
 *   - Algorithms (iterators)
 *
 * =====================================================================
 * COMMON PATTERNS
 * =====================================================================
 *
 * FACTORY FUNCTION:
 *   unique_ptr<Widget> createWidget() {
 *     return make_unique<Widget>();
 *   }
 *
 * PASSING TO FUNCTION (observe):
 *   void process(const Widget* widget) {
 *     // Use widget, don't own it
 *   }
 *   auto w = make_unique<Widget>();
 *   process(w.get());
 *
 * PASSING TO FUNCTION (transfer ownership):
 *   void sink(unique_ptr<Widget> widget) {
 *     // Take ownership
 *   }
 *   sink(move(widget));
 *
 * SHARED RESOURCE:
 *   auto resource = make_shared<Resource>();
 *   thread1.setResource(resource);
 *   thread2.setResource(resource);
 *
 * OBSERVER:
 *   weak_ptr<Subject> observer = subject;
 *   if (auto s = observer.lock()) {
 *     s->notify();
 *   }
 *
 * =====================================================================
 * COMMON MISTAKES TO AVOID
 * =====================================================================
 *
 * 1. Using new instead of make_unique/make_shared
 * 2. Creating shared_ptr from same raw pointer twice
 * 3. Circular references with shared_ptr
 * 4. Forgetting to use move() with unique_ptr
 * 5. Deleting raw pointer from get()
 * 6. Not checking weak_ptr before use
 * 7. Using shared_ptr when unique_ptr would work
 * 8. Storing shared_ptr when weak_ptr is enough
 * 9. Mixing smart and raw pointer ownership
 * 10. Using smart pointers in performance-critical loops unnecessarily
 *
 * =====================================================================
 */

int main() {
  cout << "=========================================================" << endl;
  cout << "       SMART POINTERS - MODERN C++ MEMORY MANAGEMENT     " << endl;
  cout << "=========================================================" << endl;

  example1_unique_ptr_basics();
  example2_unique_ptr_move();
  example3_unique_ptr_functions();
  example4_shared_ptr_basics();
  example5_shared_ptr_copy_vs_move();
  example6_weak_ptr_basics();
  example7_circular_reference();
  example8_smart_ptr_arrays();
  example9_custom_deleters();
  example10_smart_ptr_containers();
  example11_converting_smart_ptrs();
  example12_performance();

  cout << "\n=========================================================" << endl;
  cout << "         PRACTICE EXERCISES" << endl;
  cout << "=========================================================" << endl;
  cout << "\n1. Convert raw pointer code to use unique_ptr" << endl;
  cout << "2. Implement factory function returning unique_ptr" << endl;
  cout << "3. Create shared resource manager with shared_ptr" << endl;
  cout << "4. Implement observer pattern using weak_ptr" << endl;
  cout << "5. Fix memory leak caused by circular reference" << endl;
  cout << "6. Write function that transfers ownership via unique_ptr" << endl;
  cout << "7. Implement cache using weak_ptr" << endl;
  cout << "8. Create custom deleter for file handling" << endl;
  cout << "9. Build container of polymorphic objects with unique_ptr" << endl;
  cout << "10. Implement doubly-linked list with shared_ptr and weak_ptr"
       << endl;

  cout << "\n=========================================================" << endl;
  cout << "         KEY TAKEAWAYS" << endl;
  cout << "=========================================================" << endl;
  cout << "\n✓ Smart pointers prevent memory leaks automatically" << endl;
  cout << "✓ unique_ptr for exclusive ownership (default choice)" << endl;
  cout << "✓ shared_ptr for shared ownership (reference counting)" << endl;
  cout << "✓ weak_ptr to break circular references" << endl;
  cout << "✓ Always use make_unique/make_shared" << endl;
  cout << "✓ Never manually delete smart pointers" << endl;
  cout << "✓ RAII = automatic resource management" << endl;
  cout << "\n=========================================================" << endl;

  return 0;
}
