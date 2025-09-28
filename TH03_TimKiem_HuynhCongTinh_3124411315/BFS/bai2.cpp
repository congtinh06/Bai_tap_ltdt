#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ifstream fin("DuongDiBFS.INP");
    ofstream fout("DuongDiBFS.OUT");

    if (!fin) {
        cerr << "Khong mo duoc file DuongDiBFS.INP\n";
        return 1;
    }

    int n, x, y;
    if (!(fin >> n >> x >> y)) {
        cerr << "File input khong hop le (khong doc duoc n x y)\n";
        return 1;
    }

    string line;
    getline(fin, line); 


    vector< vector<int> > adj(n + 1);

    // Doc chinh xac n dong: moi dong la danh sach ke cua dinh i (ho tro -1 de ket thuc dong)
    for (int i = 1; i <= n; ++i) {
        if (!getline(fin, line)) line = ""; 
        istringstream iss(line);
        int v;
        while (iss >> v) {
            if (v == -1) break;        
            if (v >= 1 && v <= n) adj[i].push_back(v);
        }
    }

    vector<int> visited(n + 1, 0);
    vector<int> parent(n + 1, -1);
    queue<int> q;

    visited[x] = 1;
    q.push(x);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        // DUNG VONG LAP CHO COMPILER CU
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (!visited[v]) {
                visited[v] = 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    vector<int> path;
    if (visited[y]) {
        for (int cur = y; cur != -1; cur = parent[cur]) {
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());

        fout << path.size() << "\n";
        for (size_t i = 0; i < path.size(); ++i) {
            if (i) fout << " ";
            fout << path[i];
        }
        fout << "\n";
    } else {
        // Khong co duong di
        fout << 0 << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}

