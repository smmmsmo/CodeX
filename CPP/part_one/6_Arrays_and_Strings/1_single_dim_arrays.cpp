#include <algorithm>
#include <climits>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

/*
 * =====================================================================
 * TOPIC 6.1: SINGLE-DIMENSIONAL ARRAYS
 * =====================================================================
 *
 * WHAT ARE ARRAYS?
 * An array is a collection of elements of the same data type stored in
 * contiguous memory locations. Arrays provide efficient access to elements
 * using indices and are fundamental to competitive programming.
 *
 * KEY CONCEPTS COVERED:
 * 1. Array declaration and initialization
 * 2. Accessing and modifying elements
 * 3. Array size and bounds
 * 4. Traversing arrays
 * 5. Passing arrays to functions
 * 6. Common array operations
 * 7. Array algorithms (search, sort, reverse)
 * 8. Prefix sum and difference arrays
 * 9. Sliding window technique basics
 * 10. Two-pointer technique
 * 11. Kadane's algorithm
 * 12. Array rotation and manipulation
 *
 * =====================================================================
 * ARRAY BASICS
 * =====================================================================
 *
 * DECLARATION:
 *    data_type array_name[size];
 *
 * INITIALIZATION:
 *    int arr[5] = {1, 2, 3, 4, 5};  // Initialize all elements
 *    int arr[5] = {1, 2};            // Remaining elements = 0
 *    int arr[] = {1, 2, 3};          // Size determined automatically
 *
 * MEMORY LAYOUT:
 *    Arrays are stored in contiguous memory
 *    arr[0] | arr[1] | arr[2] | arr[3] | arr[4]
 *    Address: base, base+4, base+8, base+12, base+16 (for int)
 *
 * TIME COMPLEXITIES:
 *    Access: O(1)
 *    Search: O(n) for unsorted, O(log n) for sorted (binary search)
 *    Insertion at end: O(1) if space available
 *    Insertion at beginning/middle: O(n)
 *    Deletion: O(n)
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: ARRAY DECLARATION AND INITIALIZATION ==============
void example1_declaration_initialization() {
  cout << "\n============== EXAMPLE 1: DECLARATION & INITIALIZATION "
          "=============="
       << endl;
  cout << "Different ways to create and initialize arrays\n" << endl;

  // Method 1: Declare with size, initialize later
  int arr1[5];
  arr1[0] = 10;
  arr1[1] = 20;
  arr1[2] = 30;
  arr1[3] = 40;
  arr1[4] = 50;

  cout << "Method 1 - Manual initialization:" << endl;
  for (int i = 0; i < 5; i++) {
    cout << "arr1[" << i << "] = " << arr1[i] << endl;
  }

  // Method 2: Declare and initialize together
  int arr2[5] = {100, 200, 300, 400, 500};
  cout << "\nMethod 2 - List initialization:" << endl;
  for (int i = 0; i < 5; i++) {
    cout << "arr2[" << i << "] = " << arr2[i] << endl;
  }

  // Method 3: Partial initialization (remaining elements = 0)
  int arr3[5] = {1, 2}; // arr3 = {1, 2, 0, 0, 0}
  cout << "\nMethod 3 - Partial initialization (rest = 0):" << endl;
  for (int i = 0; i < 5; i++) {
    cout << "arr3[" << i << "] = " << arr3[i] << endl;
  }

  // Method 4: Initialize all to zero
  int arr4[5] = {0}; // All elements = 0
  cout << "\nMethod 4 - Initialize all to zero:" << endl;
  for (int i = 0; i < 5; i++) {
    cout << "arr4[" << i << "] = " << arr4[i] << endl;
  }

  // Method 5: Size determined by initialization
  int arr5[] = {10, 20, 30}; // Size = 3
  int size5 = sizeof(arr5) / sizeof(arr5[0]);
  cout << "\nMethod 5 - Auto-sized array (size = " << size5 << "):" << endl;
  for (int i = 0; i < size5; i++) {
    cout << "arr5[" << i << "] = " << arr5[i] << endl;
  }

  cout << "\nKey Point: Arrays use 0-based indexing!" << endl;
}

// ============== EXAMPLE 2: ARRAY TRAVERSAL TECHNIQUES ==============
void example2_array_traversal() {
  cout << "\n============== EXAMPLE 2: ARRAY TRAVERSAL ==============" << endl;
  cout << "Different ways to iterate through arrays\n" << endl;

  int arr[] = {5, 10, 15, 20, 25, 30};
  int size = sizeof(arr) / sizeof(arr[0]);

  // Method 1: Traditional for loop
  cout << "Method 1 - Traditional for loop:" << endl;
  for (int i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  // Method 2: Range-based for loop (C++11)
  cout << "\nMethod 2 - Range-based for loop:" << endl;
  for (int element : arr) {
    cout << element << " ";
  }
  cout << endl;

  // Method 3: While loop
  cout << "\nMethod 3 - While loop:" << endl;
  int i = 0;
  while (i < size) {
    cout << arr[i] << " ";
    i++;
  }
  cout << endl;

  // Method 4: Reverse traversal
  cout << "\nMethod 4 - Reverse traversal:" << endl;
  for (int i = size - 1; i >= 0; i--) {
    cout << arr[i] << " ";
  }
  cout << endl;

  // Method 5: Using pointers
  cout << "\nMethod 5 - Using pointers:" << endl;
  for (int *ptr = arr; ptr < arr + size; ptr++) {
    cout << *ptr << " ";
  }
  cout << endl;

  cout << "\nSize calculation: sizeof(arr) / sizeof(arr[0]) = " << size << endl;
}

// ============== EXAMPLE 3: COMMON ARRAY OPERATIONS ==============
void example3_array_operations() {
  cout << "\n============== EXAMPLE 3: COMMON OPERATIONS =============="
       << endl;
  cout << "Basic operations on arrays\n" << endl;

  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  int size = sizeof(arr) / sizeof(arr[0]);

  cout << "Original array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  // Find minimum element
  int min_elem = arr[0];
  for (int i = 1; i < size; i++) {
    if (arr[i] < min_elem) {
      min_elem = arr[i];
    }
  }
  cout << "\nMinimum element: " << min_elem << endl;

  // Find maximum element
  int max_elem = arr[0];
  for (int i = 1; i < size; i++) {
    if (arr[i] > max_elem) {
      max_elem = arr[i];
    }
  }
  cout << "Maximum element: " << max_elem << endl;

  // Calculate sum
  int sum = 0;
  for (int x : arr) {
    sum += x;
  }
  cout << "Sum of elements: " << sum << endl;

  // Calculate average
  double avg = (double)sum / size;
  cout << "Average: " << avg << endl;

  // Count even and odd numbers
  int even_count = 0, odd_count = 0;
  for (int x : arr) {
    if (x % 2 == 0)
      even_count++;
    else
      odd_count++;
  }
  cout << "Even numbers: " << even_count << ", Odd numbers: " << odd_count
       << endl;

  // Using STL algorithms
  cout << "\nUsing STL algorithms:" << endl;
  cout << "Min: " << *min_element(arr, arr + size) << endl;
  cout << "Max: " << *max_element(arr, arr + size) << endl;
  cout << "Sum: " << accumulate(arr, arr + size, 0) << endl;
}

// ============== EXAMPLE 4: LINEAR SEARCH ==============
int linear_search(int arr[], int size, int target) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == target) {
      return i; // Return index if found
    }
  }
  return -1; // Return -1 if not found
}

void example4_linear_search() {
  cout << "\n============== EXAMPLE 4: LINEAR SEARCH ==============" << endl;
  cout << "Search for an element in unsorted array - O(n)\n" << endl;

  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  int size = sizeof(arr) / sizeof(arr[0]);

  cout << "Array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  int targets[] = {22, 100, 64, 11};
  for (int target : targets) {
    int index = linear_search(arr, size, target);
    if (index != -1) {
      cout << "\n" << target << " found at index " << index << endl;
    } else {
      cout << "\n" << target << " not found in array" << endl;
    }
  }

  cout << "\nTime Complexity: O(n)" << endl;
  cout << "Space Complexity: O(1)" << endl;
}

// ============== EXAMPLE 5: BINARY SEARCH ==============
int binary_search(int arr[], int size, int target) {
  int left = 0, right = size - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2; // Avoid overflow

    if (arr[mid] == target) {
      return mid; // Found
    } else if (arr[mid] < target) {
      left = mid + 1; // Search right half
    } else {
      right = mid - 1; // Search left half
    }
  }
  return -1; // Not found
}

void example5_binary_search() {
  cout << "\n============== EXAMPLE 5: BINARY SEARCH ==============" << endl;
  cout << "Search in SORTED array - O(log n)\n" << endl;

  int arr[] = {11, 12, 22, 25, 34, 64, 90};
  int size = sizeof(arr) / sizeof(arr[0]);

  cout << "Sorted array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  int targets[] = {22, 100, 11, 90};
  for (int target : targets) {
    int index = binary_search(arr, size, target);
    if (index != -1) {
      cout << "\n" << target << " found at index " << index << endl;
    } else {
      cout << "\n" << target << " not found in array" << endl;
    }
  }

  cout << "\nTime Complexity: O(log n)" << endl;
  cout << "Space Complexity: O(1)" << endl;
  cout << "Note: Array MUST be sorted!" << endl;
}

// ============== EXAMPLE 6: ARRAY REVERSAL ==============
void reverse_array(int arr[], int size) {
  int left = 0, right = size - 1;
  while (left < right) {
    // Swap elements
    int temp = arr[left];
    arr[left] = arr[right];
    arr[right] = temp;
    left++;
    right--;
  }
}

void example6_array_reversal() {
  cout << "\n============== EXAMPLE 6: ARRAY REVERSAL ==============" << endl;
  cout << "Reverse array using two pointers - O(n)\n" << endl;

  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int size = sizeof(arr) / sizeof(arr[0]);

  cout << "Original array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  reverse_array(arr, size);

  cout << "Reversed array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  // Using STL
  int arr2[] = {10, 20, 30, 40, 50};
  int size2 = sizeof(arr2) / sizeof(arr2[0]);
  cout << "\nUsing STL reverse():" << endl;
  cout << "Before: ";
  for (int x : arr2)
    cout << x << " ";
  reverse(arr2, arr2 + size2);
  cout << "\nAfter:  ";
  for (int x : arr2)
    cout << x << " ";
  cout << endl;

  cout << "\nTime Complexity: O(n)" << endl;
  cout << "Space Complexity: O(1)" << endl;
}

// ============== EXAMPLE 7: ARRAY ROTATION ==============
void rotate_left(int arr[], int size, int k) {
  k = k % size; // Handle k > size
  reverse(arr, arr + k);
  reverse(arr + k, arr + size);
  reverse(arr, arr + size);
}

void rotate_right(int arr[], int size, int k) {
  k = k % size;
  reverse(arr, arr + size);
  reverse(arr, arr + k);
  reverse(arr + k, arr + size);
}

void example7_array_rotation() {
  cout << "\n============== EXAMPLE 7: ARRAY ROTATION ==============" << endl;
  cout << "Rotate array left/right by k positions - O(n)\n" << endl;

  int arr1[] = {1, 2, 3, 4, 5, 6, 7};
  int size = sizeof(arr1) / sizeof(arr1[0]);

  cout << "Original array: ";
  for (int x : arr1)
    cout << x << " ";
  cout << endl;

  // Rotate left by 2
  int arr_left[7] = {1, 2, 3, 4, 5, 6, 7};
  rotate_left(arr_left, size, 2);
  cout << "After left rotation by 2: ";
  for (int x : arr_left)
    cout << x << " ";
  cout << endl;

  // Rotate right by 3
  int arr_right[7] = {1, 2, 3, 4, 5, 6, 7};
  rotate_right(arr_right, size, 3);
  cout << "After right rotation by 3: ";
  for (int x : arr_right)
    cout << x << " ";
  cout << endl;

  cout << "\nAlgorithm: Reversal algorithm" << endl;
  cout << "Left rotation by k: reverse(0,k), reverse(k,n), reverse(0,n)"
       << endl;
  cout << "Time Complexity: O(n)" << endl;
  cout << "Space Complexity: O(1)" << endl;
}

// ============== EXAMPLE 8: PREFIX SUM ARRAY ==============
void example8_prefix_sum() {
  cout << "\n============== EXAMPLE 8: PREFIX SUM ARRAY ==============" << endl;
  cout << "Calculate prefix sums for range query optimization - O(n)\n" << endl;

  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int size = sizeof(arr) / sizeof(arr[0]);

  // Build prefix sum array
  vector<int> prefix(size);
  prefix[0] = arr[0];
  for (int i = 1; i < size; i++) {
    prefix[i] = prefix[i - 1] + arr[i];
  }

  cout << "Original array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  cout << "Prefix sum array: ";
  for (int x : prefix)
    cout << x << " ";
  cout << endl;

  // Query: sum from index l to r
  auto range_sum = [&](int l, int r) {
    if (l == 0)
      return prefix[r];
    return prefix[r] - prefix[l - 1];
  };

  cout << "\nRange sum queries:" << endl;
  cout << "Sum[0, 3] = " << range_sum(0, 3) << " (1+2+3+4)" << endl;
  cout << "Sum[2, 5] = " << range_sum(2, 5) << " (3+4+5+6)" << endl;
  cout << "Sum[4, 7] = " << range_sum(4, 7) << " (5+6+7+8)" << endl;

  cout << "\nUse Case: Optimize range sum queries from O(n) to O(1)" << endl;
  cout << "Preprocessing: O(n), Query: O(1)" << endl;
}

// ============== EXAMPLE 9: TWO POINTER TECHNIQUE ==============
void example9_two_pointer() {
  cout << "\n============== EXAMPLE 9: TWO POINTER TECHNIQUE =============="
       << endl;
  cout << "Find pair with given sum in sorted array - O(n)\n" << endl;

  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = sizeof(arr) / sizeof(arr[0]);
  int target = 10;

  cout << "Sorted array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;
  cout << "Target sum: " << target << endl;

  // Two pointer approach
  int left = 0, right = size - 1;
  bool found = false;

  while (left < right) {
    int current_sum = arr[left] + arr[right];

    if (current_sum == target) {
      cout << "\nPair found: (" << arr[left] << ", " << arr[right] << ")"
           << endl;
      cout << "Indices: (" << left << ", " << right << ")" << endl;
      found = true;
      break;
    } else if (current_sum < target) {
      left++; // Need larger sum
    } else {
      right--; // Need smaller sum
    }
  }

  if (!found) {
    cout << "\nNo pair found with sum " << target << endl;
  }

  cout << "\nTime Complexity: O(n)" << endl;
  cout << "Space Complexity: O(1)" << endl;
  cout << "Note: Array must be sorted!" << endl;
}

// ============== EXAMPLE 10: KADANE'S ALGORITHM ==============
int max_subarray_sum(int arr[], int size) {
  int max_so_far = INT_MIN;
  int max_ending_here = 0;

  for (int i = 0; i < size; i++) {
    max_ending_here += arr[i];
    max_so_far = max(max_so_far, max_ending_here);

    if (max_ending_here < 0) {
      max_ending_here = 0;
    }
  }
  return max_so_far;
}

void example10_kadane_algorithm() {
  cout << "\n============== EXAMPLE 10: KADANE'S ALGORITHM =============="
       << endl;
  cout << "Maximum subarray sum - O(n)\n" << endl;

  int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  int size = sizeof(arr) / sizeof(arr[0]);

  cout << "Array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  int max_sum = max_subarray_sum(arr, size);
  cout << "\nMaximum subarray sum: " << max_sum << endl;
  cout << "Subarray: [4, -1, 2, 1]" << endl;

  // Test with all negative
  int arr2[] = {-5, -2, -8, -1, -4};
  int size2 = sizeof(arr2) / sizeof(arr2[0]);
  cout << "\nArray with all negative: ";
  for (int x : arr2)
    cout << x << " ";
  cout << endl;
  cout << "Maximum sum: " << max_subarray_sum(arr2, size2) << endl;

  cout << "\nAlgorithm: Kadane's Algorithm" << endl;
  cout << "Time Complexity: O(n)" << endl;
  cout << "Space Complexity: O(1)" << endl;
  cout << "Classic DP problem!" << endl;
}

// ============== EXAMPLE 11: SLIDING WINDOW MAXIMUM ==============
void example11_sliding_window() {
  cout << "\n============== EXAMPLE 11: SLIDING WINDOW TECHNIQUE =============="
       << endl;
  cout << "Find maximum in every window of size k - O(n*k) naive\n" << endl;

  int arr[] = {1, 3, -1, -3, 5, 3, 6, 7};
  int size = sizeof(arr) / sizeof(arr[0]);
  int k = 3;

  cout << "Array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;
  cout << "Window size k = " << k << endl;

  cout << "\nMaximum in each window:" << endl;
  for (int i = 0; i <= size - k; i++) {
    int window_max = arr[i];
    cout << "Window [";
    for (int j = i; j < i + k; j++) {
      cout << arr[j];
      if (j < i + k - 1)
        cout << ", ";
      window_max = max(window_max, arr[j]);
    }
    cout << "] -> Max = " << window_max << endl;
  }

  cout << "\nTime Complexity: O(n * k) for naive approach" << endl;
  cout << "Can be optimized to O(n) using deque!" << endl;
}

// ============== EXAMPLE 12: PASSING ARRAYS TO FUNCTIONS ==============
void print_array(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

void modify_array(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    arr[i] *= 2; // Double each element
  }
}

int array_sum(int arr[], int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum;
}

void example12_passing_arrays() {
  cout << "\n============== EXAMPLE 12: PASSING ARRAYS TO FUNCTIONS "
          "=============="
       << endl;
  cout << "Arrays are passed by reference (pointer)\n" << endl;

  int arr[] = {1, 2, 3, 4, 5};
  int size = sizeof(arr) / sizeof(arr[0]);

  cout << "Original array: ";
  print_array(arr, size);

  cout << "Sum of elements: " << array_sum(arr, size) << endl;

  modify_array(arr, size);
  cout << "After doubling: ";
  print_array(arr, size);

  cout << "\nKey Point: Arrays decay to pointers when passed to functions"
       << endl;
  cout << "Must pass size separately!" << endl;
  cout << "Changes in function affect original array!" << endl;
}

/*
 * =====================================================================
 * KEY CONCEPTS SUMMARY
 * =====================================================================
 *
 * 1. ARRAY BASICS:
 *    - Contiguous memory, 0-indexed, fixed size
 *    - Access: O(1), Search: O(n), Insertion/Deletion: O(n)
 *
 * 2. COMMON OPERATIONS:
 *    - Traversal, search (linear, binary)
 *    - Find min/max, sum, average
 *    - Reverse, rotate
 *
 * 3. IMPORTANT ALGORITHMS:
 *    - Kadane's Algorithm: Maximum subarray sum - O(n)
 *    - Two Pointers: Find pairs, partition - O(n)
 *    - Sliding Window: Subarray problems - O(n)
 *    - Prefix Sum: Range queries - O(1) per query
 *
 * 4. SEARCH ALGORITHMS:
 *    - Linear Search: O(n) - works on any array
 *    - Binary Search: O(log n) - requires sorted array
 *
 * 5. ARRAY MANIPULATION:
 *    - Reversal: O(n) time, O(1) space
 *    - Rotation: O(n) time, O(1) space using reversal
 *
 * 6. PASSING TO FUNCTIONS:
 *    - Arrays decay to pointers
 *    - Must pass size separately
 *    - Modifications affect original
 *
 * =====================================================================
 * COMPETITIVE PROGRAMMING TIPS
 * =====================================================================
 *
 * 1. Always check array bounds to avoid undefined behavior
 * 2. Use long long for large sums to avoid overflow
 * 3. Prefix sums are crucial for range query problems
 * 4. Two pointers work great on sorted arrays
 * 5. Sliding window for contiguous subarray problems
 * 6. Kadane's algorithm is a must-know for max subarray
 * 7. Learn to recognize when to use each technique
 * 8. Practice reversing thinking (inverse operations)
 * 9. Consider edge cases: empty array, single element, all same
 * 10. STL algorithms (sort, reverse, etc.) save time in contests
 *
 * =====================================================================
 * COMMON MISTAKES TO AVOID
 * =====================================================================
 *
 * 1. Array index out of bounds (accessing arr[size] instead of arr[size-1])
 * 2. Not initializing array elements (contains garbage values)
 * 3. Comparing arrays with == (compares pointers, not contents)
 * 4. Forgetting to pass size when passing array to function
 * 5. Integer overflow in sum calculations
 * 6. Using = instead of == in conditions
 * 7. Off-by-one errors in loops
 * 8. Not handling empty arrays in functions
 * 9. Assuming array is sorted when it's not
 * 10. Modifying array while iterating (for certain operations)
 *
 * =====================================================================
 */

