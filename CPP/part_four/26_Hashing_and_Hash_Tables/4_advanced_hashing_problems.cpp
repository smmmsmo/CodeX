#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
 * =====================================================================
 * TOPIC 26.4: ADVANCED HASHING & PRACTICAL PROBLEMS
 * =====================================================================
 *
 * This file covers advanced hashing techniques and real-world problems
 * that are commonly solved using hash tables.
 *
 * KEY CONCEPTS COVERED:
 * 1. Rolling hash (Rabin-Karp algorithm)
 * 2. Consistent hashing
 * 3. Bloom filters (concept)
 * 4. Common interview problems
 * 5. Optimization techniques
 * 6. Real-world applications
 *
 * =====================================================================
 * ADVANCED HASHING TECHNIQUES
 * =====================================================================
 *
 * 1. ROLLING HASH
 *    - Update hash in O(1) when sliding window moves
 *    - Used in pattern matching, substring search
 *
 * 2. POLYNOMIAL HASH
 *    - hash(s) = s[0]*p^0 + s[1]*p^1 + ... + s[n-1]*p^(n-1)
 *    - p is prime (31, 53, etc.)
 *
 * 3. CONSISTENT HASHING
 *    - Minimizes redistribution when adding/removing nodes
 *    - Used in distributed systems
 *
 * 4. BLOOM FILTERS
 *    - Space-efficient probabilistic data structure
 *    - Can have false positives, but no false negatives
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: ROLLING HASH (RABIN-KARP) ==============
class RollingHash {
private:
  const long long MOD = 1e9 + 7;
  const long long BASE = 31;

public:
  // Compute hash of string
  long long compute_hash(const string &s) {
    long long hash_value = 0;
    long long pow_base = 1;

    for (char c : s) {
      hash_value = (hash_value + (c - 'a' + 1) * pow_base) % MOD;
      pow_base = (pow_base * BASE) % MOD;
    }

    return hash_value;
  }

  // Find pattern in text using rolling hash
  vector<int> search(const string &text, const string &pattern) {
    vector<int> positions;
    int n = text.length();
    int m = pattern.length();

    if (m > n)
      return positions;

    long long pattern_hash = compute_hash(pattern);
    long long text_hash = compute_hash(text.substr(0, m));

    // Check first window
    if (pattern_hash == text_hash && text.substr(0, m) == pattern) {
      positions.push_back(0);
    }

    // Rolling hash for remaining windows
    long long pow_base = 1;
    for (int i = 0; i < m - 1; i++) {
      pow_base = (pow_base * BASE) % MOD;
    }

    for (int i = m; i < n; i++) {
      // Remove leftmost character
      text_hash = (text_hash - (text[i - m] - 'a' + 1)) % MOD;
      if (text_hash < 0)
        text_hash += MOD;
      text_hash = (text_hash * BASE) % MOD;

      // Add rightmost character
      text_hash = (text_hash + (text[i] - 'a' + 1)) % MOD;

      // Check if hashes match
      if (pattern_hash == text_hash) {
        // Verify actual match (avoid hash collision)
        if (text.substr(i - m + 1, m) == pattern) {
          positions.push_back(i - m + 1);
        }
      }
    }

    return positions;
  }
};

void example1_rolling_hash() {
  cout << "\n============== EXAMPLE 1: ROLLING HASH (RABIN-KARP) =============="
       << endl;
  cout << "Efficient pattern matching using rolling hash\n" << endl;

  string text = "ababcababa";
  string pattern = "aba";

  RollingHash rh;
  vector<int> positions = rh.search(text, pattern);

  cout << "Text: \"" << text << "\"" << endl;
  cout << "Pattern: \"" << pattern << "\"" << endl;
  cout << "\nPattern found at positions: ";
  for (int pos : positions) {
    cout << pos << " ";
  }
  cout << endl;

  cout << "\nTime Complexity: O(n + m) average" << endl;
  cout << "where n = text length, m = pattern length" << endl;
}

