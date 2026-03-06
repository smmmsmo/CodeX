#include <bits/stdc++.h>

using namespace std;

int solve(string s, char target) {
    int n = s.length();
    int ops = 0;
    int left = 0, right = n - 1;
    
    while(left <= right) {
        if(s[left] == target) {
            left++;
        } else if(s[right] == target) {
            right--;
        } else {
            ops++;
            left++;
        }
    }
    return ops;
}

int main() {
    int t;
    cin >> t;
    
    while(t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        
        int ops0 = solve(s, '0');
        int ops1 = solve(s, '1');
        
        cout << min(ops0, ops1) << endl;
    }
    return 0;
}