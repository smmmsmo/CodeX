#include <iostream>

using namespace std;

int main() {

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    if (n % 2 == 0) {
      cout << n << " is an Even number." << endl;
    } else {
      cout << n << " is an Odd number." << endl;
    }
  }
}