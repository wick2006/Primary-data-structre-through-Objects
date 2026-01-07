#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <iomanip>
#include <string>
#include <limits>
#include <sstream>
using namespace std;

// ==================== 静态搜索结构 ====================

// 顺序查找
int sequentialSearch(const vector<int>& arr, int key) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

// 折半查找（要求数组有序）
int binarySearch(const vector<int>& arr, int key) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// 分块查找
class BlockSearch {
private:
    vector<vector<int>> blocks;      // 分块数据
    vector<int> blockMax;            // 每块最大值
    int blockSize;                   // 块大小
    
public:
    BlockSearch(const vector<int>& data, int bs) : blockSize(bs) {
        // 数据排序
        vector<int> sortedData = data;
        sort(sortedData.begin(), sortedData.end());
        
        // 分块
        int numBlocks = (sortedData.size() + blockSize - 1) / blockSize;
        blocks.resize(numBlocks);
        blockMax.resize(numBlocks);
        
        for (int i = 0; i < sortedData.size(); i++) {
            int blockIdx = i / blockSize;
            blocks[blockIdx].push_back(sortedData[i]);
            blockMax[blockIdx] = sortedData[i];  // 更新块最大值
        }
    }
    
    int search(int key) {
        // 确定所在块
        int blockIdx = -1;
        for (int i = 0; i < blockMax.size(); i++) {
            if (key <= blockMax[i]) {
                blockIdx = i;
                break;
            }
        }
        
        if (blockIdx == -1) return -1;
        
        // 在块内顺序查找
        for (int i = 0; i < blocks[blockIdx].size(); i++) {
            if (blocks[blockIdx][i] == key) {
                // 计算全局位置
                int pos = 0;
                for (int j = 0; j < blockIdx; j++) {
                    pos += blocks[j].size();
                }
                return pos + i;
            }
        }
        
        return -1;
    }
    
    void display() {
        cout << "分块情况（块大小=" << blockSize << "）:" << endl;
        for (int i = 0; i < blocks.size(); i++) {
            cout << "块" << i << " [最大值=" << blockMax[i] << "]: ";
            for (int val : blocks[i]) {
                cout << val << " ";
            }
            cout << endl;
        }
    }
};

