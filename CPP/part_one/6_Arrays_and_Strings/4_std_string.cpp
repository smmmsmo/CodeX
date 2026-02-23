#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

/*
 * =====================================================================
 * TOPIC 6.4: std::string CLASS (Modern C++ Strings)
 * =====================================================================
 *
 * WHAT IS std::string?
 * std::string is a C++ Standard Library class that provides a safer,
 * more convenient way to work with strings compared to C-style strings.
 * It handles memory automatically and provides rich functionality.
 *
 * KEY CONCEPTS COVERED:
 * 1. string declaration and initialization
 * 2. String operations (concatenation, comparison, etc.)
 * 3. Accessing characters ([], at(), front(), back())
 * 4. String modifiers (append, insert, erase, replace)
 * 5. String capacity (size, length, empty, clear)
 * 6. String searching (find, rfind, find_first_of, etc.)
 * 7. Substring operations
 * 8. String conversion (to_string, stoi, stod, etc.)
 * 9. String streams (stringstream)
 * 10. String iterators
 * 11. Common algorithms with strings
 * 12. String comparison and lexicographic ordering
 *
 * =====================================================================
 * std::string BASICS
 * =====================================================================
 *
 * DECLARATION:
 *    string str;                    // Empty string
 *    string str = "Hello";          // Initialize with literal
 *    string str("Hello");           // Constructor
 *    string str(5, 'A');            // "AAAAA"
 *
 * ADVANTAGES OVER C-STRINGS:
 *    - Automatic memory management
 *    - Dynamic size (grows/shrinks as needed)
 *    - Rich set of member functions
 *    - Safer (no buffer overflow)
 *    - Can use operators (+, ==, <, etc.)
 *
 * TIME COMPLEXITIES:
 *    Access: O(1)
 *    Append/Push back: O(1) amortized
 *    Insert/Erase: O(n)
 *    Find: O(n*m) worst case
 *    Substring: O(n)
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: STRING DECLARATION AND INITIALIZATION
// ==============
void example1_string_declaration() {
  cout << "\n============== EXAMPLE 1: STRING DECLARATION =============="
       << endl;
  cout << "Different ways to create std::string objects\n" << endl;

  // Method 1: Default constructor (empty string)
  string str1;
  cout << "Empty string: \"" << str1 << "\" (length: " << str1.length() << ")"
       << endl;

  // Method 2: Initialize with string literal
  string str2 = "Hello";
  cout << "String literal: \"" << str2 << "\"" << endl;

  // Method 3: Constructor with literal
  string str3("World");
  cout << "Constructor: \"" << str3 << "\"" << endl;

  // Method 4: Copy constructor
  string str4 = str2;
  cout << "Copy: \"" << str4 << "\"" << endl;

  // Method 5: Repeat character
  string str5(5, 'A');
  cout << "Repeat char: \"" << str5 << "\"" << endl;

  // Method 6: Substring of another string
  string str6(str2, 1, 3); // From index 1, length 3
  cout << "Substring: \"" << str6 << "\" (from \"" << str2 << "\")" << endl;

  // Method 7: From C-string
  char cstr[] = "C-Style";
  string str7(cstr);
  cout << "From C-string: \"" << str7 << "\"" << endl;

  // Method 8: Using assign
  string str8;
  str8.assign("Assigned");
  cout << "Using assign: \"" << str8 << "\"" << endl;

  cout << "\nNote: No need to worry about null terminator!" << endl;
}

// ============== EXAMPLE 2: STRING CONCATENATION ==============
void example2_string_concatenation() {
  cout << "\n============== EXAMPLE 2: STRING CONCATENATION =============="
       << endl;
  cout << "Different ways to join strings\n" << endl;

  string str1 = "Hello";
  string str2 = "World";

  // Method 1: Using + operator
  string result1 = str1 + " " + str2;
  cout << "Using +: \"" << result1 << "\"" << endl;

  // Method 2: Using += operator
  string result2 = str1;
  result2 += " ";
  result2 += str2;
  cout << "Using +=: \"" << result2 << "\"" << endl;

  // Method 3: Using append()
  string result3 = str1;
  result3.append(" ").append(str2);
  cout << "Using append(): \"" << result3 << "\"" << endl;

  // Method 4: Concatenate with numbers
  string msg = "The answer is " + to_string(42);
  cout << "With number: \"" << msg << "\"" << endl;

  // Method 5: Multiple concatenations
  string result4 = str1 + ", " + str2 + "!";
  cout << "Multiple: \"" << result4 << "\"" << endl;

  cout << "\nNote: + operator creates new string, += modifies existing" << endl;
}

// ============== EXAMPLE 3: ACCESSING CHARACTERS ==============
void example3_accessing_chars() {
  cout << "\n============== EXAMPLE 3: ACCESSING CHARACTERS =============="
       << endl;
  cout << "Different ways to access individual characters\n" << endl;

  string str = "Programming";

  // Method 1: Using [] operator (no bounds checking)
  cout << "Using []:" << endl;
  cout << "str[0] = " << str[0] << endl;
  cout << "str[5] = " << str[5] << endl;

  // Method 2: Using at() (with bounds checking)
  cout << "\nUsing at():" << endl;
  cout << "str.at(0) = " << str.at(0) << endl;
  cout << "str.at(5) = " << str.at(5) << endl;

  // Method 3: Using front() and back()
  cout << "\nUsing front() and back():" << endl;
  cout << "str.front() = " << str.front() << " (first char)" << endl;
  cout << "str.back() = " << str.back() << " (last char)" << endl;

  // Modify characters
  str[0] = 'p';
  cout << "\nAfter str[0] = 'p': \"" << str << "\"" << endl;

  // Iterate through string
  cout << "\nIterate with range-based for:" << endl;
  for (char c : str) {
    cout << c << " ";
  }
  cout << endl;

  cout << "\nNote: at() throws exception if out of bounds, [] doesn't!" << endl;
}

// ============== EXAMPLE 4: STRING SIZE AND CAPACITY ==============
void example4_size_capacity() {
  cout << "\n============== EXAMPLE 4: SIZE AND CAPACITY =============="
       << endl;
  cout << "Understanding string size and capacity\n" << endl;

  string str = "Hello";

  cout << "String: \"" << str << "\"" << endl;
  cout << "size() = " << str.size() << endl;
  cout << "length() = " << str.length() << " (same as size)" << endl;
  cout << "capacity() = " << str.capacity() << " (allocated space)" << endl;
  cout << "max_size() = " << str.max_size() << " (theoretical max)" << endl;

  // Check if empty
  cout << "\nempty() = " << (str.empty() ? "true" : "false") << endl;

  string empty_str;
  cout << "Empty string: empty() = " << (empty_str.empty() ? "true" : "false")
       << endl;

  // Reserve capacity
  str.reserve(100);
  cout << "\nAfter reserve(100):" << endl;
  cout << "capacity() = " << str.capacity() << endl;
  cout << "size() = " << str.size() << " (unchanged)" << endl;

  // Clear string
  str.clear();
  cout << "\nAfter clear():" << endl;
  cout << "String: \"" << str << "\"" << endl;
  cout << "size() = " << str.size() << endl;
  cout << "empty() = " << (str.empty() ? "true" : "false") << endl;

  cout << "\nNote: capacity() >= size() always" << endl;
}

// ============== EXAMPLE 5: STRING MODIFIERS ==============
void example5_string_modifiers() {
  cout << "\n============== EXAMPLE 5: STRING MODIFIERS ==============" << endl;
  cout << "Modifying strings with various operations\n" << endl;

  string str = "Hello World";
  cout << "Original: \"" << str << "\"" << endl;

  // append()
  str.append("!");
  cout << "After append(\"!\"): \"" << str << "\"" << endl;

  // insert()
  str.insert(5, ",");
  cout << "After insert(5, \",\"): \"" << str << "\"" << endl;

  // erase()
  str.erase(5, 1); // Remove 1 char at position 5
  cout << "After erase(5, 1): \"" << str << "\"" << endl;

  // replace()
  str.replace(0, 5, "Hi"); // Replace "Hello" with "Hi"
  cout << "After replace(0, 5, \"Hi\"): \"" << str << "\"" << endl;

  // push_back() and pop_back()
  str.push_back('?');
  cout << "After push_back('?'): \"" << str << "\"" << endl;

  str.pop_back();
  cout << "After pop_back(): \"" << str << "\"" << endl;

  // substr()
  string sub = str.substr(0, 2); // From position 0, length 2
  cout << "substr(0, 2): \"" << sub << "\"" << endl;

  cout << "\nAll modifiers change the original string!" << endl;
}

// ============== EXAMPLE 6: STRING SEARCHING ==============
void example6_string_searching() {
  cout << "\n============== EXAMPLE 6: STRING SEARCHING ==============" << endl;
  cout << "Finding substrings and characters\n" << endl;

  string str = "Hello World, Hello Universe";
  cout << "String: \"" << str << "\"" << endl;

  // find() - first occurrence
  size_t pos = str.find("Hello");
  cout << "\nfind(\"Hello\") = " << pos << " (first occurrence)" << endl;

  // find() with start position
  pos = str.find("Hello", 1);
  cout << "find(\"Hello\", 1) = " << pos << " (search from index 1)" << endl;

  // rfind() - last occurrence
  pos = str.rfind("Hello");
  cout << "rfind(\"Hello\") = " << pos << " (last occurrence)" << endl;

  // find() returns npos if not found
  pos = str.find("Python");
  if (pos == string::npos) {
    cout << "\nfind(\"Python\") = npos (not found)" << endl;
  }

  // find_first_of() - first occurrence of any char from set
  pos = str.find_first_of("aeiou");
  cout << "\nfind_first_of(\"aeiou\") = " << pos << " ('" << str[pos] << "')"
       << endl;

  // find_last_of()
  pos = str.find_last_of("aeiou");
  cout << "find_last_of(\"aeiou\") = " << pos << " ('" << str[pos] << "')"
       << endl;

  // find_first_not_of()
  pos = str.find_first_not_of("Hello ");
  cout << "find_first_not_of(\"Hello \") = " << pos << " ('" << str[pos] << "')"
       << endl;

  cout << "\nNote: All return string::npos if not found" << endl;
}

// ============== EXAMPLE 7: STRING COMPARISON ==============
void example7_string_comparison() {
  cout << "\n============== EXAMPLE 7: STRING COMPARISON =============="
       << endl;
  cout << "Comparing strings using operators and compare()\n" << endl;

  string str1 = "apple";
  string str2 = "banana";
  string str3 = "apple";

  // Using == operator
  cout << "\"" << str1 << "\" == \"" << str3
       << "\" : " << (str1 == str3 ? "true" : "false") << endl;
  cout << "\"" << str1 << "\" == \"" << str2
       << "\" : " << (str1 == str2 ? "true" : "false") << endl;

  // Using != operator
  cout << "\n\"" << str1 << "\" != \"" << str2
       << "\" : " << (str1 != str2 ? "true" : "false") << endl;

  // Lexicographic comparison
  cout << "\nLexicographic comparison:" << endl;
  cout << "\"" << str1 << "\" < \"" << str2
       << "\" : " << (str1 < str2 ? "true" : "false") << endl;
  cout << "\"" << str2 << "\" > \"" << str1
       << "\" : " << (str2 > str1 ? "true" : "false") << endl;

  // Using compare()
  cout << "\nUsing compare():" << endl;
  int result = str1.compare(str2);
  cout << "\"" << str1 << "\".compare(\"" << str2 << "\") = " << result;
  cout << (result < 0 ? " (str1 < str2)" : " (str1 >= str2)") << endl;

  cout << "\nNote: compare() returns 0 (equal), <0 (less), >0 (greater)"
       << endl;
}

// ============== EXAMPLE 8: STRING CONVERSION ==============
void example8_string_conversion() {
  cout << "\n============== EXAMPLE 8: STRING CONVERSION =============="
       << endl;
  cout << "Converting between strings and numbers\n" << endl;

  // Number to string
  int num = 42;
  double pi = 3.14159;
  string str1 = to_string(num);
  string str2 = to_string(pi);

  cout << "to_string(42) = \"" << str1 << "\"" << endl;
  cout << "to_string(3.14159) = \"" << str2 << "\"" << endl;

  // String to number
  string num_str = "12345";
  string float_str = "3.14";
  string hex_str = "0x1A";

  int converted_int = stoi(num_str);
  double converted_double = stod(float_str);
  int hex_num = stoi(hex_str, nullptr, 16);

  cout << "\nstoi(\"12345\") = " << converted_int << endl;
  cout << "stod(\"3.14\") = " << converted_double << endl;
  cout << "stoi(\"0x1A\", nullptr, 16) = " << hex_num << " (hex to decimal)"
       << endl;

  // Other conversions
  long l = stol("1234567890");
  long long ll = stoll("12345678901234");
  float f = stof("2.71828");

  cout << "\nstol() -> long: " << l << endl;
  cout << "stoll() -> long long: " << ll << endl;
  cout << "stof() -> float: " << f << endl;

  cout << "\nNote: sto* functions throw exception for invalid conversion"
       << endl;
}

// ============== EXAMPLE 9: SUBSTRING OPERATIONS ==============
void example9_substring() {
  cout << "\n============== EXAMPLE 9: SUBSTRING OPERATIONS =============="
       << endl;
  cout << "Extracting parts of strings\n" << endl;

  string str = "Competitive Programming";
  cout << "Original: \"" << str << "\"" << endl;

  // Extract substring
  string sub1 = str.substr(0, 11); // From index 0, length 11
  cout << "\nsubstr(0, 11): \"" << sub1 << "\"" << endl;

  string sub2 = str.substr(12); // From index 12 to end
  cout << "substr(12): \"" << sub2 << "\"" << endl;

  // Find and extract
  size_t pos = str.find("Program");
  if (pos != string::npos) {
    string sub3 = str.substr(pos, 7);
    cout << "Found and extracted: \"" << sub3 << "\"" << endl;
  }

  // Extract words
  cout << "\nExtracting words:" << endl;
  size_t start = 0;
  size_t space = str.find(' ');
  while (space != string::npos) {
    cout << "Word: \"" << str.substr(start, space - start) << "\"" << endl;
    start = space + 1;
    space = str.find(' ', start);
  }
  cout << "Word: \"" << str.substr(start) << "\"" << endl;

  cout << "\nsubstr(pos, len): pos is starting index, len is length" << endl;
}

// ============== EXAMPLE 10: STRING STREAMS ==============
void example10_string_streams() {
  cout << "\n============== EXAMPLE 10: STRING STREAMS ==============" << endl;
  cout << "Using stringstream for parsing and formatting\n" << endl;

  // Parse string to extract values
  string data = "John 25 3.75";
  stringstream ss(data);

  string name;
  int age;
  double gpa;

  ss >> name >> age >> gpa;

  cout << "Parsed data:" << endl;
  cout << "Name: " << name << endl;
  cout << "Age: " << age << endl;
  cout << "GPA: " << gpa << endl;

  // Build string using stringstream
  stringstream ss2;
  ss2 << "The answer is " << 42 << " and pi is " << 3.14;
  string result = ss2.str();
  cout << "\nBuilt string: \"" << result << "\"" << endl;

  // Split string by delimiter
  string csv = "apple,banana,cherry,date";
  stringstream ss3(csv);
  string token;

  cout << "\nSplitting CSV:" << endl;
  while (getline(ss3, token, ',')) {
    cout << "  - " << token << endl;
  }

  cout << "\nstringstream is great for parsing and formatting!" << endl;
}

// ============== EXAMPLE 11: STRING ALGORITHMS ==============
void example11_string_algorithms() {
  cout << "\n============== EXAMPLE 11: STRING ALGORITHMS =============="
       << endl;
  cout << "Using STL algorithms with strings\n" << endl;

  string str = "programming";
  cout << "Original: \"" << str << "\"" << endl;

  // reverse()
  reverse(str.begin(), str.end());
  cout << "Reversed: \"" << str << "\"" << endl;

  // Reverse back
  reverse(str.begin(), str.end());

  // sort()
  sort(str.begin(), str.end());
  cout << "Sorted: \"" << str << "\"" << endl;

  // Check if contains only unique characters
  string test = "abcdefg";
  sort(test.begin(), test.end());
  bool has_duplicates = adjacent_find(test.begin(), test.end()) != test.end();
  cout << "\n\"abcdefg\" has duplicates: "
       << (has_duplicates ? "true" : "false") << endl;

  // Transform to uppercase
  string lower = "hello";
  transform(lower.begin(), lower.end(), lower.begin(), ::toupper);
  cout << "Uppercase: \"" << lower << "\"" << endl;

  // Count occurrences
  string text = "hello world";
  int count_l = count(text.begin(), text.end(), 'l');
  cout << "\nCount of 'l' in \"hello world\": " << count_l << endl;

  cout << "\nSTL algorithms work great with strings!" << endl;
}

// ============== EXAMPLE 12: COMMON STRING PATTERNS ==============
void example12_common_patterns() {
  cout << "\n============== EXAMPLE 12: COMMON PATTERNS ==============" << endl;
  cout << "Frequently used string operations in competitive programming\n"
       << endl;

  // 1. Palindrome check
  auto is_palindrome = [](const string &s) {
    int left = 0, right = s.length() - 1;
    while (left < right) {
      if (s[left++] != s[right--])
        return false;
    }
    return true;
  };

  string test1 = "racecar";
  cout << "\"" << test1
       << "\" is palindrome: " << (is_palindrome(test1) ? "true" : "false")
       << endl;

  // 2. Remove spaces
  auto remove_spaces = [](string s) {
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    return s;
  };

  string test2 = "Hello World";
  cout << "\nRemove spaces from \"" << test2 << "\": \"" << remove_spaces(test2)
       << "\"" << endl;

  // 3. Count vowels
  auto count_vowels = [](const string &s) {
    int count = 0;
    for (char c : s) {
      char lower_c = tolower(c);
      if (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' ||
          lower_c == 'o' || lower_c == 'u') {
        count++;
      }
    }
    return count;
  };

  string test3 = "Education";
  cout << "\nVowels in \"" << test3 << "\": " << count_vowels(test3) << endl;

  // 4. Frequency map
  auto freq_map = [](const string &s) {
    int freq[256] = {0};
    for (char c : s) {
      freq[c]++;
    }
    cout << "\nCharacter frequencies in \"" << s << "\":" << endl;
    for (int i = 0; i < 256; i++) {
      if (freq[i] > 0) {
        cout << "  '" << (char)i << "': " << freq[i] << endl;
      }
    }
  };

  freq_map("hello");

  cout << "\nThese patterns appear frequently in problems!" << endl;
}

/*
 * =====================================================================
 * KEY CONCEPTS SUMMARY
 * =====================================================================
 *
 * 1. BASIC OPERATIONS:
 *    - Creation: string s = "text" or string s(10, 'A')
 *    - Concatenation: + or += or append()
 *    - Access: [], at(), front(), back()
 *
 * 2. SIZE AND CAPACITY:
 *    - size()/length(): number of characters
 *    - capacity(): allocated space
 *    - empty(): check if empty
 *    - clear(): remove all characters
 *
 * 3. MODIFIERS:
 *    - append(), insert(), erase(), replace()
 *    - push_back(), pop_back()
 *    - substr(): extract substring
 *
 * 4. SEARCHING:
 *    - find(), rfind(): search substring
 *    - find_first_of(), find_last_of()
 *    - Returns string::npos if not found
 *
 * 5. COMPARISON:
 *    - Operators: ==, !=, <, >, <=, >=
 *    - compare() method
 *    - Lexicographic ordering
 *
 * 6. CONVERSION:
 *    - to_string(): number → string
 *    - stoi(), stol(), stod(), stof(): string → number
 *
 * 7. ITERATORS:
 *    - begin(), end()
 *    - Can use with STL algorithms
 *    - Range-based for loops
 *
 * =====================================================================
 * COMPETITIVE PROGRAMMING TIPS
 * =====================================================================
 *
 * 1. Use string instead of char[] for contests - safer and easier
 * 2. Remember: find() returns string::npos when not found
 * 3. substr() creates new string - be aware of memory
 * 4. Use stringstream for parsing complex inputs
 * 5. Transform to lowercase/uppercase for case-insensitive operations
 * 6. Sort string for anagram detection
 * 7. Use frequency array for character counting
 * 8. += is efficient for building strings
 * 9. Reserve capacity for large string building
 * 10. Learn common patterns: palindrome, anagram, subsequence
 *
 * =====================================================================
 * COMMON MISTAKES TO AVOID
 * =====================================================================
 *
 * 1. Forgetting that find() returns npos (not -1)
 * 2. Using [] without bounds checking (use at() for safety)
 * 3. Modifying string while iterating (invalidates iterators)
 * 4. Not checking empty() before accessing front()/back()
 * 5. Assuming stoi() always succeeds (can throw exception)
 * 6. Comparing string and char* with == (works, but know it)
 * 7. Off-by-one errors with substr(pos, len)
 * 8. Not handling string::npos properly
 * 9. Inefficient string building with + in loop (use +=)
 * 10. Forgetting that strings are mutable in C++
 *
 * =====================================================================
 */

int main() {
  cout << "=========================================================" << endl;
  cout << "         std::string - COMPREHENSIVE GUIDE               " << endl;
  cout << "=========================================================" << endl;

  example1_string_declaration();
  example2_string_concatenation();
  example3_accessing_chars();
  example4_size_capacity();
  example5_string_modifiers();
  example6_string_searching();
  example7_string_comparison();
  example8_string_conversion();
  example9_substring();
  example10_string_streams();
  example11_string_algorithms();
  example12_common_patterns();

  cout << "\n=========================================================" << endl;
  cout << "         PRACTICE EXERCISES" << endl;
  cout << "=========================================================" << endl;
  cout << "\n1. Reverse words in a string" << endl;
  cout << "2. Check if two strings are anagrams" << endl;
  cout << "3. Find longest palindromic substring" << endl;
  cout << "4. Implement atoi() function" << endl;
  cout << "5. Remove duplicate characters" << endl;
  cout << "6. Check if string is rotation of another" << endl;
  cout << "7. Group anagrams from list of strings" << endl;
  cout << "8. Find first non-repeating character" << endl;
  cout << "9. Longest common prefix in array of strings" << endl;
  cout << "10. Valid parentheses checker" << endl;

  return 0;
}
