#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <iomanip> // std::setprecision
#include <algorithm>
#include <limits>
#include <fstream>
#include <chrono>

/*
 * Archivo para la experimentación:
 * Implementación:
 *                - 0 = Kruskal O(N^2), DSU cuadrático
 *                - 1 = Kruskal O(M * log(N)), union by rank y path compression
 *                - 2 = Kruskal O(M * N^2), sin union by rank y sin path compression
 */

#define IMPLEMENTATION 2

double inf = std::numeric_limits<double>::infinity();
using namespace std;
vector<tuple<int, int>> verticeACoord;
vector<tuple<double, int, int>> E;
vector<vector<double>> g;
vector<pair<int, int>> oficinas;
int N, R, W, U, V;

double dist(tuple<int, int> p1, tuple<int, int> p2)
{
    double dist = sqrt(pow(get<0>(p1) - get<0>(p2), 2) + pow(get<1>(p1) - get<1>(p2), 2));
    return dist;
}

struct DSU_n2
{
    DSU_n2()
    {
        componente = vector<int>(g.size());
        mas_cercano = vector<pair<int, double>>(g.size());

        for (int v = 0; v < g.size(); v++)
            componente[v] = v;
        // Inicializo el mas cercano de cada nodo.
        for (int i = 0; i < g.size(); i++)
        {
            double dist_mas_cerc = inf;

            for (int j = 0; j < g.size(); j++)
            {
                if (j != i and g[i][j] < dist_mas_cerc)
                {
                    dist_mas_cerc = g[i][j];
                    mas_cercano[i] = make_pair(j, dist_mas_cerc);
                }
            }
        }
    }

    tuple<int, int, double> proxima_arista()
    {
        int u = -1;
        int v = -1;
        double menor_distancia = inf;

        for (int i = 0; i < mas_cercano.size(); i++)
        {
            // i = componente[i];
            if (mas_cercano[i].second < menor_distancia)
            {
                menor_distancia = mas_cercano[i].second;
                u = componente[i];
                v = mas_cercano[i].first;
                v = componente[v];
            }
        }
        // u y v son los representantes de cada componente

        return {u, v, menor_distancia};
    }

