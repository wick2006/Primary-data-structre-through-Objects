#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <random>
using namespace std;

// 排序算法统计结构
struct SortStats {
    long long compareCount;  // 比较次数
    long long moveCount;     // 移动次数
    double timeCost;        // 时间（秒）
    bool sorted;            // 是否排序成功
    
    SortStats() : compareCount(0), moveCount(0), timeCost(0.0), sorted(false) {}
};

// 工具函数：判断数组是否已排序
template<typename T>
bool isSorted(const vector<T>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i-1]) return false;
    }
    return true;
}

// 工具函数：判断是否为堆序列
template<typename T>
bool isHeap(const vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        
        if (left < n && arr[i] < arr[left]) return false;
        if (right < n && arr[i] < arr[right]) return false;
    }
    return true;
}

// ==================== 排序算法实现 ====================

// 1. 直接插入排序
SortStats insertionSort(vector<int>& arr) {
    SortStats stats;
    clock_t start = clock();
    
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0) {
            stats.compareCount++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                stats.moveCount++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
        stats.moveCount++;  // 插入操作
    }
    
    clock_t end = clock();
    stats.timeCost = double(end - start) / CLOCKS_PER_SEC;
    stats.sorted = isSorted(arr);
    return stats;
}

// 2. 折半插入排序
SortStats binaryInsertionSort(vector<int>& arr) {
    SortStats stats;
    clock_t start = clock();
    
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int left = 0, right = i - 1;
        
        // 折半查找插入位置
        while (left <= right) {
            stats.compareCount++;
            int mid = left + (right - left) / 2;
            if (key < arr[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        // 移动元素
        for (int j = i - 1; j >= left; j--) {
            arr[j + 1] = arr[j];
            stats.moveCount++;
        }
        
        arr[left] = key;
        stats.moveCount++;  // 插入操作
    }
    
    clock_t end = clock();
    stats.timeCost = double(end - start) / CLOCKS_PER_SEC;
    stats.sorted = isSorted(arr);
    return stats;
}

// 3. 希尔排序
SortStats shellSort(vector<int>& arr) {
    SortStats stats;
    clock_t start = clock();
    
    int n = arr.size();
    
    // 使用希尔增量序列
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            
            for (j = i; j >= gap; j -= gap) {
                stats.compareCount++;
                if (arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    stats.moveCount++;
                } else {
                    break;
                }
            }
            
            arr[j] = temp;
            stats.moveCount++;
        }
    }
    
    clock_t end = clock();
    stats.timeCost = double(end - start) / CLOCKS_PER_SEC;
    stats.sorted = isSorted(arr);
    return stats;
}

// 4. 冒泡排序
SortStats bubbleSort(vector<int>& arr) {
    SortStats stats;
    clock_t start = clock();
    
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            stats.compareCount++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                stats.moveCount += 3;  // 交换算3次移动
                swapped = true;
            }
        }
        
        // 如果这一轮没有交换，说明已经有序
        if (!swapped) break;
    }
    
    clock_t end = clock();
    stats.timeCost = double(end - start) / CLOCKS_PER_SEC;
    stats.sorted = isSorted(arr);
    return stats;
}

// 5. 快速排序辅助函数（划分）
int partition(vector<int>& arr, int low, int high, SortStats& stats) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        stats.compareCount++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            stats.moveCount += 3;
        }
    }
    
    swap(arr[i + 1], arr[high]);
    stats.moveCount += 3;
    return i + 1;
}

// 快速排序递归函数
void quickSortRecursive(vector<int>& arr, int low, int high, SortStats& stats) {
    if (low < high) {
        int pi = partition(arr, low, high, stats);
        quickSortRecursive(arr, low, pi - 1, stats);
        quickSortRecursive(arr, pi + 1, high, stats);
    }
}

// 5. 快速排序
SortStats quickSort(vector<int>& arr) {
    SortStats stats;
    clock_t start = clock();
    
    quickSortRecursive(arr, 0, arr.size() - 1, stats);
    
    clock_t end = clock();
    stats.timeCost = double(end - start) / CLOCKS_PER_SEC;
    stats.sorted = isSorted(arr);
    return stats;
}

