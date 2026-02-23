#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
 * =====================================================================
 * TOPIC 26.1: HASH FUNCTIONS AND BASICS
 * =====================================================================
 *
 * WHAT IS HASHING?
 * Hashing is a technique to convert data of arbitrary size into a
 * fixed-size output called a HASH CODE or HASH VALUE.
 *
 * KEY CONCEPTS COVERED:
 * 1. Hash Functions - What they are and how they work
 * 2. Properties of good hash functions
 * 3. std::hash in C++
 * 4. Custom hash functions
 * 5. Hash function design principles
 * 6. Distribution and uniformity
 *
 * =====================================================================
 * HASH FUNCTION PROPERTIES
 * =====================================================================
 *
 * A good hash function should have these properties:
 *
 * 1. DETERMINISTIC
 *    - Same input always produces same output
 *    - hash("apple") must always return the same value
 *
 * 2. FAST COMPUTATION
 *    - Should compute quickly (O(1) or O(k) where k is key size)
 *    - Critical for hash table performance
 *
 * 3. UNIFORM DISTRIBUTION
 *    - Spreads data evenly across hash table
 *    - Minimizes collisions
 *    - Good: hash values spread across 0 to N-1
 *    - Bad: All values hash to same bucket
 *
 * 4. AVALANCHE EFFECT
 *    - Small change in input causes large change in output
 *    - hash("apple") vs hash("apples") should be very different
 *    - Prevents clustering
 *
 * 5. CONSISTENT
 *    - Works well for all types of input data
 *    - No worst-case patterns
 *
 * =====================================================================
 * HASH FUNCTION FORMULA
 * =====================================================================
 *
 * For an integer key:
 *    hash(key) = key % table_size
 *
 * For a string key:
 *    hash(string) = (sum of char values * multiplier) % table_size
 *
 * For complex types:
 *    hash(object) = combine(hash(field1), hash(field2), ...)
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: BASIC HASH FUNCTION FOR INTEGERS ==============
void example1_basic_integer_hash() {
  cout << "\n============== EXAMPLE 1: INTEGER HASH FUNCTION =============="
       << endl;
  cout << "Simple hash function: hash(x) = x % table_size\n" << endl;

  int table_size = 10; // Hash table with 10 buckets (0-9)

  // Hash various integers
  int keys[] = {5, 15, 25, 35, 42, 100, 137};

  cout << "Table size: " << table_size << " buckets (indices 0-9)\n" << endl;
  cout << "Key    -> Hash Value (bucket index)" << endl;
  cout << "------    -------------------------" << endl;

  for (int key : keys) {
    int hash_value = key % table_size;
    cout << key << "\t -> " << hash_value << endl;
  }

  cout << "\nObservation: Keys 5, 15, 25, 35 all hash to bucket 5 (collision!)"
       << endl;
}

// ============== EXAMPLE 2: USING std::hash ==============
void example2_std_hash() {
  cout << "\n============== EXAMPLE 2: std::hash IN C++ ==============" << endl;
  cout << "C++ provides std::hash for built-in types\n" << endl;

  // Create hash function objects
  hash<int> int_hasher;
  hash<string> string_hasher;
  hash<double> double_hasher;
  hash<char> char_hasher;

  // Hash integers
  cout << "Integer hashes:" << endl;
  cout << "  hash(42)   = " << int_hasher(42) << endl;
  cout << "  hash(100)  = " << int_hasher(100) << endl;
  cout << "  hash(-17)  = " << int_hasher(-17) << endl;

  // Hash strings
  cout << "\nString hashes:" << endl;
  cout << "  hash(\"apple\")  = " << string_hasher("apple") << endl;
  cout << "  hash(\"banana\") = " << string_hasher("banana") << endl;
  cout << "  hash(\"cherry\") = " << string_hasher("cherry") << endl;

  // Deterministic property
  cout << "\nDeterministic property (same input = same output):" << endl;
  cout << "  hash(\"apple\") again = " << string_hasher("apple") << endl;

  // Hash doubles
  cout << "\nDouble hashes:" << endl;
  cout << "  hash(3.14)  = " << double_hasher(3.14) << endl;
  cout << "  hash(2.718) = " << double_hasher(2.718) << endl;

  // Hash characters
  cout << "\nCharacter hashes:" << endl;
  cout << "  hash('A') = " << char_hasher('A') << endl;
  cout << "  hash('Z') = " << char_hasher('Z') << endl;
}

