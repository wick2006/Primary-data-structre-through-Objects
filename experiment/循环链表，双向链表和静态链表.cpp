#include <iostream>
#include <vector>
using namespace std;

// ==================== 循环链表 ====================
struct CircularNode {
    int data;
    CircularNode* next;
    CircularNode(int val = 0) : data(val), next(nullptr) {}
};

class CircularLinkedList {
private:
    CircularNode* tail;
    int length;
    
public:
    CircularLinkedList() : tail(nullptr), length(0) {}
    
    ~CircularLinkedList() {
        clear();
    }
    
    bool isEmpty() {
        return tail == nullptr;
    }
    
    int getLength() {
        return length;
    }
    
    void clear() {
        if (isEmpty()) return;
        
        CircularNode* head = tail->next;
        CircularNode* current = head;
        
        do {
            CircularNode* next = current->next;
            delete current;
            current = next;
        } while (current != head);
        
        tail = nullptr;
        length = 0;
    }
    
    void createTailInsert(const vector<int>& vec) {
        clear();
        if (vec.empty()) return;
        
        tail = new CircularNode(vec[0]);
        tail->next = tail;
        length = 1;
        
        for (size_t i = 1; i < vec.size(); i++) {
            CircularNode* newNode = new CircularNode(vec[i]);
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
            length++;
        }
    }
    
    bool insert(int pos, int val) {
        if (pos < 0 || pos > length) {
            cout << "位置不合法" << endl;
            return false;
        }
        
        CircularNode* newNode = new CircularNode(val);
        
        if (isEmpty()) {
            tail = newNode;
            tail->next = tail;
            length = 1;
            return true;
        }
        
        if (pos == 0) {
            newNode->next = tail->next;
            tail->next = newNode;
            length++;
            return true;
        }
        
        if (pos == length) {
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
            length++;
            return true;
        }
        
        CircularNode* prev = tail->next;
        for (int i = 0; i < pos - 1; i++) {
            prev = prev->next;
        }
        
        newNode->next = prev->next;
        prev->next = newNode;
        length++;
        return true;
    }
    
    bool deletePos(int pos) {
        if (isEmpty() || pos < 0 || pos >= length) {
            cout << "删除位置不合法" << endl;
            return false;
        }
        
        if (length == 1) {
            delete tail;
            tail = nullptr;
            length = 0;
            return true;
        }
        
        if (pos == 0) {
            CircularNode* toDelete = tail->next;
            tail->next = toDelete->next;
            delete toDelete;
            length--;
            return true;
        }
        
        CircularNode* prev = tail->next;
        for (int i = 0; i < pos - 1; i++) {
            prev = prev->next;
        }
        
        CircularNode* toDelete = prev->next;
        prev->next = toDelete->next;
        
        if (toDelete == tail) {
            tail = prev;
        }
        
        delete toDelete;
        length--;
        return true;
    }
    
    int getElem(int pos) {
        if (isEmpty() || pos < 0 || pos >= length) {
            cout << "位置不合法" << endl;
            return -1;
        }
        
        CircularNode* current = tail->next;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        return current->data;
    }
    
    int locateElem(int val) {
        if (isEmpty()) return -1;
        
        CircularNode* current = tail->next;
        int pos = 0;
        
        do {
            if (current->data == val) return pos;
            current = current->next;
            pos++;
        } while (current != tail->next);
        
        return -1;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "链表为空" << endl;
            return;
        }
        
        CircularNode* current = tail->next;
        do {
            cout << current->data;
            if (current->next != tail->next) cout << " -> ";
            current = current->next;
        } while (current != tail->next);
        cout << endl;
    }
};

