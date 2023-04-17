#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace std;

vector<int> read_input(int size) {
    vector<int> input(size); string file_name = "inputs/input_" + to_string(size);
    cout << file_name << endl;
    ifstream read_file(file_name);
    for (int i=0; i<size; i++) read_file >> input[i];
    read_file.close();
    return input;
}

double measure(vector<int> a) {
    auto start = chrono::high_resolution_clock::now();

    int n = a.size();
    for (int i=0; i<n; i++) {
        if (a[i] < n) {
            if (a[a[i]] != a[i]) {
                swap(a[a[i]], a[i]); i--;
            }
        }
    }

    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;
    return diff.count();
}

int main() {
    int repeat = 10;
    ofstream output_file; output_file.open("runtime.csv");
    output_file << "n,time\n";
    
    int limit = 1<<27;
    for (int n=65536; n<limit; n*=2) {
        vector<int> input = read_input(n);

        double counter = 0;
        for (int ignore=0; ignore<repeat; ignore++) counter += measure(input);
        
        output_file << n << "," << counter / repeat << endl;
    }

    output_file.close();
    return 0;
}
