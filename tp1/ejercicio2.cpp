#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int c;
vector<int> ns, rs, ms;
int n, r, m;
vector<vector<int>> vs;
vector<int> v;
vector<vector<int>> dp;

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

bool operaciones(int mod_acum, int i)
{
    if (dp[mod_acum][i] != -1)
    {
        return dp[mod_acum][i] == 1;
    }

    bool res;

    if (i == n)
    {
        res = mod_acum == r;
    }
    else
    {
        res = operaciones(modulo_positivo(mod_acum + v[i]), i + 1) ||
              operaciones(modulo_positivo(mod_acum - v[i]), i + 1) ||
              operaciones(modulo_positivo(mod_acum * v[i]), i + 1) ||
              operaciones(modulo_positivo(potencia_modular(mod_acum, v[i])), i + 1);
    }

    if (res)
    {
        dp[mod_acum][i] = 1;
    }
    else
    {
        dp[mod_acum][i] = 0;
    }

    return res;
}

int main()
{
    cin >> c;

    // Esta bien como manejo esta entrada?
    for (int i = 0; i < c; i++)
    {
        cin >> n >> r >> m;
        ns.push_back(n);
        rs.push_back(r);
        ms.push_back(m);

        vector<int> v;
        for (int j = 0; j < n; j++)
        {
            int x;
            cin >> x;
            v.push_back(x);
        }
        vs.push_back(v);
    }


    bool res;
    for (int i = 0; i < c; i++)
    {
        v = vs[i];
        n = ns[i];
        m = ms[i];
        r = rs[i];
        dp = vector<vector<int>>(m, vector<int>(n + 1, -1));

        res = operaciones(modulo_positivo(v[0]), 1);
        if (res)
        {
            cout << "Si";
        }
        else
        {
            cout << "No";
        }
        cout << endl;
    }

    return 0;
}

// TENER EN CUENTA:
    // Actualmente funciona y los resultados son correctos

    // Esta rara la manera en la que obtenemos y usamos los datos de entrada.
    // Tampoco me gusta mucho la forma en la que declaramos siempre la matriz de dp.