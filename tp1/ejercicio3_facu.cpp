#include <vector>
#include <iostream>
#include <tuple>
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

    cout << S.size();
    cout << endl;

    for(int i = 0; i < S.size(); i++){
        cout << S[i] << " ";
    }
}

int main(){
	cin >> n;
	A.resize(n);
	int si, ti;
	for(int i=0;i<n;i++){
		cin >> si;
		cin >> ti;
		A[i] = make_tuple(i,si,ti);
	}

	actividades();
	
	return 0;
}