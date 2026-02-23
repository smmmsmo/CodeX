#include <algorithm>
#include <climits>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
 * =====================================================================
 * TOPIC 6.5: ADVANCED ARRAY TECHNIQUES
 * =====================================================================
 *
 * COMPETITIVE PROGRAMMING ARRAY TECHNIQUES
 * This file covers advanced array algorithms and techniques essential
 * for competitive programming, coding interviews, and complex problems.
 *
 * KEY CONCEPTS COVERED:
 * 1. Two Pointers (multiple variations)
 * 2. Sliding Window (fixed and variable size)
 * 3. Prefix Sum and Difference Arrays
 * 4. Hashing with Arrays
 * 5. Monotonic Stack/Queue
 * 6. Dutch National Flag (3-way partitioning)
 * 7. Moore's Voting Algorithm
 * 8. Trapping Rainwater
 * 9. Stock Buy-Sell Problems
 * 10. Subarray Sum Problems
 * 11. Longest Consecutive Sequence
 * 12. Array Manipulation Tricks
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: TWO POINTER - PAIR SUM ==============
void example1_two_pointer_pair_sum() {
  cout << "\n============== EXAMPLE 1: TWO POINTER - PAIR SUM =============="
       << endl;
  cout << "Find all pairs with given sum in sorted array - O(n)\n" << endl;

  vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int target = 10;

  cout << "Array: ";
  for (int x : arr)
    cout << x << " ";
  cout << "\nTarget sum: " << target << endl;

  cout << "\nPairs found:" << endl;
  int left = 0, right = arr.size() - 1;
  int count = 0;

  while (left < right) {
    int sum = arr[left] + arr[right];
    if (sum == target) {
      cout << "(" << arr[left] << ", " << arr[right] << ")" << endl;
      count++;
      left++;
      right--;
    } else if (sum < target) {
      left++;
    } else {
      right--;
    }
  }

  cout << "\nTotal pairs: " << count << endl;
  cout << "Time: O(n), Space: O(1)" << endl;
}

// ============== EXAMPLE 2: TWO POINTER - REMOVE DUPLICATES ==============
int remove_duplicates(vector<int> &arr) {
  if (arr.empty())
    return 0;

  int write_pos = 1;
  for (int read_pos = 1; read_pos < arr.size(); read_pos++) {
    if (arr[read_pos] != arr[read_pos - 1]) {
      arr[write_pos++] = arr[read_pos];
    }
  }
  return write_pos;
}