// ==================== 双向链表 ====================
struct DoublyNode {
    int data;
    DoublyNode* prev;
    DoublyNode* next;
    DoublyNode(int val = 0) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    DoublyNode* head;
    DoublyNode* tail;
    int length;
    
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), length(0) {}
    
    ~DoublyLinkedList() {
        clear();
    }
    
    bool isEmpty() {
        return head == nullptr;
    }
    
    int getLength() {
        return length;
    }
    
    void clear() {
        DoublyNode* current = head;
        while (current) {
            DoublyNode* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        length = 0;
    }
    
    void createTailInsert(const vector<int>& vec) {
        clear();
        if (vec.empty()) return;
        
        head = new DoublyNode(vec[0]);
        tail = head;
        length = 1;
        
        for (size_t i = 1; i < vec.size(); i++) {
            DoublyNode* newNode = new DoublyNode(vec[i]);
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            length++;
        }
    }
    
    bool insert(int pos, int val) {
        if (pos < 0 || pos > length) {
            cout << "位置不合法" << endl;
            return false;
        }
        
        DoublyNode* newNode = new DoublyNode(val);
        
        if (isEmpty()) {
            head = tail = newNode;
            length = 1;
            return true;
        }
        
        if (pos == 0) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            length++;
            return true;
        }
        
        if (pos == length) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            length++;
            return true;
        }
        
        DoublyNode* current;
        if (pos < length / 2) {
            current = head;
            for (int i = 0; i < pos; i++) {
                current = current->next;
            }
        } else {
            current = tail;
            for (int i = length - 1; i > pos; i--) {
                current = current->prev;
            }
        }
        
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        length++;
        return true;
    }
    
    bool deletePos(int pos) {
        if (isEmpty() || pos < 0 || pos >= length) {
            cout << "删除位置不合法" << endl;
            return false;
        }
        
        if (length == 1) {
            delete head;
            head = tail = nullptr;
            length = 0;
            return true;
        }
        
        if (pos == 0) {
            DoublyNode* toDelete = head;
            head = head->next;
            head->prev = nullptr;
            delete toDelete;
            length--;
            return true;
        }
        
        if (pos == length - 1) {
            DoublyNode* toDelete = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete toDelete;
            length--;
            return true;
        }
        
        DoublyNode* current;
        if (pos < length / 2) {
            current = head;
            for (int i = 0; i < pos; i++) {
                current = current->next;
            }
        } else {
            current = tail;
            for (int i = length - 1; i > pos; i--) {
                current = current->prev;
            }
        }
        
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        length--;
        return true;
    }
    
    int getElem(int pos) {
        if (isEmpty() || pos < 0 || pos >= length) {
            cout << "位置不合法" << endl;
            return -1;
        }
        
        DoublyNode* current;
        if (pos < length / 2) {
            current = head;
            for (int i = 0; i < pos; i++) {
                current = current->next;
            }
        } else {
            current = tail;
            for (int i = length - 1; i > pos; i--) {
                current = current->prev;
            }
        }
        return current->data;
    }
    
    int locateElem(int val) {
        DoublyNode* current = head;
        int pos = 0;
        
        while (current) {
            if (current->data == val) return pos;
            current = current->next;
            pos++;
        }
        return -1;
    }
    
    void displayForward() {
        if (isEmpty()) {
            cout << "链表为空" << endl;
            return;
        }
        
        DoublyNode* current = head;
        while (current) {
            cout << current->data;
            if (current->next) cout << " <-> ";
            current = current->next;
        }
        cout << endl;
    }
    
    void displayBackward() {
        if (isEmpty()) {
            cout << "链表为空" << endl;
            return;
        }
        
        DoublyNode* current = tail;
        while (current) {
            cout << current->data;
            if (current->prev) cout << " <-> ";
            current = current->prev;
        }
        cout << endl;
    }
};


const int MAX_SIZE = 100;

struct StaticNode {
    int data;
    int next;
    bool used;
    StaticNode() : data(0), next(-1), used(false) {}
};

class StaticLinkedList {
private:
    StaticNode nodes[MAX_SIZE];
    int head;
    int tail;
    int length;
    int freeHead;
    
    int allocateNode() {
        if (freeHead == -1) {
            cout << "链表已满" << endl;
            return -1;
        }
        
        int index = freeHead;
        freeHead = nodes[freeHead].next;
        nodes[index].used = true;
        return index;
    }
    
