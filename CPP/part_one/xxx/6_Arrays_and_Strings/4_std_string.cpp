/*
================================================================================
TOPIC 6: ARRAYS AND STRINGS - PART 4: std::string (Modern C++)
================================================================================

std::string:
- String class from Standard Library
- Much safer and easier than C-style strings
- Automatic memory management
- Rich set of member functions
- Can be used with operators like +, ==, etc.

ADVANTAGES OVER C-STYLE STRINGS:
- No buffer overflow risks
- Dynamic size (grows as needed)
- Easier comparison, concatenation, manipulation
- Rich set of built-in functions
- Can use with algorithms (sort, find, etc.)

HEADER:
#include <string>

CONSTRUCTION:
string str1;                    // Empty string
string str2 = "Hello";          // From literal
string str3(str2);              // Copy constructor
string str4(5, 'a');            // 5 'a's: "aaaaa"

================================================================================
*/

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
  cout << "=== std::string (Modern C++ Strings) ===" << endl << endl;

  // ======================= STRING CREATION =======================
  cout << "1. STRING CREATION:" << endl;

  string empty_str;
  string str1 = "Hello";
  string str2("World");
  string str3(5, 'a'); // "aaaaa"

  cout << "empty_str: '" << empty_str << "'" << endl;
  cout << "str1: " << str1 << endl;
  cout << "str2: " << str2 << endl;
  cout << "str3: " << str3 << endl;

  // ======================= STRING LENGTH AND SIZE =======================
  cout << endl << "2. STRING LENGTH AND SIZE:" << endl;

  string text = "Programming";
  cout << "String: " << text << endl;
  cout << "Length: " << text.length() << endl;
  cout << "Size: " << text.size() << endl;
  cout << "Empty: " << (text.empty() ? "Yes" : "No") << endl;

  // ======================= ACCESSING CHARACTERS =======================
  cout << endl << "3. ACCESSING CHARACTERS:" << endl;

  string word = "Program";
  cout << "String: " << word << endl;
  cout << "First character: " << word[0] << endl;
  cout << "Third character: " << word[2] << endl;
  cout << "At index 4: " << word.at(4) << endl;

  // ======================= MODIFYING CHARACTERS =======================
  cout << endl << "4. MODIFYING CHARACTERS:" << endl;

  string modify = "Hello";
  cout << "Original: " << modify << endl;
  modify[0] = 'J';
  cout << "After changing first: " << modify << endl;
  modify.at(1) = 'a';
  cout << "After changing second: " << modify << endl;

  // ======================= CONCATENATION =======================
  cout << endl << "5. CONCATENATION:" << endl;

  string first = "Hello";
  string second = " World";
  string result = first + second; // Using + operator
  cout << "first: " << first << endl;
  cout << "second: " << second << endl;
  cout << "result: " << result << endl;

  first += "!"; // Using += operator
  cout << "first after +=: " << first << endl;

  string append_str = "Learn";
  append_str.append(" C++"); // Using append method
  cout << "After append: " << append_str << endl;

  // ======================= STRING COMPARISON =======================
  cout << endl << "6. STRING COMPARISON:" << endl;

  string comp1 = "apple";
  string comp2 = "apple";
  string comp3 = "banana";

  cout << "comp1: " << comp1 << endl;
  cout << "comp2: " << comp2 << endl;
  cout << "comp3: " << comp3 << endl;
  cout << "comp1 == comp2: " << (comp1 == comp2 ? "true" : "false") << endl;
  cout << "comp1 != comp3: " << (comp1 != comp3 ? "true" : "false") << endl;
  cout << "comp1 < comp3: " << (comp1 < comp3 ? "true" : "false") << endl;

  // ======================= FINDING SUBSTRING =======================
  cout << endl << "7. FINDING SUBSTRING:" << endl;

  string text_search = "The quick brown fox";
  string find_str = "brown";

  size_t pos = text_search.find(find_str);

  cout << "String: " << text_search << endl;
  cout << "Finding: '" << find_str << "'" << endl;
  if (pos != string::npos) {
    cout << "Found at position: " << pos << endl;
  } else {
    cout << "Not found" << endl;
  }

  // ======================= SUBSTRING EXTRACTION =======================
  cout << endl << "8. SUBSTRING EXTRACTION:" << endl;

  string text_sub = "Hello World";
  string sub1 = text_sub.substr(0, 5); // Starting at 0, length 5
  string sub2 = text_sub.substr(6);    // From position 6 to end

  cout << "Original: " << text_sub << endl;
  cout << "substr(0, 5): " << sub1 << endl;
  cout << "substr(6): " << sub2 << endl;

  // ======================= REPLACING SUBSTRING =======================
  cout << endl << "9. REPLACING SUBSTRING:" << endl;

  string text_replace = "I like cats";
  cout << "Original: " << text_replace << endl;

  size_t pos_replace = text_replace.find("cats");
  if (pos_replace != string::npos) {
    text_replace.replace(pos_replace, 4, "dogs"); // Replace 4 chars with "dogs"
  }
  cout << "After replace: " << text_replace << endl;

  // ======================= ERASING CHARACTERS =======================
  cout << endl << "10. ERASING CHARACTERS:" << endl;

  string text_erase = "Hello World!";
  cout << "Original: " << text_erase << endl;

  text_erase.erase(5, 6); // Erase 6 characters starting at position 5
  cout << "After erase: " << text_erase << endl;

  // ======================= CONVERTING TO UPPERCASE/LOWERCASE
  // =======================
  cout << endl << "11. CONVERTING CASE:" << endl;

  string text_case = "Hello World";
  cout << "Original: " << text_case << endl;

  // Convert to uppercase
  string uppercase = text_case;
  for (auto &c : uppercase) {
    c = toupper(c);
  }
  cout << "Uppercase: " << uppercase << endl;

  // Convert to lowercase
  string lowercase = text_case;
  for (auto &c : lowercase) {
    c = tolower(c);
  }
  cout << "Lowercase: " << lowercase << endl;

  // ======================= REVERSING STRING =======================
  cout << endl << "12. REVERSING STRING:" << endl;

  string text_reverse = "Hello";
  cout << "Original: " << text_reverse << endl;

  reverse(text_reverse.begin(), text_reverse.end());
  cout << "Reversed: " << text_reverse << endl;

  // ======================= CHECKING PALINDROME =======================
  cout << endl << "13. CHECKING PALINDROME:" << endl;

  string palindrome = "racecar";
  string palindrome_check = palindrome;
  reverse(palindrome_check.begin(), palindrome_check.end());

  cout << "String: " << palindrome << endl;
  cout << "Is palindrome: " << (palindrome == palindrome_check ? "Yes" : "No")
       << endl;

  // ======================= COUNTING CHARACTERS =======================
  cout << endl << "14. COUNTING CHARACTER OCCURRENCES:" << endl;

  string text_count = "Mississippi";
  char target_char = 's';
  int count = 0;

  for (char c : text_count) {
    if (c == target_char) {
      count++;
    }
  }

  cout << "String: " << text_count << endl;
  cout << "Character '" << target_char << "' appears " << count << " times"
       << endl;

  // ======================= SPLITTING STRING =======================
  cout << endl << "15. EXTRACTING WORDS (Simple Word Count):" << endl;

  string sentence = "The quick brown fox";
  int word_count = 0;
  for (int i = 0; i < sentence.length(); i++) {
    if (sentence[i] == ' ') {
      word_count++;
    }
  }
  cout << "Sentence: " << sentence << endl;
  cout << "Number of words: " << (word_count + 1) << endl;

  return 0;
}

