#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll inf = 1e18;

int n,m;
vector<tuple<ll,int,int>> E;

struct DSU{

    DSU(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }

    vector<int> padre;
    vector<int> rank;
};

void kruskal(){
    sort(E.begin(),E.end());
    ll res = 0;
    int aristas = 0;
    DSU dsu(n);
    for(auto [c,u,v] : E){
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            // agregar
            dsu.unite(u,v);
            aristas++;
            res += c;
        }
    }
    if(aristas == n-1) cout<<res<<endl;
    else cout<<"IMPOSSIBLE\n";
}

int main() {
    cin>>n>>m;
    for(int i = 0; i < m; i++){
        int u,v; ll c;
        cin>>u>>v>>c;
        u--, v--;
        E.push_back({c,u,v});
    }
    kruskal();
    return 0;
}