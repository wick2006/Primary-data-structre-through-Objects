#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <algorithm>
using namespace std;

class Graph {
private:
	int vertexNum;// 顶点数
	vector<vector<int>> adjMatrix; //邻接矩阵

public:
	Graph(int ver) :vertexNum(ver)
	{
		adjMatrix.resize(ver, vector<int>(ver, 0));// 初始化邻接矩阵为ver行ver列，元素为0。
		// 保持自环为 0（表示无边或不考虑自环）
		for (int i = 0; i < ver; i++)
		{
			adjMatrix[i][i] = 0;
		}
	}

	void setRow(int row, vector<int> rowVal)
	{
		if (row >= 0 && row < vertexNum)
		{
			// 容错：不足则填充，过多则截断
			if ((int)rowVal.size() < vertexNum) rowVal.resize(vertexNum, 0);
			else if ((int)rowVal.size() > vertexNum) rowVal.resize(vertexNum);
			adjMatrix[row] = rowVal; // 设置一行的数据为rowValue
		}
	}

	// Dijkstra：返回 pair<dist, src>
	// dist[i] = startVertex 到 i 的最短距离（不可达为 INT_MAX）
	// src[i] = i 的前驱节点（start 的前驱为 start），不可达为 -1
	pair<vector<int>, vector<int>> dijkstra(int startVertex)
	{
		vector<int> dist(vertexNum, INT_MAX); // 存储起点到各顶点的最短距离
		vector<int> src(vertexNum, -1); // 存储最短路径的前驱节点（保持原始变量名 src）
		vector<bool> visited(vertexNum, false); // 标记顶点是否已确定最短路径

		// 边界检查
		if (startVertex < 0 || startVertex >= vertexNum) return { dist, src };

		dist[startVertex] = 0; // 起点到自身距离为0
		src[startVertex] = startVertex; // 起点的前驱节点设为自身

		for (int count = 0; count < vertexNum; count++)
		{
			int u = -1;
			int minDist = INT_MAX;// 找到未访问顶点中距离起点最近的顶点u

			for (int v = 0; v < vertexNum; v++)// v是准备寻找的顶点
			{
				if (!visited[v] && dist[v] < minDist)
				{
					minDist = dist[v];
					u = v;// 更新最近顶点
				}
			}

			if (u == -1) break; // 所有可达顶点均已访问，结束

			visited[u] = true; // 标记顶点u为已访问

			for (int v = 0; v < vertexNum; v++)// 使用顶点u更新其它未访问顶点的距离
			{
				// 注意：这里约定 0 表示无边，若需支持 0 权重边需改用其他哨兵
				if (!visited[v] && adjMatrix[u][v] != 0 && dist[u] != INT_MAX) // 存在边u-v且v未访问
				{
					int newDist = dist[u] + adjMatrix[u][v];
					if (newDist < dist[v]) // 通过u到v的距离更短
					{
						dist[v] = newDist; // 更新最短距离
						src[v] = u; // 更新前驱节点（使用原名 src）
					}
				}
			}
		}

		return { dist, src }; // 返回距离和前驱（前驱数组名为 src，未改动）
	}

	// 递归打印从 start 到 vertex 的路径（使用原始变量名 src）
	void printPath(int vertex, const vector<int>& src)
	{
		// 防御性：若索引越界或 src[vertex] 为 -1（不可达且非起点），直接打印 vertex
		if (vertex < 0 || vertex >= vertexNum || src[vertex] == -1)
		{
			cout << vertex;
			return;
		}
		// 若到达起点（src[vertex] == vertex），打印起点并返回，避免无限递归
		if (src[vertex] == vertex)
		{
			cout << vertex;
			return;
		}
		// 递归打印前驱路径
		printPath(src[vertex], src);
		cout << " -> " << vertex;
	}

	// 合并：计算并打印源点到所有顶点的最短距离与路径
	void printAllShortestPaths(int startVertex)
	{
		auto res = dijkstra(startVertex);
		vector<int> dist = res.first;
		vector<int> src = res.second;

		cout << "起点 " << startVertex << " 到各顶点的最短路径信息：" << endl;
		for (int v = 0; v < vertexNum; v++)
		{
			if (dist[v] == INT_MAX)
			{
				cout << "顶点 " << v << " 不可达" << endl;
			}
			else
			{
				cout << "顶点 " << v << " 的最短距离 = " << dist[v] << "，路径 = ";
				printPath(v, src);
				cout << endl;
			}
		}
	}

	void displayMatrix()
	{
		for (int i = 0; i < vertexNum; i++)
		{
			for (int j = 0; j < vertexNum; j++)
			{
				cout << adjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
};

int main()
{
	int n;
	string line;

	while (true)
	{
		cout << "请输入图的顶点数：";
		if (!(cin >> n)) break;
		if (n <= 0) break;
		cin.ignore(); // 忽略换行符

		Graph graph(n);

		cout << "请输入图的邻接矩阵，每行以空格分隔：" << endl;
		for (int i = 0; i < n; i++)
		{
			getline(cin, line);
			// 如果读取到空行，重读一次（容错）
			if (line.size() == 0) { i--; continue; }
			stringstream ss(line);
			vector<int> rowValue;
			int val;
			while (ss >> val)
			{
				rowValue.push_back(val);
			}
			graph.setRow(i, rowValue);
		}

		cout << endl;
		graph.displayMatrix();

		int startVertex;
		cout << "请输入Dijkstra的起始顶点：";
		if (!(cin >> startVertex)) break;

		// 使用单一函数计算并打印起点到各顶点的最短路径与距离（不改变原始变量名）
		graph.printAllShortestPaths(startVertex);
	}
	return 0;
}