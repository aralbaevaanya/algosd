#include <iostream>
#include <vector>
#include <functional> 
#include<algorithm>
using namespace std;
const int ten = 1000000000;
const vector<int> a[] = { {4,6},{6,8},{7,9},{4,8},{3,9,0},{ },{1,7,0},{2,6},{1,3},{2,4}};
int main() {
    int n;
    int d[10]; 
    for(int i = 1; i < 10; i++) {
        d[i] = 1;
    }
    d[0] = d[8] = 0;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int b[10] = { 0 };
        for (int j = 0; j < 10; j++) {
            for (int q : a[j]) {
                b[q] = (b[q] + d[j]) % ten;
            }
        }
        for (int j = 0; j < 10; j++) {
            d[j] = b[j];
        }
    }
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum  = (sum + d[i])% ten;
    }
    cout << sum;
    cin >> n;
}
