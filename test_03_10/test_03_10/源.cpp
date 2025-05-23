﻿//#include <iostream>
//#include <vector>
//#include <map>
//
//int main()
//{
//	auto il1 = { 1, 2, 3, 4, 5 };
//	std::cout << typeid(il1).name() << std::endl;
//	return 0;
//}


//#include <iostream>
//using namespace std;
//
//int main()
//{
//	int* p = new int(0);
//	int b = 1;
//	const int c = b;
//	*p = 10;
//	string s("111111");
//	s[0] = 'x';
//	cout << &c << endl;
//	cout << (void*)&s[0] << endl;
//
//	double x = 1.1, y = 2.2;
//	// 以下⼏个10、x + y、fmin(x, y)、string("11111")都是常⻅的右值
//	10;
//	x + y;
//	fmin(x, y);
//	string("11111");
//
//	// cout << &10 << endl;
//	// cout << &(x+y) << endl;
//	// cout << &(fmin(x, y)) << endl;
//	// cout << &string("11111") << endl;
//
//	int b = 10;
//
//	int&& rr1 = 10;
//	double&& rr2 = x + y;
//	string&& rr3 = ("11111");
//
//	const double& r2 = 1.1;
//
//	int&& rr4 = move(b);
//
//
//	return 0;
//}


//class AA
//{
//public:
//	AA(int a1, int a2)
//		: _a1(1), _a2(a2)
//	{}
//
//	~AA()
//	{
//		std::cout << "~AA()" << std::endl;
//	}
//
//private:
//	int _a1 = 1;
//	int _a2 = 2;
//};
//
//int main()
//{
//	AA aa1(1, 1);
//	const AA& r1 = AA(2, 2);
//	AA&& r2 = AA(2, 2);
//
//	std::cout << "---------------" << std::endl;
//	return 0;
//}

//void f(int& x)
//{
//	std::cout << "左值引⽤重载 f(" << x << ")\n";
//}
//void f(const int& x)
//{
//	std::cout << "到 const 的左值引⽤重载 f(" << x << ")\n";
//}
//void f(int&& x)
//{
//	std::cout << "右值引⽤重载 f(" << x << ")\n";
//}
//
////int main()
////{
////	int i = 1;
////	const int ci = 2;
////	f(i); // 调⽤ f(int&)
////	f(ci); // 调⽤ f(const int&)
////	f(3 + 1); // 调⽤ f(int&&)，如果没有 f(int&&) 重载则会调⽤ f(const int&)
////	f(std::move(i)); // 调⽤ f(int&&)
////	// 右值引⽤变量在⽤于表达式时是左值
////	const int&& x = 1;
////	f(x); // 调⽤ f(int& x)
////	f(std::move(x)); // 调⽤ f(int&& x)
////	return 0;
////}
//
//using namespace std;
//
//class Solution {
//public:
//	// 传值返回需要拷⻉
//	string addStrings(string num1, string num2) {
//		string str;
//		int end1 = num1.size() - 1, end2 = num2.size() - 1;
//		// 进位
//		int next = 0;
//		while (end1 >= 0 || end2 >= 0)
//		{
//			int val1 = end1 >= 0 ? num1[end1--] - '0' : 0;
//			int val2 = end2 >= 0 ? num2[end2--] - '0' : 0;
//			int ret = val1 + val2 + next;
//			next = ret / 10;
//			ret = ret % 10;
//			str += ('0' + ret);
//		}
//		if (next == 1)
//			str += '1';
//		reverse(str.begin(), str.end());
//		return str;
//	}
//};
//
//#include <vector>
//
//class Solution {
//public:
//	// 这⾥的传值返回拷⻉代价就太⼤了
//	vector<vector<int>> generate(int numRows) {
//		vector<vector<int>> vv(numRows);
//		for (int i = 0; i < numRows; ++i)
//		{
//			vv[i].resize(i + 1, 1);
//		}
//		for (int i = 2; i < numRows; ++i)
//		{
//			for (int j = 1; j < i; ++j)
//			{
//				vv[i][j] = vv[i - 1][j] + vv[i - 1][j - 1];
//			}
//		}
//		return vv;
//	}
//};

