#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <iomanip> // std::setprecision
using namespace std;

#define BLANCO 0
#define GRIS 1
#define NEGRO 2

vector<vector<int>> aristas;
vector<vector<int>> treeEdges;
vector<int> estado;
vector<int> padre;

vector<int> backConExtremoSuperiorEn;
vector<int> backConExtremoInferiorEn;

vector<int> memo;

int N, M;

void dfs(int v)
{
    estado[v] = GRIS;
    for (int u : aristas[v])
    {
        if (estado[u] == BLANCO)
        {
            padre[u] = v;
            treeEdges[v].push_back(u);
            dfs(u);
        }
        else if (u != padre[v] && estado[u] == GRIS)
        {
            if(v == 1){
                cout << "a";
            }
            backConExtremoInferiorEn[v]++;
            backConExtremoSuperiorEn[u]++;
        }
    }
    estado[v] = NEGRO;
}

int cubren(int v)
{
    if (memo[v] != -1)
        return memo[v];

    int res = 0;
    res += backConExtremoInferiorEn[v];
    res -= backConExtremoSuperiorEn[v];
    for (int hijo : treeEdges[v])
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
    
    aristas = vector<vector<int>>(N + 1);
    treeEdges = vector<vector<int>>(N + 1);
    estado = vector<int>(N + 1, BLANCO);
    padre = vector<int>(N + 1, -1);

    backConExtremoInferiorEn = vector<int>(N + 1, 0);
    backConExtremoSuperiorEn = vector<int>(N + 1, 0);

    memo = vector<int>(N + 1, -1);

    for (int i = 0; i < M; i++)
    {
        int v, w;
        cin >> v;
        cin >> w;
        aristas[v].push_back(w);
        aristas[w].push_back(v);
    }

    dfs(1);


    vector<pair<int, int>> puentes;
    for (int i = 1; i <= N; i++)
    {
        if (cubren(i) == 0 and padre[i] != -1)
        {   
            puentes.push_back(make_pair(padre[i], i));
        }
    }
    
    cout << "listo";
}