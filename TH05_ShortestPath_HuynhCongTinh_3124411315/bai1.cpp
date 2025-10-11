#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <fstream>
using namespace std;

#define INF 1000000000

int main() {
    ifstream fin("dijkstra.in");
    ofstream fout("dijkstra.out");

    if (!fin.is_open()) {
        cout << "Khong mo duoc file dau vao!" << endl;
        return 0;
    }

    int n, m, s, t;
    fin >> n >> m >> s >> t;
    vector< vector< pair<int,int> > > adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
    }

    vector<int> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);

    priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > pq;

    dist[s] = 0;
    pq.push(make_pair(0, s));

    while (!pq.empty()) {
        pair<int,int> top = pq.top();
        pq.pop();

        int du = top.first;
        int u = top.second;

        if (du != dist[u]) continue;

        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    if (dist[t] == INF) {
        fout << "Khong co duong di" << endl;
        return 0;
    }

    vector<int> path;
    int v = t;
    while (v != -1) {
        path.push_back(v);
        v = parent[v];
    }
    reverse(path.begin(), path.end());

    fout << path.size() << " " << dist[t] << endl;
    for (size_t i = 0; i < path.size(); i++)
        fout << path[i] << " ";
    fout << endl;

    fin.close();
    fout.close();

    return 0;
}

