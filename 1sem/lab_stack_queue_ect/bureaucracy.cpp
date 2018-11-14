#include<iostream>
#include<fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
bool comp(pair<int, int> x, pair<int, int> y) {
    return x.first > y.first;
}
bool compnum(pair<int, int> x, pair<int, int> y) {
    return x.second < y.second;
}
int main() {
    ifstream fin("bureaucracy.in");
    ofstream fout("bureaucracy.out");
    int n, m, p;
    fin >> n >> m;
    int sum = n;
    queue<int> a;
    vector <pair<int, int>> q;
 
    for (int i = 0; i < n; i++) {
        fin >> p;
        q.push_back(pair<int, int>(p, i));
    }
    sort(q.begin(), q.begin() + n,comp);
    int k = m / n;
    int n1 = n;
    if (k > 0) {
        for (int i = n-1; i >= 0; i--) {
            if (q[i].first <= k) {
                m -= q[i].first;
                n1--;
                q.pop_back();
                if (n1>0)
                k = m / n1;
                else k = 0;
            }
            else {
                q[i].first -= k;
                m -= k;
            }
 
        }
    }
    n = n1;
    int i = 0;
    if (n1>0) {
        sort(q.begin(), q.begin() + n1, compnum);
        while (m > 0 && n1>0) {
            q[i].first--;
            if (q[i].first <= 0) n1--;
            m--;
            i++;
        }
    }
    if (n1 == 0) {
        fout << "-1";
        return 0;
    }
    fout << n1 << '\n';
    for (int j = i; j < n; j++) {
            fout << q[j].first << ' ';
    }
    for (int j =0; j<i; j++) {
        if (q[j].first > 0)
            fout << q[j].first << ' ';
    }
     
}
