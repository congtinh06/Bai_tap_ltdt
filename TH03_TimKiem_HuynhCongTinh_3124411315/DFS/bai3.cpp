#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

int n; 
int adj[1001][1001]; 
int deg[1001];       
int color[1001];    

bool isBipartite() {
    queue<int> q;
    for (int start = 1; start <= n; start++) {
        if (color[start] == 0) { 
            color[start] = 1;
            q.push(start);

            while (!q.empty()) {
                int u = q.front(); q.pop();

                for (int i = 0; i < deg[u]; i++) {
                    int v = adj[u][i];
                    if (color[v] == 0) {
                        color[v] = -color[u]; 
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        return false; 
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    ifstream fin("input.inp");
    ofstream fout("output.out");
    fin >> n;
    for (int i = 1; i <= n; i++) {
        int v;
        while (fin >> v && v != -1) {
            adj[i][deg[i]++] = v;
        }
    }	
    for (int i = 1; i <= n; i++) color[i] = 0;

    if (isBipartite()) fout << "Do thi phan doi\n";
    else fout << "Do thi khong phan doi\n";

    fin.close();
    fout.close();
    return 0;
}

