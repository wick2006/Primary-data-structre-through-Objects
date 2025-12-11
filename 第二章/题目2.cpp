#include<iostream>

using namespace std;

template<class T>
class orderedList{
	private:
		T* data;
		int length;
		int maxSize;
		
		
		
	public:
		orderedList(int size = 100):length(0),maxSize(size)
		{
			data = new T[maxSize];
		}
		
		~orderedList()
		{
			delete[] data;
		}
		
		void initList(const T arr[],int n)
		{
			length = n;
			for(int i = 0;i < length;i++)
			{
				data[i] = arr[i];
			}
		}
		
		void display() const
		{
			for(int i = 0;i < length;i++)
			{
				cout << data[i] << " ";
			}
			cout << endl;
		}
		
		void deleteMin()
		{
			int minindex = 0;
			for(int i = 0;i < length;i++)
			{
				if(data[i] < data[minindex])
				{
					minindex = i;
				}
				
			}
			
			for(int i = minindex;i < length-1;i++)
			{
				data[i] = data[i+1];
			}
			
			length--;
		}
}; 

int main()
{
	while(1)
	{
		orderedList<int> list2(100);
		
		cout << "输入元素个数:" << endl;
		int elemnum;
		cin >> elemnum;
		
		if(elemnum == -1)
		{
			break;
		}
		
		int* tempList = new int[elemnum];
		cout << "输入元素" << endl; 
		for(int i = 0;i < elemnum;i++)
		{
			cin >> tempList[i];
		}
		
		list2.initList(tempList,elemnum);
		
		cout << "删除前元素:" << endl;
		list2.display();
		
		list2.deleteMin();
		cout << "删除后:" << endl;
		list2.display();
	}
	
}
