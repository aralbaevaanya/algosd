#include<iostream>
#include <stdint-gcc.h>
 
 
using namespace std;
int n = 0;
int k = 0;
int64_t arr[500005] = {0};
 
 
struct node {
public:
    node(int a, int b) {
        l = a;
        r = b;
 
    }
 
    int l = 0, r = 0;
    int64_t sum;
    node *left = nullptr;
    node *right = nullptr;
};
 
 
node *inicialize(node *root) {
    if (root->l == root->r) {
        if (k <= n) {
            root->sum = arr[k];
            k++;
        } else {
            root->sum = 0;
        }
    } else {
        node *x = new node(root->l, root->l + (root->r - root->l) / 2);
        root->left = inicialize(x);
        node *y = new node(root->l + 1 + (root->r - root->l) / 2, root->r);
        root->right = inicialize(y);
        root->sum = root->left->sum + root->right->sum;
    }
    return root;
}
 
int64_t myset(node *root, int i, int64_t x) {
    if (root->l == i && root->r == i) {
        root->sum = x;
        return root->sum;
    }
    int64_t a, b;
    if (i <= root->l + (root->r - root->l) / 2) {
        a = myset(root->left, i, x);
    } else {
        a = root->left->sum;
    }
    if (i > root->l + (root->r - root->l) / 2) {
        b = myset(root->right, i, x);
    } else {
        b = root->right->sum;
    }
    root->sum = a + b;
    return root->sum;
}
 
int64_t mysum(node *root, int i, int j) {
    if (root->l >= i && root->r <= j) {
        return root->sum;
    }
    int64_t a, b;
    if (i <= (root->l + (root->r - root->l) / 2)) {
        a = mysum(root->left, i, j);
    } else {
        a = 0;
    }
    if (j > root->l + (root->r - root->l) / 2) {
        b = mysum(root->right, i, j);
    } else {
        b = 0;
    }
    return a + b;
}
 
 
int main() {
 
    freopen("rsq.in", "r", stdin);
    freopen("rsq.out", "w", stdout);
    cin >> n;
    k = 1;
    int m = 0;
    while (n > (1 << m)) m++;
 
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    node *root = new node(1, (1 << m));
    inicialize(root);
    char c;
    while (cin >> c) {
        cin >> c;
        if (c == 'e') {
            int i, j;
            cin >> c;
            cin >> i >> j;
            myset(root, i, j);
        } else {
            cin >> c;
            int i, j;
            cin >> i >> j;
            cout << mysum(root, i, j) << '\n';
        }
    }
}