// ============== EXAMPLE 2: LONGEST SUBSTRING WITHOUT REPEATING ==============
void example2_longest_substring() {
  cout << "\n============== EXAMPLE 2: LONGEST SUBSTRING WITHOUT REPEATING "
          "=============="
       << endl;
  cout << "Find length of longest substring with unique characters\n" << endl;

  string s = "abcabcbb";

  unordered_map<char, int> last_seen;
  int max_len = 0;
  int start = 0;

  cout << "String: \"" << s << "\"" << endl;
  cout << "\nSliding window process:" << endl;

  for (int end = 0; end < s.length(); end++) {
    char c = s[end];

    // If character seen before in current window
    if (last_seen.find(c) != last_seen.end() && last_seen[c] >= start) {
      start = last_seen[c] + 1; // Move start past duplicate
    }

    last_seen[c] = end;
    max_len = max(max_len, end - start + 1);

    if (end < 10) { // Print first few iterations
      cout << "  [" << start << ":" << end << "] \""
           << s.substr(start, end - start + 1) << "\" len=" << (end - start + 1)
           << endl;
    }
  }

  cout << "\nLongest substring length: " << max_len << endl;
  cout << "Time Complexity: O(n)" << endl;
}

// ============== EXAMPLE 3: SUBARRAY SUM EQUALS K ==============
void example3_subarray_sum() {
  cout << "\n============== EXAMPLE 3: SUBARRAY SUM EQUALS K =============="
       << endl;
  cout << "Count subarrays with sum equal to k\n" << endl;

  vector<int> nums = {1, 2, 3, -2, 5};
  int k = 5;

  cout << "Array: ";
  for (int n : nums)
    cout << n << " ";
  cout << "\nTarget sum k = " << k << endl;

  unordered_map<int, int> prefix_sum_count;
  prefix_sum_count[0] = 1; // Base case: empty subarray

  int count = 0;
  int curr_sum = 0;

  cout << "\nProcess:" << endl;
  for (int i = 0; i < nums.size(); i++) {
    curr_sum += nums[i];

    // Check if (curr_sum - k) exists in map
    // This means there's a subarray with sum k
    if (prefix_sum_count.find(curr_sum - k) != prefix_sum_count.end()) {
      count += prefix_sum_count[curr_sum - k];
      cout << "  Found subarray ending at index " << i << endl;
    }

    prefix_sum_count[curr_sum]++;
  }

  cout << "\nTotal subarrays with sum " << k << ": " << count << endl;
  cout << "Time Complexity: O(n)" << endl;
}

// ============== EXAMPLE 4: FOUR SUM PROBLEM ==============
void example4_four_sum() {
  cout << "\n============== EXAMPLE 4: FOUR SUM (USING PAIRS) =============="
       << endl;
  cout << "Find if there exist 4 elements that sum to target\n" << endl;

  vector<int> nums = {1, 2, 3, 4, 5, 6};
  int target = 14;

  cout << "Array: ";
  for (int n : nums)
    cout << n << " ";
  cout << "\nTarget: " << target << endl;

  // Store sum of pairs
  unordered_map<int, pair<int, int>> pair_sums;

  // Generate all pair sums
  for (int i = 0; i < nums.size(); i++) {
    for (int j = i + 1; j < nums.size(); j++) {
      int sum = nums[i] + nums[j];
      pair_sums[sum] = {i, j};
    }
  }

  // Find complementary pairs
  bool found = false;
  for (auto &[sum1, indices1] : pair_sums) {
    int sum2 = target - sum1;

    if (pair_sums.find(sum2) != pair_sums.end()) {
      auto indices2 = pair_sums[sum2];

      // Ensure no index overlap
      if (indices1.first != indices2.first &&
          indices1.first != indices2.second &&
          indices1.second != indices2.first &&
          indices1.second != indices2.second) {

        cout << "\nFound: " << nums[indices1.first] << " + "
             << nums[indices1.second] << " + " << nums[indices2.first] << " + "
             << nums[indices2.second] << " = " << target << endl;
        found = true;
        break;
      }
    }
  }

  if (!found) {
    cout << "\nNo four elements sum to " << target << endl;
  }

  cout << "\nTime Complexity: O(n²)" << endl;
}

