#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<vector>
 
 
using namespace std;
int n;
int k;
int64_t arr[100000];
const int64_t M = 1000000000000000002;
 
 
struct node {
public:
    node(int a, int b) {
        l = a;
        r = b;
    }
 
    int l, r;
    int64_t m{};
    bool s = false;
    int64_t doset{}, doadd = 0;
    node *left = nullptr;
    node *right = nullptr;
};
 
int64_t myset(node *root, int i, int j, int64_t x) ;
int64_t myadd(node *root, int i, int j, int64_t x) ;
 
 
node *inicialize(node *root) {
    if (root->l == root->r) {
        if (k < n) {
            root->m = arr[k];
            k++;
        } else {
            root->m = M;
        }
    } else {
        node *x = new node(root->l, root->l + (root->r - root->l) / 2);
        root->left = inicialize(x);
        node *y = new node(root->l + 1 + (root->r - root->l) / 2, root->r);
        root->right = inicialize(y);
        root->m = min(root->left->m, root->right->m);
    }
    return root;
}
 
void propogate(node *x) {
    if (x->s) {
       myset(x->left, x->l, x->left -> r, x->doset);
       myset(x->right, x->right -> l, x-> r, x->doset);
       x->s = false;
    }
    if (x->doadd != 0) {
        myadd(x->left, x->l, x->left -> r, x->doadd);
        myadd(x->right, x->right -> l, x-> r, x->doadd);
        x->doadd = 0;
    }
}
 
int64_t myadd(node *root, int i, int j, int64_t x) {
    if (root->l >= i && root->r <= j) {
        if (root->s) {
            root->doset += x;
        } else {
            root->doadd += x;
        }
        root->m += x;
        return root->m;
    }
    int64_t a,b;
    propogate(root);
    if (i <= root->l + (root->r - root->l) / 2) {
        a = myadd(root->left, i, j, x);
    }
    else{
        a = root -> left ->m;
    }
    if (j > root->l + (root->r - root->l) / 2) {
       b = myadd(root->right, i, j, x);
    }
    else{
        b = root -> right ->m;
    }
    root -> m = min(a,b);
    return root ->m;
}
 
int64_t myset(node *root, int i, int j, int64_t x) {
    if (root->l >= i && root->r <= j) {
        root->s = true;
        root->doadd = 0;
        root->doset = x;
        root->m = x;
        return root -> m;
    }
    int64_t a,b;
    propogate(root);
    if (i <= root->l + (root->r - root->l) / 2) {
        a = myset(root->left, i, j, x);
    } else{
        a = root -> left ->m;
    }
    if (j > root->l + (root->r - root->l) / 2) {
        b = myset(root->right, i, j, x);
    }else{
        b = root -> right ->m;
    }
    root -> m = min(a,b);
    return root ->m;
}
 
int64_t mymin(node *root, int i, int j) {
    if ((root->l >= i && root->r <= j) || root->s) {
        return root->m;
    }
    propogate(root);
    int64_t a, b;
    if (i <= (root->l + (root->r - root->l) / 2)) {
        a = mymin(root->left, i, j);
    } else {
        a = M;
    }
    if (j > root->l + (root->r - root->l) / 2) {
        b = mymin(root->right, i, j);
    } else {
        b = M;
    }
    return min(a, b);
}
 
void print(node *tree) {int64_t myset();
    cout << tree->l << " " << tree->r << " " << tree->m << " " << tree->s << " " << tree->doadd << " " << tree->doset
         << "\n";
    if (tree->l == tree->r) return;
    print(tree->left);
    print(tree->right);
}
 
int main() {
 
    freopen ("rmq2.in", "r", stdin);
    freopen("rmq2.out", "w", stdout);
//    ifstream cin("rmq2.in");
//    ofstream cout("rmq2.out");
 
    cin >> n;
    k = 0;
    float im;
    if (modf(log2f((float) n), &im) != 0) {
        im += 1;
    }
    int m = (int) im;
 
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    node *root = new node(0, (1 << m) - 1);
    inicialize(root);
    char c;
    while (cin >> c) {
        if (c == 'm') {
            int i, j;
            cin >> c >> c;
            cin >> i >> j;
            cout << mymin(root, --i, --j) << "\n";
        } else {
            if (c == 'a') {
                cin >> c >> c;
                int i, j;
                int64_t x;
                cin >> i >> j >> x;
                myadd(root, --i, --j, x);
            } else {
                cin >> c >> c;
                int i, j;
                int64_t x;
                cin >> i >> j >> x;
                myset(root, --i, --j, x);
            }
        }
        //   print(root);
    }
}
