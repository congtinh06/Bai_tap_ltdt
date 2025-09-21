#include <iostream>
#include <fstream>
#include <cstring>  
#include <cstdio>   

using namespace std;

ifstream fin("tong.in");
#define cin fin

int main() {
    char line[10001];
    int tong = 0;
    while (cin.getline(line, 10000, '\n')) {
        char *p = strtok(line, " ");  // tách chu?i theo d?u cách
        while (p != NULL) {
            int a;
            sscanf(p, "%d", &a);  // chuy?n chu?i sang s?
            tong += a;
            p = strtok(NULL, " "); // ti?p t?c tách
        }
    }
    cout << tong << endl;
    return 0;
}

