#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int N;
vector<tuple<int, int, int>> A;

void merge(vector<tuple<int, int, int>> &arr, int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;
    vector<tuple<int, int, int>> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (get<2>(L[i]) <= get<2>(R[j]))
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(vector<tuple<int, int, int>> &arr, int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

int main()
{
    cin >> N;

    int s_i, t_i;
    for (int i = 0; i < N; i++)
    {
        cin >> s_i >> t_i;
        A.push_back(make_tuple(i + 1, s_i, t_i));
    }

    mergeSort(A, 0, A.size() - 1);

    int fin_ultima_actividad = 0;
    vector<int> indices;
    for (int i = 0; i < A.size(); i++)
    {
        if (get<1>(A[i]) >= fin_ultima_actividad)
        {
            indices.push_back(get<0>(A[i]));
            fin_ultima_actividad = get<2>(A[i]);
        }
    }

    cout << indices.size();
    cout << endl;

    for (int i = 0; i < indices.size(); i++)
    {
        cout << indices[i] << " ";
    }
    return 0;
}

// TENER EN CUENTA:
// Falta hacer el algoritmo de ordena el arreglo por final de la actividad,
// asi que no pude probarlo con el caso de prueba que dan en la consigna

// No se si entendi el output esperado. Interprete que la segunda linea tiene
// que tener los indices de las actividades realizadas y lo hice de esa forma.

// Creo que el algoritmo es correcto. La dificultad seguramente este en
// demostrarlo
