#include <iostream> 
#include <vector>

template <class T>
class orderedList{
	private:
		T* data;
		int length;
		int maxSize;
		
	int findInsertPos(const T& x) const
	{
		int left = 0;
		int right = length;
		
		while (left < right)
		{
			int mid = left + (right - left) / 2;
			if(data[mid] < x)
			{
				left = mid + 1;
			}
			else
			{
				right = mid;
			}
		}
		return left;
	}
	
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
			if(n > maxSize)
			{
				std::cout << "超过最大容量" << std::endl;
				return;
				
			}
			
			length = n;
			for(int i = 0;i < n;i++)
			{
				data[i] = arr[i];
			}
		}
		
		bool insert(const T& x)
		{
			if(length >= maxSize)
			{
				std::cout << "列表已满" << std::endl; 
				return false;
			}
			
			int pos = length;
			pos = findInsertPos(x);
			
			for(int i = length;i > pos;i--)
			{
				data[i] = data[i - 1];
			}
			
			data[pos] = x;
			length++; 
			
			return true;
		}
		
		int getLength() const
		{
			return length;
		}
		
		void display() const
		{
			for(int i = 0;i < length;i++)
			{
				std::cout << data[i] << " ";
			}
			std::cout << std::endl;
		}
		
		
};

int main()
{
	int maxSize = 100;
	
	while(1)
	{
		int elemnum;
		std::cout << "输入存入数组的个数"<< std::endl;
		
		std::cin >> elemnum;
		
		if(elemnum == -1)
		{
			break;
		 } 
		
		if(elemnum < 0 || elemnum > maxSize)
		{
			std::cout << "错误：元素数量无效或超过最大容量！" << std::endl;
            continue;
		}
		
		orderedList<int> list1(maxSize);
		
		std::cout << "存入的数组:" << std::endl;
		
		int* temparr = new int[elemnum];
		for(int i = 0;i < elemnum ;i++)
		{
			std::cin >> temparr[i];
		}
		
		list1.initList(temparr,elemnum);
		delete[] temparr;
		
		int newelem;
		
		std::cout << "插入的元素:" << std::endl;
		std::cin >> newelem;
		
		std::cout << "插入前数据:" << std::endl;
		list1.display();
		
		if(list1.insert(newelem))
		{
			std::cout << "插入后的数据:" << std::endl;
			list1.display();
		}
		std::cout << std::endl;
	}
}
