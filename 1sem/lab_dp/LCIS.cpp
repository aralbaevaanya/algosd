#include <iostream>
#include <vector>
#include <functional> 
#include<algorithm>
using namespace std;
const int inf = INT_MAX;
int main() {
    int n, x;
    vector<int> a;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        a.push_back(x);
    }
    vector<int> d, pos, prev;
    int length = 0;
 
    pos.push_back(-1);
    d.push_back(INT_MIN);
    for (int i = 1; i <= n; i++) {
        d.push_back(INT_MAX);
        pos.push_back(0);
        prev.push_back(0);
    }
    for (int i = 0; i < n; i++) {
        int j = (int)(upper_bound(d.begin(), d.end(), a[i]) - d.begin());
        if (d[j - 1] < a[i] && a[i] < d[j]) {
            d[j] = a[i];
            pos[j] = i;
            prev[i] = pos[j - 1];
            length = max(length, j);
        }
    }
 
    vector<int> answer;
    int p = pos[length];
    while (p != -1) {
        answer.push_back(a[p]);
        p = prev[p];
    }
    cout << answer.size() << '\n';
    for (int i = answer.size() - 1; i >= 0; i--) {
        cout << answer[i] << ' ';
    }
}
