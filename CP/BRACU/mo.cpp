#include <iostream>

using namespace std;

// using a func calculate start to end sum it and devide them by 25

int calculate(int start, int end) {
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += i;
    }
    return sum / 25;
}

int main() {
    int start, end;
    cout << "Enter start and end: ";
    cin >> start >> end;
    cout << "Result: " << calculate(start, end) << endl;
    return 0;
}

//TODO: Hi do this l

