#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <algorithm>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll inf = 1e18;

ll N, M;

ll voto;
vector<vector<ll>> vecinos;
vector<vector<ll>> capacidad_residual;
ll i, j;

ll bfs(ll s, ll t, vector<ll>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<ll, ll>> q;
    q.push({s, inf});

    while (!q.empty()) {
        ll cur = q.front().first;
        ll flow = q.front().second;
        q.pop();

        for (ll next : vecinos[cur]) {
            if (parent[next] == -1 && capacidad_residual[cur][next]) {
                parent[next] = cur;
                ll delta_p = min(flow, capacidad_residual[cur][next]);
                if (next == t)
                    return delta_p;
                q.push({next, delta_p});
            }
        }
    }

    return 0;
}

ll flujo_maximo(ll s, ll t) {
    ll flow = 0;
    vector<ll> parent(N+2);
    ll delta_p;

    while (delta_p = bfs(s, t, parent)) {
        flow += delta_p;
        ll cur = t;
        while (cur != s) {
            ll prev = parent[cur];
            capacidad_residual[prev][cur] -= delta_p;
            capacidad_residual[cur][prev] += delta_p;
            cur = prev;
        }
    }

    return flow;
}


int main()
{
    // S = 0, T = N+1
    while (true)
    {
        scanf("%lld %lld", &N, &M);

        if (N == 0 && M == 0)
        {
            break;
        }

        vecinos = vector<vector<ll>>(N + 2);
        capacidad_residual = vector<vector<ll>>(N + 2, vector<ll>(N + 2, 0));

        for (ll i = 1; i <= N; i++)
        {
            scanf("%lld",&voto);

            ll conexion;
            if (voto == 0)
            {
                conexion = 0;
            }
            else
            {
                conexion = N + 1;
            }

            vecinos[conexion].push_back(i);
            vecinos[i].push_back(conexion);

            capacidad_residual[conexion][i] = 1;
            capacidad_residual[i][conexion] = 1;
        }

        for (ll k = 0; k < M; k++)
        {
            scanf("%lld %lld", &i, &j);

            vecinos[i].push_back(j);
            vecinos[j].push_back(i);

            capacidad_residual[i][j] = 1;
            capacidad_residual[j][i] = 1;
        }

        cout << flujo_maximo(0, N + 1) << endl;
    }

    return 0;
}