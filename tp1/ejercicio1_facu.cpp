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

vector<vector<int>> matriz;

void imprimir_matriz(vector<vector<int>> M)
{
    for (int fila = 0; fila < M.size(); fila++)
    {
        for (int columna = 0; columna < M.size(); columna++)
        {
            cout << M[fila][columna] << " ";
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
            for(int i=0;i<cm.size();i++){
                for(int j=0;j<cm.size();j++){
                    matriz[i][j]=cm[i][j];
                }
            }
        }
    }

    for (int l = 1; l <= n * n; l++) {
        bool valido = true;
        if (                            //podas:
            (numeros[l - 1] == 1) or
            (sumasFil[i] + l > m) or
            (j == n - 1 && sumasFil[i] + l != m) or
            (sumasCol[j] + l > m) or
            (i == n - 1 && sumasCol[j] + l != m) or
            (i==j && sumasDiag[0] + l > m) or
            (i==j && i == n - 1 && sumasDiag[0] + l != m) or
            (i==n-j-1 && sumasDiag[1] + l > m) or
            (i==n-j-1 && i == n - 1 && sumasDiag[1] + l != m) or
            (k<0)
            ) 
        {
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
    cin >> n >> k;
    cm.resize(n,vector<int>(n,0));
    matriz.resize(n,vector<int>(n,-1));
    sumasDiag.resize(2, 0);
    sumasFil.resize(n, 0);
    sumasCol.resize(n, 0);
    numeros.resize(pow(n, 2));
    m = (pow(n, 3) + n) / 2;

    cuadradoMagicoKesimo(0,0);

    if(matriz[0][0]==-1){
        cout << "-1" << endl;
    }else{
        imprimir_matriz(matriz);
    }
    return 0;
}

