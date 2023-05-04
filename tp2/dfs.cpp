#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <iomanip> // std::setprecision
using namespace std;

// define
// BLANCO = 0
// GRIS = 1
// NEGRO = 2

# define BLANCO 0
# define GRIS 1
# define NEGRO 2

vector<vector<int>> aristas;
vector<int> estado;
vector<int> padre;
int N, M;

void dfs(int v)
{
    estado[v] = GRIS;
    for (int u : aristas[v])
    {
        if (estado[u] == BLANCO)
        {
            padre[u] = v;
            dfs(u);
        }
    }
    estado[v] = NEGRO;
}

int main()
{
    cin >> N >> M;
    padre = vector<int>(N + 1, -1);
    estado = vector<int>(N + 1, BLANCO);
    aristas = vector<vector<int>>(N + 1);

    for (int i = 0; i < M; i++)
    {
        int v, w;
        cin >> v;
        cin >> w;
        aristas[v].push_back(w);
        aristas[w].push_back(v);
    }

    dfs(1);
    cout << "listo";
}