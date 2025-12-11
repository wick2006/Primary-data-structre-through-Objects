#include <iostream>
using namespace std;

template <class T>
class listNode{
	public:
		T data;
		listNode<T>* next; //指向下一个的指针
		
		listNode(const T& value):data(value),next(nullptr){} //next指针指向空 
		
};

template <class T>
class linkedList{
	private:
		listNode<T>* head;
		int length;
		
	public:
		linkedList():head(nullptr),length(0){}
		
		~linkedList()
		{
			clear();
		}
		
		void clear()
		{
			listNode<T>* current = head;
			while(current != nullptr)
			{
				listNode<T>* temp = current;
				current = current -> next;
				delete temp;//先把要删除的保存，在current指针指向下一个要删除的以后再删除 
			}
			head = nullptr;// 表示链表为空 
			length = 0;
		}
		
		void insertOrder(const T& value)
		{
			listNode<T>* newNode = new listNode<T>(value);
			if(head == nullptr || value <= head -> data)
			{
				newNode -> next = head;
				head = newNode;
			}
			else
			{
				listNode<T>* current = head;//设置当前指针为头指针，准备遍历 
				while(current -> next != nullptr && current -> next -> data < value)
				{
					current = current -> next;
				}
				newNode -> next = current -> next;
				current -> next = newNode;// 插入newNode在current后面 
			}
			
			length++;
		}
		
		void display() const
		{
			if(head == nullptr)
			{
				cout << "空列表" << endl;
				return;
			}
			
			listNode<T>* current = head;
			while(current != nullptr)
			{
				cout << current -> data << " ";
				current = current -> next;
			}
			cout << endl;
		}
		
		void read(int elenum)
		{
			clear(); 
			T value;
			for(int i = 0;i < elenum;i++)
			{
				cin >> value;
				insertOrder(value);
			}
		}
		
};

int main()
{
	linkedList<int> list1;
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
		
		
		 cout << "待插入的元素：";
        cin >> insertVal;
        
        cout << "插入前的链表数据：";
        list1.display();
        
        list1.insertOrder(insertVal);
        
        cout << "插入后的链表数据：";
        list1.display();
        
        cout << endl;
	}
}
