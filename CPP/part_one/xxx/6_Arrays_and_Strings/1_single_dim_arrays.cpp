/*
================================================================================
TOPIC 6: ARRAYS AND STRINGS - PART 1: SINGLE-DIMENSIONAL ARRAYS
================================================================================

ARRAYS:
- Collection of elements of same data type
- Elements stored in contiguous memory
- Accessed using index (0-based)
- Fixed size (in C++, size must be known at compile time for static arrays)

ADVANTAGES:
- Fast access using index
- Cache-friendly (contiguous memory)
- Simple and efficient

DISADVANTAGES:
- Fixed size
- Cannot add/remove elements easily
- Cannot search efficiently (unless sorted)
- Memory wastage if not all elements used

SYNTAX:
data_type array_name[size];
data_type array_name[size] = {initial values};

================================================================================
*/

#include <algorithm>
#include <iostream>
using namespace std;

int main() {
  cout << "=== SINGLE-DIMENSIONAL ARRAYS ===" << endl << endl;

  // ======================= ARRAY DECLARATION AND INITIALIZATION
  // =======================
  cout << "1. ARRAY DECLARATION AND INITIALIZATION:" << endl;

  int numbers[5]; // Declaration
  cout << "Declared array of size 5" << endl;

  int scores[5] = {10, 20, 30, 40, 50}; // Declaration with initialization
  cout << "Array with values: ";
  for (int i = 0; i < 5; i++) {
    cout << scores[i] << " ";
  }
  cout << endl;

  // Partial initialization (rest are 0)
  int partial[5] = {1, 2, 3};
  cout << "Partial initialization: ";
  for (int i = 0; i < 5; i++) {
    cout << partial[i] << " ";
  }
  cout << endl;

  // ======================= ACCESSING ARRAY ELEMENTS =======================
  cout << endl << "2. ACCESSING ARRAY ELEMENTS:" << endl;

  int arr[5] = {10, 20, 30, 40, 50};
  cout << "First element (index 0): " << arr[0] << endl;
  cout << "Third element (index 2): " << arr[2] << endl;
  cout << "Last element (index 4): " << arr[4] << endl;

  // ======================= MODIFYING ARRAY ELEMENTS =======================
  cout << endl << "3. MODIFYING ARRAY ELEMENTS:" << endl;

  arr[0] = 100;
  arr[2] = 300;
  cout << "After modification: ";
  for (int i = 0; i < 5; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  // ======================= READING FROM USER =======================
  cout << endl << "4. READING ARRAY ELEMENTS FROM USER:" << endl;

  int temp_arr[3];
  cout << "Enter 3 numbers: ";
  for (int i = 0; i < 3; i++) {
    // Simulating input
    temp_arr[0] = 5;
    temp_arr[1] = 10;
    temp_arr[2] = 15;
  }
  cout << "5 10 15" << endl;
  cout << "Array: ";
  for (int i = 0; i < 3; i++) {
    cout << temp_arr[i] << " ";
  }
  cout << endl;

  // ======================= SUM OF ARRAY ELEMENTS =======================
  cout << endl << "5. SUM OF ARRAY ELEMENTS:" << endl;

  int nums[5] = {10, 20, 30, 40, 50};
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += nums[i];
  }
  cout << "Array: ";
  for (int i = 0; i < 5; i++)
    cout << nums[i] << " ";
  cout << endl << "Sum: " << sum << endl;

  // ======================= AVERAGE OF ARRAY ELEMENTS =======================
  cout << endl << "6. AVERAGE OF ARRAY ELEMENTS:" << endl;

  double values[4] = {85.5, 90.0, 78.5, 92.0};
  double average = 0;
  for (int i = 0; i < 4; i++) {
    average += values[i];
  }
  average /= 4;
  cout << "Values: ";
  for (int i = 0; i < 4; i++)
    cout << values[i] << " ";
  cout << endl << "Average: " << average << endl;

  // ======================= FINDING MAXIMUM AND MINIMUM =======================
  cout << endl << "7. FINDING MAXIMUM AND MINIMUM:" << endl;

  int data[6] = {45, 23, 67, 12, 89, 34};
  int max_val = data[0];
  int min_val = data[0];

  for (int i = 0; i < 6; i++) {
    if (data[i] > max_val)
      max_val = data[i];
    if (data[i] < min_val)
      min_val = data[i];
  }

  cout << "Array: ";
  for (int i = 0; i < 6; i++)
    cout << data[i] << " ";
  cout << endl;
  cout << "Maximum: " << max_val << endl;
  cout << "Minimum: " << min_val << endl;

  // ======================= LINEAR SEARCH =======================
  cout << endl << "8. LINEAR SEARCH:" << endl;

  int search_arr[5] = {10, 25, 40, 55, 70};
  int target = 40;
  int position = -1;

  for (int i = 0; i < 5; i++) {
    if (search_arr[i] == target) {
      position = i;
      break;
    }
  }

  cout << "Array: ";
  for (int i = 0; i < 5; i++)
    cout << search_arr[i] << " ";
  cout << endl;
  cout << "Searching for: " << target << endl;
  if (position != -1) {
    cout << "Found at index: " << position << endl;
  } else {
    cout << "Not found" << endl;
  }

  // ======================= COUNTING OCCURRENCES =======================
  cout << endl << "9. COUNTING OCCURRENCES:" << endl;

  int count_arr[8] = {1, 2, 3, 2, 4, 2, 5, 2};
  int element = 2;
  int count = 0;

  for (int i = 0; i < 8; i++) {
    if (count_arr[i] == element) {
      count++;
    }
  }

  cout << "Array: ";
  for (int i = 0; i < 8; i++)
    cout << count_arr[i] << " ";
  cout << endl;
  cout << "Element " << element << " appears " << count << " times" << endl;

  // ======================= REVERSING AN ARRAY =======================
  cout << endl << "10. REVERSING AN ARRAY:" << endl;

  int reverse_arr[5] = {1, 2, 3, 4, 5};
  cout << "Original: ";
  for (int i = 0; i < 5; i++)
    cout << reverse_arr[i] << " ";
  cout << endl;

  for (int i = 0; i < 5 / 2; i++) {
    int temp = reverse_arr[i];
    reverse_arr[i] = reverse_arr[4 - i];
    reverse_arr[4 - i] = temp;
  }

  cout << "Reversed: ";
  for (int i = 0; i < 5; i++)
    cout << reverse_arr[i] << " ";
  cout << endl;

  return 0;
}

