#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <sstream>
using namespace std;

class treeNode{
    public:
        int value;
        treeNode* left;
        treeNode* right;
        treeNode* leafNext;
        
    treeNode(int x):value(x),left(nullptr),right(nullptr),leafNext(nullptr){}
    
};

class leafNode{
    public:
        int value;
        leafNode* next;
        
    leafNode(int x):value(x),next(nullptr){
        
    }
};

class binTree{
    private:
        treeNode* root;
        leafNode* leafHead;
        leafNode* leafTail;
        
    treeNode* build(const vector<int>& preorder, int& current)
    {
        if(current >= preorder.size() || preorder[current] == 0)
        {
            current++;
            return nullptr;//如果是空节点返回空指针 
        }
        
        treeNode* tempNode = new treeNode(preorder[current]);
        current++;
        
        tempNode -> left = build(preorder,current);
        tempNode -> right = build(preorder,current);
        
        return tempNode;
    }
    
    void linkLeaves(treeNode* node)
    {
        if(node == nullptr)
        {
            return;
        }
        
        if(node -> left == nullptr && node -> right == nullptr)
        {
            leafNode* newLeaf = new leafNode(node -> value);
            
            if(leafHead == nullptr)
            {
                leafHead = leafTail = newLeaf;
            }
            else
            {
                leafTail -> next = newLeaf;
                leafTail = newLeaf;	
            }
        }
        
        linkLeaves(node -> left);
        linkLeaves(node -> right);
    }
    
    void clearLeaf()
    {
        leafNode* current = leafHead;
        while(current != nullptr)
        {
            leafNode* temp = current;
            current = current -> next;
            
            delete temp;
        }
        
        leafHead = leafTail = nullptr;
    }
    
    void clearTree(treeNode* node)
    {
        if(node == nullptr) return;
        
        clearTree(node -> left);
        clearTree(node -> right);
        
        delete node;
    }
    
    public:
        binTree():root(nullptr),leafHead(nullptr),leafTail(nullptr){}
        
        ~binTree()
        {
            clearTree(root);
            clearLeaf();
        }
        
        void buildTree(const vector<int>& preorder)
        {
            int index = 0;
            root = build(preorder,index);//buildTree中的root指向根节点，通过递归建立所有节点 
        }
        
        void buildLeafList()
        {
            clearLeaf();
            linkLeaves(root);
        }
        
        void displayLeaf()
        {
            if(leafHead == nullptr)
            {
                cout << "无叶子节点" << endl;
                return;
            }
            
            leafNode* current = leafHead;
            while(current != nullptr)
            {
                cout << current -> value;
                current = current -> next;
            }			
            
            cout << endl;
            
        }
};

int main()
{
    int treeNum;
    while(1)
    {
        cout << "请输入要进行测试的二叉树数量，输入-1结束程序：";
        if(!(cin >> treeNum)) {
            // 输入不是数字
            cin.clear();  // 清除错误状态
            cin.ignore(1000, '\n');  // 清空输入缓冲区
            cout << "请输入有效的数字！" << endl;
            continue;
        }
        
        if(treeNum == -1) {
            break;
        }
        
        if(treeNum <= 0) {
            cout << "请输入大于0的数字！" << endl;
            continue;
        }
        
        cin.ignore();  // 读取回车符
        
        for(int i = 0; i < treeNum; i++)
        {
            cout << "第" << i+1 << "棵树:" << endl;
            
            // 读取前序遍历序列
            cout << "请输入前序遍历序列，用空格分隔，以回车结束: ";
            vector<int> preorder;
            
            string line;
            getline(cin, line);
            
            if(line.empty()) {
                cout << "输入为空，请重新输入" << endl;
                continue;
            }
            
            stringstream ss(line);
            int val;
            bool hasError = false;
            
            while(ss >> val) {
                preorder.push_back(val);
            }
            
            // 检查是否成功读取所有数据
            if(ss.fail() && !ss.eof()) {
                cout << "警告：输入中包含无法读取的字符，已读取" << preorder.size() << "个" << endl;
                hasError = true;
            }
            
            // 构建并显示
            binTree tree;
            if(!hasError) {
                tree.buildTree(preorder);
                tree.buildLeafList();
                cout << "叶子节点按顺序输出为: ";
                tree.displayLeaf();
            }
        }
        
        cout << endl;
        
    }
}