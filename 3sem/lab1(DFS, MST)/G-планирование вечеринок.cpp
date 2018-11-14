#include <iostream>
#include <bits/stdc++.h>

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

void setColor(int v, int tempColor) {
    color[v] = tempColor;
    visited[v] = true;
    for (int vv : t[v]) {
        if (!visited[vv]) {
            setColor(vv, tempColor);
        }
    }
}

int main() {

    unsigned int n, m;
    cin >> n >> m;

    map<string, int> id;
    vector<string> name;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        id.insert({s, i});
        name.push_back(s);
    }

    g.resize(2 * n);
    t.resize(2 * n);
    for (int i = 0; i < m; i++) {
        string f, s;
        cin >> f >> s >> s;
        //cout << f << "!" << s << endl;
        g[id.at(f.substr(1)) + (f[0] == '+' ? 0 : n)].push_back(id.at(s.substr(1)) + (s[0] == '+' ? 0 : n));
        t[id.at(s.substr(1)) + (s[0] == '+' ? 0 : n)].push_back(id.at(f.substr(1)) + (f[0] == '+' ? 0 : n));
        g[(id.at(s.substr(1)) + (s[0] == '+' ? 0 : n) + n) % (2 * n)].push_back(
                (id.at(f.substr(1)) + (f[0] == '+' ? 0 : n) + n) % (2 * n));
        t[(id.at(f.substr(1)) + (f[0] == '+' ? 0 : n) + n) % (2 * n)].push_back(
                (id.at(s.substr(1)) + (s[0] == '+' ? 0 : n) + n) % (2 * n));
    }

    //cout << "_________________" << endl;

    /*for (int i = 0; i < 2 * n; i++) {
        cout << "vertex " << i << endl;
        for (int x : g[i]){
            cout << x << " ";
        }
        cout << endl;
    }*/

    visited.assign(2 * n, false);
    color.resize(2 * n);

    for (int i = 0; i < 2 * n; i++) {
        if (!visited[i]) {
            top(i);
        }
    }

    reverse(topSort.begin(), topSort.end());
    int curColor = 0;

    visited.assign(2 * n, false);
    for (int x : topSort) {
        if (!visited[x]) {
            setColor(x, curColor++);
        }
    }

    for (int i = 0; i < n; i++) {
        if (color[i] == color[i + n]) {
            cout << -1;
            return 0;
        }
    }


    vector<string> guys;
    for (int i = 0; i < n; i++) {
        if (color[i] > color[i + n]){
            guys.push_back(name[i]);
        }
    }

    cout << guys.size() << endl;
    for (string guy : guys){
        cout << guy << endl;
    }
    return 0;
}