#include <chrono>
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
 * MAPS vs HASH TABLES - PRACTICAL COMPARISON & ADVANCED EXAMPLES
 * =====================================================================
 *
 * QUICK REFERENCE:
 *
 * std::map (Ordered, BST-based):
 * - Time: O(log n) for insert, delete, find
 * - Space: O(n)
 * - Ordered by key
 * - Predictable performance
 *
 * std::unordered_map (Unordered, Hash Table):
 * - Time: O(1) average, O(n) worst
 * - Space: O(n)
 * - Random order
 * - Better average case, unpredictable worst case
 *
 * std::set vs std::unordered_set (No duplicates):
 * - set: Ordered, O(log n) operations
 * - unordered_set: Unordered, O(1) average operations
 *
 * std::multimap vs std::unordered_multimap (Allow duplicates):
 * - multimap: Ordered, O(log n) operations
 * - unordered_multimap: Unordered, O(1) average operations
 * =====================================================================
 */

int main() {
  cout << "\n========== DETAILED COMPARISON ==========" << endl << endl;

  // ===== 1. ORDERING BEHAVIOR =====
  cout << "1. ORDERING BEHAVIOR" << endl;
  cout << "-------------------------------------------" << endl;

  map<string, int> orderedMap = {
      {"zebra", 1}, {"apple", 2}, {"mango", 3}, {"banana", 4}};
  unordered_map<string, int> unorderedMap = {
      {"zebra", 1}, {"apple", 2}, {"mango", 3}, {"banana", 4}};

  cout << "map<string, int> (SORTED):" << endl;
  for (auto &p : orderedMap) {
    cout << "  " << p.first << " -> " << p.second << endl;
  }
  cout << endl;

  cout << "unordered_map<string, int> (RANDOM ORDER):" << endl;
  for (auto &p : unorderedMap) {
    cout << "  " << p.first << " -> " << p.second << endl;
  }
  cout << endl;

  // ===== 2. WHEN TO USE EACH TYPE =====
  cout << "2. WHEN TO USE EACH TYPE" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "USE std::map WHEN:" << endl;
  cout << "  ✓ You need keys in sorted order" << endl;
  cout << "  ✓ You need predictable O(log n) performance" << endl;
  cout << "  ✓ You need range queries (lower_bound, upper_bound)" << endl;
  cout << "  ✓ Memory efficiency is important" << endl;
  cout << "  ✓ Keys are compared (have comparison operator)" << endl << endl;

  cout << "USE std::unordered_map WHEN:" << endl;
  cout << "  ✓ You need fast O(1) average lookup" << endl;
  cout << "  ✓ Order doesn't matter" << endl;
  cout << "  ✓ You're doing many insert/delete operations" << endl;
  cout << "  ✓ Hash function available for your key type" << endl;
  cout << "  ✓ Simplicity is preferred over order" << endl << endl;

  // ===== 3. PRACTICAL EXAMPLE 1: ANAGRAM GROUPING =====
  cout << "3. EXAMPLE 1: ANAGRAM GROUPING" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "Group anagrams together" << endl;
  cout << "Anagrams: words with same letters rearranged" << endl << endl;

  vector<string> words = {"listen", "silent",   "hello",   "world",
                          "enlist", "desserts", "stressed"};

  // Use map to store sorted letter -> words mapping
  map<string, vector<string>> anagramGroups;

  for (const string &word : words) {
    string sorted_word = word;
    sort(sorted_word.begin(), sorted_word.end());
    anagramGroups[sorted_word].push_back(word);
  }

  cout << "Words to group: ";
  for (auto &w : words)
    cout << w << " ";
  cout << "\n\nAnagram groups:" << endl;
  for (auto &group : anagramGroups) {
    cout << "  [";
    for (int i = 0; i < group.second.size(); i++) {
      cout << group.second[i];
      if (i < group.second.size() - 1)
        cout << ", ";
    }
    cout << "]" << endl;
  }
  cout << endl;

  // ===== 4. PRACTICAL EXAMPLE 2: TWO SUM PROBLEM =====
  cout << "4. EXAMPLE 2: TWO SUM PROBLEM" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "Find all pairs of numbers that sum to a target" << endl;
  cout << "Using unordered_map for O(n) solution" << endl << endl;

  vector<int> numbers = {2, 7, 11, 15, 3, 6, 5};
  int target = 9;

  cout << "Array: ";
  for (int n : numbers)
    cout << n << " ";
  cout << "\nTarget sum: " << target << endl << endl;

  unordered_map<int, int> numMap;
  vector<pair<int, int>> pairs;

  for (int num : numbers) {
    int complement = target - num;
    if (numMap.find(complement) != numMap.end()) {
      pairs.push_back({complement, num});
    }
    numMap[num]++;
  }

  cout << "Pairs that sum to " << target << ":" << endl;
  for (auto &p : pairs) {
    cout << "  (" << p.first << ", " << p.second
         << ") -> sum = " << (p.first + p.second) << endl;
  }
  cout << endl;

  // ===== 5. PRACTICAL EXAMPLE 3: FREQUENCY ANALYZER =====
  cout << "5. EXAMPLE 3: FREQUENCY ANALYZER" << endl;
  cout << "-------------------------------------------" << endl;

  string sentence = "the quick brown fox jumps over the lazy dog and the fox";
  unordered_map<string, int> frequency;

  cout << "Text: \"" << sentence << "\"" << endl << endl;

  string word;
  stringstream ss(sentence);
  while (ss >> word) {
    frequency[word]++;
  }

  cout << "Word frequencies:" << endl;
  for (auto &p : frequency) {
    cout << "  " << p.first << ": " << p.second << " time(s)" << endl;
  }
  cout << endl;

  // ===== 6. PRACTICAL EXAMPLE 4: CACHE IMPLEMENTATION =====
  cout << "6. EXAMPLE 4: SIMPLE CACHE (LRU-like)" << endl;
  cout << "-------------------------------------------" << endl;

  unordered_map<int, string> cache;

  cout << "Caching user data:" << endl;
  cache[101] = "User_Alice";
  cache[102] = "User_Bob";
  cache[103] = "User_Charlie";

  cout << "Cached users: " << cache.size() << endl;

  // Retrieve from cache
  int userId = 102;
  if (cache.find(userId) != cache.end()) {
    cout << "Cache HIT: User " << userId << " -> " << cache[userId] << endl;
  } else {
    cout << "Cache MISS: User " << userId << " not found" << endl;
  }

  userId = 999;
  if (cache.find(userId) != cache.end()) {
    cout << "Cache HIT: User " << userId << " -> " << cache[userId] << endl;
  } else {
    cout << "Cache MISS: User " << userId << " not found" << endl;
  }
  cout << endl;

  // ===== 7. PRACTICAL EXAMPLE 5: URL VALIDATION =====
  cout << "7. EXAMPLE 5: URL VALIDATION" << endl;
  cout << "-------------------------------------------" << endl;

  unordered_set<string> validDomains = {"google.com", "github.com",
                                        "stackoverflow.com", "cppreference.com",
                                        "linkedin.com"};

  vector<string> urlsToCheck = {"github.com", "reddit.com", "google.com",
                                "twitter.com", "cppreference.com"};

  cout << "Valid domains registered: " << validDomains.size() << endl;
  cout << "\nChecking URLs:" << endl;
  for (const string &url : urlsToCheck) {
    bool valid = validDomains.find(url) != validDomains.end();
    cout << "  " << url << " -> " << (valid ? "VALID" : "INVALID") << endl;
  }
  cout << endl;

  // ===== 8. PRACTICAL EXAMPLE 6: SUBSTRING FINDER =====
  cout << "8. EXAMPLE 6: SUBSTRING FINDER" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "Find all characters that appear in first string but not in second"
       << endl;
  string s1 = "characters";
  string s2 = "alphabets";

  unordered_set<char> set1(s1.begin(), s1.end());
  unordered_set<char> set2(s2.begin(), s2.end());

  cout << "String 1: \"" << s1 << "\"" << endl;
  cout << "String 2: \"" << s2 << "\"" << endl << endl;

  cout << "Characters only in first string: ";
  for (char c : set1) {
    if (set2.find(c) == set2.end()) {
      cout << c << " ";
    }
  }
  cout << endl << endl;

  // ===== 9. SET vs UNORDERED_SET =====
  cout << "9. SET vs UNORDERED_SET COMPARISON" << endl;
  cout << "-------------------------------------------" << endl;

  set<int> orderedSet = {5, 2, 8, 1, 9, 3};
  unordered_set<int> unorderedSet = {5, 2, 8, 1, 9, 3};

  cout << "set<int> (SORTED, no duplicates):" << endl;
  for (int n : orderedSet)
    cout << n << " ";
  cout << endl << endl;

  cout << "unordered_set<int> (RANDOM, no duplicates):" << endl;
  for (int n : unorderedSet)
    cout << n << " ";
  cout << endl << endl;

  // ===== 10. MULTIMAP vs UNORDERED_MULTIMAP =====
  cout << "10. MULTIMAP vs UNORDERED_MULTIMAP" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "Scenario: Phone book with multiple numbers per person" << endl
       << endl;

  multimap<string, string> orderedPhones;
  orderedPhones.insert({"John", "1234567"});
  orderedPhones.insert({"Alice", "9876543"});
  orderedPhones.insert({"John", "7654321"});
  orderedPhones.insert({"Alice", "1111111"});

  cout << "multimap (SORTED by name):" << endl;
  for (auto &p : orderedPhones) {
    cout << "  " << p.first << ": " << p.second << endl;
  }
  cout << endl;

  unordered_multimap<string, string> unorderedPhones;
  unorderedPhones.insert({"John", "1234567"});
  unorderedPhones.insert({"Alice", "9876543"});
  unorderedPhones.insert({"John", "7654321"});
  unorderedPhones.insert({"Alice", "1111111"});

  cout << "unordered_multimap (RANDOM order):" << endl;
  for (auto &p : unorderedPhones) {
    cout << "  " << p.first << ": " << p.second << endl;
  }
  cout << endl;

  // ===== 11. CHOOSING CORRECT CONTAINER =====
  cout << "11. CONTAINER SELECTION GUIDE" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "Need unique keys, ordered:" << endl;
  cout << "  → Use std::map or std::set" << endl << endl;

  cout << "Need unique keys, fast lookup:" << endl;
  cout << "  → Use std::unordered_map or std::unordered_set" << endl << endl;

  cout << "Need duplicate keys, ordered:" << endl;
  cout << "  → Use std::multimap or std::multiset" << endl << endl;

  cout << "Need duplicate keys, fast lookup:" << endl;
  cout << "  → Use std::unordered_multimap or std::unordered_multiset" << endl
       << endl;

  cout << "Need single values (no pairs):" << endl;
  cout << "  → Use std::set or std::unordered_set" << endl << endl;

  cout << "Need key-value pairs:" << endl;
  cout << "  → Use std::map or std::unordered_map" << endl << endl;

  // ===== 12. PERFORMANCE NOTES =====
  cout << "12. PERFORMANCE SUMMARY TABLE" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "Container            | Insert | Delete | Find   | Order" << endl;
  cout << "-----                | ------ | ------ | ------ | -----" << endl;
  cout << "map                  | O(logn)| O(logn)| O(logn)| Sorted" << endl;
  cout << "unordered_map        | O(1)   | O(1)   | O(1)   | Random" << endl;
  cout << "multimap             | O(logn)| O(logn)| O(logn)| Sorted" << endl;
  cout << "unordered_multimap   | O(1)   | O(1)   | O(1)   | Random" << endl;
  cout << "set                  | O(logn)| O(logn)| O(logn)| Sorted" << endl;
  cout << "unordered_set        | O(1)   | O(1)   | O(1)   | Random" << endl;
  cout << endl;

  cout << "Note: O(1) is average case. Worst case is O(n) for hash containers"
       << endl;
  cout << "      if many collisions occur." << endl;

  return 0;
}
