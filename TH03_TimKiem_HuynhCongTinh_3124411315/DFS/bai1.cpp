#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int n, x;
vector< vector<int> > adj;
vector<int> visited;
vector<int> result;

void dfs(int u) {
    visited[u] = 1;
    result.push_back(u);
    for (size_t i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (!visited[v]) dfs(v);
    }
}

int main() {
    ifstream fin("LienThongDFS.INP");
    ofstream fout("LienThongDFS.OUT");

    if (!fin) return 0;

    fin >> n >> x;
    adj.assign(n + 1, vector<int>()); 
    visited.assign(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        int v;
        while (fin >> v) {
            if (v == -1) break;
            adj[i].push_back(v);
        }
    }

    dfs(x);

    fout << result.size() << "\n";
    for (size_t i = 0; i < result.size(); ++i) {
        if (i) fout << " ";
        fout << result[i];
    }
    fout << "\n";

    fin.close();
    fout.close();
    return 0;
}

