#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <bits/stdc++.h>

using namespace std;
int N,M,K,P;
const int INF = 1e9;

vector<vector<int>> capacity;
vector<vector<int>> adj;

/*
 * Implementación de Edmonds-Karp prestada de:
 *  https://cp-algorithms.com/graph/edmonds_karp.html#implementation
 * */

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(N+2);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}



int main(){
    ios_base::sync_with_stdio(false); //Hack para agilizar lectura de datos
    cin.tie(NULL);
    while(true)
    {
        cin >> N >> M;
        K = N;   //Nodo kruskal = fuente
        P = N+1; //Nodo prim    = sumidero

        if(N==0 and M==0) return 0;

        capacity = vector<vector<int>>(N+2,vector<int>(N+2,1));
        adj = vector<vector<int>>(N+2);

        for(int i=0;i<N;i++)
        {
            int voto;
            cin >> voto;
            if(voto == 1)
            {
                adj[K].push_back(i);
                adj[i].push_back(K);
            }else
            {
                adj[i].push_back(P);
                adj[P].push_back(i);
            }
        }
        for(int k = 0;k<M;k++)
        {
            int i, j;
            cin >> i >> j;
            i--;j--;
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
        //Busco el valor del corte mínimo en G.
        cout << maxflow(K,P) << "\n";
    }
}