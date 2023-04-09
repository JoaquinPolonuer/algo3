#include <iostream>
#include <vector>
#include<tuple>

using namespace std;

int N;
vector<tuple<int, int,int>> A;

int main()
{
    cin >> N;

    int s_i, t_i;
    for (int i = 0; i < N; i++)
    {
        cin >> s_i >> t_i;
        A.push_back(make_tuple(i, s_i, t_i));
    }

    // TODO:
    // ordenar_actividades(A);

    int fin_ultima_actividad = 0;
    vector<int> indices;
    for(int i = 0; i < A.size(); i++){
        if (get<1>(A[i]) >= fin_ultima_actividad){
            indices.push_back(get<0>(A[i]));
            fin_ultima_actividad = get<2>(A[i]);
        }
    }

    cout << indices.size();
    cout << endl;

    for(int i = 0; i < indices.size(); i++){
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


