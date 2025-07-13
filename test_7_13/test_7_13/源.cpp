#include <iostream>
template<typename T>
class UniquePtr {
private:
    T* ptr;  // 管理的原始指针

public:
    // 构造函数
    explicit UniquePtr(T* p = nullptr) noexcept : ptr(p) {}

    // 禁止拷贝构造
    UniquePtr(const UniquePtr&) = delete;

    // 移动构造函数
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;  // 释放原指针的所有权
    }

    // 禁止拷贝赋值
    UniquePtr& operator=(const UniquePtr&) = delete;

    // 移动赋值运算符
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;       // 释放当前管理的资源
            ptr = other.ptr;  // 转移所有权
            other.ptr = nullptr;
        }
        return *this;
    }

    // 析构函数
    ~UniquePtr() noexcept {
        delete ptr;
    }

    // 解引用运算符
    T& operator*() const noexcept {
        return *ptr;
    }

    // 箭头运算符
    T* operator->() const noexcept {
        return ptr;
    }

    // 获取原始指针
    T* get() const noexcept {
        return ptr;
    }

    // 释放所有权
    T* release() noexcept {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // 重置指针
    void reset(T* p = nullptr) noexcept {
        if (ptr != p) {
            delete ptr;
            ptr = p;
        }
    }

    // 转换为布尔值
    explicit operator bool() const noexcept {
        return ptr != nullptr;
    }
};

int main() {
    // 创建 UniquePtr
    UniquePtr<int> ptr(new int(42));

    // 访问对象
    std::cout << *ptr << std::endl;  // 输出: 42

    // 移动所有权
    UniquePtr<int> ptr2 = std::move(ptr);  // ptr 变为空

    // 重置指针
    ptr2.reset(new int(100));

    //// 释放所有权
    //int* raw = ptr2.release();
    //delete raw;  // 需要手动释放
    return 0;
}