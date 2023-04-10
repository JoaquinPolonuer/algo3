#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
using namespace std;

int n, k;
vector<vector<int>> cm;
vector<int> sumasFil;
vector<int> sumasCol;
vector<int> sumasDiag;
vector<bool> numeros;
int m;


void imprimir_matriz()
{
    for (int fila = 0; fila < n; fila++)
    {
        for (int columna = 0; columna < n; columna++)
        {
            cout << cm[fila][columna] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void cuadradoMagicoKesimo(int i, int j){
    if (j==n){
        return cuadradoMagicoKesimo(i+1,0);
    }
    if(i==n){
        k--;
        if(k==0){
            imprimir_matriz();
        }
    }

    for (int l = 1; l <= n * n; l++) {
        bool valido = true;
        if (numeros[l - 1] == 1){
            valido = false;
        }
        if (sumasFil[i] + l > m){
            valido = false;
        }
        if (j == n - 1 && sumasFil[i] + l != m) {
            valido = false;
        }
        if (sumasCol[j] + l > m){
            valido = false;
        }
        if (i == n - 1 && sumasCol[j] + l != m){
            valido = false;
        }

        if (i==j && sumasDiag[0] + l > m){
            valido = false;
        }

        if (i==j && i == n - 1 && sumasDiag[0] + l != m){
            valido = false;
        }

        if (i==n-j-1 && sumasDiag[1] + l > m) {
            valido = false;
        }

        if (i==n-j-1 && i == n - 1 && sumasDiag[1] + l != m) {
            valido = false;
        }

        if(valido){
            cm[i][j] = l;
            numeros[l - 1] = 1;
            sumasFil[i] += l;
            sumasCol[j] += l;
            if (i==j) {
                sumasDiag[0] += l;
            }
            if (i==n-j-1) {
                sumasDiag[1] += l;
            }

           cuadradoMagicoKesimo(i,j+1);

            numeros[l - 1] = 0;
            sumasFil[i] -= l;
            sumasCol[j] -= l;
            if (i==j) sumasDiag[0] -= l;
            if (i==n-j-1) sumasDiag[1] -= l;
        }
    }
}

int main() {
    cout << "Cuadrado magico:" << endl;
    
    cin >> n >> k;
    cm.resize(n,vector<int>(n,0));
    sumasDiag.resize(2, 0);
    sumasFil.resize(n, 0);
    sumasCol.resize(n, 0);
    numeros.resize(pow(n, 2));
    m = (pow(n, 3) + n) / 2;

    cuadradoMagicoKesimo(0,0);

    
    return 0;
}

