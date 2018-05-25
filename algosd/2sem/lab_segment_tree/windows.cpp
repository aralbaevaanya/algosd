#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include <vector>
 
using namespace std;
 
struct node {
public:
    node(int a, int b) {
        l = a;
        r = b;
    }
 
    int maxy = 0;
    int l, r;
    int m=0;
    int doadd = 0;
    node *left = nullptr;
    node *right = nullptr;
};
 
struct coord {
    int x, y1, y2, k;
 
    coord(int X, int Y1, int Y2, int K) {
        x = X;
        y1 = Y1;
        y2 = Y2;
        k = K;
    }
};
 
 
node *inicialize(node *root) {
    root->maxy = root->l;
    if (root->l == root->r) {
        return root;
    } else {
        node *x = new node(root->l, root->l + (root->r - root->l) / 2);
        root->left = inicialize(x);
        node *y = new node(root->l + 1 + (root->r - root->l) / 2, root->r);
        root->right = inicialize(y);
    }
    return root;
}
 
void propogate(node *x) {
    x->left->doadd += x->doadd;
    x->left->m += x->doadd;
    x->right->doadd += x->doadd;
    x->right->m += x->doadd;
    x->doadd = 0;
}
 
int myadd(node *root, int i, int j, int x) {
    if (root->l >= i && root->r <= j) {
        root->doadd += x;
        root->m += x;
        return root->m;
    }
    int a, b;
    propogate(root);
    if (i <= root->l + (root->r - root->l) / 2) {
        a = myadd(root->left, i, j, x);
    } else {
        a = root->left->m;
    }
    if (j > root->l + (root->r - root->l) / 2) {
        b = myadd(root->right, i, j, x);
    } else {
        b = root->right->m;
    }
    root->m = max(a, b);
    if (a > b) {
        root->maxy = root->left->maxy;
    } else {
        root->maxy = root->right->maxy;
    }
    return root->m;
}
 
 
int mymax(node *root, int i, int j) {
    if (root->l >= i && root->r <= j) {
        return root->m;
    }
    propogate(root);
    int a, b;
    if (i <= (root->l + (root->r - root->l) / 2)) {
        a = mymax(root->left, i, j);
    } else {
        a = 0;
    }
    if (j > root->l + (root->r - root->l) / 2) {
        b = mymax(root->right, i, j);
    } else {
        b = 0;
    }
    root->m = max(a, b);
    if (a > b) {
        root->maxy = root->left->maxy;
    } else {
        root->maxy = root->right->maxy;
    }
    return root->m;
}
 
bool comp(coord *a, coord *b) {
    if (a->x == b->x){
        return a->k == 1;
    }
    return (a->x < b->x);
}
 
int main() {
 
    int n;
    cin >> n;
    node *root = new node(-(1 << 20), (1 << 20) - 1);
    inicialize(root);
    vector<coord *> arr;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        arr.push_back(new coord(x1, y1, y2, 1));
        arr.push_back(new coord(x2, y1, y2, -1));
    }
    sort(arr.begin(), arr.end(), comp);
    int res = 0;
    int resx = 0, resy = 0;
    for (coord *a:arr) {
        myadd(root, a->y1, a->y2, a->k);
        if (root->m >= res) {
            res = root->m;
            resx = a->x;
            resy = root->maxy;
        }
    }
    cout << res << '\n' << resx << ' ' << resy << '\n';
}
