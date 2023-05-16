#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <iomanip> // std::setprecision
#include <algorithm>

using namespace std;
using ll = long long;
const ll inf = 1e18;

vector<vector<double>> g;
int C, N, R, W, U, V;

double dist(tuple<int, int> p1, tuple<int, int> p2)
{
    double dist = sqrt(pow(get<0>(p1) - get<0>(p2), 2) + pow(get<1>(p1) - get<1>(p2), 2));
    return dist;
}

int main()
{
    cin >> C;
    for (int it = 0; it < C; it++)
    {
        cin >> N >> R >> W >> U >> V;
    }
    return 0;
}