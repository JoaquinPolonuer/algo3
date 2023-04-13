#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int c;
int n, r, m;
vector<int> v;
vector<vector<int>> dp;

int potencia_modular(int a, int k)
{
    if (k == 0)
    {
        return a;
    }
    else
    {
        int aux = potencia_modular(a, k / 2) % m;
        if (k % 2 == 0)
        {
            return (aux * aux) % m;
        }
        else
        {
            return (((aux * aux) % m) * a) % m;
        }
    }
}

int modulo_positivo(int a)
{
    return (m + (a % m)) % m;
}

bool operaciones(long long int mod_acum, long int i)
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
        bool suma = operaciones(modulo_positivo(mod_acum + v[i]), i + 1);
        bool resta = operaciones(modulo_positivo(mod_acum - v[i]), i + 1);
        bool multi = operaciones(modulo_positivo(mod_acum * v[i]), i + 1);

        int p = potencia_modular(mod_acum, v[i]);
        bool potencia = operaciones(modulo_positivo(p), i + 1);
        bool res = suma or resta or multi or potencia;
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
        v = vector<int>(); 
        for (int j = 0; j < n; j++)
        {
            int x;
            cin >> x;
            v.push_back(x);
        }
        dp = vector<vector<int>>(m, vector<int>(n + 1, -1));
        
        bool res = operaciones(modulo_positivo(v[0]), 1);
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