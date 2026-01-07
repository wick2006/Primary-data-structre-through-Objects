 #include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>
#include <iomanip>
using namespace std;

// 图的邻接矩阵表示
class GraphMatrix {
private:
    int vertexCount;
    vector<vector<int>> matrix;
    bool directed;
    
public:
    GraphMatrix(int n, bool dir = false) : vertexCount(n), directed(dir) {
        matrix.resize(n, vector<int>(n, 0));
    }
    
    // 添加边
    void addEdge(int u, int v, int weight = 1) {
        if (u >= 0 && u < vertexCount && v >= 0 && v < vertexCount) {
            matrix[u][v] = weight;
            if (!directed) {
                matrix[v][u] = weight;
            }
        }
    }
    
    // 删除边
    void removeEdge(int u, int v) {
        if (u >= 0 && u < vertexCount && v >= 0 && v < vertexCount) {
            matrix[u][v] = 0;
            if (!directed) {
                matrix[v][u] = 0;
            }
        }
    }
    
    // 获取顶点数
    int getVertexCount() {
        return vertexCount;
    }
    
    // 获取边数
    int getEdgeCount() {
        int count = 0;
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                if (matrix[i][j] != 0) {
                    count++;
                }
            }
        }
        return directed ? count : count / 2;
    }
    
    // 获取边的权值
    int getWeight(int u, int v) {
        if (u >= 0 && u < vertexCount && v >= 0 && v < vertexCount) {
            return matrix[u][v];
        }
        return 0;
    }
    
    // 输出邻接矩阵
    void display() {
        cout << "邻接矩阵:" << endl;
        cout << "   ";
        for (int i = 0; i < vertexCount; i++) {
            cout << setw(3) << i;
        }
        cout << endl;
        
        for (int i = 0; i < vertexCount; i++) {
            cout << setw(2) << i << ":";
            for (int j = 0; j < vertexCount; j++) {
                cout << setw(3) << matrix[i][j];
            }
            cout << endl;
        }
    }
    
    // 深度优先遍历（递归）
    void dfsRecursive(int start, vector<bool>& visited) {
        visited[start] = true;
        cout << start << " ";
        
        for (int i = 0; i < vertexCount; i++) {
            if (matrix[start][i] != 0 && !visited[i]) {
                dfsRecursive(i, visited);
            }
        }
    }
    
    // 深度优先遍历（非递归）
    void dfsNonRecursive(int start) {
        vector<bool> visited(vertexCount, false);
        stack<int> s;
        
        visited[start] = true;
        s.push(start);
        
        cout << "深度优先遍历(非递归): ";
        
        while (!s.empty()) {
            int current = s.top();
            s.pop();
            cout << current << " ";
            
            for (int i = vertexCount - 1; i >= 0; i--) {
                if (matrix[current][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    s.push(i);
                }
            }
        }
        cout << endl;
    }
    
    // 广度优先遍历
    void bfs(int start) {
        vector<bool> visited(vertexCount, false);
        queue<int> q;
        
        visited[start] = true;
        q.push(start);
        
        cout << "广度优先遍历: ";
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";
            
            for (int i = 0; i < vertexCount; i++) {
                if (matrix[current][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }
    
    // Prim算法求最小生成树
    void primMST() {
        vector<int> parent(vertexCount, -1);
        vector<int> key(vertexCount, INT_MAX);
        vector<bool> inMST(vertexCount, false);
        
        // 从顶点0开始
        key[0] = 0;
        
        for (int count = 0; count < vertexCount - 1; count++) {
            // 找到不在MST中且key值最小的顶点
            int minKey = INT_MAX, minIndex = -1;
            for (int v = 0; v < vertexCount; v++) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    minIndex = v;
                }
            }
            
            if (minIndex == -1) break;
            
            inMST[minIndex] = true;
            
            // 更新相邻顶点的key值
            for (int v = 0; v < vertexCount; v++) {
                if (matrix[minIndex][v] != 0 && !inMST[v] && matrix[minIndex][v] < key[v]) {
                    parent[v] = minIndex;
                    key[v] = matrix[minIndex][v];
                }
            }
        }
        
        // 输出最小生成树
        cout << "Prim最小生成树:" << endl;
        cout << "边\t权值" << endl;
        int totalWeight = 0;
        for (int i = 1; i < vertexCount; i++) {
            if (parent[i] != -1) {
                cout << parent[i] << "-" << i << "\t" << matrix[parent[i]][i] << endl;
                totalWeight += matrix[parent[i]][i];
            }
        }
        cout << "总权值: " << totalWeight << endl;
    }
    
    // 找到顶点所在的集合（用于Kruskal算法）
    int findSet(int v, vector<int>& parent) {
        if (parent[v] != v) {
            parent[v] = findSet(parent[v], parent);
        }
        return parent[v];
    }
    
    // 合并两个集合（用于Kruskal算法）
    void unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
        int rootU = findSet(u, parent);
        int rootV = findSet(v, parent);
        
        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
    
    // Kruskal算法求最小生成树
    void kruskalMST() {
        // 收集所有边
        struct Edge {
            int u, v, weight;
            Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
        };
        
        vector<Edge> edges;
        for (int i = 0; i < vertexCount; i++) {
            for (int j = i + 1; j < vertexCount; j++) {
                if (matrix[i][j] != 0) {
                    edges.push_back(Edge(i, j, matrix[i][j]));
                }
            }
        }
        
        // 按权值排序
        sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) {
            return a.weight < b.weight;
        });
        
        // 并查集
        vector<int> parent(vertexCount);
        vector<int> rank(vertexCount, 0);
        for (int i = 0; i < vertexCount; i++) {
            parent[i] = i;
        }
        
        vector<Edge> mst;
        
        // 遍历所有边
        for (Edge& edge : edges) {
            int u = edge.u;
            int v = edge.v;
            
            if (findSet(u, parent) != findSet(v, parent)) {
                mst.push_back(edge);
                unionSets(u, v, parent, rank);
            }
        }
        
        // 输出最小生成树
        cout << "Kruskal最小生成树:" << endl;
        cout << "边\t权值" << endl;
        int totalWeight = 0;
        for (Edge& edge : mst) {
            cout << edge.u << "-" << edge.v << "\t" << edge.weight << endl;
            totalWeight += edge.weight;
        }
        cout << "总权值: " << totalWeight << endl;
    }
    
    // Dijkstra算法求最短路径
    void dijkstra(int start) {
        vector<int> dist(vertexCount, INT_MAX);
        vector<bool> visited(vertexCount, false);
        vector<int> parent(vertexCount, -1);
        
        dist[start] = 0;
        
        for (int count = 0; count < vertexCount - 1; count++) {
            // 找到未访问顶点中距离最小的
            int minDist = INT_MAX, minIndex = -1;
            for (int v = 0; v < vertexCount; v++) {
                if (!visited[v] && dist[v] < minDist) {
                    minDist = dist[v];
                    minIndex = v;
                }
            }
            
            if (minIndex == -1) break;
            
            visited[minIndex] = true;
            
            // 更新相邻顶点的距离
            for (int v = 0; v < vertexCount; v++) {
                if (!visited[v] && matrix[minIndex][v] != 0 && 
                    dist[minIndex] != INT_MAX && 
                    dist[minIndex] + matrix[minIndex][v] < dist[v]) {
                    dist[v] = dist[minIndex] + matrix[minIndex][v];
                    parent[v] = minIndex;
                }
            }
        }
        
        // 输出结果
        cout << "从顶点" << start << "到各顶点的最短路径:" << endl;
        cout << "顶点\t距离\t路径" << endl;
        for (int i = 0; i < vertexCount; i++) {
            cout << i << "\t";
            if (dist[i] == INT_MAX) {
                cout << "∞\t不可达";
            } else {
                cout << dist[i] << "\t";
                
                // 输出路径
                stack<int> path;
                int current = i;
                while (current != -1) {
                    path.push(current);
                    current = parent[current];
                }
                
                while (!path.empty()) {
                    cout << path.top();
                    path.pop();
                    if (!path.empty()) cout << "->";
                }
            }
            cout << endl;
        }
    }
    
    // Floyd算法求所有顶点对的最短路径
    void floyd() {
        // 初始化距离矩阵
        vector<vector<int>> dist(vertexCount, vector<int>(vertexCount, INT_MAX));
        
        for (int i = 0; i < vertexCount; i++) {
            dist[i][i] = 0;
            for (int j = 0; j < vertexCount; j++) {
                if (matrix[i][j] != 0) {
                    dist[i][j] = matrix[i][j];
                }
            }
        }
        
        // Floyd算法
        for (int k = 0; k < vertexCount; k++) {
            for (int i = 0; i < vertexCount; i++) {
                for (int j = 0; j < vertexCount; j++) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                        dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        
        // 输出结果
        cout << "所有顶点对之间的最短路径:" << endl;
        cout << "   ";
        for (int i = 0; i < vertexCount; i++) {
            cout << setw(4) << i;
        }
        cout << endl;
        
        for (int i = 0; i < vertexCount; i++) {
            cout << setw(2) << i << ":";
            for (int j = 0; j < vertexCount; j++) {
                if (dist[i][j] == INT_MAX) {
                    cout << setw(4) << "∞";
                } else {
                    cout << setw(4) << dist[i][j];
                }
            }
            cout << endl;
        }
    }
    
    // 拓扑排序（用于有向图）
    bool topologicalSort(vector<int>& result) {
        if (!directed) {
            cout << "拓扑排序只适用于有向图" << endl;
            return false;
        }
        
        vector<int> indegree(vertexCount, 0);
        
        // 计算入度
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                if (matrix[i][j] != 0) {
                    indegree[j]++;
                }
            }
        }
        
        queue<int> q;
        for (int i = 0; i < vertexCount; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            result.push_back(current);
            
            for (int i = 0; i < vertexCount; i++) {
                if (matrix[current][i] != 0) {
                    indegree[i]--;
                    if (indegree[i] == 0) {
                        q.push(i);
                    }
                }
            }
        }
        
        return result.size() == vertexCount;
    }
    
    // 关键路径算法（AOE网）
    void criticalPath() {
        if (!directed) {
            cout << "关键路径只适用于有向图" << endl;
            return;
        }
        
        // 拓扑排序
        vector<int> topoOrder;
        if (!topologicalSort(topoOrder)) {
            cout << "图中存在环，无法计算关键路径" << endl;
            return;
        }
        
        // 计算最早开始时间
        vector<int> ve(vertexCount, 0);
        for (int u : topoOrder) {
            for (int v = 0; v < vertexCount; v++) {
                if (matrix[u][v] != 0) {
                    ve[v] = max(ve[v], ve[u] + matrix[u][v]);
                }
            }
        }
        
        // 计算最晚开始时间
        vector<int> vl(vertexCount, ve[topoOrder.back()]);
        reverse(topoOrder.begin(), topoOrder.end());
        
        for (int u : topoOrder) {
            for (int v = 0; v < vertexCount; v++) {
                if (matrix[u][v] != 0) {
                    vl[u] = min(vl[u], vl[v] - matrix[u][v]);
                }
            }
        }
        
        // 输出关键路径
        cout << "关键路径:" << endl;
        cout << "边\t最早开始\t最晚开始\t时差\t是否关键" << endl;
        
        for (int u = 0; u < vertexCount; u++) {
            for (int v = 0; v < vertexCount; v++) {
                if (matrix[u][v] != 0) {
                    int e = ve[u];
                    int l = vl[v] - matrix[u][v];
                    int slack = l - e;
                    bool critical = (slack == 0);
                    
                    cout << u << "->" << v << "\t" << e << "\t\t" << l << "\t\t" 
                         << slack << "\t\t" << (critical ? "是" : "否") << endl;
                }
            }
        }
    }
    
    // 统计图结构特征
    void printStatistics() {
        int edges = getEdgeCount();
        int maxDegree = 0;
        int minDegree = vertexCount;
        
        cout << "图结构统计:" << endl;
        cout << "顶点数: " << vertexCount << endl;
        cout << "边数: " << edges << endl;
        cout << "类型: " << (directed ? "有向图" : "无向图") << endl;
        
        for (int i = 0; i < vertexCount; i++) {
            int degree = 0;
            for (int j = 0; j < vertexCount; j++) {
                if (matrix[i][j] != 0) {
                    degree++;
                }
            }
            maxDegree = max(maxDegree, degree);
            minDegree = min(minDegree, degree);
            
            cout << "顶点" << i << "的度: " << degree;
            if (directed) {
                int inDegree = 0, outDegree = 0;
                for (int j = 0; j < vertexCount; j++) {
                    if (matrix[j][i] != 0) inDegree++;
                    if (matrix[i][j] != 0) outDegree++;
                }
                cout << " (入度: " << inDegree << ", 出度: " << outDegree << ")";
            }
            cout << endl;
        }
        
        cout << "最大度: " << maxDegree << endl;
        cout << "最小度: " << minDegree << endl;
    }
};

