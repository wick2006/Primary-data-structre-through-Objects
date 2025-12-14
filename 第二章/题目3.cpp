#include <iostream>
using namespace std;

template <class T>
class listNode {
public:
	T data;
	listNode<T>* next; // 指向下一个节点的指针

	listNode(const T& value) : data(value), next(nullptr) {} // 构造函数，next指向空
};

template <class T>
class linkedList {
private:
	listNode<T>* head;
	int length;

public:
	linkedList() : head(nullptr), length(0) {}

	~linkedList() {
		clear();
	}

	void clear() {
		listNode<T>* current = head;
		while (current != nullptr) {
			listNode<T>* temp = current;
			current = current->next;
			delete temp; // 先删除当前节点，再让current指向下一个要删除的节点
		}
		head = nullptr; // 表示链表为空
		length = 0;
	}

	void insertOrder(const T& value) {
		listNode<T>* newNode = new listNode<T>(value);
		if (head == nullptr || value <= head->data) {
			newNode->next = head;
			head = newNode;
		} else {
			listNode<T>* current = head; // 当前指针为头指针，准备遍历
			while (current->next != nullptr && current->next->data < value) {
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode; // 插入newNode到current之后
		}

		length++;
	}

	void display() const {
		if (head == nullptr) {
			cout << "链表为空" << endl;
			return;
		}

		listNode<T>* current = head;
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}

	void read(int elenum) {
		clear();
		T value;
		for (int i = 0; i < elenum; i++) {
			cin >> value;
			insertOrder(value);
		}
	}
};

int main() {
	linkedList<int> list1;
	int elenum;
	int insertVal;

	while (1) {
		cout << "请输入链表元素个数（输入-1结束）：";
		cin >> elenum;

		if (elenum == -1) {
			break;
		}

		cout << "请输入链表元素：" << endl;

		list1.read(elenum);

		cout << "请输入要插入的元素：";
		cin >> insertVal;

		cout << "插入前链表数据：";
		list1.display();

		list1.insertOrder(insertVal);

		cout << "插入后链表数据：";
		list1.display();

		cout << endl;
	}
}
