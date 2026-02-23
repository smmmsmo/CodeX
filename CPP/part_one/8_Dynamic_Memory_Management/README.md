# Topic 8: Dynamic Memory Management

## 📚 Overview

Dynamic Memory Management is a critical skill for C++ developers, especially in competitive programming and systems programming. This topic covers manual memory allocation with `new`/`delete` and modern C++ smart pointers for automatic memory management.

## 📂 Files in This Topic

### 1. [1_new_delete_dynamic_arrays.cpp](1_new_delete_dynamic_arrays.cpp)
**Focus:** Manual memory management with new, delete, and dynamic arrays

**Key Concepts:**
- Stack vs Heap memory architecture
- `new` operator for single objects and arrays
- `delete` and `delete[]` operators
- Memory leaks and detection
- Dangling pointers and prevention
- 2D dynamic arrays
- Allocation failure handling
- RAII principle introduction
- Manual resizing techniques

**Examples Covered (12):**
1. Stack vs Heap memory comparison
2. `new` operator for single objects
3. `delete` operator and best practices
4. Dynamic arrays with `new[]` and `delete[]`
5. Memory leak demonstration
6. Dangling pointers and how to avoid them
7. 2D dynamic arrays (matrix allocation)
8. Handling allocation failures (`nothrow`)
9. Dynamic C-strings
10. Manual array resizing
11. RAII principle with custom class
12. Common mistakes and how to fix them

### 2. [2_smart_pointers.cpp](2_smart_pointers.cpp)
**Focus:** Modern C++ smart pointers (C++11 and beyond)

**Key Concepts:**
- RAII (Resource Acquisition Is Initialization)
- `unique_ptr` - exclusive ownership
- `shared_ptr` - shared ownership with reference counting
- `weak_ptr` - non-owning references
- `make_unique` and `make_shared`
- Custom deleters
- Smart pointers with arrays
- Circular reference problem and solution
- Performance considerations
- Converting between smart pointer types

**Examples Covered (12):**
1. `unique_ptr` basics and creation
2. `unique_ptr` move semantics
3. `unique_ptr` with functions
4. `shared_ptr` basics and reference counting
5. `shared_ptr` copy vs move
6. `weak_ptr` basics
7. Circular reference problem with solution
8. Smart pointers with arrays
9. Custom deleters
10. Smart pointers in containers
11. Converting between smart pointer types
12. Performance analysis

## 🎯 Learning Objectives

After completing this topic, you should be able to:

1. **Understand Memory Layout**
   - Differentiate between stack and heap memory
   - Know when to use each type of allocation
   - Understand program memory segments

2. **Master Manual Memory Management**
   - Use `new` and `delete` correctly
   - Manage dynamic arrays with `new[]` and `delete[]`
   - Avoid memory leaks and dangling pointers
   - Implement 2D dynamic arrays

3. **Apply Smart Pointers**
   - Choose the right smart pointer type
   - Use `unique_ptr` for exclusive ownership
   - Use `shared_ptr` for shared ownership
   - Use `weak_ptr` to break circular references
   - Always use `make_unique` and `make_shared`

4. **Write Exception-Safe Code**
   - Implement RAII principle
   - Handle allocation failures
   - Prevent resource leaks in presence of exceptions

5. **Debug Memory Issues**
   - Detect memory leaks
   - Identify dangling pointers
   - Use memory debugging tools

## 📊 Memory Management Comparison

| Aspect               | Stack                       | Heap (new/delete)     | Heap (Smart Pointers)      |
| -------------------- | --------------------------- | --------------------- | -------------------------- |
| **Allocation Speed** | Very Fast (CPU instruction) | Slow (system call)    | Slow (system call)         |
| **Deallocation**     | Automatic (scope end)       | Manual (`delete`)     | Automatic (RAII)           |
| **Size**             | Limited (1-8 MB typical)    | Large (RAM limit)     | Large (RAM limit)          |
| **Lifetime**         | Function scope              | Until `delete` called | Until last owner destroyed |
| **Error Prone**      | Very Safe                   | Very Dangerous        | Safe                       |
| **Fragmentation**    | No                          | Yes                   | Yes                        |
| **Use Case**         | Local variables             | Dynamic size          | Dynamic size (safer)       |

## 🔧 Smart Pointer Comparison

| Feature            | unique_ptr | shared_ptr        | weak_ptr            |
| ------------------ | ---------- | ----------------- | ------------------- |
| **Ownership**      | Exclusive  | Shared            | Non-owning          |
| **Copyable**       | ❌ No       | ✅ Yes             | ✅ Yes               |
| **Movable**        | ✅ Yes      | ✅ Yes             | ✅ Yes               |
| **Overhead**       | Zero       | Small (ref count) | Small (ref count)   |
| **Thread-Safe**    | N/A        | Ref count only    | Ref count only      |
| **Use Count**      | N/A        | ✅ Yes             | ✅ Yes (weak count)  |
| **Default Choice** | ✅ Yes      | For sharing       | For breaking cycles |

