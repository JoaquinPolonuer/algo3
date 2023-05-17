#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <iomanip> // std::setprecision
#include <algorithm>

using namespace std;
using ll = long long;
const ll inf = 1e18;

ll C, N, R, W, U, V;

vector<tuple<double, ll, ll>> E;

vector<pair<ll, ll>> oficinas;
pair<ll, ll> oficina;
ll xi, yi;

double dist(pair<ll, ll> p1, pair<ll, ll> p2)
{
    double dist = sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
    return dist;
}

struct DSU
{

    DSU(ll n)
    {
        padre = rank = vector<ll>(n);
        for (ll v = 0; v < n; v++)
            padre[v] = v;
    }

    ll find(ll v)
    {
        if (v == padre[v])
            return v;
        return padre[v] = find(padre[v]);
    }

    void unite(ll u, ll v)
    {
        u = find(u), v = find(v);
        if (u == v)
            return;
        if (rank[u] < rank[v])
            swap(u, v);
        padre[v] = padre[u];
        rank[u] = max(rank[u], rank[v] + 1);
    }

    vector<ll> padre;
    vector<ll> rank;
};

pair<double, double> kruskal()
{
    sort(E.begin(), E.end());

    double UTP = 0;
    double F = 0;

    ll aristas = 0;
    ll ccs = N;

    DSU dsu(N);

    for (tuple<double, ll, ll> arista : E)
    {
        double distancia = get<0>(arista);
        ll u = get<1>(arista);
        ll v = get<2>(arista);

        // si (u,v) es arista segura
        if (dsu.find(u) != dsu.find(v))
        {
            // agregar
            dsu.unite(u, v);
            aristas++;
            ccs--;

            if (distancia <= R)
            {
                UTP += (distancia * U);
            }
            else
            {
                F += (distancia * V);
            }
        }

        if (ccs == W)
        {
            break;
        }
    }

    return make_pair(UTP, F);
}

int main()
{

    cin >> C;

    // Itero por la cantidad de casos de prueba
    for (ll caso = 1; caso <= C; caso++)
    {

        cin >> N >> R >> W >> U >> V;

        // Definimos el vector de oficinas
        // Esto nos va a permitir definir el grafo
        // con las distancias entre oficinas
        oficinas = vector<pair<ll, ll>>();
        E = vector<tuple<double, ll, ll>>();

        for (ll i = 0; i < N; i++)
        {
            // Tomo las coordenadas de la iesima oficina
            cin >> xi >> yi;
            oficina = make_pair(xi, yi);

            // Ahora calculo la distancia de esa oficina a todas las otras
            // Agrego esas aristas a mi grafo (representado como lista de aristas)
            for (ll j = 0; j < oficinas.size(); j++)
            {
                double distancia = dist(oficina, oficinas[j]);
                E.push_back({distancia, i, j});
            }

            // Agrego la oficina
            oficinas.push_back(oficina);
        }

        pair<double, double> costos = kruskal();
        cout << fixed << setprecision(3) << "Caso #" << caso << ": " << costos.first << " " << costos.second << endl;
    }

    return 0;
}