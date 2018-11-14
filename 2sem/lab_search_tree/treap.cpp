#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
 
using namespace std;
bool f = false;
 
struct triple {
    int x, y, z;
};
 
struct node {
    int x, y, num = 0, mn, mx;
    node *left = nullptr, *right = nullptr, *perent = nullptr;
 
    node(triple a) {
        x = a.x;
        y = a.y;
        num = a.z;
        mn = mx = a.x;
    }
};
 
node *merge(node *a, node *b) {
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }
    if (a->y < b->y) {
        if (b->mn > a->x) {
            a->mn = min(a->mn, b->mn);
            a->mx = max(a->mx, b->mx);
            b->perent = a;
            a->right = merge(a->right, b);
            return a;
        } else {
            f = true;
            return nullptr;
        }
    } else {
        if (a->mx < b->x) {
            b->mn = min(a->mn, b->mn);
            b->mx = max(a->mx, b->mx);
            a->perent = b;
            b->left = merge(a, b->left);
            return b;
        } else {
            f = true;
            return nullptr;
        }
    }
 
}
 
bool cmpPrintLikeIWant(node *a, node *b) {
    return a->num < b->num;
}
 
vector<node *> print;
 
void walk(node *root) {
    if (root == nullptr) {
        return;
    }
    print.push_back(root);
    walk(root->left);
    walk(root->right);
}
 
//void print(node *root) {
//    cout << ((root->perent == nullptr) ? 0 : root->perent->num) << ' ' <<
//         ((root->left == nullptr) ? 0 : root->left->num) << ' ' << ((root->right == nullptr) ? 0 : root->right->num)
//         << '\n';
//    if (root->left != nullptr) {
//        print(root->left);
//    }
//    if (root->right != nullptr) {
//        print(root->right);
//    }
//}
 
 
 
bool cmp(triple a, triple b) {
    return a.x < b.x;
}
 
int main() {
    int n;
    cin >> n;
    int x, y;
    vector<triple> arr;
    for (int i = 0; i < n; i++) {
        triple a;
        cin >> a.x >> a.y;
        a.z = i + 1;
        arr.push_back(a);
    }
    sort(arr.begin(), arr.end(), cmp);
    queue<node *> q, copyq;
    for (triple a:arr) {
        q.push(new node(a));
    }
    arr.clear();
    while (q.size() > 1) {
        while (!q.empty()) {
            node *a = q.front();
            q.pop();
            if (!q.empty()) {
                node *b = q.front();
                q.pop();
                copyq.push(merge(a, b));
            } else {
                if (a != nullptr) {
                    copyq.push(a);
                }
            }
            if (f) {
                cout << "NO";
                return 0;
            }
        }
        q.swap(copyq);
    }
 
    cout << "YES\n";
    walk(q.front());
    sort(print.begin(), print.end(), cmpPrintLikeIWant);
    for (node *a : print) {
        cout << ((a->perent == nullptr) ? 0 : a->perent->num) << ' ' <<
             ((a->left == nullptr) ? 0 : a->left->num) << ' ' << ((a->right == nullptr) ? 0 : a->right->num) << '\n';
    }
}