// ============== EXAMPLE 5: LRU CACHE ==============
class LRUCache {
private:
  struct Node {
    int key, value;
    Node *prev, *next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
  };

  int capacity;
  unordered_map<int, Node *> cache;
  Node *head, *tail;

  void add_to_front(Node *node) {
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
  }

  void remove_node(Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void move_to_front(Node *node) {
    remove_node(node);
    add_to_front(node);
  }

public:
  LRUCache(int cap) : capacity(cap) {
    head = new Node(0, 0);
    tail = new Node(0, 0);
    head->next = tail;
    tail->prev = head;
  }

  int get(int key) {
    if (cache.find(key) == cache.end()) {
      return -1;
    }

    Node *node = cache[key];
    move_to_front(node);
    return node->value;
  }

  void put(int key, int value) {
    if (cache.find(key) != cache.end()) {
      // Update existing
      Node *node = cache[key];
      node->value = value;
      move_to_front(node);
    } else {
      // Add new
      Node *node = new Node(key, value);
      cache[key] = node;
      add_to_front(node);

      if (cache.size() > capacity) {
        // Remove LRU
        Node *lru = tail->prev;
        remove_node(lru);
        cache.erase(lru->key);
        delete lru;
      }
    }
  }

  void display() {
    cout << "Cache: ";
    Node *curr = head->next;
    while (curr != tail) {
      cout << "(" << curr->key << ":" << curr->value << ") ";
      curr = curr->next;
    }
    cout << endl;
  }
};

void example5_lru_cache() {
  cout << "\n============== EXAMPLE 5: LRU CACHE ==============" << endl;
  cout << "Least Recently Used cache with O(1) operations\n" << endl;

  LRUCache cache(3); // Capacity = 3

  cout << "Operations:" << endl;
  cache.put(1, 10);
  cout << "put(1, 10): ";
  cache.display();

  cache.put(2, 20);
  cout << "put(2, 20): ";
  cache.display();

  cache.put(3, 30);
  cout << "put(3, 30): ";
  cache.display();

  cout << "get(1) = " << cache.get(1) << endl;
  cache.display();

  cache.put(4, 40); // Evicts key 2
  cout << "put(4, 40): ";
  cache.display();

  cout << "\nget(2) = " << cache.get(2) << " (evicted)" << endl;

  cout
      << "\nCombines: Hash map (O(1) lookup) + Doubly linked list (O(1) update)"
      << endl;
}

// ============== EXAMPLE 6: VALID SUDOKU ==============
void example6_valid_sudoku() {
  cout << "\n============== EXAMPLE 6: VALID SUDOKU CHECKER =============="
       << endl;
  cout << "Check if partially filled Sudoku is valid\n" << endl;

  vector<vector<char>> board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  unordered_set<string> seen;
  bool valid = true;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      char num = board[i][j];
      if (num == '.')
        continue;

      string row_key = "row" + to_string(i) + num;
      string col_key = "col" + to_string(j) + num;
      string box_key = "box" + to_string(i / 3 * 3 + j / 3) + num;

      if (seen.count(row_key) || seen.count(col_key) || seen.count(box_key)) {
        valid = false;
        break;
      }

      seen.insert(row_key);
      seen.insert(col_key);
      seen.insert(box_key);
    }
    if (!valid)
      break;
  }

  cout << "Sudoku is " << (valid ? "VALID" : "INVALID") << endl;
  cout << "\nUsing hash set to track seen numbers in rows/cols/boxes" << endl;
  cout << "Time Complexity: O(1) - board is always 9×9" << endl;
}

