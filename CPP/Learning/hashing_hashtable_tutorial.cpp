#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
 * =====================================================================
 * HASHING AND HASH TABLES - COMPREHENSIVE TUTORIAL
 * =====================================================================
 *
 * WHAT IS HASHING?
 * Hashing is a technique to convert an input (any size) into a fixed-size
 * output called a HASH CODE or HASH VALUE.
 *
 * HASH FUNCTION: A function that takes input and returns a fixed-size number
 * Example: hash("John") might return 12345
 *
 * KEY PROPERTIES OF HASH FUNCTIONS:
 * 1. Deterministic: Same input always produces same output
 * 2. Fast: Can compute hash quickly
 * 3. Uniform Distribution: Spreads data across hash table
 * 4. Avalanche Effect: Small input change = big hash change
 *
 * WHAT IS A HASH TABLE?
 * A data structure that uses a hash function to map keys to values.
 * It stores data in an array of "buckets" or "slots".
 *
 * BASIC CONCEPT:
 * Key → [Hash Function] → Hash Code → [Index] → Bucket → Store (Key, Value)
 *
 * TIME COMPLEXITY:
 * Average Case: O(1) - constant time (best case)
 * Worst Case: O(n) - when all keys hash to same bucket (collision)
 *
 * COLLISION:
 * When two different keys produce the same hash code.
 * Example: hash("John") = 12345 AND hash("Jane") = 12345
 *
 * COLLISION RESOLUTION TECHNIQUES:
 * 1. Chaining - Store multiple values in one bucket (using a list)
 * 2. Open Addressing - Find another empty bucket
 *    - Linear Probing: Check next bucket
 *    - Quadratic Probing: Check at quadratic intervals
 *    - Double Hashing: Use second hash function
 * =====================================================================
 */