// ============== EXAMPLE 3: AVALANCHE EFFECT ==============
void example3_avalanche_effect() {
  cout << "\n============== EXAMPLE 3: AVALANCHE EFFECT ==============" << endl;
  cout << "Small input change should cause large hash change\n" << endl;

  hash<string> hasher;

  cout << "Similar strings have very different hashes:" << endl;
  cout << "  hash(\"cat\")  = " << hasher("cat") << endl;
  cout << "  hash(\"bat\")  = " << hasher("bat") << endl;
  cout << "  hash(\"cats\") = " << hasher("cats") << endl;

  cout << "\nSingle character change:" << endl;
  cout << "  hash(\"hello\") = " << hasher("hello") << endl;
  cout << "  hash(\"hallo\") = " << hasher("hallo") << endl;

  cout << "\nCase change:" << endl;
  cout << "  hash(\"Apple\") = " << hasher("Apple") << endl;
  cout << "  hash(\"apple\") = " << hasher("apple") << endl;
}

// ============== EXAMPLE 4: SIMPLE CUSTOM HASH FOR STRINGS ==============
size_t simple_string_hash(const string &str, int table_size) {
  // Sum of ASCII values
  size_t sum = 0;
  for (char c : str) {
    sum += static_cast<size_t>(c);
  }
  return sum % table_size;
}

void example4_simple_custom_hash() {
  cout << "\n============== EXAMPLE 4: SIMPLE CUSTOM HASH FUNCTION "
          "=============="
       << endl;
  cout << "Custom hash: sum of ASCII values % table_size\n" << endl;

  int table_size = 100;
  vector<string> words = {"cat", "dog", "bird", "fish", "lion"};

  cout << "Table size: " << table_size << endl << endl;

  for (const string &word : words) {
    size_t hash_val = simple_string_hash(word, table_size);
    cout << "hash(\"" << word << "\") = " << hash_val << endl;
  }

  cout << "\nProblem with this simple hash:" << endl;
  cout << "  Anagrams have same hash!" << endl;
  cout << "  hash(\"listen\") = " << simple_string_hash("listen", table_size)
       << endl;
  cout << "  hash(\"silent\") = " << simple_string_hash("silent", table_size)
       << endl;
  cout << "  These should be different!" << endl;
}

// ============== EXAMPLE 5: BETTER STRING HASH (POLYNOMIAL ROLLING)
// ==============
size_t polynomial_hash(const string &str, int table_size) {
  const int p = 31; // Prime multiplier
  size_t hash_value = 0;
  size_t p_pow = 1;

  for (char c : str) {
    hash_value = (hash_value + (c - 'a' + 1) * p_pow) % table_size;
    p_pow = (p_pow * p) % table_size;
  }

  return hash_value;
}

void example5_polynomial_hash() {
  cout << "\n============== EXAMPLE 5: POLYNOMIAL ROLLING HASH =============="
       << endl;
  cout << "Better hash: hash = (c1*p^0 + c2*p^1 + c3*p^2 + ...) % table_size"
       << endl;
  cout << "where p is a prime number (often 31 or 53)\n" << endl;

  int table_size = 1000;
  vector<string> words = {"cat", "dog", "listen", "silent", "abc", "bca"};

  cout << "Table size: " << table_size << endl << endl;

  for (const string &word : words) {
    size_t hash_val = polynomial_hash(word, table_size);
    cout << "hash(\"" << word << "\") = " << hash_val << endl;
  }

  cout << "\nAnagrams now have different hashes (better distribution):" << endl;
  cout << "  listen != silent (usually)" << endl;
}

// ============== EXAMPLE 6: HASH FUNCTION FOR INTEGERS (MULTIPLICATION METHOD)
// ==============
size_t multiplication_hash(int key, int table_size) {
  // Multiplication method using golden ratio
  const double A = 0.6180339887; // (√5 - 1) / 2
  double temp = key * A;
  temp = temp - static_cast<int>(temp); // Fractional part
  return static_cast<size_t>(table_size * temp);
}