int main() {
  cout << "=========================================================" << endl;
  cout << "      SINGLE-DIMENSIONAL ARRAYS - COMPREHENSIVE GUIDE      " << endl;
  cout << "=========================================================" << endl;

  example1_declaration_initialization();
  example2_array_traversal();
  example3_array_operations();
  example4_linear_search();
  example5_binary_search();
  example6_array_reversal();
  example7_array_rotation();
  example8_prefix_sum();
  example9_two_pointer();
  example10_kadane_algorithm();
  example11_sliding_window();
  example12_passing_arrays();

  cout << "\n=========================================================" << endl;
  cout << "         PRACTICE EXERCISES" << endl;
  cout << "=========================================================" << endl;
  cout << "\n1. Find second largest element in array" << endl;
  cout << "2. Remove duplicates from sorted array" << endl;
  cout << "3. Find the missing number in array [0...n]" << endl;
  cout << "4. Move all zeros to the end of array" << endl;
  cout << "5. Find majority element (appears more than n/2 times)" << endl;
  cout << "6. Rearrange array in alternating positive & negative" << endl;
  cout << "7. Find all pairs with given difference" << endl;
  cout << "8. Longest consecutive subsequence" << endl;
  cout << "9. Trapping rainwater problem" << endl;
  cout << "10. Stock buy and sell to maximize profit" << endl;

  return 0;
}
