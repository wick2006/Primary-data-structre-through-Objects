#include<iostream>
#include<stack>
#include<sstream>
#include<vector>
#include<cmath>
using namespace std;

class treeNode{
    public:
        int value;
        treeNode* left;
        treeNode* right;
        
        treeNode(int x):value(x),left(nullptr),right(nullptr)
        {
        }
};

class binTree{
    private:
        treeNode* root;
        vector<int> result;
        
        treeNode* build(const vector<int>& preorder,int& index)// 根据前序遍历递归建立二叉树 
        {
            if(index >= preorder.size() || preorder[index] == 0)
            {
                index++;
                return nullptr;
            }
            
            treeNode* node = new treeNode(preorder[index]);
            index++;
            
            node->left = build(preorder,index);
            node->right = build(preorder,index);
            return node;
        }
        
        int getHeight(treeNode* node)
        {
            if(node == nullptr) return 0;
            
            int leftHeight = getHeight(node->left);
            int rightHeight = getHeight(node->right);
            
            return max(leftHeight,rightHeight)+1;
        }
        
        void findNode(treeNode* node)
        {
            if(node == nullptr) return;
            
            int leftHeight = getHeight(node->left);
            int rightHeight = getHeight(node->right);//计算左右子树高度
            
            if(abs(leftHeight - rightHeight) == 2)
            {
                result.push_back(node->value);
             } 
             
            findNode(node->left);
            findNode(node->right);
        }
        
        void clear(treeNode* node)
        {
            if(node == nullptr) return;
            
            clear(node->left);
            clear(node->right);
            
            delete node;
        }
        
    public:
        
        binTree():root(nullptr)
        {
            
        }
        
        ~binTree()
        {
            clear(root);
        }
        
        void build_from_preorder(vector<int>& preorder)
        {
            int index = 0;
            root = build(preorder,index);		
        }		
        
        vector<int> findResult()
        {
            result.clear();
            findNode(root);
            return result;
        }
        
        void display()
        {
            vector<int> node = findResult();
            
            if(node.empty())
            {
                cout << "没有满足条件的节点" << endl;
            }
            else
            {
                for(int i = 0;i < node.size();i++)
                {
                    cout << node[i] << " ";
                }
                
                cout << endl;
            }
        }
        
        
};

int main()
{
    int treeNum;
    
    while(1)
    {
        cout << "请输入要进行测试的二叉树数量，输入-1结束程序：";
        cin >> treeNum;
        
        if(treeNum == -1) break;

        cin.ignore(100000,'\n');
        
        for (int i = 0; i < treeNum; i++) 
        {
            cout << "\n第" << i + 1 << "棵树:" << endl;
            cout << "请输入该树的前序遍历序列（节点值为0表示空节点），用空格分隔，以回车结束：";
            
            vector<int> preorder;
            string line;
            
            getline(cin,line);
            stringstream ss(line);
            int value;
            while(ss >> value)
            {
                preorder.push_back(value);
            }
            
            binTree tree;
            tree.build_from_preorder(preorder);
            
            cout << "该树左右子树高度差为2的节点值有：";
            tree.display();
            
        }
    }
}