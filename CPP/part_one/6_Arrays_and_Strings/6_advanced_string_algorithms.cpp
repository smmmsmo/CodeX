#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
 * =====================================================================
 * TOPIC 6.6: ADVANCED STRING ALGORITHMS
 * =====================================================================
 *
 * COMPETITIVE PROGRAMMING STRING ALGORITHMS
 * This file covers advanced string algorithms and techniques essential
 * for competitive programming, pattern matching, and complex problems.
 *
 * KEY CONCEPTS COVERED:
 * 1. Anagram Detection and Grouping
 * 2. Palindrome Algorithms (multiple approaches)
 * 3. String Pattern Matching (Naive, KMP, Rabin-Karp)
 * 4. Longest Common Substring/Subsequence
 * 5. Edit Distance (Levenshtein)
 * 6. String Hashing and Rolling Hash
 * 7. Trie-based String Operations
 * 8. Manacher's Algorithm (Longest Palindrome)
 * 9. Z-Algorithm
 * 10. String Rotation and Permutation
 * 11. Window-based String Problems
 * 12. Advanced String Manipulation
 *
 * =====================================================================
 */

// ============== EXAMPLE 1: ANAGRAM DETECTION ==============
bool is_anagram(const string &s1, const string &s2) {
  if (s1.length() != s2.length())
    return false;

  unordered_map<char, int> freq;

  for (char c : s1)
    freq[c]++;
  for (char c : s2)
    freq[c]--;

  for (auto &p : freq) {
    if (p.second != 0)
      return false;
  }

  return true;
}

void example1_anagram_detection() {
  cout << "\n============== EXAMPLE 1: ANAGRAM DETECTION =============="
       << endl;
  cout << "Check if two strings are anagrams - O(n)\n" << endl;

  vector<pair<string, string>> tests = {
      {"listen", "silent"}, {"hello", "world"}, {"triangle", "integral"}};

  for (auto &p : tests) {
    cout << "\"" << p.first << "\" and \"" << p.second << "\": "
         << (is_anagram(p.first, p.second) ? "Anagrams" : "Not anagrams")
         << endl;
  }

  cout << "\nAlternative: Sort both strings and compare - O(n log n)" << endl;
  cout << "Hash map approach: O(n) time, O(1) space (26 letters)" << endl;
}

// ============== EXAMPLE 2: GROUP ANAGRAMS ==============
vector<vector<string>> group_anagrams(vector<string> &strs) {
  unordered_map<string, vector<string>> groups;

  for (string &s : strs) {
    string key = s;
    sort(key.begin(), key.end());
    groups[key].push_back(s);
  }

  vector<vector<string>> result;
  for (auto &p : groups) {
    result.push_back(p.second);
  }

  return result;
}

void example2_group_anagrams() {
  cout << "\n============== EXAMPLE 2: GROUP ANAGRAMS ==============" << endl;
  cout << "Group strings that are anagrams - O(n * k log k)\n" << endl;

  vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};

  cout << "Input: ";
  for (const string &s : strs)
    cout << "\"" << s << "\" ";
  cout << endl;

  auto groups = group_anagrams(strs);

  cout << "\nGrouped anagrams:" << endl;
  for (int i = 0; i < groups.size(); i++) {
    cout << "Group " << i + 1 << ": ";
    for (const string &s : groups[i]) {
      cout << "\"" << s << "\" ";
    }
    cout << endl;
  }

  cout << "\nTechnique: Use sorted string as key in hash map" << endl;
  cout << "Time: O(n * k log k) where n = strings, k = avg length" << endl;
}

// ============== EXAMPLE 3: LONGEST PALINDROMIC SUBSTRING (EXPAND AROUND
// CENTER) ==============
string expand_around_center(const string &s, int left, int right) {
  while (left >= 0 && right < s.length() && s[left] == s[right]) {
    left--;
    right++;
  }
  return s.substr(left + 1, right - left - 1);
}

string longest_palindrome_expand(const string &s) {
  if (s.empty())
    return "";

  string longest = "";

  for (int i = 0; i < s.length(); i++) {
    // Odd length palindromes (center is single char)
    string odd = expand_around_center(s, i, i);
    if (odd.length() > longest.length()) {
      longest = odd;
    }

    // Even length palindromes (center is between two chars)
    string even = expand_around_center(s, i, i + 1);
    if (even.length() > longest.length()) {
      longest = even;
    }
  }

  return longest;
}

