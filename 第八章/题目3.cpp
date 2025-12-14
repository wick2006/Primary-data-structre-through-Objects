#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <climits>
#include <limits> // 为 numeric_limits
using namespace std;

/*
  文件：第八章\题目3.cpp
  功能：使用邻接矩阵实现 Prim 与 Kruskal 最小生成树（MST）算法，并使用并查集实现 Kruskal。
  说明（重要约定）：
    - 邻接矩阵中：0 表示无边（不含自环的权重为 0），正整数表示边权重。
    - 图被视为无向图：adjMatrix[i][j] == adjMatrix[j][i]。getAllEdges() 只返回 i<j 的边以避免重复。
    - 顶点编号使用 0..n-1。
*/

 /* 边的简单结构体：
    - src: 边的起点
    - dest: 边的终点
    - weight: 边的权重
  */
struct edge {
	int src, dest, weight;
};

 /*
  并查集（Disjoint Set / Union-Find）
  作用：在 Kruskal 算法中检测两个顶点是否属于同一连通分量，并在加入边时合并集合。
  技术要点：
    - 路径压缩（find 中递归压缩）：将访问路径上的节点直接连接到根，从而摊销后续 find 的成本。
    - 按秩合并（union by rank）：把秩（近似树高）较小的根挂到秩较大的根下，避免树高增长。
  时间复杂度（摊销）：几乎常数，准确是反阿克曼函数 α(n) 级别。
*/
class disjointSet {
private:
	vector<int> parent;    // parent[i] = 父节点索引
	vector<int> rankArr;   // rankArr[i] = 大致的子树高度/秩

public:
	disjointSet(int n)
	{
		parent.resize(n);
		rankArr.resize(n, 0);
		for (int i = 0; i < n; i++)
			parent[i] = i; // 初始每个节点为独立集合，父节点指向自身
	}

	// 带路径压缩的查找：返回节点 u 的根
	int find(int u)
	{
		if (parent[u] != u)
			parent[u] = find(parent[u]); // 递归压缩路径
		return parent[u];
	}

	// 将两个集合合并（按秩）
	void unite(int u, int v)
	{
		int rootU = find(u);
		int rootV = find(v);
		if (rootU == rootV) return;

		if (rankArr[rootU] < rankArr[rootV])
			parent[rootU] = rootV;
		else if (rankArr[rootU] > rankArr[rootV])
			parent[rootV] = rootU;
		else
		{
			parent[rootV] = rootU;
			rankArr[rootU]++; // 秩相等时，新根的秩增1
		}
	}

	// 判断两个节点是否在同一集合（同一连通分量）
	bool connected(int u, int v)
	{
		return find(u) == find(v);
	}
};

/*
  Graph 类（基于邻接矩阵）
  - vertexNum: 顶点数
  - adjMatrix: 邻接矩阵，adjMatrix[i][j] 为 i->j 的边权（无边为 0）
  设计说明：
    - 使用邻接矩阵便于实现 Prim 的 O(V^2) 版本（适合中小规模稠密图）。
    - Kruskal 需要边列表（edges），通过扫描上三角矩阵提取所有边。
*/
class Graph {
private:
	int vertexNum;
	vector<vector<int>> adjMatrix;

public:
	Graph(int ver) : vertexNum(ver)
	{
		// 初始化 n x n 的邻接矩阵，默认 0 表示无边
		adjMatrix.resize(ver, vector<int>(ver, 0));
	}

	// 为指定行设置邻接矩阵数据（确保行长度正确）
	void setRow(int row, vector<int> rowValue)
	{
		if (row >= 0 && row < vertexNum && (int)rowValue.size() == vertexNum)
			adjMatrix[row] = rowValue;
	}

