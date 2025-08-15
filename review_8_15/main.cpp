#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

// 插入排序：适用于小数组
template <typename T>
void insertionSort(T* arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        T key = arr[i];
        int j = i - 1;

        // 将大于key的元素向右移动
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 堆排序辅助函数：维护堆性质
template <typename T>
void heapify(T* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// 堆排序
template <typename T>
void heapSort(T* arr, int left, int right) {
    int n = right - left + 1;
    T* start = arr + left;

    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(start, n, i);

    // 提取元素
    for (int i = n - 1; i >= 0; --i) {
        std::swap(start[0], start[i]);
        heapify(start, i, 0);
    }
}

// 快速排序分区操作
template <typename T>
int partition(T* arr, int left, int right) {
    // 选择最右元素作为 pivot
    T pivot = arr[right];
    int i = left - 1;

    for (int j = left; j <= right - 1; ++j) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[right]);
    return i + 1;
}

// 自省排序递归函数
template <typename T>
void introsortUtil(T* arr, int left, int right, int depthLimit) {
    const int INSERTION_SORT_THRESHOLD = 16;  // 插入排序阈值
    int n = right - left + 1;

    // 当数组大小小于阈值时，使用插入排序
    if (n <= INSERTION_SORT_THRESHOLD) {
        insertionSort(arr, left, right);
        return;
    }

    // 当递归深度超过阈值时，使用堆排序
    if (depthLimit == 0) {
        heapSort(arr, left, right);
        return;
    }

    // 否则使用快速排序
    int p = partition(arr, left, right);
    introsortUtil(arr, left, p - 1, depthLimit - 1);
    introsortUtil(arr, p + 1, right, depthLimit - 1);
}

// 自省排序主函数
template <typename T>
void introsort(T* arr, int n) {
    if (n <= 1) return;

    // 计算最大递归深度：2 * log2(n)
    int depthLimit = 2 * static_cast<int>(log2(n));
    introsortUtil(arr, 0, n - 1, depthLimit);
}

// 打印数组
template <typename T>
void printArray(const T* arr, int n, const std::string& label) {
    std::cout << label;
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// 检查数组是否已排序
template <typename T>
bool isSorted(const T* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    // 设置随机数种子
    srand(time(0));

    // 测试用例1：随机整数数组
    {
        const int n = 20;
        int arr[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = rand() % 100;
        }

        std::cout << "=== 测试用例1：随机整数数组 ===" << std::endl;
        printArray(arr, n, "排序前：");

        introsort(arr, n);

        printArray(arr, n, "排序后：");
        std::cout << "排序结果" << (isSorted(arr, n) ? "正确" : "错误") << std::endl << std::endl;
    }

    // 测试用例2：小数组（触发插入排序）
    {
        const int n = 10;
        int arr[n] = {5, 2, 9, 1, 5, 6, 3, 8, 7, 4};

        std::cout << "=== 测试用例2：小数组（触发插入排序） ===" << std::endl;
        printArray(arr, n, "排序前：");

        introsort(arr, n);

        printArray(arr, n, "排序后：");
        std::cout << "排序结果" << (isSorted(arr, n) ? "正确" : "错误") << std::endl << std::endl;
    }

    // 测试用例3：已排序数组
    {
        const int n = 15;
        int arr[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = i;
        }

        std::cout << "=== 测试用例3：已排序数组 ===" << std::endl;
        printArray(arr, n, "排序前：");

        introsort(arr, n);

        printArray(arr, n, "排序后：");
        std::cout << "排序结果" << (isSorted(arr, n) ? "正确" : "错误") << std::endl << std::endl;
    }

    // 测试用例4：逆序数组
    {
        const int n = 30;
        int arr[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = n - i - 1;
        }

        std::cout << "=== 测试用例4：逆序数组 ===" << std::endl;
        printArray(arr, n, "排序前：");

        introsort(arr, n);

        printArray(arr, n, "排序后：");
        std::cout << "排序结果" << (isSorted(arr, n) ? "正确" : "错误") << std::endl << std::endl;
    }

    // 测试用例5：包含重复元素的数组
    {
        const int n = 25;
        int arr[n] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3};

        std::cout << "=== 测试用例5：包含重复元素的数组 ===" << std::endl;
        printArray(arr, n, "排序前：");

        introsort(arr, n);

        printArray(arr, n, "排序后：");
        std::cout << "排序结果" << (isSorted(arr, n) ? "正确" : "错误") << std::endl << std::endl;
    }

    // 测试用例6：浮点数数组
    {
        const int n = 18;
        double arr[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = (rand() % 1000) / 10.0 - 50.0;  // 范围在-50到50之间
        }

        std::cout << "=== 测试用例6：浮点数数组 ===" << std::endl;
        printArray(arr, n, "排序前：");

        introsort(arr, n);

        printArray(arr, n, "排序后：");
        std::cout << "排序结果" << (isSorted(arr, n) ? "正确" : "错误") << std::endl;
    }

    return 0;
}
