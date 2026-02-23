#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
 * =====================================================================
 * TOPIC 26.3: UNORDERED_MAP AND UNORDERED_SET (C++ STL)
 * =====================================================================
 *
 * C++ Standard Template Library provides hash-based containers:
 * - unordered_map: Hash table for key-value pairs
 * - unordered_set: Hash table for unique keys only
 *
 * KEY CONCEPTS COVERED:
 * 1. unordered_map operations (insert, search, delete, update)
 * 2. unordered_set operations
 * 3. Comparison with map/set (ordered containers)
 * 4. Custom hash functions for user-defined types
 * 5. Iterator usage and bucket interface
 * 6. Performance characteristics
 * 7. Common use cases and patterns
 *
 * =====================================================================
 * UNORDERED_MAP vs MAP
 * =====================================================================
 *
 * UNORDERED_MAP (Hash Table):
 *   - Unordered elements
 *   - Average O(1) insert/search/delete
 *   - Worst O(n) if many collisions
 *   - More memory overhead
 *   - Faster for lookups
 *
 * MAP (Binary Search Tree):
 *   - Sorted elements (by key)
 *   - O(log n) insert/search/delete
 *   - Guaranteed performance
 *   - Less memory overhead
 *   - Supports range queries
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: BASIC UNORDERED_MAP OPERATIONS ==============
void example1_basic_unordered_map() {
  cout << "\n============== EXAMPLE 1: BASIC UNORDERED_MAP =============="
       << endl;
  cout << "unordered_map<Key, Value> - Hash table for key-value pairs\n"
       << endl;

  unordered_map<string, int> ages;

  // 1. INSERT - Multiple ways
  cout << "1. INSERTION METHODS:" << endl;
  ages["Alice"] = 25;                    // Using subscript operator
  ages.insert({"Bob", 30});              // Using insert
  ages.insert(make_pair("Charlie", 35)); // Using make_pair
  ages.emplace("David", 28);             // Using emplace (more efficient)

  cout << "  Inserted 4 people\n" << endl;

  // 2. ACCESS
  cout << "2. ACCESSING VALUES:" << endl;
  cout << "  ages[\"Alice\"] = " << ages["Alice"] << endl;
  cout << "  ages.at(\"Bob\") = " << ages.at("Bob") << endl;

  // Note: [] creates entry if doesn't exist, at() throws exception

  // 3. SIZE
  cout << "\n3. SIZE:" << endl;
  cout << "  Number of elements: " << ages.size() << endl;
  cout << "  Is empty? " << (ages.empty() ? "Yes" : "No") << endl;

  // 4. SEARCH
  cout << "\n4. SEARCHING:" << endl;
  if (ages.find("Charlie") != ages.end()) {
    cout << "  \"Charlie\" found with age " << ages["Charlie"] << endl;
  }

  if (ages.count("Eve") > 0) {
    cout << "  \"Eve\" exists" << endl;
  } else {
    cout << "  \"Eve\" not found" << endl;
  }

  // 5. DELETE
  cout << "\n5. DELETION:" << endl;
  ages.erase("Bob");
  cout << "  Erased \"Bob\"" << endl;
  cout << "  New size: " << ages.size() << endl;

  // 6. ITERATION
  cout << "\n6. ITERATION (order not guaranteed):" << endl;
  for (const auto &pair : ages) {
    cout << "  " << pair.first << ": " << pair.second << endl;
  }
}

// ============== EXAMPLE 2: UNORDERED_MAP VS MAP ==============
void example2_unordered_vs_ordered() {
  cout << "\n============== EXAMPLE 2: UNORDERED_MAP vs MAP =============="
       << endl;

  unordered_map<int, string> u_map;
  map<int, string> o_map;

  // Insert same data into both
  vector<pair<int, string>> data = {
      {5, "Five"}, {2, "Two"}, {8, "Eight"}, {1, "One"}, {9, "Nine"}};

  for (const auto &p : data) {
    u_map[p.first] = p.second;
    o_map[p.first] = p.second;
  }

  cout << "unordered_map (hash table - no order):" << endl;
  for (const auto &p : u_map) {
    cout << "  " << p.first << " -> " << p.second << endl;
  }

  cout << "\nmap (BST - sorted by key):" << endl;
  for (const auto &p : o_map) {
    cout << "  " << p.first << " -> " << p.second << endl;
  }

  cout << "\nKey Difference: map maintains sorted order!" << endl;
}

