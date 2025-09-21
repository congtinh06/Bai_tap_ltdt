#include <bits/stdc++.h>
using namespace std;

// ===== 1. Ma trận kề sang danh sách kề =====
vector<vector<int>> matrixToList(vector<vector<int>> &adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> adjList(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] != 0) {
                adjList[i].push_back(j);
            }
        }
    }
    return adjList;
}

// ===== 2. Ma trận kề sang danh sách cạnh =====
vector<pair<int,int>> matrixToEdges(vector<vector<int>> &adjMatrix) {
    int n = adjMatrix.size();
    vector<pair<int,int>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {  // tránh lặp cho đồ thị vô hướng
            if (adjMatrix[i][j] != 0) {
                edges.push_back({i, j});
            }
        }
    }
    return edges;
}

// ===== 3. Danh sách kề sang ma trận kề =====
vector<vector<int>> listToMatrix(vector<vector<int>> &adjList) {
    int n = adjList.size();
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int v : adjList[i]) {
            adjMatrix[i][v] = 1;
        }
    }
    return adjMatrix;
}

// ===== 4. Danh sách kề sang danh sách cạnh =====
vector<pair<int,int>> listToEdges(vector<vector<int>> &adjList) {
    int n = adjList.size();
    vector<pair<int,int>> edges;
    for (int i = 0; i < n; i++) {
        for (int v : adjList[i]) {
            if (i < v) edges.push_back({i, v}); // tránh trùng lặp
        }
    }
    return edges;
}

// ===== 5. Danh sách cạnh sang ma trận kề =====
vector<vector<int>> edgesToMatrix(vector<pair<int,int>> &edges, int n) {
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    for (auto e : edges) {
        adjMatrix[e.first][e.second] = 1;
        adjMatrix[e.second][e.first] = 1; // nếu là vô hướng
    }
    return adjMatrix;
}

// ===== 6. Danh sách cạnh sang danh sách kề =====
vector<vector<int>> edgesToList(vector<pair<int,int>> &edges, int n) {
    vector<vector<int>> adjList(n);
    for (auto e : edges) {
        adjList[e.first].push_back(e.second);
        adjList[e.second].push_back(e.first); // nếu là vô hướng
    }
    return adjList;
}

// ===== Hàm in để kiểm tra =====
void printMatrix(vector<vector<int>> &mat, ofstream &fout) {
    for (auto &row : mat) {
        for (int v : row) fout << v << " ";
        fout << "\n";
    }
}

void printList(vector<vector<int>> &lst, ofstream &fout) {
    for (int i = 0; i < lst.size(); i++) {
        fout << i << ": ";
        for (int v : lst[i]) fout << v << " ";
        fout << "\n";
    }
}

void printEdges(vector<pair<int,int>> &edges, ofstream &fout) {
    for (auto &e : edges) fout << e.first << " " << e.second << "\n";
}

// ===== MAIN DEMO =====
int main() {
    ifstream fin("graph.inp");
    ofstream fout("graph.out");

    int n;
    fin >> n; // số đỉnh
    vector<vector<int>> adjMatrix(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fin >> adjMatrix[i][j];

    // 1. Ma trận -> Danh sách kề
    auto adjList = matrixToList(adjMatrix);
    fout << "Danh sach ke:\n";
    printList(adjList, fout);

    // 2. Ma trận -> Danh sách cạnh
    auto edges = matrixToEdges(adjMatrix);
    fout << "\nDanh sach canh:\n";
    printEdges(edges, fout);

    // 3. Danh sách kề -> Ma trận
    auto mat2 = listToMatrix(adjList);
    fout << "\nMa tran ke tu danh sach ke:\n";
    printMatrix(mat2, fout);

    // 4. Danh sách kề -> Danh sách cạnh
    auto edges2 = listToEdges(adjList);
    fout << "\nDanh sach canh tu danh sach ke:\n";
    printEdges(edges2, fout);

    // 5. Danh sách cạnh -> Ma trận
    auto mat3 = edgesToMatrix(edges, n);
    fout << "\nMa tran ke tu danh sach canh:\n";
    printMatrix(mat3, fout);

    // 6. Danh sách cạnh -> Danh sách kề
    auto list2 = edgesToList(edges, n);
    fout << "\nDanh sach ke tu danh sach canh:\n";
    printList(list2, fout);

    return 0;
}