// ============== EXAMPLE 7: LONGEST CONSECUTIVE SEQUENCE ==============
void example7_longest_consecutive() {
  cout << "\n============== EXAMPLE 7: LONGEST CONSECUTIVE SEQUENCE "
          "=============="
       << endl;
  cout << "Find length of longest consecutive sequence in O(n)\n" << endl;

  vector<int> nums = {100, 4, 200, 1, 3, 2};

  cout << "Array: ";
  for (int n : nums)
    cout << n << " ";
  cout << endl;

  unordered_set<int> num_set(nums.begin(), nums.end());
  int max_length = 0;

  for (int num : num_set) {
    // Only start sequence if num-1 doesn't exist
    if (num_set.find(num - 1) == num_set.end()) {
      int current = num;
      int length = 1;

      // Extend sequence
      while (num_set.find(current + 1) != num_set.end()) {
        current++;
        length++;
      }

      max_length = max(max_length, length);

      if (length > 1) {
        cout << "Sequence found: " << num << " to " << current << " (length "
             << length << ")" << endl;
      }
    }
  }

  cout << "\nLongest consecutive sequence length: " << max_length << endl;
  cout << "Time Complexity: O(n)" << endl;
}

// ============== EXAMPLE 8: ISOMORPHIC STRINGS ==============
void example8_isomorphic_strings() {
  cout << "\n============== EXAMPLE 8: ISOMORPHIC STRINGS =============="
       << endl;
  cout << "Check if two strings are isomorphic (character mapping exists)\n"
       << endl;

  string s = "egg";
  string t = "add";

  cout << "s = \"" << s << "\"" << endl;
  cout << "t = \"" << t << "\"" << endl;

  if (s.length() != t.length()) {
    cout << "Not isomorphic (different lengths)" << endl;
    return;
  }

  unordered_map<char, char> s_to_t;
  unordered_map<char, char> t_to_s;

  bool isomorphic = true;

  for (int i = 0; i < s.length(); i++) {
    char c1 = s[i], c2 = t[i];

    if (s_to_t.count(c1) && s_to_t[c1] != c2) {
      isomorphic = false;
      break;
    }

    if (t_to_s.count(c2) && t_to_s[c2] != c1) {
      isomorphic = false;
      break;
    }

    s_to_t[c1] = c2;
    t_to_s[c2] = c1;
  }

  cout << "\nMapping: ";
  for (auto &p : s_to_t) {
    cout << p.first << "->" << p.second << " ";
  }
  cout << endl;

  cout << "Result: " << (isomorphic ? "ISOMORPHIC" : "NOT ISOMORPHIC") << endl;
  cout << "Time Complexity: O(n)" << endl;
}

// ============== EXAMPLE 9: TOP K FREQUENT ELEMENTS ==============
void example9_top_k_frequent() {
  cout << "\n============== EXAMPLE 9: TOP K FREQUENT ELEMENTS =============="
       << endl;
  cout << "Find k most frequent elements\n" << endl;

  vector<int> nums = {1, 1, 1, 2, 2, 3, 3, 3, 3, 4};
  int k = 2;

  cout << "Array: ";
  for (int n : nums)
    cout << n << " ";
  cout << "\nk = " << k << endl;

  // Count frequencies
  unordered_map<int, int> freq;
  for (int num : nums) {
    freq[num]++;
  }

  // Bucket sort by frequency
  vector<vector<int>> buckets(nums.size() + 1);
  for (auto &p : freq) {
    buckets[p.second].push_back(p.first);
  }

  // Collect top k
  vector<int> result;
  for (int i = buckets.size() - 1; i >= 0 && result.size() < k; i--) {
    for (int num : buckets[i]) {
      result.push_back(num);
      if (result.size() == k)
        break;
    }
  }

  cout << "\nTop " << k << " frequent elements: ";
  for (int n : result)
    cout << n << " ";
  cout << endl;

  cout << "Time Complexity: O(n)" << endl;
}

// ============== EXAMPLE 10: DESIGN HASHSET ==============
class MyHashSet {
private:
  static const int SIZE = 1000;
  vector<vector<int>> buckets;

  int hash(int key) { return key % SIZE; }

public:
  MyHashSet() : buckets(SIZE) {}

