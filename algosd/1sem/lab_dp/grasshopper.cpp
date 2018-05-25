#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n,k;
    fin >> n >> k;
    int a;
    vector<int> p, have;
    vector<bool> use;
    p.push_back(0);
    have.push_back(0);
    use.push_back(true);
    for (int i = 0; i < n - 2; i++) {
        fin >> a;
        p.push_back(a);
        have.push_back(0);
        use.push_back(false);
    }
    p.push_back(0);
    have.push_back(0);
    use.push_back(false);
 
    for (int i = 0; i < n - 1; i++) {
        if (!use[i]) continue;
        for (int j = 1; j <= k; j++) {
            if (i + j < p.size() && (have[i] + p[j+i] > have[j+i] || !use[i+j])) {
                have[j+i] = have[i] + p[j+i];
                use[j + i] = true;
            }
        }
    }
    fout << have[n-1] << '\n';
    int count = 0;
    vector<int> jump;
    for (int i = n -1 ; i != 0; ) {
        for (int j = 1; j <= k; j++) {
            if (i - j >= 0 && have[i] == have[i-j] + p[i] && use[i-j]) {
                count++;
                i -= j;
                jump.push_back(i);
                break;
            }
        }
    }
    fout << count << '\n';
    for (int i = jump.size() - 1; i >= 0; i--)
        fout << jump[i] + 1 << ' ';
    fout << n;
}
