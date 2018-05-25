#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
 
using namespace std;
bool f = false;
 
struct node {
    int y, size;
    node *left = nullptr, *right = nullptr;
 
    node(int i) {
        y = i;
        size = 1;
    }
 
};
 
struct mypair {
    node *first, *second;
 
    mypair(node *a, node *b) {
        first = a;
        second = b;
    }
};
 
int get_size(node *root) {
    if (root != nullptr) return root->size;
    return 0;
}
 
void calc_size(node *root) {
    if (root == nullptr)
        return;
    root->size = get_size(root->right) + get_size(root->left) + 1;
}
 
node *merge(node *a, node *b) {
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }
    if (a->y > b->y) {
        a->right = merge(a->right, b);
        calc_size(a);
        return a;
 
    }
    b->left = merge(a, b->left);
    calc_size(b);
    return b;
}
 
 
mypair split(node *root, int k) {
    mypair ans(nullptr, nullptr);
    if (root == nullptr) {
        return ans;
    }
 
    if (get_size(root->left) < k) {
        ans = split(root->right, k - get_size(root->left) - 1);
        root->right = ans.first;
        calc_size(root);
        return mypair(root, ans.second);
    }
 
    ans = split(root->left, k);
    root->left = ans.second;
    calc_size(root);
    return mypair(ans.first, root);
 
};
 
void myprint(node *root) {
    if (root == nullptr) {
        return;
    }
    myprint(root->left);
    cout << root->y << ' ';
    myprint(root->right);
 
}
 
int main() {
    int n, m;
    cin >> n >> m;
    int x, y;
    node *root = new node(1);
    for (int i = 1; i < n;) {
        root = merge(root, new node(++i));
    }
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        node *a, *b;
        mypair q = split(root, y);
        root = q.second;
        a = q.first;
        q = split(a, --x);
        root = merge(q.first, root);
        root = merge(q.second, root);
        //   myprint(root);
    }
 
    myprint(root);
 
}