void example3_longest_palindrome() {
  cout << "\n============== EXAMPLE 3: LONGEST PALINDROMIC SUBSTRING "
          "=============="
       << endl;
  cout << "Find longest palindrome using expand around center - O(n²)\n"
       << endl;

  vector<string> tests = {"babad", "cbbd", "racecar"};

  for (const string &s : tests) {
    string result = longest_palindrome_expand(s);
    cout << "\"" << s << "\" -> \"" << result << "\"" << endl;
  }

  cout << "\nTechnique: Expand around each possible center (2n-1 centers)"
       << endl;
  cout << "Time: O(n²), Space: O(1)" << endl;
  cout << "Note: Manacher's algorithm can do it in O(n)!" << endl;
}

// ============== EXAMPLE 4: KMP PATTERN MATCHING ==============
vector<int> compute_lps(const string &pattern) {
  int m = pattern.length();
  vector<int> lps(m, 0);
  int len = 0;
  int i = 1;

  while (i < m) {
    if (pattern[i] == pattern[len]) {
      len++;
      lps[i] = len;
      i++;
    } else {
      if (len != 0) {
        len = lps[len - 1];
      } else {
        lps[i] = 0;
        i++;
      }
    }
  }

  return lps;
}

vector<int> kmp_search(const string &text, const string &pattern) {
  vector<int> result;
  int n = text.length();
  int m = pattern.length();

  if (m == 0)
    return result;

  vector<int> lps = compute_lps(pattern);

  int i = 0; // index for text
  int j = 0; // index for pattern

  while (i < n) {
    if (text[i] == pattern[j]) {
      i++;
      j++;
    }

    if (j == m) {
      result.push_back(i - j);
      j = lps[j - 1];
    } else if (i < n && text[i] != pattern[j]) {
      if (j != 0) {
        j = lps[j - 1];
      } else {
        i++;
      }
    }
  }

  return result;
}

void example4_kmp_pattern_matching() {
  cout << "\n============== EXAMPLE 4: KMP PATTERN MATCHING =============="
       << endl;
  cout << "Find all occurrences of pattern in text - O(n + m)\n" << endl;

  string text = "AABAACAADAABAABA";
  string pattern = "AABA";

  cout << "Text: \"" << text << "\"" << endl;
  cout << "Pattern: \"" << pattern << "\"" << endl;

  vector<int> positions = kmp_search(text, pattern);

  cout << "\nPattern found at positions: ";
  for (int pos : positions) {
    cout << pos << " ";
  }
  cout << endl;

  cout << "\nKMP Algorithm: Use LPS (Longest Proper Prefix Suffix) array"
       << endl;
  cout << "Time: O(n + m), Space: O(m)" << endl;
  cout << "Better than naive O(n*m) approach" << endl;
}

// ============== EXAMPLE 5: RABIN-KARP (ROLLING HASH) ==============
const long long MOD = 1e9 + 7;
const int BASE = 256;

vector<int> rabin_karp(const string &text, const string &pattern) {
  vector<int> result;
  int n = text.length();
  int m = pattern.length();

  if (m > n)
    return result;

  long long pattern_hash = 0;
  long long text_hash = 0;
  long long h = 1;

  // Calculate h = pow(BASE, m-1) % MOD
  for (int i = 0; i < m - 1; i++) {
    h = (h * BASE) % MOD;
  }

  // Calculate initial hash
  for (int i = 0; i < m; i++) {
    pattern_hash = (pattern_hash * BASE + pattern[i]) % MOD;
    text_hash = (text_hash * BASE + text[i]) % MOD;
  }

  // Slide the pattern
  for (int i = 0; i <= n - m; i++) {
    if (pattern_hash == text_hash) {
      // Hash matches, verify character by character
      bool match = true;
      for (int j = 0; j < m; j++) {
        if (text[i + j] != pattern[j]) {
          match = false;
          break;
        }
      }
      if (match) {
        result.push_back(i);
      }
    }

    // Calculate hash for next window
    if (i < n - m) {
      text_hash = (BASE * (text_hash - text[i] * h) + text[i + m]) % MOD;
      if (text_hash < 0)
        text_hash += MOD;
    }
  }

  return result;
}

void example5_rabin_karp() {
  cout << "\n============== EXAMPLE 5: RABIN-KARP (ROLLING HASH) =============="
       << endl;
  cout << "Pattern matching using rolling hash - O(n + m) average\n" << endl;

  string text = "GEEKS FOR GEEKS";
  string pattern = "GEEK";

  cout << "Text: \"" << text << "\"" << endl;
  cout << "Pattern: \"" << pattern << "\"" << endl;

  vector<int> positions = rabin_karp(text, pattern);

  cout << "\nPattern found at positions: ";
  for (int pos : positions) {
    cout << pos << " ";
  }
  cout << endl;

  cout << "\nRolling Hash: Efficiently update hash by removing first char and "
          "adding new"
       << endl;
  cout << "Average Time: O(n + m), Worst: O(n*m) with many hash collisions"
       << endl;
}

