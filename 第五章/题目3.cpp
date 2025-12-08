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
		unordered_map<int,int> inorderMap;// 构建对应根节点的索引，方便查找
		
		treeNode* build(vector<int>& postorder,int postStart,int postEnd,
						vector<int>& inorder,int inStart,int inEnd)
		{
			if(postStart > postEnd || inStart > inEnd)
			{
				return nullptr;
			}
			
			int rootVal = postorder[postEnd];
			treeNode* root = new treeNode(rootVal);//根节点是后序遍历的最后一个元素 
			
			int rootIndex = inorderMap[rootVal]; //根据根节点的值快速搜索到索引，map在后面初始化。
			
			int leftSize = rootIndex - inStart; //左子树的节点数.
			
			 // 递归构建左子树
        	// 左子树的后序遍历范围: [postStart, postStart + leftSize - 1]
        	// 左子树的中序遍历范围: [inStart, rootIndex - 1]
        	root->left = build(postorder,postStart,postStart + leftSize - 1,
								 inorder,inStart,rootIndex - 1);
								 
			// 右子树后序遍历：[postStart + leftSize, postEnd - 1](postEnd为根节点) 
			// 右子树中序遍历:[rootIndex + 1,inEnd] 
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
				inorderMap[inorder[i]] = i;// 将inorder[i]这个值对应到索引(如3,5,4对应0,1,2)
				 
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
        cout << "输入有多少棵二叉树要进行测试（以-1结束整个程序的运行）：";
        cin >> treeNum;
        
        if (treeNum == -1) {
            break;
        }
        
        if (treeNum <= 0) {
            cout << "请输入大于0的数字！" << endl;
            continue;
        }
        
        // 清除输入缓冲区
        cin.ignore(1000, '\n');
        
        for (int i = 0; i < treeNum; i++) {
            cout << "\n第" << i + 1 << "棵树:" << endl;
            
            // 读取后序遍历序列
            cout << "输入二叉树的后序遍历序列（以空格分隔，回车结束）：";
            vector<int> postorder;
            string line;
            
            getline(cin, line);  // 读取整行
            stringstream ss(line);
            int value;
            
            while (ss >> value) {
                postorder.push_back(value);
            }
            
            // 读取中序遍历序列
            cout << "输入二叉树的中序遍历序列（以空格分隔，回车结束）：";
            vector<int> inorder;
            
            getline(cin, line);  // 读取整行
            stringstream ss2(line);
            
            while (ss2 >> value) {
                inorder.push_back(value);
            }
            
            // 检查序列长度是否匹配
            if (postorder.size() != inorder.size()) {
                cout << "错误：后序遍历序列和中序遍历序列长度不一致！" << endl;
                continue;
            }
            
            // 构建二叉树并显示前序遍历
            binTree tree;
            tree.buildFromInPost(postorder, inorder);
            
            cout << "二叉树的前序遍历序列：";
            tree.display();
        }
    }
}
