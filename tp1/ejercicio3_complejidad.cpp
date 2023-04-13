#include <vector>
#include <iostream>
#include <tuple>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <ctime>
using namespace std;

int n;
vector<tuple<int,int,int>> A;

void merge(vector<tuple<int, int, int>>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    vector<tuple<int, int, int>> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (get<2>(L[i]) <= get<2>(R[j])) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(vector<tuple<int, int, int>>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

void actividades(){
	mergeSort(A,0,A.size()-1);  //O(n logn) --> mergeSort
	int ultAct = 0;
    vector<int> S;
    for(int i = 0; i < A.size(); i++){
        if (get<1>(A[i]) >= ultAct){
            S.push_back(get<0>(A[i])+1);
            ultAct = get<2>(A[i]);
        }
    }

    cout << S.size();  //Para ir viendo el tamaño de la solución con cada N
    cout << endl;
}

vector<tuple<int,int,int>> construir_vector(int n){

    vector<tuple<int,int,int>> res;
    srand (time(NULL));
    tuple<int,int,int> numero;

    for(int i=0; i < n; i++){
        int fin_act = rand() % (2*n) ;
        int inic_act = rand() % 2*n;
        numero = make_tuple(i,inic_act,fin_act);
        res.push_back(numero);
    }
    return res;
}
void complejidad(){
    int n=1;
    int hasta = 50000;
    int paso = 500;
    ofstream fout;
    fout.open("datos_ej3.csv");
    fout << "n\t" << "tiempo" <<endl;
    while (n<hasta){
        vector<tuple<int,int,int>> v= construir_vector(n);

        double t0=clock();
        A = v;
        actividades();
        double t1=clock();

        double tiempo = (double (t1-t0) / CLOCKS_PER_SEC);

        fout << n << "\t" << tiempo << endl;

        n += paso;
    }
    fout.close();

}

int main(){
    complejidad();
	
	return 0;
}