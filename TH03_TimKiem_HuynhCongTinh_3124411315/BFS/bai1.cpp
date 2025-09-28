#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int main() {
    // Ð?m b?o file input d?t cùng thu m?c v?i exe
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
    getline(fin, line); // b? ph?n còn l?i c?a dòng d?u

    vector< vector<int> > adj(n + 1);

    // Ð?c chính xác n dòng, m?i dòng ch?a các d?nh k? (ho?c có -1 d? k?t thúc)
    for (int i = 1; i <= n; ++i) {
        if (!getline(fin, line)) {
            line = ""; // n?u thi?u dòng thì coi nhu r?ng
        }
        istringstream iss(line);
        int v;
        while (iss >> v) {
            if (v == -1) break;       // h? tr? c? d?ng có -1
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

