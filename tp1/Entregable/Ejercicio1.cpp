#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N, k;
vector<vector<int>> C;              // C es la matriz global donde se van calculando los cuadrados mágicos
vector<vector<int>> matrizSolucion; // matrizSolución va a guardar la instancia de C que nos interesa
vector<int> suma_filas;             // Suma de las filas de C
vector<int> suma_columnas;          // Suma de las columnas de C
vector<int> suma_diagonales;        // Suma de las diagonales de C
vector<bool> utilizados;            // Guardo si utilice un número
int numero_magico;                  // Precalculo el número mágico

void imprimir_matriz(vector<vector<int>> M)
{
    for (int fila = 0; fila < N; fila++)
    {
        for (int columna = 0; columna < N; columna++)
        {
            cout << M[fila][columna] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void cuadradoMagicoKesimo(int i, int j)
{
    if (i == N)
    {
        k--;
        if (k == 0)
        {
            matrizSolucion = C;
        }
    }

    int i_sig, j_sig;
    for (int l = 1; l <= N * N; l++)
    {
        bool valido = true;
        if ( // podas:
            (utilizados[l - 1] == 1) or
            (suma_filas[i] + l > numero_magico) or
            (j == N - 1 && suma_filas[i] + l != numero_magico) or
            (suma_columnas[j] + l > numero_magico) or
            (i == N - 1 && suma_columnas[j] + l != numero_magico) or
            (i == j && suma_diagonales[0] + l > numero_magico) or
            (i == j && i == N - 1 && suma_diagonales[0] + l != numero_magico) or
            (i == N - j - 1 && suma_diagonales[1] + l > numero_magico) or
            (i == N - j - 1 && i == N - 1 && suma_diagonales[1] + l != numero_magico) or
            (k < 0))
        {
            valido = false;
        }

        if (valido)
        {

            if (j + 1 == N)
            {
                i_sig = i + 1;
                j_sig = 0;
            }
            else
            {
                i_sig = i;
                j_sig = j + 1;
            }

            C[i][j] = l;
            utilizados[l - 1] = 1;
            suma_filas[i] += l;
            suma_columnas[j] += l;
            if (i == j)
            {
                suma_diagonales[0] += l;
            }
            if (i == N - j - 1)
            {
                suma_diagonales[1] += l;
            }

            cuadradoMagicoKesimo(i_sig, j_sig);

            utilizados[l - 1] = 0;
            suma_filas[i] -= l;
            suma_columnas[j] -= l;
            if (i == j)
                suma_diagonales[0] -= l;
            if (i == N - j - 1)
                suma_diagonales[1] -= l;
        }
    }
}

int main()
{
    cin >> N >> k;
    // Inicializar variables:
    C.resize(N, vector<int>(N, 0));
    suma_diagonales.resize(2, 0);
    suma_filas.resize(N, 0);
    suma_columnas.resize(N, 0);
    utilizados.resize(pow(N, 2));
    numero_magico = (pow(N, 3) + N) / 2;
    matrizSolucion.resize(N, vector<int>(N, -1));

    cuadradoMagicoKesimo(0, 0);

    if (matrizSolucion[0][0] == -1)
    {
        cout << "-1" << endl;
    }
    else
    {
        imprimir_matriz(matrizSolucion);
    }

    return 0;
}