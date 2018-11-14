#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
int main() {
    ifstream fin("saloon.in");
    ofstream fout("saloon.out");
    int n,p;
    int len = 1;
    fin >> n;
    queue<int> q;
    int freetime;
    int hour, minut, terp;
    fin >> hour >> minut >> terp;
    fout << (hour * 60 + minut + 20) / 60 << ' ' << (hour * 60 + minut + 20) % 60 << '\n';
    freetime = hour * 60 + minut + 20;
    q.push(freetime);
    for (int i = 1; i < n; i++) {
        fin >> hour >> minut >> terp;
        minut = 60*hour + minut;
        while (len>0 && minut >= q.front()) {
            q.pop();
            len--;
        }
        if (len <= terp) {
            freetime = max(freetime, minut) + 20;
            q.push(freetime);
            len++;          
            fout << freetime / 60 << ' ' << freetime % 60 << '\n';
        }
        else
            fout <<  minut / 60 << ' ' <<  minut % 60 << '\n';
    }
 
}
        
