#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>
#include <sstream>
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
        unordered_map<int,int> inorderMap;// 存储每个节点值对应的中序遍历下标
        
        treeNode* build(vector<int>& postorder,int postStart,int postEnd,
                        vector<int>& inorder,int inStart,int inEnd)
        {
            if(postStart > postEnd || inStart > inEnd)
            {
                return nullptr;
            }
            
            int rootVal = postorder[postEnd];
            treeNode* root = new treeNode(rootVal);//根节点是后序遍历的最后一个元素 
            
            int rootIndex = inorderMap[rootVal]; //根据根节点的值，在中序遍历的map中找到下标
            
            int leftSize = rootIndex - inStart; //左子树的节点数.
            
             // 递归构建左子树
            // 后序遍历的区间: [postStart, postStart + leftSize - 1]
            // 中序遍历的区间: [inStart, rootIndex - 1]
            root->left = build(postorder,postStart,postStart + leftSize - 1,
                                 inorder,inStart,rootIndex - 1);
                                 
            // 递归构建右子树 [postStart + leftSize, postEnd - 1](postEnd为根节点) 
            // 中序遍历区间:[rootIndex + 1,inEnd] 
            root->right = build(postorder,postStart + leftSize,postEnd -1,
                                inorder,rootIndex + 1,inEnd);
                                
            return root;
                                
        }
        
        void preorder(treeNode* node,vector<int>& result)
        {
            if(node == nullptr) return;
            
            result.push_back(node->value);
            preorder(node->left,result);
            preorder(node->right,result);
        }
        
        void clearTree(treeNode* node)
        {
            if(node == nullptr) return;
            
            clearTree(node -> left);
            clearTree(node->right);
            delete node;
        }
        
    public:
        
        binTree() : root(nullptr){}
        
        ~binTree()
        {
            clearTree(root);
        }
        
        
        void buildFromInPost(vector<int>& postorder,vector<int>& inorder)
        {
            clearTree(root);
            root = nullptr;
            
            inorderMap.clear();
            
            for(int i = 0;i < inorder.size();i++)
            {
                inorderMap[inorder[i]] = i;// 把inorder[i]的值对应下标存入map(如3,5,4对应0,1,2)
                 
            }
            
            root = build(postorder,0,postorder.size() - 1,
                         inorder,0,inorder.size() - 1);
        }
        
        vector<int> getPreorder()
        {
            vector<int> result;
            preorder(root,result);
            return result;
        }
        
        void display()
        {
            vector<int> preorder = getPreorder();
            for(int i = 0;i < preorder.size();i++)
            {
                cout << preorder[i] << " ";
            }
            cout << endl;
        }
};

int main()
{
    int treeNum;
    while (true) {
        cout << "请输入要进行测试的二叉树数量，输入-1结束程序：";
        cin >> treeNum;
        
        if (treeNum == -1) {
            break;
        }
        
        if (treeNum <= 0) {
            cout << "请输入大于0的数字！" << endl;
            continue;
        }
        
        // 清空输入缓冲区
        cin.ignore(1000, '\n');
        
        for (int i = 0; i < treeNum; i++) {
            cout << "\n第" << i + 1 << "棵树:" << endl;
            
            // 读取后序遍历
            cout << "请输入该树的后序遍历序列，用空格分隔，以回车结束：";
            vector<int> postorder;
            string line;
            
            getline(cin, line);  // 读取一行
            stringstream ss(line);
            int value;
            
            while (ss >> value) {
                postorder.push_back(value);
            }
            
            // 读取中序遍历
            cout << "请输入该树的中序遍历序列，用空格分隔，以回车结束：";
            vector<int> inorder;
            
            getline(cin, line);  // 读取一行
            stringstream ss2(line);
            
            while (ss2 >> value) {
                inorder.push_back(value);
            }
            
            // 检查两个序列长度是否匹配
            if (postorder.size() != inorder.size()) {
                cout << "错误：后序遍历和中序遍历的节点数不一致！" << endl;
                continue;
            }
            
            // 构建并输出前序遍历
            binTree tree;
            tree.buildFromInPost(postorder, inorder);
            
            cout << "该树的前序遍历为：";
            tree.display();
        }
    }
}