#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <iomanip>      // std::setprecision
using namespace std;

vector<tuple<int,int>> g;
int N,M;

int fact(int n){
    if(n==0) return 1;
    int res = 1;
    for (int i = 2; i <= n; i++)
        res = res * i;
    return res;
}
int nCr(int n, int r){
    return fact(n) / (fact(r) * fact(n - r));
}


vector<int> backConExtremoSuperiorEn(N,0);
vector<int> backConExtremoInferiorEn(N,0);
vector<vector<int>> vecinos;
vector<vector<int>> treeEdges(N,vector<int>());
vector<int> estado(N,0);

void dfs(int v, int p=-1){
    estado[v]=1; //empecé a ver
    for(int u : vecinos[v]){
        if(estado[u]==0){
            treeEdges[v].push_back(u);
            dfs(u,v);
        }else if(u != p){
            backConExtremoInferiorEn[v]++;
            backConExtremoSuperiorEn[u]++;
        }
    }
    estado[v]=2;
}

int cubren(int v, int p=-1){
    int res=0;
    res += backConExtremoInferiorEn[v];
    res -= backConExtremoSuperiorEn[v];
    for(int hijo : treeEdges[v]){
        if(hijo != p){
            res += cubren(hijo, v);
        }
    }
    return res;
}

vector<vector<int>> memo(N,vector<int>(N,-1));
bool esPuente(int i,int j);

bool ganasDeIaJ(int i, int j){
    if(memo[i][j]!=-1) return memo[i][j];
    for(int u : vecinos[i]){
        if((not esPuente(i,u)) and ganasDeIaJ(u,j)){
            return memo[i][j]=true;
        }
    }
    return memo[i][j]=false;
}


/*
 * Para i, ver sus vecinos y devolver true si no es punete y se llega de i a j
 * Obs: precalcular aristas puentes para ver en O(1)
 * Idea: en la matriz de adyacencia borrar los puentes
 * Memo iniciliarlo en true en las aristas que no son puente y false las que sí
 */



double probaDePerder(){
    int cantDeJugar = nCr(N,2); //uso nCr para la cant de formas de elegir 2 de los N nodos.
    int cantDePerder = 0;  //Para cada par de nodos, si hay un puente entre el camino mínimo entre ellos sumo 1
    for(int i=0;i<N;i++){
        for(int j=0;j<N;i++){
            if(j==i) {
                continue;
            }
            if (ganasDeIaJ(i,j)){
                continue;
            }
            cantDePerder++;
        }
    }
    double res = double(cantDePerder)/double(cantDeJugar);
    return res;
}


int main(){
    cin >> N;cin >> M;
    for(int i=0;i<M;i++){
        int v, w;
        cin >> v; cin >> w;
        tuple<int,int> eje = make_tuple(v,w);
        g.push_back(eje); //Inicializar matriz de adyacencia y lista de adyacencia
    }
    double res = probaDePerder();
    cout << fixed;
    cout << setprecision(5) << res << '\n';
    return 0;
}