// ==================== 二叉搜索树 ====================
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(int val = 0) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    BSTNode* root;
    
    // 递归插入
    BSTNode* insertRecursive(BSTNode* node, int val) {
        if (!node) {
            return new BSTNode(val);
        }
        
        if (val < node->data) {
            node->left = insertRecursive(node->left, val);
        } else if (val > node->data) {
            node->right = insertRecursive(node->right, val);
        }
        
        return node;
    }
    
    // 递归查找
    BSTNode* searchRecursive(BSTNode* node, int val) {
        if (!node || node->data == val) {
            return node;
        }
        
        if (val < node->data) {
            return searchRecursive(node->left, val);
        }
        
        return searchRecursive(node->right, val);
    }
    
    // 查找最小节点
    BSTNode* findMin(BSTNode* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }
    
    // 递归删除
    BSTNode* deleteRecursive(BSTNode* node, int val) {
        if (!node) return nullptr;
        
        if (val < node->data) {
            node->left = deleteRecursive(node->left, val);
        } else if (val > node->data) {
            node->right = deleteRecursive(node->right, val);
        } else {
            // 找到要删除的节点
            if (!node->left) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            
            // 有两个孩子：找到右子树的最小节点
            BSTNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteRecursive(node->right, temp->data);
        }
        
        return node;
    }
    
    // 中序遍历（验证BST性质）
    void inOrderTraversal(BSTNode* node, vector<int>& result) {
        if (!node) return;
        
        inOrderTraversal(node->left, result);
        result.push_back(node->data);
        inOrderTraversal(node->right, result);
    }
    
    // 释放内存
    void destroyTree(BSTNode* node) {
        if (!node) return;
        
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
    
    // 非递归查找
    BSTNode* searchIterative(int val) {
        BSTNode* current = root;
        
        while (current) {
            if (val == current->data) {
                return current;
            } else if (val < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        
        return nullptr;
    }
    
    // 非递归插入
    void insertIterative(int val) {
        if (!root) {
            root = new BSTNode(val);
            return;
        }
        
        BSTNode* current = root;
        BSTNode* parent = nullptr;
        
        while (current) {
            parent = current;
            
            if (val < current->data) {
                current = current->left;
            } else if (val > current->data) {
                current = current->right;
            } else {
                return;  // 值已存在
            }
        }
        
        if (val < parent->data) {
            parent->left = new BSTNode(val);
        } else {
            parent->right = new BSTNode(val);
        }
    }
    
public:
    BinarySearchTree() : root(nullptr) {}
    
    ~BinarySearchTree() {
        destroyTree(root);
    }
    
    // 创建二叉搜索树
    void create(const vector<int>& data) {
        destroyTree(root);
        root = nullptr;
        
        for (int val : data) {
            insertRecursive(root, val);
        }
    }
    
    // 递归插入
    void insert(int val) {
        root = insertRecursive(root, val);
    }
    
    // 非递归插入
    void insertNonRecursive(int val) {
        insertIterative(val);
    }
    
    // 递归查找
    bool search(int val) {
        return searchRecursive(root, val) != nullptr;
    }
    
    // 非递归查找
    bool searchNonRecursive(int val) {
        return searchIterative(val) != nullptr;
    }
    
    // 递归删除
    void remove(int val) {
        root = deleteRecursive(root, val);
    }
    
    // 判断是否为BST
    bool isBST() {
        vector<int> traversal;
        inOrderTraversal(root, traversal);
        
        for (int i = 1; i < traversal.size(); i++) {
            if (traversal[i] <= traversal[i - 1]) {
                return false;
            }
        }
        
        return true;
    }
    
    // 显示BST
    void display() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        cout << "二叉搜索树(中序遍历): ";
        vector<int> traversal;
        inOrderTraversal(root, traversal);
        for (int val : traversal) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    // 层次显示
    void displayLevelOrder() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        queue<BSTNode*> q;
        q.push(root);
        int level = 0;
        
        while (!q.empty()) {
            int levelSize = q.size();
            cout << "第" << level << "层: ";
            
            for (int i = 0; i < levelSize; i++) {
                BSTNode* node = q.front();
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
    
    // 清空
    void clear() {
        destroyTree(root);
        root = nullptr;
        cout << "二叉搜索树已清空" << endl;
    }
};

// ==================== AVL树 ====================
struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(int val = 0) : data(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;
    
    // 获取节点高度
    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }
    
    // 更新节点高度
    void updateHeight(AVLNode* node) {
        if (node) {
            node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        }
    }
    
    // 获取平衡因子
    int getBalanceFactor(AVLNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    
    // 右旋
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    // 左旋
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    // 平衡节点
    AVLNode* balance(AVLNode* node) {
        if (!node) return nullptr;
        
        updateHeight(node);
        int balanceFactor = getBalanceFactor(node);
        
        // 左左情况
        if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }
        
        // 右右情况
        if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }
        
        // 左右情况
        if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // 右左情况
        if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    // 插入节点
    AVLNode* insert(AVLNode* node, int val) {
        if (!node) {
            return new AVLNode(val);
        }
        
        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        } else {
            return node;  // 值已存在
        }
        
        return balance(node);
    }
    
    // 查找最小节点
    AVLNode* findMin(AVLNode* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }
    
    // 删除节点
    AVLNode* remove(AVLNode* node, int val) {
        if (!node) return nullptr;
        
        if (val < node->data) {
            node->left = remove(node->left, val);
        } else if (val > node->data) {
            node->right = remove(node->right, val);
        } else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                
                delete temp;
            } else {
                AVLNode* temp = findMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }
        
        if (!node) return node;
        
        return balance(node);
    }
    
    // 查找节点
    AVLNode* search(AVLNode* node, int val) {
        if (!node || node->data == val) {
            return node;
        }
        
        if (val < node->data) {
            return search(node->left, val);
        }
        
        return search(node->right, val);
    }
    
    // 中序遍历
    void inOrderTraversal(AVLNode* node, vector<int>& result) {
        if (!node) return;
        
        inOrderTraversal(node->left, result);
        result.push_back(node->data);
        inOrderTraversal(node->right, result);
    }
    
    // 释放内存
    void destroyTree(AVLNode* node) {
        if (!node) return;
        
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
    
    // 检查是否为AVL树
    bool isAVLTree(AVLNode* node) {
        if (!node) return true;
        
        int balanceFactor = getBalanceFactor(node);
        if (abs(balanceFactor) > 1) {
            return false;
        }
        
        return isAVLTree(node->left) && isAVLTree(node->right);
    }
    
public:
    AVLTree() : root(nullptr) {}
    
    ~AVLTree() {
        destroyTree(root);
    }
    
    // 创建AVL树
    void create(const vector<int>& data) {
        destroyTree(root);
        root = nullptr;
        
        for (int val : data) {
            root = insert(root, val);
        }
    }
    
    // 插入
    void insert(int val) {
        root = insert(root, val);
    }
    
    // 删除
    void remove(int val) {
        root = remove(root, val);
    }
    
    // 查找
    bool search(int val) {
        return search(root, val) != nullptr;
    }
    
    // 判断是否为AVL树
    bool isAVL() {
        return isAVLTree(root);
    }
    
    // 显示AVL树
    void display() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        cout << "AVL树(中序遍历): ";
        vector<int> traversal;
        inOrderTraversal(root, traversal);
        for (int val : traversal) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    // 层次显示
    void displayLevelOrder() {
        if (!root) {
            cout << "空树" << endl;
            return;
        }
        
        queue<AVLNode*> q;
        q.push(root);
        int level = 0;
        
        while (!q.empty()) {
            int levelSize = q.size();
            cout << "第" << level << "层: ";
            
            for (int i = 0; i < levelSize; i++) {
                AVLNode* node = q.front();
                q.pop();
                
                if (node) {
                    cout << node->data << "(" << getBalanceFactor(node) << ") ";
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
    
    // 清空
    void clear() {
        destroyTree(root);
        root = nullptr;
        cout << "AVL树已清空" << endl;
    }
};

// ==================== 哈希表 ====================
class HashTable {
private:
    static const int TABLE_SIZE = 20;
    int table[TABLE_SIZE];
    bool occupied[TABLE_SIZE];
    bool deleted[TABLE_SIZE];
    
    // 哈希函数：除留余数法
    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }
    
    // 线性探测
    int linearProbe(int key, bool forInsert = false) {
        int index = hashFunction(key);
        int start = index;
        
        do {
            if (forInsert) {
                if (!occupied[index] || deleted[index]) {
                    return index;
                }
            } else {
                if (occupied[index] && table[index] == key && !deleted[index]) {
                    return index;
                }
                if (!occupied[index] && !deleted[index]) {
                    return -1;
                }
            }
            
            index = (index + 1) % TABLE_SIZE;
        } while (index != start);
        
        return -1;
    }
    
public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            occupied[i] = false;
            deleted[i] = false;
            table[i] = 0;
        }
    }
    
    // 插入
    bool insert(int key) {
        int index = linearProbe(key, true);
        
        if (index == -1) {
            cout << "哈希表已满，无法插入 " << key << endl;
            return false;
        }
        
        table[index] = key;
        occupied[index] = true;
        deleted[index] = false;
        return true;
    }
    
    // 查找
    bool search(int key) {
        int index = linearProbe(key, false);
        return index != -1;
    }
    
    // 删除
    bool remove(int key) {
        int index = linearProbe(key, false);
        
        if (index == -1) {
            return false;
        }
        
        deleted[index] = true;
        return true;
    }
    
    // 显示哈希表
    void display() {
        cout << "哈希表内容:" << endl;
        cout << "索引\t键值\t状态" << endl;
        cout << "----------------------" << endl;
        
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << "\t";
            
            if (occupied[i] && !deleted[i]) {
                cout << table[i] << "\t存在";
            } else if (occupied[i] && deleted[i]) {
                cout << table[i] << "\t已删除";
            } else {
                cout << "空\t空闲";
            }
            
            cout << endl;
        }
    }
    
    // 清空
    void clear() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            occupied[i] = false;
            deleted[i] = false;
            table[i] = 0;
        }
        cout << "哈希表已清空" << endl;
    }
};

