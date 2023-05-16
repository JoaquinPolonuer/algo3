#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll inf = 1e18;

int n,m;
vector<vector<ll>> g;

void prim_n2(){
    ll res = 0;
    vector<bool> es_rojo(n,false); es_rojo[0] = true;
    vector<int> rojo_mas_cercano(n,0);
    for(int it = 0; it < n-1; it++){
        //agregar a la arista violeta mas barata
        int agrego = 0;
        while(es_rojo[agrego]) agrego++;
        for(int v = agrego+1; v < n; v++)
            if(!es_rojo[v] and g[v][rojo_mas_cercano[v]] < g[agrego][rojo_mas_cercano[agrego]])
                agrego = v;

        //pintar de rojo su extremo azul
        es_rojo[agrego] = true;

        //actualizar info de rojo_mas_cercano
        for(int v = 0; v < n; v++)
            if(!es_rojo[v] and g[v][agrego] < g[v][rojo_mas_cercano[v]]) rojo_mas_cercano[v] = agrego;

        if(g[agrego][rojo_mas_cercano[agrego]] == inf) {
            cout<<"IMPOSSIBLE\n";
            return;
        }
        res += g[agrego][rojo_mas_cercano[agrego]];
    }
    cout<<res<<endl;
}

int main() {
    cin>>n>>m;
    g = vector<vector<ll>>(n,vector<ll>(n,inf));
    for(int i = 0; i < m; i++){
        int u,v; ll c;
        cin>>u>>v>>c;
        u--, v--;
        g[v][u] = g[u][v] = c;
    }
    prim_n2();
    return 0;
}