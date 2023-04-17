#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int N;
vector<tuple<int, int, int>> A;

void bucketSort()
{
    vector<vector<tuple<int, int, int>>> buckets(2 * A.size() + 1);

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

    cout << indices.size();
    cout << endl;

    for (int i = 0; i < indices.size(); i++)
    {
        cout << indices[i] << " ";
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
    actividades();

    return 0;
}
