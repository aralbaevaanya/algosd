#include<iostream>
#include<algorithm>
#include<math.h>
#include<vector>
#include<fstream>
using namespace std;
 
vector<vector<int>> mt;
vector<int> ans;
 
int mymin(int l, int r) {
    if (l > r) swap(l,r);
    if (l == r) return ans[l];
    int d = r - l + 1;
    int k = (int)floor(log(d) / log(2));
    return min(mt[k][l], mt[k][r + 1- (1 << k)]);
}
int main() {
    int n, m, a;
    ifstream fin("sparse.in");
    fin >> n >> m >> a;
    vector<int> p;
    p.push_back(a);
    for (int i = 1; i < n; i++) {
        a = (23 * a + 21563) % 16714589;
        p.push_back(a);
    }
    //12345, 305498, 7048017,
    //11694653, 1565158, 2591019, 9471233, 570265, 13137658, 1325095
    mt.push_back(p);
    ans = p;
    for (int i = n; i < m; i++) {
        a = (23 * a + 21563) % 16714589;
        ans.push_back(a);
    }
    vector<int> q;
    int k = 1;
    while (p.size() > 1) {
        for (int i = 0; i + (1 << (k - 1)) < p.size(); i++) {
            q.push_back(min(p[i], p[i + (1 << (k - 1))]));
        }
        p = q;
        mt.push_back(q);
        q.clear();
        k++;
    }
    int u, v, u1, v1;
 
    fin >> u >> v;
    fin.close();
    for (int i = 1; i < m; i++) {
        u1 = ((17 * u + 751 + mymin(u - 1, v - 1) + 2 * i) % n) + 1;
        v1 = ((13 * v + 593 + mymin(u - 1, v - 1) + 5 * i) % n) + 1;
        u = u1;
        v = v1;
 
    }
    ofstream fout("sparse.out");
    fout << u << ' ' << v << ' ' << mymin(u - 1, v - 1);
 
}
