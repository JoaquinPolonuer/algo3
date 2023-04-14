#include <vector>
#include <iostream>
using namespace std;

long long int c, r, n, m;
vector<long long int> v;
vector<long long int> memo;  //Para la posición i: 0 i no es un resto de la iteración anterior, 1 i es un resto de la iteración anterior

long long int potencia_modular(long long int a, long long int k){
    if (k == 0){
        return 1;
    }else{
        long long int aux = potencia_modular(a, k / 2) % m;
        if(k%2==0){
            return (aux*aux)%m;
        }else{
            return (((aux*aux)%m)*a)%m;
        }
    }
}

long long int modulo_positivo(long long int a){
    return (m + (a % m)) % m;
}

bool operaciones(){
    for(int j=1;j<v.size();j++){
        vector<int> restos;
        for(int k=0;k<memo.size();k++){
            if(memo[k]==1){
                restos.push_back(k);
            }
        }
        memo = vector<long long int>(m,0);
        for(int resto_ant : restos){
            long long int suma = modulo_positivo(resto_ant+v[j]);
            long long int mult = modulo_positivo(resto_ant*v[j]);
            long long int resta = modulo_positivo(resto_ant-v[j]);
            long long int pot = modulo_positivo(potencia_modular(resto_ant,v[j]));
            //cout << "Iteracion " << j << " S, M, R, P:" << suma << " " << mult << " " << resta << " " << pot << " " << endl;
            memo[suma]=1;
            memo[mult]=1;
            memo[resta]=1;
            memo[pot]=1;
        }
    }
    return (memo[r]==1);
}

int main(){
    cin >> c;
    for(long long int j=0;j<c;j++){
        cin >> n >> r >> m;
        v = vector<long long int>();
        for(long long int k=0;k<n;k++){
            long long int elem;
            cin >> elem;
            elem = modulo_positivo(elem);
            v.push_back(elem);
        }
        memo = vector<long long int>(m,0);
        memo[modulo_positivo(v[0])]= 1;
        bool res = operaciones();
        if(res){
            cout << "Si" << endl;
        }else{
            cout << "No" << endl;
        }
    }
    return 0;
}