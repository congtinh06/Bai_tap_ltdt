#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
using namespace std;

int n;
vector<vector<int> > adj;
vector<int> visited;

void dfs(int u) {
    visited[u] = 1;
    for (int v = 0; v < n; v++) {
        if (adj[u][v] && !visited[v])
            dfs(v);
    }
}

bool isConnected() {
    visited.assign(n, 0);
    int start = -1;
    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < n; j++)
            deg += adj[i][j];
        if (deg > 0) {
            start = i;
            break;
        }
    }
    if (start == -1) return false;
    dfs(start);
    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < n; j++)
            deg += adj[i][j];
        if (deg > 0 && !visited[i])
            return false;
    }
    return true;
}

vector<int> findEulerPath(int start) {
    vector<int> path;
    stack<int> st;
    st.push(start);
    vector<vector<int> > temp = adj;
    while (!st.empty()) {
        int u = st.top();
        int v;
        for (v = 0; v < n; v++)
            if (temp[u][v]) break;
        if (v == n) {
            path.push_back(u + 1);
            st.pop();
        } else {
            st.push(v);
            temp[u][v] = temp[v][u] = 0;
        }
    }
    return path;
}

int main() {
    ifstream fin("DoThiNuaEuler.inp");
    ofstream fout("DoThiNuaEuler.out");

    fin >> n;
    adj.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fin >> adj[i][j];

    if (!isConnected()) {
        fout << 0;
        return 0;
    }

    int odd = 0, start = 0;
    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < n; j++)
            deg += adj[i][j];
        if (deg % 2 == 1) {
            odd++;
            start = i;
        }
    }

    if (odd != 2) {
        fout << 0;
        return 0;
    }

    fout << 1 << endl;
    vector<int> path = findEulerPath(start);
    for (int i = 0; i < (int)path.size(); i++)
        fout << path[i] << " ";

    fin.close();
    fout.close();
    return 0;
}

