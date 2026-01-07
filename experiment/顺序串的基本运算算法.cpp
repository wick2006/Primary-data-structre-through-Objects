#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// 二叉树节点结构
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val = 0) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;
    
    // 辅助函数
    TreeNode* copyTree(TreeNode* node) {
        if (!node) return nullptr;
        
        TreeNode* newNode = new TreeNode(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }
    
    void destroyTree(TreeNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
    // 先序遍历建立二叉树
    TreeNode* buildFromPreOrder(vector<int>& pre, int& index, int stopValue) {
        if (index >= pre.size() || pre[index] == stopValue) {
            index++;
            return nullptr;
        }
        
        TreeNode* node = new TreeNode(pre[index++]);
        node->left = buildFromPreOrder(pre, index, stopValue);
        node->right = buildFromPreOrder(pre, index, stopValue);
        return node;
    }
    
    // 递归遍历函数
    void preOrderRecursive(TreeNode* node) {
        if (!node) return;
        cout << node->data << " ";
        preOrderRecursive(node->left);
        preOrderRecursive(node->right);
    }
    
    void inOrderRecursive(TreeNode* node) {
        if (!node) return;
        inOrderRecursive(node->left);
        cout << node->data << " ";
        inOrderRecursive(node->right);
    }
    
    void postOrderRecursive(TreeNode* node) {
        if (!node) return;
        postOrderRecursive(node->left);
        postOrderRecursive(node->right);
        cout << node->data << " ";
    }
    
    // 统计函数
    int getDepth(TreeNode* node) {
        if (!node) return 0;
        return max(getDepth(node->left), getDepth(node->right)) + 1;
    }
    
    int countNodes(TreeNode* node) {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
    
    int countLeaves(TreeNode* node) {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;
        return countLeaves(node->left) + countLeaves(node->right);
    }
    
    int countDegree1(TreeNode* node) {
        if (!node) return 0;
        
        int count = 0;
        if ((!node->left && node->right) || (node->left && !node->right)) {
            count = 1;
        }
        
        return count + countDegree1(node->left) + countDegree1(node->right);
    }
    
    int countDegree2(TreeNode* node) {
        if (!node) return 0;
        
        int count = 0;
        if (node->left && node->right) {
            count = 1;
        }
        
        return count + countDegree2(node->left) + countDegree2(node->right);
    }
    
    // 路径输出
    void printPaths(TreeNode* node, vector<int>& path) {
        if (!node) return;
        
        path.push_back(node->data);
        
        if (!node->left && !node->right) {
            cout << "路径: ";
            for (int val : path) {
                cout << val << " ";
            }
            cout << endl;
            
            cout << "逆路径: ";
            for (int i = path.size() - 1; i >= 0; i--) {
                cout << path[i] << " ";
            }
            cout << endl;
        } else {
            printPaths(node->left, path);
            printPaths(node->right, path);
        }
        
        path.pop_back();
    }
    
public:
    // 构造函数
    BinaryTree() : root(nullptr) {}
    
    // 拷贝构造函数
    BinaryTree(const BinaryTree& other) {
        root = copyTree(other.root);
    }
    
    // 赋值运算符
    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            destroyTree(root);
            root = copyTree(other.root);
        }
        return *this;
    }
    
    // 析构函数
    ~BinaryTree() {
        destroyTree(root);
    }
    
    // 1. 先建立节点，再建立树（层次建立）
    void createByLevel() {
        destroyTree(root);
        root = nullptr;
        
        cout << "按层次顺序输入节点值(空格分隔，-1表示空节点):" << endl;
        string line;
        cin.ignore();
        getline(cin, line);
        
        vector<int> values;
        stringstream ss(line);
        int val;
        
        while (ss >> val) {
            values.push_back(val);
        }
        
        if (values.empty() || values[0] == -1) return;
        
        queue<TreeNode*> q;
        root = new TreeNode(values[0]);
        q.push(root);
        
        int i = 1;
        while (!q.empty() && i < values.size()) {
            TreeNode* current = q.front();
            q.pop();
            
            if (i < values.size() && values[i] != -1) {
                current->left = new TreeNode(values[i]);
                q.push(current->left);
            }
            i++;
            
            if (i < values.size() && values[i] != -1) {
                current->right = new TreeNode(values[i]);
                q.push(current->right);
            }
            i++;
        }
    }
    
    // 2. 通过先序遍历序列建立
    void createByPreOrder() {
        destroyTree(root);
        root = nullptr;
        
        cout << "输入先序遍历序列(空格分隔，-1表示空节点):" << endl;
        string line;
        cin.ignore();
        getline(cin, line);
        
        vector<int> preOrder;
        stringstream ss(line);
        int val;
        
        while (ss >> val) {
            preOrder.push_back(val);
        }
        
        int index = 0;
        root = buildFromPreOrder(preOrder, index, -1);
    }
    
    // 3. 交互式建立
    void createInteractive() {
        destroyTree(root);
        root = nullptr;
        
        cout << "交互式建立二叉树:" << endl;
        cout << "输入根节点值: ";
        int rootVal;
        cin >> rootVal;
        
        root = new TreeNode(rootVal);
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            
            char choice;
            cout << "节点" << current->data << "是否有左孩子? (y/n): ";
            cin >> choice;
            
            if (choice == 'y' || choice == 'Y') {
                int leftVal;
                cout << "输入左孩子值: ";
                cin >> leftVal;
                current->left = new TreeNode(leftVal);
                q.push(current->left);
            }
            
            cout << "节点" << current->data << "是否有右孩子? (y/n): ";
            cin >> choice;
            
            if (choice == 'y' || choice == 'Y') {
                int rightVal;
                cout << "输入右孩子值: ";
                cin >> rightVal;
                current->right = new TreeNode(rightVal);
                q.push(current->right);
            }
        }
    }
    
    // 输出二叉树（层次显示）
    void display() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        queue<TreeNode*> q;
        q.push(root);
        int level = 0;
        
        while (!q.empty()) {
            int levelSize = q.size();
            cout << "第" << level << "层: ";
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                if (node) {
                    cout << node->data << " ";
                    q.push(node->left);
                    q.push(node->right);
                } else {
                    cout << "# ";
                }
            }
            
            cout << endl;
            level++;
        }
    }
    
    // 先序遍历（递归）
    void preOrderRecursive() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        cout << "先序遍历(递归): ";
        preOrderRecursive(root);
        cout << endl;
    }
    
    // 中序遍历（递归）
    void inOrderRecursive() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        cout << "中序遍历(递归): ";
        inOrderRecursive(root);
        cout << endl;
    }
    
    // 后序遍历（递归）
    void postOrderRecursive() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        cout << "后序遍历(递归): ";
        postOrderRecursive(root);
        cout << endl;
    }
    
    // 先序遍历（非递归）
    void preOrderNonRecursive() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        cout << "先序遍历(非递归): ";
        stack<TreeNode*> s;
        TreeNode* current = root;
        
        while (current || !s.empty()) {
            while (current) {
                cout << current->data << " ";
                s.push(current);
                current = current->left;
            }
            
            if (!s.empty()) {
                current = s.top();
                s.pop();
                current = current->right;
            }
        }
        
        cout << endl;
    }
    
    // 中序遍历（非递归）
    void inOrderNonRecursive() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        cout << "中序遍历(非递归): ";
        stack<TreeNode*> s;
        TreeNode* current = root;
        
        while (current || !s.empty()) {
            while (current) {
                s.push(current);
                current = current->left;
            }
            
            if (!s.empty()) {
                current = s.top();
                s.pop();
                cout << current->data << " ";
                current = current->right;
            }
        }
        
        cout << endl;
    }
    
    // 后序遍历（非递归）
    void postOrderNonRecursive() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        cout << "后序遍历(非递归): ";
        stack<TreeNode*> s;
        TreeNode* current = root;
        TreeNode* lastVisited = nullptr;
        
        while (current || !s.empty()) {
            while (current) {
                s.push(current);
                current = current->left;
            }
            
            TreeNode* topNode = s.top();
            
            if (topNode->right && topNode->right != lastVisited) {
                current = topNode->right;
            } else {
                cout << topNode->data << " ";
                lastVisited = topNode;
                s.pop();
            }
        }
        
        cout << endl;
    }
    
    // 层次遍历
    void levelOrder() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        cout << "层次遍历: ";
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            cout << node->data << " ";
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        cout << endl;
    }
    
    // 统计二叉树特征
    void printStatistics() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        cout << "节点总数: " << countNodes(root) << endl;
        cout << "叶子节点数: " << countLeaves(root) << endl;
        cout << "树的高度: " << getDepth(root) << endl;
        cout << "度为1的节点数: " << countDegree1(root) << endl;
        cout << "度为2的节点数: " << countDegree2(root) << endl;
    }
    
    // 输出节点信息
    void printNodeInformation() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        queue<TreeNode*> q;
        q.push(root);
        int level = 0;
        
        while (!q.empty()) {
            int levelSize = q.size();
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                cout << "节点值: " << node->data;
                cout << ", 层次: " << level;
                
                if (node->left) {
                    cout << ", 左孩子: " << node->left->data;
                } else {
                    cout << ", 左孩子: 无";
                }
                
                if (node->right) {
                    cout << ", 右孩子: " << node->right->data;
                } else {
                    cout << ", 右孩子: 无";
                }
                
                if (!node->left && !node->right) {
                    cout << " (叶子节点)";
                }
                
                cout << endl;
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            level++;
        }
    }
    
    // 输出所有根到叶子的路径
    void printAllPaths() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        cout << "根到叶子的所有路径:" << endl;
        vector<int> path;
        printPaths(root, path);
    }
    
    // 清空二叉树
    void clear() {
        destroyTree(root);
        root = nullptr;
        cout << "二叉树已清空" << endl;
    }
    
    // 判断是否为空
    bool isEmpty() {
        return root == nullptr;
    }
};

