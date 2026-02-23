/*
================================================================================
TOPIC 9: CLASSES AND OBJECTS - PART 4: COPY CONSTRUCTOR AND OBJECT ASSIGNMENT
================================================================================

COPY CONSTRUCTOR:
- Constructor that initializes object from another object
- Syntax: ClassName(const ClassName& other)
- Called when object is copied (by value, initialization)
- Default version does shallow copy

SHALLOW vs DEEP COPY:
- Shallow: Copies member variables directly (pointers point to same memory)
- Deep: Duplicates pointed-to data (each object has its own data)
- Problem: Two objects managing same memory → double delete!

COPY ASSIGNMENT OPERATOR:
- Operator= function
- Syntax: ClassName& operator=(const ClassName& other)
- Called when assigning one object to another
- Must handle self-assignment
- Must free old resources

WHEN COPY HAPPENS:
1. Object initialization from another: ClassName obj2 = obj1;
2. Pass object by value: function(ClassName obj)
3. Return object by value: return ClassName obj;

THE RULE OF FIVE (C++11 and later):
If you define any of these, define all:
1. Destructor
2. Copy Constructor
3. Copy Assignment Operator
4. Move Constructor (C++11)
5. Move Assignment Operator (C++11)

================================================================================
*/

#include <cstring>
#include <iostream>
#include <string>
using namespace std;

// ======================= CLASS WITH SHALLOW COPY (PROBLEMATIC)
// =======================
class StringShallow {
private:
  char *data;
  int length;

public:
  StringShallow(const char *str = "") {
    if (str) {
      length = strlen(str);
      data = new char[length + 1];
      strcpy(data, str);
    } else {
      length = 0;
      data = new char[1];
      data[0] = '\0';
    }
    cout << "Constructor: Created StringShallow with \"" << data << "\""
         << endl;
  }

  // DEFAULT COPY CONSTRUCTOR (Shallow Copy - PROBLEMATIC)
  // StringShallow(const StringShallow& other) {
  //     data = other.data;      // PROBLEM: Both point to same memory!
  //     length = other.length;
  // }

  ~StringShallow() {
    cout << "Destructor: Deleting StringShallow \"" << data << "\"" << endl;
    delete[] data;
  }

  void display() const {
    cout << "Data: \"" << data << "\", Length: " << length << endl;
  }
};

// ======================= CLASS WITH DEEP COPY (CORRECT)
// =======================
class StringDeep {
private:
  char *data;
  int length;

public:
  StringDeep(const char *str = "") {
    if (str) {
      length = strlen(str);
      data = new char[length + 1];
      strcpy(data, str);
    } else {
      length = 0;
      data = new char[1];
      data[0] = '\0';
    }
    cout << "Constructor: Created StringDeep with \"" << data << "\"" << endl;
  }

  // CUSTOM COPY CONSTRUCTOR (Deep Copy - CORRECT)
  StringDeep(const StringDeep &other) {
    cout << "Copy Constructor: Copying \"" << other.data << "\"" << endl;
    length = other.length;
    data = new char[length + 1]; // Allocate new memory
    strcpy(data, other.data);    // Copy data
  }

  // Copy Assignment Operator
  StringDeep &operator=(const StringDeep &other) {
    cout << "Assignment Operator: Assigning \"" << other.data << "\"" << endl;

    // Self-assignment check
    if (this == &other) {
      return *this;
    }

    // Free old data
    delete[] data;

    // Copy new data
    length = other.length;
    data = new char[length + 1];
    strcpy(data, other.data);

    return *this;
  }

  ~StringDeep() {
    cout << "Destructor: Deleting StringDeep \"" << data << "\"" << endl;
    delete[] data;
  }

  void display() const {
    cout << "Data: \"" << data << "\", Length: " << length << endl;
  }
};

// ======================= DYNAMIC ARRAY CLASS =======================
class DynamicArray {
private:
  int *arr;
  int size;

public:
  DynamicArray(int s = 0) {
    cout << "Constructor: Creating array of size " << s << endl;
    size = s;
    arr = new int[size];
    for (int i = 0; i < size; i++) {
      arr[i] = 0;
    }
  }

  // Copy Constructor
  DynamicArray(const DynamicArray &other) {
    cout << "Copy Constructor: Copying array of size " << other.size << endl;
    size = other.size;
    arr = new int[size]; // Allocate new memory
    for (int i = 0; i < size; i++) {
      arr[i] = other.arr[i]; // Copy data
    }
  }

