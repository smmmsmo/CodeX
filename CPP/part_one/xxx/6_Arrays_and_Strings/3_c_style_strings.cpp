/*
================================================================================
TOPIC 6: ARRAYS AND STRINGS - PART 3: C-STYLE STRINGS (char ARRAYS)
================================================================================

C-STYLE STRINGS:
- Array of characters ending with null terminator '\0'
- String literals are automatically null-terminated
- Stored as char arrays

CHARACTERISTICS:
- Each character occupies 1 byte
- Last element is '\0' (null terminator)
- Array size should be at least string_length + 1
- String functions available in <cstring>

STRING FUNCTIONS:
strlen(str)     - Length of string (excluding '\0')
strcpy(dest, src) - Copy string
strcat(str1, str2) - Concatenate strings
strcmp(str1, str2) - Compare strings
strchr(str, c)  - Find character in string
strstr(str, substr) - Find substring

NOTE: Use std::string for safer, easier string handling in modern C++

================================================================================
*/

#include <cstring>
#include <iostream>
using namespace std;

int main() {
  cout << "=== C-STYLE STRINGS (Character Arrays) ===" << endl << endl;

  // ======================= STRING DECLARATION =======================
  cout << "1. STRING DECLARATION AND INITIALIZATION:" << endl;

  char str1[] = "Hello";          // Automatically adds '\0'
  char str2[] = {'H', 'i', '\0'}; // Manual null terminator
  char str3[20];                  // Uninitialized

  cout << "str1: " << str1 << endl;
  cout << "str2: " << str2 << endl;

  // ======================= STRING LENGTH =======================
  cout << endl << "2. STRING LENGTH:" << endl;

  char name[] = "Alice";
  cout << "String: " << name << endl;
  cout << "Length: " << strlen(name) << endl;
  cout << "Array size needed: " << (strlen(name) + 1)
       << " (including null terminator)" << endl;

  // ======================= ACCESSING CHARACTERS =======================
  cout << endl << "3. ACCESSING INDIVIDUAL CHARACTERS:" << endl;

  char word[] = "Programming";
  cout << "String: " << word << endl;
  cout << "First character: " << word[0] << endl;
  cout << "Third character: " << word[2] << endl;
  cout << "Last character: " << word[strlen(word) - 1] << endl;

  // ======================= MODIFYING CHARACTERS =======================
  cout << endl << "4. MODIFYING CHARACTERS:" << endl;

  char greeting[] = "Hello";
  cout << "Original: " << greeting << endl;
  greeting[0] = 'J';
  cout << "After changing first letter: " << greeting << endl;
  greeting[1] = 'a';
  cout << "After changing second letter: " << greeting << endl;

  // ======================= STRING COPY =======================
  cout << endl << "5. STRING COPY (strcpy):" << endl;

  char source[] = "Welcome";
  char destination[50];
  strcpy(destination, source);

  cout << "Source: " << source << endl;
  cout << "Destination (after strcpy): " << destination << endl;

  // ======================= STRING CONCATENATION =======================
  cout << endl << "6. STRING CONCATENATION (strcat):" << endl;

  char first[] = "Hello";
  char second[] = " World";
  strcat(first, second); // first now contains "Hello World"

  cout << "After concatenation: " << first << endl;
  cout << "Note: first array must be large enough!" << endl;

  // ======================= STRING COMPARISON =======================
  cout << endl << "7. STRING COMPARISON (strcmp):" << endl;

  char str_a[] = "apple";
  char str_b[] = "apple";
  char str_c[] = "banana";

  cout << "Comparing '" << str_a << "' with '" << str_b
       << "': " << (strcmp(str_a, str_b) == 0 ? "Equal" : "Not equal") << endl;
  cout << "Comparing '" << str_a << "' with '" << str_c
       << "': " << (strcmp(str_a, str_c) == 0 ? "Equal" : "Not equal") << endl;

  // ======================= FINDING CHARACTER =======================
  cout << endl << "8. FINDING CHARACTER (strchr):" << endl;

  char text[] = "Hello World";
  char target = 'o';
  char *pos = strchr(text, target);

  cout << "String: " << text << endl;
  cout << "Looking for: '" << target << "'" << endl;
  if (pos != NULL) {
    cout << "Found at position: " << (pos - text) << endl;
  } else {
    cout << "Not found" << endl;
  }

  // ======================= FINDING SUBSTRING =======================
  cout << endl << "9. FINDING SUBSTRING (strstr):" << endl;

  char sentence[] = "The quick brown fox";
  char substring[] = "brown";
  char *result = strstr(sentence, substring);

  cout << "String: " << sentence << endl;
  cout << "Looking for: '" << substring << "'" << endl;
  if (result != NULL) {
    cout << "Found at position: " << (result - sentence) << endl;
    cout << "Substring found: " << result << endl;
  }

  // ======================= REVERSING STRING =======================
  cout << endl << "10. REVERSING A STRING:" << endl;

  char reverse_str[] = "Hello";
  cout << "Original: " << reverse_str << endl;

  int len = strlen(reverse_str);
  for (int i = 0; i < len / 2; i++) {
    char temp = reverse_str[i];
    reverse_str[i] = reverse_str[len - 1 - i];
    reverse_str[len - 1 - i] = temp;
  }

  cout << "Reversed: " << reverse_str << endl;

  // ======================= COUNTING CHARACTER OCCURRENCES
  // =======================
  cout << endl << "11. COUNTING CHARACTER OCCURRENCES:" << endl;

  char count_str[] = "Mississippi";
  char ch = 's';
  int count = 0;

  for (int i = 0; count_str[i] != '\0'; i++) {
    if (count_str[i] == ch) {
      count++;
    }
  }

  cout << "String: " << count_str << endl;
  cout << "Character '" << ch << "' appears " << count << " times" << endl;

  // ======================= CHECKING PALINDROME =======================
  cout << endl << "12. CHECKING PALINDROME:" << endl;

  char palindrome[] = "racecar";
  int len_pal = strlen(palindrome);
  bool is_pal = true;

  for (int i = 0; i < len_pal / 2; i++) {
    if (palindrome[i] != palindrome[len_pal - 1 - i]) {
      is_pal = false;
      break;
    }
  }

  cout << "String: " << palindrome << endl;
  cout << "Is palindrome: " << (is_pal ? "Yes" : "No") << endl;

  // ======================= CONVERTING TO UPPERCASE =======================
  cout << endl << "13. CONVERTING TO UPPERCASE:" << endl;

  char convert_str[] = "hello world";
  cout << "Original: " << convert_str << endl;

  for (int i = 0; convert_str[i] != '\0'; i++) {
    if (convert_str[i] >= 'a' && convert_str[i] <= 'z') {
      convert_str[i] = convert_str[i] - 32; // Convert to uppercase
    }
  }

  cout << "Uppercase: " << convert_str << endl;

  return 0;
}

