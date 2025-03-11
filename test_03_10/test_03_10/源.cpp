//#include <iostream>
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
#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
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

namespace wyl 
{
	string addStrings(string num1, string num2)
	{
		string str;
		int end1 = num1.size() - 1, end2 = num2.size() - 1;
		int next = 0;
		while (end1 >= 0 || end2 >= 0)
		{
			int val1 = end1 >= 0 ? num1[end1--] - '0' : 0;
			int val2 = end2 >= 0 ? num2[end2--] - '0' : 0;
			int ret = val1 + val2 + next;
			next = ret / 10;
			ret = ret % 10;
			str += ('0' + ret);
		}
		if (next == 1)
			str += '1';
		reverse(str.begin(), str.end());
		cout << "******************************" << endl;
		return str;
	}
}
// 场景1
int main()
{
	wyl::string ret = wyl::addStrings("11111", "2222");
	cout << ret.c_str() << endl;
	return 0;
}
////// 场景2
//int main()
//{
//	bit::string ret;
//	ret = bit::addStrings("11111", "2222");
//	cout << ret.c_str() << endl;
//	return 0;
//}

