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

vector<vector<ll>> g;

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

    DSU()
    {
        componente = vector<ll>(g.size());
        mas_cercano = vector<pair<ll, double>>(g.size());

        for (ll v = 0; v < g.size(); v++)
            componente[v] = v;
    }

    tuple<ll, ll, double> proxima_arista()
    {
        ll u = -1;
        ll v = -1;
        double menor_distancia = inf;

        for (int i = 0; i < mas_cercano.size(); i++)
        {
            if (mas_cercano[i].second < menor_distancia)
            {
                menor_distancia = mas_cercano[i].second;
                u = componente[i];
                v = mas_cercano[i].first;
            }
        }

        return {u, v, g[u][v]};
    }

    void unite(ll u, ll v)
    {

        // Pongo u y v en la misma componente
        for (int i = 0; i < componente.size(); i++)
        {
            if (componente[i] == componente[v])
            {
                componente[i] = componente[u];
            }
        }

        // Ahora actualizamos las adyacencias de u y v,
        // haciendo una mezcla entre sus filas en la matriz de adyacencias
        // A su vez, guardamos la componente mas cercana a la
        // componente que resulta de unir u y v.
        ll componente_mas_cercana = -1;
        double menor_distancia = inf;

        for (int i = 0; i < g.size(); i++)
        {
            g[u][i] = min(g[u][i], g[v][i]);
            g[v][i] = min(g[u][i], g[v][i]);

            if (g[u][i] < menor_distancia && componente[i] != componente[u])
            {
                componente_mas_cercana = componente[i];
                menor_distancia = g[u][i];
            }
        }

        // Para todos los nodos, en el componente de u
        // actualizamos su componente mas cercana con su distancia
        for (int i = 0; i < componente.size(); i++)
        {
            if (componente[i] == componente[u])
            {
                mas_cercano[i] = make_pair(componente_mas_cercana, menor_distancia);
            }
        }
    }

    vector<ll> componente;
    vector<pair<ll, double>> mas_cercano;
};

pair<double, double> kruskal()
{
    double UTP = 0;
    double F = 0;

    ll ccs = N;

    DSU dsu;

    while (ccs > W)
    {
        tuple<ll, ll, double> e = dsu.proxima_arista();

        dsu.unite(get<0>(e), get<1>(e));

        double distancia = get<2>(e);
        if (distancia <= R)
        {
            UTP += distancia * U;
        }
        else
        {
            F += distancia * V;
        }

        ccs--;
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
        g = vector<vector<ll>>(N, vector<ll>(N));
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
                g[i][j] = distancia;
                g[j][i] = distancia;
            }

            // Agrego la oficina
            oficinas.push_back(oficina);
        }

        pair<double, double> costos = kruskal();
        cout << fixed << setprecision(3) << "Caso #" << caso << ": " << costos.first << " " << costos.second << endl;
    }

    return 0;
}