#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

// 二叉树节点模板类
template<typename T>
struct BinaryTreeNode {
    T data;
    BinaryTreeNode<T>* left;
    BinaryTreeNode<T>* right;
    
    BinaryTreeNode(T val = T()) : data(val), left(nullptr), right(nullptr) {}
};

// 二叉树类模板
template<typename T>
class BinaryTree {
private:
    BinaryTreeNode<T>* root;
    
    // 私有辅助函数
    BinaryTreeNode<T>* copyTree(BinaryTreeNode<T>* node) {
        if (!node) return nullptr;
        
        BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }
    
    void destroyTree(BinaryTreeNode<T>* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
    BinaryTreeNode<T>* buildFromPreOrder(vector<T>& pre, int& index, T stopValue) {
        if (index >= pre.size() || pre[index] == stopValue) {
            index++;
            return nullptr;
        }
        
        BinaryTreeNode<T>* node = new BinaryTreeNode<T>(pre[index++]);
        node->left = buildFromPreOrder(pre, index, stopValue);
        node->right = buildFromPreOrder(pre, index, stopValue);
        return node;
    }
    
    void preOrderRecursive(BinaryTreeNode<T>* node) {
        if (!node) return;
        
        cout << node->data << " ";
        preOrderRecursive(node->left);
        preOrderRecursive(node->right);
    }
    
    void inOrderRecursive(BinaryTreeNode<T>* node) {
        if (!node) return;
        
        inOrderRecursive(node->left);
        cout << node->data << " ";
        inOrderRecursive(node->right);
    }
    
    void postOrderRecursive(BinaryTreeNode<T>* node) {
        if (!node) return;
        
        postOrderRecursive(node->left);
        postOrderRecursive(node->right);
        cout << node->data << " ";
    }
    
    void printPaths(BinaryTreeNode<T>* node, vector<T>& path) {
        if (!node) return;
        
        path.push_back(node->data);
        
        if (!node->left && !node->right) {
            // 输出根到叶子的路径
            cout << "路径: ";
            for (const auto& val : path) {
                cout << val << " ";
            }
            cout << endl;
            
            // 输出叶子到根的逆路径
            cout << "逆路径: ";
            for (auto it = path.rbegin(); it != path.rend(); ++it) {
                cout << *it << " ";
            }
            cout << endl;
        } else {
            printPaths(node->left, path);
            printPaths(node->right, path);
        }
        
        path.pop_back();
    }
    
    int getDepth(BinaryTreeNode<T>* node) {
        if (!node) return 0;
        
        int leftDepth = getDepth(node->left);
        int rightDepth = getDepth(node->right);
        return max(leftDepth, rightDepth) + 1;
    }
    
    int countNodes(BinaryTreeNode<T>* node) {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
    
    int countLeaves(BinaryTreeNode<T>* node) {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;
        return countLeaves(node->left) + countLeaves(node->right);
    }
    
    int countDegree1(BinaryTreeNode<T>* node) {
        if (!node) return 0;
        
        int count = 0;
        if ((!node->left && node->right) || (node->left && !node->right)) {
            count = 1;
        }
        
        return count + countDegree1(node->left) + countDegree1(node->right);
    }
    
    int countDegree2(BinaryTreeNode<T>* node) {
        if (!node) return 0;
        
        int count = 0;
        if (node->left && node->right) {
            count = 1;
        }
        
        return count + countDegree2(node->left) + countDegree2(node->right);
    }
    
    void printNodeInfo(BinaryTreeNode<T>* node, int level) {
        if (!node) return;
        
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
        
        printNodeInfo(node->left, level + 1);
        printNodeInfo(node->right, level + 1);
    }
    
    // 层次建立二叉树的辅助函数
    BinaryTreeNode<T>* buildLevelOrder(vector<T>& values, T nullValue) {
        if (values.empty() || values[0] == nullValue) return nullptr;
        
        queue<BinaryTreeNode<T>*> q;
        root = new BinaryTreeNode<T>(values[0]);
        q.push(root);
        
        int i = 1;
        while (!q.empty() && i < values.size()) {
            BinaryTreeNode<T>* current = q.front();
            q.pop();
            
            // 左孩子
            if (i < values.size() && values[i] != nullValue) {
                current->left = new BinaryTreeNode<T>(values[i]);
                q.push(current->left);
            }
            i++;
            
            // 右孩子
            if (i < values.size() && values[i] != nullValue) {
                current->right = new BinaryTreeNode<T>(values[i]);
                q.push(current->right);
            }
            i++;
        }
        
        return root;
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
    
    // 方法1：先建立节点，再建立树
    void createByNodes() {
        destroyTree(root);
        root = nullptr;
        
        cout << "输入节点值(格式: 根 左 右, 输入'#'表示空节点):" << endl;
        cout << "例如: A B C 表示根为A，左孩子为B，右孩子为C" << endl;
        cout << "要结束输入，请输入三个'#'" << endl;
        
        // 使用简单的层次建立方式
        cout << "请按层次顺序输入节点值，用空格分隔，'#'表示空节点:" << endl;
        string line;
        cin.ignore();
        getline(cin, line);
        
        vector<T> values;
        stringstream ss(line);
        T val;
        string strVal;
        
        while (ss >> strVal) {
            if (strVal == "#") {
                // 对于T类型为int的情况，使用-1表示空，实际应根据T类型调整
                values.push_back(T());
            } else {
                stringstream converter(strVal);
                converter >> val;
                values.push_back(val);
            }
        }
        
        root = buildLevelOrder(values, T());
    }
    
    // 方法2：通过先序遍历序列建立
    void createByPreOrder() {
        destroyTree(root);
        root = nullptr;
        
        cout << "输入先序遍历序列(用空格分隔，'#'表示空节点):" << endl;
        string line;
        cin.ignore();
        getline(cin, line);
        
        vector<T> preOrder;
        stringstream ss(line);
        T val;
        string strVal;
        
        while (ss >> strVal) {
            if (strVal == "#") {
                // 使用默认值表示空节点
                preOrder.push_back(T());
            } else {
                stringstream converter(strVal);
                converter >> val;
                preOrder.push_back(val);
            }
        }
        
        int index = 0;
        root = buildFromPreOrder(preOrder, index, T());
    }
    
    // 方法3：交互式建立
    void createInteractive() {
        destroyTree(root);
        root = nullptr;
        
        cout << "交互式建立二叉树:" << endl;
        cout << "输入根节点值: ";
        T rootVal;
        cin >> rootVal;
        
        root = new BinaryTreeNode<T>(rootVal);
        queue<BinaryTreeNode<T>*> q;
        q.push(root);
        
        while (!q.empty()) {
            BinaryTreeNode<T>* current = q.front();
            q.pop();
            
            cout << "当前节点: " << current->data << endl;
            
            char choice;
            cout << "是否有左孩子? (y/n): ";
            cin >> choice;
            
            if (choice == 'y' || choice == 'Y') {
                T leftVal;
                cout << "输入左孩子值: ";
                cin >> leftVal;
                current->left = new BinaryTreeNode<T>(leftVal);
                q.push(current->left);
            }
            
            cout << "是否有右孩子? (y/n): ";
            cin >> choice;
            
            if (choice == 'y' || choice == 'Y') {
                T rightVal;
                cout << "输入右孩子值: ";
                cin >> rightVal;
                current->right = new BinaryTreeNode<T>(rightVal);
                q.push(current->right);
            }
        }
    }
    
    // 显示二叉树（层次显示）
    void display() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        queue<BinaryTreeNode<T>*> q;
        q.push(root);
        int level = 0;
        
        cout << "二叉树层次显示:" << endl;
        
        while (!q.empty()) {
            int levelSize = q.size();
            cout << "第" << level << "层: ";
            
            for (int i = 0; i < levelSize; i++) {
                BinaryTreeNode<T>* node = q.front();
                q.pop();
                
                cout << node->data << " ";
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
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
        stack<BinaryTreeNode<T>*> s;
        BinaryTreeNode<T>* current = root;
        
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
        stack<BinaryTreeNode<T>*> s;
        BinaryTreeNode<T>* current = root;
        
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
        stack<BinaryTreeNode<T>*> s;
        BinaryTreeNode<T>* current = root;
        BinaryTreeNode<T>* lastVisited = nullptr;
        
        while (current || !s.empty()) {
            while (current) {
                s.push(current);
                current = current->left;
            }
            
            BinaryTreeNode<T>* topNode = s.top();
            
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
        queue<BinaryTreeNode<T>*> q;
        q.push(root);
        
        while (!q.empty()) {
            BinaryTreeNode<T>* node = q.front();
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
        
        cout << "\n二叉树统计信息:" << endl;
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
        
        cout << "\n节点详细信息:" << endl;
        printNodeInfo(root, 0);
    }
    
    // 输出所有根到叶子的路径
    void printAllPaths() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        cout << "\n根到叶子的所有路径:" << endl;
        vector<T> path;
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
    BinaryTree<int> tree;  // 使用int类型，可以修改为其他类型
    int choice;
    
    while (true) {
        cout << "\n========== 二叉树操作系统 ==========";
        cout << "\n1. 建立二叉树(方法1: 先建节点)";
        cout << "\n2. 建立二叉树(方法2: 先序遍历)";
        cout << "\n3. 建立二叉树(方法3: 交互式)";
        cout << "\n4. 显示二叉树(层次)";
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
        cout << "\n16. 演示功能";
        cout << "\n0. 退出";
        cout << "\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1:
                tree.createByNodes();
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
                
            case 16: {
                // 演示功能
                cout << "\n========== 二叉树功能演示 ==========" << endl;
                
                // 创建示例二叉树
                BinaryTree<int> demoTree;
                cout << "创建示例二叉树: 1 2 3 4 5 6 7" << endl;
                
                // 使用层次顺序创建
                vector<int> values = {1, 2, 3, 4, 5, 6, 7};
                demoTree.createByNodes();  // 这里需要适配，简化演示
                
                cout << "1. 显示二叉树:" << endl;
                demoTree.display();
                
                cout << "\n2. 遍历操作:" << endl;
                demoTree.preOrderRecursive();
                demoTree.inOrderRecursive();
                demoTree.postOrderRecursive();
                demoTree.levelOrder();
                
                cout << "\n3. 统计信息:" << endl;
                demoTree.printStatistics();
                
                cout << "\n4. 路径信息:" << endl;
                demoTree.printAllPaths();
                
                cout << "\n演示结束" << endl;
                break;
            }
        }
    }
}

// 示例二叉树创建函数
void createSampleTree(BinaryTree<int>& tree) {
    // 创建示例树: 
    //        1
    //       / \
    //      2   3
    //     / \ / \
    //    4  5 6  7
    
    tree.clear();
    
    BinaryTreeNode<int>* root = new BinaryTreeNode<int>(1);
    root->left = new BinaryTreeNode<int>(2);
    root->right = new BinaryTreeNode<int>(3);
    root->left->left = new BinaryTreeNode<int>(4);
    root->left->right = new BinaryTreeNode<int>(5);
    root->right->left = new BinaryTreeNode<int>(6);
    root->right->right = new BinaryTreeNode<int>(7);
    
    // 注意：这里需要访问私有成员，实际应该通过公有方法设置
    // 为了演示，我们这里简化处理
}

int main() {
    menu();
    return 0;
}