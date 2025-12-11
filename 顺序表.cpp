#include <iostream>
#include <cstdlib>
const int defaultSize = 100;

template <class T>
class seqList{
	private:
		int maxSize;
		int last;//已存的最后位置 
		T *data;
		void reSize(int newSize);
	
	public:
		seqList(int as = defaultSize);
		seqList(seqList<T>& L);
		~seqList() {delete[] data;}
		int slSize() const {return maxSize;}
		int slLength() const {return last+1;}
		int slSearch(const T& x)const;
		int slLocate(int i)const;
		bool getData(int i,T& x)const
		{
			if(i > 0 && i <= last+1)
			{
				x == data[i-1];
				return true;
			}
			else
			{
				return false;
			}
		}
		bool slInsert(int i,const T& x);
		bool slRemove(int i,T& x);
		bool isEmpty() const
		{
			return last == -1 ? true : false;
		}
		bool isFull() const
		{
			return last == maxSize - 1? true : false;
		}
		
		void input();
		void output();
		seqList<T>& operator=(const seqList<T>& L);
		
}; 


template <class T>
seqList<T>::seqList(int as) //构造函数 
{
	if(as > 0)
	{
		maxSize = as;
		last = -1;
		data = new T[maxSize];
		
		if(data == NULL)
		{
			std::cerr << "存储空间分配错误" ;
			exit(1);
		}
	}
};

template <class T>
seqList<T>::seqList(seqList<T>& L)//复制构造函数 
{
	maxSize = L.slSize();
	last = L.slLength() - 1;
	data = new T[maxSize];
	T value;
	if(data == NULL)
	{
		std::cerr << "存储空间分配错误" ;
		exit(1);
	}
	
	for(int i = 0;i <= last;i++)
	{
		L.getData(i,value);
		data[i] = value;
	}
};

template<class T>
void seqList<T>::reSize(int newSize)
{
	if(newSize <= 0)
	{
		std::cerr << "无效" << std::endl;
		exit(1) ;
	}	
	
	if(newSize != maxSize)
	{
		T* newarray = new T[newSize];
		if(newarray == NULL)
		{
			std::cerr << "存储空间分配错误" ;
			exit(1);
		}
		
		int n = last+1;
		T* srcptr = data;//源数组首地址 
		T* desptr = newarray;//目的数组首地址
		while(n--)
		{
			*desptr++ = *srcptr++;
		 } 
		delete[] data;
		data = newarray;
		maxSize = newSize;
	}
};
 
template<class T>
int seqList<T>::slSearch(const T& x) const
{
	for(int i = 0;i <= last;i++)
	{
		if(data[i] == x)
		{
			return i+1;
		}
	}
	return 0;
};

template<class T>
int seqList<T>::slLocate(int i) const
{
	if(i >= 1 && i <= last+1)
	{
		return i;
	}
	else
		return 0;
};

template<class T>
bool seqList<T>::slInsert(int i,const T& x)
{
	if(last == maxSize - 1)
	{
		return false;
	}
	if(i < 0 || i > last + 1)
	{
		return false;
	}
	
	for(int j = last;j >= i;j--)
	{
		data[j+1] = data[j];
	}
	data[i] = x;
	last++;
	return true;
};

template<class T>
bool seqList<T>::slRemove(int i,T& x)
{
	if(last == -1)return false;
	if(i < 1 || i > last + 1) return false;
	
	x = data[i - 1];
	for(int j = i;j <= last;j++)
	{
		data[j-1] = data[j];
	} 
	last--;
	return true;
};

template <class T>
void seqList<T>::input()
{
	std::cout << "请输入表中元素个数" << std::endl;
	
	while(1)
	{
		std::cin >> last;
		if(last <= maxSize) break;
		
		std::cout << "表中元素个数不能超过" << maxSize - 1 << "请重新输入" << std::endl;
		
	}
	
	for(int i = 0;i <= last;i++)
	{
		std::cout << i+1 << " " ; 
		std::cin >> data[i];
	}
};

template <class T>
void seqList<T>::output()
{
	std::cout << "顺序表当前元素的最后位置:" << last << std::endl;
	
	for(int i = 0;i <= last;i++)
	{
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
	
 };

template <class T>
seqList<T>& seqList<T>::operator=(const seqList<T>& L)
{
	if (this != &L)
	{
		delete[] data;
		maxSize = L.maxSize;
		last = L.last;
		data = new T[maxSize];
		
		if(data == NULL)
		{
			std::cerr << "存储空间分配错误" << std::endl;
			exit(1);
		}
		
		for(int i = 0;i <= last;i++)
		{
			data[i] = L.data[i];
		}
	}
	
	return *this;
};

int main()
{
	seqList<int> list1;
	
	for(int i = 0;i <= 5;i++)
	{
		list1.slInsert(i,i*10);
	}
	list1.output();
	
	int removed;
	list1.slRemove(3,removed);
		std::cout << "删除的元素:" << removed << std::endl;
	list1.output();
	
	int searchVal = 40;
	int pos = list1.slSearch(searchVal);
	if(pos > 0)
	{
		std::cout << "元素" << searchVal << "在" << pos << std:: endl;
	}
	list1.output();
	std::cout << std::endl;
	seqList<int> list2 = list1;
	std::cout << list2.getData(0,0) << std::endl;
	list2.output();
	
	return 0;
}










