#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
using namespace std;

int n;
vector<vector<int> > adj;
vector<int> eulerPath;

void dfs(int u, vector<vector<int> > &graph) {
    for (int v = 0; v < n; v++) {
        if (graph[u][v] == 1) {
            graph[u][v] = graph[v][u] = 0;
            dfs(v, graph);
        }
    }
    eulerPath.push_back(u + 1);
}

bool isConnected(vector<vector<int> > &graph) {
    vector<int> visited(n, 0);
    stack<int> st;
    int start = -1;
    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < n; j++) deg += graph[i][j];
        if (deg > 0) {
            start = i;
            break;
        }
    }
    if (start == -1) return true;

    st.push(start);
    visited[start] = 1;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !visited[v]) {
                visited[v] = 1;
                st.push(v);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < n; j++) deg += graph[i][j];
        if (deg > 0 && !visited[i]) return false;
    }
    return true;
}

int main() {
    ifstream fin("DoThiEuler.inp");
    ofstream fout("DoThiEuler.out");

    fin >> n;
    adj.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fin >> adj[i][j];

    bool ok = true;
    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < n; j++) deg += adj[i][j];
        if (deg % 2 != 0) {
            ok = false;
            break;
        }
    }

    if (!isConnected(adj)) ok = false;

    if (!ok) {
        fout << 0;
        return 0;
    }

    fout << 1 << endl;
    vector<vector<int> > temp = adj;
    dfs(0, temp);

    for (int i = eulerPath.size() - 1; i >= 0; i--) {
        fout << eulerPath[i];
        if (i > 0) fout << " ";
    }

    fin.close();
    fout.close();
    return 0;
}

