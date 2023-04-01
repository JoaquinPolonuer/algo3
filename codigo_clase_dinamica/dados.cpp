#include <iostream>
#include <vector>

using namespace std;

vector<vector<vector<int>>> dp;
int n, k, s;

int DI(int i, int r, int l) {
    if (r<0 || l<1) return 0;
    if (i == 0) return r == 0 ? 1 : 0;
    if (dp[i][r][l] != -1) return dp[i][r][l];

    return dp[i][r][l] = DI(i+1, r-l, l) + DI(i, r, l-1);
}

int solve() {
    if (s > n*k) return 0;

    dp.resize(n+1, vector<vector<int>>(s+1, vector<int>(k+1, -1)));
    return DI(n, s, k);
}

int main() {
    cin >> n >> k >> s;
    cout << solve() << endl;
    return 0;
}
