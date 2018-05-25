#include <iostream>
#include <fstream>
#include <deque>
using namespace std;
int main() {
    ifstream in("hospital.in");
    ofstream fout("hospital.out");
    int n;
    int a;
    char c;
    in >> n;
    int cun1=0, cun2=0;
    deque<int> half1, half2;
    for (int i = 0; i < n; i++) {
        in >> c;
        if (c == '+') {
            in >> a;
            half2.push_back(a);
            cun2++;
            if (cun1 < (cun1 + cun2 + 1) / 2) {
                half1.push_back(half2.front());
                half2.pop_front();
                cun2--;
                cun1++;
            }
        }else
            if (c == '*') {
                in >> a;
                if (cun1 <= cun2) {
                    half1.push_back(a);
                    cun1++;
                }
                else {
                    half2.push_front(a);
                    cun2++;
                }
            }
            else {
                fout << half1.front()<<'\n';
                half1.pop_front();
                cun1--;
                if (cun1 < (cun1 + cun2 + 1) / 2) {
                    half1.push_back(half2.front());
                    half2.pop_front();
                    cun2--;
                    cun1++;
                }
            }
    }
}