// ==================== 主菜单 ====================
void staticSearchMenu() {
    vector<int> data;
    cout << "请输入数据(空格分隔，回车结束): ";
    string line;
    cin.ignore();
    getline(cin, line);
    
    stringstream ss(line);
    int val;
    while (ss >> val) {
        data.push_back(val);
    }
    
    int choice;
    while (true) {
        cout << "\n----- 静态搜索操作 -----";
        cout << "\n1. 顺序查找";
        cout << "\n2. 折半查找(数据需要排序)";
        cout << "\n3. 分块查找";
        cout << "\n0. 返回";
        cout << "\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                int key;
                cout << "输入要查找的值: ";
                cin >> key;
                int result = sequentialSearch(data, key);
                if (result != -1) {
                    cout << "找到，位置: " << result << endl;
                } else {
                    cout << "未找到" << endl;
                }
                break;
            }
            case 2: {
                // 先排序
                vector<int> sortedData = data;
                sort(sortedData.begin(), sortedData.end());
                
                cout << "排序后数据: ";
                for (int val : sortedData) {
                    cout << val << " ";
                }
                cout << endl;
                
                int key;
                cout << "输入要查找的值: ";
                cin >> key;
                int result = binarySearch(sortedData, key);
                if (result != -1) {
                    cout << "找到，位置: " << result << endl;
                } else {
                    cout << "未找到" << endl;
                }
                break;
            }
            case 3: {
                int blockSize;
                cout << "输入块大小: ";
                cin >> blockSize;
                
                BlockSearch bs(data, blockSize);
                bs.display();
                
                int key;
                cout << "输入要查找的值: ";
                cin >> key;
                int result = bs.search(key);
                if (result != -1) {
                    cout << "找到，位置: " << result << endl;
                } else {
                    cout << "未找到" << endl;
                }
                break;
            }
        }
    }
}

