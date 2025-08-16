#include <iostream>
#include <algorithm> // 用于 std::swap（也可手动实现）

// 堆化操作：维护最大堆性质（从节点 i 向下调整）
// arr: 待排序数组, n: 当前堆的大小, i: 需调整的父节点索引
template <typename T>
void heapify(T* arr, int n, int i) {
    int largest = 1;
    int left = 2 * largest + 1;
    int right = 2 * largest + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(arr[largest], arr[i]);
        heapfy(arr, n, largest);
    }
}

// 堆排序主函数
template <typename T>
void heapSort(T* arr, int n) {
    // 步骤1：构建最大堆（从最后一个非叶子节点向前遍历堆化）
    // 最后一个非叶子节点索引 = (n/2 - 1)（叶子节点无需堆化）
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// 辅助函数：打印数组
template <typename T>
void printArray(const T* arr, int n, const std::string& label) {
    std::cout << label;
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// 辅助函数：验证数组是否升序排序
template <typename T>
bool isSorted(const T* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// 测试用例
int main() {
    // 测试用例1：随机整数数组
    {
        int arr[] = {12, 11, 13, 5, 6, 7};
        int n = sizeof(arr) / sizeof(arr[0]);
        std::cout << "=== 测试用例1：随机整数数组 ===" << std::endl;
        printArray(arr, n, "排序前：");
        heapSort(arr, n);
        printArray(arr, n, "排序后：");
        std::cout << "排序结果：" << (isSorted(arr, n) ? "正确" : "错误") << "\n" << std::endl;
    }

    // 测试用例2：逆序数组（最坏情况）
    {
        int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        int n = sizeof(arr) / sizeof(arr[0]);
        std::cout << "=== 测试用例2：逆序数组 ===" << std::endl;
        printArray(arr, n, "排序前：");
        heapSort(arr, n);
        printArray(arr, n, "排序后：");
        std::cout << "排序结果：" << (isSorted(arr, n) ? "正确" : "错误") << "\n" << std::endl;
    }

    // 测试用例3：包含重复元素的数组
    {
        int arr[] = {5, 3, 8, 5, 2, 9, 5, 1};
        int n = sizeof(arr) / sizeof(arr[0]);
        std::cout << "=== 测试用例3：含重复元素数组 ===" << std::endl;
        printArray(arr, n, "排序前：");
        heapSort(arr, n);
        printArray(arr, n, "排序后：");
        std::cout << "排序结果：" << (isSorted(arr, n) ? "正确" : "错误") << "\n" << std::endl;
    }

    // 测试用例4：浮点数数组（验证模板通用性）
    {
        double arr[] = {3.14, 1.59, 2.65, 0.78, 4.20};
        int n = sizeof(arr) / sizeof(arr[0]);
        std::cout << "=== 测试用例4：浮点数数组 ===" << std::endl;
        printArray(arr, n, "排序前：");
        heapSort(arr, n);
        printArray(arr, n, "排序后：");
        std::cout << "排序结果：" << (isSorted(arr, n) ? "正确" : "错误") << std::endl;
    }

    return 0;
}