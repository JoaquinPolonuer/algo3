#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <iomanip>      // std::setprecision
#include <algorithm>
#include <limits>

/*
 * Archivo para la experimentación:
 * Implementación:
 *                - 0 = Kruskal O(N^2), DSU cuadrático
 *                - 1 = Kruskal O(M * log(N)), union by rank
 *                - 2 = Prim O(N^2),
 *                - 3 = Prim O(N * log (N)), con path compression
 */

#define IMPLEMENTATION 0

double inf = std::numeric_limits<double>::infinity();
using namespace std;
vector<tuple<int,int>> verticeACoord;
vector<tuple<double,int,int>> E;
vector<vector<double>> g;
int C,N,R,W,U,V;

struct DSU_n2
{
    DSU_n2()
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


struct DSU_byrank{
    explicit DSU_byrank(int n){
        padre = rank = vector<int>(n+1);
        for(int v = 1; v < n+1; v++) padre[v] = v;
    }
    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }
    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }
    vector<int> padre;
    vector<int> rank;
    vector<int> mas_cercano;
};

struct DSU_infeciente{
    explicit DSU_infeciente(int n){
        padre = vector<int>(n+1);
        for(int v = 1; v < n+1; v++) padre[v] = v;
    }
    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }
    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        padre[v] = padre[u];
    }
    vector<int> padre;
};

/*
 * Idea: Kruskal en O(N^2) ¿Se puede? hasta que me queden W componentes conexas (los routers)
 * Demostrar: Esto es equivalente a en lugar de N-1 aristas, elegir N-1-(W-1) = N-W aristas.
 * Complejidad: Debería ser O(N^2), para eso find y union debería ser O(1), ya que kruskal tiene un
 * ciclo que revisa todas las aristas.
 * Complejidad actual: O(M*log(N))=O(N^2*log(N)), peor que prim :(
 */

double dist(tuple<int,int> p1, tuple<int,int> p2){
    double dist = sqrt(pow(get<0>(p1)-get<0>(p2),2)+pow(get<1>(p1)-get<1>(p2),2));
    return dist;
}

pair<double,double> kruskal_mlogn()
{
    sort(E.begin(),E.end());
    pair<double,double> res = make_pair(0,0);
    int aristas = 0;
    DSU_byrank dsu(N);
    for(auto arista : E){
        //si (u,v) es arista segura
        double c = get<0>(arista);
        int u = get<1>(arista);
        int v = get<2>(arista);
        if(dsu.find(u) != dsu.find(v) and aristas<N-W){
            dsu.unite(u,v);
            aristas++;
            if(dist(verticeACoord[u],verticeACoord[v])<=R){
                get<0>(res) += c;
            }else{
                get<1>(res) += c;
            }
        }
    }
    return res;
}

pair<double,double> kruskal_ineficiente()
{
    sort(E.begin(),E.end());
    pair<double,double> res = make_pair(0,0);
    int aristas = 0;
    DSU_infeciente dsu(N);
    for(auto arista : E){
        //si (u,v) es arista segura
        double c = get<0>(arista);
        int u = get<1>(arista);
        int v = get<2>(arista);
        if(dsu.find(u) != dsu.find(v) and aristas<N-W){
            dsu.unite(u,v);
            aristas++;
            if(dist(verticeACoord[u],verticeACoord[v])<=R){
                get<0>(res) += c;
            }else{
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

pair<double,double> prim_n2(){
    pair<double,double> costos = make_pair(0,0);
    vector<bool> es_rojo(N,false); es_rojo[0] = true;
    vector<int> rojo_mas_cercano(N,0);
    for(int it = 1; it < N-W; it++){
        //agregar a la arista violeta mas barata
        int agrego = 0;
        while(es_rojo[agrego]) agrego++;
        for(int v = agrego+1; v < N; v++)
            if(!es_rojo[v] and g[v][rojo_mas_cercano[v]] < g[agrego][rojo_mas_cercano[agrego]])
                agrego = v;

        //pintar de rojo su extremo azul
        es_rojo[agrego] = true;

        //actualizar info de rojo_mas_cercano
        for(int v = 0; v < N; v++)
            if(!es_rojo[v] and g[v][agrego] < g[v][rojo_mas_cercano[v]]) rojo_mas_cercano[v] = agrego;

        //res.push_back(make_tuple(agrego,rojo_mas_cercano[agrego],g[agrego][rojo_mas_cercano[agrego]]));

        if(g[agrego][rojo_mas_cercano[agrego]] <= R){
            costos.first += g[agrego][rojo_mas_cercano[agrego]];
        }else{
            costos.second += g[agrego][rojo_mas_cercano[agrego]];
        }
    }
    return costos;
}




int main(){
    if(IMPLEMENTATION == 0){
        cout << "---------IMPLEMENTACION KRUSKAL N^2---------"<< endl;

    }else if(IMPLEMENTATION==1){
        cout << "---------IMPLEMENTACION KRUSKAL M*log(N)---------"<< endl;

    }else if(IMPLEMENTATION==2){
        cout << "---------IMPLEMENTACION KRUSKAL SIN UNION BY RANK---------"<< endl;

    }else{
        cout << "NO HAY IMPLEMENTACION" << endl;
        return 0;
    }
    cin >> C;
    for(int it=1;it<=C;it++){
        cin >> N >> R >> W >> U >> V;
        verticeACoord = vector<tuple<int,int>>(N, make_tuple(-1,-1));
        E = vector<tuple<double,int,int>>();
        g = vector<vector<double>>(N,vector<double>(N));
        for(int it2=0;it2<N;it2++){
            int x,y;
            cin >> x >> y;
            verticeACoord[it2]= make_tuple(x,y);
        }
        for(int v=0;v<N;v++){
            tuple<int,int> coord = verticeACoord[v];
            for(int u=v+1;u<N;u++){
                double distancia = dist(coord,verticeACoord[u]);
                g[u][v] = distancia;
                g[v][u] = distancia;
                if(distancia <= R){
                    double precio = U * distancia;
                    E.emplace_back(precio,u,v);
                }else{
                    double precio = V * distancia;
                    E.emplace_back(precio,u,v);
                }
            }
        }
        pair<double,double> res;
        if(IMPLEMENTATION == 0){
            res = kruskal_n2();

        }else if(IMPLEMENTATION==1){
            res = kruskal_mlogn();

        }else if(IMPLEMENTATION==2){
            res = kruskal_ineficiente();

        }

        cout << fixed << setprecision(3) << "Caso #" << it << ": " << get<0>(res) << " " << get<1>(res) << endl;
    }
    return 0;
}