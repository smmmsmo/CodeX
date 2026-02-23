#include <iostream>
#include <list>
#include <optional>
#include <string>
#include <vector>
using namespace std;

/*
 * =====================================================================
 * TOPIC 26.2: HASH TABLES AND COLLISION RESOLUTION
 * =====================================================================
 *
 * WHAT IS A HASH TABLE?
 * A data structure that implements an associative array (map/dictionary)
 * using a hash function to compute an index into an array of buckets.
 *
 * KEY CONCEPTS COVERED:
 * 1. Hash table structure and operations
 * 2. Collision detection and handling
 * 3. Chaining (separate chaining)
 * 4. Open addressing (linear probing, quadratic probing, double hashing)
 * 5. Load factor and rehashing
 * 6. Performance analysis
 *
 * =====================================================================
 * HASH TABLE BASICS
 * =====================================================================
 *
 * STRUCTURE:
 *   Key → Hash Function → Index → Bucket → Value
 *
 * OPERATIONS:
 *   - Insert(key, value): Add key-value pair
 *   - Search(key): Find value by key
 *   - Delete(key): Remove key-value pair
 *
 * TIME COMPLEXITY (Average):
 *   - Insert: O(1)
 *   - Search: O(1)
 *   - Delete: O(1)
 *
 * TIME COMPLEXITY (Worst):
 *   - All operations: O(n) when many collisions occur
 *
 * SPACE COMPLEXITY: O(n)
 *
 * =====================================================================
 * COLLISIONS
 * =====================================================================
 *
 * WHAT IS A COLLISION?
 *   When two different keys hash to the same index
 *   Example: hash("John") = 5 and hash("Jane") = 5
 *
 * WHY COLLISIONS HAPPEN?
 *   1. Limited table size (infinite keys → finite buckets)
 *   2. Imperfect hash function
 *   3. Pigeonhole principle (more items than slots)
 *
 * COLLISION RESOLUTION TECHNIQUES:
 *   1. Chaining (Closed Addressing)
 *   2. Open Addressing (Linear Probing, Quadratic, Double Hashing)
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: SIMPLE HASH TABLE WITH ARRAY ==============
void example1_simple_hash_table() {
  cout << "\n============== EXAMPLE 1: SIMPLE HASH TABLE =============="
       << endl;
  cout << "Direct addressing: key = index (works only for small integer keys)\n"
       << endl;

  const int SIZE = 100;
  int hashTable[SIZE];

  // Initialize all to -1 (empty)
  for (int i = 0; i < SIZE; i++) {
    hashTable[i] = -1;
  }

  // Insert key-value pairs (key = student ID, value = score)
  hashTable[15] = 95;
  hashTable[23] = 87;
  hashTable[42] = 92;
  hashTable[67] = 88;

  cout << "Inserted data:" << endl;
  cout << "  Student 15: Score " << hashTable[15] << endl;
  cout << "  Student 23: Score " << hashTable[23] << endl;
  cout << "  Student 42: Score " << hashTable[42] << endl;
  cout << "  Student 67: Score " << hashTable[67] << endl;

  // Search
  int search_key = 42;
  if (hashTable[search_key] != -1) {
    cout << "\nStudent " << search_key
         << " found with score: " << hashTable[search_key] << endl;
  }

  cout << "\nLimitation: Only works for small, known integer keys" << endl;
  cout << "Wastes space if keys are sparse (e.g., IDs: 1, 1000000)" << endl;
}

// ============== EXAMPLE 2: UNDERSTANDING COLLISIONS ==============
void example2_collision_demonstration() {
  cout << "\n============== EXAMPLE 2: COLLISION DEMONSTRATION =============="
       << endl;
  cout << "What happens when two keys hash to same index?\n" << endl;

  const int SIZE = 10;
  vector<string> keys = {"John", "Jane", "Bob", "Alice", "Tom"};

  // Simple hash function
  auto hash_func = [](const string &s, int size) {
    int sum = 0;
    for (char c : s)
      sum += c;
    return sum % size;
  };

  cout << "Hash table size: " << SIZE << endl;
  cout << "Hash function: sum of ASCII values % " << SIZE << "\n" << endl;

  cout << "Computing hash values:" << endl;
  for (const string &key : keys) {
    int hash_val = hash_func(key, SIZE);
    cout << "  hash(\"" << key << "\") = " << hash_val << endl;
  }

  cout << "\nCOLLISION DETECTED!" << endl;
  cout << "Multiple keys may map to same bucket" << endl;
  cout << "Need collision resolution strategy!" << endl;
}

// ============== EXAMPLE 3: CHAINING (SEPARATE CHAINING) ==============
class HashTableChaining {
private:
  static const int SIZE = 10;
  vector<list<pair<string, int>>> table;

  int hash(const string &key) {
    int sum = 0;
    for (char c : key)
      sum += c;
    return sum % SIZE;
  }

public:
  HashTableChaining() : table(SIZE) {}

  void insert(const string &key, int value) {
    int index = hash(key);

    // Check if key already exists
    for (auto &pair : table[index]) {
      if (pair.first == key) {
        pair.second = value; // Update existing
        return;
      }
    }

    // Add new key-value pair to the chain
    table[index].push_back({key, value});
  }

  optional<int> search(const string &key) {
    int index = hash(key);

    // Search in the chain
    for (const auto &pair : table[index]) {
      if (pair.first == key) {
        return pair.second;
      }
    }

    return nullopt; // Not found
  }

  void remove(const string &key) {
    int index = hash(key);

    table[index].remove_if(
        [&key](const pair<string, int> &p) { return p.first == key; });
  }

  void display() {
    cout << "Hash Table Contents:" << endl;
    for (int i = 0; i < SIZE; i++) {
      cout << "Bucket " << i << ": ";
      if (table[i].empty()) {
        cout << "(empty)";
      } else {
        for (const auto &pair : table[i]) {
          cout << "[" << pair.first << ":" << pair.second << "] ";
        }
      }
      cout << endl;
    }
  }
};

void example3_chaining() {
  cout << "\n============== EXAMPLE 3: CHAINING (SEPARATE CHAINING) "
          "=============="
       << endl;
  cout << "Each bucket stores a linked list of key-value pairs\n" << endl;

  HashTableChaining ht;

  cout << "Inserting elements:" << endl;
  ht.insert("Alice", 95);
  ht.insert("Bob", 87);
  ht.insert("Charlie", 92);
  ht.insert("David", 88);
  ht.insert("Eve", 91);

  cout << "\nAfter insertions:" << endl;
  ht.display();

  // Search
  cout << "\nSearching for 'Charlie':" << endl;
  auto result = ht.search("Charlie");
  if (result) {
    cout << "Found: Charlie -> " << *result << endl;
  }

  // Update
  cout << "\nUpdating Bob's value to 100:" << endl;
  ht.insert("Bob", 100);
  ht.display();

  // Delete
  cout << "\nDeleting 'Eve':" << endl;
  ht.remove("Eve");
  ht.display();

  cout << "\nAdvantages of Chaining:" << endl;
  cout << "  ✓ Simple implementation" << endl;
  cout << "  ✓ No clustering" << endl;
  cout << "  ✓ Can handle many collisions" << endl;
  cout << "  ✓ Load factor can exceed 1" << endl;

  cout << "\nDisadvantages:" << endl;
  cout << "  ✗ Extra memory for pointers" << endl;
  cout << "  ✗ Cache performance (non-contiguous)" << endl;
}

// ============== EXAMPLE 4: LINEAR PROBING (OPEN ADDRESSING) ==============
class HashTableLinearProbing {
private:
  static const int SIZE = 10;
  vector<optional<pair<string, int>>> table;

  int hash(const string &key) {
    int sum = 0;
    for (char c : key)
      sum += c;
    return sum % SIZE;
  }

public:
  HashTableLinearProbing() : table(SIZE) {}

  void insert(const string &key, int value) {
    int index = hash(key);
    int start_index = index;

    // Linear probing: try next slot if occupied
    while (table[index].has_value()) {
      // Update if key exists
      if (table[index]->first == key) {
        table[index]->second = value;
        return;
      }

      index = (index + 1) % SIZE; // Move to next slot

      // Table full
      if (index == start_index) {
        cout << "Error: Hash table is full!" << endl;
        return;
      }
    }

    // Insert at empty slot
    table[index] = make_pair(key, value);
  }

  optional<int> search(const string &key) {
    int index = hash(key);
    int start_index = index;

    while (table[index].has_value()) {
      if (table[index]->first == key) {
        return table[index]->second;
      }

      index = (index + 1) % SIZE;

      if (index == start_index)
        break; // Full circle
    }

    return nullopt; // Not found
  }

  void display() {
    cout << "Hash Table Contents:" << endl;
    for (int i = 0; i < SIZE; i++) {
      cout << "Slot " << i << ": ";
      if (table[i].has_value()) {
        cout << "[" << table[i]->first << ":" << table[i]->second << "]";
      } else {
        cout << "(empty)";
      }
      cout << endl;
    }
  }
};

void example4_linear_probing() {
  cout << "\n============== EXAMPLE 4: LINEAR PROBING ==============" << endl;
  cout << "If slot occupied, try next slot: (hash + 1) % size\n" << endl;

  HashTableLinearProbing ht;

  cout << "Inserting elements:" << endl;
  ht.insert("Alice", 95);
  ht.insert("Bob", 87);
  ht.insert("Charlie", 92);

  cout << "\nAfter insertions:" << endl;
  ht.display();

  cout << "\nSearching for 'Bob':" << endl;
  auto result = ht.search("Bob");
  if (result) {
    cout << "Found: Bob -> " << *result << endl;
  }

  cout << "\nAdvantages of Linear Probing:" << endl;
  cout << "  ✓ No extra memory for pointers" << endl;
  cout << "  ✓ Good cache performance (contiguous)" << endl;
  cout << "  ✓ Simple implementation" << endl;

  cout << "\nDisadvantages:" << endl;
  cout << "  ✗ Primary clustering (consecutive occupied slots)" << endl;
  cout << "  ✗ Performance degrades with high load factor" << endl;
}

// ============== EXAMPLE 5: QUADRATIC PROBING ==============
void example5_quadratic_probing() {
  cout << "\n============== EXAMPLE 5: QUADRATIC PROBING =============="
       << endl;
  cout << "Probe sequence: h(k), h(k)+1², h(k)+2², h(k)+3², ...\n" << endl;

  const int SIZE = 11; // Prime number for better probing
  int key = 42;

  auto hash_func = [](int k, int size) { return k % size; };

  int h = hash_func(key, SIZE);

  cout << "Inserting key " << key << " into table of size " << SIZE << endl;
  cout << "Initial hash: h(" << key << ") = " << h << "\n" << endl;

  cout << "Quadratic probing sequence:" << endl;
  for (int i = 0; i < 5; i++) {
    int index = (h + i * i) % SIZE;
    cout << "  Probe " << i << ": (" << h << " + " << i << "²) % " << SIZE
         << " = " << index << endl;
  }

  cout << "\nAdvantages over Linear Probing:" << endl;
  cout << "  ✓ Reduces primary clustering" << endl;
  cout << "  ✓ Better distribution" << endl;

  cout << "\nDisadvantages:" << endl;
  cout << "  ✗ Secondary clustering (same probe sequence)" << endl;
  cout << "  ✗ May not probe all slots" << endl;
}

// ============== EXAMPLE 6: DOUBLE HASHING ==============
void example6_double_hashing() {
  cout << "\n============== EXAMPLE 6: DOUBLE HASHING ==============" << endl;
  cout << "Uses two hash functions: h1(k) and h2(k)" << endl;
  cout << "Probe sequence: h1(k), h1(k)+h2(k), h1(k)+2*h2(k), ...\n" << endl;

  const int SIZE = 11;
  int key = 42;

  auto h1 = [](int k, int size) { return k % size; };
  auto h2 = [](int k, int size) { return 1 + (k % (size - 1)); };

  int hash1 = h1(key, SIZE);
  int hash2 = h2(key, SIZE);

  cout << "Inserting key " << key << " into table of size " << SIZE << endl;
  cout << "h1(" << key << ") = " << hash1 << endl;
  cout << "h2(" << key << ") = " << hash2 << "\n" << endl;

  cout << "Double hashing probe sequence:" << endl;
  for (int i = 0; i < 5; i++) {
    int index = (hash1 + i * hash2) % SIZE;
    cout << "  Probe " << i << ": (" << hash1 << " + " << i << "*" << hash2
         << ") % " << SIZE << " = " << index << endl;
  }

  cout << "\nAdvantages:" << endl;
  cout << "  ✓ Eliminates primary clustering" << endl;
  cout << "  ✓ Reduces secondary clustering" << endl;
  cout << "  ✓ Better distribution" << endl;

  cout << "\nBest Practice:" << endl;
  cout << "  - Table size should be prime" << endl;
  cout << "  - h2(k) should never be 0" << endl;
  cout << "  - h2(k) and table size should be coprime" << endl;
}

// ============== EXAMPLE 7: LOAD FACTOR ==============
void example7_load_factor() {
  cout << "\n============== EXAMPLE 7: LOAD FACTOR ==============" << endl;
  cout << "Load Factor (α) = Number of elements / Table size\n" << endl;

  int table_size = 10;

  cout << "Table size: " << table_size << "\n" << endl;

  for (int n = 0; n <= 15; n += 3) {
    double load_factor = static_cast<double>(n) / table_size;
    cout << "Elements: " << n << ", Load Factor: " << load_factor;

    if (load_factor < 0.5) {
      cout << " - Low (good performance)";
    } else if (load_factor < 0.7) {
      cout << " - Moderate (acceptable)";
    } else if (load_factor <= 1.0) {
      cout << " - High (consider resizing)";
    } else {
      cout << " - Critical (must resize for open addressing)";
    }
    cout << endl;
  }

  cout << "\nGuidelines:" << endl;
  cout << "  Chaining: Can exceed 1.0, typically keep < 1.0" << endl;
  cout << "  Open Addressing: Must stay < 1.0, typically < 0.7" << endl;
}

// ============== EXAMPLE 8: REHASHING ==============
void example8_rehashing() {
  cout << "\n============== EXAMPLE 8: REHASHING ==============" << endl;
  cout << "When load factor gets too high, resize and rehash\n" << endl;

  cout << "Process:" << endl;
  cout << "  1. Create new table (usually 2x size)" << endl;
  cout << "  2. For each element in old table:" << endl;
  cout << "     - Compute new hash with new size" << endl;
  cout << "     - Insert into new table" << endl;
  cout << "  3. Replace old table with new table\n" << endl;

  cout << "Example:" << endl;
  int old_size = 5;
  int new_size = 11; // Prime number
  vector<int> keys = {12, 22, 32, 42, 52};

  cout << "Old table (size " << old_size << "):" << endl;
  for (int key : keys) {
    cout << "  key " << key << " -> bucket " << (key % old_size) << endl;
  }

  cout << "\nRehashing to new table (size " << new_size << "):" << endl;
  for (int key : keys) {
    cout << "  key " << key << " -> bucket " << (key % new_size) << endl;
  }

  cout << "\nNote: All keys redistributed to new positions!" << endl;

  cout << "\nRehashing cost: O(n)" << endl;
  cout << "But amortized O(1) per insertion if done correctly" << endl;
}

// ============== EXAMPLE 9: COLLISION RESOLUTION COMPARISON ==============
void example9_collision_comparison() {
  cout << "\n============== EXAMPLE 9: COLLISION RESOLUTION COMPARISON "
          "=============="
       << endl;

  cout << "\n┌──────────────────┬───────────┬────────────┬──────────────┬──────"
          "─────────┐"
       << endl;
  cout << "│ Method           │ Clustering│ Memory     │ Cache        │ Load "
          "Factor   │"
       << endl;
  cout << "├──────────────────┼───────────┼────────────┼──────────────┼────────"
          "───────┤"
       << endl;
  cout << "│ Chaining         │ None      │ Extra      │ Poor         │ Can "
          "exceed 1  │"
       << endl;
  cout << "│ Linear Probing   │ Primary   │ None       │ Excellent    │ Must < "
          "1      │"
       << endl;
  cout << "│ Quadratic Prob.  │ Secondary │ None       │ Good         │ Must < "
          "1      │"
       << endl;
  cout << "│ Double Hashing   │ Minimal   │ None       │ Good         │ Must < "
          "1      │"
       << endl;
  cout << "└──────────────────┴───────────┴────────────┴──────────────┴────────"
          "───────┘"
       << endl;

  cout << "\nWhen to use each:" << endl;
  cout << "  Chaining: High load factors, unknown data size" << endl;
  cout << "  Linear Probing: Good cache, low load factor" << endl;
  cout << "  Quadratic: Balance between linear and double" << endl;
  cout << "  Double Hashing: Best distribution, willing to compute 2 hashes"
       << endl;
}

// ============== EXAMPLE 10: PERFORMANCE ANALYSIS ==============
void example10_performance_analysis() {
  cout << "\n============== EXAMPLE 10: PERFORMANCE ANALYSIS =============="
       << endl;

  cout << "\nAverage Case Time Complexity:" << endl;
  cout << "  With good hash function and low load factor:\n" << endl;

  cout << "┌───────────┬──────────┬──────────┬──────────┐" << endl;
  cout << "│ Operation │ Chaining │ Open Addr│ Expected │" << endl;
  cout << "├───────────┼──────────┼──────────┼──────────┤" << endl;
  cout << "│ Insert    │ O(1)     │ O(1)     │ O(1)     │" << endl;
  cout << "│ Search    │ O(1)     │ O(1)     │ O(1)     │" << endl;
  cout << "│ Delete    │ O(1)     │ O(1)     │ O(1)     │" << endl;
  cout << "└───────────┴──────────┴──────────┴──────────┘" << endl;

  cout << "\nWorst Case (all keys collide, α → 1):" << endl;
  cout << "  All operations: O(n)" << endl;

  cout << "\nSpace Complexity:" << endl;
  cout << "  Chaining: O(n + m) where m = table size" << endl;
  cout << "  Open Addressing: O(m) where m ≥ n" << endl;

  cout << "\nFactors affecting performance:" << endl;
  cout << "  1. Quality of hash function" << endl;
  cout << "  2. Load factor (α = n/m)" << endl;
  cout << "  3. Collision resolution method" << endl;
  cout << "  4. Table size (prime numbers preferred)" << endl;
}

int main() {
  cout << "\n======================================================" << endl;
  cout << "    HASH TABLES & COLLISION RESOLUTION TUTORIAL      " << endl;
  cout << "======================================================" << endl;

  example1_simple_hash_table();
  example2_collision_demonstration();
  example3_chaining();
  example4_linear_probing();
  example5_quadratic_probing();
  example6_double_hashing();
  example7_load_factor();
  example8_rehashing();
  example9_collision_comparison();
  example10_performance_analysis();

  cout << "\n======================================================" << endl;
  cout << "                   KEY TAKEAWAYS                      " << endl;
  cout << "======================================================" << endl;
  cout << "✓ Hash tables provide O(1) average-case operations" << endl;
  cout << "✓ Collisions inevitable due to pigeonhole principle" << endl;
  cout << "✓ Chaining: simple, handles high load factors" << endl;
  cout << "✓ Open addressing: better cache, needs load < 1" << endl;
  cout << "✓ Load factor critical for performance" << endl;
  cout << "✓ Rehashing redistributes keys when table grows" << endl;
  cout << "✓ Choose method based on use case and constraints" << endl;
  cout << "======================================================\n" << endl;

  return 0;
}

/*
 * =====================================================================
 * COMMON MISTAKES TO AVOID
 * =====================================================================
 *
 * 1. NOT HANDLING DELETIONS IN OPEN ADDRESSING
 *    ✗ BAD: Set slot to empty - breaks search chain!
 *    ✓ GOOD: Use "tombstone" marker for deleted items
 *
 * 2. POOR TABLE SIZE CHOICE
 *    ✗ BAD: table_size = 100 (power of 2 or even)
 *    ✓ GOOD: table_size = 101 (prime number)
 *
 * 3. IGNORING LOAD FACTOR
 *    ✗ BAD: Keep inserting until table full
 *    ✓ GOOD: Rehash when α > 0.7 (open addressing) or α > 1.0 (chaining)
 *
 * 4. INEFFICIENT CHAINING DATA STRUCTURE
 *    ✗ BAD: Using vector for chains (expensive insert/delete)
 *    ✓ GOOD: Use linked list for chains
 *
 * 5. POOR SECONDARY HASH FUNCTION
 *    ✗ BAD: h2(k) = 0 or h2(k) = constant
 *    ✓ GOOD: h2(k) = 1 + (k % (size-1))
 *
 * 6. NOT UPDATING ON DUPLICATE KEYS
 *    ✗ BAD: Insert duplicate, creating two entries
 *    ✓ GOOD: Check and update existing key
 *
 * 7. FORGETTING WRAPAROUND IN PROBING
 *    ✗ BAD: index = hash + i (goes out of bounds)
 *    ✓ GOOD: index = (hash + i) % size
 *
 * =====================================================================
 * PRACTICE EXERCISES
 * =====================================================================
 *
 * 1. Implement hash table with chaining that supports duplicate keys
 * 2. Implement deletion in linear probing with tombstones
 * 3. Compare performance: chaining vs linear probing (measure collisions)
 * 4. Implement automatic rehashing when load factor > 0.75
 * 5. Visualize clustering in linear vs quadratic probing
 * 6. Implement hash table that stores frequency of elements
 * 7. Create hash table with custom hash function for strings
 * 8. Implement cuckoo hashing (uses 2 tables, 2 hash functions)
 * 9. Write program to find optimal table size (prime number)
 * 10. Implement hash table that supports range queries
 *
 * =====================================================================
 * REAL-WORLD APPLICATIONS
 * =====================================================================
 *
 * 1. Databases - Indexing for fast lookups
 * 2. Compilers - Symbol tables for variables
 * 3. Caching - Store computed results (memoization)
 * 4. Routers - IP routing tables
 * 5. Spell Checkers - Dictionary lookups
 * 6. Password Storage - Hash passwords for security
 * 7. Blockchain - Hash-based data structures
 * 8. DNS - Domain name resolution
 * 9. Load Balancers - Distribute requests
 * 10. Deduplication - Remove duplicate files/data
 *
 * =====================================================================
 * COMPILATION AND EXECUTION
 * =====================================================================
 *
 * To compile and run:
 *   g++ -std=c++17 2_hash_tables_collision_resolution.cpp -o hash_tables
 *   ./hash_tables
 *
 * =====================================================================
 */
