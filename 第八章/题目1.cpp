#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>
#include <string>
using namespace std;

class graph{
    private:
        int vertexNum;// 顶点数
        vector<vector<int>> adjMatrix; //邻接矩阵

    public:
        graph(int ver):vertexNum(ver)
        {
            adjMatrix.resize(ver, vector<int>(ver, 0));// 初始化邻接矩阵为ver行ver列，元素为0。
        }

        void setRow(int row, vector<int> rowValue)
        {
            if(row >= 0 && row < vertexNum && rowValue.size() == vertexNum)// 行数在0到ver-1之间，且行元素个数等于ver
            {
                adjMatrix[row] = rowValue; // 设置一行的数据为rowValue
            }
        }
        
        vector<int> bfs(int startVertex)
        {
            vector<int> result;// 存放结果
            if(startVertex < 0 || startVertex >= vertexNum) return result; // 起始顶点不合法;

            vector<bool> visited(vertexNum, false);// 记录访问过的顶点
            queue<int> bfsQueue; // 广度优先搜索队列

            visited[startVertex] = true; // 起始顶点标记为已访问
            bfsQueue.push(startVertex); // 入队

            while(!bfsQueue.empty())
            {
                int currentVertex = bfsQueue.front(); // 取出队头元素
                bfsQueue.pop(); // 出队
                result.push_back(currentVertex); // 记录访问顺序

                // 遍历邻接矩阵的当前行，找到所有未访问的邻接顶点
                for(int i = 0; i < vertexNum; ++i)
                {
                    if(adjMatrix[currentVertex][i] == 1 && !visited[i]) // 如果有边且未访问
                    {
                        visited[i] = true; // 标记为已访问
                        bfsQueue.push(i); // 入队
                    }
                }
            }
            return result; // 返回访问顺序
        }

        vector<int> dfs(int startVertex)
        {
            vector<int> result;// 存放结果
            if (startVertex < 0 || startVertex >= vertexNum) return result; // 起始顶点不合法;

            vector<bool> visited(vertexNum, false);// 记录访问过的顶点
            dfsRec(startVertex, visited, result); // 调用递归辅助函数
            return result; // 返回访问顺序
        }

        void dfsRec(int vertex, vector<bool>& visited, vector<int>& result)
        {
            visited[vertex] = true; // 标记为已访问
            result.push_back(vertex); // 记录访问顺序

            // 遍历邻接矩阵的当前行，找到所有未访问的邻接顶点
            for(int i = 0; i < vertexNum; ++i)
            {
                if(adjMatrix[vertex][i] == 1 && !visited[i]) // 如果有边且未访问
                {
                    dfsRec(i, visited, result); // 递归访问
                }
            }
        }
        
        void displayMatrix()
        {
            for(int i = 0; i < vertexNum; ++i)
            {
                for(int j = 0; j < vertexNum; ++j)
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

    while (1)
    {
        cout << "请输入顶点数：";
        if (!(cin >> n)) break;
        if (n <= 0) break;

        // 清除到行尾的残留换行，之后使用 getline 读取整行
        cin.ignore(10000, '\n');

        graph g(n);
        cout << "请输入邻接矩阵：\n";
        for (int i = 0; i < n; ++i)
        {
            getline(cin, line);
            stringstream ss(line);
            vector<int> rowValue;
            rowValue.clear();
            int val;
            while (ss >> val)
            {
                rowValue.push_back(val);
            }
            g.setRow(i, rowValue);
        }

        cout << "邻接矩阵为：\n";
        g.displayMatrix();

        int startVertex;
        cout << "请输入起始顶点：";
        cin >> startVertex;

        cout << "广度优先搜索结果为：";
        vector<int> bfsResult = g.bfs(startVertex);
        for (int i = 0; i < bfsResult.size(); ++i)
        {
            cout << bfsResult[i] << " ";
        }
        cout << endl;

        cout << "深度优先搜索结果为：";
        vector<int> dfsResult = g.dfs(startVertex);
        for (int i = 0; i < dfsResult.size(); ++i)
        {
            cout << dfsResult[i] << " ";
        }
        cout << endl;
    }

    return 0;
}   