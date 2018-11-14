#include <iostream>
#include <fstream>
#include <deque>
#include <string>
using namespace std;
int main() {
    char ch;
    deque <char> cipher;
    ifstream in("decode.in");
    while ((ch = in.get()) != EOF) {
        if ((cipher.empty()) || (cipher.back() != ch)) {
            cipher.push_back(ch);
        }
        else{
            cipher.pop_back();
        }
    }
    in.close();
    ofstream fout("decode.out");
    while (!cipher.empty()) {
        fout << cipher.front();
        cipher.pop_front();
    }
    fout.close();
}