/*
OUTPUT:
=== SINGLE-DIMENSIONAL ARRAYS ===

1. ARRAY DECLARATION AND INITIALIZATION:
Declared array of size 5
Array with values: 10 20 30 40 50
Partial initialization: 1 2 3 0 0

2. ACCESSING ARRAY ELEMENTS:
First element (index 0): 10
Third element (index 2): 30
Last element (index 4): 50

3. MODIFYING ARRAY ELEMENTS:
After modification: 100 20 300 40 50

4. READING ARRAY ELEMENTS FROM USER:
Enter 3 numbers: 5 10 15
Array: 5 10 15

5. SUM OF ARRAY ELEMENTS:
Array: 10 20 30 40 50
Sum: 150

6. AVERAGE OF ARRAY ELEMENTS:
Values: 85.5 90 78.5 92
Average: 86.5

7. FINDING MAXIMUM AND MINIMUM:
Array: 45 23 67 12 89 34
Maximum: 89
Minimum: 12

8. LINEAR SEARCH:
Array: 10 25 40 55 70
Searching for: 40
Found at index: 2

9. COUNTING OCCURRENCES:
Array: 1 2 3 2 4 2 5 2
Element 2 appears 4 times

10. REVERSING AN ARRAY:
Original: 1 2 3 4 5
Reversed: 5 4 3 2 1

================================================================================
KEY CONCEPTS
================================================================================

1. ARRAY SIZE:
   - Must be compile-time constant (in static arrays)
   - Use dynamic arrays for runtime sizes

2. INDEXING:
   - Zero-based (first element at index 0)
   - Out of bounds access causes undefined behavior

3. ARRAY NAME:
   - Without []: represents address of first element
   - arr == &arr[0] (essentially equivalent)

4. COMMON OPERATIONS:
   - Traversal: O(n)
   - Searching: O(n) for linear search
   - Sorting: O(n log n) with efficient algorithms
   - Insertion/Deletion: O(n) for maintaining order

5. MEMORY USAGE:
   - Memory = sizeof(data_type) * array_size
   - Contiguous memory allocation

================================================================================
PRACTICE EXERCISES
================================================================================

1. Find second largest element in array

2. Check if array is palindrome

3. Rotate array elements by k positions

4. Find if two arrays are equal

5. Merge two sorted arrays into third array

6. Remove duplicates from array

7. Find missing number in array of 1 to n

================================================================================
*/
