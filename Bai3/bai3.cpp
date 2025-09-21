#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("DanhSachKe.inp");
    ofstream fout("DanhSachKe.out");

    int n;
    fin >> n;   // số đỉnh
    fout << n << "\n";

    for (int i = 1; i <= n; i++) {
        int deg = 0;   // bậc của đỉnh i
        while (true) {
            int x;
            fin >> x;
            if (x == -1) break; // kết thúc danh sách kề của đỉnh i
            deg++;
        }
        fout << deg << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
