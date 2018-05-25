#include <iostream>
#include<string>
 
using namespace std;
 
struct node {
    int x;
    int height = 0;
    node *left = nullptr, *right = nullptr;
 
    node(int y) {
        x = y;
    }
};
 
 
int get_h(node *root) {
    if (root != nullptr) return root->height;
    else return 0;
}
 
void calc_h(node *root) {
    root->height = max(get_h(root->right), get_h(root->left)) + 1;
}
 
node *leftRotate(node *&a) {
    node *b = a->right;
    a->right = b->left;
    b->left = a;
 
    calc_h(a);
    calc_h(b);
    return b;
}
 
node *rightRotate(node *&a) {
    node *b = a->left;
    a->left = b->right;
    b->right = a;
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
    } else {
        if (x < root->x) {
            root->left = mydelete(root->left, x);
        } else {
            if (x == root->x) {
                if ((root->left != nullptr) && (root->right != nullptr)) {
                    node *a = next(root, root->x);
                    root->x = a->x;
                    root->right = mydelete(root->right, a->x);
                } else {
                    if (root->left != nullptr) {
                        root = root->left;
                    } else {
                        if (root->right != nullptr) {
                            root = root->right;
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
 
int main() {
    string s;
    node *root = nullptr;
    int val;
    node* temp;
    while (cin >> s) {
        switch (s[0]) {
            case 'i':
                cin >> val;
                root = insert(root, val);
                break;
            case 'd':
                cin >> val;
                root = mydelete(root, val);
                break;
            case 'e':
                cin >> val;
                if (exists(root, val)) {
                    cout << "true\n";
                } else {
                    cout << "false\n";
                }
                break;
            case 'n':
                cin >> val;
                temp = next(root, val);
                if (temp == nullptr) {
                    cout << "none\n";
                } else {
                    cout << temp->x << '\n';
                }
                break;
            default:
                cin >> val;
                temp = prev(root, val);
                if (temp == nullptr) {
                    cout << "none\n";
                } else {
                    cout << temp->x << '\n';
                }
                break;
 
        }
    }
}