// ============== EXAMPLE 3: UNORDERED_SET OPERATIONS ==============
void example3_basic_unordered_set() {
  cout << "\n============== EXAMPLE 3: BASIC UNORDERED_SET =============="
       << endl;
  cout << "unordered_set<T> - Hash table for unique elements\n" << endl;

  unordered_set<string> fruits;

  // 1. INSERT
  cout << "1. INSERTION:" << endl;
  fruits.insert("Apple");
  fruits.insert("Banana");
  fruits.insert("Cherry");
  fruits.insert("Apple"); // Duplicate - won't be inserted

  cout << "  Inserted 4 items (1 duplicate)" << endl;
  cout << "  Actual size: " << fruits.size() << " (duplicates ignored)\n"
       << endl;

  // 2. SEARCH
  cout << "2. SEARCHING:" << endl;
  if (fruits.find("Banana") != fruits.end()) {
    cout << "  \"Banana\" found!" << endl;
  }

  cout << "  \"Orange\" exists? " << (fruits.count("Orange") > 0 ? "Yes" : "No")
       << endl;

  // 3. DELETE
  cout << "\n3. DELETION:" << endl;
  fruits.erase("Cherry");
  cout << "  Removed \"Cherry\"" << endl;
  cout << "  New size: " << fruits.size() << endl;

  // 4. ITERATION
  cout << "\n4. ITERATION:" << endl;
  for (const string &fruit : fruits) {
    cout << "  " << fruit << endl;
  }

  // 5. CLEAR
  fruits.clear();
  cout << "\n5. After clear(), size = " << fruits.size() << endl;
}

// ============== EXAMPLE 4: FREQUENCY COUNTER ==============
void example4_frequency_counter() {
  cout << "\n============== EXAMPLE 4: FREQUENCY COUNTER =============="
       << endl;
  cout << "Classic use case: Count occurrences of elements\n" << endl;

  vector<string> words = {"apple",  "banana", "apple", "cherry",
                          "banana", "apple",  "date",  "banana"};

  unordered_map<string, int> frequency;

  // Count frequencies
  for (const string &word : words) {
    frequency[word]++; // Auto-initializes to 0 if not exists
  }

  cout << "Word frequencies:" << endl;
  for (const auto &pair : frequency) {
    cout << "  " << pair.first << ": " << pair.second << " times" << endl;
  }

  // Find most frequent
  auto max_elem = max_element(
      frequency.begin(), frequency.end(),
      [](const auto &a, const auto &b) { return a.second < b.second; });

  cout << "\nMost frequent: \"" << max_elem->first << "\" (" << max_elem->second
       << " times)" << endl;
}

// ============== EXAMPLE 5: REMOVE DUPLICATES ==============
void example5_remove_duplicates() {
  cout << "\n============== EXAMPLE 5: REMOVE DUPLICATES =============="
       << endl;
  cout << "Using unordered_set to remove duplicates\n" << endl;

  vector<int> nums = {1, 2, 3, 2, 4, 1, 5, 3, 6, 4};

  cout << "Original: ";
  for (int n : nums)
    cout << n << " ";
  cout << endl;

  // Method 1: Using unordered_set
  unordered_set<int> unique_set(nums.begin(), nums.end());
  vector<int> unique_nums(unique_set.begin(), unique_set.end());

  cout << "After removing duplicates: ";
  for (int n : unique_nums)
    cout << n << " ";
  cout << "\n(Note: order not preserved)" << endl;
}

