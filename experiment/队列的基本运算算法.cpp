#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// ==================== 环形队列 ====================
const int QUEUE_SIZE = 100;

class CircularQueue {
private:
    int data[QUEUE_SIZE];
    int front;
    int rear;
    int length;
    
public:
    CircularQueue() : front(0), rear(0), length(0) {}
    
    bool isEmpty() {
        return length == 0;
    }
    
    bool isFull() {
        return length == QUEUE_SIZE;
    }
    
    bool enqueue(int val) {
        if (isFull()) {
            cout << "队列满" << endl;
            return false;
        }
        data[rear] = val;
        rear = (rear + 1) % QUEUE_SIZE;
        length++;
        return true;
    }
    
    bool dequeue() {
        if (isEmpty()) {
            cout << "队列空" << endl;
            return false;
        }
        front = (front + 1) % QUEUE_SIZE;
        length--;
        return true;
    }
    
    int getFront() {
        if (isEmpty()) {
            cout << "队列空" << endl;
            return -1;
        }
        return data[front];
    }
    
    void display() {
        if (isEmpty()) {
            cout << "队列空" << endl;
            return;
        }
        
        cout << "队列内容(队头在前): ";
        int i = front;
        for (int count = 0; count < length; count++) {
            cout << data[i] << " ";
            i = (i + 1) % QUEUE_SIZE;
        }
        cout << endl;
    }
    
    void clear() {
        front = rear = 0;
        length = 0;
        cout << "队列已清空" << endl;
    }
    
    int getSize() {
        return length;
    }
};

// ==================== 链队 ====================
struct QueueNode {
    int data;
    QueueNode* next;
    QueueNode(int val = 0) : data(val), next(nullptr) {}
};

class LinkedQueue {
private:
    QueueNode* front;
    QueueNode* rear;
    int length;
    
public:
    LinkedQueue() : front(nullptr), rear(nullptr), length(0) {}
    
    ~LinkedQueue() {
        clear();
    }
    
    bool isEmpty() {
        return front == nullptr;
    }
    
    bool enqueue(int val) {
        QueueNode* newNode = new QueueNode(val);
        
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        length++;
        return true;
    }
    
    bool dequeue() {
        if (isEmpty()) {
            cout << "队列空" << endl;
            return false;
        }
        
        QueueNode* temp = front;
        front = front->next;
        delete temp;
        
        if (front == nullptr) {
            rear = nullptr;
        }
        
        length--;
        return true;
    }
    
    int getFront() {
        if (isEmpty()) {
            cout << "队列空" << endl;
            return -1;
        }
        return front->data;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "队列空" << endl;
            return;
        }
        
        cout << "队列内容(队头在前): ";
        QueueNode* current = front;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
        cout << "队列已清空" << endl;
    }
    
    int getSize() {
        return length;
    }
};

// ==================== 优先级队列 ====================
class PriorityQueue {
private:
    vector<int> heap;
    bool maxHeap;  // true为最大堆，false为最小堆
    
    void heapifyUp(int index) {
        if (index == 0) return;
        
        int parent = (index - 1) / 2;
        if (maxHeap) {
            if (heap[parent] < heap[index]) {
                swap(heap[parent], heap[index]);
                heapifyUp(parent);
            }
        } else {
            if (heap[parent] > heap[index]) {
                swap(heap[parent], heap[index]);
                heapifyUp(parent);
            }
        }
    }
    
    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int extreme = index;
        
        if (maxHeap) {
            if (left < heap.size() && heap[left] > heap[extreme]) {
                extreme = left;
            }
            if (right < heap.size() && heap[right] > heap[extreme]) {
                extreme = right;
            }
        } else {
            if (left < heap.size() && heap[left] < heap[extreme]) {
                extreme = left;
            }
            if (right < heap.size() && heap[right] < heap[extreme]) {
                extreme = right;
            }
        }
        
        if (extreme != index) {
            swap(heap[index], heap[extreme]);
            heapifyDown(extreme);
        }
    }
    
public:
    PriorityQueue(bool isMaxHeap = true) : maxHeap(isMaxHeap) {}
    
    bool isEmpty() {
        return heap.empty();
    }
    
    void enqueue(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }
    
    bool dequeue() {
        if (isEmpty()) {
            cout << "队列空" << endl;
            return false;
        }
        
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return true;
    }
    
    int getFront() {
        if (isEmpty()) {
            cout << "队列空" << endl;
            return -1;
        }
        return heap[0];
    }
    
    void display() {
        if (isEmpty()) {
            cout << "队列空" << endl;
            return;
        }
        
        cout << "优先级队列内容: ";
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    void clear() {
        heap.clear();
        cout << "队列已清空" << endl;
    }
    
    int getSize() {
        return heap.size();
    }
    
    void changePriority(bool newMaxHeap) {
        if (maxHeap != newMaxHeap) {
            maxHeap = newMaxHeap;
            // 重建堆
            for (int i = heap.size() / 2 - 1; i >= 0; i--) {
                heapifyDown(i);
            }
        }
    }
};

// ==================== 双端队列 ====================
class Deque {
private:
    vector<int> data;
    
public:
    Deque() {}
    
    bool isEmpty() {
        return data.empty();
    }
    
    void pushFront(int val) {
        data.insert(data.begin(), val);
    }
    
    void pushBack(int val) {
        data.push_back(val);
    }
    
    bool popFront() {
        if (isEmpty()) {
            cout << "队列空" << endl;
            return false;
        }
        data.erase(data.begin());
        return true;
    }
    
    bool popBack() {
        if (isEmpty()) {
            cout << "队列空" << endl;
            return false;
        }
        data.pop_back();
        return true;
    }
    
