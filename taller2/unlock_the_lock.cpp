#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int L, U, R;
int ri;
vector<int> level;
vector<int> botones;

void bfs(int v)
{
    queue<int> lista;
    lista.push(v);

    level[v] = 0;
    while (!lista.empty())
    {
        int u = lista.front();
        for (int boton : botones)
        {
            int prox = (u + boton) % 10000;
            if (level[prox] == -1)
            {
                level[prox] = level[u] + 1;
                lista.push(prox);
            }
        }
        lista.pop();
    }
}

int main()
{
    int it = 1;
    while (true)
    {
        cin >> L >> U >> R;
        if (L == 0 && U == 0 && R == 0)
        {
            break;
        }

        level = vector<int>(10000, -1);
        botones = vector<int>();

        for (int i = 0; i < R; i++)
        {
            cin >> ri;
            botones.push_back(ri);
        }

        bfs(L);
        if (level[U] == -1)
        {
            cout << "Case " << it << ": Permanently Locked" << endl;
        }
        else
        {
            cout << "Case " << it << ": " << level[U] << endl;
        }
        it++;
    }

    return 0;
}
