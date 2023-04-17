#include <vector>
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

int c, r, n, m;
vector<int> v;
vector<vector<int>> memo; //-1 no definido, 0 false, 1 true
int potencia_modular(int a, int k)
{
    if (k == 1)
    {
        return a;
    }
    else
    {
        int aux = potencia_modular(a, k / 2) % m;
        int resto = a * (k % 2) % m;
        return (aux * aux * resto) % m;
    }
}
int modulo_positivo(int a)
{
    return (m + (a % m)) % m;
}
bool operaciones(int acum, int i)
{
    if (memo[acum][i] != -1)
    {
        return memo[acum][i] == 1;
    }

    bool res;
    if (i == n)
    {
        res = (acum == r);
    }
    else
    {
        bool suma = operaciones(modulo_positivo(acum + v[i]), i + 1);

        bool mult = operaciones(modulo_positivo(acum * v[i]), i + 1);

        bool pot = operaciones(modulo_positivo(potencia_modular(acum, v[i])), i + 1);

        bool resta = operaciones(modulo_positivo(acum - v[i]), i + 1);

        res = suma or mult or pot or resta;
    }
    if (res)
    {
        memo[acum][i] = 1;
    }
    else
    {
        memo[acum][i] = 0;
    }
    return res;
}

int main()
{
    vector<string> respuestas;
    cin >> c;
    for (int j = 0; j < c; j++)
    {
        cin >> n >> r >> m;
        v = vector<int>();
        for (int k = 0; k < n; k++)
        {
            int elem;
            cin >> elem;
            v.push_back(elem);
        }
        memo = vector<vector<int>>(m, vector<int>(n + 1, -1));
        bool res = operaciones(modulo_positivo(v[0]), 1);
        if (res)
        {
            respuestas.push_back("Si");
        }
        else
        {
            respuestas.push_back("No");
        }
    }
    for (const auto &elem : respuestas)
    {
        cout << elem << endl;
    }
    return 0;
}