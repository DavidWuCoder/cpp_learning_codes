//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//using namespace std;
//
//template<class T>
//class SmartPtr
//{
//public:
//	// RAII
//	SmartPtr(T* ptr)
//		:_ptr(ptr)
//	{}
//	~SmartPtr()
//	{
//		cout << "delete[] " << _ptr << endl;
//		delete[] _ptr;
//	}
//private:
//	T* _ptr;
//};
//
//double Divide(int a, int b)
//{
//	// 当b == 0时抛出异常
//	if (b == 0)
//	{
//		throw "Divide by zero condition!";
//	}
//	else
//	{
//		return (double)a / (double)b;
//	}
//}
//void Func()
//{
//	// 这⾥可以看到如果发⽣除0错误抛出异常，另外下⾯的array和array2没有得到释放。
//	// 所以这⾥捕获异常后并不处理异常，异常还是交给外⾯处理，这⾥捕获了再重新抛出去。
//	// 但是如果array2new的时候抛异常呢，就还需要套⼀层捕获释放逻辑，这⾥更好解决⽅案
//	// 是智能指针，否则代码太戳了
//	SmartPtr<int> array1 = new int[10];
//	SmartPtr<int> array2 = new int[10]; // 抛异常呢
//
//	int len, time;
//	cin >> len >> time;
//	cout << Divide(len, time) << endl;
//}
//int main()
//{
//	try
//	{
//		Func();
//	}
//	catch (const char* errmsg)
//	{
//		cout << errmsg << endl;
//	}
//	catch (const exception& e)
//	{
//		cout << e.what() << endl;
//	}
//	catch (...)
//	{
//		cout << "未知异常" << endl;
//	}
//	return 0;
//}
//
//
//

#include <iostream>
#include <memory>
using namespace std;

struct Date
{
	int _year;
	int _month;
	int _day;
	Date(int year = 1, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{}
	~Date()
	{
		cout << "~Date()" << endl;
	}
};
//int main()
//{
//	auto_ptr<Date> ap1(new Date);
//	// 拷⻉时，管理权限转移，被拷⻉对象ap1悬空
//	auto_ptr<Date> ap2(ap1);
//	
//	unique_ptr<Date> up1(new Date);
//
//	shared_ptr<Date> sp1(new Date);
//	// ⽀持拷⻉
//	shared_ptr<Date> sp2(sp1);
//	shared_ptr<Date> sp3(sp2);
//	cout << sp1.use_count() << endl;
//	sp1->_year++;
//	cout << sp1->_year << endl;
//	cout << sp2->_year << endl;
//	cout << sp3->_year << endl;
//
//	return 0;
//}
template<class T>
void DeleteArrayFunc(T* ptr)
{
	delete[] ptr;
}
template<class T>
class DeleteArray
{
public:
	void operator()(T* ptr)
	{
		delete[] ptr;
	}
};

class Fclose
{
public:
	void operator()(FILE* ptr)
	{
		cout << "fclose:" << ptr << endl;
		fclose(ptr);
	}
};

//int main()
//{
//	/*unique_ptr<Date> up1(new Date[10]);
//	shared_ptr<Date> sp1(new Date[10]);*/
//
//	unique_ptr<Date, DeleteArray<Date>> up2(new Date[5]);
//	shared_ptr<Date> sp2(new Date[5], DeleteArray<Date>());
//
//	return 0;
//}

//int main()
//{
//	shared_ptr<Date> sp1(new Date(2025, 3, 15));
//	shared_ptr<Date> sp2 = make_shared<Date>(2025, 3, 15);
//	auto sp3 = make_shared<Date>(2025, 3, 15);
//	shared_ptr<Date> sp4;
//
//	if (!sp4)
//	{
//		std::cout << "sp4 is nullptr!" << std::endl;
//	}
//
//	return 0;
//
// }

#include "shared_ptr.h"


void del(Date* ptr)
{
	delete[] ptr;
}

//int main()
//{
//	//wyl::shared_ptr<Date> sp1(new Date(2024, 9, 11));
//	//wyl::shared_ptr<Date> sp2(sp1);
//
//	//wyl::shared_ptr<Date> sp3(new Date(2025, 9, 11));
//
//	//sp1 = sp3;
//
//	//wyl::shared_ptr<Date> sp4;
//
//	//if (!sp4)
//	//{
//	//	std::cout << "sp1 is not empty" << std::endl;
//	//}
//
//	//wyl::shared_ptr<Date> sp5(new Date[10], [](Date* ptr) {delete[] ptr; });
//	wyl::shared_ptr<Date> sp5(new Date[10], del);
//	return 0;
//}

struct ListNode
{
	int _data;
/*	std::shared_ptr<ListNode> _next;
	std::shared_ptr<ListNode> _prev*/;
	// 这⾥改成weak_ptr，当n1->_next = n2;绑定shared_ptr时
	// 不增加n2的引⽤计数，不参与资源释放的管理，就不会形成循环引⽤了
	std::weak_ptr<ListNode> _next;
	std::weak_ptr<ListNode> _prev;
	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
};
int main()
{
	// 循环引⽤ -- 内存泄露
	std::shared_ptr<ListNode> n1(new ListNode);
	std::shared_ptr<ListNode> n2(new ListNode);

	n2->_next = n1;
	n1->_prev = n2;


	std::cout << n1.use_count() << std::endl;
	std::cout << n2.use_count() << std::endl;
	return 0;
}