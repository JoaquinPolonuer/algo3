#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <algorithm>
#include <queue>
#include <chrono>
#include <fstream>

using namespace std;

using ll = long long;
const ll inf = 1e18;

int C;
ll N, M, K, s, t;
ll u, v, c;

vector<vector<pair<ll, ll>>> g_aristas;
vector<vector<pair<ll, ll>>> gt_aristas;
vector<tuple<ll, ll, ll>> aristas_extra;

vector<ll> dijkstra_logn(vector<vector<pair<ll, ll>>> &g, ll s)
{
    vector<ll> d = vector<ll>(g.size(), inf);
    vector<bool> processed = vector<bool>(g.size(), false);

    queue<pair<ll, ll>> q;

    d[s] = 0;
    q.push({0, s});

    for(int i = 0; i < N; i++){
        q.push({inf, i}); //Esto nos asegura que va a visitar todos los nodos
    }

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

vector<ll> dijkstra_cuadratico(vector<vector<pair<ll, ll>>> &g, ll s)
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

pair<double, double> medir_instancia_denso(int n)
{
    srand(time(NULL));

    N = n;
    M = n * (n - 1);
    K = rand() % (300);

    g_aristas = vector<vector<pair<ll, ll>>>(N);
    gt_aristas = vector<vector<pair<ll, ll>>>(N);
    aristas_extra = vector<tuple<ll, ll, ll>>();

    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            int wi = rand() % (1000);
            g_aristas[i].push_back({j, wi});
            gt_aristas[j].push_back({i, wi});
        }
    }
    s = 0;
    t = N - 1;

    auto start = chrono::high_resolution_clock::now();
    dijkstra_cuadratico(g_aristas, s);
    dijkstra_cuadratico(gt_aristas, t);
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> denso_diff_cuadratico = stop - start;

    start = chrono::high_resolution_clock::now();
    dijkstra_logn(g_aristas, s);
    dijkstra_logn(gt_aristas, t);
    stop = chrono::high_resolution_clock::now();

    chrono::duration<double> denso_diff_logn = stop - start;

    return make_pair(denso_diff_cuadratico.count(), denso_diff_logn.count());
}

pair<double, double> medir_instancia_ralo(int n)
{
    srand(time(NULL));

    N = n;
    M = n;
    K = rand() % (300);

    g_aristas = vector<vector<pair<ll, ll>>>(N);
    gt_aristas = vector<vector<pair<ll, ll>>>(N);
    aristas_extra = vector<tuple<ll, ll, ll>>();

    for (int i = 0; i < N; i++)
    {
        for(int it = 0; it < 3; it++){
            int xi, wi;
            xi = rand() % (N);
            wi = rand() % (1000);
            // agregar al grafo
            g_aristas[i].push_back({xi, wi});
            gt_aristas[xi].push_back({i, wi});
        }
    }
    //Agrego camino de S a T para que siempre haya camino 3
    for(int arista = 0; arista < N; arista++){
        int peso = rand() % (1000);
        g_aristas[arista].push_back({arista+1, peso});
        gt_aristas[arista+1].push_back({arista, peso});
    }

    s = 0;
    t = N - 1;

    auto start = chrono::high_resolution_clock::now();
    dijkstra_cuadratico(g_aristas, s);
    dijkstra_cuadratico(gt_aristas, t);
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> ralo_diff_cuadratico = stop - start;

    start = chrono::high_resolution_clock::now();
    dijkstra_logn(g_aristas, s);
    dijkstra_logn(gt_aristas, t);
    stop = chrono::high_resolution_clock::now();

    chrono::duration<double> ralo_diff_logn = stop - start;

    return make_pair(ralo_diff_cuadratico.count(), ralo_diff_logn.count());
}

int main()
{
    int repeat = 5;
    ofstream output_file;
    
    output_file.open("runtime.csv");
    output_file << "n,denso_time_logn,ralo_time_logn,denso_time_cuadratico,ralo_time_cuadratico" << endl;

    // Itero por la cantidad de casos de prueba
    for (int n = 2; n < 10000; n += 500)
    {
        double ralo_cuadratico = 0;
        double ralo_logn = 0;
        double denso_cuadratico = 0;
        double denso_logn = 0;

        for (int it = 0; it < repeat; it++)
        {
            auto medicion_ralo = medir_instancia_ralo(n);
            auto medicion_denso = medir_instancia_denso(n);

            ralo_cuadratico += medicion_ralo.first;
            ralo_logn += medicion_ralo.second;

            denso_cuadratico += medicion_denso.first;
            denso_logn += medicion_denso.second;
        }

        ralo_cuadratico /= repeat;
        ralo_logn /= repeat;
        denso_cuadratico /= repeat;
        denso_logn /= repeat;

        output_file << n << "," << denso_logn << "," << ralo_logn << "," << denso_cuadratico << "," << ralo_cuadratico << endl;
        cout << n << endl;
    }

    return 0;
}