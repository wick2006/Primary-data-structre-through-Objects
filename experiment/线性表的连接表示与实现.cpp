#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int data;
    ListNode* next;
    ListNode(int val = 0) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;
    int length;
    
public:
    LinkedList() : head(nullptr), length(0) {}
    
    ~LinkedList() {
        clear();
    }
    
    void createFromVector(const vector<int>& vec) {
        clear();
        if (vec.empty()) return;
        
        head = new ListNode(vec[0]);
        ListNode* current = head;
        length = 1;
        
        for (size_t i = 1; i < vec.size(); i++) {
            current->next = new ListNode(vec[i]);
            current = current->next;
            length++;
        }
    }
    
    bool insert(int pos, int val) {
        if (pos < 0 || pos > length) {
            cout << "位置不合法" << endl;
            return false;
        }
        
        ListNode* newNode = new ListNode(val);
        
        if (pos == 0) {
            newNode->next = head;
            head = newNode;
            length++;
            return true;
        }
        
        ListNode* prev = head;
        for (int i = 0; i < pos - 1; i++) {
            prev = prev->next;
        }
        
        newNode->next = prev->next;
        prev->next = newNode;
        length++;
        return true;
    }
    
    bool deletePos(int pos) {
        if (pos < 0 || pos >= length || !head) {
            cout << "删除位置不合法" << endl;
            return false;
        }
        
        ListNode* toDelete;
        if (pos == 0) {
            toDelete = head;
            head = head->next;
            delete toDelete;
            length--;
            return true;
        }
        
        ListNode* prev = head;
        for (int i = 0; i < pos - 1; i++) {
            prev = prev->next;
        }
        
        toDelete = prev->next;
        prev->next = toDelete->next;
        delete toDelete;
        length--;
        return true;
    }
    
    int getElem(int pos) {
        if (pos < 0 || pos >= length || !head) {
            cout << "位置不合法" << endl;
            return -1;
        }
        
        ListNode* current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        return current->data;
    }
    
    int locateElem(int val) {
        ListNode* current = head;
        int pos = 0;
        
        while (current) {
            if (current->data == val) return pos;
            current = current->next;
            pos++;
        }
        return -1;
    }
    
    void clear() {
        ListNode* current = head;
        while (current) {
            ListNode* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        length = 0;
    }
    
    void display() {
        if (!head) {
            cout << "链表为空" << endl;
            return;
        }
        
        ListNode* current = head;
        while (current) {
            cout << current->data;
            if (current->next) cout << " -> ";
            current = current->next;
        }
        cout << endl;
    }
    
    int getLength() { return length; }
    bool isEmpty() { return head == nullptr; }
    
    static LinkedList merge(const LinkedList& list1, const LinkedList& list2) {
        LinkedList merged;
        if (!list1.head) {
            merged.head = copyList(list2.head);
            merged.length = list2.length;
            return merged;
        }
        
        merged.head = copyList(list1.head);
        merged.length = list1.length;
        
        ListNode* tail = merged.head;
        while (tail->next) tail = tail->next;
        
        ListNode* current = list2.head;
        while (current) {
            tail->next = new ListNode(current->data);
            tail = tail->next;
            current = current->next;
            merged.length++;
        }
        
        return merged;
    }
    
private:
    static ListNode* copyList(ListNode* head) {
        if (!head) return nullptr;
        
        ListNode* newHead = new ListNode(head->data);
        ListNode* current = newHead;
        ListNode* original = head->next;
        
        while (original) {
            current->next = new ListNode(original->data);
            current = current->next;
            original = original->next;
        }
        return newHead;
    }
};

void menu() {
    LinkedList list;
    int choice;
    
    while (true) {
        cout << "\n1.创建链表 2.插入 3.删除 4.按位置查找 5.按值查找 6.显示 7.清空 8.长度 9.合并 0.退出\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                cout << "输入元素(空格分隔): ";
                vector<int> vec;
                int val;
                while (cin >> val) vec.push_back(val);
                cin.clear();
                list.createFromVector(vec);
                break;
            }
            case 2: {
                int pos, val;
                cout << "位置和值: ";
                cin >> pos >> val;
                list.insert(pos, val);
                break;
            }
            case 3: {
                int pos;
                cout << "删除位置: ";
                cin >> pos;
                list.deletePos(pos);
                break;
            }
            case 4: {
                int pos;
                cout << "查找位置: ";
                cin >> pos;
                int result = list.getElem(pos);
                if (result != -1) cout << "值: " << result << endl;
                break;
            }
            case 5: {
                int val;
                cout << "查找值: ";
                cin >> val;
                int pos = list.locateElem(val);
                if (pos != -1) cout << "位置: " << pos << endl;
                else cout << "未找到" << endl;
                break;
            }
            case 6:
                list.display();
                break;
            case 7:
                list.clear();
                cout << "已清空" << endl;
                break;
            case 8:
                cout << "长度: " << list.getLength() << endl;
                break;
            case 9: {
                LinkedList list2;
                cout << "创建第二个链表: ";
                vector<int> vec;
                int val;
                while (cin >> val) vec.push_back(val);
                cin.clear();
                list2.createFromVector(vec);
                
                LinkedList merged = LinkedList::merge(list, list2);
                cout << "合并结果: ";
                merged.display();
                break;
            }
        }
    }
}

int main() {
    menu();
    return 0;
}