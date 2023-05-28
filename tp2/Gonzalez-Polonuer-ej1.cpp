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

vector<vector<ll>> aristas;
vector<vector<ll>> treeEdges;
vector<ll> estado;
vector<ll> padre;

vector<ll> backConExtremoSuperiorEn;
vector<ll> backConExtremoInferiorEn;

vector<ll> memo;

ll N, M;

ll elementos_CC;

void dfs(ll v)
{
    elementos_CC++;
    estado[v] = GRIS;
    for (ll u : aristas[v])
    {
        if (u == -1)
        {
            continue;
        }

        if (estado[u] == BLANCO)
        {
            padre[u] = v;
            treeEdges[v].push_back(u);
            dfs(u);
        }
        else if (u != padre[v] && estado[u] == GRIS)
        {
            backConExtremoInferiorEn[v]++;
            backConExtremoSuperiorEn[u]++;
        }
    }
    estado[v] = NEGRO;
}

ll cubren(ll v)
{
    if (memo[v] != -1)
        return memo[v];

    ll res = 0;
    res += backConExtremoInferiorEn[v];
    res -= backConExtremoSuperiorEn[v];
    for (ll hijo : treeEdges[v])
        if (hijo != padre[v]) // es necesario?
        {
            res += cubren(hijo);
        }
    memo[v] = res;
    return res;
}

int main()
{
    cin >> N >> M;

    aristas = vector<vector<ll>>(N + 1);
    treeEdges = vector<vector<ll>>(N + 1);
    estado = vector<ll>(N + 1, BLANCO);
    padre = vector<ll>(N + 1, -1);

    backConExtremoInferiorEn = vector<ll>(N + 1, 0);
    backConExtremoSuperiorEn = vector<ll>(N + 1, 0);

    memo = vector<ll>(N + 1, -1);

    for (ll i = 0; i < M; i++)
    {
        ll v, w;
        cin >> v;
        cin >> w;
        aristas[v].push_back(w);
        aristas[w].push_back(v);
    }

    // Voy a hacer dfs por todo el grafo, para armar el arbol
    // por mas que no sea conexo
    for (ll i = 0; i < estado.size(); i++)
    {
        if (estado[i] == BLANCO)
        {
            dfs(i);
        }
    }

    // Ahora me voy a guardar cuales aristas son puentes
    // Esto es O(n)
    vector<pair<ll, ll>> puentes;
    for (ll i = 1; i <= N; i++)
    {
        if (cubren(i) == 0 and padre[i] != -1)
        {
            puentes.push_back(make_pair(padre[i], i));
        }
    }

    // Ahora voy a poner -1 en los puentes para no pasar por ahi
    for (pair<ll, ll> arista : puentes)
    {
        ll u = arista.first;
        ll v = arista.second;

        for (ll i = 0; i < aristas[u].size(); i++)
        {
            if (aristas[u][i] == v)
            {
                aristas[u][i] = -1;
            }
        }

        for (ll i = 0; i < aristas[v].size(); i++)
        {
            if (aristas[v][i] == u)
            {
                aristas[v][i] = -1;
            }
        }
    }

    // Ahora reiniciamos el estado, porque el nuevo grafo ya no es conexo
    // y quiero ver que pasa.
    estado = vector<ll>(N + 1, BLANCO);

    // Vamos a contar cuantos elementos hay en las componentes conexas sin los vertices
    // Y en base a eso hacer la cuenta de elecciones posibles que me hacen ganar
    long long cant_elecciones_buenas = 0;
    for (ll i = 0; i < estado.size(); i++)
    {
        if (estado[i] == BLANCO)
        {
            elementos_CC = 0;
            dfs(i);
            if (elementos_CC != 1)
            {
                cant_elecciones_buenas += ((elementos_CC) * (elementos_CC - 1) / 2);
            }
        }
    }

    // Ahora veamos todas las elecciones que hay
    // Y cuales son las malas
    long long cant_elecciones_totales = N * (N - 1) / 2;
    long long cant_elecciones_malas = cant_elecciones_totales - cant_elecciones_buenas;

    // Finalmente, calculamos la probabilidad de perder
    double proba_de_perder = double(cant_elecciones_malas) / double(cant_elecciones_totales);

    cout << fixed << setprecision(5) << proba_de_perder;

    return 0;
}