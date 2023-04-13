#include <iostream>
#include <vector>

using namespace std;

vector<int> precios;

void merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = precios[left + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = precios[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            precios[k] = L[i];
            i++;
        } else {
            precios[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        precios[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        precios[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

int maximo_descuento(){
    int max_desc = 0;
    mergeSort(0, precios.size() - 1);
    for(int i = 2; i < precios.size(); i = i+3){
        max_desc += precios[i];
    }
    return max_desc;
}

int main() {
    int c; 
    cin >> c;

    int n;
    int p_i;
    while (c--) {
        precios = vector<int>();
        
        cin >> n;
        while(n--){
            cin >> p_i;
            precios.push_back(p_i);
        }

        cout << maximo_descuento() << endl;
    }

    return 0;
}