// ============== EXAMPLE 6: TWO SUM PROBLEM ==============
void example6_two_sum() {
  cout << "\n============== EXAMPLE 6: TWO SUM PROBLEM ==============" << endl;
  cout << "Find two numbers that sum to target\n" << endl;

  vector<int> nums = {2, 7, 11, 15};
  int target = 9;

  cout << "Array: ";
  for (int n : nums)
    cout << n << " ";
  cout << "\nTarget: " << target << endl;

  unordered_map<int, int> seen; // value -> index

  for (int i = 0; i < nums.size(); i++) {
    int complement = target - nums[i];

    if (seen.find(complement) != seen.end()) {
      cout << "\nFound: nums[" << seen[complement] << "] + nums[" << i
           << "] = " << nums[seen[complement]] << " + " << nums[i] << " = "
           << target << endl;
      break;
    }

    seen[nums[i]] = i;
  }

  cout << "\nTime Complexity: O(n) using hash map" << endl;
  cout << "vs O(n²) using nested loops" << endl;
}

// ============== EXAMPLE 7: GROUP ANAGRAMS ==============
void example7_group_anagrams() {
  cout << "\n============== EXAMPLE 7: GROUP ANAGRAMS ==============" << endl;
  cout << "Group words that are anagrams of each other\n" << endl;

  vector<string> words = {"eat", "tea", "tan", "ate", "nat", "bat"};

  unordered_map<string, vector<string>> anagram_groups;

  for (const string &word : words) {
    string key = word;
    sort(key.begin(), key.end()); // Sorted word as key
    anagram_groups[key].push_back(word);
  }

  cout << "Anagram groups:" << endl;
  for (const auto &group : anagram_groups) {
    cout << "  [";
    for (size_t i = 0; i < group.second.size(); i++) {
      cout << group.second[i];
      if (i < group.second.size() - 1)
        cout << ", ";
    }
    cout << "]" << endl;
  }
}

// ============== EXAMPLE 8: BUCKET INTERFACE ==============
void example8_bucket_interface() {
  cout << "\n============== EXAMPLE 8: BUCKET INTERFACE ==============" << endl;
  cout << "Examining internal hash table structure\n" << endl;

  unordered_map<string, int> scores;
  scores["Alice"] = 95;
  scores["Bob"] = 87;
  scores["Charlie"] = 92;
  scores["David"] = 88;

  cout << "Statistics:" << endl;
  cout << "  Size (elements): " << scores.size() << endl;
  cout << "  Bucket count: " << scores.bucket_count() << endl;
  cout << "  Load factor: " << scores.load_factor() << endl;
  cout << "  Max load factor: " << scores.max_load_factor() << endl;

  cout << "\nBucket assignments:" << endl;
  for (const auto &pair : scores) {
    size_t bucket = scores.bucket(pair.first);
    cout << "  \"" << pair.first << "\" in bucket " << bucket << endl;
  }

  cout << "\nBucket sizes:" << endl;
  for (size_t i = 0; i < scores.bucket_count(); i++) {
    size_t bsize = scores.bucket_size(i);
    if (bsize > 0) {
      cout << "  Bucket " << i << ": " << bsize << " element(s)" << endl;
    }
  }
}

// ============== EXAMPLE 9: CUSTOM HASH FOR USER-DEFINED TYPE ==============
struct Person {
  string name;
  int age;

  bool operator==(const Person &other) const {
    return name == other.name && age == other.age;
  }
};

// Custom hash function
struct PersonHash {
  size_t operator()(const Person &p) const {
    // Combine hashes of name and age
    hash<string> str_hash;
    hash<int> int_hash;
    return str_hash(p.name) ^ (int_hash(p.age) << 1);
  }
};

void example9_custom_hash() {
  cout << "\n============== EXAMPLE 9: CUSTOM HASH FUNCTION =============="
       << endl;
  cout << "Using user-defined types in unordered_map\n" << endl;

  unordered_map<Person, string, PersonHash> person_data;

  person_data[Person{"Alice", 25}] = "Engineer";
  person_data[Person{"Bob", 30}] = "Manager";
  person_data[Person{"Charlie", 28}] = "Designer";

  cout << "Person data:" << endl;
  for (const auto &pair : person_data) {
    cout << "  " << pair.first.name << " (" << pair.first.age << ") -> "
         << pair.second << endl;
  }

  cout << "\nNote: Must provide custom hash function AND equality operator"
       << endl;
}

// ============== EXAMPLE 10: CACHING WITH UNORDERED_MAP ==============
class SimpleCache {
private:
  unordered_map<int, int> cache;