  void add(int key) {
    int bucket = hash(key);
    if (find(buckets[bucket].begin(), buckets[bucket].end(), key) ==
        buckets[bucket].end()) {
      buckets[bucket].push_back(key);
    }
  }

  void remove(int key) {
    int bucket = hash(key);
    auto it = find(buckets[bucket].begin(), buckets[bucket].end(), key);
    if (it != buckets[bucket].end()) {
      buckets[bucket].erase(it);
    }
  }

  bool contains(int key) {
    int bucket = hash(key);
    return find(buckets[bucket].begin(), buckets[bucket].end(), key) !=
           buckets[bucket].end();
  }
};

void example10_design_hashset() {
  cout << "\n============== EXAMPLE 10: DESIGN HASHSET FROM SCRATCH "
          "=============="
       << endl;
  cout << "Implement HashSet without using built-in library\n" << endl;

  MyHashSet hashSet;

  hashSet.add(1);
  hashSet.add(2);
  cout << "Added 1, 2" << endl;

  cout << "contains(1): " << (hashSet.contains(1) ? "true" : "false") << endl;
  cout << "contains(3): " << (hashSet.contains(3) ? "true" : "false") << endl;

  hashSet.add(2);
  cout << "Added 2 again (duplicate)" << endl;

  cout << "contains(2): " << (hashSet.contains(2) ? "true" : "false") << endl;

  hashSet.remove(2);
  cout << "Removed 2" << endl;

  cout << "contains(2): " << (hashSet.contains(2) ? "true" : "false") << endl;

  cout << "\nImplementation uses chaining for collision resolution" << endl;
}

int main() {
  cout << "\n======================================================" << endl;
  cout << "      ADVANCED HASHING & PRACTICAL PROBLEMS          " << endl;
  cout << "======================================================" << endl;

  example1_rolling_hash();
  example2_longest_substring();
  example3_subarray_sum();
  example4_four_sum();
  example5_lru_cache();
  example6_valid_sudoku();
  example7_longest_consecutive();
  example8_isomorphic_strings();
  example9_top_k_frequent();
  example10_design_hashset();

  cout << "\n======================================================" << endl;
  cout << "                   KEY TAKEAWAYS                      " << endl;
  cout << "======================================================" << endl;
  cout << "✓ Rolling hash enables O(1) window updates" << endl;
  cout << "✓ Hash maps solve many O(n²) problems in O(n)" << endl;
  cout << "✓ LRU cache combines hash map + doubly linked list" << endl;
  cout << "✓ Use hash sets for uniqueness and membership checks" << endl;
  cout << "✓ Prefix sums + hash map for subarray problems" << endl;
  cout << "✓ Frequency counting is a classic hash map pattern" << endl;
  cout << "✓ String encoding helps with complex key structures" << endl;
  cout << "======================================================\n" << endl;

  return 0;
}

