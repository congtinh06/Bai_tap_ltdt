#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

int main() {
    ifstream fin("floyd.in");
    ofstream fout("floyd.out");

    if (!fin) {
        cout << "Khong mo duoc file dau vao!" << endl;
        return 0;
    }

    int n, m;
    fin >> n >> m;

    vector<vector<int> > dist(n + 1, vector<int>(n + 1, INF));

    for (int i = 1; i <= n; i++)
        dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        if (w < dist[u][v]) { 
            dist[u][v] = w;
            dist[v][u] = w; // d? th? vô hu?ng
        }
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] == INF) fout << "0 ";
            else fout << dist[i][j] << " ";
        }
        fout << endl;
    }

    fin.close();
    fout.close();
    return 0;
}

