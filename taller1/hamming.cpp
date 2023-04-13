#include <iostream>
#include <vector>

using namespace std;

int T, N, H;
int distancia_actual;
vector<int> cadena;

void imprimir_cadena(){
    for(int i = 0; i < cadena.size(); i++){
        cout << cadena[i];
    }
    cout << endl;
}

void hamming(int i){
    if(i == N){
        imprimir_cadena();
    }else{

        if(distancia_actual + (N- i -1) >= H){
            cadena[i] = 0;
            hamming(i+1);
        }

        if(distancia_actual + 1 <= H){
            cadena[i] = 1;
            distancia_actual += 1;
            hamming(i+1);
            distancia_actual -= 1;
        }
    }
}

int main()
{
    cin >> T;

    for(int i = 0; i < T; i++)
    {
        cin >> N;
        cin >> H;

        distancia_actual = 0;
        cadena = vector<int>(N, 0);
        hamming(0);
        if (i != T-1){
            cout << endl;
        }
    }

    return 0;
}