/*
OUTPUT:
=== std::string (Modern C++ Strings) ===

1. STRING CREATION:
empty_str: ''
str1: Hello
str2: World
str3: aaaaa

2. STRING LENGTH AND SIZE:
String: Programming
Length: 11
Size: 11
Empty: No

3. ACCESSING CHARACTERS:
String: Program
First character: P
Third character: o
At index 4: a

4. MODIFYING CHARACTERS:
Original: Hello
After changing first: Jello
After changing second: Jallo

5. CONCATENATION:
first: Hello
second:  World
result: Hello World
first after +=: Hello!
After append: Learn C++

6. STRING COMPARISON:
comp1: apple
comp2: apple
comp3: banana
comp1 == comp2: true
comp1 != comp3: true
comp1 < comp3: true

7. FINDING SUBSTRING:
String: The quick brown fox
Finding: 'brown'
Found at position: 10

8. SUBSTRING EXTRACTION:
Original: Hello World
substr(0, 5): Hello
substr(6): World

9. REPLACING SUBSTRING:
Original: I like cats
After replace: I like dogs

10. ERASING CHARACTERS:
Original: Hello World!
After erase: Hello!

11. CONVERTING CASE:
Original: Hello World
Uppercase: HELLO WORLD
Lowercase: hello world

12. REVERSING STRING:
Original: Hello
Reversed: olleH

13. CHECKING PALINDROME:
String: racecar
Is palindrome: Yes

14. COUNTING CHARACTER OCCURRENCES:
String: Mississippi
Character 's' appears 4 times

15. EXTRACTING WORDS (Simple Word Count):
Sentence: The quick brown fox
Number of words: 4

================================================================================
KEY CONCEPTS
================================================================================

1. STRING::NPOS:
   - Special value indicating "not found"
   - Used as return value for find()

2. USEFUL METHODS:
   - length(), size()     : Get length
   - empty()              : Check if empty
   - find(substr)         : Find substring
   - substr(pos, len)     : Extract substring
   - replace(pos, len, str) : Replace substring
   - erase(pos, len)      : Erase characters
   - at(index)            : Access with bounds check
   - operator[]           : Access without bounds check

3. ITERATORS:
   - begin(), end()       : For range-based loops
   - Can use with algorithms: sort, reverse, find, etc.

4. OPERATORS:
   - +, +=                : Concatenation
   - ==, !=, <, >, <=, >= : Comparison
   - []                   : Character access

5. SAFETY FEATURES:
   - Automatic memory management
   - No buffer overflow
   - Bounds checking with at()
   - Can throw exceptions

================================================================================
PRACTICE EXERCISES
================================================================================

1. Count total vowels and consonants in string

2. Check if string is valid email (basic check)

3. Remove all vowels from string

4. Replace all spaces with underscores

5. Check if two strings are anagrams

6. Find longest word in a sentence

7. Implement simple string encryption/decryption

8. Check if string contains only digits

9. Remove duplicate characters from string

10. Implement simple text search and replace

================================================================================
*/
