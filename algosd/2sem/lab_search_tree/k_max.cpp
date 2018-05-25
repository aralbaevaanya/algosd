#include <iostream>
#include<string>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
struct node {
    int x, k;
    int height = 0;
    node *left = nullptr, *right = nullptr;
 
    node(int y) {
        x = y;
        k = 1;
    }
};
 
 
int get_h(node *root) {
    if (root != nullptr) return root->height;
    return 0;
}
 
int get_k(node *root) {
    if (root != nullptr) return root->k;
    return 0;
}
 
void calc_k(node *root) {
    if (root == nullptr)
        return;
    root->k = get_k(root->right) + get_k(root->left) + 1;
}
 
void calc_h(node *root) {
    root->height = max(get_h(root->right), get_h(root->left)) + 1;
}
 
node *leftRotate(node *&a) {
    node *b = a->right;
    a->right = b->left;
    b->left = a;
    calc_k(a);
    calc_k(b);
    calc_h(a);
    calc_h(b);
    return b;
}
 
node *rightRotate(node *&a) {
    node *b = a->left;
    a->left = b->right;
    b->right = a;
    calc_k(a);
    calc_k(b);
    calc_h(a);
    calc_h(b);
    return b;
}
 
node *balance(node *&root) {
    calc_h(root);
    if (get_h(root->left) - get_h(root->right) == 2) {
        if (get_h(root->left->left) - get_h(root->left->right) >= 0) {
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    } else {
        if (get_h(root->left) - get_h(root->right) == -2) {
            if (get_h(root->right->left) - get_h(root->right->right) <= 0) {
                return leftRotate(root);
            } else {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
    }
    return root;
}
 
node *insert(node *&root, int x) {
    if (root == nullptr) {
        root = new node(x);
        return root;
    }
    if (x < root->x) {
        root->left = insert(root->left, x);
    } else {
        if (x > root->x) {
            root->right = insert(root->right, x);
        }
    }
    calc_k(root);
    return balance(root);
}
 
bool exists(node *&root, int x) {
    if (root == nullptr) {
        return false;
    }
    if (root->x == x) {
        return true;
    }
    if (x > root->x) {
        exists(*&root->right, x);
    } else {
        exists(*&root->left, x);
    }
}
 
node *next(node *&root, int x) {
    node *result = nullptr;
    node *current = root;
    while (current != nullptr) {
        if (current->x > x) {
            result = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return result;
}
 
 
node *prev(node *&root, int x) {
    node *result = nullptr;
    node *current = root;
 
    while (current != nullptr) {
        if (current->x < x) {
            result = current;
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return result;
}
 
node *mydelete(node *&root, int x) {
    if (root == nullptr) {
        return nullptr;
    }
    if (x > root->x) {
        root->right = mydelete(root->right, x);
        calc_k(root->right);
        calc_k(root);
    } else {
        if (x < root->x) {
            root->left = mydelete(root->left, x);
            calc_k(root->left);
            calc_k(root);
        } else {
            if (x == root->x) {
                if ((root->left != nullptr) && (root->right != nullptr)) {
                    node *a = next(root, root->x);
                    root->x = a->x;
                    root->right = mydelete(root->right, a->x);
                    calc_k(root->right);
                    calc_k(root);
                } else {
                    if (root->left != nullptr) {
                        root = root->left;
                        calc_k(root->left);
                        calc_k(root);
                    } else {
                        if (root->right != nullptr) {
                            root = root->right;
                            calc_k(root->right);
                            calc_k(root);
                        } else {
                            return nullptr;
                        }
                    }
                }
            }
        }
    }
    return balance(root);
}
 
node *find_k(node *&a, int k) {
    node *root = a;
    if (get_k(root->right) + 1 == k) {
        return root;
    }
    if (k > get_k(root->right) + 1) {
        return find_k(root->left, k - get_k(root->right) - 1);
    }
    return find_k(root->right, k);
}
 
int main() {
    int n, a, b;
    node *root = nullptr;
    cin >> n;
    node *ans;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        if (a == 1) {
            root = insert(root, b);
        } else {
            if (a == 0) {
                ans = find_k(root, b);
                cout << ans->x << '\n';
            } else {
                root = mydelete(root, b);
            }
        }
    }
}
