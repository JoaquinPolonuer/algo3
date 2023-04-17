#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

int N;
vector<tuple<int, int, int>> A;

void bucketSort()
{
    vector<vector<tuple<int,int,int>>> buckets(2*A.size()+1);

    for (auto a : A)
    {
        buckets[get<2>(a)].push_back(a);
    }
    int indice = 0;
    for (auto bucket : buckets)
    {
        for (int i = 0; i < bucket.size(); i++)
        {
            A[indice] = bucket[i];
            indice++;
        }
    }
}

void actividades()
{
    bucketSort();

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

    // cout << indices.size();
    // cout << endl;

    // for (int i = 0; i < indices.size(); i++)
    // {
    //     cout << indices[i] << " ";
    // }
}


double measure()
{
    auto start = chrono::high_resolution_clock::now();
    actividades();
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;
    return diff.count();
}

vector<tuple<int, int, int>> construir_vector_random(int n)
{

    vector<tuple<int, int, int>> res;
    srand(time(NULL));
    tuple<int, int, int> numero;

    for (int i = 0; i < n; i++)
    {
        int fin_act = rand() % (2 * n);
        int inic_act = rand() % (fin_act + 1);
        numero = make_tuple(i + 1, inic_act, fin_act);
        res.push_back(numero);
    }
    return res;
}

vector<tuple<int, int, int>> construir_vector_iguales(int n)
{

    vector<tuple<int, int, int>> res;
    srand(time(NULL));
    tuple<int, int, int> numero;

    int fin_act = rand() % (2 * n);
    int inic_act = rand() % (fin_act + 1);

    for (int i = 0; i < n; i++)
    {
        numero = make_tuple(i + 1, inic_act, fin_act);
        res.push_back(numero);
    }
    return res;
}

vector<tuple<int, int, int>> construir_vector_acotado(int n)
{

    vector<tuple<int, int, int>> res;
    srand(time(NULL));
    tuple<int, int, int> numero;

    for (int i = 0; i < n; i++)
    {
        int fin_act = rand() % n;
        int inic_act = rand() % (fin_act + 1);
        numero = make_tuple(i + 1, inic_act, fin_act);
        res.push_back(numero);
    }
    return res;
}

vector<tuple<int, int, int>> construir_vector_sorted(int n)
{

    vector<tuple<int, int, int>> res;
    srand(time(NULL));
    tuple<int, int, int> numero;

    for(int i=0; i < 2*n; i+=2){
        int fin_act = i+1;
        int inic_act = i;
        numero = make_tuple(i + 1, inic_act, fin_act);
        res.push_back(numero);
    }
    return res;
}

int main()
{
    int repeat = 5;
    ofstream output_file;

    // output_file.open("runtime_random.csv");
    // output_file.open("runtime_sorted.csv");
    // output_file.open("runtime_acotado.csv");
    output_file.open("runtime_iguales.csv");


    output_file << "n,time\n";

    int limit = 1 << 27;
    for (int n = 65536; n < limit; n *= 2)
    {
        // A = construir_vector_random(n);
        // A = construir_vector_sorted(n);
        // A = construir_vector_acotado(n);
        A = construir_vector_iguales(n);

        double counter = 0;
        for (int ignore = 0; ignore < repeat; ignore++)
            counter += measure();

        output_file << n << "," << counter / repeat << endl;
    }

    output_file.close();
    return 0;
}