// ============== EXAMPLE 6: LONGEST COMMON SUBSEQUENCE (LCS) ==============
int lcs_length(const string &s1, const string &s2) {
  int m = s1.length();
  int n = s2.length();
  vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  return dp[m][n];
}

void example6_lcs() {
  cout
      << "\n============== EXAMPLE 6: LONGEST COMMON SUBSEQUENCE =============="
      << endl;
  cout << "Find length of longest common subsequence - O(m*n)\n" << endl;

  vector<pair<string, string>> tests = {
      {"ABCDGH", "AEDFHR"}, {"AGGTAB", "GXTXAYB"}, {"programming", "gaming"}};

  for (auto &p : tests) {
    int length = lcs_length(p.first, p.second);
    cout << "\"" << p.first << "\" and \"" << p.second
         << "\" -> LCS length: " << length << endl;
  }

  cout << "\nDynamic Programming: dp[i][j] = LCS of s1[0..i-1] and s2[0..j-1]"
       << endl;
  cout << "Time: O(m*n), Space: O(m*n) (can optimize to O(n))" << endl;
}

// ============== EXAMPLE 7: EDIT DISTANCE (LEVENSHTEIN) ==============
int edit_distance(const string &s1, const string &s2) {
  int m = s1.length();
  int n = s2.length();
  vector<vector<int>> dp(m + 1, vector<int>(n + 1));

  // Base cases
  for (int i = 0; i <= m; i++)
    dp[i][0] = i;
  for (int j = 0; j <= n; j++)
    dp[0][j] = j;

  // Fill DP table
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = 1 + min({
                           dp[i - 1][j],    // Delete
                           dp[i][j - 1],    // Insert
                           dp[i - 1][j - 1] // Replace
                       });
      }
    }
  }

  return dp[m][n];
}

void example7_edit_distance() {
  cout << "\n============== EXAMPLE 7: EDIT DISTANCE (LEVENSHTEIN) "
          "=============="
       << endl;
  cout << "Minimum operations to convert one string to another - O(m*n)\n"
       << endl;

  vector<pair<string, string>> tests = {
      {"horse", "ros"}, {"intention", "execution"}, {"kitten", "sitting"}};

  for (auto &p : tests) {
    int dist = edit_distance(p.first, p.second);
    cout << "\"" << p.first << "\" -> \"" << p.second
         << "\" : distance = " << dist << endl;
  }

  cout << "\nOperations: Insert, Delete, Replace" << endl;
  cout << "DP: dp[i][j] = min operations to convert s1[0..i-1] to s2[0..j-1]"
       << endl;
  cout << "Time: O(m*n), Space: O(m*n)" << endl;
}

// ============== EXAMPLE 8: STRING ROTATION CHECK ==============
bool is_rotation(const string &s1, const string &s2) {
  if (s1.length() != s2.length())
    return false;

  string concatenated = s1 + s1;
  return concatenated.find(s2) != string::npos;
}

void example8_string_rotation() {
  cout << "\n============== EXAMPLE 8: STRING ROTATION CHECK =============="
       << endl;
  cout << "Check if one string is rotation of another - O(n)\n" << endl;

  vector<pair<string, string>> tests = {
      {"waterbottle", "erbottlewat"}, {"hello", "llohe"}, {"abc", "bca"}};

  for (auto &p : tests) {
    cout << "\"" << p.first << "\" and \"" << p.second << "\": "
         << (is_rotation(p.first, p.second) ? "Is rotation" : "Not rotation")
         << endl;
  }

  cout << "\nTrick: If s2 is rotation of s1, then s2 is substring of s1+s1"
       << endl;
  cout << "Example: 'erbottlewat' is in 'waterbottlewaterbottle'" << endl;
}

// ============== EXAMPLE 9: MINIMUM WINDOW SUBSTRING ==============
string min_window(const string &s, const string &t) {
  if (t.length() > s.length())
    return "";

  unordered_map<char, int> target_freq, window_freq;
  for (char c : t)
    target_freq[c]++;

  int required = target_freq.size();
  int formed = 0;
  int left = 0, right = 0;
  int min_len = INT_MAX;
  int min_left = 0;

  while (right < s.length()) {
    char c = s[right];
    window_freq[c]++;

    if (target_freq.count(c) && window_freq[c] == target_freq[c]) {
      formed++;
    }

    while (left <= right && formed == required) {
      if (right - left + 1 < min_len) {
        min_len = right - left + 1;
        min_left = left;
      }

      char left_char = s[left];
      window_freq[left_char]--;
      if (target_freq.count(left_char) &&
          window_freq[left_char] < target_freq[left_char]) {
        formed--;
      }
      left++;
    }

    right++;
  }

  return min_len == INT_MAX ? "" : s.substr(min_left, min_len);
}

