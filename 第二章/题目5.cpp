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
		cirList():head(nullptr),length(0)
		{
			
		}
		
		~cirList()
		{
			clear();
		}
		
		void clear()
		{
			if(head == nullptr)
			{
				return;
			}
			
			listNode<T>* current = head -> next;
			listNode<T>* temp;
			
			do{
				temp = current;
				current = current -> next;
				delete temp;
			}while(current != head);
			
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
				listNode<T>* current = head -> next;
				while(current -> next != head)
				{
					current = current -> next;
				}
				
				current -> next = newNode;
				newNode -> next = head;
			}
			
			length++;
		}
		
		listNode<T>* reverseList(listNode<T>* current)
		{
			if(current == nullptr || current -> next == nullptr)
			{
				return current;
			}
			
			listNode<T>* newHead = reverseList(current -> next);
			
			current -> next -> next = current;// 例如原链表C->D，递归时current指向C，current->next指向D，变成D->C->nullptr 
			current -> next = nullptr;
			
			return newHead;
		}
		
		void inverse()
		{
			if(head == nullptr || head -> next == head)// 只有一个节点 
			{
				return ;
			}
			
			listNode<T>* current = head;
			
			while(current -> next != head)
			{
				current = current -> next;
			}
			current -> next = nullptr;// 断开循环链表形成单链表
			
			head = reverseList(head);
			
			current = head;
			while(current -> next != nullptr)
			{
				current = current -> next;
			 } 
			 
			current -> next = head;// 再次连接成循环链表 
		}
		
		void read()
		{
			clear();
			T value;
			
			while(1)
			{
				cin >> value;
				if(value == -1)
				{
					break;
				}
				
				endInsert(value);
			}
		}
		
		void display() const
		{
		    if(head == nullptr)
		    {
				cout << "链表为空" << endl;
		        return;
		    }
		    
		    listNode<T>* current = head;
		    do {
		        cout << current->data << " ";
		        current = current->next;
			} while(current != head); // 使用do-while确保至少执行一次
			cout << endl;
	}		
};

int main() {
    cirList<int> list;
    
    while (true) {
		cout << "请输入要插入的数据（以-1结束输入）:";
        list.read();
        
		cout << "当前链表中的数据:";
        list.display();
        
        list.inverse();
        
		cout << "逆置后链表中的数据:";
        list.display();
        
        cout << endl;
    }
    
    return 0;
}
