#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int n;
vector<vector<int> > adj;
vector<int> path;
vector<int> visited;
bool found = false;

void Try(int k) {
    if (found) return;
    for (int v = 1; v <= n; v++) {
        if (adj[path[k - 1]][v] && !visited[v]) {
            path[k] = v;
            visited[v] = 1;
            if (k == n) {
                if (adj[v][path[1]]) found = true;
            } else Try(k + 1);
            visited[v] = 0;
            if (found) return;
        }
    }
}

int main() {
    ifstream fin("Hamilton.inp");
    ofstream fout("Hamilton.out");

    fin >> n;
    adj.assign(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fin >> adj[i][j];

    path.assign(n + 1, 0);
    visited.assign(n + 1, 0);
    path[1] = 1;
    visited[1] = 1;
    Try(2);

    if (!found) fout << 0;
    else {
        fout << 1 << endl;
        for (int i = 1; i <= n; i++) fout << path[i] << " ";
        fout << path[1];
    }

    fin.close();
    fout.close();
    return 0;
}

