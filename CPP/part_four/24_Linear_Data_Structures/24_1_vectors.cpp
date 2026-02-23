/*
================================================================================
                        TOPIC 24.1: VECTORS (DYNAMIC ARRAYS)
                    Part 4: Data Structures - Linear Data Structures
================================================================================

CONCEPT BREAKDOWN:
1. Vector basics and declaration
2. Memory management and time/space complexity
3. Vector operations (insert, delete, search, update)
4. Multi-dimensional vectors
5. Vector implementation details
6. Advanced usage patterns

KEY LEARNING POINTS:
- Vectors are dynamic arrays that grow/shrink at runtime
- Automatic memory management with RAII principles
- Cache-friendly due to contiguous memory allocation
- Time complexity analysis for different operations
- Understanding vector capacity vs size
- Iterator-based access patterns

================================================================================
                             SECTION 1: THEORY
================================================================================

1. WHAT IS A VECTOR?
   - A dynamic array that can grow or shrink at runtime
   - Part of STL (Standard Template Library)
   - Maintains contiguous memory like C-style arrays
   - Automatically manages memory (no manual delete needed)
   - Template class: std::vector<T>

2. VECTOR VS ARRAY
   Array:
   - Fixed size at compile time
   - Stack or static memory
   - Manual memory management if dynamic
   - arr[10] = 10 elements always

   Vector:
   - Size can change at runtime
   - Heap memory
   - Automatic memory management
   - Starts empty, grows as needed

3. MEMORY MANAGEMENT CONCEPTS
   - Size: Number of elements currently in the vector
   - Capacity: Total space allocated (>= size)
   - When push_back() is called and size == capacity:
     * Vector allocates new, larger memory block
     * Copies existing elements
     * Deallocates old memory
     * Adds new element

4. TIME COMPLEXITY ANALYSIS
   Operation              Time Complexity    Notes
   ─────────────────────────────────────────────────────────
   access(index)          O(1)               Direct access
   push_back()            O(1) amortized     Usually O(1), sometimes O(n) when
resize pop_back()             O(1)               Just remove from end
   insert(position)       O(n)               Need to shift elements
   erase(position)        O(n)               Need to shift elements
   find/search            O(n)               Linear search needed
   sort()                 O(n log n)         Uses std::sort internally

5. SPACE COMPLEXITY
   - O(n) where n is number of elements
   - Extra space due to capacity > size
   - Grows by ~1.5x or 2x when resizing

================================================================================
                         SECTION 2: CODE EXAMPLES
================================================================================

*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// ======================= EXAMPLE 1: BASIC VECTOR CREATION
// =======================
void example_1_vector_creation() {
  cout << "\n===== EXAMPLE 1: Vector Creation =====" << endl;

  // Empty vector
  vector<int> vec1;
  cout << "Empty vector - size: " << vec1.size()
       << ", capacity: " << vec1.capacity() << endl;

  // Vector with initial size
  vector<int> vec2(5); // 5 elements, all initialized to 0
  cout << "Vector(5) - size: " << vec2.size()
       << ", capacity: " << vec2.capacity() << endl;

  // Vector with initial size and value
  vector<int> vec3(5, 10); // 5 elements, all = 10
  cout << "Vector(5, 10) - size: " << vec3.size() << ", content: ";
  for (int x : vec3)
    cout << x << " ";
  cout << endl;

  // Vector initialized with list
  vector<int> vec4 = {1, 2, 3, 4, 5};
  cout << "Vector = {1,2,3,4,5} - size: " << vec4.size()
       << ", capacity: " << vec4.capacity() << endl;

  // Vector from another vector
  vector<int> vec5 = vec4;
  cout << "Copy of vec4 - size: " << vec5.size() << ", content: ";
  for (int x : vec5)
    cout << x << " ";
  cout << endl;
}

// ======================= EXAMPLE 2: PUSH_BACK AND CAPACITY
// =======================
void example_2_push_back_capacity() {
  cout << "\n===== EXAMPLE 2: Push_back and Capacity =====" << endl;

  vector<int> vec;

  cout << "Initially - size: " << vec.size() << ", capacity: " << vec.capacity()
       << endl;

  // Push elements and observe capacity growth
  for (int i = 1; i <= 20; i++) {
    vec.push_back(i);

    // Print when capacity changes
    if (i == 1 || i == 2 || i == 4 || i == 8 || i == 16) {
      cout << "After push_back(" << i << ") - size: " << vec.size()
           << ", capacity: " << vec.capacity() << endl;
    }
  }

  cout << "Final - size: " << vec.size() << ", capacity: " << vec.capacity()
       << endl;
  cout << "Wasted space: " << (vec.capacity() - vec.size()) << " elements"
       << endl;
}

// ======================= EXAMPLE 3: ELEMENT ACCESS =======================
void example_3_element_access() {
  cout << "\n===== EXAMPLE 3: Element Access =====" << endl;

  vector<int> vec = {10, 20, 30, 40, 50};

  // Using operator[]
  cout << "Using operator[]: " << endl;
  for (int i = 0; i < vec.size(); i++) {
    cout << "vec[" << i << "] = " << vec[i] << endl;
  }

  // Using .at() with bounds checking
  cout << "\nUsing .at() with bounds checking:" << endl;
  try {
    cout << "vec.at(2) = " << vec.at(2) << endl;
    // cout << "vec.at(10) = " << vec.at(10) << endl;  // Would throw exception
  } catch (std::out_of_range &e) {
    cout << "Exception caught: " << e.what() << endl;
  }

  // Using iterators
  cout << "\nUsing iterators:" << endl;
  cout << "Forward: ";
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;

  // Using range-based for loop (C++11)
  cout << "Range-based for: ";
  for (int val : vec) {
    cout << val << " ";
  }
  cout << endl;
}

// ======================= EXAMPLE 4: INSERT AND ERASE =======================
void example_4_insert_erase() {
  cout << "\n===== EXAMPLE 4: Insert and Erase =====" << endl;

  vector<int> vec = {1, 2, 3, 4, 5};
  cout << "Original: ";
  for (int x : vec)
    cout << x << " ";
  cout << endl;

  // Insert at position
  vec.insert(vec.begin() + 2, 99); // Insert 99 at index 2
  cout << "After insert(index 2, 99): ";
  for (int x : vec)
    cout << x << " ";
  cout << endl;

  // Insert multiple elements
  vec.insert(vec.begin() + 4, 3, 88); // Insert 3 copies of 88
  cout << "After insert(index 4, 3 x 88): ";
  for (int x : vec)
    cout << x << " ";
  cout << endl;

  // Erase single element
  vec.erase(vec.begin() + 2);
  cout << "After erase(index 2): ";
  for (int x : vec)
    cout << x << " ";
  cout << endl;

  // Erase range
  vec.erase(vec.begin() + 4, vec.begin() + 7);
  cout << "After erase(index 4 to 6): ";
  for (int x : vec)
    cout << x << " ";
  cout << endl;
}

// ======================= EXAMPLE 5: POP_BACK AND CLEAR =======================
void example_5_pop_clear() {
  cout << "\n===== EXAMPLE 5: Pop_back and Clear =====" << endl;

  vector<int> vec = {10, 20, 30, 40, 50};

  cout << "Original: ";
  for (int x : vec)
    cout << x << " ";
  cout << " (size: " << vec.size() << ")" << endl;

  // Pop back
  vec.pop_back();
  cout << "After pop_back(): ";
  for (int x : vec)
    cout << x << " ";
  cout << " (size: " << vec.size() << ")" << endl;

  // Pop multiple by creating a loop
  vec.pop_back();
  vec.pop_back();
  cout << "After 2 more pop_back(): ";
  for (int x : vec)
    cout << x << " ";
  cout << " (size: " << vec.size() << ")" << endl;

  // Clear everything
  cout << "\nBefore clear - size: " << vec.size()
       << ", capacity: " << vec.capacity() << endl;
  vec.clear();
  cout << "After clear() - size: " << vec.size()
       << ", capacity: " << vec.capacity() << endl;

  // Note: capacity remains same, only size becomes 0
}

// ======================= EXAMPLE 6: SEARCHING AND FINDING
// =======================
void example_6_search_find() {
  cout << "\n===== EXAMPLE 6: Search and Find =====" << endl;

  vector<int> vec = {10, 20, 30, 40, 50, 30, 60};

  cout << "Vector: ";
  for (int x : vec)
    cout << x << " ";
  cout << endl;

  // Using std::find
  int search_val = 30;
  auto it = std::find(vec.begin(), vec.end(), search_val);

  if (it != vec.end()) {
    int index = std::distance(vec.begin(), it);
    cout << "Found " << search_val << " at index: " << index << endl;
  } else {
    cout << search_val << " not found" << endl;
  }

  // Find last occurrence manually
  int last_index = -1;
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i] == 30) {
      last_index = i;
    }
  }
  cout << "Last occurrence of 30 at index: " << last_index << endl;

  // Using std::count
  int count = std::count(vec.begin(), vec.end(), 30);
  cout << "Number of 30's in vector: " << count << endl;
}

// ======================= EXAMPLE 7: SORTING AND ALGORITHMS
// =======================
void example_7_sorting_algorithms() {
  cout << "\n===== EXAMPLE 7: Sorting and Algorithms =====" << endl;

  vector<int> vec = {50, 30, 70, 20, 10, 60, 40};

  cout << "Original: ";
  for (int x : vec)
    cout << x << " ";
  cout << endl;

  // Sorting
  std::sort(vec.begin(), vec.end());
  cout << "After sort(): ";
  for (int x : vec)
    cout << x << " ";
  cout << endl;

  // Reverse sort
  std::sort(vec.begin(), vec.end(), std::greater<int>());
  cout << "After sort(greater): ";
  for (int x : vec)
    cout << x << " ";
  cout << endl;

  // Reverse
  std::reverse(vec.begin(), vec.end());
  cout << "After reverse(): ";
  for (int x : vec)
    cout << x << " ";
  cout << endl;

  // Sum using accumulate
  int sum = std::accumulate(vec.begin(), vec.end(), 0);
  cout << "Sum of all elements: " << sum << endl;

  // Min and max
  int min_val = *std::min_element(vec.begin(), vec.end());
  int max_val = *std::max_element(vec.begin(), vec.end());
  cout << "Min: " << min_val << ", Max: " << max_val << endl;
}

// ======================= EXAMPLE 8: RESERVE AND SHRINK_TO_FIT
// =======================
void example_8_reserve_shrink() {
  cout << "\n===== EXAMPLE 8: Reserve and Shrink_to_fit =====" << endl;

  // Without reserve
  cout << "Without reserve:" << endl;
  vector<int> vec1;
  cout << "Before loop - capacity: " << vec1.capacity() << endl;
  for (int i = 0; i < 100; i++) {
    vec1.push_back(i);
  }
  cout << "After adding 100 elements - capacity: " << vec1.capacity() << endl;

  // With reserve
  cout << "\nWith reserve:" << endl;
  vector<int> vec2;
  vec2.reserve(100); // Allocate space for 100 elements upfront
  cout << "After reserve(100) - capacity: " << vec2.capacity() << endl;
  for (int i = 0; i < 100; i++) {
    vec2.push_back(i);
  }
  cout << "After adding 100 elements - capacity: " << vec2.capacity() << endl;

  // Shrink to fit
  cout << "\nShrink to fit:" << endl;
  vector<int> vec3 = {1, 2, 3, 4, 5};
  vec3.reserve(1000);
  cout << "After reserve(1000) - size: " << vec3.size()
       << ", capacity: " << vec3.capacity() << endl;
  vec3.shrink_to_fit();
  cout << "After shrink_to_fit() - size: " << vec3.size()
       << ", capacity: " << vec3.capacity() << endl;
}

// ======================= EXAMPLE 9: 2D VECTORS =======================
void example_9_2d_vectors() {
  cout << "\n===== EXAMPLE 9: 2D Vectors (Matrices) =====" << endl;

  // Create 3x4 matrix initialized with 0
  vector<vector<int>> matrix(3, vector<int>(4, 0));

  cout << "Created 3x4 matrix:" << endl;
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }

  // Fill with values
  int value = 1;
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      matrix[i][j] = value++;
    }
  }

  cout << "\nAfter filling with values:" << endl;
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }

  // Access element
  cout << "\nElement at [1][2]: " << matrix[1][2] << endl;
  cout << "Matrix dimensions: " << matrix.size() << "x" << matrix[0].size()
       << endl;
}

// ======================= EXAMPLE 10: VECTOR OF STRUCTURES
// =======================
struct Student {
  int id;
  std::string name;
  float gpa;
};

void example_10_vector_of_struct() {
  cout << "\n===== EXAMPLE 10: Vector of Structures =====" << endl;

  vector<Student> students;

  // Add students
  students.push_back({101, "Alice", 3.8});
  students.push_back({102, "Bob", 3.5});
  students.push_back({103, "Charlie", 3.9});

  cout << "Students in vector:" << endl;
  for (const auto &student : students) {
    cout << "ID: " << student.id << ", Name: " << student.name
         << ", GPA: " << student.gpa << endl;
  }

  // Find student by ID
  int search_id = 102;
  for (const auto &student : students) {
    if (student.id == search_id) {
      cout << "\nFound student: " << student.name << " with GPA " << student.gpa
           << endl;
      break;
    }
  }
}

// ======================= EXAMPLE 11: VECTOR COMPARISON AND OPERATIONS
// =======================
void example_11_vector_operations() {
  cout << "\n===== EXAMPLE 11: Vector Comparison and Operations =====" << endl;

  vector<int> vec1 = {1, 2, 3, 4, 5};
  vector<int> vec2 = {1, 2, 3, 4, 5};
  vector<int> vec3 = {1, 2, 3};

  // Comparison
  cout << "vec1 == vec2: " << (vec1 == vec2 ? "true" : "false") << endl;
  cout << "vec1 == vec3: " << (vec1 == vec3 ? "true" : "false") << endl;
  cout << "vec1 > vec3: " << (vec1 > vec3 ? "true" : "false") << endl;

  // Assignment
  cout << "\nvec3 before assignment - size: " << vec3.size() << endl;
  vec3 = vec1;
  cout << "vec3 after vec3 = vec1 - size: " << vec3.size() << endl;
  cout << "Content: ";
  for (int x : vec3)
    cout << x << " ";
  cout << endl;

  // Swap
  vector<int> vec4 = {10, 20, 30};
  cout << "\nBefore swap - vec1: ";
  for (int x : vec1)
    cout << x << " ";
  cout << ", vec4: ";
  for (int x : vec4)
    cout << x << " ";
  cout << endl;

  vec1.swap(vec4);
  cout << "After swap - vec1: ";
  for (int x : vec1)
    cout << x << " ";
  cout << ", vec4: ";
  for (int x : vec4)
    cout << x << " ";
  cout << endl;
}

// ======================= EXAMPLE 12: COMMON MISTAKES AND PITFALLS
// =======================
void example_12_common_mistakes() {
  cout << "\n===== EXAMPLE 12: Common Mistakes =====" << endl;

  cout << "MISTAKE 1: Accessing out of bounds (UNDEFINED BEHAVIOR)" << endl;
  vector<int> vec = {1, 2, 3};
  cout << "Vector size: " << vec.size() << endl;
  cout << "Using operator[] (no bounds check): vec[5] = ";
  // cout << vec[5] << endl;  // DANGEROUS - undefined behavior
  cout << "(skipped - would crash)" << endl;

  cout << "\nSAFE WAY - Using at() with try-catch:" << endl;
  try {
    cout << vec.at(5) << endl;
  } catch (std::out_of_range &e) {
    cout << "Caught exception: Index out of range" << endl;
  }

  cout << "\nMISTAKE 2: Iterator invalidation" << endl;
  vector<int> vec2 = {1, 2, 3, 4, 5};
  auto it = vec2.begin();
  cout << "Iterator points to: " << *it << endl;

  vec2.insert(vec2.begin(), 99); // This invalidates iterator!
  // cout << *it << endl;  // DANGEROUS - iterator invalidated
  cout << "(iterator invalidated after insert, cannot use old iterator)"
       << endl;

  cout << "\nMISTAKE 3: Using vector on empty vector" << endl;
  vector<int> empty_vec;
  cout << "Empty vector size: " << empty_vec.size() << endl;
  cout << "Trying front() on empty vector: ";
  if (!empty_vec.empty()) {
    cout << empty_vec.front() << endl;
  } else {
    cout << "(skipped - vector is empty)" << endl;
  }

  cout << "\nCORRECT WAY: Always check before access" << endl;
  if (!empty_vec.empty()) {
    cout << "Front: " << empty_vec.front() << endl;
  } else {
    cout << "Vector is empty, cannot access elements" << endl;
  }
}

/*
================================================================================
                            KEY CONCEPTS SUMMARY
================================================================================

VECTOR CHARACTERISTICS:
✓ Dynamic size - grows/shrinks at runtime
✓ Contiguous memory - like arrays, fast random access
✓ Automatic memory - no manual delete needed
✓ RAII pattern - resources freed automatically
✓ Cache friendly - elements stored contiguously

VECTOR OPERATIONS COMPLEXITY:
┌─────────────────────┬────────────┬─────────────────────┐
│ Operation           │ Complexity │ Notes               │
├─────────────────────┼────────────┼─────────────────────┤
│ push_back()         │ O(1) avg   │ May reallocate      │
│ pop_back()          │ O(1)       │ Fast                │
│ insert()            │ O(n)       │ Shifts elements     │
│ erase()             │ O(n)       │ Shifts elements     │
│ access [i]          │ O(1)       │ Direct access       │
│ find()              │ O(n)       │ Linear search       │
│ sort()              │ O(n log n) │ std::sort used      │
└─────────────────────┴────────────┴─────────────────────┘

WHEN TO USE VECTORS:
✓ Need dynamic array
✓ Need random access with O(1)
✓ Frequently add/remove from end
✓ Working with STL algorithms
✗ Frequent insertions in middle (use list instead)
✗ Need specific memory layout (use arrays)
✗ Real-time systems with allocation constraints

SIZE VS CAPACITY:
- size(): Number of elements currently stored
- capacity(): Total space allocated (always >= size)
- resize(): Changes size (may allocate)
- reserve(): Pre-allocates capacity (doesn't change size)

ITERATOR RULES:
- push_back() may invalidate all iterators
- insert()/erase() invalidate iterators after position
- Check if iterator is valid before using
- Prefer range-based for loops when possible

VECTOR INITIALIZATION:
vector<T> v;              // empty
vector<T> v(n);           // n elements, default initialized
vector<T> v(n, val);      // n elements, all = val
vector<T> v = {1,2,3};    // initialized with values
vector<T> v2 = v1;        // copy constructor

================================================================================
*/

