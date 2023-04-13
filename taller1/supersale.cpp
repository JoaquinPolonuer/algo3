#include <iostream>
#include <vector>

using namespace std;

int T, N, G, c_i;
vector<pair<int, int>> PW;
vector<int> C;
vector<vector<int>> dp;

int mochila(int capacidad, int indice)
{
    if (indice == PW.size())
    {
        return 0;
    }

    if (dp[capacidad][indice] != -1){
        return dp[capacidad][indice];
    }

    int opc1 = mochila(capacidad, indice + 1);
    int opc2;
    if (capacidad - PW[indice].second < 0)
    {
        opc2 = -1;
    }
    else
    {
        opc2 = mochila(capacidad - PW[indice].second, indice + 1) + PW[indice].first;
    }
    dp[capacidad][indice] = max(opc1, opc2);
    
    return dp[capacidad][indice];
}

int main()
{
    cin >> T;

    int p_i, w_i, c_i;
    while (T--)
    {
        PW = vector<pair<int,int>>();
        C = vector<int>();

        cin >> N;
        while (N--)
        {
            cin >> p_i;
            cin >> w_i;
            PW.push_back(make_pair(p_i, w_i));
        }

        cin >> G;
        while (G--)
        {
            cin >> c_i;
            C.push_back(c_i);
        }

        int solucion = 0;
        for (int i = 0; i < C.size(); i++)
        {
            c_i = C[i];
            dp = vector<vector<int>>(c_i + 1, vector<int>(PW.size() + 1, -1));
            solucion += mochila(c_i, 0);
        }

        cout << solucion << endl;
    }

    return 0;
}