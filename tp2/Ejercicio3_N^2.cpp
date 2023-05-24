#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <iomanip> // std::setprecision
#include <algorithm>
#include <limits>

using namespace std;
double inf = std::numeric_limits<double>::infinity();
int C, N, R, W, U, V;

vector<vector<double>> g;

vector<pair<int, int>> oficinas;

int xi, yi;

double dist(pair<int, int> p1, pair<int, int> p2)
{
    double dist = sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
    return dist;
}
struct DSU
{

    DSU()
    {
        componente = vector<int>(g.size());
        mas_cercano = vector<pair<int, double>>(g.size());

        for (int v = 0; v < g.size(); v++)
            componente[v] = v;
        //Inicializo el mas cercano de cada nodo.
        for(int i = 0; i < g.size(); i++)
        {
            double dist_mas_cerc = inf;

            for(int j = 0; j < g.size();j++)
            {
                if(j != i and g[i][j] < dist_mas_cerc)
                {
                    dist_mas_cerc = g[i][j];
                    mas_cercano[i]= make_pair(j,dist_mas_cerc);
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
            //i = componente[i];
            if (mas_cercano[i].second < menor_distancia)
            {
                menor_distancia = mas_cercano[i].second;
                u = componente[i];
                v = mas_cercano[i].first;
                v = componente[v];
            }
        }
        //u y v son los representantes de cada componente

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
        // Una buena idea ademas seria actualizar las distancias desde todos los otros
        // nodos hasta u y v. Esto se haria mirando las columnas u y v y haciendo el 
        // mismo procedimiento.


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

pair<double, double> kruskal()
{
    double UTP = 0.0;
    double F = 0.0;

    int ccs = N;

    DSU dsu;

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

int main()
{

    cin >> C;

    // Itero por la cantidad de casos de prueba
    for (int caso = 1; caso <= C; caso++)
    {

        cin >> N >> R >> W >> U >> V;

        // Definimos el vector de oficinas
        // Esto nos va a permitir definir el grafo
        // con las distancias entre oficinas

        oficinas = vector<pair<int, int>>();
        g = vector<vector<double>>(N, vector<double>(N));

        for (int i = 0; i < N; i++)
        {
            // Tomo las coordenadas de la iesima oficina
            cin >> xi >> yi;
            pair<int,int> oficina = make_pair(xi, yi);

            // Ahora calculo la distancia de esa oficina a todas las otras
            // Agrego esas aristas a mi grafo (representado como lista de aristas)
            for (int j = 0; j < oficinas.size(); j++)
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