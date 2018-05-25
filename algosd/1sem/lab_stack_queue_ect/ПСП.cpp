#include <iostream>
#include <fstream>
#include <stack>
#include <stdio.h>
 
using namespace std;
 
int main() {
    freopen("brackets.in", "r", stdin);
    freopen("brackets.out", "w", stdout);
    string s;
    cin >> s;
    int n = (int)s.length();
    stack <char> bal;
    for (int i = 0; i < n; ++i) {
        if (bal.empty()) {
            bal.push(s[i]);
        }
        else {
            if (s[i] == ']' && bal.top() == '[' || s[i] == ')' && bal.top() == '(' || s[i] == '}' && bal.top() == '{') {
                bal.pop();
            }
            else {
                bal.push(s[i]);
            }
        }
    }
    if (bal.empty()) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
}
