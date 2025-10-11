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

vector<int> dijkstra(int n, int start, vector<vector<Edge> > &adj, vector<int> &parent) {
    vector<int> dist(n + 1, INF);
    parent.assign(n + 1, -1);

    // priority_queue <pair<khoang cach, dinh>, ... >
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

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
    ifstream fin("priorityqueue.in");
    ofstream fout("priorityqueue.out");

    if (!fin.is_open()) {
        cout << "Khong mo duoc file dau vao!\n";
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

    vector<int> parentS, parentX;
    vector<int> distS = dijkstra(n, s, adj, parentS);
    vector<int> distX = dijkstra(n, x, adj, parentX);

    if (distS[x] == INF || distX[t] == INF) {
        fout << "Khong co duong di" << endl;
        fin.close();
        fout.close();
        return 0;
    }

    int total = distS[x] + distX[t];
    fout << total << endl;

    vector<int> path1;
    for (int v = x; v != -1; v = parentS[v])
        path1.push_back(v);
    reverse(path1.begin(), path1.end());

    vector<int> path2;
    for (int v = t; v != -1; v = parentX[v])
        path2.push_back(v);
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

