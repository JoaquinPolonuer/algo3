#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N, k;
vector<vector<int>> C;
vector<int> suma_filas;
vector<int> suma_columnas;
vector<int> suma_diagonales;
vector<bool> utilizados;
int numero_magico;

pair<int, int> siguiente_posicion(int i, int j)
{
    if (j + 1 == N)
    {
        i += 1;
        j = 0;
    }
    else
    {
        j++;
    }
    return make_pair(i, j);
}

void imprimir_matriz()
{
    for (int fila = 0; fila < N; fila++)
    {
        for (int columna = 0; columna < N; columna++)
        {
            cout << C[fila][columna] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void k_esimo_cuadrado(int i, int j)
{
    if (i == N && suma_diagonales[1] == numero_magico && suma_diagonales[0] == numero_magico)
    {
        if (k == 1)
        {
            imprimir_matriz();
        }
        k--;
    }

    pair<int, int> siguientes = siguiente_posicion(i, j);
    int i_sig = siguientes.first;
    int j_sig = siguientes.second;

    for (int num = 1; num < utilizados.size() + 1; num++)
    {
        if (utilizados[num - 1])
        {
            continue;
        }

        C[i][j] = num;
        utilizados[num - 1] = true;

        suma_filas[i] += num;
        suma_columnas[j] += num;
        if (i == j)
            suma_diagonales[0] += num;
        if (i + j == N - 1)
            suma_diagonales[1] += num;

        if (suma_filas[i] <= numero_magico && suma_columnas[j] <= numero_magico)
        {
            k_esimo_cuadrado(i_sig, j_sig);
        }

        utilizados[num - 1] = false;

        suma_filas[i] -= num;
        suma_columnas[j] -= num;
        if (i == j)
            suma_diagonales[0] -= num;
        if (i + j == N - 1)
            suma_diagonales[1] -= num;
    }
}

int main()
{
    cin >> N >> k;
    C.resize(N, vector<int>(N, 0));
    suma_diagonales.resize(2, 0);
    suma_filas.resize(N, 0);
    suma_columnas.resize(N, 0);
    utilizados.resize(pow(N, 2));
    numero_magico = (pow(N, 3) + N) / 2;

    k_esimo_cuadrado(0, 0);

    return 0;
}

// TENER EN CUENTA:
    // Actualmente funciona, pero es rara y poco eficiente la 
    // forma en la que devuelvo la matrix. Notar que se tiene una variable global k y 
    // que el codigo siempre encuentra TODOS los cuadrados magicos.

    // Las podas tienen en cuenta filas y columnas, y se chequean las diagonales al 
    // finalizar

    // Capaz habria que poner un if/else que separe el caso base del recursivo, aunque
    // como esta anda