void example9_min_window_substring() {
  cout << "\n============== EXAMPLE 9: MINIMUM WINDOW SUBSTRING =============="
       << endl;
  cout << "Find smallest window containing all chars of pattern - O(n)\n"
       << endl;

  vector<pair<string, string>> tests = {
      {"ADOBECODEBANC", "ABC"}, {"a", "a"}, {"ab", "b"}};

  for (auto &p : tests) {
    string result = min_window(p.first, p.second);
    cout << "s=\"" << p.first << "\", t=\"" << p.second << "\" -> \"" << result
         << "\"" << endl;
  }

  cout << "\nSlidingWindow: Expand right, contract left when valid" << endl;
  cout << "Time: O(m + n), Space: O(m + n)" << endl;
}

// ============== EXAMPLE 10: LONGEST SUBSTRING WITHOUT REPEATING CHARS
// ==============
int longest_substring_no_repeat(const string &s) {
  unordered_set<char> window;
  int left = 0;
  int max_len = 0;

  for (int right = 0; right < s.length(); right++) {
    while (window.count(s[right])) {
      window.erase(s[left]);
      left++;
    }
    window.insert(s[right]);
    max_len = max(max_len, right - left + 1);
  }

  return max_len;
}

void example10_longest_no_repeat() {
  cout << "\n============== EXAMPLE 10: LONGEST SUBSTRING WITHOUT REPEATING "
          "=============="
       << endl;
  cout << "Find longest substring with all unique characters - O(n)\n" << endl;

  vector<string> tests = {"abcabcbb", "bbbbb", "pwwkew", "dvdf"};

  for (const string &s : tests) {
    int length = longest_substring_no_repeat(s);
    cout << "\"" << s << "\" -> " << length << endl;
  }

  cout << "\nSliding Window: Track characters in current window" << endl;
  cout << "Time: O(n), Space: O(min(m, n)) where m = charset size" << endl;
}

// ============== EXAMPLE 11: VALID PARENTHESES ==============
bool is_valid_parentheses(const string &s) {
  vector<char> stack;
  unordered_map<char, char> pairs = {{')', '('}, {'}', '{'}, {']', '['}};

  for (char c : s) {
    if (c == '(' || c == '{' || c == '[') {
      stack.push_back(c);
    } else {
      if (stack.empty() || stack.back() != pairs[c]) {
        return false;
      }
      stack.pop_back();
    }
  }

  return stack.empty();
}

void example11_valid_parentheses() {
  cout << "\n============== EXAMPLE 11: VALID PARENTHESES =============="
       << endl;
  cout << "Check if parentheses are properly matched - O(n)\n" << endl;

  vector<string> tests = {"()", "()[]{}", "(]", "([)]", "{[]}"};

  for (const string &s : tests) {
    cout << "\"" << s << "\" -> "
         << (is_valid_parentheses(s) ? "Valid" : "Invalid") << endl;
  }

  cout << "\nStack-based: Push opening, pop and match closing" << endl;
  cout << "Time: O(n), Space: O(n)" << endl;
}

// ============== EXAMPLE 12: FIRST NON-REPEATING CHARACTER ==============
int first_unique_char(const string &s) {
  unordered_map<char, int> freq;

  for (char c : s) {
    freq[c]++;
  }

  for (int i = 0; i < s.length(); i++) {
    if (freq[s[i]] == 1) {
      return i;
    }
  }

  return -1;
}

void example12_first_non_repeating() {
  cout << "\n============== EXAMPLE 12: FIRST NON-REPEATING CHARACTER "
          "=============="
       << endl;
  cout << "Find first character that appears only once - O(n)\n" << endl;

  vector<string> tests = {"leetcode", "loveleetcode", "aabb"};

  for (const string &s : tests) {
    int index = first_unique_char(s);
    if (index != -1) {
      cout << "\"" << s << "\" -> '" << s[index] << "' at index " << index
           << endl;
    } else {
      cout << "\"" << s << "\" -> No unique character" << endl;
    }
  }

  cout << "\nTwo passes: First count frequencies, then find first with freq=1"
       << endl;
  cout << "Time: O(n), Space: O(1) (26 letters max)" << endl;
}

