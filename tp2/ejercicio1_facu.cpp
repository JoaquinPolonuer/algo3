#include <iostream>
#include <vector>
#include <iomanip>      // std::setprecision
using namespace std;
typedef long long ll;

#define BLANCO 0
#define GRIS 1
#define NEGRO 2

int N,M;
vector<vector<int>> vecinos; //Lista de adyacencia
vector<tuple<int,int>> puentes;
vector<int> backConExtremoSuperiorEn;
vector<int> backConExtremoInferiorEn;
vector<vector<int>> treeEdges;
vector<int> estado;
vector<int> padres;
int elementos;

void dfs(int v)
{
    estado[v] = GRIS;
    elementos++;
    for (int u : vecinos[v])
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
vector<int> memo;

int cubren(int v, int p=-1){ //TODO: Falta aplicarle programación dinámica
    if (memo[v] != -1) return memo[v];
    int res=0;
    res += backConExtremoInferiorEn[v];
    res -= backConExtremoSuperiorEn[v];
    for(int hijo : treeEdges[v]){
        if(hijo != p){
            res += cubren(hijo, v);
        }
    }
    return memo[v]=res;
}

double probaDePerder(){
    //Obs: combinatorio(N,2) = N(N-1)/2 Para cualquier N. Usamos esto ya que solo necesitamos cuando r=2.
    int cantDeJugar = N*(N-1)/2;
    int cantDeCC = 0;
    vector<int> verticesEnCC = vector<int>();
    estado = vector<int>(N+1,0);
    for(int i=1;i<N+1;i++){
        if (estado[i]==0){
            elementos=0;
            dfs(i);
            cantDeCC++;
            verticesEnCC.push_back(elementos);
        }
    }
    int cantDeGanar = 0;
    for(int c : verticesEnCC){
        int aux;
        if(c>=2){
            aux = c*(c-1)/2;
        }else{
            aux=0;
        }
        cantDeGanar+=aux;
    }
    int cantDePerder = cantDeJugar-cantDeGanar;
    double res = double(cantDePerder)/double(cantDeJugar);
    return res;
}

int main(){
    cin >> N;cin >> M;
    vecinos = vector<vector<int>>(N+1,vector<int>());
    for(int i=0;i<M;i++){
        int v, w;
        cin >> v; cin >> w;
        vecinos[v].push_back(w);
        vecinos[w].push_back(v);
    }
    //Buscar los puentes:
    backConExtremoInferiorEn = vector<int>(N+1,0);
    backConExtremoSuperiorEn = vector<int>(N+1,0);
    estado = vector<int>(N+1,0);
    padres = vector<int>(N+1,-1);
    treeEdges = vector<vector<int>>(N+1,vector<int>());
    for(int i=1;i<N+1;i++){
        if (estado[i]==0){
            dfs(i); //Asegurarnos que buscamos en todo el grafo por si no es conexo
        }
    }
    memo = vector<int>(N+1,-1);
    puentes = vector<tuple<int,int>>();
    for(int i=1;i<N+1;i++){
        if(cubren(i)==0){
            if (padres[i]>0) {
                puentes.push_back(make_tuple(i,padres[i]));
            }
        }
    }
    //Elimino las aristas puentes
    //TODO: En lugar de eliminar las aristas le pongo -1 y en DFS me fijo que los vecinos no sean -1
    for(auto arista : puentes){
        int u = get<0>(arista);
        int v = get<1>(arista);
        for (int i = 0;i< vecinos[u].size();i++) {
            if (vecinos[u][i] == v) {
                vecinos[u][i]=-1;
            }
        }
        for (int i = 0;i< vecinos[v].size();i++) {
            if (vecinos[v][i] == u) {
                vecinos[v][i]=-1;
            }
        }
    }

    double res = probaDePerder();
    cout << fixed;
    cout << setprecision(5) << res <<endl;
    return 0;
}