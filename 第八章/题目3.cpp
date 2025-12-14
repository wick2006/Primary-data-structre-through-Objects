#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>
#include <climits>
using namespace std;

struct edge {
	int src, dest, weight;
};

class disjointSet {
	private:
		vector<int> parent, rank;// parent和rank(秩)数组
	
	public:
		disjointSet(int n)
		{
			parent.resize(n);
			rank.resize(n, 0);

			for(int i = 0; i < n; i++)
			{
				parent[i] = i;// 初始化每个节点为独立集合
			}
		}

		int find(int u)// 查找根节点
		{
			if (parent[u] != u) // 路径压缩,将节点直接连接到根节点
			{
				parent[u] = find(parent[u]);
			}
			return parent[u];
		}

		void union(int u, int v)
		{
			int rootU = find(u);
			int rootV = find(v);

			if (rootU != rootV)// 不在同一集合中
			{
				// 按秩合并,将秩较小的树连接到秩较大的树下
				if(rank[rootU] < rank[rootV])
				{
					parent[rootU] = rootV;
				}
				else if (rank[rootU] > rank[rootV]) // 秩较大,连接较小的
				{
					parent[rootV] = rootU;
				}
				else// 秩相等,任选一棵作为新根,秩加1
				{
					parent[rootV] = rootU;
					rank[rootU]++;
				}
			}

			bool connected(int u, int v)
			{
				return find(u) == find(v);
			}
		}
};

class Graph {
	private:
		int vertexNum;// 顶点数
		vector<int,vector<int>> adjMatrix;// 邻接矩阵

	public:
		Graph(int ver):vertexNum(ver)
		{
			adjMatrix.resize(ver,vector<int>(ver,0));
		}

		void setRow(int row, vector<int> rowValue)
		{
			if(row >= 0 && row < vertexNum && rowValue.size() == vertexNum)
			{
				adjMatrix[row] = rowValue;
			}
		}

		vector<edge> primMST(int startVertex = 0)
		{
			vector<edge> result;
			if (startVertex < 0 || startVertex >= vertexNum) return result;

			vector<bool> inMST(vertexNum, false);// 记录顶点是否在最小生成树中

			vector<int> minWeight(vertexNum, INT_MAX);// 记录每个顶点到最小生成树的最小权重边

			vector<int> parent(vertexNum, -1);// 记录每个顶点在最小生成树中的父节点

			minWeight[startVertex] = 0; // 起始顶点的权重设为0

			for (int count = 0; count < vertexNum - 1; count++)// 需要找到vertexNum - 1个节点
			{
				//u为当前找到的权重最小的顶点，初始化为-1表示未找到
				
				int u = -1;
				int minW = INT_MAX;

				for (int v = 0; v < vertexNum; v++)// 找到不在MST中且权重最小的顶点
				{
					if (!inMST[v] && minWeight[v] < minW)
					{
						minW = minWeight[v];// 更新最小权重
						u = v;// 更新顶点
					}
				}
				
				if (u == -1) break; // 所有顶点都已包含在MST中
				inMST[u] = true; // 将顶点u加入MST

				if (parent[u] != -1)
				{
					result.push_back({ parent[u],u,adjMatrix[parent[u]][u] }) // 将边加入结果
				}

				for (int v = 0; v < vertexNum; v++)// 更新未入树顶点的权重
				{
					//满足条件：v未在MST中，u和v之间有边，且边权小于当前记录的最小权重minWeights[v]
					if(!inMST[v] && adjMatrix[u][v] != 0 && adjMatrix[u][v] < minWeight[v])
					{
						minWeights[v] = adjMatrix[u][v];// 更新最小权重
						parent[v] = u;// 更新父节点
					}
				}
			}
			return result;
		}

		vector<edge> getAllEdges()
		{
			vector<edge> edges;

			for (int i = 0; i < vertexNum; i++)
			{
				for (int j = i + 1; j < vertexNum; j++)
				{
					if(adjMatrix[i][j] != 0)
					{
						edges.push_back({ i, j, adjMatrix[i][j] });// 添加边
					}
				}
			}
		}

		vector<edge> kruskalMST()
		{
			vector<edge> result;
			
			if (vertexNum <= 0) return result;

			vector<edge> AllEdges = getAllEdges();
			// 按边权排序
			sort(allEdges.begin(), allEdges.end());

			disjointSet ds(vertexNum);// 初始化并查集

			for(const edge& e: allEdges)
			{
				if (!ds.connected(e.src, e.dest))// 如果边的两个端点不在同一集合中
				{
					ds.union(e.src, e.dest);// 合并集合
					result.push_back(e);// 将边加入结果

					if(result.size() == vertexNum - 1)// 已找到足够的边
					{
						break;
					}
				}
			}

			return result;
		}

};

int main()
{
	int n;
	string line;
	while (1)
	{
		cout << "请输入图的顶点数：";
		cin >> n;
		if(n <= 0) break;
		Graph graph(n);
		cout << "请输入图的邻接矩阵，每行以空格分隔：" << endl;
		cin.ignore(); //忽略换行符
		for(int i = 0; i < n; i++)
		{
			getline(cin, line);
			stringstream ss(line);
			vector<int> rowValue;
			int val;
			while(ss >> val)
			{
				rowValue.push_back(val);
			}
			graph.setRow(i, rowValue);
		}
		int startVertex;
		cout << "请输入Prim算法的起始顶点：";
		cin >> startVertex;
		vector<edge> primResult = graph.primMST(startVertex);
		cout << "Prim算法最小生成树的边为：" << endl;
		for(const edge& e : primResult)
		{
			cout << e.src << " - " << e.dest << " : " << e.weight << endl;
		}
		vector<edge> kruskalResult = graph.kruskalMST();
		cout << "Kruskal算法最小生成树的边为：" << endl;
		for(const edge& e : kruskalResult)
		{
			cout << e.src << " - " << e.dest << " : " << e.weight << endl;
		}
	}
	return 0;

}

