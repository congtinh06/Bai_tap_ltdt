#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
using namespace std;

int n;
vector<vector<int> > adj;
vector<pair<int, int> > domino;
vector<pair<int, int> > euler;

void dfs(int u, vector<vector<int> > &graph) {
    for (int v = 0; v < 7; v++) {
        if (graph[u][v] > 0) {
            graph[u][v]--;
            graph[v][u]--;
            dfs(v, graph);
            euler.push_back(make_pair(u, v));
        }
    }
}

bool isConnected(vector<vector<int> > &graph) {
    vector<int> visited(7, 0);
    stack<int> st;
    int start = -1;
    for (int i = 0; i < 7; i++) {
        int deg = 0;
        for (int j = 0; j < 7; j++) deg += graph[i][j];
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
        for (int v = 0; v < 7; v++) {
            if (graph[u][v] && !visited[v]) {
                visited[v] = 1;
                st.push(v);
            }
        }
    }

    for (int i = 0; i < 7; i++) {
        int deg = 0;
        for (int j = 0; j < 7; j++) deg += graph[i][j];
        if (deg > 0 && !visited[i]) return false;
    }
    return true;
}

int main() {
    ifstream fin("Domino.inp");
    ofstream fout("Domino.out");

    fin >> n;
    adj.assign(7, vector<int>(7, 0));
    domino.resize(n);

    for (int i = 0; i < n; i++) {
        int x, y;
        fin >> x >> y;
        domino[i] = make_pair(x, y);
        adj[x][y]++;
        adj[y][x]++;
    }

    bool ok = true;
    for (int i = 0; i < 7; i++) {
        int deg = 0;
        for (int j = 0; j < 7; j++) deg += adj[i][j];
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

    for (int i = euler.size() - 1; i >= 0; i--) {
        fout << euler[i].first << " " << euler[i].second << endl;
    }

    fin.close();
    fout.close();
    return 0;
}