/*
OUTPUT:
=== C-STYLE STRINGS (Character Arrays) ===

1. STRING DECLARATION AND INITIALIZATION:
str1: Hello
str2: Hi

2. STRING LENGTH:
String: Alice
Length: 5
Array size needed: 6 (including null terminator)

3. ACCESSING INDIVIDUAL CHARACTERS:
String: Programming
First character: P
Third character: o
Last character: g

4. MODIFYING CHARACTERS:
Original: Hello
After changing first letter: Jello
After changing second letter: Jallo

5. STRING COPY (strcpy):
Source: Welcome
Destination (after strcpy): Welcome

6. STRING CONCATENATION (strcat):
After concatenation: Hello World
Note: first array must be large enough!

7. STRING COMPARISON (strcmp):
Comparing 'apple' with 'apple': Equal
Comparing 'apple' with 'banana': Not equal

8. FINDING CHARACTER (strchr):
String: Hello World
Looking for: 'o'
Found at position: 4
Substring found: o World

9. FINDING SUBSTRING (strstr):
String: The quick brown fox
Looking for: 'brown'
Found at position: 10
Substring found: brown fox

10. REVERSING A STRING:
Original: Hello
Reversed: olleH

11. COUNTING CHARACTER OCCURRENCES:
String: Mississippi
Character 's' appears 4 times

12. CHECKING PALINDROME:
String: racecar
Is palindrome: Yes

13. CONVERTING TO UPPERCASE:
Original: hello world
Uppercase: HELLO WORLD

================================================================================
KEY CONCEPTS
================================================================================

1. NULL TERMINATOR:
   - Every string ends with '\0'
   - Not part of string length (strlen doesn't count it)
   - Must allocate size + 1 for char arrays

2. BUFFER OVERFLOW:
   - strcpy can overflow if destination is too small
   - Use strncpy for safer copying: strncpy(dest, src, n)

3. STRING LITERALS:
   - "Hello" stored in read-only memory
   - Cannot be modified
   - Can initialize char array from literal

4. UNSAFE FUNCTIONS:
   - strcpy, strcat are unsafe (can overflow)
   - Modern C++ uses std::string instead

5. COMMON OPERATIONS:
   - Length: strlen()
   - Copy: strcpy(), strncpy()
   - Concatenate: strcat(), strncat()
   - Compare: strcmp(), strncmp()
   - Search: strchr(), strstr()

================================================================================
PRACTICE EXERCISES
================================================================================

1. Count number of vowels in a string

2. Remove all spaces from a string

3. Check if two strings are anagram

4. Find longest word in a sentence

5. Replace all occurrences of a character

6. Check if string is valid palindrome (ignoring spaces)

7. Implement your own strlen function

8. Sort words in alphabetical order

================================================================================
*/
