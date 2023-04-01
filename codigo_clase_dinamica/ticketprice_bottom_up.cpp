#include <iostream>
#include <vector>

using namespace std;

int N, W;
vector<int> dp;
vector<vector<int>> lp, ls;

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

    // Creo la memoria en la semana W+1-esima
    dp.resize(N+1, 0);

    // Voy calculando el resto
    for (int i=W; i>=0; i--) {
        // Creo un vector temporal donde calcular la nueva fila
        vector<int> fila_i = vector<int>(N+1);

        for (int n=0; n<=N; n++) {
            // Esta es la formula recursiva
            int best = -1;
            for (int j=0; j<lp[i].size(); j++) {
                int p = lp[i][j]; int s = ls[i][j];
                best = max(best, p * min(n, s) + dp[n - min(n, s)]);
            }
            fila_i[n] = best;
        }

        // Copio el resultado al vector
        for (int n=0; n<=N; n++) dp[n] = fila_i[n];
    }
    
    cout << dp[N] << endl;

    return 0;
}
