#include <iostream>
using namespace std;

class listNode{
	public:
		int value;
		listNode* next;
		
		listNode(int x):value(x),next(nullptr){}
};

class linkList{
	private:
		listNode* head;
		
	// current: 当前处理的节点指针
    // length: 当前需要处理的链表长度
    // round: 当前是第几轮排序（外部初始化为链表长度）
	    listNode* bubbleSort(listNode* current, int length) 
		{
	        // 递归终止条件：所有轮次已完成或链表已排序好
	        if (length <= 1) 
			{
	            return current;
	        }
	        
	        // 如果到达链表末尾，开始新的一轮
	        if (current == nullptr || current->next == nullptr) 
			{
	            // 重新从头开始，进行下一轮
	            return bubbleSort(head, length - 1);
	        }
	        
	        // 比较当前节点和下一个节点
	        if (current->value > current->next->value) 
			{
	            // 交换数据
	            swap(current->value, current->next->value);
	        }
	        
	        // 继续处理下一个节点
	        return bubbleSort(current->next, length);
	    }
    
    public:
    	linkList():head(nullptr){}
    	
    	~linkList()
		{
    		clear();
		}
		
		void clear()
		{
			listNode* current = head;
			while(current != nullptr)
			{
				listNode* temp = current;
				current = current->next;
				delete temp;
			}
			head = nullptr;
		}
		
		void push(int val) // 尾部插入 
		{
			listNode* newNode = new listNode(val);
			
			if(head == nullptr)
			{
				head = newNode;
			}
			else
			{
				listNode* current = head;
				while(current->next != nullptr)
				{
					current = current->next;
				}
				
				current->next = newNode;
			}
		}
		
		int getLength()
		{
			listNode* current = head;
			int len = 0;
			while(current != nullptr)
			{
				len++;
				current = current->next;
			}
			
			return len;
		}
		
		void listSort()
		{
			int length = getLength();
			if(length <= 1) return;
			
			bubbleSort(head,length);
		}
		
		void display()
		{
			listNode* current = head;
			
			while(current!=nullptr)
			{
				cout << current->value << " ";
				current = current->next;
			}
			cout << endl;
		}
};

int main()
{
	while (true) 
	{
        linkList list;
        int num;
        
        cout << "请输入一组整数（以0结束输入，以-1结束程序）: ";
        cin >> num;
        
        if (num == -1) {
            break;
        }
        
        while (num != 0) {
            list.push(num);
            cin >> num;
        }
        
        cout << "排序前的序列: ";
        list.display();
        
        list.listSort();
        
        cout << "排序后的序列: ";
        list.display();
        cout << endl;
    }
    
    return 0;
}