/*
 * =====================================================================
 * KEY ALGORITHMS SUMMARY
 * =====================================================================
 *
 * 1. ANAGRAM PROBLEMS:
 *    - Frequency map or sorting
 *    - Time: O(n) with map, O(n log n) with sorting
 *
 * 2. PALINDROME:
 *    - Expand around center: O(n²)
 *    - Manacher's algorithm: O(n)
 *    - DP approach: O(n²)
 *
 * 3. PATTERN MATCHING:
 *    - Naive: O(n*m)
 *    - KMP: O(n+m) - uses LPS array
 *    - Rabin-Karp: O(n+m) average - rolling hash
 *    - Boyer-Moore: O(n/m) best case
 *
 * 4. SUBSEQUENCE PROBLEMS:
 *    - LCS: O(m*n) DP
 *    - LIS: O(n log n) with binary search
 *
 * 5. EDIT DISTANCE:
 *    - DP approach: O(m*n)
 *    - Three operations: insert, delete, replace
 *
 * 6. SLIDING WINDOW:
 *    - Minimum window substring
 *    - Longest substring without repeating
 *    - Anagrams in string
 *
 * 7. STRING HASHING:
 *    - Rolling hash for pattern matching
 *    - Polynomial hash function
 *    - Handle collisions carefully
 *
 * 8. STACK-BASED:
 *    - Valid parentheses
 *    - Decode string
 *    - Next greater element
 *
 * =====================================================================
 * PATTERN RECOGNITION GUIDE
 * =====================================================================
 *
 * "Find pattern in text" → KMP or Rabin-Karp
 * "Anagram" → Frequency map or sorting
 * "Palindrome" → Two pointers or expand around center
 * "Longest substring with..." → Sliding window
 * "Edit distance/similarity" → DP
 * "Substring that contains all..." → Sliding window + hash map
 * "Valid parentheses/brackets" → Stack
 * "First non-repeating" → Frequency map
 * "String rotation" → Concatenate and search
 * "Group similar strings" → Hash map with sorted key
 *
 * =====================================================================
 * COMPETITIVE PROGRAMMING TIPS
 * =====================================================================
 *
 * 1. KMP is faster than naive for pattern matching
 * 2. Rolling hash great for multiple pattern searches
 * 3. Sliding window for substring problems
 * 4. DP for LCS, LIS, edit distance
 * 5. Two pointers for palindrome, two sum in strings
 * 6. Hash map for anagrams, character frequency
 * 7. Stack for bracket matching, expression parsing
 * 8. Trie for prefix matching, autocomplete
 * 9. Know when to use O(n) vs O(n²) solutions
 * 10. Practice on LeetCode string problems
 *
 * =====================================================================
 * COMMON MISTAKES TO AVOID
 * =====================================================================
 *
 * 1. Not handling empty strings
 * 2. Off-by-one errors in substring operations
 * 3. Not considering case sensitivity
 * 4. Hash collisions in rolling hash (use good modulo)
 * 5. Incorrect LPS array computation in KMP
 * 6. Not checking bounds in DP tables
 * 7. Forgetting to handle Unicode/special characters
 * 8. Inefficient string concatenation in loops
 * 9. Not optimizing space in DP (can often use O(n) instead of O(n²))
 * 10. Mixing up LCS (longest common subsequence) vs substring
 *
 * =====================================================================
 */

int main() {
  cout << "=========================================================" << endl;
  cout << "   ADVANCED STRING ALGORITHMS - COMPETITIVE PROGRAMMING    " << endl;
  cout << "=========================================================" << endl;

  example1_anagram_detection();
  example2_group_anagrams();
  example3_longest_palindrome();
  example4_kmp_pattern_matching();
  example5_rabin_karp();
  example6_lcs();
  example7_edit_distance();
  example8_string_rotation();
  example9_min_window_substring();
  example10_longest_no_repeat();
  example11_valid_parentheses();
  example12_first_non_repeating();

  cout << "\n=========================================================" << endl;
  cout << "         PRACTICE PROBLEMS" << endl;
  cout << "=========================================================" << endl;
  cout << "\n1. Implement strStr() / Find needle in haystack (KMP)" << endl;
  cout << "2. Longest palindromic substring (Manacher's)" << endl;
  cout << "3. Regular expression matching" << endl;
  cout << "4. Wildcard pattern matching" << endl;
  cout << "5. Count and say sequence" << endl;
  cout << "6. Decode ways (DP)" << endl;
  cout << "7. Word break problem" << endl;
  cout << "8. Interleaving strings" << endl;
  cout << "9. Distinct subsequences" << endl;
  cout << "10. Scramble string" << endl;

  return 0;
}