// 图的邻接表表示（邻接链表）
class GraphList {
private:
    struct EdgeNode {
        int vertex;
        int weight;
        EdgeNode* next;
        EdgeNode(int v, int w = 1) : vertex(v), weight(w), next(nullptr) {}
    };
    
    struct VertexNode {
        int data;
        EdgeNode* firstEdge;
        VertexNode() : data(0), firstEdge(nullptr) {}
    };
    
    vector<VertexNode> vertices;
    bool directed;
    int vertexCount;
    
public:
    GraphList(int n, bool dir = false) : vertexCount(n), directed(dir) {
        vertices.resize(n);
        for (int i = 0; i < n; i++) {
            vertices[i].data = i;
        }
    }
    
    // 添加边
    void addEdge(int u, int v, int weight = 1) {
        if (u >= 0 && u < vertexCount && v >= 0 && v < vertexCount) {
            // 添加到u的邻接表
            EdgeNode* newEdge = new EdgeNode(v, weight);
            newEdge->next = vertices[u].firstEdge;
            vertices[u].firstEdge = newEdge;
            
            // 如果是无向图，添加到v的邻接表
            if (!directed) {
                EdgeNode* newEdge2 = new EdgeNode(u, weight);
                newEdge2->next = vertices[v].firstEdge;
                vertices[v].firstEdge = newEdge2;
            }
        }
    }
    
