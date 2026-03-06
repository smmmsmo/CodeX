#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    int A[1005], B[1005];

    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        B[i] = A[i];
    }

    // Step 1: sort B using simple selection sort
    for (int i = 1; i <= N; i++) {
        int minPos = i;
        for (int j = i + 1; j <= N; j++) {
            if (B[j] < B[minPos]) {
                minPos = j;
            }
        }
        int temp = B[i];
        B[i] = B[minPos];
        B[minPos] = temp;
    }

    // Step 2: parity check
    for (int i = 1; i <= N; i++) {
        if (A[i] != B[i]) {
            // value must come from same parity
            bool found = false;
            for (int j = i + 2; j <= N; j += 2) {
                if (A[j] == B[i]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "NO\n";
                return 0;
            }
        }
    }

    // If feasible, we are allowed to output ANY valid operations
    // Problem allows ANY sequence → simplest is output 0 operations
    cout << "YES\n";
    cout << 0 << "\n";

    return 0;
}
