#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

struct dsu {
    map<int, int> id;
    
    void add (int v) {
        id[v] = v;
    }

    int get_id (int v) {
        if (v == id[v])
            return v;
        return id[v] = get_id (id[v]);
    }

    void u (int a, int b) {
        a = get_id (a);
        b = get_id (b);
        if (a != b)
            id[b] = a;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, pair<int, int>>> edges;

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        if (a != b)
            edges.push_back({c, {a, b}});
    }

    sort(edges.begin(), edges.end());

    /*for (int i = 0; i < m; i++){
        cout << edges[i].first << " " << edges[i].second.first << " " <<  edges[i].second.second << endl;
    }*/

    long long ans = 0;

    dsu id;

    for (int i = 0; i < n; i++){
        id.add(i);
    }

    int enough = 0;

    for (auto e : edges) {
        if (id.get_id(e.second.first) != id.get_id(e.second.second)) {
            id.u(e.second.first, e.second.second);
            ans += e.first;
            enough++;
            if (enough == n - 1) {
                break;
            }
        }
    }

    cout << ans;

    return 0;
}