#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
using namespace std;
vector<vector<int>> cuadradoMagicoKesimo(int n, int i, int j, vector<vector<int>>& cm,int k,vector<int>& numeros, vector<int>& sumasFil, vector<int>& sumasCol, tuple<int,int>& sumasDiag){
    if (j==n){
        return cuadradoMagicoKesimo(n,i+1,0,cm,k,numeros,sumasFil,sumasCol,sumasDiag);
    }
    if(i==n){
        k=k-1;
        if(k==0){
            return cm;
        }else{
            //return cuadradoMagicoKesimo(n,0,0,cm,k,numeros,sumasFil,sumasCol,sumasDiag); //esto siempre daría el primer CM
        }
    }
    int m = (n*n*n+n)/2;
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

        if (i==j && get<0>(sumasDiag) + l > m){
            valido = false;
        }

        if (i==j && i == n - 1 && get<0>(sumasDiag) + l != m){
            valido = false;
        }

        if (i==n-j-1 && get<1>(sumasDiag) + l > m) {
            valido = false;
        }

        if (i==n-j-1 && i == n - 1 && get<1>(sumasDiag) + l != m) {
            valido = false;
        }

        if(valido){
            cm[i][j] = l;
            numeros[l - 1] = 1;
            sumasFil[i] += l;
            sumasCol[j] += l;
            if (i==j) {
                get<0>(sumasDiag) += l;
            }
            if (i==n-j-1) {
                get<1>(sumasDiag) += l;
            }

            vector<vector<int>> sig = cuadradoMagicoKesimo(n,i,j+1,cm,k,numeros,sumasFil,sumasCol,sumasDiag);

            numeros[l - 1] = 0;
            sumasFil[i] -= l;
            sumasCol[j] -= l;
            if (i==j) get<0>(sumasDiag) -= l;
            if (i==n-j-1) get<1>(sumasDiag) -= l;
        }
    }
    vector<vector<int>> error(1,vector<int>(1,-1));
    return cm;
}
/*
vector<int> v = {3,1,5,2,1};
int n = v.size();

vector<char> pd(int i, int w, vector<char> acum, int res){
    if(i==n){
        if(res==w){
            return acum;
        }else{
            return {};
        }
    }

    vector<char> s(acum);
    s.push_back('s');

    vector<char> suma = pd(i+1,w,s,res+v[i]);
    if(!suma.empty()){
        return suma;
    }

    vector<char> m(acum);
    m.push_back('m');

    vector<char> prod = pd(i+1,w,m,res*v[i]);
    if(!prod.empty()){
        return prod;
    }

    vector<char> p(acum);
    p.push_back('p');
    vector<char> pot = pd(i+1,w,p,pow(res,v[i]));
    if(!pot.empty()){
        return pot;
    }
}
*/
int main() {
    std::cout << "Cuadrado magico:" << std::endl;
    /*
    vector<char> res = pd(1,400,{},v[0]);
    for(auto elem : res){
        cout << elem;
    }
     */
    int n=3;
    vector<vector<int>> cuadrado(n,vector<int>(n));
    vector<int> numeros(n*n,0);
    vector<int> sumasFilas(n,0);
    vector<int> sumasColumnas(n,0);
    tuple<int,int> sumasDiagonales(0,0);

    vector<vector<int>> m = cuadradoMagicoKesimo(n,0,0,cuadrado,2,numeros,sumasFilas,sumasColumnas,sumasDiagonales);

    for (const auto& fila:m) {
        for(auto elem : fila){
            printf("%d",elem);
            printf(" ");
        }
        printf("\n");
    }
    return 0;
}