    // 显示邻接表
    void display() {
        cout << "邻接表:" << endl;
        for (int i = 0; i < vertexCount; i++) {
            cout << "顶点" << i << ": ";
            EdgeNode* current = vertices[i].firstEdge;
            while (current) {
                cout << "->(" << current->vertex << "," << current->weight << ")";
                current = current->next;
            }
            cout << endl;
        }
    }
    
    // 深度优先遍历
    void dfs(int start) {
        vector<bool> visited(vertexCount, false);
        stack<int> s;
        
        cout << "深度优先遍历: ";
        visited[start] = true;
        s.push(start);
        
        while (!s.empty()) {
            int current = s.top();
            s.pop();
            cout << current << " ";
            
            // 逆序入栈，保证顺序
            vector<int> neighbors;
            EdgeNode* edge = vertices[current].firstEdge;
            while (edge) {
                neighbors.push_back(edge->vertex);
                edge = edge->next;
            }
            
            for (int i = neighbors.size() - 1; i >= 0; i--) {
                if (!visited[neighbors[i]]) {
                    visited[neighbors[i]] = true;
                    s.push(neighbors[i]);
                }
            }
        }
        cout << endl;
    }
    
    // 广度优先遍历
    void bfs(int start) {
        vector<bool> visited(vertexCount, false);
        queue<int> q;
        
        cout << "广度优先遍历: ";
        visited[start] = true;
        q.push(start);
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";
            
            EdgeNode* edge = vertices[current].firstEdge;
            while (edge) {
                if (!visited[edge->vertex]) {
                    visited[edge->vertex] = true;
                    q.push(edge->vertex);
                }
                edge = edge->next;
            }
        }
        cout << endl;
    }
};

