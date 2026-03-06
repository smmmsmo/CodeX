#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    cin >> s;

    int count[26] = {0};
    
    for(int i = 0; i < s.size(); i++) {
        count[s[i] - 'a']++;
    }
    
    for(int i = 0; i < 26; i++) {
        if(count[i] == 1) {
            cout << (char)('a' + i) << endl;
            break;
        }
    }

    return 0;
}