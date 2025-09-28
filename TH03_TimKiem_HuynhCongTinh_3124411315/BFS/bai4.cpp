	#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int n;

int bfs_count(const vector< vector<int> >& adj, int start, bool skip_edge, int skip_u, int skip_v, int skip_vertex) {
    if (start == skip_vertex) return 0;
    vector<int> visited(n + 1, 0);
    queue<int> q;
    visited[start] = 1;
    q.push(start);
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ++cnt;
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (v == skip_vertex) continue;
            if (skip_edge) {
                if ((u == skip_u && v == skip_v) || (u == skip_v && v == skip_u)) continue;
            }
            if (!visited[v]) {
                visited[v] = 1;
                q.push(v);
            }
        }
    }
    return cnt;
}

int count_components(const vector< vector<int> >& adj, int skip_vertex) {
    vector<int> visited(n + 1, 0);
    int comps = 0;
    for (int i = 1; i <= n; ++i) {
        if (i == skip_vertex) continue;
        if (!visited[i]) {
            comps++;
            queue<int> q;
            visited[i] = 1;
            q.push(i);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (size_t j = 0; j < adj[u].size(); ++j) {
                    int v = adj[u][j];
                    if (v == skip_vertex) continue;
                    if (!visited[v]) {
                        visited[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
    }
    return comps;
}

int main() {
    ifstream fin("CanhCauDinhKhop.INP");
    ofstream fout("CanhCauDinhKhop.OUT");

    int x, y, z;
    fin >> n >> x >> y >> z;
    string line;
    getline(fin, line);
    vector< vector<int> > adj(n + 1);

    for (int i = 1; i <= n; i++) {
        if (!getline(fin, line)) line = "";
        istringstream iss(line);
        int v;
        while (iss >> v) {
            if (v == -1) break;
            if (v >= 1 && v <= n) adj[i].push_back(v);
        }
    }

    bool is_bridge = false;
    if (x != y && x >= 1 && x <= n && y >= 1 && y <= n) {
        bool adjacent = false;
        for (size_t i = 0; i < adj[x].size(); i++) if (adj[x][i] == y) adjacent = true;
        for (size_t i = 0; i < adj[y].size(); i++) if (adj[y][i] == x) adjacent = true;
        if (adjacent) {
            vector<int> visited(n + 1, 0);
            queue<int> q;
            visited[x] = 1; q.push(x);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (size_t i = 0; i < adj[u].size(); i++) {
                    int v = adj[u][i];
                    if ((u == x && v == y) || (u == y && v == x)) continue;
                    if (!visited[v]) {
                        visited[v] = 1;
                        q.push(v);
                    }
                }
            }
            if (!visited[y]) is_bridge = true;
        }
    }

    int comps_before = count_components(adj, -1);
    int comps_after = count_components(adj, z);
    bool is_articulation = (z >= 1 && z <= n && comps_after > comps_before);

    if (is_bridge) fout << "canh cau\n";
    else fout << "khong la canh cau\n";

    if (is_articulation) fout << "dinh khop\n";
    else fout << "khong la dinh khop\n";

    fin.close();
    fout.close();
    return 0;
}

