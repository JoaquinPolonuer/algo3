#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

long long int c;
long long int n, r, m;
vector<long long int> v;
vector<vector<long long int>> dp;

long long int potencia_modular(long long int a, long long int k)
{
    if (k == 0)
    {
        return 1;
    }
    else
    {
        long long int aux = potencia_modular(a, k / 2) % m;
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

long long int modulo_positivo(long long int a)
{
    return (m + (a % m)) % m;
}

bool operaciones(long long int mod_acum, long long int i)
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
        long long int mod_v = modulo_positivo(v[i]);

        bool suma = operaciones(modulo_positivo(mod_acum + mod_v), i + 1);
        bool resta = operaciones(modulo_positivo(mod_acum - mod_v), i + 1);
        bool multi = operaciones(modulo_positivo(mod_acum * mod_v), i + 1);

        long long int p = potencia_modular(mod_acum, mod_v);
        bool potencia = operaciones(modulo_positivo(p), i + 1);
        res = (suma or resta or multi or potencia);
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
    for (long long int i = 0; i < c; i++)
    {
        cin >> n >> r >> m;
        v = vector<long long int>(); 
        for (long long int j = 0; j < n; j++)
        {
            long long int x;
            cin >> x;
            v.push_back(x);
        }
        dp = vector<vector<long long int>>(m, vector<long long int>(n + 1, -1));
        
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