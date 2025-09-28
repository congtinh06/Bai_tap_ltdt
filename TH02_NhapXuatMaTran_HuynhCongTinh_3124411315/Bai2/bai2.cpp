#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("BacVaoBacRa.inp");
    ofstream fout("BacVaoBacRa.out");

    int n;
    fin >> n;
    int a[1001][1001];

    // Đọc ma trận kề
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            fin >> a[i][j];
        }
    }

    fout << n << "\n"; // dòng đầu ghi số đỉnh

    for (int i = 1; i <= n; i++) {
        int bacVao = 0, bacRa = 0;
        for (int j = 1; j <= n; j++) {
            if (a[j][i] == 1) bacVao++; // cột i => bậc vào
            if (a[i][j] == 1) bacRa++;  // hàng i => bậc ra
        }
        fout << bacVao << " " << bacRa << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