## ⚡ Time & Space Complexity

### Memory Operations

| Operation             | Stack | Heap (new/delete) | Smart Pointer           |
| --------------------- | ----- | ----------------- | ----------------------- |
| **Allocate Single**   | O(1)  | O(1) to O(n)*     | O(1) to O(n)*           |
| **Deallocate Single** | O(1)  | O(1) to O(n)*     | O(1) to O(n)*           |
| **Allocate Array**    | O(1)  | O(n)              | O(n)                    |
| **Deallocate Array**  | O(1)  | O(n)              | O(n)                    |
| **unique_ptr Create** | -     | -                 | O(1)                    |
| **shared_ptr Create** | -     | -                 | O(1) + ref count        |
| **shared_ptr Copy**   | -     | -                 | O(1) (atomic increment) |
| **weak_ptr Lock**     | -     | -                 | O(1) (atomic check)     |

\* Complexity depends on heap allocator implementation

### Smart Pointer Overhead

| Type              | Size             | Additional Memory         |
| ----------------- | ---------------- | ------------------------- |
| `int*`            | 8 bytes (64-bit) | None                      |
| `unique_ptr<int>` | 8 bytes          | None                      |
| `shared_ptr<int>` | 16 bytes         | Control block (~24 bytes) |
| `weak_ptr<int>`   | 16 bytes         | Shares control block      |

## 🐛 Common Mistakes and Solutions

### Manual Memory Management

| Mistake                     | Problem            | Solution                           |
| --------------------------- | ------------------ | ---------------------------------- |
| **Forgot to delete**        | Memory leak        | Use smart pointers or RAII         |
| **Double delete**           | Undefined behavior | Set to nullptr after delete        |
| **delete vs delete[]**      | Undefined behavior | Match new[] with delete[]          |
| **Using after delete**      | Dangling pointer   | Set to nullptr, use smart ptrs     |
| **Leak on exception**       | Memory leak        | Use RAII/smart pointers            |
| **Shallow copy**            | Double deletion    | Implement deep copy or Rule of 3/5 |
| **Returning local address** | Dangling pointer   | Return by value or use heap        |
| **Lost pointer reference**  | Memory leak        | Store pointer before reassigning   |

### Smart Pointers

| Mistake                           | Problem             | Solution                                           |
| --------------------------------- | ------------------- | -------------------------------------------------- |
| **Using new instead of make_**    | Two allocations     | Use make_unique/make_shared                        |
| **Circular shared_ptr**           | Memory leak         | Use weak_ptr for back references                   |
| **shared_ptr from raw ptr twice** | Double deletion     | Never create multiple smart ptrs from same raw ptr |
| **Forgot to move unique_ptr**     | Compile error       | Use std::move()                                    |
| **Deleting from get()**           | Double deletion     | Never delete raw pointer from get()                |
| **Not checking weak_ptr**         | Null pointer access | Always check lock() result or expired()            |
| **Overusing shared_ptr**          | Performance hit     | Use unique_ptr when possible                       |

## 💡 Decision Tree: Which Memory Management?

```
Need dynamic memory?
├─ No
│  └─ Use stack allocation (automatic)
│
└─ Yes
   ├─ Known at compile time?
   │  └─ Yes → Use std::array
   │
   └─ No
      ├─ Need resizing?
      │  └─ Yes → Use std::vector
      │
      └─ No
         ├─ Single owner?
         │  └─ Yes → Use unique_ptr
         │
         └─ No
            ├─ Multiple owners?
            │  └─ Yes → Use shared_ptr
            │
            └─ Observer only?
               └─ Yes → Use weak_ptr
```

## 🎓 Study Tips

### For Beginners
1. **Start with manual memory** - Understand the pain points
2. **Practice with examples** - Run each example and modify
3. **Use memory debugging tools** - Valgrind, AddressSanitizer
4. **Master unique_ptr first** - Most common use case
5. **Understand RAII** - Foundation of modern C++

### For Competitive Programming
1. **Prefer stack/vector** - Usually sufficient
2. **Use unique_ptr** - When dynamic memory needed
3. **Avoid shared_ptr** - Overhead usually not needed
4. **Know when to use raw pointers** - Performance-critical sections
5. **Practice with STL containers** - vector, deque, list use smart pointers internally

### Memory Debugging Tools

**Linux/macOS:**
```bash
# Valgrind (memory leak detection)
valgrind --leak-check=full --show-leak-kinds=all ./program

# AddressSanitizer (compile-time flag)
g++ -std=c++17 -fsanitize=address -g program.cpp -o program
./program
```

**Any Platform:**
```bash
# Compile with debug symbols
g++ -std=c++17 -g -Wall -Wextra program.cpp -o program

# Use debugger (gdb/lldb)
gdb ./program
```

