#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <iomanip> // std::setprecision

using namespace std;
typedef long long ll;

#define BLANCO 0
#define GRIS 1
#define NEGRO 2

ll N, M;
ll u, v;

vector<vector<ll>> aristas;
vector<ll> estado;

vector<ll> finish;

void dfs(ll v)
{
    estado[v] = GRIS;
    for (ll u : aristas[v])
    {
        if (estado[u] == BLANCO)
        {
            dfs(u);
        }
    }
    finish.push_back(v);
    estado[v] = NEGRO;
}

int main()
{
    cin >> N >> M;
    aristas = vector<vector<ll>>(N + 1);

    // Ingreso las aristas a mi representacion del grafo
    // como listas de adyacencia
    for (ll i = 0; i < M; i++)
    {
        cin >> u >> v;
        aristas[u].push_back(v);
    }

    // Voy a hacer dfs por todo el grafo
    // De esta forma, voy a ir armando mi lista de finish
    // para "topological sort". 
    // (En realidad se permiten ciclos en el grafo, pero 
    // definimos el orden como si la ultima arista del ciclo 
    // no existiera)
    estado = vector<ll>(N + 1, BLANCO);
    finish = vector<ll>();
    for (ll i = 1; i < estado.size(); i++)
    {
        if (estado[i] == BLANCO)
        {
            dfs(i);
        }
    }

    // Ahora voy a querer volver a recorrer mi grafo pero en
    // el orden definido previamente, a ver cuales voy tirando
    vector<ll> cuales;
    estado = vector<ll>(N + 1, BLANCO);
    for (ll i = finish.size() - 1; i >= 0; i--)
    {
        ll nodo = finish[i];
        if (estado[nodo] == BLANCO)
        {
            dfs(nodo);
            cuales.push_back(nodo);
        }
    }

    // Imprimo cuales al reves porque el orden generado me devuelve
    // antes los vertices mas grandes
    cout << cuales.size() << endl;
    for (ll i = cuales.size() - 1; i >= 0; i--)
    {
        cout << cuales[i] << " ";
    }

    return 0;
}