#include<iostream>
#include <fstream>
#include<stack>
using namespace std;
int sum[50000];
int main() {
    ifstream fin("hemoglobin.in");
    ofstream fout("hemoglobin.out");
    int n,a,k=0;
    char ch;
    fin >> n;
    stack <int> client;
    for (int i = 0; i < n; i++) {
        fin >> ch;
        if (ch == '+') {
            fin >> a;
            client.push(a);
            sum[k+1] = sum[k] + a;
            k++;
        }
        else
            if (ch == '-') {
                fout << client.top() << '\n';
                client.pop();
                k--;
            }
            else {
                fin >> a;
                fout << sum[k] - sum[k - a] << '\n';
            }
    }
}
