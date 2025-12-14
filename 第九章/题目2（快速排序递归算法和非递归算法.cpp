#include <iostream>
#include <vector>
#include <stack> 
#include <algorithm>
using namespace std;

// 递归实现快速排序
void quickSort_recursion(vector<int>& arr,int start,int end)
{
	int left = start;
	int right = end;
	int key = arr[start];
	
	if(start >= end)
	{
		return;
	}
	
	while(left < right)
	{
		// 找到右边小于key的值停下
		while(left < right && arr[right] >= key)
		{
			right--;
		}
		
		// 找到左边大于key的值停下
		while(left < right && arr[left] <= key)
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

// 非递归实现快速排序
void quickSort_nonRec(vector<int>& arr,int start,int end)
{
	if(start >= end) return;
	
	stack<pair<int,int> > arrStack;
	arrStack.push({start,end}); // 初始区间入栈（栈中存储待排序区间的起止下标）
	
	while(!arrStack.empty()) // 栈不空说明还有区间需要排序
	{
		pair<int,int> current = arrStack.top();
		arrStack.pop();// 取出栈顶区间
		
		int left = current.first;  // current存储一个区间的起止下标
		int right = current.second;
		
		if(left >= right) continue; // 区间只有一个元素，无需排序
		
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
		
		// 先压右区间再压左区间，保证左区间先处理
		arrStack.push({rightPtr + 1,right});
		arrStack.push({left,rightPtr - 1});
	}
}

// 显示数组
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
		// 判断是否继续
		cout << "输入1开始测试，输入-1退出：";
		int choice;
		cin >> choice;
		
		if (choice == -1) {
			cout << "程序结束" << endl;
			break;
		}
		
		if (choice != 1) {
			cout << "无效输入，请重新输入。" << endl;
			continue;
		}
		
		// 获取数据
		cout << "请输入待排序的整数（以0结束输入）：" << endl;
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
		cout << "递归算法排序结果" << endl;
		
		// 递归快速排序
		vector<int> arr_recursive = numbers;
		cout << "排序前数组:";
		display(arr_recursive);
		cout << "排序后数组:";
		quickSort_recursion(arr_recursive, 0, arr_recursive.size() - 1);
		display(arr_recursive);
		
		cout << endl;
		cout << "非递归算法排序结果" << endl;
		
		// 非递归快速排序
		vector<int> arr_nonrecursive = numbers;
		cout << "排序前数组:";
		display(arr_nonrecursive);
		
		quickSort_nonRec(arr_nonrecursive,0,arr_nonrecursive.size()-1);
		cout << "排序后数组:";
		display(arr_nonrecursive);
		
		cout << endl;
	}
	
	return 0;
}