    void freeNode(int index) {
        nodes[index].next = freeHead;
        nodes[index].used = false;
        freeHead = index;
    }
    
public:
    StaticLinkedList() : head(-1), tail(-1), length(0), freeHead(0) {
        for (int i = 0; i < MAX_SIZE - 1; i++) {
            nodes[i].next = i + 1;
        }
        nodes[MAX_SIZE - 1].next = -1;
    }
    
    bool isEmpty() {
        return head == -1;
    }
    
    int getLength() {
        return length;
    }
    
    void clear() {
        int current = head;
        while (current != -1) {
            int next = nodes[current].next;
            freeNode(current);
            current = next;
        }
        head = tail = -1;
        length = 0;
    }
    
    void createTailInsert(const vector<int>& vec) {
        clear();
        if (vec.empty()) return;
        
        head = allocateNode();
        if (head == -1) return;
        
        nodes[head].data = vec[0];
        tail = head;
        length = 1;
        
        for (size_t i = 1; i < vec.size(); i++) {
            int newIndex = allocateNode();
            if (newIndex == -1) break;
            
            nodes[newIndex].data = vec[i];
            nodes[tail].next = newIndex;
            tail = newIndex;
            length++;
        }
    }
    
    bool insert(int pos, int val) {
        if (pos < 0 || pos > length) {
            cout << "位置不合法" << endl;
            return false;
        }
        
        int newIndex = allocateNode();
        if (newIndex == -1) return false;
        
        nodes[newIndex].data = val;
        
        if (isEmpty()) {
            head = tail = newIndex;
            length = 1;
            return true;
        }
        
        if (pos == 0) {
            nodes[newIndex].next = head;
            head = newIndex;
            length++;
            return true;
        }
        
        if (pos == length) {
            nodes[tail].next = newIndex;
            tail = newIndex;
            length++;
            return true;
        }
        
        int current = head;
        for (int i = 0; i < pos - 1; i++) {
            current = nodes[current].next;
        }
        
        nodes[newIndex].next = nodes[current].next;
        nodes[current].next = newIndex;
        length++;
        return true;
    }
    
    bool deletePos(int pos) {
        if (isEmpty() || pos < 0 || pos >= length) {
            cout << "删除位置不合法" << endl;
            return false;
        }
        
        if (pos == 0) {
            int toDelete = head;
            head = nodes[head].next;
            if (head == -1) tail = -1;
            freeNode(toDelete);
            length--;
            return true;
        }
        
        int prev = head;
        for (int i = 0; i < pos - 1; i++) {
            prev = nodes[prev].next;
        }
        
        int toDelete = nodes[prev].next;
        nodes[prev].next = nodes[toDelete].next;
        
        if (toDelete == tail) {
            tail = prev;
        }
        
        freeNode(toDelete);
        length--;
        return true;
    }
    
    int getElem(int pos) {
        if (isEmpty() || pos < 0 || pos >= length) {
            cout << "位置不合法" << endl;
            return -1;
        }
        
        int current = head;
        for (int i = 0; i < pos; i++) {
            current = nodes[current].next;
        }
        return nodes[current].data;
    }
    
    int locateElem(int val) {
        if (isEmpty()) return -1;
        
        int current = head;
        int pos = 0;
        
        while (current != -1) {
            if (nodes[current].data == val) return pos;
            current = nodes[current].next;
            pos++;
        }
        return -1;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "链表为空" << endl;
            return;
        }
        
        int current = head;
        while (current != -1) {
            cout << "[" << current << "]:" << nodes[current].data;
            if (nodes[current].next != -1) cout << " -> ";
            current = nodes[current].next;
        }
        cout << endl;
    }
};

