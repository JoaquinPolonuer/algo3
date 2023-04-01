#include <iostream>

using namespace std;

int fibo(int N) {
    int mem[N+1];
    mem[0] = 0; mem[1] = 1;

    for (int i=2; i<=N; i++) mem[i] = mem[i-1] + mem[i-2];
    
    return mem[N];
}

int main() {
    int N; cin >> N;

    cout << fibo(N) << endl;

    return 0;
}
