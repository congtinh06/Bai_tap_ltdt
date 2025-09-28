#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

int n, x, y;
int adj[1001][1001]; 
int deg[1001];      
int parent[1001];
bool visited[1001];

void myReverse(int path[], int &len) {
    int l = 0, r = len - 1;
    while (l < r) {
        int tmp = path[l];
        path[l] = path[r];
        path[r] = tmp;
        l++;
        r--;
    }
}

int main() {
    ifstream fin("DuongDiDFS.inp");
    ofstream fout("DuongDiDFS.out");

    fin >> n >> x >> y;

    for (int i = 1; i <= n; i++) {
        int v;
        while (fin >> v && v != -1) {
            adj[i][deg[i]++] = v;
        }
    }

    for (int i = 1; i <= n; i++) {
        visited[i] = false;
        parent[i] = -1;
    }

    queue<int> q;
    q.push(x);
    visited[x] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int i = 0; i < deg[u]; i++) {
            int v = adj[u][i];
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    int path[1001], len = 0;
    int cur = y;
    while (cur != -1) {
        path[len++] = cur;
        cur = parent[cur];
    }

    myReverse(path, len);

    fout << len << endl;
    for (int i = 0; i < len; i++) {
        fout << path[i] << " ";
    }
    fout << endl;

    fin.close();
    fout.close();
    return 0;
}

