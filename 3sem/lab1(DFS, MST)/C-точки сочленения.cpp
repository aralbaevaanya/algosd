#include <iostream>
#include <vector>
#include <algorithm>
int const inf = INTMAX_MAX;

std::vector<std::vector<int>> grath;
std::vector<int> timein, color,ret,ans,used;
int t = 0;
//std::vector<int>ver;

void find_points(int v, int lastv){
    color[v] = 1;
    timein[v] = ++t;
    ret[v] = t;
    int next = 0;
    for (int i :grath[v]){ ;
        if (i == lastv){
            continue;
        }
        if (color[i] == 1 && ret[v] > timein[i]){
            ret[v] = timein[i];
        }
        if (color[i] == 0){
            find_points(i,v);
            if(ret[i] < ret[v]){
                ret[v] = ret[i];
            }
            if(ret[i] >= timein[v] && lastv != inf && used[v]==0){
              ans.push_back(v);
                used[v] =1;
            }
            next++;
        }
    }
    if(lastv == inf && next >1 && used[v] == 0){
        used[v] = 1;
        ans.push_back(v);
    }
}

/*
void dfs(int v){
    color[v] = 1;
    for(auto i: grath[v]){
        ver[i.first] = t;
        if (!color[i.first]){
            dfs(i.first);
        }
    }
}
*/

int main() {
    int n,m;
    std::cin >> n >> m;
    timein.assign(n,inf);
    ret.assign(n,inf);
    color.assign(n,0);
    grath.resize(n);
    used.assign(n,0);

    for (size_t i=0; i<m; ++i){
        int u,v;
        std::cin >> u >> v;
        --u;
        --v;
        grath[u].push_back(v);
        grath[v].push_back(u);
    }

    for (int i=0; i<n;++i){
        if (color[i] == 0) {
            find_points(i, inf);
        }
    }

    /*color.clear();
    ver.resize(n);
    t =0;
    color.assign(n,0);
    for (int i=0; i<n; ++i){
        if (!color[i]){
            t++;
            dfs(i);
        }
    }*/
    sort(ans.begin(), ans.end());
    std:: cout << ans.size() << '\n';
    for (int i:ans) {
        std::cout << i+1 << ' ';
    }


}