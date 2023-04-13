#include <iostream>
#include <vector>

using namespace std;

int T, n, m;
vector<pair<int, int>> fichas;
vector<bool> fichas_utilizadas;
pair<int, int> I, D;

bool dominos(int i, int r1)
{
    if (i == n)
    {
        return r1 == D.first;
    }

    bool puedo = false;

    for (int j = 0; j < fichas.size(); j++)
    {
        if (fichas_utilizadas[j])
        {
            continue;
        }

        fichas_utilizadas[j] = true;
        if (fichas[j].first == r1)
        {
            puedo = puedo or dominos(i + 1, fichas[j].second);
        }

        if (fichas[j].second == r1)
        {
            puedo = puedo or dominos(i + 1, fichas[j].first);
        }
        fichas_utilizadas[j] = false;
    }

    return puedo;
}

int main()
{
    int l, r;
    while (cin >> n)
    {
        cin >> m;

        cin >> l >> r ;
        I = make_pair(l, r);

        cin >> l >> r;
        D = make_pair(l, r);

        fichas = vector<pair<int, int>>();
        for (int i = 0; i < m; i++)
        {
            cin >> l >> r;
            fichas.push_back(make_pair(l, r));
        }

        fichas_utilizadas = vector<bool>(fichas.size(), false);

        if (dominos(0, I.second))
        {
            cout << "YES";
        }
        else
        {
            cout << "NO";
        }
        cout << endl;
    }

    return 0;
}
