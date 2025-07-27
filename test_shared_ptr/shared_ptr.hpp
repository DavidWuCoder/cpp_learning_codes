//
// Created by 46858 on 25-7-23.
//

#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <atomic>
#include <cassert>
#include <utility>

template <typename T>
class MySharedPtr {
public:
    // a. 构造函数（空指针）
    MySharedPtr() noexcept
        : ptr(nullptr), refCount(nullptr) {}

    // a. 有参构造函数（ explicit 修饰，禁止隐式转换 ）
    explicit MySharedPtr(T* rawPtr)
        : ptr(rawPtr) {
        refCount = new std::atomic<size_t>(1);
    }

    // b. 析构函数
    ~MySharedPtr() {
        if (refCount && --(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }

    // c. 拷贝构造函数（ const 引用入参 ）
    MySharedPtr(const MySharedPtr& other)
        : ptr(other.ptr), refCount(other.refCount) {
        if (refCount) {
            (*refCount)++;
        }
    }

    // d. 拷贝赋值运算符（ const 引用入参 ）
    MySharedPtr& operator=(const MySharedPtr& other) {
        if (this != &other) {
            // 释放当前对象引用计数、资源
            if (refCount && --(*refCount) == 0) {
                delete ptr;
                delete refCount;
            }
            // 接管新对象资源
            ptr = other.ptr;
            refCount = other.refCount;
            if (refCount) {
                (*refCount)++;
            }
        }
        return *this;
    }

    // e. 移动构造函数（ noexcept 修饰 ）
    MySharedPtr(MySharedPtr&& other) noexcept
        : ptr(other.ptr), refCount(other.refCount) {
        other.ptr = nullptr;
        other.refCount = nullptr;
    }

    // f. 移动赋值运算符（ noexcept 修饰 ）
    MySharedPtr& operator=(MySharedPtr&& other) noexcept {
        if (this != &other) {
            // 释放当前对象引用计数、资源
            if (refCount && --(*refCount) == 0) {
                delete ptr;
                delete refCount;
            }
            // 接管资源
            ptr = other.ptr;
            refCount = other.refCount;
            // 置空源对象
            other.ptr = nullptr;
            other.refCount = nullptr;
        }
        return *this;
    }

    // g. 解引用、箭头运算符
    T& operator*() const {
        assert(ptr != nullptr);
        return *ptr;
    }

    T* operator->() const {
        assert(ptr != nullptr);
        return ptr;
    }

    // h. 引用计数、原始指针、重置指针
    size_t use_count() const {
        if (refCount) {
            return *refCount;
        }
        return 0;
    }

    T* get() const {
        return ptr;
    }

    void reset(T* newPtr = nullptr) {
        // 释放当前对象引用计数、资源
        if (refCount && --(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
        // 重置为新指针（若传参非空则创建新引用计数）
        ptr = newPtr;
        if (newPtr) {
            refCount = new std::atomic<size_t>(1);
        } else {
            refCount = nullptr;
        }
    }

private:
    T* ptr;
    std::atomic<size_t>* refCount;
};

#endif //SHARED_PTR_HPP



