#include <iostream>

using namespace std;

// Completar
int mod_bin_exp(int x, int y, int n) {
    if (y == 0)
    {
        return 1;
    }
    else
    {
        int aux = mod_bin_exp(x, y / 2, n) % n;
        if (y % 2 == 0)
        {
            return (aux * aux) % n;
        }
        else
        {
            return ((aux * aux % n) * x) % n;
        }
    }
}

int main() {
    int c; cin >> c;

    while (c--) {
        int x, y, n; cin >> x >> y >> n;
        cout << mod_bin_exp(x, y, n) << endl;
    }

    return 0;
}