void example2_remove_duplicates() {
  cout
      << "\n============== EXAMPLE 2: REMOVE DUPLICATES (SORTED) =============="
      << endl;
  cout << "Remove duplicates in-place from sorted array - O(n)\n" << endl;

  vector<int> arr = {1, 1, 2, 2, 2, 3, 4, 4, 5};

  cout << "Original: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  int new_length = remove_duplicates(arr);

  cout << "After removing duplicates (length " << new_length << "): ";
  for (int i = 0; i < new_length; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  cout << "\nTechnique: Two pointers (read and write position)" << endl;
  cout << "Time: O(n), Space: O(1)" << endl;
}

// ============== EXAMPLE 3: SLIDING WINDOW - MAXIMUM SUM SUBARRAY
// ==============
int max_sum_subarray(const vector<int> &arr, int k) {
  if (arr.size() < k)
    return -1;

  // Calculate sum of first window
  int window_sum = 0;
  for (int i = 0; i < k; i++) {
    window_sum += arr[i];
  }

  int max_sum = window_sum;

  // Slide the window
  for (int i = k; i < arr.size(); i++) {
    window_sum += arr[i] - arr[i - k]; // Add new, remove old
    max_sum = max(max_sum, window_sum);
  }

  return max_sum;
}

void example3_sliding_window_fixed() {
  cout << "\n============== EXAMPLE 3: SLIDING WINDOW (FIXED SIZE) "
          "=============="
       << endl;
  cout << "Maximum sum of k consecutive elements - O(n)\n" << endl;

  vector<int> arr = {1, 4, 2, 10, 23, 3, 1, 0, 20};
  int k = 4;

  cout << "Array: ";
  for (int x : arr)
    cout << x << " ";
  cout << "\nWindow size k = " << k << endl;

  int max_sum = max_sum_subarray(arr, k);
  cout << "\nMaximum sum of " << k << " consecutive elements: " << max_sum
       << endl;
  cout << "Subarray: [2, 10, 23, 3] = 38" << endl;

  cout << "\nTechnique: Slide window, add new element, remove old element"
       << endl;
  cout << "Time: O(n), Space: O(1)" << endl;
}

// ============== EXAMPLE 4: SLIDING WINDOW - LONGEST SUBARRAY WITH SUM K
// ==============
int longest_subarray_with_sum(const vector<int> &arr, int target) {
  int max_len = 0;
  int window_sum = 0;
  int left = 0;

  for (int right = 0; right < arr.size(); right++) {
    window_sum += arr[right];

    // Shrink window if sum exceeds target
    while (window_sum > target && left <= right) {
      window_sum -= arr[left];
      left++;
    }

    if (window_sum == target) {
      max_len = max(max_len, right - left + 1);
    }
  }

  return max_len;
}

void example4_sliding_window_variable() {
  cout << "\n============== EXAMPLE 4: SLIDING WINDOW (VARIABLE SIZE) "
          "=============="
       << endl;
  cout << "Longest subarray with sum = k (positive numbers) - O(n)\n" << endl;

  vector<int> arr = {1, 2, 3, 7, 5};
  int target = 12;

  cout << "Array: ";
  for (int x : arr)
    cout << x << " ";
  cout << "\nTarget sum: " << target << endl;

  int max_len = longest_subarray_with_sum(arr, target);
  cout << "\nLongest subarray length: " << max_len << endl;
  cout << "Subarray: [3, 7] or [7, 5]" << endl;

  cout << "\nTechnique: Expand right, shrink left when needed" << endl;
  cout << "Time: O(n), Space: O(1)" << endl;
}

// ============== EXAMPLE 5: PREFIX SUM - RANGE QUERIES ==============
class PrefixSum {
  vector<long long> prefix;

public:
  PrefixSum(const vector<int> &arr) {
    prefix.resize(arr.size() + 1, 0);
    for (int i = 0; i < arr.size(); i++) {
      prefix[i + 1] = prefix[i] + arr[i];
    }
  }

  long long range_sum(int left, int right) {
    return prefix[right + 1] - prefix[left];
  }
};

void example5_prefix_sum_queries() {
  cout
      << "\n============== EXAMPLE 5: PREFIX SUM - RANGE QUERIES =============="
      << endl;
  cout << "Answer multiple range sum queries in O(1) each\n" << endl;

  vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  cout << "Array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  PrefixSum ps(arr);

  cout << "\nRange sum queries:" << endl;
  cout << "Sum[0, 4] = " << ps.range_sum(0, 4) << " (1+2+3+4+5)" << endl;
  cout << "Sum[3, 7] = " << ps.range_sum(3, 7) << " (4+5+6+7+8)" << endl;
  cout << "Sum[5, 9] = " << ps.range_sum(5, 9) << " (6+7+8+9+10)" << endl;

  cout << "\nPreprocessing: O(n), Each query: O(1)" << endl;
  cout << "Space: O(n) for prefix array" << endl;
}

// ============== EXAMPLE 6: DIFFERENCE ARRAY - RANGE UPDATES ==============
void example6_difference_array() {
  cout << "\n============== EXAMPLE 6: DIFFERENCE ARRAY - RANGE UPDATES "
          "=============="
       << endl;
  cout << "Efficiently handle multiple range updates - O(n)\n" << endl;

  int n = 10;
  vector<int> arr(n, 0);
  vector<int> diff(n + 1, 0);

  // Range updates using difference array
  auto range_update = [&](int left, int right, int value) {
    diff[left] += value;
    diff[right + 1] -= value;
  };

  cout << "Applying range updates:" << endl;
  range_update(0, 4, 5);
  cout << "  Add 5 to range [0, 4]" << endl;
  range_update(2, 7, 3);
  cout << "  Add 3 to range [2, 7]" << endl;
  range_update(5, 9, 2);
  cout << "  Add 2 to range [5, 9]" << endl;

  // Build final array from difference array
  arr[0] = diff[0];
  for (int i = 1; i < n; i++) {
    arr[i] = arr[i - 1] + diff[i];
  }

  cout << "\nFinal array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  cout << "\nTechnique: Mark start (+value) and end+1 (-value)" << endl;
  cout << "Time: O(n + q) for q updates" << endl;
}

// ============== EXAMPLE 7: HASHING - SUBARRAY WITH SUM 0 ==============
void example7_subarray_sum_zero() {
  cout << "\n============== EXAMPLE 7: SUBARRAY WITH SUM 0 (HASHING) "
          "=============="
       << endl;
  cout << "Find if any subarray has sum = 0 - O(n)\n" << endl;

  vector<int> arr = {4, 2, -3, 1, 6};

  cout << "Array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  unordered_set<int> prefix_sums;
  prefix_sums.insert(0); // For subarray starting from index 0
  int sum = 0;
  bool found = false;

  for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];

    if (prefix_sums.find(sum) != prefix_sums.end()) {
      cout << "\nSubarray with sum 0 exists!" << endl;
      cout << "Sum appeared before at same value: " << sum << endl;
      found = true;
      break;
    }

    prefix_sums.insert(sum);
  }

  if (!found) {
    cout << "\nNo subarray with sum 0" << endl;
  }

  cout << "\nTechnique: If prefix sum repeats, subarray between has sum 0"
       << endl;
  cout << "Time: O(n), Space: O(n)" << endl;
}

