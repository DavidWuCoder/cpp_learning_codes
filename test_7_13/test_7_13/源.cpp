#include <iostream>
template<typename T>
class UniquePtr {
private:
    T* ptr;  // �����ԭʼָ��

public:
    // ���캯��
    explicit UniquePtr(T* p = nullptr) noexcept : ptr(p) {}

    // ��ֹ��������
    UniquePtr(const UniquePtr&) = delete;

    // �ƶ����캯��
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;  // �ͷ�ԭָ�������Ȩ
    }

    // ��ֹ������ֵ
    UniquePtr& operator=(const UniquePtr&) = delete;

    // �ƶ���ֵ�����
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;       // �ͷŵ�ǰ�������Դ
            ptr = other.ptr;  // ת������Ȩ
            other.ptr = nullptr;
        }
        return *this;
    }

    // ��������
    ~UniquePtr() noexcept {
        delete ptr;
    }

    // �����������
    T& operator*() const noexcept {
        return *ptr;
    }

    // ��ͷ�����
    T* operator->() const noexcept {
        return ptr;
    }

    // ��ȡԭʼָ��
    T* get() const noexcept {
        return ptr;
    }

    // �ͷ�����Ȩ
    T* release() noexcept {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // ����ָ��
    void reset(T* p = nullptr) noexcept {
        if (ptr != p) {
            delete ptr;
            ptr = p;
        }
    }

    // ת��Ϊ����ֵ
    explicit operator bool() const noexcept {
        return ptr != nullptr;
    }
};

int main() {
    // ���� UniquePtr
    UniquePtr<int> ptr(new int(42));

    // ���ʶ���
    std::cout << *ptr << std::endl;  // ���: 42

    // �ƶ�����Ȩ
    UniquePtr<int> ptr2 = std::move(ptr);  // ptr ��Ϊ��

    // ����ָ��
    ptr2.reset(new int(100));

    //// �ͷ�����Ȩ
    //int* raw = ptr2.release();
    //delete raw;  // ��Ҫ�ֶ��ͷ�
    return 0;
}