void example6_multiplication_hash() {
  cout
      << "\n============== EXAMPLE 6: MULTIPLICATION HASH METHOD =============="
      << endl;
  cout << "hash(key) = floor(table_size * frac(key * A))" << endl;
  cout << "where A = 0.618... (golden ratio), frac = fractional part\n" << endl;

  int table_size = 100;
  int keys[] = {12, 25, 37, 42, 67, 89, 123, 456};

  cout << "Table size: " << table_size << endl << endl;
  cout << "Key    -> Hash Value" << endl;
  cout << "-----     ----------" << endl;

  for (int key : keys) {
    size_t hash_val = multiplication_hash(key, table_size);
    cout << key << "\t -> " << hash_val << endl;
  }

  cout << "\nBetter distribution than modulo for certain patterns" << endl;
}

// ============== EXAMPLE 7: HASH FOR PAIR (COMBINING HASHES) ==============
size_t hash_pair(int x, int y) {
  // Combine two hash values using XOR and bit shifting
  hash<int> hasher;
  size_t h1 = hasher(x);
  size_t h2 = hasher(y);

  // Combine using XOR and shifting
  return h1 ^ (h2 << 1);
}

void example7_combining_hashes() {
  cout << "\n============== EXAMPLE 7: COMBINING HASH VALUES =============="
       << endl;
  cout << "For composite types (pairs, tuples), combine individual hashes\n"
       << endl;

  cout << "Method: hash(pair) = hash(first) XOR (hash(second) << 1)\n" << endl;

  vector<pair<int, int>> pairs = {{1, 2}, {2, 1}, {3, 5}, {5, 3}};

  for (auto &p : pairs) {
    size_t hash_val = hash_pair(p.first, p.second);
    cout << "hash((" << p.first << ", " << p.second << ")) = " << hash_val
         << endl;
  }

  cout << "\nNote: (1,2) and (2,1) have different hashes (order matters)"
       << endl;
}

// ============== EXAMPLE 8: DISTRIBUTION ANALYSIS ==============
void example8_distribution_analysis() {
  cout
      << "\n============== EXAMPLE 8: HASH DISTRIBUTION ANALYSIS =============="
      << endl;
  cout << "Analyzing how well a hash function distributes values\n" << endl;

  int table_size = 10;
  vector<int> buckets(table_size, 0); // Count per bucket

  // Generate random keys and hash them
  cout << "Hashing 100 integers (0-999) using modulo:" << endl;
  for (int i = 0; i < 100; i++) {
    int key = i * 10; // Keys: 0, 10, 20, ..., 990
    int bucket = key % table_size;
    buckets[bucket]++;
  }

  cout << "\nBucket distribution:" << endl;
  for (int i = 0; i < table_size; i++) {
    cout << "Bucket " << i << ": ";
    for (int j = 0; j < buckets[i]; j++) {
      cout << "*";
    }
    cout << " (" << buckets[i] << ")" << endl;
  }

  cout << "\nIdeal: All buckets have equal count (uniform distribution)"
       << endl;
  cout << "This shows perfect distribution for this pattern!" << endl;
}

// ============== EXAMPLE 9: HASH FUNCTION FOR CUSTOM STRUCT ==============
struct Point {
  int x, y;
};

size_t hash_point(const Point &p) {
  // Combine x and y coordinates
  return hash_pair(p.x, p.y);
}

void example9_custom_struct_hash() {
  cout
      << "\n============== EXAMPLE 9: HASH FOR CUSTOM STRUCTURES =============="
      << endl;
  cout << "Creating hash function for Point(x, y)\n" << endl;

  vector<Point> points = {{0, 0}, {1, 2}, {3, 4}, {5, 5}, {-1, 2}};

  for (const Point &p : points) {
    size_t hash_val = hash_point(p);
    cout << "hash(Point(" << p.x << ", " << p.y << ")) = " << hash_val << endl;
  }

  cout << "\nKey principle: Combine hashes of individual fields" << endl;
}