// 6. 简单选择排序
SortStats selectionSort(vector<int>& arr) {
    SortStats stats;
    clock_t start = clock();
    
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        
        for (int j = i + 1; j < n; j++) {
            stats.compareCount++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
            stats.moveCount += 3;
        }
    }
    
    clock_t end = clock();
    stats.timeCost = double(end - start) / CLOCKS_PER_SEC;
    stats.sorted = isSorted(arr);
    return stats;
}

// 7. 堆排序辅助函数：调整堆
void heapify(vector<int>& arr, int n, int i, SortStats& stats) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n) {
        stats.compareCount++;
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }
    
    if (right < n) {
        stats.compareCount++;
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        stats.moveCount += 3;
        heapify(arr, n, largest, stats);
    }
}

// 7. 堆排序
SortStats heapSort(vector<int>& arr) {
    SortStats stats;
    clock_t start = clock();
    
    int n = arr.size();
    
    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, stats);
    }
    
    // 逐个提取元素
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        stats.moveCount += 3;
        heapify(arr, i, 0, stats);
    }
    
    clock_t end = clock();
    stats.timeCost = double(end - start) / CLOCKS_PER_SEC;
    stats.sorted = isSorted(arr);
    return stats;
}

// 8. 归并排序辅助函数：合并
void merge(vector<int>& arr, int left, int mid, int right, SortStats& stats) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<int> L(n1), R(n2);
    
    // 复制数据到临时数组
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
        stats.moveCount++;
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        stats.moveCount++;
    }
    
    // 合并临时数组
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        stats.compareCount++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            stats.moveCount++;
            i++;
        } else {
            arr[k] = R[j];
            stats.moveCount++;
            j++;
        }
        k++;
    }
    
    // 复制剩余元素
    while (i < n1) {
        arr[k] = L[i];
        stats.moveCount++;
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        stats.moveCount++;
        j++;
        k++;
    }
}

// 归并排序递归函数
void mergeSortRecursive(vector<int>& arr, int left, int right, SortStats& stats) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSortRecursive(arr, left, mid, stats);
        mergeSortRecursive(arr, mid + 1, right, stats);
        merge(arr, left, mid, right, stats);
    }
}

// 8. 二路归并排序
SortStats mergeSort(vector<int>& arr) {
    SortStats stats;
    clock_t start = clock();
    
    mergeSortRecursive(arr, 0, arr.size() - 1, stats);
    
    clock_t end = clock();
    stats.timeCost = double(end - start) / CLOCKS_PER_SEC;
    stats.sorted = isSorted(arr);
    return stats;
}

// 9. 基数排序辅助函数：获取最大位数
int getMaxDigits(const vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    int digits = 0;
    
    while (maxVal > 0) {
        digits++;
        maxVal /= 10;
    }
    
    return digits;
}

// 9. 基数排序
SortStats radixSort(vector<int>& arr) {
    SortStats stats;
    clock_t start = clock();
    
    int n = arr.size();
    if (n == 0) {
        clock_t end = clock();
        stats.timeCost = double(end - start) / CLOCKS_PER_SEC;
        stats.sorted = true;
        return stats;
    }
    
    int maxDigits = getMaxDigits(arr);
    
    // 创建10个桶
    vector<queue<int>> buckets(10);
    
    // 从最低位到最高位进行排序
    for (int digit = 0; digit < maxDigits; digit++) {
        // 分配到桶中
        for (int i = 0; i < n; i++) {
            int num = arr[i];
            int divisor = 1;
            for (int d = 0; d < digit; d++) {
                divisor *= 10;
            }
            int bucketIndex = (num / divisor) % 10;
            buckets[bucketIndex].push(num);
            stats.moveCount++;
        }
        
        // 收集回数组
        int index = 0;
        for (int i = 0; i < 10; i++) {
            while (!buckets[i].empty()) {
                arr[index++] = buckets[i].front();
                buckets[i].pop();
                stats.moveCount++;
            }
        }
    }
    
    clock_t end = clock();
    stats.timeCost = double(end - start) / CLOCKS_PER_SEC;
    stats.sorted = isSorted(arr);
    return stats;
}

// ==================== 性能测试函数 ====================

