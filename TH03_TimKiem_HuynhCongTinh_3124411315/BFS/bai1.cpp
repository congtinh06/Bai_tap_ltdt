#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int main() {
    // �?m b?o file input d?t c�ng thu m?c v?i exe
    ifstream fin("LienThongBFS.INP");
    ofstream fout("LienThongBFS.OUT");

    if (!fin) {
        cerr << "Khong mo duoc file LienThongBFS.INP\n";
        return 1;
    }

    int n, x;
    if (!(fin >> n >> x)) {
        cerr << "File input khong hop le (khong doc duoc n, x)\n";
        return 1;
    }

    string line;
    getline(fin, line); // b? ph?n c�n l?i c?a d�ng d?u

    vector< vector<int> > adj(n + 1);

    // �?c ch�nh x�c n d�ng, m?i d�ng ch?a c�c d?nh k? (ho?c c� -1 d? k?t th�c)
    for (int i = 1; i <= n; ++i) {
        if (!getline(fin, line)) {
            line = ""; // n?u thi?u d�ng th� coi nhu r?ng
        }
        istringstream iss(line);
        int v;
        while (iss >> v) {
            if (v == -1) break;       // h? tr? c? d?ng c� -1
            if (v >= 1 && v <= n) adj[i].push_back(v);
        }
    }

    vector<int> visited(n + 1, 0);
    queue<int> q;
    vector<int> result;

    visited[x] = 1;
    q.push(x);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (!visited[v]) {
                visited[v] = 1;
                q.push(v);
                result.push_back(v);
            }
        }
    }

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