// ============== EXAMPLE 10: COMPARING HASH FUNCTIONS ==============
void example10_hash_comparison() {
  cout << "\n============== EXAMPLE 10: COMPARING HASH FUNCTIONS =============="
       << endl;
  cout << "Comparing different hash methods for same input\n" << endl;

  int table_size = 1000;
  string test_str = "hello";

  cout << "Input string: \"" << test_str << "\"\n" << endl;

  // Method 1: std::hash
  hash<string> std_hasher;
  cout << "1. std::hash: " << std_hasher(test_str) % table_size << endl;

  // Method 2: Simple sum
  cout << "2. Simple sum: " << simple_string_hash(test_str, table_size) << endl;

  // Method 3: Polynomial
  cout << "3. Polynomial: " << polynomial_hash(test_str, table_size) << endl;

  cout << "\nEach method produces different hash values" << endl;
  cout << "std::hash is generally preferred for production code" << endl;
}

int main() {
  cout << "\n======================================================" << endl;
  cout << "         HASH FUNCTIONS AND BASICS TUTORIAL          " << endl;
  cout << "======================================================" << endl;

  example1_basic_integer_hash();
  example2_std_hash();
  example3_avalanche_effect();
  example4_simple_custom_hash();
  example5_polynomial_hash();
  example6_multiplication_hash();
  example7_combining_hashes();
  example8_distribution_analysis();
  example9_custom_struct_hash();
  example10_hash_comparison();

  cout << "\n======================================================" << endl;
  cout << "                   KEY TAKEAWAYS                      " << endl;
  cout << "======================================================" << endl;
  cout << "✓ Hash functions convert data to fixed-size values" << endl;
  cout << "✓ Good hashes are: deterministic, fast, uniform, avalanche" << endl;
  cout << "✓ Use std::hash for built-in types" << endl;
  cout << "✓ Combine hashes for composite types (XOR, shifting)" << endl;
  cout << "✓ Polynomial rolling hash for strings" << endl;
  cout << "✓ Modulo and multiplication methods for integers" << endl;
  cout << "✓ Test distribution to verify hash quality" << endl;
  cout << "======================================================\n" << endl;

  return 0;
}

/*
 * =====================================================================
 * COMMON MISTAKES TO AVOID
 * =====================================================================
 *
 * 1. USING NON-DETERMINISTIC FUNCTIONS
 *    ✗ BAD: hash(x) = random()  // Different every time!
 *    ✓ GOOD: hash(x) = x % size  // Always same for same x
 *
 * 2. POOR DISTRIBUTION
 *    ✗ BAD: hash(x) = x % 2  // Only 2 buckets, many collisions
 *    ✓ GOOD: Use prime table size, better hash function
 *
 * 3. NOT HANDLING NEGATIVE NUMBERS
 *    ✗ BAD: hash(x) = x % size  // Negative result for negative x
 *    ✓ GOOD: hash(x) = abs(x) % size  or  ((x % size) + size) % size
 *
 * 4. IGNORING HASH COMBINING FOR COMPOSITE TYPES
 *    ✗ BAD: hash(pair) = hash(first) + hash(second)  // Commutative!
 *    ✓ GOOD: hash(pair) = hash(first) ^ (hash(second) << 1)
 *
 * 5. USING TABLE SIZE THAT'S NOT PRIME
 *    ✗ BAD: table_size = 100 (even number)
 *    ✓ GOOD: table_size = 101 (prime) - better distribution
 *
 * 6. FORGETTING OVERFLOW
 *    ✗ BAD: size_t hash = huge_value * another_huge_value  // Overflow
 *    ✓ GOOD: Use modulo during calculation to keep values small
 *
 * =====================================================================
 * PRACTICE EXERCISES
 * =====================================================================
 *
 * 1. Write a hash function for a Date struct (day, month, year)
 * 2. Implement a hash function that handles negative integers correctly
 * 3. Create a hash function for a string that's case-insensitive
 * 4. Compare distribution of modulo vs multiplication hash for 1000 keys
 * 5. Write a hash function for a 3D Point(x, y, z)
 * 6. Implement a hash function for a vector<int>
 * 7. Create a hash that combines multiple string fields
 * 8. Test avalanche effect: count how many bits change for 1-char difference
 * 9. Implement FNV-1a hash algorithm for strings
 * 10. Write a hash function for a matrix (2D vector)
 *
 * =====================================================================
 * COMPILATION AND EXECUTION
 * =====================================================================
 *
 * To compile and run:
 *   g++ -std=c++17 1_hash_functions_basics.cpp -o hash_basics
 *   ./hash_basics
 *
 * =====================================================================
 */
