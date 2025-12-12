#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <list>

using namespace std;

class Graph {
    private:
        int vertexNum;// 顶点数
        vector<list <int> > adjList;// 邻接表   

    public:
        Graph(int ver):vertexNum(ver) 
        {
            adjList.resize(ver);
        }

        void setRow(int row, vector<int> rowValue)
        {
            if(row >= 0 && row < vertexNum && rowValue.size() == vertexNum)
            {
                adjList[row].clear();
                for(int i = 0; i < vertexNum; i++)
                {
                    if(rowValue[i] == 1)
                    {
                        adjList[row].push_back(i);
                    }
                }
            }


        }

        vector<int> bfs(int start)
        {
            vector<int> result;
            if(start < 0 || start >= vertexNum) return result;
            
            vector<bool> visited(vertexNum, false);
            queue<int> bfsQueue;
            
            visited[start] = true;
            bfsQueue.push(start);

            while(!bfsQueue.empty())
            {
                int current = bfsQueue.front();
                bfsQueue.pop();
                result.push_back(current);
                for(int neighbor : adjList[current])
                {
                    if(!visited[neighbor])
                    {
                        visited[neighbor] = true;
                        bfsQueue.push(neighbor);
                    }
                }
                
            }

            return result;
        }

        vector<int> dfs(int start)
        {
            vector<int> result;
            if(start < 0 || start >= vertexNum)   return result;
            
            vector<bool> visited(vertexNum, false);
            dfsRec(start, visited, result);
            return result;
        }

        vector<int> dfsRec(int vertex, vector<bool>& visited, vector<int>& result)
        {
            visited[vertex] = true;
            result.push_back(vertex);

            for(int neighbor : adjList[vertex])
            {
                if(!visited[neighbor])
                {
                    dfsRec(neighbor, visited, result);                   
                }
            }

            return result;
        }

        void display()
        {
            for(int i = 0; i < vertexNum; i++)
            {
                cout << "Vertex " << i << ": ";
                for(int neighbor : adjList[i])
                {
                    cout << neighbor << " ";
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

        cout << "图的邻接表表示为：" << endl;
        graph.display();

        int startVertex;
        cout << "请输入BFS和DFS的起始顶点：";
        cin >> startVertex;

        vector<int> bfsResult = graph.bfs(startVertex);
        cout << "BFS访问顺序：";
        for(int v : bfsResult)
        {
            cout << v << " ";
        }
        cout << endl;

        vector<int> dfsResult = graph.dfs(startVertex);
        cout << "DFS访问顺序：";
        for(int v : dfsResult)
        {
            cout << v << " ";
        }
        cout << endl;
    }
    
}