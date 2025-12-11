#include <iostream>
#include <vector>   
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class treeNode{
    public:
        int value;
        treeNode* left;
        treeNode* right;

        treeNode(int x):value(x),left(nullptr),right(nullptr){
        
    }
};

class binarySearchTree{
    private:
        treeNode* root;

        treeNode* insert(treeNode* node, int value)
        {
            if(node == nullptr)
            {
                return new treeNode(value);
            }

            if(value < node->value)
            {
                node->left = insert(node->left, value);
            }
            else if(value > node->value)
            {
                node->right = insert(node->right, value);
            }

            return node;
        }

        bool search(treeNode* node, int value)
        {
            if(node == nullptr) return false;

            if(node->value == value) return true;
            
            if(value < node->value)
            {
                return search(node->left, value);
            }
            else if(value > node->value)
            {
                return search(node->right, value);
            }

        }

        treeNode* minNode(treeNode* node)
        {
            treeNode* current = node;
            while(current && current->left != nullptr)
            {
                current = current->left;
            }
            return current; // 二叉查找树的最小值一定是最左边的节点
        }

        treeNode* deleteNode(treeNode* node, int value)
        {
            if(node == nullptr) return node;

            if(value < node->value)
            {
                node->left = deleteNode(node->left, value);
            }
            else if(value > node->value)
            {
                node->right = deleteNode(node->right, value);
            }
            else
            {
                if(node->left == nullptr && node->right == nullptr)
                {
                    delete node;
                    node = nullptr;
                }
                else if(node->left == nullptr)// 只有右子树
                {
                    treeNode* temp = node->right;
                    delete node;
                    return temp;
                    
                }
                else if(node->right == nullptr)// 只有左子树
                {
                    treeNode* temp = node->left;
                    delete node;
                    return temp;
                }
                else // 有两个子树
                {
                    treeNode* temp = minNode(node->right);// 找到右子树的最小值
                    node->value = temp->value;  // 用右子树的最小值代替当前节点的值
                    node->right = deleteNode(node->right, temp->value);// 删除右子树的最小值
                }
            }
            
            return node;
        }

        

    public:
        binarySearchTree():root(nullptr){}

        ~binarySearchTree()
        {
            clearTree(root);
        }

        void buildTree(vector<int>& data)
        {
            for(int i = 0;i < data.size();i++)
            {
                root = insert(root, data[i]);
            }
        }
    
        void insertNode(int value)
        {
            root = insert(root, value);
        }

        bool searchNode(int value)
        {
            return search(root, value);
        }

        void deleteNode(int value)
        {
            root = deleteNode(root, value);
        }

        void displayTree(treeNode* node)// 中序遍历显示树的节点值
        {
            if(node == nullptr) return;

            displayTree(node->left);
            cout << node->value << " ";
            displayTree(node->right);
        }
        
        treeNode* getRoot()
        {
            if(root == nullptr) return nullptr;
            return root;
        }

        void clearTree(treeNode* node)
        {
            if(node == nullptr) return;

            clearTree(node->left);
            clearTree(node->right);

            delete node;
        }
};

int main()
{
    binarySearchTree bst;
    int n;
    string line;
    while(1)
    {
        
        cout << "请输入树的节点数：";
        cin >> n;
        if(n <= 0) break;
        vector<int> data(n);

        cout << "请输入树的节点值：" << endl;
        cin.ignore();
        getline(cin, line);
        stringstream ss(line);
        for(int i = 0;i < n;i++)
        {
            ss >> data[i];
        }
        
        bst.buildTree(data);
        cout << "建立二叉查找树成功" << endl;
        bst.displayTree(bst.getRoot());
        cout << endl;

        cout << "请输入要查找的节点值：";
        int searchVal;
        cin >> searchVal;
        if(bst.searchNode(searchVal))
        {
            cout << "找到节点" << endl;
        }
        else
        {
            cout << "未找到节点" << endl;
        }

        cout << "请输入要删除的节点值：";
        int deleteVal;
        cin >> deleteVal;
        cout << "删除前：" << endl;
        bst.displayTree(bst.getRoot());
        cout << endl;
        bst.deleteNode(deleteVal);
        cout << "删除后："<< endl;
        bst.displayTree(bst.getRoot());
        cout << endl;

    }


}