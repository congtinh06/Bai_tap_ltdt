#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <numeric>
using namespace std;

int n;
vector<vector<int> > adj;

bool isConnected(vector<vector<int> > &graph) {
    vector<int> visited(n, 0);
    stack<int> st;
    int start = -1;
    for (int i = 0; i < n; i++) {
        int deg = accumulate(graph[i].begin(), graph[i].end(), 0);
        if (deg > 0) {
            start = i;
            break;
        }
    }
    if (start == -1) return true;
    st.push(start);
    visited[start] = 1;
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !visited[v]) {
                visited[v] = 1;
                st.push(v);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        int deg = accumulate(graph[i].begin(), graph[i].end(), 0);
        if (deg > 0 && !visited[i])
            return false;
    }
    return true;
}

vector<int> eulerIterative(int start) {
    vector<int> path;
    stack<int> st;
    vector<vector<int> > temp = adj;
    st.push(start);
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
    ifstream fin("EulerKhongDeQuy.inp");
    ofstream fout("EulerKhongDeQuy.out");

    fin >> n;
    adj.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fin >> adj[i][j];

    bool ok = true;
    for (int i = 0; i < n; i++) {
        int deg = accumulate(adj[i].begin(), adj[i].end(), 0);
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
    vector<int> res = eulerIterative(0);
    for (int i = res.size() - 1; i >= 0; i--) {
        fout << res[i];
        if (i > 0) fout << " ";
    }

    fin.close();
    fout.close();
    return 0;
}

