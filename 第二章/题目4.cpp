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
		    
		    // 先删除除头节点外的所有节点
		    while(current != head)
		    {
		        temp = current;
		        current = current->next;
		        delete temp;
		    }
		    
		    // 最后删除头节点
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
				listNode<T>* tail = head; //尾节点指向头节点
				while(tail->next != head)
				{
					tail = tail -> next; 
				} 
				
				tail -> next = newNode;
				newNode -> next = head; //在尾节点后插入新节点。
				 
			}
			
			length++;
		}
		
		void delMin()
		{
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
			
			if(min == head)//最小节点是头节点则更新 
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
		        cout << "空列表" << endl;
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
		cout << "存入链表的元素个数（以-1结束整个程序的运行）：";
        cin >> elenum;
        
        if(elenum == -1)
        {
        	break;
		}
		
		cout << "存入链表的数据" << endl;
	
		list1.read(elenum);
		
        
        cout << "删除前的链表数据：";
        list1.display();
        
        list1.delMin();
        
        cout << "删除后的链表数据：";
        list1.display();
        
        cout << endl;
	}
}