  int expensive_computation(int n) {
    // Simulate expensive operation
    return n * n;
  }

public:
  int get(int key) {
    // Check if result is cached
    if (cache.find(key) != cache.end()) {
      cout << "  Cache HIT for " << key << endl;
      return cache[key];
    }

    cout << "  Cache MISS for " << key << " - computing..." << endl;
    int result = expensive_computation(key);
    cache[key] = result; // Store in cache
    return result;
  }

  void clear() { cache.clear(); }
};

void example10_caching() {
  cout << "\n============== EXAMPLE 10: CACHING (MEMOIZATION) =============="
       << endl;
  cout << "Store computed results for fast retrieval\n" << endl;

  SimpleCache cache;

  cout << "First call (will compute):" << endl;
  cout << "  get(5) = " << cache.get(5) << endl;

  cout << "\nSecond call (cached):" << endl;
  cout << "  get(5) = " << cache.get(5) << endl;

  cout << "\nDifferent key (will compute):" << endl;
  cout << "  get(10) = " << cache.get(10) << endl;

  cout << "\nBenefit: Avoid redundant expensive computations!" << endl;
}

// ============== EXAMPLE 11: SET OPERATIONS ==============
void example11_set_operations() {
  cout << "\n============== EXAMPLE 11: SET OPERATIONS ==============" << endl;

  unordered_set<int> set1 = {1, 2, 3, 4, 5};
  unordered_set<int> set2 = {4, 5, 6, 7, 8};

  cout << "Set 1: ";
  for (int x : set1)
    cout << x << " ";
  cout << "\nSet 2: ";
  for (int x : set2)
    cout << x << " ";
  cout << endl;

  // Union
  unordered_set<int> union_set = set1;
  union_set.insert(set2.begin(), set2.end());
  cout << "\nUnion: ";
  for (int x : union_set)
    cout << x << " ";

  // Intersection
  unordered_set<int> intersection;
  for (int x : set1) {
    if (set2.count(x) > 0) {
      intersection.insert(x);
    }
  }
  cout << "\nIntersection: ";
  for (int x : intersection)
    cout << x << " ";

  // Difference (set1 - set2)
  unordered_set<int> difference;
  for (int x : set1) {
    if (set2.count(x) == 0) {
      difference.insert(x);
    }
  }
  cout << "\nDifference (1-2): ";
  for (int x : difference)
    cout << x << " ";
  cout << endl;
}

// ============== EXAMPLE 12: PERFORMANCE COMPARISON ==============
void example12_performance_tips() {
  cout << "\n============== EXAMPLE 12: PERFORMANCE TIPS =============="
       << endl;

  cout << "\n1. RESERVE SPACE (avoid rehashing):" << endl;
  unordered_map<int, int> map1;
  map1.reserve(1000); // Reserve space for 1000 elements
  cout << "  Reserved bucket count: " << map1.bucket_count() << endl;

  cout << "\n2. EMPLACE vs INSERT:" << endl;
  unordered_map<string, string> map2;

  // insert creates temporary pair
  map2.insert({"key1", "value1"});

  // emplace constructs in-place (more efficient)
  map2.emplace("key2", "value2");

  cout << "  Use emplace() for better performance" << endl;

  cout << "\n3. FIND vs COUNT for existence check:" << endl;
  cout << "  find() - returns iterator (can get value)" << endl;
  cout << "  count() - returns 0 or 1 (only check existence)" << endl;
  cout << "  find() is slightly faster for large tables" << endl;

  cout << "\n4. CONST REFERENCES in loops:" << endl;
  cout << "  for (const auto& pair : map) {...}" << endl;
  cout << "  Avoids copying key-value pairs" << endl;
}

