# Topic 26: Hashing and Hash Tables

## Overview
This folder contains comprehensive learning materials for **Hashing and Hash Tables**, covering everything from basic hash functions to advanced problem-solving techniques.

## 📚 File Structure

### 1. Hash Functions and Basics
**File:** `1_hash_functions_basics.cpp`

**Topics Covered:**
- What is hashing and why we need it
- Properties of good hash functions (deterministic, fast, uniform, avalanche)
- std::hash in C++
- Custom hash functions for different types
- Polynomial rolling hash
- Multiplication hash method
- Hash function for composite types
- Distribution analysis

**Key Examples:**
- Basic integer hash functions
- Using std::hash for built-in types
- Demonstrating avalanche effect
- Polynomial hash for strings
- Combining hashes for pairs and custom types
- Distribution testing

### 2. Hash Tables and Collision Resolution
**File:** `2_hash_tables_collision_resolution.cpp`

**Topics Covered:**
- Hash table structure and operations
- Collision detection and handling
- Chaining (separate chaining with linked lists)
- Open addressing techniques:
  - Linear probing
  - Quadratic probing
  - Double hashing
- Load factor and performance
- Rehashing and table growth

**Key Examples:**
- Simple hash table implementation
- Collision demonstration
- Hash table with chaining (complete implementation)
- Linear probing implementation
- Comparison of collision resolution methods
- Load factor impact on performance

### 3. unordered_map and unordered_set (C++ STL)
**File:** `3_unordered_map_unordered_set.cpp`

**Topics Covered:**
- unordered_map operations (insert, search, delete, update)
- unordered_set operations
- Comparison: unordered_map vs map, unordered_set vs set
- Custom hash functions for user-defined types
- Bucket interface and statistics
- Performance optimization techniques

**Key Examples:**
- Basic unordered_map/set operations
- Frequency counter
- Remove duplicates
- Two Sum problem
- Group anagrams
- Bucket inspection
- Custom hash for structs
- Caching/memoization
- Set operations

### 4. Advanced Hashing and Practical Problems
**File:** `4_advanced_hashing_problems.cpp`

**Topics Covered:**
- Rolling hash (Rabin-Karp algorithm)
- Advanced problem-solving patterns
- LRU Cache implementation
- Subarray problems with prefix sums
- String pattern problems
- Competitive programming techniques

**Key Examples:**
- Rolling hash for pattern matching
- Longest substring without repeating characters
- Subarray sum equals K
- Four Sum problem
- LRU Cache (hash map + doubly linked list)
- Valid Sudoku checker
- Longest consecutive sequence
- Isomorphic strings
- Top K frequent elements
- Custom HashSet implementation

## 🎯 Learning Path

### Beginner Level
1. Start with `1_hash_functions_basics.cpp`
   - Understand what hashing is
   - Learn properties of good hash functions
   - Practice using std::hash

2. Move to `2_hash_tables_collision_resolution.cpp`
   - Understand hash table structure
   - Learn collision resolution techniques
   - Implement basic hash table

### Intermediate Level
3. Study `3_unordered_map_unordered_set.cpp`
   - Master STL hash containers
   - Learn common use cases
   - Practice problem-solving patterns

### Advanced Level
4. Complete `4_advanced_hashing_problems.cpp`
   - Advanced algorithms (rolling hash)
   - Complex data structures (LRU Cache)
   - Competitive programming problems

## 💡 Key Concepts Summary

### Hash Functions
- **Purpose**: Map arbitrary data to fixed-size values
- **Properties**: Deterministic, fast, uniform distribution, avalanche effect
- **Common Methods**: Modulo, multiplication, polynomial rolling hash

### Hash Tables
- **Time Complexity**: O(1) average for insert/search/delete
- **Space Complexity**: O(n)
- **Collision Resolution**: Chaining, linear probing, quadratic probing, double hashing

### Load Factor
```
Load Factor (α) = Number of elements / Table size
```
- **Chaining**: Can exceed 1.0, typically keep < 1.0
- **Open Addressing**: Must stay < 1.0, typically < 0.7

### When to Use What

**Use unordered_map when:**
- Need fast O(1) lookups
- Don't care about order
- Working with large datasets
- Implementing caches, frequency counters

**Use map when:**
- Need sorted order
- Need range queries
- Need guaranteed O(log n) performance

**Use unordered_set when:**
- Only tracking presence/absence
- Removing duplicates
- Fast membership testing

**Use set when:**
- Need sorted unique elements
- Need ordered iteration

## 🔧 Common Problem-Solving Patterns

### 1. Frequency Counting
```cpp
unordered_map<element, count>
```
Count occurrences of elements

### 2. Two/Three/Four Sum
```cpp
unordered_map<value, index>
```
Store complements for efficient lookup

### 3. Sliding Window + Hash
```cpp
unordered_map/set + two pointers
```
Track elements in current window

### 4. Prefix Sum + Hash
```cpp
unordered_map<prefix_sum, count>
```
Find subarrays with specific sum

### 5. String Encoding
```cpp
unordered_map<encoded_state, value>
```
Complex state as string key

