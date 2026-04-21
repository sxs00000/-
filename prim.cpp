#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// 定义边的结构体
struct Edge {
    int to;    // 目标顶点
    int weight; // 边的权值
    Edge(int t, int w) : to(t), weight(w) {}
    // 重载运算符，用于优先队列（最小堆）
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

// Prim算法实现
void prim(int n, const vector<vector<Edge>>& graph) {
    vector<bool> visited(n, false); // 标记顶点是否已被访问
    vector<int> parent(n, -1);      // 记录生成树中每个顶点的父节点
    vector<int> key(n, INT_MAX);    // 记录每个顶点到生成树的最小权值
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq; // 最小堆

    // 从顶点0开始
    key[0] = 0;
    pq.push(Edge(0, 0));

    while (!pq.empty()) {
        // 取出权值最小的边
        Edge current = pq.top();
        pq.pop();
        int u = current.to;

        // 如果顶点已经被访问过，跳过
        if (visited[u]) continue;

        // 标记顶点为已访问
        visited[u] = true;

        // 遍历当前顶点的所有邻接边
        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;

            // 如果顶点v未被访问，且当前边的权值小于key[v]
            if (!visited[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push(Edge(v, weight));
            }
        }
    }

    // 输出最小生成树的边
    cout << "最小生成树的边：" << endl;
    int totalWeight = 0;
    for (int i = 1; i < n; i++) {
        cout << parent[i] << " - " << i << " (权值: " << key[i] << ")" << endl;
        totalWeight += key[i];
    }
    cout << "最小生成树的总权值：" << totalWeight << endl;
}

int main() {
    // 测试用例：顶点数为4，边及权值为：0-1(2), 0-2(3), 0-3(1), 1-2(4), 1-3(5), 2-3(6)
    int n = 4;
    vector<vector<Edge>> graph(n);

    // 添加边
    graph[0].emplace_back(1, 2);
    graph[0].emplace_back(2, 3);
    graph[0].emplace_back(3, 1);
    graph[1].emplace_back(0, 2);
    graph[1].emplace_back(2, 4);
    graph[1].emplace_back(3, 5);
    graph[2].emplace_back(0, 3);
    graph[2].emplace_back(1, 4);
    graph[2].emplace_back(3, 6);
    graph[3].emplace_back(0, 1);
    graph[3].emplace_back(1, 5);
    graph[3].emplace_back(2, 6);

    // 调用Prim算法
    prim(n, graph);

    return 0;
}
