#include <iostream>
using namespace std;

template <class T>
class listNode{
	public:
		T data;
		listNode<T>* next;
		
	listNode(const T& value):data(value),next(nullptr)
	{
		
	}
};

template <class T>
class cirList{
	private:
		listNode<T>* head;
		int length;
		
	public:
		cirList():head(nullptr),length(0){}
		
		~cirList()
		{
			clear();
		}
		
		void clear()
		{
			if(head == nullptr) return;
			
			listNode<T>* current = head->next;
			listNode<T>* temp;
			
			// 先删除头结点之后的所有节点
			while(current != head)
			{
				temp = current;
				current = current->next;
				delete temp;
			}
			
			// 最后删除头结点
			delete head;
			head = nullptr;
			length = 0;
		}

		
		void endInsert(const T& value)
		{
			listNode<T>* newNode = new listNode<T>(value);
			
			if(head == nullptr)
			{
				head = newNode;
				head -> next = head;
			}
			else
			{
				listNode<T>* tail = head; // 尾节点指向头结点
				while(tail->next != head)
				{
					tail = tail -> next; 
				} 
				
				tail -> next = newNode;
				newNode -> next = head; // 新尾节点指向头结点
				 
			}
			
			length++;
		}
		
		void delMin()
		{
			if(head == nullptr) return;
			if(head -> next == head)
			{
				delete head;
				head = nullptr;
				length = 0;
				return;
			}
			
			listNode<T>* min = head;
			listNode<T>* prev = head;
			listNode<T>* minPrev = head;
			listNode<T>* current = head -> next;
			
			while(current != head)
			{
				if(current -> data < min -> data)
				{
					min = current;
					minPrev = prev;
				}
				prev = current;
				current = current -> next;
			}
			
			if(min == head)// 最小节点是头结点
			{
				listNode<T>* tail = head;
				while(tail->next != head)
				{
					tail = tail -> next;
				}
				
				head = head -> next;
				tail -> next = head; 
			}
			else
			{
				minPrev -> next = min -> next;
			}
			
			delete min;
			length--;
			return;
		}
		
		void display() const
		{
			if(head == nullptr)
			{
				cout << "空链表" << endl;
				return;
			}
			
			listNode<T>* current = head;
			do {
				cout << current->data << " ";
				current = current->next;
			} while(current != head); // 使用do-while确保至少执行一次
			cout << endl;
		}        
		
		void read(int elenum)
		{
			clear(); 
			T value;
			for(int i = 0;i < elenum;i++)
			{
				cin >> value;
				endInsert(value);
			}
		}
}; 

int main()
{
	cirList<int> list1;
	int elenum;
	int insertVal;
	
	while(1)
	{
		cout << "请输入元素个数，输入-1结束程序：" ;
		cin >> elenum;
		
		if(elenum == -1)
		{
			break;
		}
		
		cout << "请输入链表元素：" << endl;
	
		list1.read(elenum);
		
		cout << "删除前链表数据：";
		list1.display();
		
		list1.delMin();
		
		cout << "删除最小元素后链表数据：";
		list1.display();
		
		cout << endl;
	}
}
