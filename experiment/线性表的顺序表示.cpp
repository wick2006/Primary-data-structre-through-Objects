#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class seqList{
    private:
        vector<int> data;
        int length;

    public:
        seqList(int n):length(n)
        {
            data.resize(n);
        }

        seqList(int n,vector<int> vec):length(n)
        {
            data = vec;
        }

        void insert(int pos,int x)// 实现插入
        {
            data.resize(length+1);
            for(int i = length;i > pos;i--)
            {
                data[i] = data[i-1];
            }
            data[pos] = x;
            length++;
        }
        
        void deletePos(int pos)// 实现删除
        {
            for(int i = pos;i < length-1;i++)
            {
                data[i] = data[i+1];
            }
            length--;
            data.resize(length);
        }
        
        int findPos(int pos)// 实现查找位置
        {
            return data[pos];
        }

        int findX(int x) // 实现查找值,没找到返回-1
        {
            for(int i = 0;i < length;i++)
            {
                if(data[i]==x) return i;
            }

            return -1;
        }

        void display() // 实现打印
        {
            for(int i = 0;i < length;i++)
            {
                cout<<data[i]<<" ";
            }
            cout<<endl;
        }

};

int main()
{
    int num;
    cout << "请输入线性表的长度：";
    cin >> num;

    int op;
    int pos,x;
    cout << "请输入线性表初始值：";
    string line;
    vector<int> vec;//传入初始值
    int val;// 临时变量
    cin.ignore();
    getline(cin, line);
    stringstream ss(line);
    while(ss >> val)
    {
        vec.push_back(val);
    }

    seqList list(num,vec);

    while (1)
    {
        cout << "1.插入 2.删除 3.查找位置 4.查找值 5.打印 0.退出" << endl;
        cout << "请输入操作类型：";
        cin >> op;
        if (op == 0) break;
        switch (op)
        {
        case 1:
            cout << "请输入插入位置：";
            cin >> pos;
            cout << "请输入插入值：";
            cin >> x;
            list.insert(pos,x);
            break;
        case 2:
            cout << "请输入删除位置：";
            cin >> pos;
            list.deletePos(pos);
            break;
        case 3:
            cout << "请输入查找位置：";
            cin >> pos;
            cout << "查找位置为：" << list.findPos(pos) << endl;
            break;
        case 4:
            cout << "请输入查找值：";
            cin >> x;
            cout << "查找值在第" << list.findX(x) + 1<< "位" << endl;// 返回为数组下标+1
            break;
        case 5:
            list.display();
            break;
        default:
            cout << "输入错误！" << endl;
            break;
        }
    }
    return 0;
}