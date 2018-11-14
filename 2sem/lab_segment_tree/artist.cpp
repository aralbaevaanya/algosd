#include <iostream>
#include <algorithm>
 
using namespace std;
 
struct node {
    int l, r, count = 0, length = 0;
    char left = 'W', right = 'W';
    node *leftChild = nullptr, *rightChild = nullptr;
 
    node(int L, int R) {
        //cout << L << R;
        l = L;
        r = R;
        if (L < R) {
            leftChild = new node(l, l + (r - l) / 2);
            rightChild = new node(l + 1 + (r - l) / 2, r);
        }
    }
 
    void propagate() {
        if (length == 0) {
            leftChild->length = 0;
            rightChild->length = 0;
            leftChild->count = 0;
            rightChild->count = 0;
            leftChild->left = 'W';
            leftChild->right = 'W';
            rightChild->left = 'W';
            rightChild->right = 'W';
 
        }
        if (length == r - l + 1) {
            leftChild->length = length / 2;
            rightChild->length = length / 2;
            leftChild->count = 1;
            rightChild->count = 1;
            leftChild->left = 'B';
            leftChild->right = 'B';
            rightChild->left = 'B';
            rightChild->right = 'B';
        }
    }
 
    void upd(char c, int L, int R) {
        //cout  << l << " " << r << " by " << c << endl;
        //7cout << "range: [" << L << ", " << R << "]\n";
        if (l >= L && r <= R) {
            left = c;
            right = c;
            if (c == 'B') {
                count = 1;
                length = r - l + 1;
            } else {
                count = 0;
                length = 0;
            }
            return;
        }
        propagate();
 
        int mid = l + (r - l) / 2;
 
        if (L <= mid) {
            leftChild->upd(c, L, R);
        }
 
        if (R > mid) {
            rightChild->upd(c, L, R);
        }
 
        left = leftChild->left;
        right = rightChild->right;
        length = leftChild->length + rightChild->length;
        count = leftChild->count + rightChild->count - ((leftChild->right == 'B' && rightChild->left == 'B') ? 1 : 0);
    }
 
    void print() {
        cout << "left: " << l << " right: " << r << " count: " << count << " length: " << length << " leftPart: "
             << left
             << " rightPart: " << right << endl;
        if (l == r) {
            return;
        }
        leftChild->print();
        rightChild->print();
    }
 
};
 
node *root;
 
 
int main() {
    freopen("painter.in", "r", stdin);
    freopen("painter.out", "w", stdout);
    int n;
    const int N = 524288;
    cin >> n;
    root = new node(-N, N - 1);
    char c;
    int x, y;
    for (int i = 0; i < n; i++) {
        cin >> c >> x >> y;
        root->upd(c, x, x + y - 1);
        cout << root->count << ' ' << root->length << '\n';
        //root->print();
    }
 
}
