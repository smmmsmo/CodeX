# Arrays and Strings - Comprehensive Learning Guide

## Overview
This folder contains comprehensive learning materials for **Arrays and Strings** (Topic #6 from the C++ DSA Learning Roadmap). These files cover everything from fundamentals to advanced competitive programming techniques.

## 📚 File Structure

### 1️⃣ **1_single_dim_arrays.cpp** - Single-Dimensional Arrays
**Fundamentals & Core Techniques**
- Array declaration, initialization, and access
- Traversal patterns and iteration methods
- Common operations (search, find min/max, sum, average)
- Linear search and Binary search
- Array reversal and rotation algorithms
- Prefix sum arrays for range queries
- Two-pointer technique
- Kadane's algorithm (Maximum subarray sum)
- Sliding window basics
- Passing arrays to functions

**Key Algorithms:**
- Time Complexity: O(1) access, O(n) traversal, O(log n) binary search
- Kadane's Algorithm: O(n) for max subarray sum
- Two Pointers: O(n) for sorted array problems
- Prefix Sum: O(n) preprocessing, O(1) per query

---

### 2️⃣ **2_multi_dim_arrays.cpp** - Multi-Dimensional Arrays
**Matrices & Grid Problems**
- 2D array declaration and initialization
- Matrix traversal patterns (row-wise, column-wise, diagonal, zigzag)
- Spiral matrix traversal
- Matrix operations (transpose, rotation, addition, multiplication)
- Searching in row-column sorted matrices
- Boundary and wave print patterns
- Dynamic 2D arrays using vectors
- 3D arrays and higher dimensions
- Jagged arrays

**Key Algorithms:**
- Spiral Traversal: O(rows × cols) using 4 pointers
- Matrix Rotation: O(n²) with transpose + reverse
- Search in Sorted Matrix: O(rows + cols) from top-right
- Matrix Multiplication: O(r₁ × c₁ × c₂)

---

### 3️⃣ **3_c_style_strings.cpp** - C-Style Strings (char arrays)
**Character Arrays & String Fundamentals**
- Null-terminated character arrays
- String declaration and initialization
- String input/output (cin, getline)
- String library functions (strlen, strcpy, strcat, strcmp)
- String length calculation
- String reversal and palindrome checking
- String copy and concatenation
- String comparison
- Character classification (isalpha, isdigit, etc.)
- Case conversion (uppercase/lowercase)
- Word counting

**Key Concepts:**
- Null terminator '\0' is essential
- strlen() vs sizeof()
- Manual implementation of string functions
- Understanding low-level string manipulation

---

### 4️⃣ **4_std_string.cpp** - Modern C++ Strings
**std::string Class & Operations**
- String declaration and initialization
- String concatenation and operators
- Character access ([], at(), front(), back())
- Size and capacity management
- String modifiers (append, insert, erase, replace, substr)
- String searching (find, rfind, find_first_of, etc.)
- String comparison (operators and compare())
- String conversion (to_string, stoi, stod, etc.)
- String streams (stringstream for parsing)
- Using STL algorithms with strings
- Common string patterns

**Advantages over C-strings:**
- Automatic memory management
- Dynamic sizing
- Rich functionality
- Safer operations
- Operator overloading

---

### 5️⃣ **5_advanced_array_techniques.cpp** - Competitive Programming Arrays
**Advanced Algorithms & Techniques**
- Two-pointer variations (opposite direction, same direction)
- Sliding window (fixed and variable size)
- Prefix sum and difference arrays
- Hashing with arrays for O(1) lookups
- Monotonic stack/queue applications
- Dutch National Flag (3-way partitioning)
- Moore's Voting Algorithm (majority element)
- Trapping Rainwater problem
- Stock Buy-Sell problems
- Subarray sum problems with hashing
- Longest consecutive sequence
- Array manipulation tricks

**Essential Patterns:**
- Two Pointers: O(n) for sorted arrays, pairs, partitioning
- Sliding Window: O(n) for subarray problems
- Prefix Sum: O(1) queries after O(n) preprocessing
- Difference Array: O(1) per range update
- Moore's Voting: O(n) time, O(1) space for majority

---

### 6️⃣ **6_advanced_string_algorithms.cpp** - Competitive Programming Strings
**Pattern Matching & Advanced Algorithms**
- Anagram detection and grouping
- Palindrome algorithms (expand around center, DP, Manacher's)
- Pattern matching (Naive, KMP, Rabin-Karp)
- Longest Common Subsequence (LCS)
- Edit Distance (Levenshtein Distance)
- String hashing and rolling hash
- String rotation and permutation
- Minimum window substring
- Longest substring without repeating characters
- Valid parentheses checking
- First non-repeating character

**Advanced Algorithms:**
- KMP Pattern Matching: O(n + m) with LPS array
- Rabin-Karp: O(n + m) average with rolling hash
- Edit Distance: O(m × n) DP
- LCS: O(m × n) DP
- Sliding Window: O(n) for substring problems
- Manacher's Algorithm: O(n) for longest palindrome

---

## 🎯 Learning Path

### Beginner Level (Start Here)
1. **1_single_dim_arrays.cpp** - Master basic arrays first
2. **3_c_style_strings.cpp** - Understand strings at low level
3. **4_std_string.cpp** - Learn modern C++ strings

### Intermediate Level
4. **2_multi_dim_arrays.cpp** - Work with matrices and grids
5. First half of **5_advanced_array_techniques.cpp** - Two pointers, sliding window

### Advanced Level (Competition Ready)
6. Rest of **5_advanced_array_techniques.cpp** - All advanced patterns
7. **6_advanced_string_algorithms.cpp** - Pattern matching, DP

---

## 📊 Time Complexity Quick Reference

### Array Operations
| Operation          | Time Complexity | Space |
| ------------------ | --------------- | ----- |
| Access             | O(1)            | O(1)  |
| Search (unsorted)  | O(n)            | O(1)  |
| Binary Search      | O(log n)        | O(1)  |
| Insert/Delete      | O(n)            | O(1)  |
| Kadane's Algorithm | O(n)            | O(1)  |
| Two Pointers       | O(n)            | O(1)  |
| Sliding Window     | O(n)            | O(1)  |
| Prefix Sum Query   | O(1)            | O(n)  |

### String Algorithms
| Algorithm         | Time Complexity | Space    |
| ----------------- | --------------- | -------- |
| KMP Pattern Match | O(n + m)        | O(m)     |
| Rabin-Karp        | O(n + m) avg    | O(1)     |
| Edit Distance     | O(m × n)        | O(m × n) |
| LCS               | O(m × n)        | O(m × n) |
| Anagram Check     | O(n)            | O(1)     |
| Palindrome Check  | O(n)            | O(1)     |

---

## 🏆 Competitive Programming Essentials

### Must-Know Array Techniques
1. ✅ Two Pointers (opposite & same direction)
2. ✅ Sliding Window (fixed & variable size)
3. ✅ Prefix Sum & Difference Array
4. ✅ Kadane's Algorithm
5. ✅ Dutch National Flag
6. ✅ Moore's Voting Algorithm
7. ✅ Binary Search variations
8. ✅ Hashing for O(1) lookups

### Must-Know String Techniques
1. ✅ KMP Pattern Matching
2. ✅ Rabin-Karp (Rolling Hash)
3. ✅ Sliding Window on Strings
4. ✅ Anagram Detection
5. ✅ Palindrome Algorithms
6. ✅ Edit Distance DP
7. ✅ LCS/LIS DP
8. ✅ String Hashing

---

## 💡 Common Problem Patterns

### Arrays
- **"Find pair with sum = k"** → Two Pointers or Hashing
- **"Maximum subarray sum"** → Kadane's Algorithm
- **"Longest subarray with condition"** → Sliding Window
- **"Range sum queries"** → Prefix Sum
- **"Sort 0,1,2"** → Dutch National Flag
- **"Majority element"** → Moore's Voting
- **"Trapped water"** → Two Pointers with max tracking

### Strings
- **"Find pattern in text"** → KMP or Rabin-Karp
- **"Anagram detection"** → Frequency map or sorting
- **"Longest palindrome"** → Expand around center or Manacher's
- **"Edit distance"** → DP
- **"Substring with all chars of pattern"** → Sliding Window
- **"Valid parentheses"** → Stack
- **"String rotation"** → Concatenate and search
- **"Group anagrams"** → Hash map with sorted key

---

## 🔧 Compilation & Execution

Each file can be compiled and run independently:

```bash
# Compile
g++ -std=c++17 -o program 1_single_dim_arrays.cpp

# Run
./program
```

Or compile all at once:
```bash
g++ -std=c++17 -o arrays_demo 1_single_dim_arrays.cpp
g++ -std=c++17 -o matrices_demo 2_multi_dim_arrays.cpp
g++ -std=c++17 -o cstrings_demo 3_c_style_strings.cpp
g++ -std=c++17 -o strings_demo 4_std_string.cpp
g++ -std=c++17 -o advanced_arrays_demo 5_advanced_array_techniques.cpp
g++ -std=c++17 -o advanced_strings_demo 6_advanced_string_algorithms.cpp
```

---

## 📝 Practice Resources

### Online Judges
- **LeetCode**: Arrays & Strings sections
- **Codeforces**: Div 2 A/B problems
- **HackerRank**: Arrays and Strings tracks
- **GeeksforGeeks**: Practice problems with solutions

### Recommended Problems
**Arrays:**
- Two Sum, 3Sum, 4Sum
- Container With Most Water
- Trapping Rain Water
- Maximum Subarray (Kadane's)
- Best Time to Buy and Sell Stock (all variations)
- Longest Consecutive Sequence
- First Missing Positive
- Merge Intervals

**Strings:**
- Longest Substring Without Repeating Characters
- Longest Palindromic Substring
- Valid Parentheses
- Group Anagrams
- Minimum Window Substring
- Implement strStr() (KMP)
- Edit Distance
- Regular Expression Matching

---

## 🎓 Study Tips

1. **Master the Basics First**: Start with files 1-4 before attempting advanced topics
2. **Code Along**: Don't just read - type out every example
3. **Understand, Don't Memorize**: Focus on why algorithms work
4. **Practice Daily**: Solve at least 1-2 problems daily
5. **Recognize Patterns**: Learn to identify which technique to use
6. **Time Yourself**: Practice under contest conditions
7. **Review Mistakes**: Understand why solutions failed
8. **Optimize**: Always think about time and space complexity
9. **Test Edge Cases**: Empty arrays, single elements, duplicates
10. **Use Debugger**: Step through complex algorithms

---

## ⚠️ Common Pitfalls

### Arrays
- ❌ Array index out of bounds
- ❌ Not initializing array elements
- ❌ Integer overflow in sum calculations
- ❌ Off-by-one errors in loops
- ❌ Forgetting to pass size to functions
- ❌ Assuming array is sorted when it's not

### Strings
- ❌ Forgetting null terminator in C-strings
- ❌ Not checking for string::npos in find()
- ❌ Off-by-one in substr(pos, len)
- ❌ Not handling empty strings
- ❌ Comparing strings with == on char* (in C)
- ❌ Modifying string while iterating

---

## 📈 Complexity Analysis Cheat Sheet

### When to Use What?

**O(1) - Constant Time**
- Array element access
- Hash map lookup
- Prefix sum query (after preprocessing)

**O(log n) - Logarithmic**
- Binary search
- Balanced BST operations
- Divide and conquer (each step)

**O(n) - Linear**
- Single array traversal
- Kadane's algorithm
- Two pointers
- Sliding window
- KMP pattern matching

**O(n log n) - Linearithmic**
- Sorting (merge sort, quick sort)
- Building segment tree
- Binary search on each element

**O(n²) - Quadratic**
- Nested loops
- Naive pattern matching
- Bubble/Selection/Insertion sort
- DP on 2D tables (often optimizable)

**O(2ⁿ) - Exponential**
- Brute force subsets
- Naive Fibonacci
- Avoid in competitive programming!

---

## 🌟 Next Steps

After mastering Arrays and Strings:
1. Move to **Linked Lists** (Topic 24.2)
2. Study **Stacks and Queues** (Topics 24.3, 24.4)
3. Learn **Hashing** in depth (Topic 26)
4. Advanced: **Dynamic Programming** (Topic 31)
5. Master **Graph Algorithms** (Topic 34)

---

## 📞 Support & Resources

- **Documentation**: Each file has extensive inline comments
- **Practice Exercises**: End of each file has 10 practice problems
- **Complexity Analysis**: Included for every algorithm
- **Real Examples**: All code is runnable and tested

---

## 🏁 Summary

This comprehensive collection covers:
- ✅ 6 detailed learning files
- ✅ 70+ working examples
- ✅ 30+ algorithms and techniques
- ✅ 60+ practice exercises
- ✅ Complete competitive programming coverage
- ✅ Interview preparation material

**Total Learning Time**: 40-60 hours for complete mastery
**Practice Problems**: 100+ recommended across all platforms

Happy Learning! 🚀

---

*Last Updated: February 23, 2026*
*Part of: C++ DSA Learning Roadmap - Part 1*