    void unite(int u, int v)
    {

        // Pongo u y v en la misma componente
        int comp_a_reemplazar = componente[v];
        for (int i = 0; i < componente.size(); i++)
        {
            if (componente[i] == comp_a_reemplazar)
            {
                componente[i] = componente[u];
            }
        }

        // Ahora actualizamos las adyacencias de u y v,
        // haciendo una mezcla entre sus filas en la matriz de adyacencias
        // A su vez, guardamos la componente mas cercana a la
        // componente que resulta de unir u y v.
        int componente_mas_cercana = -1;
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

    vector<int> componente;
    vector<pair<int, double>> mas_cercano;
};

struct DSU_byrank
{
    explicit DSU_byrank(int n)
    {
        padre = rank = vector<int>(n + 1);
        for (int v = 1; v < n + 1; v++)
            padre[v] = v;
    }
    int find(int v)
    {
        if (v == padre[v])
            return v;
        return padre[v] = find(padre[v]);
    }
    void unite(int u, int v)
    {
        u = find(u), v = find(v);
        if (u == v)
            return;
        if (rank[u] < rank[v])
            swap(u, v);
        padre[v] = padre[u];
        rank[u] = max(rank[u], rank[v] + 1);
    }
    vector<int> padre;
    vector<int> rank;
    vector<int> mas_cercano;
};

struct DSU_infeciente
{
    explicit DSU_infeciente(int n)
    {
        padre = vector<int>(n + 1);
        for (int v = 1; v < n + 1; v++)
            padre[v] = v;
    }
    int find(int v)
    {
        if (v == padre[v])
            return v;
        return padre[v] = find(padre[v]);
    }
    void unite(int u, int v)
    {
        // u = find(u), v = find(v);
        if (u == v)
            return;
        padre[v] = padre[u];
    }
    vector<int> padre;
};

pair<double, double> kruskal_mlogn()
{
    sort(E.begin(), E.end());
    pair<double, double> res = make_pair(0, 0);
    int aristas = 0;
    DSU_byrank dsu(N);
    for (auto arista : E)
    {
        // si (u,v) es arista segura
        double c = get<0>(arista);
        int u = get<1>(arista);
        int v = get<2>(arista);
        if (dsu.find(u) != dsu.find(v) and aristas < N - W)
        {
            dsu.unite(u, v);
            aristas++;
            if (dist(verticeACoord[u], verticeACoord[v]) <= R)
            {
                get<0>(res) += c;
            }
            else
            {
                get<1>(res) += c;
            }
        }
    }
    return res;
}

pair<double, double> kruskal_ineficiente()
{
    sort(E.begin(), E.end());
    pair<double, double> res = make_pair(0, 0);
    int aristas = 0;
    DSU_infeciente dsu(N);
    for (auto arista : E)
    {
        // si (u,v) es arista segura
        double c = get<0>(arista);
        int u = get<1>(arista);
        int v = get<2>(arista);
        if (dsu.find(u) != dsu.find(v) and aristas < N - W)
        {
            dsu.unite(u, v);
            aristas++;
            if (dist(verticeACoord[u], verticeACoord[v]) <= R)
            {
                get<0>(res) += c;
            }
            else
            {
                get<1>(res) += c;
            }
        }
    }
    return res;
}

pair<double, double> kruskal_n2()
{
    double UTP = 0.0;
    double F = 0.0;

    int ccs = N;

    DSU_n2 dsu;

    while (ccs > W)
    {
        tuple<int, int, double> e = dsu.proxima_arista();

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

void construir_instancia_random(int n)
{
    vector<tuple<int, int, int>> res;
    srand(time(NULL));
    tuple<int, int, int> numero;

    N = n;
    W = rand() % (N - 1) + 1;
    R = rand() % (100000) + 1;
    V = rand() % (10) + 1;
    U = rand() % (V) + 1;

    oficinas = vector<pair<int, int>>();
    g = vector<vector<double>>(N, vector<double>(N));
    verticeACoord = vector<tuple<int, int>>(N, make_tuple(-1, -1));
    E = vector<tuple<double, int, int>>();

    for (int i = 0; i < N; i++)
    {
        int xi, yi;
        xi = rand() % (20000) - 10000;
        yi = rand() % (20000) - 10000;
        pair<int, int> oficina = make_pair(xi, yi);
        tuple<int, int> coord = verticeACoord[i];

        for (int j = 0; j < oficinas.size(); j++)
        {
            double distancia = dist(oficina, oficinas[j]);
            g[i][j] = distancia;
            g[j][i] = distancia;
            if (distancia <= R)
            {
                double precio = U * distancia;
                E.emplace_back(precio, i, j);
            }
            else
            {
                double precio = V * distancia;
                E.emplace_back(precio, i, j);
            }
        }

        // Agrego la oficina
        oficinas.push_back(oficina);
    }
}

tuple<double, double, double> measure(int n)
{
    construir_instancia_random(n);

    auto start = chrono::high_resolution_clock::now();
    auto res = kruskal_n2();
    auto stop = chrono::high_resolution_clock::now();
    double cuadrado = (stop - start).count();

    construir_instancia_random(n);
    start = chrono::high_resolution_clock::now();
    res = kruskal_mlogn();
    stop = chrono::high_resolution_clock::now();
    double mlogn = (stop - start).count();


    construir_instancia_random(n);
    start = chrono::high_resolution_clock::now();
    res = kruskal_ineficiente();
    stop = chrono::high_resolution_clock::now();
    double mncuadrado = (stop - start).count();

    return {cuadrado, mlogn, mncuadrado};
}

int main()
{
    int repeat = 20;
    ofstream output_file;

    /*
     * Actualmente solo está hecho el de RANDOM
     * Habría que pensar qué otro es interesante para testear la complejidad
     */

    output_file.open("runtime_random.csv");
    output_file << "n,n^2,mlogn,mn^2\n";

    /*
     * Obs: En el enunciado 1<=N<=1000, podemos subirlo hasta 2000 para que se vea un poco mejor la comlejidad
     */

    int limit = 1000;
    for (int n = 2; n <= limit; n += 50)
    {
        double counter = 0;
        double cuadrado_total = 0;
        double nlogm_total = 0;
        double mncuadrado = 0;

        double cuadrado, nlogm, nlogmcuadrado;
        for (int it = 0; it < repeat; it++)
        {
            tie(cuadrado, nlogm, nlogmcuadrado) = measure(n);

            cuadrado_total += cuadrado;
            nlogm_total += nlogm;
            mncuadrado += nlogmcuadrado;
        }

        output_file << n    << "," << cuadrado_total / repeat 
                            << "," << nlogm_total / repeat
                            << "," << mncuadrado / repeat << endl;

        cout << n << "/" << limit << endl;
    }

    output_file.close();
    return 0;
}
