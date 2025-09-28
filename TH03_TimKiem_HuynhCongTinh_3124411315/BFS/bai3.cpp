#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ifstream fin("LTPLT.INP");
    ofstream fout("LTPLT.OUT");

    int n;
    fin >> n;
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

    vector<int> visited(n + 1, 0);
    vector< vector<int> > components;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            vector<int> comp;
            queue<int> q;
            visited[i] = 1;
            q.push(i);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                comp.push_back(u);
                for (size_t j = 0; j < adj[u].size(); j++) {
                    int v = adj[u][j];
                    if (!visited[v]) {
                        visited[v] = 1;
                        q.push(v);
                    }
                }
            }
            sort(comp.begin(), comp.end());
            components.push_back(comp);
        }
    }

    fout << components.size() << "\n";
    for (size_t i = 0; i < components.size(); i++) {
        for (size_t j = 0; j < components[i].size(); j++) {
            if (j) fout << " ";
            fout << components[i][j];
        }
        fout << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}

