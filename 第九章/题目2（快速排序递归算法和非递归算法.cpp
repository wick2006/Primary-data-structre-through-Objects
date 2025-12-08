#include <iostream>
#include <vector>
#include <stack> 
#include <algorithm>
using namespace std;

void quickSort_recursion(vector<int>& arr,int start,int end)
{
	int left = start;
	int right = end;
	int key = arr[start];
	
	if(start >= end)
	{
		return;
	}
	
	while(left<right)
	{
		while(left < right && arr[right] >= key )//找到右边小于等于key的值后停下（或者左索引等于右索引） 
		{
			right--;
		}
		
		while(left < right && arr[left] <= key)//找到左边大于等于key的值后停下 同上 
		{
			left++;
		}
		
		if(left < right)
		{
			swap(arr[left],arr[right]);
		}
		
	}
	
	swap(arr[start],arr[right]);
	
	quickSort_recursion(arr,start,right-1);
	quickSort_recursion(arr,right+1,end);
	
}

void quickSort_nonRec(vector<int>& arr,int start,int end)
{
	if(start >= end) return;
	
	stack<pair<int,int> > arrStack;
	arrStack.push({start,end}); //将初始区间压入栈中(栈中存储分段区间值） 
	
	while(!arrStack.empty()) // 栈空说明排序已完成 
	{
		pair<int,int> current = arrStack.top();
		arrStack.pop();//取栈顶的进行排序
		
		int left = current.first;//current存储一个数组的区间。current.first 表示一个区间的开始second表示结束， 
		int right = current.second;
		
		if(left >= right) continue;//对于只有一个元素的区间和无效区间跳过排序过程 
		
		int key = arr[left];
		int leftPtr = left;
		int rightPtr = right;
		
		while(leftPtr < rightPtr)
		{
			while(leftPtr < rightPtr && arr[rightPtr] >= key)
			{
				rightPtr--;
			}
			while(leftPtr < rightPtr && arr[leftPtr] <= key)
			{
				leftPtr++;
			}
			if(leftPtr < rightPtr)
			{
				swap(arr[leftPtr],arr[rightPtr]);
			}
		}
		
		swap(arr[left],arr[rightPtr]);
		
		arrStack.push({rightPtr + 1,right});// 保证左区间在栈顶，先将右区间压入栈 
		arrStack.push({left,rightPtr - 1});
		
	}
	
}

void display(const vector<int>& arr)
{
	for(int i = 0;i < arr.size();i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
    while (true) {
        // 检查是否结束程序
        cout << "输入1开始测试，输入-1结束程序：";
        int choice;
        cin >> choice;
        
        if (choice == -1) {
            cout << "程序结束。" << endl;
            break;
        }
        
        if (choice != 1) {
            cout << "无效输入，请重新输入。" << endl;
            continue;
        }
        
        // 读取数据
        cout << "请输入若干个整数（以0结束输入）：" << endl;
        vector<int> numbers;
        int num;
        
        while (cin >> num) {
            if (num == 0) break;
            numbers.push_back(num);
        }
        
        if (numbers.empty()) {
            cout << "输入为空，请重新输入。" << endl;
            continue;
        }
        
        cout << endl;
        cout << "快速排序递归算法" << endl;
        
        // 创建副本用于递归排序
        vector<int> arr_recursive = numbers;
        cout << "排序前的序列:";
        display(arr_recursive);
        cout << "排序后的序列:";
        quickSort_recursion(arr_recursive, 0, arr_recursive.size() - 1);
        display(arr_recursive);
        
        cout << endl;
        cout << "快速排序非递归算法：" << endl;
        
        // 创建副本用于非递归排序
        vector<int> arr_nonrecursive = numbers;
        cout << "排序前的序列:";
        display(arr_nonrecursive);
        
        // 注意：这里只传入数组，不需要传入区间
        quickSort_nonRec(arr_nonrecursive,0,arr_nonrecursive.size()-1);
        cout << "排序后的序列:";
        display(arr_nonrecursive);
        
        cout << endl;
    }
    
    return 0;
}
