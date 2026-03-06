// store the train names in string array
// store time in array

// lexographical order of train names //func to cut train name and time from
// input string if name same then sort by time //string to int conversion of
// time if time also same then sort by index

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// creating a function so that it cuts the string at space
string get_train_name(string full_line) {
  string train_name = "";
  for (int i = 0; i < full_line.size(); i++) {
    if (full_line[i] == ' ') {
      break;
    }
    train_name += full_line[i];
  }
  return train_name;
}

// Extract time from full line, remove colon, and convert to integer
// Example: "HogwartsExpress will depart for Hogwarts at 11:15" -> 1115
int get_train_time(string full_line) {
  // Find the last space in the string
  int last_space_position = -1;
  for (int i = full_line.size() - 1; i >= 0; i--) {
    if (full_line[i] == ' ') {
      last_space_position = i;
      break;
    }
  }

  // Extract time after the last space
  string time_string = full_line.substr(last_space_position + 1);

  // Remove colon to convert "11:15" to "1115" for integer comparison
  string time_without_colon = "";
  for (int i = 0; i < time_string.size(); i++) {
    if (time_string[i] != ':') {
      time_without_colon += time_string[i];
    }
  }
  return stoi(time_without_colon);
}

// Get priority value for special lexicographical order
// a-z: 0-25, A-Z: 26-51
int get_char_priority(char c) {
  if (c >= 'a' && c <= 'z') {
    return c - 'a';
  } else if (c >= 'A' && c <= 'Z') {
    return c - 'A' + 26;
  }
  return 0;
}

// Compare two strings using special lexicographical order
// Returns: negative if s1 < s2, positive if s1 > s2, 0 if equal
int compare_special(string s1, string s2) {
  int min_len = min(s1.size(), s2.size());
  for (int i = 0; i < min_len; i++) {
    int p1 = get_char_priority(s1[i]);
    int p2 = get_char_priority(s2[i]);
    if (p1 != p2) {
      return p1 - p2;
    }
  }
  // If all characters match, shorter string comes first
  return s1.size() - s2.size();
}

// Sort trains by: 1) name (lexicographically), 2) time (ascending), 3) original
// index We sort the idx array, not the actual data, to maintain original
// entries
void sort_trains(string train_names[], int train_times[], int idx[],
                 int num_trains) {
  // Selection sort: compares each element with all elements after it
  for (int i = 0; i < num_trains - 1; i++) {
    for (int j = i + 1; j < num_trains; j++) {
      bool should_swap = false;

      // Priority 1: Compare train names using special lexicographical order
      int name_comparison =
          compare_special(train_names[idx[i]], train_names[idx[j]]);
      if (name_comparison > 0) {
        should_swap = true;
      }
      // Priority 2: If names are equal, compare departure times (latest first)
      else if (name_comparison == 0) {
        if (train_times[idx[i]] < train_times[idx[j]]) {
          should_swap = true;
        }
        // Priority 3: If both name and time equal, maintain original order
        else if (train_times[idx[i]] == train_times[idx[j]]) {
          if (idx[i] > idx[j]) {
            should_swap = true;
          }
        }
      }

      // Perform swap if any condition above was true
      if (should_swap) {
        int temp = idx[i];
        idx[i] = idx[j];
        idx[j] = temp;
      }
    }
  }
}

// sort func with given 2 parameters( train name and time array)

int main() {
  int num_trains;
  cin >> num_trains;
  cin.ignore(); // Ignore newline left in buffer after reading integer

  const int MAX = 1000;
  string entries[MAX];     // Store original full lines
  string train_names[MAX]; // Store extracted train names
  int train_times[MAX];    // Store times as integers (e.g., 1115)
  int idx[MAX];            // Store idx to maintain original order

  // Read and parse all train entries
  for (int i = 0; i < num_trains; i++) {
    getline(cin, entries[i]);
    train_names[i] = get_train_name(entries[i]);
    train_times[i] = get_train_time(entries[i]);
    idx[i] = i; // Initialize idx array: [0, 1, 2, 3, ...]
  }

  // Sort idx array based on train name, time, and original position
  // After sorting, idx might be [3, 1, 0, 2, ...] representing sorted order
  sort_trains(train_names, train_times, idx, num_trains);

  // Print entries using sorted idx (preserves original full lines)
  for (int i = 0; i < num_trains; i++) {
    cout << entries[idx[i]] << endl;
  }

  return 0;
}