#include <iostream>
#include <vector>
#include <algorithm>

int const inf = INTMAX_MAX;

struct way{
    int p;
    int num;
    way(int v, int n):p(v),num(n){
    }
};

std::vector<std::vector<way>> grath;
std::vector<int> timein, color,ret;
int t = 0;
std::vector<int>ans;

void find_briges(int v, int lastv){
    color[v] = 1;
    timein[v] = ++t;
    ret[v] = t;
    for (int j = 0; j < grath[v].size(); ++j){
        int i =grath[v][j].p;
        if (i == lastv){
            continue;
        }
        if (color[i] == 1 && ret[v] > timein[i]){
            ret[v] = timein[i];
        }
        if (color[i] == 0){
            find_briges(i,v);
            if(ret[i] < ret[v]){
                ret[v] = ret[i];
            }
            if(ret[i] > timein[v]){
                ans.push_back(grath[v][j].num);
            }
        }
    }
}

int main() {
    int n,m;
    std::cin >> n >> m;
    timein.assign(n,inf);
    ret.assign(n,inf);
    color.assign(n,0);
    grath.assign(n,std::vector<way>());

    for (size_t i=0; i<m; ++i){
        int u,v;
        std::cin >> u >> v;
        --u;
        --v;
        grath[u].emplace_back(v,i+1);
        grath[v].emplace_back(u,i+1);
    }

    for (int i=0; i<n;++i){
        if (color[i] ==0){
            find_briges(i, inf);
        }
    }

    std:: sort(ans.begin(), ans.end());
    std:: cout << ans.size()<<'\n';
    for (int p:ans){
        std:: cout << p << ' ';
    }


}