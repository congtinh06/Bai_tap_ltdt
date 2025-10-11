#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
using namespace std;

const int INF = 1000000000;

struct Edge {
    int v, w;
};

vector<int> dijkstra(int n, int start, const vector<vector<Edge> > &adj, vector<int> &parent) {
    vector<int> dist(n + 1, INF);
    parent.assign(n + 1, -1);
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq;

    dist[start] = 0;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        int du = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (du != dist[u]) continue;

        for (int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i].v;
            int w = adj[u][i].w;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return dist;
}

int main() {
    ifstream fin("ngannhat.in");
    ofstream fout("ngannhat.out");

    if (!fin) {
        cout << "Khong mo duoc file dau vao!" << endl;
        return 0;
    }

    int n, m, s, t, x;
    fin >> n >> m >> s >> t >> x;

    vector<vector<Edge> > adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        Edge e;
        e.v = v;
        e.w = w;
        adj[u].push_back(e);
    }

    vector<int> parent1, parent2;
    vector<int> dist1 = dijkstra(n, s, adj, parent1);
    vector<int> dist2 = dijkstra(n, x, adj, parent2);

    if (dist1[x] == INF || dist2[t] == INF) {
        fout << "Khong co duong di" << endl;
        return 0;
    }

    int tong = dist1[x] + dist2[t];
    fout << tong << endl;

    vector<int> path1;
    for (int v = x; v != -1; v = parent1[v]) path1.push_back(v);
    reverse(path1.begin(), path1.end());

    vector<int> path2;
    for (int v = t; v != -1; v = parent2[v]) path2.push_back(v);
    reverse(path2.begin(), path2.end());

    vector<int> path = path1;
    for (int i = 1; i < (int)path2.size(); i++)
        path.push_back(path2[i]);

    for (int i = 0; i < (int)path.size(); i++)
        fout << path[i] << " ";
    fout << endl;

    fin.close();
    fout.close();
    return 0;
}