/*
================================================================================
                        SECTION 3: PRACTICE EXERCISES
================================================================================

1. BASIC OPERATIONS:
   Write a program that:
   - Creates a vector and adds 10 numbers (1 to 10)
   - Prints size and capacity after each addition
   - Removes last 3 elements using pop_back()
   - Prints final vector

2. SEARCHING:
   Write a function that:
   - Takes a vector and a value as input
   - Returns the count of that value
   - Returns -1 if value not found
   - Print all indices where value occurs

3. 2D MATRIX OPERATIONS:
   Write a program that:
   - Creates a 3x3 matrix with 1-9
   - Calculates sum of main diagonal
   - Calculates sum of anti-diagonal
   - Finds maximum element and its position

4. FILTERING:
   Write a program that:
   - Creates vector with 20 random numbers (1-100)
   - Creates two new vectors: even_nums and odd_nums
   - Separates numbers into appropriate vectors
   - Prints both vectors

5. SORTING AND SEARCHING:
   Write a program that:
   - Creates vector with 10 numbers
   - Sorts in ascending order
   - Implements binary search for target value
   - Returns index if found, -1 if not

6. MEMORY ANALYSIS:
   Write a program that:
   - Creates vectors with different initial capacities
   - Measures time to add 1000 elements
   - Without reserve(): observe reallocations
   - With reserve(1000): observe direct allocation
   - Compare performance

7. VECTOR OF PAIRS:
   Write a program that:
   - Creates vector<pair<int, string>> for (ID, Name)
   - Adds 5 pairs
   - Searches by ID
   - Searches by Name
   - Prints all in sorted order by ID

8. TRANSPOSE MATRIX:
   Write a program that:
   - Creates a 3x4 2D vector
   - Computes transpose (4x3)
   - Prints original and transposed

9. REMOVE DUPLICATES:
   Write a function that:
   - Takes a vector with duplicates
   - Returns new vector without duplicates
   - Preserves original order
   - Uses STL algorithms

10. VECTOR STATISTICS:
    Write a program that:
    - Creates vector with N numbers
    - Calculates: min, max, average, median
    - Finds all numbers above average
    - Finds mode (most frequent number)

================================================================================
*/

