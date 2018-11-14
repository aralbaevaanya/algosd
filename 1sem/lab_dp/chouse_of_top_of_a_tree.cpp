#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
 
int const inf = 1e9;
int const maxN = 200;
 
vector <int> dp(maxN, inf);
vector <int> children[maxN];
 
int solve(int v) {
    int s1 = 1;
    int s2 = 0;
    if (dp[v] == inf) {
        if (children[v].empty()) {
            dp[v] = 1;
        }
        else {
 
            for (int u : children[v]) {
                for (int w : children[u]) {
                    s1 += solve(w);
                }
            }
            for (int u : children[v]) {
                s2 += solve(u);
            }
        }
        dp[v] = max(s1, s2);
    }
    return dp[v];
}
 
int main() {
    int n;
    cin >> n;
    int root = 0;
    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> p;
        if (p == 0) {
            root = i;
        }
        else {
            children[p].push_back(i);
        }
    }
    cout << solve(root);
}
