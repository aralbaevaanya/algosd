#include<iostream>
#include<string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <bitset>
using namespace std;
int sum = 0;
int n, m, power;
 
int check(int i, int j)
{
    unsigned int first = i&j;
    unsigned int second = (1 << n) - 1 - (i | j);
// cout << ((or<<1)& or);
    if ((((first << 1) & first) == 0)
            && ((second << 1) & second) == 0)
    {
        return 1;
    }
    else
        return 0;
}
int main()
{
    ofstream fout("nice.out");
    ifstream fin("nice.in");
    fin >> n >> m;
    vector<int> dp;
    if (n > m){
        swap(n, m);
    }
    for (int i = 0; i < (1 << n); i++)
    {
        dp.push_back(1);
    }
    vector<int> next;
    for (unsigned int k = 1; k < m; k++)
    {
        next.clear();
        for (unsigned int i = 0; i < (1 << n); i++)
        {
            next.push_back(0);
            for (unsigned int j = 0; j < ( 1 << n); j++)
            {
                next[i] += dp[j] * check(i, j);
            }
        }
        dp = next;
    }
    int ans = 0;
    for (int i = 0; i < (1 << n); i++)
    {
        ans += dp[i];
    }
    fout << ans;
 
}
