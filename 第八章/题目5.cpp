#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <list>
using namespace std;

class Graph {
    private:
        int vertexNum;
        vector<list<int> > adjList;

    public:
        Graph(int ver):vertexNum(ver)
        {
            adjList.resize(vertexNum);
        }

        void addEdge(int src,int dest)
        {
            adjList[src].push_back(dest); // 有向图，单向边
        }

        vector<int> sortList() // bfs排序
        {
            vector<int> result(vertexNum);
            vector<bool> visited(vertexNum,false);
            queue<int> inDegree0;// 入度为0的点队列
            vector<int> inDegree(vertexNum,0);

            for(int i = 0; i < vertexNum; i++)
            {
                for(int neighbor : adjList[i])
                {
                    inDegree[neighbor]++;// 计算入度
                }
            }

            for(int i = 0; i < vertexNum; i++)
            {
                if(inDegree[i] == 0)
                {
                    inDegree0.push(i);// 入度为0的点入队
                }
            }

            int index = 0;
            while(!inDegree0.empty())
            {
                int current = inDegree0.front();// 队首出队
                inDegree0.pop();
                result[index++] = current;// 入队点入结果

                for(int neighbor : adjList[current])
                {
                    inDegree[neighbor]--;
                    if(inDegree[neighbor] == 0)
                    {
                        inDegree0.push(neighbor);
                    }
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

        bool hasCycle() // 判断有向图是否有环
        {
            vector<int> sorted = sortList();
            for(int i = 0; i < vertexNum; i++)
            {
                if(sorted[i] == 0 && i != 0)
                {
                    return true; // 有环
                }
            }
            return false; // 无环
        }

};

int main()
{
    int num;
    string line;

    while(1)
    {
        cout << "请输入有向图的顶点数，输入-1结束程序：";
        if(!(cin >> num)) break;
        if(num == -1) break;

        Graph graph(num);
        cout << "请输入邻接表：\n";
        cin.ignore();
        for(int i = 0;i < num;i++)
        {
            cout << "顶点" << i << "的邻接情况：";
            getline(cin, line);
            stringstream ss(line);
            int neighbor;
            
            while(ss >> neighbor)
            {
                if(neighbor == -1) break; // -1表示该行输入结束
                graph.addEdge(i, neighbor);
            }
        }

        cout << "图的邻接表表示：" << endl;
        graph.display();

        cout << "拓扑排序" << endl;
        vector<int> sorted = graph.sortList();
        for(int i = 0; i < num; i++)
        {
            cout << "顶点" << sorted[i] << " ";
        }
        cout << endl;

        if(graph.hasCycle())
        {
            cout << "该有向图有环" << endl;
        }
        else
        {
            cout << "该有向图无环" << endl;
        }

        cout << endl;
    }
}