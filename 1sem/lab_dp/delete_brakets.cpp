#include<iostream>
#include<string>
#include <algorithm>
using namespace std;
string s;
int dp[100][100];
bool ispair(char l, char r) {
    return (l == '(' && r == ')' || l == '[' && r == ']' || l == '{' && r == '}');
}
int ans(int l, int r) {
    if (l > r) return 0;
    if (l == r) return 1;
    if (dp[l][r] != -1) {
        return dp[l][r];
    }
    int answer = s.length() + 1;
    if (ispair(s[l], s[r])) {
        answer =ans(l + 1, r - 1);
    }
     
    for (int i = l; i < r; i++) {
        answer = min(answer, ans(l, i) + ans(i + 1, r));
    }
    dp[l][r] = answer;
    return answer;
}
 
int main() {
     
    getline(cin, s);
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            dp[i][j] = -1;
        }
    }
    cout << s.length() - ans(0, s.length() - 1);
    cin >> s;
}