void binarySearchTreeMenu() {
    BinarySearchTree bst;
    int choice;
    
    while (true) {
        cout << "\n----- 二叉搜索树操作 -----";
        cout << "\n1. 创建BST";
        cout << "\n2. 插入(递归)";
        cout << "\n3. 插入(非递归)";
        cout << "\n4. 查找(递归)";
        cout << "\n5. 查找(非递归)";
        cout << "\n6. 删除";
        cout << "\n7. 显示(中序)";
        cout << "\n8. 显示(层次)";
        cout << "\n9. 判断是否为BST";
        cout << "\n10. 清空";
        cout << "\n0. 返回";
        cout << "\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                string line;
                vector<int> data;
                cout << "请输入数据(空格分隔，回车结束): ";
                cin.ignore();
                getline(cin, line);
                
                stringstream ss(line);
                int val;
                while (ss >> val) {
                    data.push_back(val);
                }
                
                bst.create(data);
                cout << "BST创建完成" << endl;
                bst.display();
                break;
            }
            case 2: {
                int val;
                cout << "输入要插入的值: ";
                cin >> val;
                bst.insert(val);
                cout << "插入完成" << endl;
                break;
            }
            case 3: {
                int val;
                cout << "输入要插入的值: ";
                cin >> val;
                bst.insertNonRecursive(val);
                cout << "插入完成" << endl;
                break;
            }
            case 4: {
                int val;
                cout << "输入要查找的值: ";
                cin >> val;
                if (bst.search(val)) {
                    cout << "找到" << endl;
                } else {
                    cout << "未找到" << endl;
                }
                break;
            }
            case 5: {
                int val;
                cout << "输入要查找的值: ";
                cin >> val;
                if (bst.searchNonRecursive(val)) {
                    cout << "找到" << endl;
                } else {
                    cout << "未找到" << endl;
                }
                break;
            }
            case 6: {
                int val;
                cout << "输入要删除的值: ";
                cin >> val;
                bst.remove(val);
                cout << "删除完成" << endl;
                break;
            }
            case 7:
                bst.display();
                break;
            case 8:
                bst.displayLevelOrder();
                break;
            case 9:
                if (bst.isBST()) {
                    cout << "是二叉搜索树" << endl;
                } else {
                    cout << "不是二叉搜索树" << endl;
                }
                break;
            case 10:
                bst.clear();
                break;
        }
    }
}

