#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

struct Node {
    int x, y, cost;
    bool operator>(const Node &other) const {
        return cost > other.cost;
    }
};

int main() {
    freopen("input1.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);

    int N, M, XI, YI, XJ, YJ;
    cin >> N >> M >> XI >> YI >> XJ >> YJ;

    vector<vector<int>> A(N + 1, vector<int>(M + 1));
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            cin >> A[i][j];

    const int INF = INT_MAX;
    vector<vector<int>> dist(N + 1, vector<int>(M + 1, INF));
    vector<vector<pair<int, int>>> parent(N + 1, vector<pair<int, int>>(M + 1, {-1, -1}));

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dist[XI][YI] = 0;
    pq.push({XI, YI, 0});

    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        int x = cur.x, y = cur.y;

        if (cur.cost > dist[x][y]) continue;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
            if (A[nx][ny] == 0) continue; // không được đi vào ô 0

            int newCost = dist[x][y] + A[nx][ny];
            if (newCost < dist[nx][ny]) {
                dist[nx][ny] = newCost;
                parent[nx][ny] = {x, y};
                pq.push({nx, ny, newCost});
            }
        }
    }

    // Không có đường đi
    if (dist[XJ][YJ] == INF) {
        cout << 0;
        return 0;
    }

    // Có đường đi
    cout << 1 << "\n";
    cout << dist[XJ][YJ] << "\n";

    // Truy vết đường đi
    vector<pair<int, int>> path;
    for (pair<int, int> v = {XJ, YJ}; v.first != -1; v = parent[v.first][v.second])
        path.push_back(v);
    reverse(path.begin(), path.end());

    for (auto [x, y] : path)
        cout << x << " " << y << "\n";

    return 0;
}