// 生成随机数组
vector<int> generateRandomArray(int size, int minVal = 0, int maxVal = 10000) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(minVal, maxVal);
    
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    
    return arr;
}

// 生成有序数组
vector<int> generateSortedArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    return arr;
}

// 生成逆序数组
vector<int> generateReverseArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = size - i - 1;
    }
    return arr;
}

// 打印数组（小规模）
void printArray(const vector<int>& arr, int limit = 20) {
    int n = min((int)arr.size(), limit);
    cout << "数组前" << n << "个元素: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    if (arr.size() > limit) {
        cout << "... (共" << arr.size() << "个元素)";
    }
    cout << endl;
}

// 打印排序结果
void printSortStats(const string& algorithm, const SortStats& stats) {
    cout << left << setw(20) << algorithm;
    cout << right << setw(15) << stats.compareCount;
    cout << setw(15) << stats.moveCount;
    cout << fixed << setprecision(6) << setw(15) << stats.timeCost;
    cout << setw(10) << (stats.sorted ? "是" : "否");
    cout << endl;
}

// 测试单个算法
void testSingleAlgorithm(const string& algorithm, vector<int>& arr, 
                        SortStats (*sortFunc)(vector<int>&)) {
    vector<int> arrCopy = arr;
    SortStats stats = sortFunc(arrCopy);
    
    cout << "算法: " << algorithm << endl;
    cout << "原始数组: ";
    printArray(arr);
    cout << "排序后数组: ";
    printArray(arrCopy);
    
    cout << "统计信息:" << endl;
    cout << "比较次数: " << stats.compareCount << endl;
    cout << "移动次数: " << stats.moveCount << endl;
    cout << "时间(秒): " << fixed << setprecision(6) << stats.timeCost << endl;
    cout << "是否排序成功: " << (stats.sorted ? "是" : "否") << endl;
    
    // 验证是否为堆序列（如果是堆排序）
    if (algorithm == "堆排序") {
        cout << "是否为堆序列: " << (isHeap(arrCopy) ? "是" : "否") << endl;
    }
    
    cout << "------------------------" << endl;
}

// 批量测试所有算法
void testAllAlgorithms(int size, const string& dataType = "随机") {
    cout << "\n========== 测试规模: " << size << " (" << dataType << "数据) ==========" << endl;
    
    // 生成测试数据
    vector<int> arr;
    if (dataType == "随机") {
        arr = generateRandomArray(size);
    } else if (dataType == "有序") {
        arr = generateSortedArray(size);
    } else if (dataType == "逆序") {
        arr = generateReverseArray(size);
    }
    
    // 测试算法列表
    vector<pair<string, SortStats (*)(vector<int>&)>> algorithms = {
        {"直接插入排序", insertionSort},
        {"折半插入排序", binaryInsertionSort},
        {"希尔排序", shellSort},
        {"冒泡排序", bubbleSort},
        {"快速排序", quickSort},
        {"简单选择排序", selectionSort},
        {"堆排序", heapSort},
        {"二路归并排序", mergeSort},
        {"基数排序", radixSort}
    };
    
    // 打印表头
    cout << left << setw(20) << "算法";
    cout << right << setw(15) << "比较次数";
    cout << setw(15) << "移动次数";
    cout << setw(15) << "时间(秒)";
    cout << setw(10) << "排序成功";
    cout << endl;
    cout << string(75, '-') << endl;
    
    // 测试每个算法
    for (auto& algo : algorithms) {
        vector<int> arrCopy = arr;
        SortStats stats = algo.second(arrCopy);
        printSortStats(algo.first, stats);
    }
}

