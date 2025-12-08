#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template <class T>
class completeBinTree{
	private:
		vector<T> tree;
		int n; //度数
		
	public:
		completeBinTree():n(0){}
		
		void read(int size)
		{
			n = size;
			tree.resize(n);
			cout << "二叉树节点数据" << endl;
			
			for(int i = 0;i < n;i++)
			{
				cin >> tree[i];
			}
		} 
		
		void minRead()
		{
			if(n == 0)
			{
				return; //树为空 
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
		cout << "输入完全二叉树的元素个数（以-1结束整个程序的运行）：" << endl;
		cin >> n;
		
		if(n == -1)
		{
			break;
		 } 
		 
		tree.read(n);
		cout << "中序遍历序列：" << endl;
		tree.minRead(); 
		
		cout << endl;
	}
	
	
}