  // Copy Assignment Operator
  DynamicArray &operator=(const DynamicArray &other) {
    cout << "Assignment Operator: Assigning array of size " << other.size
         << endl;

    // Self-assignment check
    if (this == &other) {
      cout << "Self-assignment detected, skipping" << endl;
      return *this;
    }

    // Free old memory
    delete[] arr;

    // Allocate and copy new data
    size = other.size;
    arr = new int[size];
    for (int i = 0; i < size; i++) {
      arr[i] = other.arr[i];
    }

    return *this;
  }

  ~DynamicArray() {
    cout << "Destructor: Deleting array of size " << size << endl;
    delete[] arr;
  }

  void setValue(int index, int value) {
    if (index >= 0 && index < size) {
      arr[index] = value;
    }
  }

  int getValue(int index) const {
    if (index >= 0 && index < size) {
      return arr[index];
    }
    return -1;
  }

  void display() const {
    cout << "Array[" << size << "]: ";
    for (int i = 0; i < size; i++) {
      cout << arr[i];
      if (i < size - 1)
        cout << ", ";
    }
    cout << endl;
  }
};

// ======================= MATRIX CLASS =======================
class Matrix {
private:
  int **data;
  int rows, cols;

public:
  Matrix(int r, int c) {
    cout << "Constructor: Creating " << r << "x" << c << " matrix" << endl;
    rows = r;
    cols = c;
    data = new int *[rows];
    for (int i = 0; i < rows; i++) {
      data[i] = new int[cols];
      for (int j = 0; j < cols; j++) {
        data[i][j] = 0;
      }
    }
  }

  // Copy Constructor
  Matrix(const Matrix &other) {
    cout << "Copy Constructor: Copying " << other.rows << "x" << other.cols
         << " matrix" << endl;
    rows = other.rows;
    cols = other.cols;

    data = new int *[rows];
    for (int i = 0; i < rows; i++) {
      data[i] = new int[cols];
      for (int j = 0; j < cols; j++) {
        data[i][j] = other.data[i][j];
      }
    }
  }

  // Copy Assignment
  Matrix &operator=(const Matrix &other) {
    cout << "Assignment: Copying " << other.rows << "x" << other.cols
         << " matrix" << endl;

    if (this == &other)
      return *this;

    // Free old matrix
    for (int i = 0; i < rows; i++) {
      delete[] data[i];
    }
    delete[] data;

    // Copy new matrix
    rows = other.rows;
    cols = other.cols;
    data = new int *[rows];
    for (int i = 0; i < rows; i++) {
      data[i] = new int[cols];
      for (int j = 0; j < cols; j++) {
        data[i][j] = other.data[i][j];
      }
    }

    return *this;
  }

  ~Matrix() {
    cout << "Destructor: Deleting " << rows << "x" << cols << " matrix" << endl;
    for (int i = 0; i < rows; i++) {
      delete[] data[i];
    }
    delete[] data;
  }

  void setValue(int i, int j, int val) {
    if (i >= 0 && i < rows && j >= 0 && j < cols) {
      data[i][j] = val;
    }
  }

  void display() const {
    cout << "Matrix[" << rows << "x" << cols << "]:" << endl;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        cout << data[i][j] << " ";
      }
      cout << endl;
    }
  }
};

