#include <vector>
#include <iostream>
#include <tuple>
using namespace std;

int n;
vector<tuple<int, int, int>> A;

void bucketSort(vector<tuple<int,int,int>>& v){
    int max_val = 0;
    for (int i = 0; i < v.size(); i++) {
        max_val = max(max_val, get<2>(v[i]));
    }

    vector<vector<tuple<int,int,int>>> buckets(max_val+1);
    for(auto t : v){
        buckets[get<2>(t)].push_back(t);
    }
    int indice=0;
    for(int i=0;i<=max_val;i++){
        for(int j=0;j<buckets[i].size();j++){
            v[indice]=buckets[i][j];
            indice++;
        }
    }
}

void actividades()
{
    bucketSort(A); // O(n) --> bucketSort
    int ultAct = 0;
    vector<int> S;
    for (int i = 0; i < A.size(); i++)
    {
        if (get<1>(A[i]) >= ultAct)
        {
            S.push_back(get<0>(A[i]) + 1);
            ultAct = get<2>(A[i]);
        }
    }

    cout << S.size();
    cout << endl;

    for (int i = 0; i < S.size(); i++)
    {
        cout << S[i] << " ";
    }
}

int main()
{
    cin >> n;
    A.resize(n);
    int si, ti;
    for (int i = 0; i < n; i++)
    {
        cin >> si;
        cin >> ti;
        A[i] = make_tuple(i, si, ti);
    }

    actividades();

    return 0;
}