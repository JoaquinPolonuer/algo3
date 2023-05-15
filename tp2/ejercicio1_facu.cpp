#include <iostream>
#include <vector>
#include <iomanip>      // std::setprecision
using namespace std;
typedef long long ll;

#define BLANCO 0
#define GRIS 1
#define NEGRO 2

ll N,M;
vector<vector<ll>> vecinos; //Lista de adyacencia
vector<tuple<ll,ll>> puentes;
vector<ll> backConExtremoSuperiorEn;
vector<ll> backConExtremoInferiorEn;
vector<vector<ll>> treeEdges;
vector<ll> estado;
vector<ll> padres;
ll elementos;

void dfs(ll v)
{
    estado[v] = GRIS;
    elementos++;
    for (ll u : vecinos[v])
    {
        if(u==-1){
            continue;
        }
        if (estado[u] == BLANCO)
        {
            padres[u] = v;
            treeEdges[v].push_back(u);
            dfs(u);
        }
        else if (u != padres[v] && estado[u] == GRIS)
        {
            if(v == 1){
                cout << "a";
            }
            backConExtremoInferiorEn[v]++;
            backConExtremoSuperiorEn[u]++;
        }
    }
    estado[v] = NEGRO;
}
vector<ll> memo;
ll cubren(ll v, ll p=-1){
    if (memo[v] != -1) return memo[v];
    ll res=0;
    res += backConExtremoInferiorEn[v];
    res -= backConExtremoSuperiorEn[v];
    for(ll hijo : treeEdges[v]){
        if(hijo != p){
            res += cubren(hijo, v);
        }
    }
    return memo[v]=res;
}

double probaDePerder(){
    //Obs: combinatorio(N,2) = N(N-1)/2 Para cualquier N. Usamos esto ya que solo necesitamos cuando r=2.
    ll cantDeJugar = N*(N-1)/2;
    ll cantDeCC = 0;
    vector<ll> verticesEnCC = vector<ll>();
    estado = vector<ll>(N+1,0);
    for(ll i=1;i<N+1;i++){
        if (estado[i]==0){
            elementos=0;
            dfs(i);
            cantDeCC++;
            verticesEnCC.push_back(elementos);
        }
    }
    ll cantDeGanar = 0;
    for(ll c : verticesEnCC){
        ll aux;
        if(c>=2){
            aux = c*(c-1)/2;
        }else{
            aux=0;
        }
        cantDeGanar+=aux;
    }
    ll cantDePerder = cantDeJugar-cantDeGanar;
    double res = double(cantDePerder)/double(cantDeJugar);
    return res;
}

int main(){
    cin >> N;cin >> M;
    vecinos = vector<vector<ll>>(N+1,vector<ll>());
    for(ll i=0;i<M;i++){
        ll v, w;
        cin >> v; cin >> w;
        vecinos[v].push_back(w);
        vecinos[w].push_back(v);
    }

    //Buscar los puentes:
    backConExtremoInferiorEn = vector<ll>(N+1,0);
    backConExtremoSuperiorEn = vector<ll>(N+1,0);
    estado = vector<ll>(N+1,0);
    padres = vector<ll>(N+1,-1);
    treeEdges = vector<vector<ll>>(N+1,vector<ll>());
    for(ll i=1;i<N+1;i++){
        if (estado[i]==0){
            dfs(i); //Asegurarnos que buscamos en to do el grafo por si no es conexo
        }
    }
    memo = vector<ll>(N+1,-1);
    puentes = vector<tuple<ll,ll>>();
    for(ll i=1;i<N+1;i++){
        if(cubren(i)==0){
            if (padres[i]>0) {
                puentes.push_back(make_tuple(i,padres[i]));
            }
        }
    }
    //Elimino las aristas puentes
    //En lugar de eliminar las aristas le pongo -1 y en DFS me fijo que los vecinos no sean -1
    for(auto arista : puentes){
        ll u = get<0>(arista);
        ll v = get<1>(arista);
        for (ll i = 0;i< vecinos[u].size();i++) {
            if (vecinos[u][i] == v) {
                vecinos[u][i]=-1;
            }
        }
        for (ll i = 0;i< vecinos[v].size();i++) {
            if (vecinos[v][i] == u) {
                vecinos[v][i]=-1;
            }
        }
    }

    double res = probaDePerder();
    cout << fixed << setprecision(5) << res;
    return 0;
}