// ============== EXAMPLE 8: DUTCH NATIONAL FLAG ==============
void dutch_national_flag(vector<int> &arr) {
  int low = 0, mid = 0, high = arr.size() - 1;

  while (mid <= high) {
    if (arr[mid] == 0) {
      swap(arr[low], arr[mid]);
      low++;
      mid++;
    } else if (arr[mid] == 1) {
      mid++;
    } else { // arr[mid] == 2
      swap(arr[mid], arr[high]);
      high--;
    }
  }
}

void example8_dutch_national_flag() {
  cout << "\n============== EXAMPLE 8: DUTCH NATIONAL FLAG (3-WAY PARTITION) "
          "=============="
       << endl;
  cout << "Sort array of 0s, 1s, and 2s - O(n)\n" << endl;

  vector<int> arr = {2, 0, 1, 2, 1, 0, 2, 1, 0};

  cout << "Original: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  dutch_national_flag(arr);

  cout << "Sorted: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  cout << "\nTechnique: Three pointers (low, mid, high)" << endl;
  cout << "All 0s before low, all 1s between low-mid, all 2s after high"
       << endl;
  cout << "Time: O(n), Space: O(1)" << endl;
}

// ============== EXAMPLE 9: MOORE'S VOTING ALGORITHM ==============
int find_majority_element(const vector<int> &arr) {
  int candidate = arr[0];
  int count = 1;

  // Find candidate
  for (int i = 1; i < arr.size(); i++) {
    if (arr[i] == candidate) {
      count++;
    } else {
      count--;
      if (count == 0) {
        candidate = arr[i];
        count = 1;
      }
    }
  }

  // Verify candidate appears > n/2 times
  count = 0;
  for (int x : arr) {
    if (x == candidate)
      count++;
  }

  return (count > arr.size() / 2) ? candidate : -1;
}

void example9_moore_voting() {
  cout << "\n============== EXAMPLE 9: MOORE'S VOTING ALGORITHM =============="
       << endl;
  cout << "Find majority element (appears > n/2 times) - O(n)\n" << endl;

  vector<int> arr = {2, 2, 1, 1, 2, 2, 2};

  cout << "Array: ";
  for (int x : arr)
    cout << x << " ";
  cout << endl;

  int majority = find_majority_element(arr);

  if (majority != -1) {
    cout << "\nMajority element: " << majority << endl;
  } else {
    cout << "\nNo majority element" << endl;
  }

  cout << "\nAlgorithm: Cancel out different elements, remaining is candidate"
       << endl;
  cout << "Time: O(n), Space: O(1)" << endl;
}

