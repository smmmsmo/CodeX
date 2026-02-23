/*
================================================================================
TOPIC 2: VARIABLES AND DATA TYPES - PART 1: PRIMITIVE DATA TYPES
================================================================================

PRIMITIVE DATA TYPES IN C++:
1. Integers: int, short, long, long long
2. Floating-point: float, double, long double
3. Character: char
4. Boolean: bool

SIZE AND RANGE:
- int: 4 bytes (on most systems), range: -2^31 to 2^31-1
- short: 2 bytes, range: -2^15 to 2^15-1
- long: 4 or 8 bytes
- long long: 8 bytes
- float: 4 bytes, ~6-7 decimal digits precision
- double: 8 bytes, ~15-17 decimal digits precision
- char: 1 byte, stores single character (ASCII value 0-127)
- bool: 1 byte, values: true (1) or false (0)

================================================================================
*/

#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

int main() {
  cout << "=== PRIMITIVE DATA TYPES EXAMPLES ===" << endl << endl;

  // ======================= INTEGER TYPES =======================
  cout << "1. INTEGER TYPES:" << endl;

  int age = 25;
  short year_diff = 10;
  long population = 8000000000;
  long long large_number = 123456789123456LL;

  cout << "int age = " << age << " (size: " << sizeof(int) << " bytes)" << endl;
  cout << "short year_diff = " << year_diff << " (size: " << sizeof(short)
       << " bytes)" << endl;
  cout << "long population = " << population << " (size: " << sizeof(long)
       << " bytes)" << endl;
  cout << "long long large_number = " << large_number
       << " (size: " << sizeof(long long) << " bytes)" << endl;

  cout << endl << "Int Range: " << INT_MIN << " to " << INT_MAX << endl;
  cout << "Short Range: " << SHRT_MIN << " to " << SHRT_MAX << endl;

  // ======================= FLOATING-POINT TYPES =======================
  cout << endl << "2. FLOATING-POINT TYPES:" << endl;

  float pi_approx = 3.14f; // Need 'f' suffix for float
  double pi_precise = 3.14159265359;
  long double pi_very_precise = 3.14159265358979323846L;

  cout << fixed << setprecision(10);
  cout << "float pi_approx = " << pi_approx << " (size: " << sizeof(float)
       << " bytes)" << endl;
  cout << "double pi_precise = " << pi_precise << " (size: " << sizeof(double)
       << " bytes)" << endl;
  cout << "long double pi_very_precise = " << pi_very_precise
       << " (size: " << sizeof(long double) << " bytes)" << endl;

  // ======================= CHARACTER TYPE =======================
  cout << endl << "3. CHARACTER TYPE:" << endl;

  char first_initial = 'A';
  char last_initial = 'B';
  int ascii_value = 'A'; // Characters are stored as ASCII values

  cout << "char first_initial = '" << first_initial
       << "' (ASCII value: " << (int)first_initial << ")" << endl;
  cout << "char last_initial = '" << last_initial
       << "' (ASCII value: " << (int)last_initial << ")" << endl;
  cout << "Size of char: " << sizeof(char) << " byte" << endl;

  // ======================= BOOLEAN TYPE =======================
  cout << endl << "4. BOOLEAN TYPE:" << endl;

  bool is_student = true;
  bool is_working = false;

  cout << "bool is_student = " << is_student << " (size: " << sizeof(bool)
       << " byte)" << endl;
  cout << "bool is_working = " << is_working << " (size: " << sizeof(bool)
       << " byte)" << endl;
  cout << "Note: true = 1, false = 0" << endl;

  // ======================= TYPE MODIFIERS =======================
  cout << endl << "5. TYPE MODIFIERS:" << endl;

  signed int signed_num = -50;
  unsigned int unsigned_num = 50;

  cout << "signed int signed_num = " << signed_num << endl;
  cout << "unsigned int unsigned_num = " << unsigned_num << endl;
  cout << "Max unsigned int: " << UINT_MAX << endl;

  return 0;
}

/*
OUTPUT:
=== PRIMITIVE DATA TYPES EXAMPLES ===

1. INTEGER TYPES:
int age = 25 (size: 4 bytes)
short year_diff = 10 (size: 2 bytes)
long population = 8000000000 (size: 8 bytes)
long long large_number = 123456789123456 (size: 8 bytes)

Int Range: -2147483648 to 2147483647
Short Range: -32768 to 32767

2. FLOATING-POINT TYPES:
float pi_approx = 3.1400000095 (size: 4 bytes)
double pi_precise = 3.1415926536 (size: 8 bytes)
long double pi_very_precise = 3.1415926536 (size: 16 bytes)

3. CHARACTER TYPE:
char first_initial = 'A' (ASCII value: 65)
char last_initial = 'B' (ASCII value: 66)
Size of char: 1 byte

4. BOOLEAN TYPE:
bool is_student = 1 (size: 1 byte)
bool is_working = 0 (size: 1 byte)
Note: true = 1, false = 0

5. TYPE MODIFIERS:
signed int signed_num = -50
unsigned int unsigned_num = 50
Max unsigned int: 4294967295

================================================================================
KEY POINTS
================================================================================

1. CHOOSE APPROPRIATE TYPE:
   - Use int for most integer calculations
   - Use short/long only when necessary
   - Use float for memory-constrained scenarios
   - Use double for scientific/financial calculations
   - Use bool for logical values

2. LITERALS:
   - Integer: 123, 0x1F (hex), 0b101 (binary)
   - Float: 3.14f
   - Double: 3.14 (default), 3.14d
   - Character: 'A', '\n' (escape sequences)
   - String: "Hello"

3. SIGNED vs UNSIGNED:
   - signed: can represent negative numbers
   - unsigned: only positive numbers, wider range

4. sizeof() OPERATOR:
   - Returns size of data type in bytes
   - Useful for understanding memory usage

================================================================================
PRACTICE EXERCISES
================================================================================

1. Create variables for: height (float), weight (float), age (int), name (char)

2. Print the size of all primitive data types

3. Create a program that calculates: person's height in inches and cm

4. Store ASCII value 65 in an int, then print it as both number and character

5. Calculate BMI using height and weight variables

================================================================================
*/