int main() {
  cout << "\n========== HASHING FUNDAMENTALS ==========" << endl << endl;

  // ===== 1. UNDERSTANDING HASH FUNCTIONS =====
  cout << "1. HASH FUNCTIONS IN C++" << endl;
  cout << "-------------------------------------------" << endl;

  // Using std::hash
  hash<string> stringHasher;
  hash<int> intHasher;
  hash<double> doubleHasher;

  cout << "Hash values for strings:" << endl;
  cout << "hash(\"apple\") = " << stringHasher("apple") << endl;
  cout << "hash(\"banana\") = " << stringHasher("banana") << endl;
  cout << "hash(\"cherry\") = " << stringHasher("cherry") << endl;
  cout << "hash(\"apple\") again = " << stringHasher("apple")
       << " (same as before!)" << endl;
  cout << endl;

  cout << "Hash values for integers:" << endl;
  cout << "hash(42) = " << intHasher(42) << endl;
  cout << "hash(100) = " << intHasher(100) << endl;
  cout << "hash(42) again = " << intHasher(42) << endl;
  cout << endl;

  // ===== 2. HOW HASH TABLES WORK =====
  cout << "2. HOW HASH TABLES WORK" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "Concept: Hash Table with 10 buckets (indices 0-9)" << endl;
  cout << "Storing key-value pairs:" << endl;
  cout << "  Key \"John\" -> hash value might be 23456 -> 23456 % 10 = 6 "
          "(bucket 6)"
       << endl;
  cout << "  Key \"Mary\" -> hash value might be 98765 -> 98765 % 10 = 5 "
          "(bucket 5)"
       << endl;
  cout << "  Key \"Bob\"  -> hash value might be 45678 -> 45678 % 10 = 8 "
          "(bucket 8)"
       << endl;
  cout << endl;

  // ===== 3. PRACTICAL EXAMPLE: MANUAL HASH TABLE =====
  cout << "3. SIMULATED HASH TABLE (Simplified)" << endl;
  cout << "-------------------------------------------" << endl;

  // Simple bucket size
  const int BUCKET_SIZE = 5;
  vector<vector<pair<string, int>>> simpleHashTable(BUCKET_SIZE);

  auto manualHash = [](const string &key, int size) {
    return hash<string>()(key) % size;
  };

  // Insert operations
  cout << "Inserting data into hash table:" << endl;
  string keys[] = {"Alice", "Bob", "Charlie", "David", "Eve"};
  int values[] = {90, 85, 92, 88, 95};

  for (int i = 0; i < 5; i++) {
    int index = manualHash(keys[i], BUCKET_SIZE);
    simpleHashTable[index].push_back({keys[i], values[i]});
    cout << "  \"" << keys[i] << "\" -> bucket " << index << endl;
  }
  cout << endl;

  cout << "Hash table contents:" << endl;
  for (int i = 0; i < BUCKET_SIZE; i++) {
    cout << "Bucket " << i << ": ";
    if (simpleHashTable[i].empty()) {
      cout << "(empty)";
    } else {
      for (auto &p : simpleHashTable[i]) {
        cout << "(" << p.first << "->" << p.second << ") ";
      }
    }
    cout << endl;
  }
  cout << endl;

  // ===== 4. UNORDERED_MAP - HASH TABLE IMPLEMENTATION =====
  cout << "\n========== UNORDERED_MAP (Hash Table Based) ==========" << endl;
  cout << "Uses hash table internally" << endl << endl;

  cout << "1. BASIC UNORDERED_MAP OPERATIONS" << endl;
  cout << "-------------------------------------------" << endl;

  unordered_map<string, int> scores;
  scores["Alice"] = 95;
  scores["Bob"] = 87;
  scores["Charlie"] = 92;
  scores["David"] = 88;
  scores["Eve"] = 91;

  cout << "Scores (note: order is NOT guaranteed):" << endl;
  for (auto &p : scores) {
    cout << p.first << ": " << p.second << endl;
  }
  cout << endl;

  cout << "2. HASH TABLE STATISTICS" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "Size (number of elements): " << scores.size() << endl;
  cout << "Bucket count: " << scores.bucket_count() << endl;
  cout << "Load factor: " << scores.load_factor() << " (elements / buckets)"
       << endl;
  cout << "Max load factor: " << scores.max_load_factor() << endl;
  cout << endl;

  cout << "3. WHICH BUCKET STORES EACH KEY?" << endl;
  cout << "-------------------------------------------" << endl;

  for (auto &p : scores) {
    cout << "\"" << p.first << "\" stored in bucket: " << scores.bucket(p.first)
         << endl;
  }
  cout << endl;

  cout << "4. BUCKET CONTENTS" << endl;
  cout << "-------------------------------------------" << endl;

  for (int i = 0; i < scores.bucket_count(); i++) {
    cout << "Bucket " << i << ": ";
    auto bucketSize = scores.bucket_size(i);
    if (bucketSize == 0) {
      cout << "(empty)";
    } else {
      auto it = scores.begin(i);
      for (int j = 0; j < bucketSize; j++, it++) {
        cout << "(" << it->first << "->" << it->second << ") ";
      }
    }
    cout << endl;
  }
  cout << endl;

  // ===== 5. COLLISION HANDLING =====
  cout << "5. COLLISION DEMONSTRATION" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "When multiple keys hash to the same bucket:" << endl;
  unordered_map<int, string> collisionTest;

  // Manually demonstrate collision concept
  cout << "Adding entries that might collide:" << endl;
  collisionTest[1] = "First";
  collisionTest[11] = "Second";
  collisionTest[21] = "Third";

  cout << "If bucket size is 10, all hash to same index!" << endl;
  cout << "C++ uses chaining to handle this:" << endl;
  cout << "  Bucket stores: (1,First) -> (11,Second) -> (21,Third)" << endl;
  cout << "  When searching for key 11, it traverses the chain" << endl;
  cout << endl;

  // ===== 6. UNORDERED_SET - HASH SET =====
  cout << "6. UNORDERED_SET (Hash Set - No Values)" << endl;
  cout << "-------------------------------------------" << endl;

  unordered_set<string> visited;
  visited.insert("New York");
  visited.insert("Los Angeles");
  visited.insert("Chicago");
  visited.insert("New York"); // Duplicate, not inserted

  cout << "Visited cities (unordered, no duplicates):" << endl;
  for (auto &city : visited) {
    cout << "  " << city << endl;
  }
  cout << "Size: " << visited.size() << " (not 4 because of duplicate)" << endl;
  cout << endl;

  cout << "Check if city visited:" << endl;
  cout << "  \"Chicago\" visited? "
       << (visited.find("Chicago") != visited.end() ? "Yes" : "No") << endl;
  cout << "  \"Boston\" visited? "
       << (visited.find("Boston") != visited.end() ? "Yes" : "No") << endl;
  cout << endl;

  // ===== 7. CUSTOM HASH FUNCTION =====
  cout << "7. CUSTOM HASH FUNCTIONS" << endl;
  cout << "-------------------------------------------" << endl;

  struct Person {
    string name;
    int id;

    bool operator==(const Person &other) const { return id == other.id; }
  };

  // Custom hash function for Person
  struct PersonHash {
    size_t operator()(const Person &p) const { return hash<int>()(p.id); }
  };

  unordered_map<Person, string, PersonHash> personData;
  personData[Person{"Alice", 1}] = "Engineer";
  personData[Person{"Bob", 2}] = "Manager";
  personData[Person{"Charlie", 3}] = "Designer";

  cout << "Using custom hash for Person objects:" << endl;
  for (auto &p : personData) {
    cout << p.first.name << " (ID: " << p.first.id << ") -> " << p.second
         << endl;
  }
  cout << endl;

  // ===== 8. COMPARISON: MAP vs UNORDERED_MAP =====
  cout << "\n========== MAP vs UNORDERED_MAP ==========" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "std::map:" << endl;
  cout << "  - Ordered by key (sorted)" << endl;
  cout << "  - Insert/Delete/Find: O(log n)" << endl;
  cout << "  - Uses Binary Search Tree internally" << endl;
  cout << "  - Guaranteed performance" << endl;
  cout << "  - Use when you need sorted data" << endl << endl;

  cout << "std::unordered_map:" << endl;
  cout << "  - Unordered" << endl;
  cout << "  - Insert/Delete/Find: O(1) average, O(n) worst" << endl;
  cout << "  - Uses Hash Table internally" << endl;
  cout << "  - Better average performance" << endl;
  cout << "  - Use when speed is critical" << endl << endl;

  // ===== 9. LOAD FACTOR AND REHASHING =====
  cout << "9. LOAD FACTOR AND REHASHING" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "Load Factor = (Number of elements) / (Number of buckets)" << endl;
  cout << "When load factor exceeds max_load_factor, hash table rehashes"
       << endl;
  cout << "(Creates larger table and re-inserts all elements)" << endl << endl;

  unordered_map<int, string> growingMap;
  cout << "Adding elements and watching load factor:" << endl;
  for (int i = 0; i < 15; i++) {
    growingMap[i] = "value_" + to_string(i);
    if (i % 5 == 0) {
      cout << "After adding " << (i + 1) << " elements:" << endl;
      cout << "  Buckets: " << growingMap.bucket_count()
           << ", Load Factor: " << growingMap.load_factor() << endl;
    }
  }
  cout << endl;

  // ===== 10. USE CASES =====
  cout << "10. COMMON USE CASES FOR HASH TABLES" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "✓ Frequency Counter - Count word occurrences" << endl;
  cout << "✓ Caching - Store computed results" << endl;
  cout << "✓ Deduplication - Remove duplicates from data" << endl;
  cout << "✓ Fast Lookup - Check if element exists" << endl;
  cout << "✓ Two Sum Problem - Find pairs that sum to target" << endl;
  cout << "✓ Anagram Groups - Group anagrams together" << endl;
  cout << "✓ URL Shortener - Map short URLs to long URLs" << endl;
  cout << endl;

  // ===== 11. PRACTICAL EXAMPLE: WORD FREQUENCY =====
  cout << "11. PRACTICAL EXAMPLE: WORD FREQUENCY COUNTER" << endl;
  cout << "-------------------------------------------" << endl;

  string text = "the quick brown fox jumps over the lazy dog the fox is quick";
  unordered_map<string, int> wordFreq;

  // Count words (simplified - doesn't handle punctuation)
  string word;
  stringstream ss(text);
  while (ss >> word) {
    wordFreq[word]++;
  }

  cout << "Text: \"" << text << "\"" << endl << endl;
  cout << "Word frequencies:" << endl;
  for (auto &p : wordFreq) {
    cout << "  \"" << p.first << "\": " << p.second << " times" << endl;
  }
  cout << endl;

  // ===== 12. HASH COLLISIONS IN DETAIL =====
  cout << "12. UNDERSTANDING HASH COLLISIONS" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "Problem: Different keys hashing to same bucket" << endl;
  cout << "Example with small hash table (10 buckets):" << endl << endl;

  auto simpleHash = [](int x) { return x % 10; };

  cout << "hash(15) = 15 % 10 = " << simpleHash(15) << " (bucket 5)" << endl;
  cout << "hash(25) = 25 % 10 = " << simpleHash(25)
       << " (bucket 5) <- COLLISION!" << endl;
  cout << "hash(35) = 35 % 10 = " << simpleHash(35)
       << " (bucket 5) <- COLLISION!" << endl
       << endl;

  cout << "Chaining solution (used by C++):" << endl;
  cout << "Bucket 5: [15, value1] -> [25, value2] -> [35, value3]" << endl;
  cout << "When finding key 25, traverse chain until found" << endl;
  cout << endl;

  return 0;
}
