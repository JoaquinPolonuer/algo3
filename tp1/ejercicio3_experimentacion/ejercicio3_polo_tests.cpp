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



vector<int> read_input(int size)
{
    vector<int> input(size);
    string file_name = "inputs/input_random_" + to_string(size);
    cout << file_name << endl;
    ifstream read_file(file_name);
    for (int i = 0; i < size; i++)
        read_file >> input[i];
    read_file.close();
    return input;
}

double measure(vector<int> a)
{
    auto start = chrono::high_resolution_clock::now();
    actividades();
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;
    return diff.count();
}

int main()
{
    int repeat = 10;
    ofstream output_file;
    output_file.open("runtime_random.csv");
    output_file << "n,time\n";

    int limit = 1 << 27;
    for (int n = 65536; n < limit; n *= 2)
    {
        vector<int> input = read_input(n);

        double counter = 0;
        for (int ignore = 0; ignore < repeat; ignore++)
            counter += measure(input);

        output_file << n << "," << counter / repeat << endl;
    }

    output_file.close();
    return 0;
}
