#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template <class T>
class completeBinTree{
	private:
		vector<T> tree;
		int n; // 节点数
		
	public:
		completeBinTree():n(0){}
		
		void read(int size)
		{
			n = size;
			tree.resize(n);
			cout << "请输入各节点的值" << endl;
			
			for(int i = 0;i < n;i++)
			{
				cin >> tree[i];
			}
		} 
		
		void minRead()
		{
			if(n == 0)
			{
				return; // 如果为空 
			}
			
			stack<T> st;
			int current = 0;
			
			while(current < n || !st.empty())
			{
				while(current < n )
				{
					st.push(current); 
					current = current * 2 + 1;
				}
				
				current = st.top();
				
				st.pop();
				cout << tree[current];
				
				current = 2*current + 2;
			}
			 
		}
		
		void display()
		{
			for(int i = 0;i < n;i++)
			{
				cout << tree[i];
			}
			cout << endl;
		}
	
	 
}; 

int main()
{
	completeBinTree<int> tree;
	int n;
	
	while(1)
	{
		cout << "请输入完全二叉树的元素个数，输入-1结束程序：" << endl;
		cin >> n;
		
		if(n == -1)
		{
			break;
		 } 
		 
		tree.read(n);
		cout << "中序遍历结果为：" << endl;
		tree.minRead(); 
		
		cout << endl;
	}
	
	
}