    int getFront() {
        if (isEmpty()) {
            cout << "队列空" << endl;
            return -1;
        }
        return data.front();
    }
    
    int getBack() {
        if (isEmpty()) {
            cout << "队列空" << endl;
            return -1;
        }
        return data.back();
    }
    
    void display() {
        if (isEmpty()) {
            cout << "队列空" << endl;
            return;
        }
        
        cout << "双端队列内容: ";
        for (int val : data) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    void clear() {
        data.clear();
        cout << "队列已清空" << endl;
    }
    
    int getSize() {
        return data.size();
    }
};

// ==================== 主菜单 ====================
void circularQueueMenu() {
    CircularQueue queue;
    int choice;
    
    while (true) {
        cout << "\n环形队列操作:";
        cout << "\n1.入队 2.出队 3.获取队头 4.显示 5.清空 6.判空 7.判满 8.大小 0.返回\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                int val;
                cout << "输入入队值: ";
                cin >> val;
                queue.enqueue(val);
                break;
            }
            case 2:
                if (queue.dequeue()) {
                    cout << "出队成功" << endl;
                }
                break;
            case 3: {
                int front = queue.getFront();
                if (front != -1) {
                    cout << "队头元素: " << front << endl;
                }
                break;
            }
            case 4:
                queue.display();
                break;
            case 5:
                queue.clear();
                break;
            case 6:
                if (queue.isEmpty()) cout << "队列空" << endl;
                else cout << "队列非空" << endl;
                break;
            case 7:
                if (queue.isFull()) cout << "队列满" << endl;
                else cout << "队列未满" << endl;
                break;
            case 8:
                cout << "队列大小: " << queue.getSize() << endl;
                break;
        }
    }
}

void linkedQueueMenu() {
    LinkedQueue queue;
    int choice;
    
    while (true) {
        cout << "\n链队操作:";
        cout << "\n1.入队 2.出队 3.获取队头 4.显示 5.清空 6.判空 7.大小 0.返回\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                int val;
                cout << "输入入队值: ";
                cin >> val;
                queue.enqueue(val);
                break;
            }
            case 2:
                if (queue.dequeue()) {
                    cout << "出队成功" << endl;
                }
                break;
            case 3: {
                int front = queue.getFront();
                if (front != -1) {
                    cout << "队头元素: " << front << endl;
                }
                break;
            }
            case 4:
                queue.display();
                break;
            case 5:
                queue.clear();
                break;
            case 6:
                if (queue.isEmpty()) cout << "队列空" << endl;
                else cout << "队列非空" << endl;
                break;
            case 7:
                cout << "队列大小: " << queue.getSize() << endl;
                break;
        }
    }
}

void priorityQueueMenu() {
    PriorityQueue queue(true);  // 默认最大堆
    int choice;
    
    while (true) {
        cout << "\n优先级队列操作:";
        cout << "\n1.入队 2.出队 3.获取队头 4.显示 5.清空 6.判空 7.大小 8.切换最大/最小堆 0.返回\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                int val;
                cout << "输入入队值: ";
                cin >> val;
                queue.enqueue(val);
                break;
            }
            case 2:
                if (queue.dequeue()) {
                    cout << "出队成功" << endl;
                }
                break;
            case 3: {
                int front = queue.getFront();
                if (front != -1) {
                    cout << "队头元素: " << front << endl;
                }
                break;
            }
            case 4:
                queue.display();
                break;
            case 5:
                queue.clear();
                break;
            case 6:
                if (queue.isEmpty()) cout << "队列空" << endl;
                else cout << "队列非空" << endl;
                break;
            case 7:
                cout << "队列大小: " << queue.getSize() << endl;
                break;
            case 8: {
                cout << "1.最大堆 2.最小堆\n选择: ";
                int opt;
                cin >> opt;
                queue.changePriority(opt == 1);
                cout << "已切换" << endl;
                break;
            }
        }
    }
}

void dequeMenu() {
    Deque deque;
    int choice;
    
    while (true) {
        cout << "\n双端队列操作:";
        cout << "\n1.前端入队 2.后端入队 3.前端出队 4.后端出队 5.获取前端 6.获取后端 7.显示 8.清空 9.判空 10.大小 0.返回\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                int val;
                cout << "输入前端入队值: ";
                cin >> val;
                deque.pushFront(val);
                break;
            }
            case 2: {
                int val;
                cout << "输入后端入队值: ";
                cin >> val;
                deque.pushBack(val);
                break;
            }
            case 3:
                if (deque.popFront()) {
                    cout << "前端出队成功" << endl;
                }
                break;
            case 4:
                if (deque.popBack()) {
                    cout << "后端出队成功" << endl;
                }
                break;
            case 5: {
                int front = deque.getFront();
                if (front != -1) {
                    cout << "前端元素: " << front << endl;
                }
                break;
            }
            case 6: {
                int back = deque.getBack();
                if (back != -1) {
                    cout << "后端元素: " << back << endl;
                }
                break;
            }
            case 7:
                deque.display();
                break;
            case 8:
                deque.clear();
                break;
            case 9:
                if (deque.isEmpty()) cout << "队列空" << endl;
                else cout << "队列非空" << endl;
                break;
            case 10:
                cout << "队列大小: " << deque.getSize() << endl;
                break;
        }
    }
}

int main() {
    int choice;
    
    while (true) {
        cout << "\n========== 队列系统 ==========";
        cout << "\n1.环形队列 2.链队 3.优先级队列 4.双端队列 0.退出\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1:
                circularQueueMenu();
                break;
            case 2:
                linkedQueueMenu();
                break;
            case 3:
                priorityQueueMenu();
                break;
            case 4:
                dequeMenu();
                break;
        }
    }
    
    return 0;
}