int main() {
  cout << "=== COPY CONSTRUCTOR AND ASSIGNMENT OPERATOR ===" << endl << endl;

  // ======================= DEEP COPY WITH STRINGS =======================
  cout << "1. DEEP COPY - STRING CLASS:" << endl;

  StringDeep str1("Hello");
  str1.display();

  cout << endl << "Creating str2 from str1 (copy constructor):" << endl;
  StringDeep str2 = str1; // Calls copy constructor
  str2.display();

  cout << endl << "Both objects:" << endl;
  cout << "str1: ";
  str1.display();
  cout << "str2: ";
  str2.display();

  cout << endl << "Destroying objects:" << endl;

  // ======================= DYNAMIC ARRAY COPY =======================
  cout << endl << "2. DYNAMIC ARRAY - COPY CONSTRUCTOR:" << endl;

  {
    DynamicArray arr1(5);
    arr1.setValue(0, 10);
    arr1.setValue(1, 20);
    arr1.setValue(2, 30);
    arr1.setValue(3, 40);
    arr1.setValue(4, 50);

    cout << "Original array:" << endl;
    arr1.display();

    cout << endl << "Creating arr2 from arr1:" << endl;
    DynamicArray arr2 = arr1; // Copy constructor

    cout << "Copied array:" << endl;
    arr2.display();

    cout << endl << "Modifying arr1:" << endl;
    arr1.setValue(0, 100);
    arr1.display();

    cout << "arr2 unchanged:" << endl;
    arr2.display();

    cout << endl << "Destructors will be called:" << endl;
  }

  // ======================= COPY ASSIGNMENT OPERATOR =======================
  cout << endl << "3. COPY ASSIGNMENT OPERATOR:" << endl;

  {
    DynamicArray arr1(3);
    arr1.setValue(0, 5);
    arr1.setValue(1, 10);
    arr1.setValue(2, 15);

    cout << "arr1: ";
    arr1.display();

    DynamicArray arr2(2);
    arr2.setValue(0, 99);
    arr2.setValue(1, 88);

    cout << "arr2 before assignment: ";
    arr2.display();

    cout << endl << "Assigning arr1 to arr2:" << endl;
    arr2 = arr1; // Copy assignment operator

    cout << "arr2 after assignment: ";
    arr2.display();

    cout << endl << "Destructors:" << endl;
  }

  // ======================= SELF-ASSIGNMENT CHECK =======================
  cout << endl << "4. SELF-ASSIGNMENT CHECK:" << endl;

  {
    DynamicArray arr(3);
    arr.setValue(0, 1);
    arr.setValue(1, 2);
    arr.setValue(2, 3);

    cout << "Original array: ";
    arr.display();

    cout << endl << "Self-assignment (arr = arr):" << endl;
    arr = arr; // Self-assignment

    cout << "Array after self-assignment: ";
    arr.display();
  }

  // ======================= MATRIX DEEP COPY =======================
  cout << endl << "5. MATRIX CLASS - DEEP COPY:" << endl;

  {
    Matrix m1(2, 2);
    m1.setValue(0, 0, 1);
    m1.setValue(0, 1, 2);
    m1.setValue(1, 0, 3);
    m1.setValue(1, 1, 4);

    cout << "Original matrix:" << endl;
    m1.display();

    cout << endl << "Creating m2 from m1:" << endl;
    Matrix m2 = m1;

    cout << "Copied matrix:" << endl;
    m2.display();

    cout << endl << "Modifying m1:" << endl;
    m1.setValue(0, 0, 99);
    m1.display();

    cout << "m2 unchanged:" << endl;
    m2.display();

    cout << endl << "Destructors:" << endl;
  }

  // ======================= MATRIX ASSIGNMENT =======================
  cout << endl << "6. MATRIX ASSIGNMENT OPERATOR:" << endl;

  {
    Matrix m1(2, 2);
    m1.setValue(0, 0, 1);
    m1.setValue(0, 1, 2);
    m1.setValue(1, 0, 3);
    m1.setValue(1, 1, 4);

    Matrix m2(3, 3);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        m2.setValue(i, j, 0);
      }
    }

    cout << "m1 (2x2):" << endl;
    m1.display();

    cout << "m2 (3x3) before assignment:" << endl;
    m2.display();

    cout << "Assigning m1 to m2:" << endl;
    m2 = m1;

    cout << "m2 after assignment:" << endl;
    m2.display();

    cout << "Destructors:" << endl;
  }

  // ======================= FUNCTION PARAMETER COPY =======================
  cout << endl << "7. PASSING BY VALUE (COPY CONSTRUCTOR):" << endl;

  {
    cout << "Function that modifies a copy:" << endl;
    DynamicArray arr(3);
    arr.setValue(0, 10);
    arr.setValue(1, 20);
    arr.setValue(2, 30);

    cout << "Original: ";
    arr.display();
  }

  return 0;
}