// ============== EXAMPLE 10: TRAPPING RAINWATER ==============
int trap_rainwater(const vector<int> &heights) {
  int n = heights.size();
  if (n <= 2)
    return 0;

  int left = 0, right = n - 1;
  int left_max = 0, right_max = 0;
  int water = 0;

  while (left < right) {
    if (heights[left] < heights[right]) {
      if (heights[left] >= left_max) {
        left_max = heights[left];
      } else {
        water += left_max - heights[left];
      }
      left++;
    } else {
      if (heights[right] >= right_max) {
        right_max = heights[right];
      } else {
        water += right_max - heights[right];
      }
      right--;
    }
  }

  return water;
}

void example10_trapping_rainwater() {
  cout << "\n============== EXAMPLE 10: TRAPPING RAINWATER =============="
       << endl;
  cout << "Calculate trapped water between bars - O(n)\n" << endl;

  vector<int> heights = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

  cout << "Heights: ";
  for (int h : heights)
    cout << h << " ";
  cout << endl;

  int water = trap_rainwater(heights);
  cout << "\nTrapped water: " << water << " units" << endl;

  cout << "\nTechnique: Two pointers with left_max and right_max tracking"
       << endl;
  cout << "Time: O(n), Space: O(1)" << endl;
}

// ============== EXAMPLE 11: BEST TIME TO BUY-SELL STOCK ==============
int max_profit_one_transaction(const vector<int> &prices) {
  int min_price = INT_MAX;
  int max_profit = 0;

  for (int price : prices) {
    min_price = min(min_price, price);
    max_profit = max(max_profit, price - min_price);
  }

  return max_profit;
}

void example11_stock_buy_sell() {
  cout << "\n============== EXAMPLE 11: STOCK BUY-SELL (ONE TRANSACTION) "
          "=============="
       << endl;
  cout << "Find maximum profit with one buy-sell - O(n)\n" << endl;

  vector<int> prices = {7, 1, 5, 3, 6, 4};

  cout << "Prices: ";
  for (int p : prices)
    cout << p << " ";
  cout << endl;

  int profit = max_profit_one_transaction(prices);
  cout << "\nMaximum profit: " << profit << endl;
  cout << "Buy at 1, sell at 6" << endl;

  cout << "\nTechnique: Track minimum price seen so far, calculate profit at "
          "each step"
       << endl;
  cout << "Time: O(n), Space: O(1)" << endl;
}

// ============== EXAMPLE 12: LONGEST CONSECUTIVE SEQUENCE ==============
int longest_consecutive(const vector<int> &nums) {
  unordered_set<int> num_set(nums.begin(), nums.end());
  int max_length = 0;

  for (int num : num_set) {
    // Only start sequence if num is the beginning
    if (num_set.find(num - 1) == num_set.end()) {
      int current = num;
      int length = 1;

      while (num_set.find(current + 1) != num_set.end()) {
        current++;
        length++;
      }

      max_length = max(max_length, length);
    }
  }

  return max_length;
}

void example12_longest_consecutive() {
  cout << "\n============== EXAMPLE 12: LONGEST CONSECUTIVE SEQUENCE "
          "=============="
       << endl;
  cout << "Find longest sequence of consecutive numbers - O(n)\n" << endl;

  vector<int> nums = {100, 4, 200, 1, 3, 2};

  cout << "Array: ";
  for (int x : nums)
    cout << x << " ";
  cout << endl;

  int longest = longest_consecutive(nums);
  cout << "\nLongest consecutive sequence length: " << longest << endl;
  cout << "Sequence: [1, 2, 3, 4]" << endl;

  cout << "\nTechnique: Use hash set, only start counting from sequence "
          "beginnings"
       << endl;
  cout << "Time: O(n), Space: O(n)" << endl;
}

