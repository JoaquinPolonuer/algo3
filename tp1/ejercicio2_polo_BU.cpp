#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

long long int c;
long long int n, r, m;
vector<long long int> v;
vector<int> fila_superior;
vector<int> fila_actual;

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
    if (fila_superior[mod_acum] != -1)
    {
        return fila_superior[mod_acum] == 1;
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
        fila_actual[mod_acum] = 1;
    }
    else
    {
        fila_actual[mod_acum] = 0;
    }

    return res;
}

int main()
{
    cin >> c;

    // Esta bien como manejo esta entrada?
    bool res;
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
        fila_superior = vector<int>(m -1);
        fila_actual = vector<int>(m -1);

        for (int j = n; j < 0; j--){
            res = operaciones(modulo_positivo(v[n]), 1);
            fila_superior = fila_actual;
        }

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