## 📝 Practice Problems

### Basic Level
1. Allocate array of size n, fill with squares, find sum, clean up
2. Create dynamic 2D matrix, initialize, transpose, deallocate
3. Implement dynamic string concatenation
4. Write function that resizes dynamic array
5. Fix given code with memory leaks

### Intermediate Level
6. Implement dynamic stack with resize capability
7. Create custom smart pointer class (simple RAII)
8. Build dynamic 2D array manager with RAII
9. Implement deep copy for class with dynamic members
10. Write reference-counted resource manager

### Advanced Level
11. Implement custom allocator for memory pool
12. Build cache with weak_ptr to avoid holding resources
13. Create observer pattern using weak_ptr
14. Implement intrusive reference counting
15. Build tree structure with parent weak_ptr references

### Competitive Programming
16. Dynamic programming with memoization (2D array)
17. Segment tree with dynamic memory
18. Sparse matrix with dynamic allocation
19. Graph adjacency list with smart pointers
20. LRU cache with shared_ptr and weak_ptr

## 🔗 Related Topics

- **Topic 6:** Arrays and Strings (static arrays comparison)
- **Topic 9:** Classes and Objects (Rule of Three/Five)
- **Topic 24:** Linear Data Structures (dynamic implementations)
- **STL Containers:** vector, deque, list (use dynamic memory internally)

## 📖 Additional Resources

### Documentation
- [cppreference: Smart Pointers](https://en.cppreference.com/w/cpp/memory)
- [cppreference: new operator](https://en.cppreference.com/w/cpp/language/new)
- [cppreference: delete operator](https://en.cppreference.com/w/cpp/language/delete)

### Articles
- "Understanding unique_ptr" - Herb Sutter
- "shared_ptr Internals" - Bartosz Milewski
- "RAII: Resource Acquisition Is Initialization"
- "C++ Core Guidelines: Resource Management"

### Books
- "Effective Modern C++" by Scott Meyers (Items 18-22)
- "C++ Primer" by Lippman (Chapter 12)
- "The C++ Programming Language" by Stroustrup (Chapter 13)

### Tools
- **Valgrind** - Memory leak detector (Linux/Mac)
- **AddressSanitizer** - Runtime error detector (GCC/Clang)
- **Dr. Memory** - Memory debugger (Windows)
- **Visual Studio** - Memory diagnostics

## ✅ Quick Reference

### Manual Memory Management

```cpp
// Single object
int* p = new int(42);
delete p;
p = nullptr;

// Array
int* arr = new int[10];
delete[] arr;
arr = nullptr;

// 2D array
int** matrix = new int*[rows];
for (int i = 0; i < rows; i++)
    matrix[i] = new int[cols];
// ... use matrix ...
for (int i = 0; i < rows; i++)
    delete[] matrix[i];
delete[] matrix;
```

### Smart Pointers

```cpp
// unique_ptr (exclusive ownership)
auto ptr = make_unique<int>(42);
auto arr = make_unique<int[]>(10);

// shared_ptr (shared ownership)
auto shared = make_shared<int>(42);
auto shared2 = shared;  // Share ownership

// weak_ptr (non-owning)
weak_ptr<int> weak = shared;
if (auto locked = weak.lock()) {
    // Use locked like shared_ptr
}

// Custom deleter
shared_ptr<FILE> file(fopen("file.txt", "r"), 
                      [](FILE* f) { fclose(f); });

// In container
vector<unique_ptr<Widget>> widgets;
widgets.push_back(make_unique<Widget>());
```

### When to Use What

```cpp
// Known size, compile time → std::array
std::array<int, 100> arr;

// Dynamic size, need resizing → std::vector
std::vector<int> vec;

// Dynamic, single owner → unique_ptr
auto ptr = make_unique<Widget>();

// Dynamic, multiple owners → shared_ptr
auto shared = make_shared<Resource>();

// Observer, break cycles → weak_ptr
weak_ptr<Node> parent = child->parent.lock();
```

## 🎯 Key Takeaways

1. **Prefer automatic memory** (stack, smart pointers) over manual (new/delete)
2. **Always match** new with delete, new[] with delete[]
3. **Set pointers to nullptr** after deletion
4. **Use smart pointers** for exception safety
5. **unique_ptr is default** - only use shared_ptr when needed
6. **weak_ptr breaks cycles** - essential for graph-like structures
7. **RAII is fundamental** - acquire in constructor, release in destructor
8. **make_unique/make_shared** preferred over new
9. **Never delete** raw pointer from get()
10. **Memory debugging tools** are essential

---

**Next Topic:** [Topic 9: Classes and Objects](../9_Classes_and_Objects/)  
**Previous Topic:** [Topic 7: Pointers and References](../7_Pointers_and_References/)
