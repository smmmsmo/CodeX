#include <iomanip>
#include <iostream>

using namespace std;

float string_to_num(string s) {
  float num = 0;
  for (int i = 0; i < s.size(); i++) {
    num = num * 10 + (s[i] - '0');
  }
  return num;
}

char expression_sign_finder(string s) {

  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
      return s[i];
    }
  }
  return '\0';
}

float expression_calculator(string s) {
  char sign = expression_sign_finder(s);
  int sign_index = s.find(sign);
  string first_num_str = s.substr(0, sign_index);
  string second_num_str = s.substr(sign_index + 1);
  float first_num = string_to_num(first_num_str);
  float second_num = string_to_num(second_num_str);

  switch (sign) {
  case '+':
    return first_num + second_num;
  case '-':
    return first_num - second_num;
  case '*':
    return first_num * second_num;
  case '/':
    return first_num / second_num;
  }
  return 0;
}

int main() {
  int t;
  cin >> t;
  cin.ignore();
  cout << fixed << setprecision(6);
  while (t--) {
    string line;
    getline(cin, line);

    string expr = line.substr(10);

    string s;
    for (char c : expr) {
      if (c != ' ') {
        s += c;
      }
    }

    cout << expression_calculator(s) << endl;
  }
}
