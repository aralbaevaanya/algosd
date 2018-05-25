#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
int main() {
    cin.tie();
    ios_base::sync_with_stdio(0);
    freopen("sum0.in", "r", stdin);
    freopen("sum0.out", "w", stdout);
    int n, x, y;
    long long a;
    cin >> n >> x >> y >> a;
    long long sum[10000001];
    sum[0] = a = a % (1<<16); //inv: a is element before this
    for (int i = 1; i < n; i++) {
        a = ((a*x + y) + ((a*x + y < 0) ? (1 << 16) : 0)) % (1 << 16);
        sum[i] = sum[i-1] + a;
    }
    int m;
    long long sumofsum = 0;
    long long b1, b2 = 0;
    cin >> m >> x >> y >> b1;
 
    for (int i = 0; i < m; i++) {
        b2 = a = ((b1*x + y) + ((b1*x + y < 0)? (1<<30) : 0)) % (1 << 30);
        b1 %= n;
        b2 %= n;
        if (b1 > b2) swap(b1, b2); //b1<b2
        sumofsum += (sum[b2] -( (b1 > 0) ? sum[b1 - 1] : 0));
        b1 = ((a*x + y) + ((a*x + y < 0) ? (1 << 30) : 0)) % (1 << 30);
    }
    cout << sumofsum;
}
