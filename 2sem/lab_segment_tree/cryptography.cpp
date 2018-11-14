#include <iostream>
 
using namespace std;
 
int r;
 
struct matrix {
    long long a = 1, b = 0, c = 0, d = 1;
};
 
matrix one{1, 0, 0, 1,};
 
matrix arr[500005];
 
matrix mul(matrix left, matrix right) {
    return {(left.a * right.a + left.b * right.c) % r,
            (left.a * right.b + left.b * right.d) % r,
            (left.c * right.a + left.d * right.c) % r,
            (left.c * right.b + left.d * right.d) % r
    };
}
 
struct node {
    matrix m;
    int l, r;
    node *leftChaild = nullptr;
    node *rightChaild = nullptr;
 
    node(int L, int R) {
        l = L;
        r = R;
        if (l == r) {
            m = arr[l];
        } else {
            int mid = l + (r - l) / 2;
            leftChaild = new node(l, mid);
            rightChaild = new node(mid + 1, r);
            m = mul(leftChaild->m, rightChaild->m);
        }
    };
 
};
 
 
matrix search(node *root, int x, int y) {
    if (x <= root->l && y >= root->r) {
        return root->m;
    }
 
    if (y <= root->leftChaild->r) {
        return search(root->leftChaild, x, y);
    }
 
    if (x >= root->rightChaild->l) {
        return search(root->rightChaild, x, y);
    }
 
    return mul(search(root->leftChaild, x, y), search(root->rightChaild, x, y));
}
 
int main() {
    cin.tie();
    ios_base::sync_with_stdio(0);
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);
    int n, m;
    cin >> r >> n >> m;
    int k = 0;
    while (n > (1 << k)) {
        k++;
    }
 
    for (int i = 1; i <= n; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        arr[i] = {a, b, c, d};
    }
 
    node *root = new node(1, (1 << k));
 
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        matrix res = search(root, x, y);
        cout << res.a << ' ' << res.b << '\n' << res.c << ' ' << res.d << '\n';
    }
 
}
