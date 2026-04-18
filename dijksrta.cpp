#include <bits/stdc++.h>
using namespace std;

const int N = 1010;      // 最大点数
const int M = 100010;    // 最大边数
const int INF = 0x3f3f3f3f;

// ==================== 方法一：邻接矩阵 + 朴素 Dijkstra O(n2) ====================
class DijkstraMatrix {
private:
    int g[N][N];  // 邻接矩阵
    int dist[N];
    bool st[N];
    int n;
    
public:
    DijkstraMatrix(int n) : n(n) {
        // 初始化邻接矩阵为无穷大
        memset(g, 0x3f, sizeof(g));
        for (int i = 1; i <= n; i++) g[i][i] = 0;
    }
    
    void addEdge(int u, int v, int w) {
        g[u][v] = min(g[u][v], w);  // 处理重边，取最小值
    }
    
    vector<int> dijkstra(int s) {
        memset(dist, 0x3f, sizeof(dist));
        memset(st, 0, sizeof(st));
        dist[s] = 0;
        
        for (int i = 1; i <= n; i++) {
            // 1. 找未确定点中距离最小的点 t (O(n))
            int t = -1;
            for (int j = 1; j <= n; j++) {
                if (!st[j] && (t == -1 || dist[j] < dist[t])) {
                    t = j;
                }
            }
            
            if (t == -1 || dist[t] == INF) break;  // 剩余点不可达
            
            // 2. 用 t 更新所有点的距离 (O(n))
            for (int j = 1; j <= n; j++) {
                if (dist[j] > dist[t] + g[t][j]) {
                    dist[j] = dist[t] + g[t][j];
                }
            }
            
            st[t] = true;
        }
        
        vector<int> res(n + 1);
        for (int i = 1; i <= n; i++) res[i] = dist[i];
        return res;
    }
};


// ==================== 方法二：邻接表 + 堆优化 Dijkstra O(m log n) ====================
class DijkstraHeap {
private:
    vector<vector<pair<int, int>>> g;  // 邻接表: g[u] = {v, w}
    int n;
    
public:
    DijkstraHeap(int n) : n(n) {
        g.resize(n + 1);
    }
    
    void addEdge(int u, int v, int w) {
        g[u].push_back({v, w});
    }
    
    vector<int> dijkstra(int s) {
        vector<int> dist(n + 1, INF);
        vector<bool> st(n + 1, false);
        // 小根堆：{距离, 节点}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        
        dist[s] = 0;
        pq.push({0, s});
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (st[u]) continue;
            st[u] = true;
            
            // 只遍历 u 的实际出边
            for (auto [v, w] : g[u]) {
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist;
    }
};

int main() {
}
