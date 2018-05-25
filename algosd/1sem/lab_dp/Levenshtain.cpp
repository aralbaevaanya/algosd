#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <algorithm>
using namespace std;
int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
 
    string s1, s2;
    getline(fin, s1);
    getline(fin, s2);
    vector<vector<int>> dp;
     
    for (int i = 0; i <= s1.length(); i++) {
        dp.push_back({ i });
    }
    for (int i = 1; i <= s2.length(); i++) {
        dp[0].push_back(i);
    }
    for (int i = 1; i <= s1.length(); i++) {
        for (int j = 1; j <= s2.length(); j++) {
            if (s2[j-1] == s1[i-1]) {
                dp[i].push_back(dp[i- 1][j - 1]);
            }
            else {
                dp[i].push_back(min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1])) + 1);
            }
        }
    }
    fout << dp[s1.length()][s2.length()];
}
