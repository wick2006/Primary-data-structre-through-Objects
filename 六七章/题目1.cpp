/*
二叉查找树：
    对于每个节点，其左子树上所有节点的值均小于该节点的值，
    其右子树上所有节点的值均大于该节点的值。
*/

#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class treeNode{
    public:
        int value;
        treeNode* left;
        treeNode* right;
        
    
        treeNode(int x):value(x),left(nullptr),right(nullptr){
        
    }
};

class binTree{
    private:
        treeNode* root;
        
        treeNode* buildTree(vector<int>& preorder,int& index)
        {
            if(index >= preorder.size() || preorder[index] == -1)
            {
                index++;
                return nullptr;
            }
            
            treeNode* node = new treeNode(preorder[index++]);
            node->left = buildTree(preorder,index);
            node->right = buildTree(preorder,index);
            
            return node;
        }

        bool isBST(treeNode* node,treeNode*& prev) //中序遍历判断BST
        {
            if(node == nullptr) return true;//如果为空树，返回true
            
            if(!isBST(node->left,prev))//左子树不是BST
                return false;
                
            if(prev != nullptr && node->value <= prev->value)//当前节点值小于等于前一个节点值
                return false;
                
            prev = node;// 更新前一个节点
            
            return isBST(node->right,prev);
        }

        bool inRange(treeNode* node,int* minVal,int* maxVal)
        {
            if(node == nullptr) return true;//
            
            if((minVal != nullptr && node->value <= *minVal) || (maxVal != nullptr && node->value >= *maxVal))
                return false; //节点值不在范围内
                
            return inRange(node->left,minVal,&node->value) && inRange(node->right,&node->value,maxVal);
        }

        void clearTree(treeNode* node)
        {
            if(node == nullptr) return;
            
            clearTree(node->left);
            clearTree(node->right);
            
            delete node;
        }

    public:
        binTree():root(nullptr){}

        ~binTree()
        {
            clearTree(root);
        }

        void buildFromPreorder(vector<int>& preorder)
        {
            int index = 0;
            root = buildTree(preorder,index);
        }

        bool isBST()
        {
            treeNode* prev = nullptr;
            return isBST(root,prev);
        }

        bool isBSTInRange()
        {
            return inRange(root,nullptr,nullptr);
        }

};

int main()
{
    int n;
    string line;

    while(1)
    {
        cout << "输入有多少二叉树需要判断：" << endl;
        cin >> n;
        cin.ignore(); //忽略换行符
        if(n == -1) break;
        for(int i = 0;i < n;i++)
        {
            cout << "输入二叉树的前序遍历序列（-1表示空节点）：" << endl;
            vector<int> preorder;
            int value;
            getline(cin,line);
            stringstream ss(line);
            while(ss >> value)
            {
                preorder.push_back(value);
            }

            binTree tree;
            tree.buildFromPreorder(preorder);

            if(tree.isBST())
                cout << "该二叉树是二叉搜索树" << endl;
            else
                cout << "该二叉树不是二叉搜索树" << endl;
        }
        
    }
}