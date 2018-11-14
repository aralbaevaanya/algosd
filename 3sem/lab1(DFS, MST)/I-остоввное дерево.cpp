#include <iostream>
#include <vector>
#include <math.h>
#include <set>


using namespace std;
using pdd = pair<double, double>;

double dist(pdd f, pdd s) {
    return sqrt((f.first - s.first) * (f.first - s.first) + (f.second - s.second) * (f.second - s.second));
}

int main() {
    int n;
    cin >> n;

    vector<pdd> dots;
    vector<double> minDist;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        dots.emplace_back(a, b);
    }

    for (int i = 0; i < n; i++) {
        minDist.push_back(dist(dots[0], dots[i]));
    }
    set<int> got;
    for (int i = 1; i < n; i++) {
        got.insert(i);
    }

    double ans = 0;

    for (int i = 0; i < n - 1; i++) {
        int k = 0;
        for (int j : got) {
            if (k == 0 || minDist[j] < minDist[k]) {
                k = j;
            }
        }

        got.erase(k);
        ans += minDist[k];
        for (int j : got) {

            minDist[j] = min(minDist[j], dist(dots[k], dots[j]));

        }
    }

    cout << ans;

    return 0;
}