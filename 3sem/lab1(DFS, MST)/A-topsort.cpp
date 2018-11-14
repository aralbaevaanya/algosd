#include <iostream>
#include <vector>
#include <set>
using namespace std;
vector<int8_t> typebool;
vector<set<int>> cnt;
vector<int> res;

int dfs(int v){
    typebool[v] = 1;
    for(int u:cnt[v]){
        if (typebool[u] == 0){
           if(dfs(u) == 1) return 1;
        }else{
            if (typebool[u] == 1) {
                cout << -1;
                return 1;
            }
        }
    }
    res.push_back(v);
    typebool[v] = -1;
    return 0;
}


int main() {
   int m,n,u,v;
   cin >> n >> m;
   typebool.assign(n,0);
   cnt.assign(n,*new set<int>());

   for (int i=0; i<m; ++i){
       cin >> u >> v;
       u--; v--;
       cnt[u].insert(v);
   }
   for(int i=0; i<n; ++i){
       if (typebool[i] == 0){
           if(dfs(i) == 1){
               return 0;
           }
       }
   }
   for (int i=res.size()-1; i>=0; --i){
       cout << res[i] + 1<<' ';
   }


}