void menu() {
    CircularLinkedList circularList;
    DoublyLinkedList doublyList;
    StaticLinkedList staticList;
    
    int choice;
    
    while (true) {
        cout << "\n1.循环链表 2.双向链表 3.静态链表 0.退出\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        vector<int> vec;
        int val, pos;
        
        switch (choice) {
            case 1: {
                cout << "\n循环链表操作:";
                cout << "\n1.创建 2.插入 3.删除 4.按位置查找 5.按值查找 6.显示 7.清空\n选择: ";
                int op;
                cin >> op;
                
                if (op == 1) {
                    cout << "输入元素: ";
                    int num;
                    while (cin >> num) vec.push_back(num);
                    cin.clear();
                    circularList.createTailInsert(vec);
                    circularList.display();
                } else if (op == 2) {
                    cout << "位置和值: ";
                    cin >> pos >> val;
                    circularList.insert(pos, val);
                    circularList.display();
                } else if (op == 3) {
                    cout << "删除位置: ";
                    cin >> pos;
                    circularList.deletePos(pos);
                    circularList.display();
                } else if (op == 4) {
                    cout << "查找位置: ";
                    cin >> pos;
                    int result = circularList.getElem(pos);
                    if (result != -1) cout << "值: " << result << endl;
                } else if (op == 5) {
                    cout << "查找值: ";
                    cin >> val;
                    pos = circularList.locateElem(val);
                    if (pos != -1) cout << "位置: " << pos << endl;
                    else cout << "未找到" << endl;
                } else if (op == 6) {
                    circularList.display();
                } else if (op == 7) {
                    circularList.clear();
                    cout << "已清空" << endl;
                }
                break;
            }
            case 2: {
                cout << "\n双向链表操作:";
                cout << "\n1.创建 2.插入 3.删除 4.按位置查找 5.按值查找 6.正向显示 7.反向显示 8.清空\n选择: ";
                int op;
                cin >> op;
                
                if (op == 1) {
                    cout << "输入元素: ";
                    int num;
                    while (cin >> num) vec.push_back(num);
                    cin.clear();
                    doublyList.createTailInsert(vec);
                    doublyList.displayForward();
                } else if (op == 2) {
                    cout << "位置和值: ";
                    cin >> pos >> val;
                    doublyList.insert(pos, val);
                    doublyList.displayForward();
                } else if (op == 3) {
                    cout << "删除位置: ";
                    cin >> pos;
                    doublyList.deletePos(pos);
                    doublyList.displayForward();
                } else if (op == 4) {
                    cout << "查找位置: ";
                    cin >> pos;
                    int result = doublyList.getElem(pos);
                    if (result != -1) cout << "值: " << result << endl;
                } else if (op == 5) {
                    cout << "查找值: ";
                    cin >> val;
                    pos = doublyList.locateElem(val);
                    if (pos != -1) cout << "位置: " << pos << endl;
                    else cout << "未找到" << endl;
                } else if (op == 6) {
                    doublyList.displayForward();
                } else if (op == 7) {
                    doublyList.displayBackward();
                } else if (op == 8) {
                    doublyList.clear();
                    cout << "已清空" << endl;
                }
                break;
            }
            case 3: {
                cout << "\n静态链表操作:";
                cout << "\n1.创建 2.插入 3.删除 4.按位置查找 5.按值查找 6.显示 7.清空\n选择: ";
                int op;
                cin >> op;
                
                if (op == 1) {
                    cout << "输入元素: ";
                    int num;
                    while (cin >> num) vec.push_back(num);
                    cin.clear();
                    staticList.createTailInsert(vec);
                    staticList.display();
                } else if (op == 2) {
                    cout << "位置和值: ";
                    cin >> pos >> val;
                    staticList.insert(pos, val);
                    staticList.display();
                } else if (op == 3) {
                    cout << "删除位置: ";
                    cin >> pos;
                    staticList.deletePos(pos);
                    staticList.display();
                } else if (op == 4) {
                    cout << "查找位置: ";
                    cin >> pos;
                    int result = staticList.getElem(pos);
                    if (result != -1) cout << "值: " << result << endl;
                } else if (op == 5) {
                    cout << "查找值: ";
                    cin >> val;
                    pos = staticList.locateElem(val);
                    if (pos != -1) cout << "位置: " << pos << endl;
                    else cout << "未找到" << endl;
                } else if (op == 6) {
                    staticList.display();
                } else if (op == 7) {
                    staticList.clear();
                    cout << "已清空" << endl;
                }
                break;
            }
        }
    }
}

int main() {
    menu();
    return 0;
}