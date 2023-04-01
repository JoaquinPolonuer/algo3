#include <iostream>
#include <vector>

using namespace std;

int N, W;
vector<vector<int>> dp;
vector<vector<int>> lp, ls;

int TP(int i, int n) {
    if (i==W+1) return 0;
    if (dp[i][n] != -1) return dp[i][n];

    int best = -1;
    for (int j=0; j<lp[i].size(); j++) {
        int p = lp[i][j]; int s = ls[i][j];
        best = max(best, p * min(n, s) + TP(i+1, n - min(n, s)));
    }

    return dp[i][n] = best;
}

int main() {
    // Leo la entrada
    cin >> N >> W;

    lp.resize(W+1); ls.resize(W+1);
    for (int i=0; i<=W; i++) {
        int k_i; cin >> k_i;

        int s_j, p_j;
        for (int j=0; j<k_i; j++) {cin >> p_j; lp[i].push_back(p_j);}
        for (int j=0; j<k_i; j++) {cin >> s_j; ls[i].push_back(s_j);}
    }

    // Inicializo la memoria y llamo a la solucion
    dp.resize(W+1, vector<int>(N+1, -1));
    cout << TP(0, N) << endl;

    return 0;
}
