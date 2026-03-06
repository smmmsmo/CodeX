#include <iostream>
#include <string>

using namespace std;

int main() {
    string x, y;
    cin >> x >> y;

    string array[] = {"Ocelot", "Serval", "Lynx"};
    int posX, posY;

    for(int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        if(array[i] == x) {
            posX = i;
        }
        if(array[i] == y) {
            posY = i;
        }
    }

    if(posX >= posY) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}