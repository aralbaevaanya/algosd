#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;
int main() {
    ifstream fin("postfix.in");
    int a,b;
    char ch;
    stack <int> count;
    while (fin >> ch) {
        switch (ch) {
        case  '+': {
                a = count.top();
                count.pop();
                b = count.top();
                count.pop();
                count.push(a + b);
                break;
            }
        case  '*': {
            a = count.top();
            count.pop();
            b = count.top();
            count.pop();
            count.push(a * b);
            break;
        }
        case  '-': {
            a = count.top();
            count.pop();
            b = count.top();
            count.pop();
            count.push(b - a);
            break;
        }
        default: count.push(ch - '0');
 
        }
    }
    freopen("postfix.out", "w", stdout);
    int ans = count.top();
    cout << ans << '\n';
    return 0;
}
