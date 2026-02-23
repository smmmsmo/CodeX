#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
using namespace std;

/*
 * =====================================================================
 * MAPS IN C++ - COMPREHENSIVE TUTORIAL
 * =====================================================================
 *
 * WHAT ARE MAPS?
 * Maps are associative containers that store key-value pairs.
 * Each key is unique and maps to exactly one value.
 *
 * KEY CONCEPTS:
 * - Key: The identifier/index (must be unique)
 * - Value: The data associated with the key
 * - Pair: A key-value combination
 *
 * TWO MAIN TYPES:
 * 1. std::map - Ordered map (sorted by key)
 * 2. std::unordered_map - Unordered map (uses hash table internally)
 *
 * TWO VARIANTS:
 * 3. std::multimap - Map allowing duplicate keys
 * 4. std::unordered_multimap - Unordered map with duplicate keys
 * =====================================================================
 */

// Example struct for learning
struct Person {
  string name;
  int age;
  string city;

  Person() {}
  Person(string n, int a, string c) : name(n), age(a), city(c) {}
};

int main() {
  cout << "\n========== STD::MAP TUTORIAL ==========" << endl;
  cout << "ORDERED MAP - Sorted by Key" << endl << endl;

  // ===== 1. std::map - BASIC OPERATIONS =====
  cout << "1. CREATING AND INSERTING INTO std::map" << endl;
  cout << "-------------------------------------------" << endl;

  map<int, string> studentMap; // Key: int (ID), Value: string (Name)

  // Method 1: Using insert()
  studentMap.insert({101, "Alice"});
  studentMap.insert({103, "Charlie"});
  studentMap.insert({102, "Bob"});

  // Method 2: Using bracket notation
  studentMap[104] = "David";
  studentMap[100] = "Eve";

  cout << "Map contents (automatically sorted by key):" << endl;
  for (auto &pair : studentMap) {
    cout << "ID: " << pair.first << " -> Name: " << pair.second << endl;
  }
  cout << endl;

  // ===== 2. ACCESSING ELEMENTS =====
  cout << "2. ACCESSING ELEMENTS FROM std::map" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "Using [] operator: studentMap[102] = " << studentMap[102] << endl;

  cout << "Using .at() method (with bounds checking): ";
  try {
    cout << "studentMap.at(103) = " << studentMap.at(103) << endl;
  } catch (out_of_range &e) {
    cout << "Key not found!" << endl;
  }

  cout << "Using .find() method:" << endl;
  auto it = studentMap.find(101);
  if (it != studentMap.end()) {
    cout << "Found! ID: " << it->first << " -> Name: " << it->second << endl;
  } else {
    cout << "Not found!" << endl;
  }
  cout << endl;

  // ===== 3. SIZE AND EMPTY CHECKS =====
  cout << "3. SIZE AND CHECKS" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "Map size: " << studentMap.size() << endl;
  cout << "Is empty? " << (studentMap.empty() ? "Yes" : "No") << endl;
  cout << "Count of key 102: " << studentMap.count(102) << " (0 or 1 for map)"
       << endl;
  cout << endl;

  // ===== 4. MODIFYING ELEMENTS =====
  cout << "4. MODIFYING ELEMENTS" << endl;
  cout << "-------------------------------------------" << endl;

  studentMap[102] = "Robert"; // Update existing value
  cout << "After updating ID 102 to 'Robert': " << studentMap[102] << endl;

  cout << "All entries after modification:" << endl;
  for (auto &p : studentMap) {
    cout << p.first << " -> " << p.second << endl;
  }
  cout << endl;

  // ===== 5. REMOVING ELEMENTS =====
  cout << "5. REMOVING ELEMENTS" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "Before erase - Size: " << studentMap.size() << endl;
  studentMap.erase(100); // Remove by key
  cout << "After erasing ID 100 - Size: " << studentMap.size() << endl;

  cout << "Remaining entries:" << endl;
  for (auto &p : studentMap) {
    cout << p.first << " -> " << p.second << endl;
  }
  cout << endl;

  // ===== 6. STRING KEYS =====
  cout << "6. MAP WITH STRING KEYS" << endl;
  cout << "-------------------------------------------" << endl;

  map<string, int> ageMap;
  ageMap["Alice"] = 25;
  ageMap["Bob"] = 30;
  ageMap["Charlie"] = 28;
  ageMap["David"] = 35;

  cout << "Age Map (sorted alphabetically by name):" << endl;
  for (auto &p : ageMap) {
    cout << p.first << " -> " << p.second << " years old" << endl;
  }
  cout << endl;

  // ===== 7. MAP WITH COMPLEX VALUES (OBJECTS) =====
  cout << "7. MAP WITH COMPLEX VALUES (OBJECTS)" << endl;
  cout << "-------------------------------------------" << endl;

  map<int, Person> peopleMap;
  peopleMap[1] = Person("Alice Johnson", 25, "New York");
  peopleMap[2] = Person("Bob Smith", 30, "Los Angeles");
  peopleMap[3] = Person("Charlie Brown", 28, "Chicago");

  cout << "People Map:" << endl;
  for (auto &p : peopleMap) {
    cout << "ID: " << p.first << " -> Name: " << p.second.name
         << ", Age: " << p.second.age << ", City: " << p.second.city << endl;
  }
  cout << endl;

  // ===== 8. ITERATING THROUGH MAPS =====
  cout << "8. DIFFERENT WAYS TO ITERATE" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "Range-based for loop:" << endl;
  for (auto &[key, value] : ageMap) {
    cout << key << ": " << value << endl;
  }
  cout << endl;

  cout << "Using iterator:" << endl;
  for (auto it = ageMap.begin(); it != ageMap.end(); it++) {
    cout << it->first << ": " << it->second << endl;
  }
  cout << endl;

  cout << "Using const_iterator (read-only):" << endl;
  for (auto it = ageMap.cbegin(); it != ageMap.cend(); it++) {
    cout << it->first << ": " << it->second << endl;
  }
  cout << endl;

  // ===== 9. MULTIMAP - ALLOWING DUPLICATE KEYS =====
  cout << "\n========== STD::MULTIMAP TUTORIAL ==========" << endl;
  cout << "ALLOWS MULTIPLE VALUES FOR SAME KEY" << endl << endl;

  cout << "1. CREATING AND INSERTING INTO std::multimap" << endl;
  cout << "-------------------------------------------" << endl;

  multimap<string, int> phoneBook;
  phoneBook.insert({"John", 1234567});
  phoneBook.insert({"John", 7654321}); // Same key, different value!
  phoneBook.insert({"Mary", 9876543});
  phoneBook.insert({"Alice", 1111111});
  phoneBook.insert({"John", 5555555}); // Third value for "John"

  cout << "Phone Book (allows duplicate names):" << endl;
  for (auto &p : phoneBook) {
    cout << p.first << " -> " << p.second << endl;
  }
  cout << endl;

  cout << "2. FINDING ALL VALUES FOR A KEY IN MULTIMAP" << endl;
  cout << "-------------------------------------------" << endl;

  cout << "All phone numbers for John:" << endl;
  auto range = phoneBook.equal_range("John");
  for (auto it = range.first; it != range.second; it++) {
    cout << "  " << it->second << endl;
  }

  cout << "Count of entries with key 'John': " << phoneBook.count("John")
       << endl;
  cout << endl;

  // ===== 10. UNORDERED_MAP - FAST LOOKUP (USES HASH TABLE) =====
  cout << "\n========== STD::UNORDERED_MAP TUTORIAL ==========" << endl;
  cout << "UNORDERED - Uses HASH TABLE internally" << endl;
  cout << "Better performance for lookup, insert, delete (O(1) average)"
       << endl;
  cout << "Order is not guaranteed" << endl << endl;

  cout << "1. CREATING UNORDERED_MAP" << endl;
  cout << "-------------------------------------------" << endl;

  unordered_map<string, int> scoreBoard;
  scoreBoard["Alice"] = 95;
  scoreBoard["Bob"] = 87;
  scoreBoard["Charlie"] = 92;
  scoreBoard["David"] = 88;

  cout << "Scoreboard (order may vary due to hashing):" << endl;
  for (auto &p : scoreBoard) {
    cout << p.first << " -> " << p.second << endl;
  }
  cout << endl;

  cout << "2. PERFORMANCE COMPARISON" << endl;
  cout << "-------------------------------------------" << endl;
  cout << "std::map: O(log n) for insert, delete, find - Ordered" << endl;
  cout
      << "std::unordered_map: O(1) average, O(n) worst for insert, delete, find"
      << endl;
  cout << "                    - Unordered, uses hash table" << endl;
  cout << endl;

  // ===== 11. PRACTICAL EXAMPLES =====
  cout << "11. PRACTICAL EXAMPLES" << endl;
  cout << "-------------------------------------------" << endl;

  // Example 1: Word frequency counter
  cout << "Example 1: Word Frequency Counter" << endl;
  unordered_map<string, int> wordCount;
  string words[] = {"apple", "banana", "apple", "orange", "banana", "apple"};

  for (string word : words) {
    wordCount[word]++; // Increment count, creates entry if not exists
  }

  cout << "Word frequencies:" << endl;
  for (auto &p : wordCount) {
    cout << p.first << ": " << p.second << " times" << endl;
  }
  cout << endl;

  // Example 2: Grade mapping
  cout << "Example 2: Numeric Grade to Letter Grade" << endl;
  map<int, char> gradeMap;
  gradeMap[95] = 'A';
  gradeMap[87] = 'B';
  gradeMap[92] = 'A';
  gradeMap[88] = 'B';
  gradeMap[78] = 'C';

  cout << "Grades (sorted by numeric value):" << endl;
  for (auto &p : gradeMap) {
    cout << p.first << " -> " << p.second << endl;
  }
  cout << endl;

  // ===== 12. CLEAR AND OTHER OPERATIONS =====
  cout << "12. OTHER USEFUL OPERATIONS" << endl;
  cout << "-------------------------------------------" << endl;

  map<int, string> tempMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  cout << "Original map size: " << tempMap.size() << endl;

  tempMap.clear();
  cout << "After clear(): size = " << tempMap.size() << endl;
  cout << "Is empty? " << (tempMap.empty() ? "Yes" : "No") << endl;
  cout << endl;

  // ===== 13. BOUNDS - LOWER_BOUND AND UPPER_BOUND =====
  cout << "13. LOWER_BOUND AND UPPER_BOUND" << endl;
  cout << "-------------------------------------------" << endl;

  map<int, string> boundMap = {
      {1, "one"}, {3, "three"}, {5, "five"}, {7, "seven"}};

  cout << "Map: 1->one, 3->three, 5->five, 7->seven" << endl;

  auto lower = boundMap.lower_bound(4);
  cout << "lower_bound(4): " << lower->first << " -> " << lower->second << endl;

  auto upper = boundMap.upper_bound(4);
  cout << "upper_bound(4): " << upper->first << " -> " << upper->second << endl;
  cout << endl;

  return 0;
}
