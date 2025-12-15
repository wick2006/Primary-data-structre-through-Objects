#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <sstream>
#include <list>
using namespace std;

class Graph{
    private:
        int vertexNum;// 顶点数
        vector<list <int> > adjList;// 邻接表
    
    public:
        Graph(int ver):vertexNum(ver)
        {
            adjList.resize(ver);
        }

        void addEdge(int src, int dest)
        {
            if(src >= 0 && src < vertexNum && dest >=0 && dest < vertexNum)
            {
                adjList[src].push_back(dest);// 有向图,从src指向dest
            }
        }

        vector<int> sortList() //存储顶点的排序
        {
            vector<int> result;
            vector<bool> visited(vertexNum, false);
            vector<int> inDegeree(vertexNum, 0);
            queue<int> q;//存储入度为0的顶点
        
            for(int i = 0;i < vertexNum;i++)
            {
                for(int neighbor:adjList[i])// 计算每个顶点的入度
                {
                    inDegeree[neighbor]++; // indegree加1
                }
            }

            for(int i = 0;i < vertexNum;i++)
            {
                if(inDegeree[i] == 0)
                {
                    q.push(i); // 入度为0的顶点入队
                }
            }

            while(!q.empty())
            {
                int current = q.front();
                q.pop();
                result.push_back(current);
                for(int neighbor:adjList[current])
                {
                    inDegeree[neighbor]--;// 移除当前顶点的边
                    if(inDegeree[neighbor] == 0)// 如果邻接点入度为0，加入队列
                    {
                        q.push(neighbor);
                    }
                }
            }
            return result;
        }

        bool hasCircle()
        {
            vector<int> result = sortList();
            return result.size() < vertexNum; // 排序后的顶点数小于顶点数，说明有环
        }

        void displayList()
        {
            for(int i = 0;i < vertexNum;i++)
            {
                cout << "顶点 " << i << ": ";
                for(int neighbor:adjList[i])
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
        cout << "请输入顶点数: ";
        cin >> n;
        if(n <= 0)
        {
            break;
        }

        Graph graph(n);
        cout << "请输入图的邻接表，每行以空格分隔：" << endl;
        cin.ignore(); // 忽略换行符

        cout << "请输入邻接表：\n";
        for(int i = 0;i < n;i++)
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

        cout << endl;
        cout << "图的邻接表：" << endl;
        graph.displayList();

        cout << "是否有环？" << (graph.hasCircle()? "有" : "无") << endl;
        
        if(graph.hasCircle())
        {
            cout << "图中有环，无法进行拓扑排序。" << endl;
            continue;
        }

        cout << "顶点的排序：" << endl;
        vector<int> result = graph.sortList();
        for(int i = 0;i < result.size();i++)
        {
            cout << result[i] << " ";
        }
    }
}
