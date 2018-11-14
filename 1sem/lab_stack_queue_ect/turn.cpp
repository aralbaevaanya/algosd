#include <iostream>
#include <fstream>
#include <deque>
#include <string>
using namespace std;
int main() {
    ifstream fin("kenobi.in");
    ofstream fout("kenobi.out");
    int n,a;
    fin >> n;
    string s;
    int len1=0, len2 = 0;
    deque<int> t1, t2; 
    bool f = false; //t1,t2;
    for (int i = 0; i < n; i++) {
        fin >> s;
        if (s == "add") {
            fin >> a;
            if (f) {
                t1.push_back(a);
                len1++;
                while (len2 < (len1 + len2) / 2) {
                    t2.push_back(t1.front());
                    t1.pop_front();
                    len1--;
                    len2++;
                }
            }
            else {
                t2.push_back(a);
                len2++;
                while (len1 < (len1 + len2) / 2) {
                    t1.push_back(t2.front());
                    t2.pop_front();
                    len1++;
                    len2--;
                }
            }
        }
        else
            if (s == "take") {
                if (len1 + len2 > 0) {
                    if ((f && len1>0) || len2 == 0) {
                        t1.pop_back();
                        len1--;
                        if (len2 > (len1 + len2) / 2) {
                            t1.push_front(t2.back());
                            t2.pop_back();
                            len1++;
                            len2--;
                        }
                    }
                    else {
                        t2.pop_back();
                        len2--;
                        if (len1 > (len1 + len2) / 2) {
                            t2.push_front(t1.back());
                            t1.pop_back();
                            len2++;
                            len1--;
                        }
                    }
                }
            }
            else {
                f = !f;
                if (f) {
                    if (len2 > (len1 + len2) / 2) {
                        t1.push_front(t2.back());
                        t2.pop_back();
                        len1++;
                        len2--;
                    }
                }
                else {
                    if (len1 > (len1 + len2) / 2) {
                        t2.push_front(t1.back());
                        t1.pop_back();
                        len2++;
                        len1--;
                    }
                }
            }
    }
    fout << len1 + len2 << '\n';
    if (f) {
        for (int i = 0; i < len2; i++) {
            fout << t2.front() << ' ';
            t2.pop_front();
        }
        for (int i = 0; i < len1; i++) {
            fout << t1.front() << ' ';
            t1.pop_front();
        }
    }
    else {
        for (int i = 0; i < len1; i++) {
            fout << t1.front() << ' ';
            t1.pop_front();
        }
        for (int i = 0; i < len2; i++) {
            fout << t2.front() << ' ';
            t2.pop_front();
        }
    }
}
