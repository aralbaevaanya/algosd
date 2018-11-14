#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<vector<int>> g, t;
vector<bool> visited;
vector<int> topSort;
vector<int> color;

void top(int v) {
    visited[v] = true;
    for (int vv : g[v]) {
        if (!visited[vv]) {
            top(vv);
        }
    }
    topSort.push_back(v);
}

void solve(int v, int curColor) {
    visited[v] = true;
    color[v] = curColor;
    for (int vv : t[v]) {
        if (!visited[vv]) {
            solve(vv, curColor);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    g.resize(n);
    t.resize(n);
    color.resize(n);
    visited.assign(n, false);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
            g[a].push_back(b);
            t[b].push_back(a);

    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            top(i);
        }
    }

    reverse(topSort.begin(), topSort.end());
    /*for (int a : topSort){
        cout << (a+1) << endl;
    }*/

    visited.assign(n, false);

    int temp = 0;
    for (int v : topSort) {
        if (!visited[v]) {
            solve(v, temp++);
        }
    }

    set<pair<int, int>> check;

    int ans = 0;
    for (int i = 0; i < n; i++){
        for (int v : g[i]){
            if (color[i] != color[v] && check.count({color[i], color[v]}) == 0){
                check.insert({color[i], color[v]});
                ans++;
            }
        }
    }

    cout << ans;
    return 0;
}