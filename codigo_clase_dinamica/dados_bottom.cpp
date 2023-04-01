#include <iostream>
#include <vector>

using namespace std;

int n, s, k;

int main() {
    cin >> n >> s >> k;

    if (s > n*k) cout << 0 << endl;
    else {

        vector<vector<int>> mem(s+1, vector<int>(k+1, 0));

        // Caso base
        for (int l=1; l<=k; l++) mem[0][l] = 1;

        // Iteramos las longitudes, desde la mas chica
        for (int i=1; i<=n; i++) {
            vector<vector<int>> mem_i(s+1, vector<int>(k+1));
            
            // Cargamos el caso base de l=0
            for (int r=0; r<=s; r++) mem_i[r][0] = 0;

            // Casos recursivos: el loop exterior tiene que ser sobre los limites
            for (int l=1; l<=k; l++) {
                for (int r=0; r<=s; r++) {
                    mem_i[r][l] = mem_i[r][l-1] + (r-l >= 0 ? mem[r-l][l] : 0);
                }
            }

            // Copiamos la matriz
            for (int r=0; r<=s; r++)
                for (int l=0; l<=k; l++)
                    mem[r][l] = mem_i[r][l];
        }

        cout << mem[s][k] << endl;
    }

    return 0;
}