int main() {
  cout << "\n======================================================" << endl;
  cout << "     UNORDERED_MAP & UNORDERED_SET TUTORIAL          " << endl;
  cout << "======================================================" << endl;

  example1_basic_unordered_map();
  example2_unordered_vs_ordered();
  example3_basic_unordered_set();
  example4_frequency_counter();
  example5_remove_duplicates();
  example6_two_sum();
  example7_group_anagrams();
  example8_bucket_interface();
  example9_custom_hash();
  example10_caching();
  example11_set_operations();
  example12_performance_tips();

  cout << "\n======================================================" << endl;
  cout << "                   KEY TAKEAWAYS                      " << endl;
  cout << "======================================================" << endl;
  cout << "✓ unordered_map: O(1) avg key-value storage" << endl;
  cout << "✓ unordered_set: O(1) avg unique element storage" << endl;
  cout << "✓ Use map/set when you need sorted order" << endl;
  cout << "✓ Custom types need hash function + equality operator" << endl;
  cout << "✓ Perfect for: frequency counting, caching, deduplication" << endl;
  cout << "✓ reserve() to avoid rehashing" << endl;
  cout << "✓ emplace() more efficient than insert()" << endl;
  cout << "======================================================\n" << endl;

  return 0;
}

/*
 * =====================================================================
 * COMMON MISTAKES TO AVOID
 * =====================================================================
 *
 * 1. USING [] FOR SEARCH
 *    ✗ BAD: if (map["key"]) {...}  // Creates entry if doesn't exist!
 *    ✓ GOOD: if (map.find("key") != map.end()) {...}
 *
 * 2. NOT CHECKING FIND RESULT
 *    ✗ BAD: int val = *map.find(key);  // Crashes if not found!
 *    ✓ GOOD: auto it = map.find(key); if (it != map.end()) val = it->second;
 *
 * 3. MODIFYING KEYS
 *    ✗ BAD: Cannot modify key in map (undefined behavior)
 *    ✓ GOOD: Erase and insert with new key
 *
 * 4. FORGETTING CUSTOM HASH FOR USER TYPES
 *    ✗ BAD: unordered_map<MyClass, int> map;  // Won't compile!
 *    ✓ GOOD: Provide hash function: unordered_map<MyClass, int, MyHash>
 *
 * 5. ASSUMING ORDER
 *    ✗ BAD: Expecting elements in insertion or sorted order
 *    ✓ GOOD: Use map or maintain separate order
 *
 * 6. INEFFICIENT LOOPS
 *    ✗ BAD: for (auto pair : map) {...}  // Copies each pair!
 *    ✓ GOOD: for (const auto& pair : map) {...}
 *
 * 7. USING at() WITHOUT TRY-CATCH
 *    ✗ BAD: int val = map.at("key");  // Throws if missing!
 *    ✓ GOOD: Use find() or wrap in try-catch
 *
 * =====================================================================
 * PRACTICE EXERCISES
 * =====================================================================
 *
 * 1. Find first non-repeating character in a string
 * 2. Check if two strings are anagrams using unordered_map
 * 3. Implement LRU (Least Recently Used) cache
 * 4. Find all pairs with given difference in array
 * 5. Count distinct elements in every window of size k
 * 6. Find itinerary from tickets (origin -> destination pairs)
 * 7. Implement phone directory with prefix search
 * 8. Group students by score ranges using hash map
 * 9. Find longest consecutive sequence in unsorted array
 * 10. Implement word frequency counter with top-k words
 *
 * =====================================================================
 * WHEN TO USE WHAT
 * =====================================================================
 *
 * USE UNORDERED_MAP when:
 *   ✓ Need fast lookups (O(1) average)
 *   ✓ Don't care about order
 *   ✓ Working with large datasets
 *   ✓ Implementing caches, frequency counters
 *
 * USE MAP when:
 *   ✓ Need sorted order
 *   ✓ Need range queries (lower_bound, upper_bound)
 *   ✓ Need guaranteed O(log n) performance
 *   ✓ Keys have natural ordering
 *
 * USE UNORDERED_SET when:
 *   ✓ Only need to track presence/absence
 *   ✓ Removing duplicates
 *   ✓ Fast membership testing
 *
 * USE SET when:
 *   ✓ Need sorted unique elements
 *   ✓ Need ordered iteration
 *   ✓ Implementing priority-like structures
 *
 * =====================================================================
 * COMPILATION AND EXECUTION
 * =====================================================================
 *
 * To compile and run:
 *   g++ -std=c++17 3_unordered_map_unordered_set.cpp -o stl_hash
 *   ./stl_hash
 *
 * =====================================================================
 */
