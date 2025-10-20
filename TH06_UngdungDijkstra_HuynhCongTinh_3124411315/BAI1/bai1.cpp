#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

struct Circle {
    double x, y, r;
};

double distance_between(const Circle &a, const Circle &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin.is_open() || !fout.is_open()) {
        cout << "Khong mo duoc file!" << endl;
        return 1;
    }

    int N, S, T;
    fin >> N >> S >> T;

    vector<Circle> c(N + 1);
    for (int i = 1; i <= N; i++)
        fin >> c[i].x >> c[i].y >> c[i].r;

    vector<vector<int>> adj(N + 1);
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            double d = distance_between(c[i], c[j]);
            double diff = fabs(d - (c[i].r + c[j].r));
            if (diff >= 50 && diff <= 60) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    vector<int> dist(N + 1, -1), parent(N + 1, -1);
    queue<int> q;
    dist[S] = 0;
    q.push(S);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    if (dist[T] == -1) {
        fout << 0;
        fin.close();
        fout.close();
        return 0;
    }

    fout << 1 << "\n";
    fout << dist[T] << " " << dist[T] + 1 << "\n";

    vector<int> path;
    for (int v = T; v != -1; v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    for (int v : path)
        fout << v << " ";
    fout << "\n";

    fin.close();
    fout.close();

    return 0;
}