### 6. Caching/Memoization
```cpp
unordered_map<input, result>
```
Store computed results

## 📊 Performance Characteristics

| Operation | Average | Worst Case | Space |
| --------- | ------- | ---------- | ----- |
| Insert    | O(1)    | O(n)       | O(n)  |
| Search    | O(1)    | O(n)       | -     |
| Delete    | O(1)    | O(n)       | -     |

**Factors Affecting Performance:**
1. Quality of hash function
2. Load factor
3. Collision resolution method
4. Table size (prime numbers preferred)

## 🏆 Common Interview Problems

### Easy
- Two Sum
- Contains Duplicate
- Valid Anagram
- First Unique Character
- Intersection of Two Arrays

### Medium
- Group Anagrams
- Top K Frequent Elements
- Longest Substring Without Repeating
- Subarray Sum Equals K
- Longest Consecutive Sequence
- LRU Cache

### Hard
- Minimum Window Substring
- Substring with Concatenation
- Longest Duplicate Substring

## 🚀 Real-World Applications

1. **Databases**: Indexing, join operations
2. **Web Servers**: Session management, caching
3. **Compilers**: Symbol tables, variable scope
4. **Networking**: Routing tables, DNS
5. **Security**: Password hashing, digital signatures
6. **Distributed Systems**: Consistent hashing, load balancing
7. **Search Engines**: Inverted index, URL shortening
8. **Deduplication**: File systems, backups

## 🛠️ Compilation and Execution

### Compile Individual Files
```bash
g++ -std=c++17 1_hash_functions_basics.cpp -o hash_basics
./hash_basics

g++ -std=c++17 2_hash_tables_collision_resolution.cpp -o hash_tables
./hash_tables

g++ -std=c++17 3_unordered_map_unordered_set.cpp -o stl_hash
./stl_hash

g++ -std=c++17 4_advanced_hashing_problems.cpp -o advanced_hash
./advanced_hash
```

### Compile All Files
```bash
g++ -std=c++17 1_hash_functions_basics.cpp -o 1_basics && ./1_basics
g++ -std=c++17 2_hash_tables_collision_resolution.cpp -o 2_tables && ./2_tables
g++ -std=c++17 3_unordered_map_unordered_set.cpp -o 3_stl && ./3_stl
g++ -std=c++17 4_advanced_hashing_problems.cpp -o 4_advanced && ./4_advanced
```

## 📝 Practice Strategy

1. **Day 1-2**: Hash functions and basics
   - Understand hash function properties
   - Implement custom hash functions
   - Practice distribution analysis

2. **Day 3-4**: Hash tables and collisions
   - Implement hash table with chaining
   - Implement linear probing
   - Compare collision methods

3. **Day 5-6**: STL containers
   - Master unordered_map/set operations
   - Solve easy problems (Two Sum, frequency counting)
   - Learn common patterns

4. **Day 7-10**: Advanced problems
   - Implement LRU Cache
   - Solve medium problems
   - Practice competitive programming patterns

5. **Day 11-14**: Problem-solving marathon
   - Solve 20+ hash table problems
   - Focus on medium and hard problems
   - Time yourself

## ⚠️ Common Mistakes to Avoid

1. **Using [] for search** - Creates entry if doesn't exist
2. **Not checking find() result** - Crashes if not found
3. **Modifying keys** - Undefined behavior
4. **Forgetting custom hash** - Won't compile for user types
5. **Assuming order** - Hash tables are unordered
6. **Inefficient loops** - Copy instead of reference
7. **Poor table size** - Use prime numbers
8. **Ignoring load factor** - Performance degrades

## 📖 Additional Resources

### Books
- "Introduction to Algorithms" (CLRS) - Chapter on Hash Tables
- "The Art of Computer Programming Vol 3" - Searching and Sorting
- "Competitive Programming" - Hash table problems

### Online
- LeetCode Hash Table tag
- GeeksforGeeks Hashing section
- Codeforces hashing tutorials
- CP-Algorithms hashing guide

## ✅ Checklist

After completing this topic, you should be able to:

- [ ] Explain how hash functions work
- [ ] Implement custom hash functions
- [ ] Understand collision resolution techniques
- [ ] Choose between chaining and open addressing
- [ ] Use unordered_map and unordered_set effectively
- [ ] Solve Two Sum and variations
- [ ] Implement frequency counter
- [ ] Use sliding window with hash map
- [ ] Solve subarray sum problems
- [ ] Implement LRU Cache
- [ ] Handle custom types in hash containers
- [ ] Optimize hash table performance
- [ ] Recognize hash table problem patterns
- [ ] Apply hashing to real-world problems

## 🎓 Next Steps

After mastering hashing and hash tables:
1. Move to **Topic 27: Advanced Data Structures** (Disjoint Set, Skip Lists)
2. Study **Graph Algorithms** (use hash maps for adjacency lists)
3. Learn **String Algorithms** (use rolling hash)
4. Practice **Dynamic Programming** (use hash maps for memoization)
5. Explore **System Design** (consistent hashing, distributed caches)

---

**Happy Learning! 🚀**

*Last Updated: February 23, 2026*
