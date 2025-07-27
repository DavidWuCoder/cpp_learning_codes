#include "shared_ptr.hpp"  // 假设你的MySharedPtr定义在这个头文件中
#include <thread>
#include <vector>
#include <chrono>
#include <iostream>

void test_my_shared_ptr_thread_safety() {
    MySharedPtr<int> ptr(new int(42));

    // 创建多个线程，每个线程都进行拷贝构造操作来增减引用计数
    const int num_threads = 10;
    const int loop_count = 1000;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&ptr]() {
            for (int j = 0; j < loop_count; ++j) {
                MySharedPtr<int> local_ptr(ptr);  // 拷贝构造，增加引用计数
                // 短暂暂停，增加线程切换的可能性
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            // local_ptr 析构，减少引用计数
        });
    }

    // 等待所有线程完成
    for (auto& thread : threads) {
        thread.join();
    }

    // 检查引用计数是否正确
    std::cout << "use count: " << ptr.use_count() << std::endl;
    if (ptr.use_count() == 1) {
        std::cout << "Test passed: MySharedPtr is thread-safe!" << std::endl;
    } else {
        std::cout << "Test failed: MySharedPtr is not thread-safe!" << std::endl;
    }
}

int main() {
    test_my_shared_ptr_thread_safety();
    return 0;
}