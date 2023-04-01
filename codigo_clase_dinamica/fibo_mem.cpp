#include <iostream>

using namespace std;

int fibo(int N) {
    if (N == 0) return 0;
    if (N == 1) return 1;

    int fibN_2 = 0; int fibN_1 = 1;

    while (N >= 2) {
        int fibN = fibN_2 + fibN_1;
        fibN_2 = fibN_1; fibN_1 = fibN;
        N--;
    }

    return fibN_1;
}

int main() {
    int N; cin >> N;

    cout << fibo(N) << endl;

    return 0;
}