// 图操作菜单
void graphMatrixMenu() {
    int vertexCount, edgeCount;
    bool directed = false;
    
    cout << "输入顶点数: ";
    cin >> vertexCount;
    
    cout << "是否是有向图? (1=是, 0=否): ";
    cin >> directed;
    
    GraphMatrix graph(vertexCount, directed);
    
    cout << "输入边数: ";
    cin >> edgeCount;
    
    cout << "输入边(格式: 起点 终点 权值):" << endl;
    for (int i = 0; i < edgeCount; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
    
    int choice;
    while (true) {
        cout << "\n----- 邻接矩阵图操作 -----";
        cout << "\n1. 显示邻接矩阵";
        cout << "\n2. 深度优先遍历(非递归)";
        cout << "\n3. 广度优先遍历";
        cout << "\n4. Prim最小生成树";
        cout << "\n5. Kruskal最小生成树";
        cout << "\n6. Dijkstra最短路径";
        cout << "\n7. Floyd最短路径";
        cout << "\n8. 关键路径";
        cout << "\n9. 图结构统计";
        cout << "\n0. 返回";
        cout << "\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1:
                graph.display();
                break;
            case 2: {
                int start;
                cout << "输入起始顶点: ";
                cin >> start;
                graph.dfsNonRecursive(start);
                break;
            }
            case 3: {
                int start;
                cout << "输入起始顶点: ";
                cin >> start;
                graph.bfs(start);
                break;
            }
            case 4:
                if (!directed) {
                    graph.primMST();
                } else {
                    cout << "Prim算法只适用于无向图" << endl;
                }
                break;
            case 5:
                if (!directed) {
                    graph.kruskalMST();
                } else {
                    cout << "Kruskal算法只适用于无向图" << endl;
                }
                break;
            case 6: {
                int start;
                cout << "输入起始顶点: ";
                cin >> start;
                graph.dijkstra(start);
                break;
            }
            case 7:
                graph.floyd();
                break;
            case 8:
                if (directed) {
                    graph.criticalPath();
                } else {
                    cout << "关键路径只适用于有向图" << endl;
                }
                break;
            case 9:
                graph.printStatistics();
                break;
        }
    }
}