// 主菜单
void menu() {
    BinaryTree tree;
    int choice;
    
    while (true) {
        cout << "\n========== 二叉树操作系统 ==========";
        cout << "\n1. 建立二叉树(层次顺序)";
        cout << "\n2. 建立二叉树(先序遍历)";
        cout << "\n3. 建立二叉树(交互式)";
        cout << "\n4. 显示二叉树";
        cout << "\n5. 先序遍历(递归)";
        cout << "\n6. 中序遍历(递归)";
        cout << "\n7. 后序遍历(递归)";
        cout << "\n8. 先序遍历(非递归)";
        cout << "\n9. 中序遍历(非递归)";
        cout << "\n10. 后序遍历(非递归)";
        cout << "\n11. 层次遍历";
        cout << "\n12. 统计二叉树特征";
        cout << "\n13. 显示节点信息";
        cout << "\n14. 显示所有根到叶子的路径";
        cout << "\n15. 清空二叉树";
        cout << "\n0. 退出";
        cout << "\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1:
                tree.createByLevel();
                break;
                
            case 2:
                tree.createByPreOrder();
                break;
                
            case 3:
                tree.createInteractive();
                break;
                
            case 4:
                tree.display();
                break;
                
            case 5:
                tree.preOrderRecursive();
                break;
                
            case 6:
                tree.inOrderRecursive();
                break;
                
            case 7:
                tree.postOrderRecursive();
                break;
                
            case 8:
                tree.preOrderNonRecursive();
                break;
                
            case 9:
                tree.inOrderNonRecursive();
                break;
                
            case 10:
                tree.postOrderNonRecursive();
                break;
                
            case 11:
                tree.levelOrder();
                break;
                
            case 12:
                tree.printStatistics();
                break;
                
            case 13:
                tree.printNodeInformation();
                break;
                
            case 14:
                tree.printAllPaths();
                break;
                
            case 15:
                tree.clear();
                break;
        }
    }
}

int main() {
    menu();
    return 0;
}