/*
OUTPUT:
=== COPY CONSTRUCTOR AND ASSIGNMENT OPERATOR ===

1. DEEP COPY - STRING CLASS:
Constructor: Created StringDeep with "Hello"
Data: "Hello", Length: 5

Creating str2 from str1 (copy constructor):
Copy Constructor: Copying "Hello"
Data: "Hello", Length: 5

Both objects:
str1: Data: "Hello", Length: 5
str2: Data: "Hello", Length: 5

Destroying objects:
Destructor: Deleting StringDeep "Hello"
Destructor: Deleting StringDeep "Hello"

2. DYNAMIC ARRAY - COPY CONSTRUCTOR:
Constructor: Creating array of size 5
Original array:
Array[5]: 10, 20, 30, 40, 50

Creating arr2 from arr1:
Copy Constructor: Copying array of size 5
Copied array:
Array[5]: 10, 20, 30, 40, 50

Modifying arr1:
Array[5]: 100, 20, 30, 40, 50
arr2 unchanged:
Array[5]: 10, 20, 30, 40, 50

Destructors will be called:
Destructor: Deleting array of size 5
Destructor: Deleting array of size 5

3. COPY ASSIGNMENT OPERATOR:
Constructor: Creating array of size 3
arr1: Array[3]: 5, 10, 15
Constructor: Creating array of size 2
arr2 before assignment: Array[2]: 99, 88

Assigning arr1 to arr2:
Assignment Operator: Assigning array of size 3
Destructor: Deleting array of size 2
arr2 after assignment: Array[3]: 5, 10, 15

Destructors:
Destructor: Deleting array of size 3
Destructor: Deleting array of size 3

4. SELF-ASSIGNMENT CHECK:
Constructor: Creating array of size 3
Original array: Array[3]: 1, 2, 3

Self-assignment (arr = arr):
Assignment Operator: Assigning array of size 3
Self-assignment detected, skipping
Array after self-assignment: Array[3]: 1, 2, 3

5. MATRIX CLASS - DEEP COPY:
Constructor: Creating 2x2 matrix
Original matrix:
Matrix[2x2]:
1 2
3 4

Creating m2 from m1:
Copy Constructor: Copying 2x2 matrix
Copied matrix:
Matrix[2x2]:
1 2
3 4

Modifying m1:
Matrix[2x2]:
99 2
3 4
m2 unchanged:
Matrix[2x2]:
1 2
3 4

Destructors:
Destructor: Deleting 2x2 matrix
Destructor: Deleting 2x2 matrix

6. MATRIX ASSIGNMENT OPERATOR:
Constructor: Creating 2x2 matrix
Constructor: Creating 3x3 matrix
m1 (2x2):
Matrix[2x2]:
1 2
3 4
m2 (3x3) before assignment:
Matrix[3x3]:
0 0 0
0 0 0
0 0 0

Assigning m1 to m2:
Assignment: Copying 2x2 matrix
m2 after assignment:
Matrix[2x2]:
1 2
3 4

Destructors:
Destructor: Deleting 2x2 matrix
Destructor: Deleting 2x2 matrix

7. PASSING BY VALUE (COPY CONSTRUCTOR):
Function that modifies a copy:
Constructor: Creating array of size 3
Original: Array[3]: 10, 20, 30
Destructor: Deleting array of size 3

================================================================================
KEY CONCEPTS
================================================================================

1. SHALLOW vs DEEP COPY:
   - Shallow: Copies pointers (share same data) - PROBLEMATIC
   - Deep: Copies data (separate copies) - CORRECT for pointers

2. COPY CONSTRUCTOR:
   - Called when initializing object from another: obj2 = obj1;
   - Takes const reference parameter
   - Must allocate new memory for dynamic data
   - Must copy data completely

3. COPY ASSIGNMENT OPERATOR:
   - Called when assigning after creation: obj2 = obj1;
   - Must check self-assignment
   - Must free old resources first
   - Must allocate and copy new resources

4. SELF-ASSIGNMENT:
   - Check: if (this == &other) return *this;
   - Essential for safe assignment
   - Prevents deleting data before copying

5. THE RULE OF FIVE:
   If you define:
   - Destructor → also define copy constructor
   - Copy constructor → also define copy assignment
   - Move constructor (C++11)
   - Move assignment operator (C++11)

6. WHEN COPY HAPPENS:
   - Object initialization from another
   - Passing by value
   - Returning by value
   - Using with containers (vector, etc.)

================================================================================
PRACTICE EXERCISES
================================================================================

1. Implement LinkedList with copy constructor

2. Create String class with all copy operations

3. Implement 2D array with proper copying

4. Create Stack class with copy support

5. Implement polynomial class with copy operations

================================================================================
*/