/*
 * =====================================================================
 * KEY TECHNIQUES SUMMARY
 * =====================================================================
 *
 * 1. TWO POINTERS:
 *    - Opposite direction: For sorted arrays, pair sum
 *    - Same direction: Remove duplicates, partition
 *    - Time: O(n), Space: O(1)
 *
 * 2. SLIDING WINDOW:
 *    - Fixed size: Maximum sum subarray
 *    - Variable size: Longest subarray with condition
 *    - Key: Maintain window invariant
 *
 * 3. PREFIX SUM:
 *    - Range sum queries: O(1) after O(n) preprocessing
 *    - Subarray sum problems with hashing
 *
 * 4. DIFFERENCE ARRAY:
 *    - Multiple range updates efficiently
 *    - O(1) per update, O(n) to build final array
 *
 * 5. HASHING:
 *    - Subarray sum problems
 *    - Longest consecutive sequence
 *    - Space-time tradeoff
 *
 * 6. DUTCH NATIONAL FLAG:
 *    - 3-way partitioning in O(n)
 *    - Sort 0s, 1s, 2s
 *
 * 7. MOORE'S VOTING:
 *    - Find majority element in O(n) time, O(1) space
 *    - Based on cancellation
 *
 * 8. SPECIAL PROBLEMS:
 *    - Trapping rainwater: Two pointers with max tracking
 *    - Stock buy-sell: Track minimum and maximum profit
 *    - Container with most water: Two pointers
 *
 * =====================================================================
 * WHEN TO USE WHICH TECHNIQUE
 * =====================================================================
 *
 * TWO POINTERS:
 *    - Sorted array problems
 *    - Finding pairs/triplets
 *    - Partition problems
 *    - Palindrome checking
 *
 * SLIDING WINDOW:
 *    - Subarray/substring problems
 *    - "Longest/shortest subarray with condition"
 *    - "Maximum/minimum of subarrays"
 *
 * PREFIX SUM:
 *    - Multiple range sum queries
 *    - "Count subarrays with sum = k"
 *    - Equilibrium index problems
 *
 * HASHING:
 *    - "Find in O(1)" requirements
 *    - Subarray sum = k (with prefix sums)
 *    - Longest consecutive sequence
 *    - Two sum variants
 *
 * =====================================================================
 * COMPETITIVE PROGRAMMING TIPS
 * =====================================================================
 *
 * 1. Identify if array is sorted - enables two pointers, binary search
 * 2. Look for "subarray" keyword - consider sliding window
 * 3. Range queries - think prefix sum or segment tree
 * 4. "Find pair/triplet" - two pointers or hashing
 * 5. Array of 0,1,2 or limited values - counting sort or DNF
 * 6. Majority element - Moore's voting algorithm
 * 7. Maximum/minimum with constraints - monotonic stack/deque
 * 8. Practice recognizing patterns in problem statements
 * 9. Know time complexities: O(n) is ideal for array problems
 * 10. Edge cases: empty array, single element, all same values
 *
 * =====================================================================
 */

int main() {
  cout << "=========================================================" << endl;
  cout << "     ADVANCED ARRAY TECHNIQUES - COMPETITIVE PROGRAMMING   " << endl;
  cout << "=========================================================" << endl;

  example1_two_pointer_pair_sum();
  example2_remove_duplicates();
  example3_sliding_window_fixed();
  example4_sliding_window_variable();
  example5_prefix_sum_queries();
  example6_difference_array();
  example7_subarray_sum_zero();
  example8_dutch_national_flag();
  example9_moore_voting();
  example10_trapping_rainwater();
  example11_stock_buy_sell();
  example12_longest_consecutive();

  cout << "\n=========================================================" << endl;
  cout << "         PRACTICE PROBLEMS" << endl;
  cout << "=========================================================" << endl;
  cout << "\n1. Container with most water (LeetCode 11)" << endl;
  cout << "2. 3Sum problem (LeetCode 15)" << endl;
  cout << "3. Minimum window substring (LeetCode 76)" << endl;
  cout << "4. Subarray sum equals k (LeetCode 560)" << endl;
  cout << "5. Longest substring without repeating chars (LeetCode 3)" << endl;
  cout << "6. Maximum product subarray (LeetCode 152)" << endl;
  cout << "7. First missing positive (LeetCode 41)" << endl;
  cout << "8. Merge intervals (LeetCode 56)" << endl;
  cout << "9. Next permutation (LeetCode 31)" << endl;
  cout << "10. Find all duplicates in array (LeetCode 442)" << endl;

  return 0;
}
