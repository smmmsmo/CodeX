#include <cstring>
#include <iostream>
using namespace std;

/*
 * =====================================================================
 * TOPIC 6.3: C-STYLE STRINGS (Character Arrays)
 * =====================================================================
 *
 * WHAT ARE C-STYLE STRINGS?
 * C-style strings are null-terminated character arrays inherited from C.
 * They are fundamental to understanding how strings work at low level
 * and are still used in competitive programming and system programming.
 *
 * KEY CONCEPTS COVERED:
 * 1. Character arrays and null terminator
 * 2. String declaration and initialization
 * 3. String input and output
 * 4. String library functions (cstring)
 * 5. String manipulation (copy, concatenate, compare)
 * 6. String length calculation
 * 7. Character-by-character processing
 * 8. Common string algorithms
 * 9. String reversal and palindrome
 * 10. Substring operations
 * 11. String tokenization
 * 12. Character classification functions
 *
 * =====================================================================
 * C-STRING BASICS
 * =====================================================================
 *
 * DECLARATION:
 *    char str[size];              // Character array
 *    char str[] = "Hello";        // Null-terminated string
 *
 * NULL TERMINATOR:
 *    - Strings end with '\0' (null character, ASCII 0)
 *    - "Hello" is stored as: 'H' 'e' 'l' 'l' 'o' '\0'
 *    - Length = 5, but array size = 6
 *
 * MEMORY:
 *    char str[] = "Hi";
 *    Memory: ['H']['i']['\0']
 *    sizeof(str) = 3, strlen(str) = 2
 *
 * IMPORTANT:
 *    - Always account for null terminator in size
 *    - String literals are read-only
 *    - Array must be large enough for string + '\0'
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: STRING DECLARATION AND INITIALIZATION
// ==============
void example1_string_declaration() {
  cout << "\n============== EXAMPLE 1: STRING DECLARATION =============="
       << endl;
  cout << "Different ways to create C-style strings\n" << endl;

  // Method 1: String literal
  char str1[] = "Hello";
  cout << "Method 1 - String literal:" << endl;
  cout << "str1 = \"" << str1 << "\"" << endl;
  cout << "sizeof(str1) = " << sizeof(str1) << " (includes \\0)" << endl;
  cout << "strlen(str1) = " << strlen(str1) << " (excludes \\0)" << endl;

  // Method 2: Character array with size
  char str2[20] = "World";
  cout << "\nMethod 2 - Array with size:" << endl;
  cout << "str2 = \"" << str2 << "\"" << endl;
  cout << "sizeof(str2) = " << sizeof(str2) << endl;
  cout << "strlen(str2) = " << strlen(str2) << endl;

  // Method 3: Character by character
  char str3[6];
  str3[0] = 'H';
  str3[1] = 'e';
  str3[2] = 'l';
  str3[3] = 'l';
  str3[4] = 'o';
  str3[5] = '\0'; // Must add null terminator!
  cout << "\nMethod 3 - Character by character:" << endl;
  cout << "str3 = \"" << str3 << "\"" << endl;

  // Method 4: Empty string
  char str4[10] = "";
  cout << "\nMethod 4 - Empty string:" << endl;
  cout << "str4 = \"" << str4 << "\"" << endl;
  cout << "strlen(str4) = " << strlen(str4) << endl;

  cout << "\nKey Point: Null terminator '\\0' is essential!" << endl;
}

// ============== EXAMPLE 2: STRING INPUT AND OUTPUT ==============
void example2_string_io() {
  cout << "\n============== EXAMPLE 2: STRING INPUT/OUTPUT =============="
       << endl;
  cout << "Different ways to read and print strings\n" << endl;

  char str1[50];

  // Using cin (reads until whitespace)
  cout << "Using cin (reads one word):" << endl;
  cout << "Enter a word: ";
  cin >> str1;
  cout << "You entered: " << str1 << endl;
  cin.ignore(); // Clear newline from buffer

  // Using cin.getline() (reads entire line)
  char str2[100];
  cout << "\nUsing cin.getline() (reads line with spaces):" << endl;
  cout << "Enter a sentence: ";
  cin.getline(str2, 100);
  cout << "You entered: " << str2 << endl;

  // Using gets() - DANGEROUS, DON'T USE (no bounds checking)
  // gets(str); // Deprecated and unsafe!

  // Character output
  cout << "\nCharacter-by-character output:" << endl;
  char str3[] = "Test";
  for (int i = 0; str3[i] != '\0'; i++) {
    cout << str3[i] << " ";
  }
  cout << endl;

  cout << "\nNote: cin stops at whitespace, use getline() for full input"
       << endl;
}

// ============== EXAMPLE 3: STRING LIBRARY FUNCTIONS ==============
void example3_string_functions() {
  cout << "\n============== EXAMPLE 3: STRING LIBRARY FUNCTIONS =============="
       << endl;
  cout << "Common functions from <cstring>\n" << endl;

  char str1[50] = "Hello";
  char str2[50] = "World";
  char str3[50];

  // strlen() - Get string length
  cout << "strlen(\"" << str1 << "\") = " << strlen(str1) << endl;

  // strcpy() - Copy string
  strcpy(str3, str1);
  cout << "strcpy(str3, \"" << str1 << "\") -> str3 = \"" << str3 << "\""
       << endl;

  // strcat() - Concatenate strings
  char str4[50] = "Hello ";
  strcat(str4, "World");
  cout << "strcat(\"Hello \", \"World\") = \"" << str4 << "\"" << endl;

  // strcmp() - Compare strings
  cout << "\nstrcmp comparisons:" << endl;
  cout << "strcmp(\"Hello\", \"Hello\") = " << strcmp("Hello", "Hello")
       << " (equal)" << endl;
  cout << "strcmp(\"Apple\", \"Banana\") = " << strcmp("Apple", "Banana")
       << " (negative)" << endl;
  cout << "strcmp(\"Zebra\", \"Apple\") = " << strcmp("Zebra", "Apple")
       << " (positive)" << endl;

  // strncpy() - Copy n characters
  char str5[50] = "Programming";
  char str6[50];
  strncpy(str6, str5, 7);
  str6[7] = '\0'; // Add null terminator
  cout << "\nstrncpy(str6, \"Programming\", 7) = \"" << str6 << "\"" << endl;

  // strchr() - Find character
  char str7[] = "Hello World";
  char *ptr = strchr(str7, 'W');
  if (ptr != NULL) {
    cout << "strchr(\"Hello World\", 'W') found at position: " << (ptr - str7)
         << endl;
  }

  // strstr() - Find substring
  char *pos = strstr(str7, "World");
  if (pos != NULL) {
    cout << "strstr(\"Hello World\", \"World\") found at position: "
         << (pos - str7) << endl;
  }
}

// ============== EXAMPLE 4: STRING LENGTH CALCULATION ==============
int string_length(char str[]) {
  int length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
}

void example4_string_length() {
  cout << "\n============== EXAMPLE 4: STRING LENGTH ==============" << endl;
  cout << "Calculate length manually and using strlen()\n" << endl;

  char str[] = "Competitive Programming";

  cout << "String: \"" << str << "\"" << endl;
  cout << "Manual length: " << string_length(str) << endl;
  cout << "strlen() length: " << strlen(str) << endl;
  cout << "sizeof() array: " << sizeof(str) << " (includes \\0)" << endl;

  // Empty string
  char empty[] = "";
  cout << "\nEmpty string:" << endl;
  cout << "strlen(\"\") = " << strlen(empty) << endl;

  cout << "\nDifference: strlen() counts chars until \\0, sizeof() returns "
          "array size"
       << endl;
}

// ============== EXAMPLE 5: STRING REVERSAL ==============
void reverse_string(char str[]) {
  int len = strlen(str);
  int left = 0, right = len - 1;

  while (left < right) {
    // Swap characters
    char temp = str[left];
    str[left] = str[right];
    str[right] = temp;
    left++;
    right--;
  }
}

void example5_string_reversal() {
  cout << "\n============== EXAMPLE 5: STRING REVERSAL ==============" << endl;
  cout << "Reverse string using two pointers - O(n)\n" << endl;

  char str1[] = "Hello";
  cout << "Original: \"" << str1 << "\"" << endl;
  reverse_string(str1);
  cout << "Reversed: \"" << str1 << "\"" << endl;

  char str2[] = "Competitive";
  cout << "\nOriginal: \"" << str2 << "\"" << endl;
  reverse_string(str2);
  cout << "Reversed: \"" << str2 << "\"" << endl;

  cout << "\nAlgorithm: Swap characters from both ends moving inward" << endl;
  cout << "Time Complexity: O(n)" << endl;
  cout << "Space Complexity: O(1)" << endl;
}

// ============== EXAMPLE 6: PALINDROME CHECK ==============
bool is_palindrome(char str[]) {
  int len = strlen(str);
  int left = 0, right = len - 1;

  while (left < right) {
    if (str[left] != str[right]) {
      return false;
    }
    left++;
    right--;
  }
  return true;
}

void example6_palindrome() {
  cout << "\n============== EXAMPLE 6: PALINDROME CHECK ==============" << endl;
  cout << "Check if string reads same forwards and backwards - O(n)\n" << endl;

  char test1[] = "racecar";
  char test2[] = "hello";
  char test3[] = "madam";
  char test4[] = "noon";

  cout << "\"" << test1 << "\" is " << (is_palindrome(test1) ? "" : "not ")
       << "a palindrome" << endl;
  cout << "\"" << test2 << "\" is " << (is_palindrome(test2) ? "" : "not ")
       << "a palindrome" << endl;
  cout << "\"" << test3 << "\" is " << (is_palindrome(test3) ? "" : "not ")
       << "a palindrome" << endl;
  cout << "\"" << test4 << "\" is " << (is_palindrome(test4) ? "" : "not ")
       << "a palindrome" << endl;

  cout << "\nAlgorithm: Compare characters from both ends" << endl;
  cout << "Time Complexity: O(n)" << endl;
}

// ============== EXAMPLE 7: STRING COPY ==============
void string_copy(char dest[], const char src[]) {
  int i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0'; // Don't forget null terminator!
}

void example7_string_copy() {
  cout << "\n============== EXAMPLE 7: STRING COPY ==============" << endl;
  cout << "Copy string manually and using strcpy()\n" << endl;

  char source[] = "Programming";
  char dest1[50], dest2[50];

  // Manual copy
  string_copy(dest1, source);
  cout << "Manual copy:" << endl;
  cout << "Source: \"" << source << "\"" << endl;
  cout << "Dest:   \"" << dest1 << "\"" << endl;

  // Using strcpy()
  strcpy(dest2, source);
  cout << "\nUsing strcpy():" << endl;
  cout << "Source: \"" << source << "\"" << endl;
  cout << "Dest:   \"" << dest2 << "\"" << endl;

  cout << "\nWarning: Destination must have enough space!" << endl;
  cout << "Use strncpy() for safer copying with size limit" << endl;
}

// ============== EXAMPLE 8: STRING CONCATENATION ==============
void string_concat(char dest[], const char src[]) {
  int dest_len = strlen(dest);
  int i = 0;

  while (src[i] != '\0') {
    dest[dest_len + i] = src[i];
    i++;
  }
  dest[dest_len + i] = '\0';
}

void example8_string_concat() {
  cout << "\n============== EXAMPLE 8: STRING CONCATENATION =============="
       << endl;
  cout << "Concatenate strings manually and using strcat()\n" << endl;

  char str1[50] = "Hello ";
  char str2[] = "World";

  cout << "Before: \"" << str1 << "\"" << endl;
  string_concat(str1, str2);
  cout << "After concat: \"" << str1 << "\"" << endl;

  // Using strcat()
  char str3[50] = "C++ ";
  char str4[] = "Programming";
  cout << "\nUsing strcat():" << endl;
  cout << "Before: \"" << str3 << "\"" << endl;
  strcat(str3, str4);
  cout << "After: \"" << str3 << "\"" << endl;

  cout << "\nWarning: Ensure destination has enough space!" << endl;
}

// ============== EXAMPLE 9: STRING COMPARISON ==============
int string_compare(const char str1[], const char str2[]) {
  int i = 0;
  while (str1[i] != '\0' && str2[i] != '\0') {
    if (str1[i] < str2[i])
      return -1;
    if (str1[i] > str2[i])
      return 1;
    i++;
  }

  // Check if one string is longer
  if (str1[i] == '\0' && str2[i] == '\0')
    return 0; // Equal
  if (str1[i] == '\0')
    return -1; // str1 shorter
  return 1;    // str2 shorter
}

void example9_string_compare() {
  cout << "\n============== EXAMPLE 9: STRING COMPARISON =============="
       << endl;
  cout << "Compare strings lexicographically\n" << endl;

  const char *pairs[][2] = {{"apple", "apple"},
                            {"apple", "banana"},
                            {"zebra", "apple"},
                            {"cat", "cats"}};

  for (int i = 0; i < 4; i++) {
    int result = string_compare(pairs[i][0], pairs[i][1]);
    cout << "compare(\"" << pairs[i][0] << "\", \"" << pairs[i][1] << "\") = ";
    if (result == 0)
      cout << "0 (equal)";
    else if (result < 0)
      cout << "-1 (first < second)";
    else
      cout << "1 (first > second)";
    cout << endl;
  }

  cout << "\nLexicographic: Compare character by character (dictionary order)"
       << endl;
  cout << "strcmp() returns: 0 (equal), negative (less), positive (greater)"
       << endl;
}

// ============== EXAMPLE 10: CHARACTER CLASSIFICATION ==============
void example10_char_classification() {
  cout << "\n============== EXAMPLE 10: CHARACTER CLASSIFICATION =============="
       << endl;
  cout << "Using character classification functions from <cctype>\n" << endl;

  char test[] = "Hello123!";

  cout << "String: \"" << test << "\"" << endl;
  cout << "\nCharacter analysis:" << endl;

  for (int i = 0; test[i] != '\0'; i++) {
    cout << "'" << test[i] << "': ";

    if (isalpha(test[i]))
      cout << "letter ";
    if (isdigit(test[i]))
      cout << "digit ";
    if (isupper(test[i]))
      cout << "uppercase ";
    if (islower(test[i]))
      cout << "lowercase ";
    if (isspace(test[i]))
      cout << "space ";
    if (ispunct(test[i]))
      cout << "punctuation ";

    cout << endl;
  }

  cout << "\nUseful functions: isalpha, isdigit, isupper, islower, isspace, "
          "ispunct"
       << endl;
}

// ============== EXAMPLE 11: CASE CONVERSION ==============
void to_uppercase(char str[]) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      str[i] = str[i] - 32; // or str[i] - 'a' + 'A'
    }
  }
}

void to_lowercase(char str[]) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      str[i] = str[i] + 32; // or str[i] - 'A' + 'a'
    }
  }
}

void example11_case_conversion() {
  cout << "\n============== EXAMPLE 11: CASE CONVERSION ==============" << endl;
  cout << "Convert string to uppercase/lowercase\n" << endl;

  char str1[] = "Hello World";
  char str2[] = "PROGRAMMING";

  cout << "Original: \"" << str1 << "\"" << endl;
  to_uppercase(str1);
  cout << "Uppercase: \"" << str1 << "\"" << endl;

  cout << "\nOriginal: \"" << str2 << "\"" << endl;
  to_lowercase(str2);
  cout << "Lowercase: \"" << str2 << "\"" << endl;

  cout << "\nASCII difference: 'A'(65) to 'a'(97) = 32" << endl;
  cout << "Can also use toupper() and tolower() from <cctype>" << endl;
}

// ============== EXAMPLE 12: WORD COUNT ==============
int count_words(char str[]) {
  int count = 0;
  bool in_word = false;

  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
      if (!in_word) {
        count++;
        in_word = true;
      }
    } else {
      in_word = false;
    }
  }
  return count;
}

void example12_word_count() {
  cout << "\n============== EXAMPLE 12: WORD COUNT ==============" << endl;
  cout << "Count number of words in a string\n" << endl;

  char str1[] = "Hello World";
  char str2[] = "Competitive Programming is Fun";
  char str3[] = "  Multiple   spaces   between  ";

  cout << "\"" << str1 << "\" -> " << count_words(str1) << " words" << endl;
  cout << "\"" << str2 << "\" -> " << count_words(str2) << " words" << endl;
  cout << "\"" << str3 << "\" -> " << count_words(str3) << " words" << endl;

  cout << "\nAlgorithm: Count transitions from whitespace to non-whitespace"
       << endl;
}

/*
 * =====================================================================
 * KEY CONCEPTS SUMMARY
 * =====================================================================
 *
 * 1. C-STRING FUNDAMENTALS:
 *    - Null-terminated character arrays
 *    - '\0' marks end of string
 *    - strlen() vs sizeof()
 *
 * 2. COMMON OPERATIONS:
 *    - Copy: strcpy(), strncpy()
 *    - Concatenate: strcat(), strncat()
 *    - Compare: strcmp(), strncmp()
 *    - Search: strchr(), strstr()
 *    - Length: strlen()
 *
 * 3. STRING MANIPULATION:
 *    - Reversal: Two pointers - O(n)
 *    - Palindrome: Compare from both ends - O(n)
 *    - Case conversion: +/- 32 for ASCII
 *
 * 4. CHARACTER FUNCTIONS (cctype):
 *    - isalpha(), isdigit(), isupper(), islower()
 *    - isspace(), ispunct(), isalnum()
 *    - toupper(), tolower()
 *
 * 5. INPUT/OUTPUT:
 *    - cin >> : Reads until whitespace
 *    - cin.getline(): Reads entire line
 *    - Never use gets() - unsafe!
 *
 * 6. IMPORTANT RULES:
 *    - Always null-terminate manually created strings
 *    - Ensure destination has enough space
 *    - Check bounds to avoid buffer overflow
 *    - String literals are read-only
 *
 * =====================================================================
 * COMPETITIVE PROGRAMMING TIPS
 * =====================================================================
 *
 * 1. Prefer std::string over C-strings in contests
 * 2. But understand C-strings for low-level problems
 * 3. Use cin.getline() for reading lines with spaces
 * 4. Two-pointer technique works great for strings
 * 5. Remember ASCII values: 'A'=65, 'a'=97, '0'=48
 * 6. Palindrome checking is a common pattern
 * 7. Learn anagram detection (frequency counting)
 * 8. String hashing for pattern matching
 * 9. Practice substring problems
 * 10. KMP algorithm for advanced pattern matching
 *
 * =====================================================================
 * COMMON MISTAKES TO AVOID
 * =====================================================================
 *
 * 1. Forgetting null terminator when creating strings manually
 * 2. Not allocating enough space for string + '\0'
 * 3. Buffer overflow (writing beyond array bounds)
 * 4. Using gets() instead of cin.getline()
 * 5. Comparing strings with == (compares pointers, not content)
 * 6. Not checking if strchr/strstr returns NULL
 * 7. Modifying string literals (undefined behavior)
 * 8. Off-by-one errors in loops
 * 9. Not clearing input buffer after cin >>
 * 10. Assuming strings are always valid/non-empty
 *
 * =====================================================================
 */

int main() {
  cout << "=========================================================" << endl;
  cout << "       C-STYLE STRINGS - COMPREHENSIVE GUIDE             " << endl;
  cout << "=========================================================" << endl;

  example1_string_declaration();
  // example2_string_io(); // Commented out as it requires user input
  example3_string_functions();
  example4_string_length();
  example5_string_reversal();
  example6_palindrome();
  example7_string_copy();
  example8_string_concat();
  example9_string_compare();
  example10_char_classification();
  example11_case_conversion();
  example12_word_count();

  cout << "\n=========================================================" << endl;
  cout << "         PRACTICE EXERCISES" << endl;
  cout << "=========================================================" << endl;
  cout << "\n1. Check if two strings are anagrams" << endl;
  cout << "2. Remove all duplicate characters from string" << endl;
  cout << "3. Find first non-repeating character" << endl;
  cout << "4. Check if string has all unique characters" << endl;
  cout << "5. Reverse words in a sentence" << endl;
  cout << "6. Check if one string is rotation of another" << endl;
  cout << "7. Count frequency of each character" << endl;
  cout << "8. Remove all spaces from string" << endl;
  cout << "9. Find longest palindromic substring" << endl;
  cout << "10. Implement strstr() function from scratch" << endl;

  return 0;
}
