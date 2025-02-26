#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<assert.h>
#include<map>
using namespace std;

struct Point
{
	int _x;
	int _y;
};

class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		cout << "Date(int year, int month, int day)" << endl;
	}
	Date(const Date& d)
		:_year(d._year)
		, _month(d._month)
		, _day(d._day)
	{
		cout << "Date(const Date& d)" << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

void PushBack(const Date& d)
{}

//int main()
//{
//	// C++98支持的
//	int a1[] = { 1, 2, 3, 4, 5 };
//	int a2[5] = { 0 };
//	Point p = { 1, 2 };
//
//	// C++11支持的
//	// 内置类型支持
//	int x1 = { 2 };
//
//	// 运行一下，我们可以验证上面的理论，发现是没调用拷贝构造的
//	// 本质都是由构造函数支持的隐式类型转换
//	string str = "11111111";
//	Date d0 = 2020;
//	Date d1 = { 2025, 1, 1 };
//	Date d2(2025, 1, 1);
//
//	const Date& r1 = 2020;
//	const Date& r2 = { 2025, 1, 1 };
//
//
//	Date d3(2025, 1, 1);
//	PushBack(d3);
//
//	PushBack({ 2025, 1, 1 });
//	PushBack(2020);
//	PushBack({ 2020,12 });
//
//	// 可以省略掉=
//	Point p1{ 1, 2 };
//	int x2{ 2 };
//	Date d6{ 2024, 7, 25 };
//	const Date& d7{ 2024, 7, 25 };
//
//	// 不支持，只有{}初始化，才能省略=
//	// Date d8 2025;
//
//
//	return 0;
//}

//int main()
//{
//	auto il = { 10, 20, 30, 40, 50 };
//	cout << typeid(il).name() << endl;
//
//	cout << il.begin() << endl;
//	int i = 0, j = 1;
//	cout << &i << endl;
//	cout << &j << endl;
//
//	cout << sizeof(il) << endl;
//
//	vector<int> v1 = { 1,2,3,4 };
//	vector<int> v2 = { 1,2,3,4,5,6,7 };
//
//	v1 = { 10,20,30 };
//
//	// 这里是pair对象的{}初始化和map的initializer_list构造结合到一起用了
//	map<string, string> dict = { {"sort", "排序"}, {"string", "字符串"} };
//
//	/*pair<string, string> kv1("sort", "排序");
//	pair<string, string> kv2("string", "字符串");
//	map<string, string> dict = { kv1, kv2 };*/
//
//	return 0;
//}

///////////////////////////////////////////////////////////////////////////////////

//int main()
//{
//	// 左值：可以取地址
//	// 以下的p、b、c、*p、s、s[0]就是常见的左值
//	int* p = new int(0);
//	int b = 1;
//	const int c = b;
//	*p = 10;
//	string s("111111");
//	s[0] = 'x';
//	cout << &c << endl;
//	cout << (void*)&s[0] << endl;
//
//	// 20：05
//	// 右值：不能取地址
//	double x = 1.1, y = 2.2;
//	// 以下几个10、x + y、fmin(x, y)、string("11111")都是常见的右值
//	10;
//	x + y;
//	fmin(x, y);
//	string("11111");
//
//	//cout << &10 << endl;
//	//cout << &(x+y) << endl;
//	//cout << &(fmin(x, y)) << endl;
//	//cout << &string("11111") << endl;
//
//	// 右值引用
//	int&& rr1 = 10;
//	double&& rr2 = x+y;
//	string&& rr3 = string("11111");
//
//	const double& r2 = x + y;
//	int&& rr4 = move(b);
//	//int&& rr4 = (int&&)b;
//
//	cout << &r2 << endl;
//	cout << &rr1 << endl;
//
//	return 0;
//}

class AA
{
public:
	AA(int a1, int a2)
		:_a1(a1)
		, _a2(a2)
	{}

	~AA()
	{
		cout << "~AA()" << endl;
	}
private:
	int _a1 = 1;
	int _a2 = 1;
};

//int main()
//{
//	AA aa1(1, 1);
//	const AA& rr1 = AA(2, 2);
//	AA&& rr2 = AA(3, 3);
//
//	cout << "----------------------" << endl;
//
//	return 0;
//}

//void f(int& x)
//{
//	std::cout << "左值引用重载 f(" << x << ")\n";
//}
//
//void f(const int& x)
//{
//	std::cout << "到 const 的左值引用重载 f(" << x << ")\n";
//}
//
//void f(int&& x)
//{
//	std::cout << "右值引用重载 f(" << x << ")\n";
//}
//
//int main()
//{
//	int i = 1;
//	const int ci = 2;
//	f(i); // 调用 f(int&)
//	f(ci); // 调用 f(const int&)
//	f(3); // 调用 f(int&&)，如果没有 f(int&&) 重载则会调用 f(const int&)
//	f(std::move(i)); // 调用 f(int&&)
//
//	int& y = i;
//	f(y);
//	int&& x = 1;
//	f(x); // 调用 f(int& x)
//	f(std::move(x)); // 调用 f(int&& x)
//
//	return 0;
//}

namespace bit
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
			cout << "string(const string& s) -- 拷贝构造" << endl;
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
			cout << "string& operator=(const string& s) -- 拷贝赋值" <<
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
//	bit::string s1("xxxxx");
//	// 拷贝构造
//	bit::string s2 = s1;
//
//	// 构造+移动构造，优化后直接构造
//	bit::string s3 = bit::string("yyyyy");
//
//	// 移动构造
//	bit::string s4 = move(s1);
//	cout << "******************************" << endl;
//	return 0;
//}
namespace bit
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

int main()
{
	bit::string ret;
	//...

	ret = bit::addStrings("11111", "2222");

	cout << ret.c_str() << endl;

	return 0;
}