void avlTreeMenu() {
    AVLTree avl;
    int choice;
    string line;
    
    while (true) {
        cout << "\n----- AVL树操作 -----";
        cout << "\n1. 创建AVL树";
        cout << "\n2. 插入";
        cout << "\n3. 删除";
        cout << "\n4. 查找";
        cout << "\n5. 显示(中序)";
        cout << "\n6. 显示(层次)";
        cout << "\n7. 判断是否为AVL树";
        cout << "\n8. 清空";
        cout << "\n0. 返回";
        cout << "\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                vector<int> data;
                cout << "请输入数据(空格分隔，回车结束): ";
                cin.ignore();
                getline(cin, line);
                
                stringstream ss(line);
                int val;
                while (ss >> val) {
                    data.push_back(val);
                }
                
                avl.create(data);
                cout << "AVL树创建完成" << endl;
                avl.display();
                break;
            }
            case 2: {
                int val;
                cout << "输入要插入的值: ";
                cin >> val;
                avl.insert(val);
                cout << "插入完成" << endl;
                if (avl.isAVL()) {
                    cout << "插入后仍是AVL树" << endl;
                } else {
                    cout << "警告: 插入后可能不是AVL树" << endl;
                }
                break;
            }
            case 3: {
                int val;
                cout << "输入要删除的值: ";
                cin >> val;
                avl.remove(val);
                cout << "删除完成" << endl;
                if (avl.isAVL()) {
                    cout << "删除后仍是AVL树" << endl;
                } else {
                    cout << "警告: 删除后可能不是AVL树" << endl;
                }
                break;
            }
            case 4: {
                int val;
                cout << "输入要查找的值: ";
                cin >> val;
                if (avl.search(val)) {
                    cout << "找到" << endl;
                } else {
                    cout << "未找到" << endl;
                }
                break;
            }
            case 5:
                avl.display();
                break;
            case 6:
                avl.displayLevelOrder();
                break;
            case 7:
                if (avl.isAVL()) {
                    cout << "是AVL树" << endl;
                } else {
                    cout << "不是AVL树" << endl;
                }
                break;
            case 8:
                avl.clear();
                break;
        }
    }
}

void hashTableMenu() {
    HashTable ht;
    int choice;
    
    while (true) {
        cout << "\n----- 哈希表操作 -----";
        cout << "\n1. 插入";
        cout << "\n2. 查找";
        cout << "\n3. 删除";
        cout << "\n4. 显示";
        cout << "\n5. 清空";
        cout << "\n0. 返回";
        cout << "\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                int key;
                cout << "输入要插入的键值: ";
                cin >> key;
                if (ht.insert(key)) {
                    cout << "插入成功" << endl;
                } else {
                    cout << "插入失败" << endl;
                }
                break;
            }
            case 2: {
                int key;
                cout << "输入要查找的键值: ";
                cin >> key;
                if (ht.search(key)) {
                    cout << "找到" << endl;
                } else {
                    cout << "未找到" << endl;
                }
                break;
            }
            case 3: {
                int key;
                cout << "输入要删除的键值: ";
                cin >> key;
                if (ht.remove(key)) {
                    cout << "删除成功" << endl;
                } else {
                    cout << "删除失败" << endl;
                }
                break;
            }
            case 4:
                ht.display();
                break;
            case 5:
                ht.clear();
                break;
        }
    }
}

int main() {
    int choice;
    
    while (true) {
        cout << "\n========== 搜索结构系统 ==========";
        cout << "\n1. 静态搜索（顺序、折半、分块）";
        cout << "\n2. 二叉搜索树";
        cout << "\n3. AVL树";
        cout << "\n4. 哈希表";
        cout << "\n0. 退出";
        cout << "\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1:
                staticSearchMenu();
                break;
            case 2:
                binarySearchTreeMenu();
                break;
            case 3:
                avlTreeMenu();
                break;
            case 4:
                hashTableMenu();
                break;
        }
    }
    
    return 0;
}