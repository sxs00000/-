#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 100010;

vector<int> g[MAXN];   // 原图
vector<int> gr[MAXN];  // 逆图
bool vis[MAXN];
vector<int> order;     // 存 DFS 结束序（拓扑序前身）
int belong[MAXN];
int scc_cnt;

// 第一次 DFS：求【结束序 / 后序】，这就是 Kosaraju 的拓扑序核心
void dfs1(int u) {
    vis[u] = true;
    for (int v : g[u]) {
        if (!vis[v])
            dfs1(v);
    }
    // 递归结束时才加入 → 这就是拓扑序的关键
    order.push_back(u);
}

// 第二次 DFS：划分强连通分量
void dfs2(int u) {
    belong[u] = scc_cnt;
    for (int v : gr[u]) {
        if (!belong[v])
            dfs2(v);
    }
}

void kosaraju(int n) {
    memset(vis, 0, sizeof(vis));
    memset(belong, 0, sizeof(belong));
    order.clear();
    scc_cnt = 0;

    // 1. 原图 DFS，得到结束序
    for (int i = 1; i <= n; ++i) {
        if (!vis[i])
            dfs1(i);
    }

    // 2. 逆序 → 变成合法拓扑序
    reverse(order.begin(), order.end());

    // 3. 按拓扑序在逆图上 DFS
    for (int u : order) {
        if (!belong[u]) {
            scc_cnt++;
            dfs2(u);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        gr[v].push_back(u);
    }

    kosaraju(n);

    cout << "强连通分量数量：" << scc_cnt << endl;
    for (int i = 1; i <= n; ++i)
        cout << i << " : " << belong[i] << endl;

    return 0;
}