#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include "list.h"
#include<assert.h>
#include<string.h>
#include<algorithm>
using namespace std;
namespace wyl
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}
		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			cout << "string(char* str)-构造" << endl;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		void swap(string& s)
		{
			::swap(_str, s._str);
			::swap(_size, s._size);
			::swap(_capacity, s._capacity);
		}
		string(const string& s)
			:_str(nullptr)
		{
			cout << "string(const string& s) -- 拷⻉构造" << endl;
			reserve(s._capacity);
			for (auto ch : s)
			{
				push_back(ch);
			}
		}
		// 移动构造
		string(string&& s)
		{
			cout << "string(string&& s) -- 移动构造" << endl;
			swap(s);
		}
		string& operator=(const string& s)
		{
			cout << "string& operator=(const string& s) -- 拷⻉赋值" <<
				endl;
			if (this != &s)
			{
				_str[0] = '\0';
				_size = 0;
				reserve(s._capacity);
				for (auto ch : s)
				{
					push_back(ch);
				}
			}
			return *this;
		}
		// 移动赋值
		string& operator=(string&& s)
		{
			cout << "string& operator=(string&& s) -- 移动赋值" << endl;
			swap(s);
			return *this;
		}
		~string()
		{
			cout << "~string() -- 析构" << endl;
			delete[] _str;
			_str = nullptr;
		}
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				if (_str)
				{
					strcpy(tmp, _str);
					delete[] _str;
				}
				_str = tmp;
				_capacity = n;
			}
		}
		void push_back(char ch)
		{
			if (_size >= _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity *
					2;
				reserve(newcapacity);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}
		const char* c_str() const
		{
			return _str;
		}
		size_t size() const
		{
			return _size;
		}
private:
	char* _str = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
};
}

//int main()
//{
//	wyl::string s1("xxxxx");
//	// 拷⻉构造
//	wyl::string s2 = s1;
//	// 构造+移动构造，优化后直接构造
//	wyl::string s3 = wyl::string("yyyyy");
//	// 移动构造
//	//wyl::string s4 = move(s1);
//	cout << "******************************" << endl;
//	return 0;
//}

//namespace wyl 
//{
//	string addStrings(string num1, string num2)
//	{
//		string str;
//		int end1 = num1.size() - 1, end2 = num2.size() - 1;
//		int next = 0;
//		while (end1 >= 0 || end2 >= 0)
//		{
//			int val1 = end1 >= 0 ? num1[end1--] - '0' : 0;
//			int val2 = end2 >= 0 ? num2[end2--] - '0' : 0;
//			int ret = val1 + val2 + next;
//			next = ret / 10;
//			ret = ret % 10;
//			str += ('0' + ret);
//		}
//		if (next == 1)
//			str += '1';
//		reverse(str.begin(), str.end());
//		cout << "******************************" << endl;
//		return str;
//	}
//}
////// 场景1
////int main()
////{
////	wyl::string ret = wyl::addStrings("11111", "2222");
////	cout << ret.c_str() << endl;
////	return 0;
////}
//////// 场景2
////int main()
////{
////	bit::string ret;
////	ret = bit::addStrings("11111", "2222");
////	cout << ret.c_str() << endl;
////	return 0;
////}
//// Test.cpp
//#include"list.h"
//int main()
//{
//	wyl::list<wyl::string> lt;
//	cout << "*************************" << endl;
//	wyl::string s1("111111111111111111111");
//	lt.push_back(s1);
//	cout << "*************************" << endl;
//	lt.push_back(wyl::string("22222222222222222222222222222"));
//	cout << "*************************" << endl;
//	lt.push_back("3333333333333333333333333333");
//	cout << "*************************" << endl;
//	lt.push_back(move(s1));
//	cout << "*************************" << endl;
//	return 0;
//}


//void Fun(int& x) { cout << "左值引⽤" << endl; }
//void Fun(const int& x) { cout << "const 左值引⽤" << endl; }
//void Fun(int&& x) { cout << "右值引⽤" << endl; }
//void Fun(const int&& x) { cout << "const 右值引⽤" << endl; }
//
//template<class T>
//void Function(T&& t)
//{
//	//Fun(t);
//	Fun(forward<T>(t));
//}
//int main()
//{
//	// 10是右值，推导出T为int，模板实例化为void Function(int&& t)
//	Function(10); // 右值
//	int a;
//	// a是左值，推导出T为int&，引⽤折叠，模板实例化为void Function(int& t)
//	Function(a); // 左值
//	// std::move(a)是右值，推导出T为int，模板实例化为void Function(int&& t)
//	Function(std::move(a)); // 右值
//	const int b = 8;
//	// a是左值，推导出T为const int&，引⽤折叠，模板实例化为void Function(const int&t)
//	Function(b); // const 左值
//	// std::move(b)右值，推导出T为const int，模板实例化为void Function(const int&&t)
//	Function(std::move(b)); // const 右值
//	return 0;
//}