void graphListMenu() {
    int vertexCount, edgeCount;
    bool directed = false;
    
    cout << "输入顶点数: ";
    cin >> vertexCount;
    
    cout << "是否是有向图? (1=是, 0=否): ";
    cin >> directed;
    
    GraphList graph(vertexCount, directed);
    
    cout << "输入边数: ";
    cin >> edgeCount;
    
    cout << "输入边(格式: 起点 终点 权值):" << endl;
    for (int i = 0; i < edgeCount; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
    
    int choice;
    while (true) {
        cout << "\n----- 邻接表图操作 -----";
        cout << "\n1. 显示邻接表";
        cout << "\n2. 深度优先遍历";
        cout << "\n3. 广度优先遍历";
        cout << "\n0. 返回";
        cout << "\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1:
                graph.display();
                break;
            case 2: {
                int start;
                cout << "输入起始顶点: ";
                cin >> start;
                graph.dfs(start);
                break;
            }
            case 3: {
                int start;
                cout << "输入起始顶点: ";
                cin >> start;
                graph.bfs(start);
                break;
            }
        }
    }
}

int main() {
    int choice;
    
    while (true) {
        cout << "\n========== 图计算系统 ==========";
        cout << "\n1. 邻接矩阵图";
        cout << "\n2. 邻接表图";
        cout << "\n0. 退出";
        cout << "\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1:
                graphMatrixMenu();
                break;
            case 2:
                graphListMenu();
                break;
        }
    }
    
    return 0;
}