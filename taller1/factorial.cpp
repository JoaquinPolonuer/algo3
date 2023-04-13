#include <iostream>
#include <vector>

using namespace std;

int mejorK(int n)
{
    if(n == 0){
        return 0;
    }
    int i = 1;
    int factorial = 1;
    for (int i = 1; factorial * i <= n; i++)
    {
        factorial = factorial * i;
    }
    return 1 + mejorK(n - factorial);
}

int main()
{
    int n;
    while (cin >> n)
    {
        cout << mejorK(n);
        cout << endl;
    }

    return 0;
}