//template <class ...Args>
//void Print(Args&&... args)
//{
//	cout << sizeof...(args) << endl;
//}
//int main()
//{
//	double x = 2.2;
//	Print(); // 包⾥有0个参数
//	Print(1); // 包⾥有1个参数
//	Print(1, string("xxxxx")); // 包⾥有2个参数
//	Print(1.1, string("xxxxx"), x); // 包⾥有3个参数
//	return 0;
//}


//// 编译时递归推导
//void ShowList()
//{
//	// 编译器时递归的终⽌条件，参数包是0个时，直接匹配这个函数
//	cout << endl;
//}
//template <class T, class ...Args>
//void ShowList(T x, Args... args)
//{
//	cout << x << " ";
//	// args是N个参数的参数包
//	// 调⽤ShowList，参数包的第⼀个传给x，剩下N-1传给第⼆个参数包
//	ShowList(args...);
//}
//// 编译时递归推导解析参数
//template <class ...Args>
//void Print(Args... args)
//{
//	ShowList(args...);
//}
//int main()
//{
//	Print();
//	Print(1);
//	Print(1, string("xxxxx"));
//	Print(1, string("xxxxx"), 2.2);
//	return 0;
//}

//template <class T>
//const T& GetArg(const T& x)
//{
//	cout << x << " ";
//	return x;
//}
//template <class ...Args>
//void Arguments(Args... args)
//{}
//template <class ...Args>
//void Print(Args... args)
//{
//	// 注意GetArg必须返回或者到的对象，这样才能组成参数包给Arguments
//	Arguments(GetArg(args)...);
//}
//// 本质可以理解为编译器编译时，包的扩展模式
//// 将上⾯的函数模板扩展实例化为下⾯的函数
////void Print(int x, string y, double z)
////{
//// Arguments(GetArg(x), GetArg(y), GetArg(z));
////}
//int main()
//{
//	Print(1, string("xxxxx"), 2.2);
//	return 0;
//}
// emplace_back总体⽽⾔是更⾼效，推荐以后使⽤emplace系列替代insert和push系列
//int main()
//{
//	wyl::list<wyl::string> lt;
//	// 传左值，跟push_back⼀样，⾛拷⻉构造
//	wyl::string s1("111111111111");
//	lt.emplace_back(s1);
//	cout << "*********************************" << endl;
//	// 右值，跟push_back⼀样，⾛移动构造
//	lt.emplace_back(move(s1));
//	cout << "*********************************" << endl;
//	// 直接把构造string参数包往下传，直接⽤string参数包构造string
//	// 这⾥达到的效果是push_back做不到的
//	lt.emplace_back("111111111111");
//	cout << "*********************************" << endl << std::endl;;
//
//
//	wyl::list<pair<wyl::string, int>> lt1;
//	// 跟push_back⼀样
//	// 构造pair + 拷⻉/移动构造pair到list的节点中data上
//	pair<wyl::string, int> kv("苹果", 1);
//	lt1.emplace_back(kv);
//	cout << "*********************************" << endl;
//	// 跟push_back⼀样
//	lt1.emplace_back(move(kv));
//	cout << "*********************************" << endl;
//	////////////////////////////////////////////////////////////////////
//	// 直接把构造pair参数包往下传，直接⽤pair参数包构造pair
//	// 这⾥达到的效果是push_back做不到的
//	lt1.emplace_back("苹果", 1);
//	cout << "*********************************" << endl;
//	return 0;
//}

class Person
{
public:
	Person(const char* name = "", int age = 0)
		:_name(name)
		, _age(age)
	{}
private:
	wyl::string _name;
	int _age;
};
int main()
{
	Person s1;
	Person s2 = s1;
	Person s3 = std::move(s1);
	Person s4;
	s4 = std::move(s2);
	return 0;
}