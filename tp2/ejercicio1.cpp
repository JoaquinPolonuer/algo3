#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <iomanip>      // std::setprecision
using namespace std;


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

vector<vector<int>> matrizDeAdy;
int N,M;

vector<int> backConExtremoSuperiorEn;
vector<int> backConExtremoInferiorEn;
vector<vector<int>> treeEdges;
vector<int> estado;
vector<int> padres;

vector<int> vecinosDe(int v){
    vector<int> res;
    for(int i=1;i<N+1;i++){
        if(matrizDeAdy[v][i]>0){
            res.push_back(i);
        }
    }
    return res;
}

void dfs(int v, int p=-1){
    estado[v]=1; //empecé a ver
    for(int u : vecinosDe(v)){
        if(estado[u]==0){
            treeEdges[v].push_back(u);
            padres[u]=v;
            dfs(u,v);
        }else if(u != p and p!=-1){             //ESTO SE ROMPE ACA: Algunas backedges las cuenta dos veces (como superior e inferior a la vez)
                                                //Y entonces despues marca puentes que no existen. (En el test case la backedge (5,7) la marca dos veces)
                                                //Y termina decidiendo que (5,6) es puente.
            backConExtremoInferiorEn[v]++;
            backConExtremoSuperiorEn[u]++;
        }
    }
    estado[v]=2;
}
int cubren(int v, int p=-1){ //Falta aplicarle programación dinámica
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

vector<vector<int>> memo;
bool esPuente(int i,int j){
    return matrizDeAdy[i][j]==2;
}

bool ganasDeIaJ(int i, int j){
    if(memo[i][j]!=-1) return memo[i][j]==1;
    for(int u : vecinosDe(i)){              //EXPLOTA ACA PORQUE ITERA INFINITAMENTE AL IR DEL 1 AL 2 Y DEL 2 AL 1
        if((not esPuente(i,u)) and ganasDeIaJ(u,j)){
            return memo[i][j]=1;
        }
    }
    return memo[i][j]=0;
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
    for(int i=1;i<N+1;i++){
        for(int j=i+1;j<N+1;j++){
            if(j==i or j<i) { //No me fijo i=j ni los menores a i (porque ya los vi antes)
                continue;
            }
            /*
            estado = vector<int>(N+1,0);
            dfs(i);
            if (estado[j]==2){
                continue;
            }
            */
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
    matrizDeAdy = vector<vector<int>>(N+1,vector<int>(N+1,0));
    for(int i=0;i<M;i++){
        int v, w;
        cin >> v; cin >> w;
        matrizDeAdy[v][w]=1;
        matrizDeAdy[w][v]=1;
    }
    //Buscar los puentes:
    memo = vector<vector<int>>(N+1,vector<int>(N+1,-1));
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
    for(int i=1;i<N+1;i++){
        if(cubren(i)==0){
            if (padres[i]>0) {
                matrizDeAdy[i][padres[i]] = 2;
                matrizDeAdy[padres[i]][i] = 2;
                memo[i][padres[i]] = 0;
                memo[padres[i]][i] = 0;
            }
        }
    }
    double res = probaDePerder();
    cout << fixed;
    cout << setprecision(5) << res << '\n';
    return 0;
}