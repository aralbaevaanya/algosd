#include <iostream>
using namespace std;
struct node{
    int l,r;
    int64_t sum =0;
    node *left = nullptr, *right = nullptr;
    node(int L,int R){
        l = L;
        r = R;
    }
 
};
 
int64_t mysum(node *root, int i, int j) {
    if (root->l >= i && root->r <= j)  {
        return root->sum;
    }
    int64_t a, b;
    if ((i <= (root->l + (root->r - root->l) / 2)) && root->left != nullptr) {
        a = mysum(root->left, i, j);
    } else {
        a = 0;
    }
    if ((j > root->l + (root->r - root->l) / 2) && root->right != nullptr) {
        b = mysum(root->right, i, j);
    } else {
        b = 0;
    }
    return a+b;
}
 
bool myadd(node *root, int i, int s) {
    if (root->l == root->r)  {
       if (root->sum == 0){
           root->sum += s;
           return true;
       }else{
           return false;
       }
    }
    if (i <= (root->l + (root->r - root->l) / 2)){
        if (root->left == nullptr){
            root->left = new node(root->l,(root->l + (root->r - root->l) / 2));
        }
        if (myadd(root->left,i,s)){
            root->sum+=s;
            return true;
        }else{
            return false;
        }
    }
    if (root->right == nullptr){
        root->right = new node((root->l + (root->r - root->l) / 2) + 1, root->r);
    }
    if (myadd(root->right,i,s)){
        root->sum+=s;
        return true;
    }else{
        return false;
    }
}
 
 
int main() {
  int n;
  cin >> n;
  char c;
  const int N = 1000000000;
  int64_t lastq = 0;
  node *root = new node(0, (1<<30));
   
  for (int i=0; i<n; i++){
      cin >> c;
      if (c == '?'){
          int l,r;
          cin >> l >> r;
          lastq = mysum(root,l,r);
          cout << lastq << '\n';
      }else{
          int s;
          cin >> s;
          myadd(root, (s + lastq)%N, (s+lastq)%N );
          lastq = 0;
      }
 
  }
}
