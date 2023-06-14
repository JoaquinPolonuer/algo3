#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <algorithm>
#include <queue>
#include <chrono>

using namespace std;

using ll = long long;
const ll inf = 1e18;

int C;
ll N, M, K, s, t;
ll u, v, c;

vector<vector<pair<ll, ll>>> g_aristas;
vector<vector<pair<ll, ll>>> gt_aristas;
vector<tuple<ll, ll, ll>> aristas_extra;

vector<ll> dijkstra_ralo(vector<vector<pair<ll, ll>>> &g, ll s)
{
    vector<ll> d = vector<ll>(g.size(), inf);
    vector<bool> processed = vector<bool>(g.size(), false);

    queue<pair<ll, ll>> q;

    d[s] = 0;
    q.push({0, s});

    while (!q.empty())
    {
        ll u = q.front().second;
        q.pop();

        if (processed[u])
            continue;

        processed[u] = true;
        for (auto e : g[u])
        {
            ll v = e.first;
            ll c = e.second;

            if (d[u] + c < d[v])
            {
                d[v] = d[u] + c;
                q.push({-d[v], v});
            }
        }
    }

    return d;
}

vector<ll> dijkstra_denso(vector<vector<pair<ll, ll>>> &g, ll s)
{
    vector<ll> d = vector<ll>(N, inf);
    vector<bool> processed = vector<bool>(N, false);

    d[s] = 0;

    for (int it = 0; it < N; it++)
    {
        ll d_mas_cercano = inf;
        ll u;

        for (int i = 0; i < N; i++)
        {
            if (!processed[i] && d[i] < d_mas_cercano)
            {
                u = i;
                d_mas_cercano = d[i];
            }
        }

        processed[u] = true;

        for (auto e : g[u])
        {
            ll v = e.first;
            ll c = e.second;

            if (d[u] + c < d[v])
            {
                d[v] = d[u] + c;                
            }
        }
    }

    return d;
}

void construir_instancia_ralo(int n)
{
    srand(time(NULL));

    N = n;
    M = n;
    K = rand() % (300);

    for(int i = 0;i < M; i++){
        int xi, yi, wi;
        xi = rand() % (N);
        yi = rand() % (N);
        wi = rand() % (1000);
        //agregar al grafo

    }
    
}

int main()
{

    cin >> C;

    // Itero por la cantidad de casos de prueba
    for (int caso = 0; caso < C; caso++)
    {
        // recibo el input
        // para no tener problema con el indexado, voy a
        // restarle 1 a todos los vertices, de manera que
        // vayan de 0 a n-1
        cin >> N >> M >> K >> s >> t;
        s--, t--;

        g_aristas = vector<vector<pair<ll, ll>>>(N);
        gt_aristas = vector<vector<pair<ll, ll>>>(N);
        aristas_extra = vector<tuple<ll, ll, ll>>();

        // para cada nodo u calculo
        // d(s, u) y d(u, t)
        vector<ll> d_d_s = dijkstra(g_aristas, s);
        vector<ll> d_a_t = dijkstra(gt_aristas, t);

        // el camino minimo antes de hacer cualquier
        // cambio es el que encuentra dijkstra
        ll cm = d_d_s[t];
        for (auto e : aristas_extra)
        {
            tie(u, v, c) = e;

            // si la distancia a t disminuye al usar mi nueva
            // arista e, cambio la longitud del camino minimo
            if (d_d_s[u] + c + d_a_t[v] < cm)
            {
                cm = d_d_s[u] + c + d_a_t[v];
            }

            if (d_d_s[v] + c + d_a_t[u] < cm)
            {
                cm = d_d_s[v] + c + d_a_t[u];
            }
        }
        if (cm != inf)
        {
            cout << cm << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }

    return 0;
}