/*
================================================================================
                         COMMON MISTAKES TO AVOID
================================================================================

MISTAKE 1: Out-of-Bounds Access
❌ WRONG:
   vector<int> v = {1, 2, 3};
   cout << v[5];  // Undefined behavior!

✓ RIGHT:
   vector<int> v = {1, 2, 3};
   if (v.size() > 5) cout << v[5];
   // Or use .at(5) with try-catch

────────────────────────────────────────────────────────────────────

MISTAKE 2: Using Vector After Clear
❌ WRONG:
   vector<int> v = {1, 2, 3};
   v.clear();
   cout << v.front();  // Crash! Vector is empty

✓ RIGHT:
   vector<int> v = {1, 2, 3};
   v.clear();
   if (!v.empty()) cout << v.front();

────────────────────────────────────────────────────────────────────

MISTAKE 3: Iterator Invalidation
❌ WRONG:
   vector<int> v = {1, 2, 3};
   auto it = v.begin();
   v.insert(v.begin(), 99);  // Invalidates iterator
   cout << *it;  // Undefined behavior!

✓ RIGHT:
   vector<int> v = {1, 2, 3};
   v.insert(v.begin(), 99);
   auto it = v.begin();
   cout << *it;  // Safe now

────────────────────────────────────────────────────────────────────

MISTAKE 4: Inefficient Insertions
❌ WRONG:
   vector<int> v;
   for (int i = 0; i < 1000; i++) {
       v.insert(v.begin(), i);  // O(n²) total!
   }

✓ RIGHT:
   vector<int> v;
   for (int i = 0; i < 1000; i++) {
       v.push_back(i);  // O(1) amortized
   }
   std::reverse(v.begin(), v.end());

────────────────────────────────────────────────────────────────────

MISTAKE 5: Memory Waste with Reserve
❌ WRONG:
   vector<int> v;
   v.reserve(1000000);  // 4MB unused!
   v.push_back(1);

✓ RIGHT:
   vector<int> v;
   v.reserve(1000);  // Reserve only what you need
   for (int i = 0; i < 1000; i++) {
       v.push_back(i);
   }

════════════════════════════════════════════════════════════════════════

================================================================================
*/

