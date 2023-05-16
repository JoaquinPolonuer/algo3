#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll inf = 1e18;

int n,m;
vector<vector<pair<ll,int>>> g;

void prim_m_lg_n(){
    ll res = 0;
    vector<bool> es_rojo(n,false); es_rojo[0] = true;
    set<pair<ll,int>> s; //pares (costo, extremo azul)
    for(auto [c,u] : g[0])
        s.insert({c,u});

    for(int it = 0; it < n-1; it++){
        if(s.empty()){
            cout<<"IMPOSSIBLE\n";
            return;
        }
        //meter violeta mas barata (usando info de s)
        auto [c,v] = *s.begin();
        res += c;

        //pintar de rojo el extremo azul
        es_rojo[v] = true;

        //actualizar info de s
        for(auto [c,u] : g[v]){
            if(es_rojo[u]) s.erase({c,v});
            else s.insert({c,u});
        }
    }
    cout<<res<<endl;
}

int main() {
    cin>>n>>m;
    g = vector<vector<pair<ll,int>>>(n);
    for(int i = 0; i < m; i++){
        int u,v; ll c;
        cin>>u>>v>>c;
        u--, v--;
        g[v].push_back({c,u});
        g[u].push_back({c,v});
    }
    prim_m_lg_n();
    return 0;
}