/*
 * =====================================================================
 * COMMON INTERVIEW PROBLEMS USING HASHING
 * =====================================================================
 *
 * EASY:
 * 1. Two Sum
 * 2. Contains Duplicate
 * 3. Valid Anagram
 * 4. First Unique Character in String
 * 5. Intersection of Two Arrays
 * 6. Happy Number
 * 7. Isomorphic Strings
 * 8. Word Pattern
 *
 * MEDIUM:
 * 1. Group Anagrams
 * 2. Top K Frequent Elements
 * 3. Longest Substring Without Repeating Characters
 * 4. Subarray Sum Equals K
 * 5. Longest Consecutive Sequence
 * 6. 4Sum
 * 7. Encode and Decode TinyURL
 * 8. Design HashMap
 * 9. LRU Cache
 * 10. Valid Sudoku
 *
 * HARD:
 * 1. Substring with Concatenation of All Words
 * 2. Minimum Window Substring
 * 3. Longest Duplicate Substring
 * 4. Find All Duplicates in Array
 * 5. Largest Rectangle in Histogram
 *
 * =====================================================================
 * PROBLEM-SOLVING PATTERNS
 * =====================================================================
 *
 * PATTERN 1: FREQUENCY COUNTING
 *   - Count occurrences of elements
 *   - Use unordered_map<element, count>
 *   - Examples: Character frequency, word frequency
 *
 * PATTERN 2: TWO/THREE/FOUR SUM
 *   - Find pairs/triplets that meet condition
 *   - Use hash map to store complements
 *   - Examples: Two Sum, 3Sum with hash map optimization
 *
 * PATTERN 3: SLIDING WINDOW + HASH
 *   - Maintain window with hash map/set
 *   - Track characters/elements in current window
 *   - Examples: Longest substring, minimum window
 *
 * PATTERN 4: PREFIX SUM + HASH
 *   - Store prefix sums in hash map
 *   - Find subarrays with specific sum
 *   - Examples: Subarray sum equals K, contiguous array
 *
 * PATTERN 5: STRING ENCODING
 *   - Convert complex state to string key
 *   - Use in hash map for memoization
 *   - Examples: Valid Sudoku, serialize state
 *
 * PATTERN 6: CACHING/MEMOIZATION
 *   - Store computed results
 *   - Avoid redundant calculations
 *   - Examples: LRU cache, Fibonacci with memoization
 *
 * =====================================================================
 * OPTIMIZATION TECHNIQUES
 * =====================================================================
 *
 * 1. CHOOSE RIGHT DATA STRUCTURE
 *    - unordered_map: When you need key-value mapping
 *    - unordered_set: When you only need membership testing
 *    - map/set: When you need ordering
 *
 * 2. RESERVE SPACE
 *    map.reserve(expected_size);  // Avoid rehashing
 *
 * 3. USE EMPLACE
 *    map.emplace(key, value);  // Construct in-place
 *
 * 4. CONST REFERENCES IN LOOPS
 *    for (const auto& pair : map) {...}  // Avoid copies
 *
 * 5. CHOOSE GOOD HASH FUNCTION
 *    - Avoid collisions
 *    - Distribute uniformly
 *
 * 6. MONITOR LOAD FACTOR
 *    - Keep under 0.75 for open addressing
 *    - Rehash if needed
 *
 * =====================================================================
 * PRACTICE EXERCISES
 * =====================================================================
 *
 * 1. Implement custom HashMap class from scratch
 * 2. Find all anagrams in a string
 * 3. Implement consistent hashing algorithm
 * 4. Design time-based key-value store
 * 5. Find minimum window substring containing all characters
 * 6. Implement bloom filter
 * 7. Design underground system (metro card system)
 * 8. Find all substring concatenations
 * 9. Implement LFU (Least Frequently Used) cache
 * 10. Serialize and deserialize hash map
 * 11. Find duplicate subtrees in binary tree
 * 12. Random pick with blacklist
 * 13. Design Twitter (hash map + data structures)
 * 14. Alien dictionary (topological sort + hash map)
 * 15. Design search autocomplete system
 *
 * =====================================================================
 * REAL-WORLD APPLICATIONS
 * =====================================================================
 *
 * 1. DATABASES
 *    - Indexing for fast lookups
 *    - Join operations
 *
 * 2. WEB SERVERS
 *    - Session management
 *    - Caching (Redis, Memcached)
 *
 * 3. COMPILERS
 *    - Symbol tables
 *    - Variable scope management
 *
 * 4. NETWORKING
 *    - Routing tables
 *    - DNS resolution
 *
 * 5. SECURITY
 *    - Password storage (hashing)
 *    - Digital signatures
 *
 * 6. DISTRIBUTED SYSTEMS
 *    - Consistent hashing for load balancing
 *    - Distributed caches
 *
 * 7. DATA DEDUPLICATION
 *    - File systems
 *    - Backup systems
 *
 * 8. SEARCH ENGINES
 *    - Inverted index
 *    - URL shortening
 *
 * =====================================================================
 * COMPILATION AND EXECUTION
 * =====================================================================
 *
 * To compile and run:
 *   g++ -std=c++17 4_advanced_hashing_problems.cpp -o advanced_hash
 *   ./advanced_hash
 *
 * =====================================================================
 */