// ==================== 主菜单 ====================
void mainMenu() {
    int choice;
    
    while (true) {
        cout << "\n========== 内排序算法系统 ==========";
        cout << "\n1. 测试单个算法（小规模，20个元素）";
        cout << "\n2. 批量测试所有算法（中规模，2000个元素）";
        cout << "\n3. 批量测试所有算法（大规模，200000个元素）";
        cout << "\n4. 测试不同数据分布";
        cout << "\n5. 算法性能对比分析";
        cout << "\n0. 退出";
        cout << "\n选择: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                // 测试单个算法（小规模）
                cout << "\n生成20个随机数进行测试..." << endl;
                vector<int> arr = generateRandomArray(20);
                
                cout << "\n选择要测试的算法:";
                cout << "\n1. 直接插入排序";
                cout << "\n2. 折半插入排序";
                cout << "\n3. 希尔排序";
                cout << "\n4. 冒泡排序";
                cout << "\n5. 快速排序";
                cout << "\n6. 简单选择排序";
                cout << "\n7. 堆排序";
                cout << "\n8. 二路归并排序";
                cout << "\n9. 基数排序";
                cout << "\n选择: ";
                
                int algoChoice;
                cin >> algoChoice;
                
                vector<pair<string, SortStats (*)(vector<int>&)>> algorithms = {
                    {"直接插入排序", insertionSort},
                    {"折半插入排序", binaryInsertionSort},
                    {"希尔排序", shellSort},
                    {"冒泡排序", bubbleSort},
                    {"快速排序", quickSort},
                    {"简单选择排序", selectionSort},
                    {"堆排序", heapSort},
                    {"二路归并排序", mergeSort},
                    {"基数排序", radixSort}
                };
                
                if (algoChoice >= 1 && algoChoice <= 9) {
                    testSingleAlgorithm(algorithms[algoChoice-1].first, arr, 
                                      algorithms[algoChoice-1].second);
                } else {
                    cout << "无效选择" << endl;
                }
                break;
            }
                
            case 2: {
                // 中规模测试
                testAllAlgorithms(2000, "随机");
                break;
            }
                
            case 3: {
                // 大规模测试
                testAllAlgorithms(200000, "随机");
                break;
            }
                
            case 4: {
                // 测试不同数据分布
                cout << "\n测试不同数据分布下的性能..." << endl;
                
                cout << "\n1. 随机数据" << endl;
                testAllAlgorithms(1000, "随机");
                
                cout << "\n2. 有序数据" << endl;
                testAllAlgorithms(1000, "有序");
                
                cout << "\n3. 逆序数据" << endl;
                testAllAlgorithms(1000, "逆序");
                break;
            }
                
            case 5: {
                // 性能对比分析
                cout << "\n========== 排序算法性能分析 ==========" << endl;
                cout << "\n1. 时间复杂度对比:" << endl;
                cout << "   直接插入排序: O(n²) 最好O(n)" << endl;
                cout << "   折半插入排序: O(n²) 比较次数减少" << endl;
                cout << "   希尔排序: O(n¹·³)" << endl;
                cout << "   冒泡排序: O(n²)" << endl;
                cout << "   快速排序: O(nlogn) 平均, O(n²) 最坏" << endl;
                cout << "   简单选择排序: O(n²)" << endl;
                cout << "   堆排序: O(nlogn)" << endl;
                cout << "   二路归并排序: O(nlogn)" << endl;
                cout << "   基数排序: O(d*(n+k)), d为位数, k为基数" << endl;
                
                cout << "\n2. 空间复杂度对比:" << endl;
                cout << "   直接插入排序: O(1)" << endl;
                cout << "   折半插入排序: O(1)" << endl;
                cout << "   希尔排序: O(1)" << endl;
                cout << "   冒泡排序: O(1)" << endl;
                cout << "   快速排序: O(logn) 递归栈" << endl;
                cout << "   简单选择排序: O(1)" << endl;
                cout << "   堆排序: O(1)" << endl;
                cout << "   二路归并排序: O(n)" << endl;
                cout << "   基数排序: O(n+k)" << endl;
                
                cout << "\n3. 稳定性对比:" << endl;
                cout << "   稳定: 直接插入、折半插入、冒泡、归并、基数" << endl;
                cout << "   不稳定: 希尔、快速、选择、堆" << endl;
                
                cout << "\n4. 适用场景:" << endl;
                cout << "   小规模数据: 直接插入、冒泡" << endl;
                cout << "   中等规模: 希尔、快速、堆排序" << endl;
                cout << "   大规模: 快速、堆、归并" << endl;
                cout << "   整数排序: 基数排序" << endl;
                cout << "   链表排序: 归并排序" << endl;
                break;
            }
        }
    }
}

int main() {
    mainMenu();
    return 0;
}