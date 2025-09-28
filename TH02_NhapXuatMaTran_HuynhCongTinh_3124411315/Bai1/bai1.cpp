#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("MaTranKe.inp");
    ofstream fout("MaTranKe.out");

    int n;
    fin >> n;
    int a[1005][1005];

    // đọc ma trận kề
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> a[i][j];
        }
    }

    fout << n << "\n";
    // tính bậc của từng đỉnh
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 1) degree++;
        }
        fout << degree << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
