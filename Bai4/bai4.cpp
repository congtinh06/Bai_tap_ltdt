#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream fin("DanhSachCanh.inp");
    ofstream fout("DanhSachCanh.out");

    int n, m;
    fin >> n >> m;

    vector<int> deg(n + 1, 0);  // deg[i] lưu bậc của đỉnh i

    for (int i = 0; i < m; i++) {
        int u, v;
        fin >> u >> v;
        deg[u]++;
        deg[v]++;  // vì đồ thị vô hướng
    }

    fout << n << "\n";
    for (int i = 1; i <= n; i++) {
        fout << deg[i] << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