	/*
	  Prim 最小生成树（MST）——邻接矩阵的简单实现（贪心）
	  思路（经典版本，时间复杂度 O(V^2)）：
	    1. 维护集合 inMST，记录哪些顶点已加入树。
	    2. 维护 minWeight[v]：当前树到顶点 v 的最小边权，parent[v] 为相应的父节点。
	    3. 每轮选择不在树中且 minWeight 最小的顶点 u，加入树并把对应边加入结果集合。
	    4. 用 u 更新其它顶点的 minWeight（若通过 u 有更小的边）。
	  复杂度：
	    - O(V^2)（选择最小的步骤使用线性扫描）。
	    - 若使用二叉堆/优先队列并用邻接表，可优化到 O(E log V)。
	*/
	vector<edge> primMST(int startVertex = 0)
	{
		vector<edge> result;
		if (startVertex < 0 || startVertex >= vertexNum) return result;

		vector<bool> inMST(vertexNum, false);     // 标记是否已在 MST
		vector<int> minWeight(vertexNum, INT_MAX); // 到树的最小权重
		vector<int> parent(vertexNum, -1);        // 最小边对应的父节点索引

		// 从 startVertex 开始，设其 minWeight 为 0，保证最先被选择
		minWeight[startVertex] = 0;

		// 进行 vertexNum 次选择（最多）
		for (int count = 0; count < vertexNum; count++)
		{
			int u = -1;
			int minW = INT_MAX;
			// 在未加入树的顶点中选择 minWeight 最小的顶点 u
			for (int v = 0; v < vertexNum; v++)
			{
				if (!inMST[v] && minWeight[v] < minW)
				{
					minW = minWeight[v];
					u = v;
				}
			}

			// 若找不到可加顶点（图不连通），结束
			if (u == -1) break;

			inMST[u] = true;

			// 若 u 有父节点，则把这条边加入结果（跳过起始顶点）
			if (parent[u] != -1)
			{
				result.push_back({ parent[u], u, adjMatrix[parent[u]][u] });
			}

			// 使用 u 更新其它未入树顶点的最小权重和父节点
			for (int v = 0; v < vertexNum; v++)
			{
				// 条件：v 未加入树，存在边 u-v（权重非 0），且通过 u 的边权更小
				if (!inMST[v] && adjMatrix[u][v] != 0 && adjMatrix[u][v] < minWeight[v])
				{
					minWeight[v] = adjMatrix[u][v];
					parent[v] = u;
				}
			}
		}
		return result;
	}

	/*
	  将邻接矩阵中的所有边构造成边列表（只取 i < j 上三角，避免重复）
	  目的：为 Kruskal 算法准备边集合。
	*/
	vector<edge> getAllEdges()
	{
		vector<edge> edges;
		for (int i = 0; i < vertexNum; i++)
		{
			for (int j = i + 1; j < vertexNum; j++)
			{
				if (adjMatrix[i][j] != 0)
					edges.push_back({ i, j, adjMatrix[i][j] });
			}
		}
		return edges;
	}

	/*
	  Kruskal 最小生成树（MST）
	  思路（贪心 + 并查集）：
	    1. 获取图的所有边，按权重从小到大排序。
	    2. 依次遍历边，若边的两个端点在不同集合（不形成环），则加入结果并合并集合。
	    3. 当结果边数达到 V-1 时停止。
	 
	*/
	vector<edge> kruskalMST()
	{
		vector<edge> result;
		if (vertexNum <= 0) return result;

		vector<edge> allEdges = getAllEdges();

		// 按权重从小到大排序
		sort(allEdges.begin(), allEdges.end(), [](const edge& a, const edge& b) {
			return a.weight < b.weight;
		});

		disjointSet ds(vertexNum);

		for (const edge& e : allEdges)
		{
			// 若这条边的两个端点不在同一集合中，加入结果并合并集合
			if (!ds.connected(e.src, e.dest))
			{
				ds.unite(e.src, e.dest);
				result.push_back(e);
				// 已找到足够多的边（连通图时为 vertexNum-1）
				if ((int)result.size() == vertexNum - 1) break;
			}
		}
		return result;
	}
};

/*
  主函数：读取邻接矩阵并展示 Prim 与 Kruskal 的结果。
  输入格式说明（交互式）：
    - 先输入顶点数 n（整数），n<=0 时程序退出。
    - 然后依次输入 n 行，每行 n 个整数（用空格分隔），表示邻接矩阵的一行。
    - 最后输入 Prim 的起始顶点（0..n-1）。
  示例：
    4
    0 1 3 0
    1 0 2 4
    3 2 0 5
    0 4 5 0
    0
*/
int main()
{
	int n;
	string line;
	while (true)
	{
		cout << "请输入图的顶点数：";
		if (!(cin >> n)) break; // 非法输入或文件结束则退出
		if (n <= 0) break;

		Graph graph(n);
		cout << "请输入图的邻接矩阵，每行以空格分隔：" << endl;
		// 清除当前行剩余输入，换行符等，准备 getline 读取每一矩阵行
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		for (int i = 0; i < n; i++)
		{
			getline(cin, line);
			stringstream ss(line);
			vector<int> rowValue;
			int val;
			while (ss >> val) rowValue.push_back(val);
			// 如果输入列数不足或过多，setRow 会校验长度相等才能设置
			graph.setRow(i, rowValue);
		}

		int startVertex;
		cout << "请输入Prim算法的起始顶点：";
		cin >> startVertex;

		vector<edge> primResult = graph.primMST(startVertex);
		cout << "Prim算法最小生成树的边为：" << endl;
		for (const edge& e : primResult)
			cout << e.src << " - " << e.dest << " : " << e.weight << endl;

		vector<edge> kruskalResult = graph.kruskalMST();
		cout << "Kruskal算法最小生成树的边为：" << endl;
		for (const edge& e : kruskalResult)
			cout << e.src << " - " << e.dest << " : " << e.weight << endl;
	}
	return 0;
}
