#include <iostream>

using namespace std;

bool is_sorted(int arr[], int size) {
  for (int i = 0; i < size - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      return false;
    }
  }
  return true;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int size;
    cin >> size;

    int arr[size];
    for (int i = 0; i < size; i++) {
      cin >> arr[i];
    }
    if (is_sorted(arr, size)) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}