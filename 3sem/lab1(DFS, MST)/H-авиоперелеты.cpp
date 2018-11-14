#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int d[1000][1000], temp[1000][1000];

//vector<int> topSort;
vector<bool> visited;
int n;

bool checkVisited() {
    for (bool v : visited) {
        if (!v) {
            return false;
        }
    }
    return true;
}

void getTop(int v) {
    visited[v] = true;
    for (int i = 0; i < n; i++) {
        if (temp[v][i] != 0 && !visited[i]) {
            getTop(i);
        }
    }
    //topSort.push_back(v);
}

void dfs(int v){
    visited[v] = true;
    for (int i = 0; i < n; i++){
        if (temp[i][v] != 0 && !visited[i]){
            dfs(i);
        }
    }
}

int main() {

    cin.tie();
    ios_base::sync_with_stdio(0);
    freopen("avia.in", "r", stdin);
    freopen("avia.out", "w", stdout);


    cin >> n;

    int l = 0, r = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> d[i][j];
            r = max(r, d[i][j]);
        }
    }

    while (l < r) {
        int m = (l + r) / 2;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                temp[i][j] = (d[i][j] <= m ? d[i][j] : 0);
            }
        }
        visited.assign(n, false);
        getTop(0);
        if (checkVisited()){
            visited.assign(n, false);
            dfs(0);
            if (checkVisited()){
                r = m;
            } else {
                l = m + 1;
            }
        } else {
            l = m + 1;
        }

    }

    cout << l;


    return 0;
}