#include <iostream>
#include <vector>
#include <algorithm>

#define BLANCO 0
#define GRIS 1
#define NEGRO 2

using namespace std;
using ll = long long;

vector<vector<ll>> vecinos; //Lista de adyacencia
ll N,M;
vector<ll> estado;
vector<ll> finish;


void dfs(ll v)
{
    estado[v] = GRIS;
    for (ll u : vecinos[v])
    {
        if (estado[u] == BLANCO)
        {
            dfs(u);
        }
    }
    finish.push_back(v);
    estado[v] = NEGRO;
}


int main(){
    cin >> N >> M;
    vecinos = vector<vector<ll>>(N+1);
    for(ll it=0;it<M;it++){
        ll i,j;
        cin >> i >> j;
        vecinos[i].push_back(j);
    }
    //Hago topological sort para ver de cual arranco:
    estado = vector<ll>(N+1,BLANCO);
    finish = vector<ll>();
    for(ll i=1;i<N+1;i++){
        if(estado[i]==BLANCO){
            dfs(i);
        }
    }
    //Finish al revés es topological sort
    vector<ll> res;
    estado = vector<ll>(N+1,BLANCO);
    for(ll i=finish.size()-1;i>=0;i--){
        if(estado[finish[i]]==BLANCO){
            dfs(finish[i]);
            res.push_back(finish[i]);
        }
    }
    //En res tengo los órdenes de mayor a menor, los imprimo al revés:
    //TODO: Ver bien eso, pero creo que al correr topological sort de 1 a N vale.
    cout << res.size() << endl;
    for(ll i=res.size()-1;i>=0;i--){
        cout << res[i] << " ";
    }
    return 0;
}