#include <iostream>
#include <vector>
using namespace std;

// ==================== 顺序栈 ====================
const int MAX_SIZE = 100;

class SeqStack {
private:
    int data[MAX_SIZE];
    int top;
    
public:
    SeqStack() : top(-1) {}
    
    bool isEmpty() {
        return top == -1;
    }
    
    bool isFull() {
        return top == MAX_SIZE - 1;
    }
    
    bool push(int val) {
        if (isFull()) {
            cout << "栈满" << endl;
            return false;
        }
        data[++top] = val;
        return true;
    }
    
    bool pop() {
        if (isEmpty()) {
            cout << "栈空" << endl;
            return false;
        }
        top--;
        return true;
    }
    
    int getTop() {
        if (isEmpty()) {
            cout << "栈空" << endl;
            return -1;
        }
        return data[top];
    }
    
    void display() {
        if (isEmpty()) {
            cout << "栈空" << endl;
            return;
        }
        
        cout << "栈内容(栈顶在上): ";
        for (int i = top; i >= 0; i--) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    
    void clear() {
        top = -1;
        cout << "栈已清空" << endl;
    }
    
    int getSize() {
        return top + 1;
    }
};

// ==================== 链栈 ====================
struct LinkNode {
    int data;
    LinkNode* next;
    LinkNode(int val = 0) : data(val), next(nullptr) {}
};

class LinkStack {
private:
    LinkNode* top;
    int length;
    
public:
    LinkStack() : top(nullptr), length(0) {}
    
    ~LinkStack() {
        clear();
    }
    
    bool isEmpty() {
        return top == nullptr;
    }
    
    bool push(int val) {
        LinkNode* newNode = new LinkNode(val);
        newNode->next = top;
        top = newNode;
        length++;
        return true;
    }
    
    bool pop() {
        if (isEmpty()) {
            cout << "栈空" << endl;
            return false;
        }
        
        LinkNode* temp = top;
        top = top->next;
        delete temp;
        length--;
        return true;
    }
    
    int getTop() {
        if (isEmpty()) {
            cout << "栈空" << endl;
            return -1;
        }
        return top->data;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "栈空" << endl;
            return;
        }
        
        cout << "栈内容(栈顶在上): ";
        LinkNode* current = top;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    void clear() {
        while (!isEmpty()) {
            pop();
        }
        cout << "栈已清空" << endl;
    }
    
    int getSize() {
        return length;
    }
};

// ==================== 主菜单 ====================
void seqStackMenu() {
    SeqStack stack;
    int choice;
    
    while (true) {
        cout << "\n顺序栈操作:";
        cout << "\n1.入栈 2.出栈 3.获取栈顶 4.显示 5.清空 6.判空 7.判满 8.大小 0.返回\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                int val;
                cout << "输入入栈值: ";
                cin >> val;
                stack.push(val);
                break;
            }
            case 2:
                if (stack.pop()) {
                    cout << "出栈成功" << endl;
                }
                break;
            case 3: {
                int topVal = stack.getTop();
                if (topVal != -1) {
                    cout << "栈顶元素: " << topVal << endl;
                }
                break;
            }
            case 4:
                stack.display();
                break;
            case 5:
                stack.clear();
                break;
            case 6:
                if (stack.isEmpty()) cout << "栈空" << endl;
                else cout << "栈非空" << endl;
                break;
            case 7:
                if (stack.isFull()) cout << "栈满" << endl;
                else cout << "栈未满" << endl;
                break;
            case 8:
                cout << "栈大小: " << stack.getSize() << endl;
                break;
        }
    }
}

void linkStackMenu() {
    LinkStack stack;
    int choice;
    
    while (true) {
        cout << "\n链栈操作:";
        cout << "\n1.入栈 2.出栈 3.获取栈顶 4.显示 5.清空 6.判空 7.大小 0.返回\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                int val;
                cout << "输入入栈值: ";
                cin >> val;
                stack.push(val);
                break;
            }
            case 2:
                if (stack.pop()) {
                    cout << "出栈成功" << endl;
                }
                break;
            case 3: {
                int topVal = stack.getTop();
                if (topVal != -1) {
                    cout << "栈顶元素: " << topVal << endl;
                }
                break;
            }
            case 4:
                stack.display();
                break;
            case 5:
                stack.clear();
                break;
            case 6:
                if (stack.isEmpty()) cout << "栈空" << endl;
                else cout << "栈非空" << endl;
                break;
            case 7:
                cout << "栈大小: " << stack.getSize() << endl;
                break;
        }
    }
}

int main() {
    int choice;
    
    while (true) {
        cout << "\n========== 栈系统 ==========";
        cout << "\n1.顺序栈 2.链栈 0.退出\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1:
                seqStackMenu();
                break;
            case 2:
                linkStackMenu();
                break;
        }
    }
    
    return 0;
}