int main() {
  cout << "╔════════════════════════════════════════════════════════════╗"
       << endl;
  cout << "║           COMPREHENSIVE VECTOR LEARNING GUIDE              ║"
       << endl;
  cout << "║          Part 4, Topic 24.1: Linear Data Structures       ║"
       << endl;
  cout << "╚════════════════════════════════════════════════════════════╝"
       << endl;

  // Run all examples
  example_1_vector_creation();
  example_2_push_back_capacity();
  example_3_element_access();
  example_4_insert_erase();
  example_5_pop_clear();
  example_6_search_find();
  example_7_sorting_algorithms();
  example_8_reserve_shrink();
  example_9_2d_vectors();
  example_10_vector_of_struct();
  example_11_vector_operations();
  example_12_common_mistakes();

  cout << "\n╔════════════════════════════════════════════════════════════╗"
       << endl;
  cout << "║                    EXAMPLES COMPLETED                      ║"
       << endl;
  cout << "║          Now try the practice exercises above!             ║"
       << endl;
  cout << "╚════════════════════════════════════════════════════════════╝"
       << endl;

  return 0;
}

/*
================================================================================
                        ADVANCED TOPICS & EXTENSIONS
================================================================================

1. CUSTOM ALLOCATORS:
   - You can provide custom memory allocation strategies
   - Example: vector<int, CustomAllocator> v;
   - Useful for embedded systems or special memory requirements

2. MOVE SEMANTICS:
   - vector<int> v1 = {1, 2, 3};
   - vector<int> v2 = std::move(v1);  // v1 becomes empty
   - Very efficient for large vectors

3. EMPLACE_BACK vs PUSH_BACK:
   - push_back(): copies/moves object into vector
   - emplace_back(): constructs object in-place
   - emplace_back() can be more efficient

   struct Point { int x, y; };
   vector<Point> v;
   v.emplace_back(1, 2);  // Constructs in-place
   v.push_back({1, 2});   // Creates temp, then moves

4. VECTOR PERFORMANCE TIPS:
   - Use reserve() if you know the size beforehand
   - Avoid frequent reallocations in loops
   - Use emplace_back() instead of push_back() for complex types
   - Prefer swap() for efficient exchanges
   - Use move semantics for large data transfers

5. ITERATORS AND ALGORITHMS:
   - Most STL algorithms work with vectors
   - std::sort, std::find, std::transform, etc.
   - Using algorithms is usually more efficient than manual loops

6. MEMORY LAYOUT AND CACHE:
   - Vectors store contiguous memory
   - Good cache locality = better performance
   - This is why vectors are faster than linked lists for iteration

================================================================================
                        REFERENCE DOCUMENTATION
================================================================================

VECTOR MEMBER FUNCTIONS:

Capacity/Size:
  size()              - return number of elements
  capacity()          - return allocated capacity
  empty()             - check if empty
  resize(n, val)      - change size
  reserve(n)          - reserve space
  shrink_to_fit()     - reduce capacity to size

Element Access:
  operator[]          - fast access (no bounds check)
  at()                - safe access (bounds check)
  front()             - first element
  back()              - last element
  data()              - pointer to data

Modification:
  push_back()         - add to end
  pop_back()          - remove from end
  insert()            - insert at position
  erase()             - remove at position
  clear()             - remove all elements
  swap()              - swap with another vector

Iterators:
  begin()             - iterator to start
  end()               - iterator to end
  rbegin()            - reverse iterator to end
  rend()              - reverse iterator to start

Comparison:
  operator==          - equality
  operator<           - less than
  operator>           - greater than
  (and more...)

================================================================================
                           LEARNING CHECKLIST
================================================================================

After completing this section, you should understand:

☐ Vector vs Array differences and when to use each
☐ Dynamic memory allocation and deallocation
☐ Size vs Capacity concepts
☐ Time complexity of vector operations
☐ How to create and initialize vectors
☐ Element access methods ([], .at(), iterators)
☐ How to add/remove elements efficiently
☐ Searching and sorting vectors
☐ 2D and multi-dimensional vectors
☐ Vector of custom types/structures
☐ Common mistakes and how to avoid them
☐ Iterator invalidation rules
☐ Memory management best practices
☐ Performance optimization techniques
☐ STL algorithms with vectors

Next Topics:
- 24.2: Linked Lists (Singly, Doubly, Circular)
- 24.3: Stacks (LIFO principle)
- 24.4: Queues (FIFO principle)

================================================================================
                             END OF SECTION
================================================================================
*/
