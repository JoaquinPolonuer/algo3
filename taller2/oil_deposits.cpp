#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int n, m;
char a;
vector<vector<int>> visitados;
vector<pair<int, int>> posiciones;

int main()
{
    while (true)
    {
        cin >> n >> m;
        posiciones = vector<pair<int,int>>();
        visitados = vector<vector<int>>();
 
        if (n == 0)
        {
            break;
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {

                cin >> a;
                if (a == '@')
                {
                    posiciones.push_back(make_pair(i, j));
                }
            }
        }

        for (auto posicion : posiciones)
        {
            // Ahora defino la lista de adyacencias
        }

        // Despues hago bfs/dfs para encontrar componentes conexas
    }

    return 0;
}
