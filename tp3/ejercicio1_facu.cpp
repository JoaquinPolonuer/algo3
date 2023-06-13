#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;
const int inf = 1e9;


int N,M,K,S,T;
vector<tuple<int,int,int>> caintes; //No lo estoy usando
vector<tuple<int,int,int>> caintes_propuestas;
vector<int> distancia;
vector<int> distancia_T;
vector<int> procesados;
vector<int> procesados_T;
vector<vector<pair<int,int>>> vecinos;
vector<vector<pair<int,int>>> vecinos_inv;


void dijkstra()
{
    //Calcular la distancia de S a todos los nodos

    queue<pair<int,int>>cola = queue<pair<int,int>>();

    distancia[S] = 0;
    cola.push({0,S});

    while(!cola.empty())
    {
        int nodo = (cola.front()).second;
        cola.pop();
        if(procesados[nodo]==1) continue;
        procesados[nodo] = 1;
        for(auto u : vecinos[nodo])
        {
            int b = u.first;
            int w = u.second;
            if(distancia[nodo]+w<distancia[b])
            {
                distancia[b] = distancia[nodo]+w;
                cola.push({-distancia[b],b});
            }
        }
    }
}

void dijkstra_T()
{
    //Calcular la distancia de todos los nodos a T
    //Usando el grafo inverso
    queue<pair<int,int>>cola = queue<pair<int,int>>();

    distancia_T[T] = 0;
    cola.push({0,T});
    while(!cola.empty())
    {
        int nodo = (cola.front()).second;
        cola.pop();
        if(procesados_T[nodo]==1) continue;
        procesados_T[nodo] = 1;
        for(auto u : vecinos_inv[nodo])
        {
            int b = u.first;
            int w = u.second;
            if(distancia_T[nodo]+w<distancia_T[b])
            {
                distancia_T[b] = distancia_T[nodo]+w;
                cola.push({-distancia_T[b],b});
            }
        }
    }
}

int menor_distancia(){
    dijkstra();
    dijkstra_T();
    int min = distancia[T];
    for(auto e : caintes_propuestas)
    {
        int u,v,l;
        tie(u,v,l) = e;

        // Hay que chequear para ambos lados porque son calles bidireccionales

        if(distancia[u]+l+distancia_T[v] < min)
        {
            min = distancia[u]+l+distancia_T[v];
        }
        if (distancia[v]+l+distancia_T[u] < min)
        {
            min = distancia[v]+l+distancia_T[u];
        }
    }
    return min;
}

int main(){
    int C;
    cin >> C;
    for(int it=0;it<C;it++)
    {
        cin >> N >> M >> K >> S >> T;
        caintes = vector<tuple<int,int,int>>();
        caintes_propuestas = vector<tuple<int,int,int>>();

        distancia = vector<int>(N+1,inf);
        distancia_T = vector<int>(N+1,inf);

        procesados = vector<int>(N+1,0);
        procesados_T = vector<int>(N+1,0);

        vecinos = vector<vector<pair<int,int>>>(N+1,vector<pair<int,int>>());
        vecinos_inv = vector<vector<pair<int,int>>>(N+1,vector<pair<int,int>>());

        for(int i = 0; i < M ;i++)
        {
            int di,ci,li;
            cin >> di >> ci >> li;
            caintes.emplace_back(di,ci,li);
            vecinos[di].emplace_back(ci,li);
            vecinos_inv[ci].emplace_back(di,li);
        }
        for(int j = 0; j < K ;j++)
        {
            int uj,vj,qj;
            cin >> uj >> vj >> qj;
            caintes_propuestas.emplace_back(uj,vj,qj);
        }
        int res = menor_distancia();
        if (res < inf){
            cout << res << endl; //Se puede llegar de S a T
        }else{
            cout << -1 << endl;  //No se puede llegar de S a T
        }

    }
    return 0;
}