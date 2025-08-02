#include <iostream>
#include <cassert>

// 前置声明
template<typename T>
class weak_ptr;

// 控制块：管理引用计数
template<typename T>
struct ControlBlock {
    T* object;               // 指向管理的对象
    size_t shared_count;     // 共享引用计数（被shared_ptr使用）
    size_t weak_count;       // 弱引用计数（被weak_ptr使用）

    ControlBlock(T* obj) : object(obj), shared_count(1), weak_count(0) {}

    ~ControlBlock() {
        delete object;       // 最后销毁对象
        object = nullptr;
    }
};

// 模拟shared_ptr（与weak_ptr配合使用）
template<typename T>
class shared_ptr {
private:
    T* object;               // 指向对象
    ControlBlock<T>* cb;     // 指向控制块

    // 释放当前持有资源
    void release() {
        if (cb) {
            cb->shared_count--;
            // 共享计数为0时，检查是否需要销毁控制块
            if (cb->shared_count == 0) {
                // 弱引用计数为0时才销毁控制块
                if (cb->weak_count == 0) {
                    delete cb;
                } else {
                    // 仅销毁对象，保留控制块供weak_ptr查询
                    cb->object = nullptr;
                }
            }
            cb = nullptr;
            object = nullptr;
        }
    }

public:
    // 构造函数
    explicit shared_ptr(T* ptr = nullptr) : object(ptr) {
        if (ptr) {
            cb = new ControlBlock<T>(ptr);
        } else {
            cb = nullptr;
        }
    }

    // 拷贝构造
    shared_ptr(const shared_ptr& other) : object(other.object), cb(other.cb) {
        if (cb) {
            cb->shared_count++;
        }
    }

    // 从weak_ptr构造（lock()功能）
    shared_ptr(const weak_ptr<T>& wp) {
        if (wp.expired()) {
            object = nullptr;
            cb = nullptr;
        } else {
            object = wp.object;
            cb = wp.cb;
            if (cb) {
                cb->shared_count++;
            }
        }
    }

    // 析构函数
    ~shared_ptr() {
        release();
    }

    // 拷贝赋值
    shared_ptr& operator=(const shared_ptr& other) {
        if (this != &other) {
            release();
            object = other.object;
            cb = other.cb;
            if (cb) {
                cb->shared_count++;
            }
        }
        return *this;
    }

    // 重置指针
    void reset() {
        release();
    }

    // 重载*运算符
    T& operator*() const {
        assert(object != nullptr);
        return *object;
    }

    // 重载->运算符
    T* operator->() const {
        assert(object != nullptr);
        return object;
    }

    // 重载bool转换，用于判断是否为空
    operator bool() const {
        return object != nullptr;
    }

    // 获取共享引用计数
    size_t use_count() const {
        return cb ? cb->shared_count : 0;
    }

    // 友元声明：允许weak_ptr访问私有成员
    friend class weak_ptr<T>;
};

// 模拟weak_ptr
template<typename T>
class weak_ptr {
private:
    T* object;               // 指向对象（可能已失效）
    ControlBlock<T>* cb;     // 指向控制块

    // 释放弱引用
    void release() {
        if (cb) {
            cb->weak_count--;
            // 弱引用和共享引用都为0时，销毁控制块
            if (cb->weak_count == 0 && cb->shared_count == 0) {
                delete cb;
            }
            cb = nullptr;
            object = nullptr;
        }
    }

public:
    // 默认构造
    weak_ptr() : object(nullptr), cb(nullptr) {}

    // 从shared_ptr构造
    weak_ptr(const shared_ptr<T>& sp) : object(sp.object), cb(sp.cb) {
        if (cb) {
            cb->weak_count++;
        }
    }

    // 拷贝构造
    weak_ptr(const weak_ptr& other) : object(other.object), cb(other.cb) {
        if (cb) {
            cb->weak_count++;
        }
    }

    // 析构函数
    ~weak_ptr() {
        release();
    }

    // 拷贝赋值
    weak_ptr& operator=(const weak_ptr& other) {
        if (this != &other) {
            release();
            object = other.object;
            cb = other.cb;
            if (cb) {
                cb->weak_count++;
            }
        }
        return *this;
    }

    // 从shared_ptr赋值
    weak_ptr& operator=(const shared_ptr<T>& sp) {
        release();
        object = sp.object;
        cb = sp.cb;
        if (cb) {
            cb->weak_count++;
        }
        return *this;
    }

    // 检查对象是否已被销毁（过期）
    bool expired() const {
        // 共享计数为0表示对象已销毁
        return cb == nullptr || cb->shared_count == 0;
    }

    // 获取对应的shared_ptr（如果对象还存活）
    shared_ptr<T> lock() const {
        return shared_ptr<T>(*this);
    }

    // 获取弱引用计数
    size_t use_count() const {
        return cb ? cb->shared_count : 0;
    }

    // 友元声明
    friend class shared_ptr<T>;
};

// 测试代码
int main() {
    // 测试1：基本功能测试
    {
        shared_ptr<int> sp(new int(100));
        weak_ptr<int> wp(sp);

        std::cout << "测试1：基本功能" << std::endl;
        std::cout << "shared_ptr引用计数: " << sp.use_count() << std::endl;  // 应输出1
        std::cout << "weak_ptr观察到的引用计数: " << wp.use_count() << std::endl;  // 应输出1
        std::cout << "对象是否存活: " << (wp.expired() ? "已销毁" : "存活中") << std::endl;  // 应输出存活中

        // 通过weak_ptr获取shared_ptr
        shared_ptr<int> sp2 = wp.lock();
        std::cout << "通过lock()获取的引用计数: " << sp2.use_count() << std::endl;  // 应输出2

        // 销毁原始shared_ptr
        sp.reset();
        std::cout << "销毁sp后，sp2的引用计数: " << sp2.use_count() << std::endl;  // 应输出1
        std::cout << "对象是否存活: " << (wp.expired() ? "已销毁" : "存活中") << std::endl;  // 应输出存活中
    }

    // 测试2：对象销毁后weak_ptr的状态
    {
        weak_ptr<int> wp;
        {
            shared_ptr<int> sp(new int(200));
            wp = sp;
            std::cout << "\n测试2：对象销毁后状态" << std::endl;
            std::cout << "作用域内，对象是否存活: " << (wp.expired() ? "已销毁" : "存活中") << std::endl;  // 存活中
        }
        std::cout << "作用域外，对象是否存活: " << (wp.expired() ? "已销毁" : "存活中") << std::endl;  // 已销毁
        std::cout << "对象销毁后lock()的结果: " << (wp.lock() ? "非空" : "空") << std::endl;  // 空
    }

    // 测试3：循环引用问题解决
    struct Node {
        int value;
        weak_ptr<Node> next;  // 使用weak_ptr打破循环引用
        Node(int v) : value(v) {}
        ~Node() {
            std::cout << "\nNode被销毁，值为: " << value << std::endl;
        }
    };

    {
        std::cout << "\n测试3：解决循环引用" << std::endl;
        shared_ptr<Node> node1(new Node(1));
        shared_ptr<Node> node2(new Node(2));

        node1->next = node2;  // weak_ptr赋值，不增加引用计数
        node2->next = node1;  // weak_ptr赋值，不增加引用计数

        std::cout << "node1引用计数: " << node1.use_count() << std::endl;  // 1
        std::cout << "node2引用计数: " << node2.use_count() << std::endl;  // 1
    }  // 离开作用域时，node1和node2的引用计数都减为0，对象被销毁

    return 0;
}
