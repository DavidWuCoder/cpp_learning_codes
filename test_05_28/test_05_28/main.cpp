#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Goods
{
	string _name; // 名字
	double _price; // 价格
	int _evaluate; // 评价
	// ...
	Goods(const char* str, double price, int evaluate)
		:_name(str)
		, _price(price)
		, _evaluate(evaluate)
	{
	}
};
struct ComparePriceLess
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._price < gr._price;
	}
};
struct ComparePriceGreater
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._price > gr._price;
	}
};
//int main()
//{
//	vector<Goods> v = { { "苹果", 2.1, 5 }, { "⾹蕉", 3, 4 }, { "橙⼦", 2.2, 3
//	}, { "菠萝", 1.5, 4 } };
//	// 类似这样的场景，我们实现仿函数对象或者函数指针⽀持商品中
//	// 不同项的⽐较，相对还是⽐较⿇烦的，那么这⾥lambda就很好⽤了
//	sort(v.begin(), v.end(), ComparePriceLess());
//	sort(v.begin(), v.end(), ComparePriceGreater());
//	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2) {
//		return g1._price < g2._price;
//		});
//	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2) {
//		return g1._price > g2._price;
//		});
//	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2) {
//		return g1._evaluate < g2._evaluate;
//		});
//	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2) {
//		return g1._evaluate > g2._evaluate;
//		});
//	return 0;
//}

class Rate
{
public:
	Rate(double rate)
		: _rate(rate)
	{
	}
	double operator()(double money, int year)
	{
		return money * _rate * year;
	}
private:
	double _rate;
};
//int main()
//{
//	double rate = 0.49;
//	// lambda
//	auto r2 = [rate](double money, int year) {
//		return money * rate * year;
//		};
//	// 函数对象
//	Rate r1(rate);
//	r1(10000, 2);
//	r2(10000, 2);
//	auto func1 = [] {
//		cout << "hello world" << endl;
//		};
//	func1();
//	return 0;
//}

#include<functional>
int f(int a, int b)
{
	return a + b;
}
struct Functor
{
public:
	int operator() (int a, int b)
	{
		return a + b;
	}
};
class Plus
{
public:
	Plus(int n = 10)
		:_n(n)
	{
	}
	static int plusi(int a, int b)
	{
		return a + b;
	}
	double plusd(double a, double b)
	{
		return (a + b) * _n;
	}
private:
	int _n;
};
int main()
{
	// 包装各种可调⽤对象
	function<int(int, int)> f1 = f;
	function<int(int, int)> f2 = Functor();
	function<int(int, int)> f3 = [](int a, int b) {return a + b; };
	cout << f1(1, 1) << endl;
	cout << f2(1, 1) << endl;
	cout << f3(1, 1) << endl;
	// 包装静态成员函数
	// 成员函数要指定类域并且前⾯加&才能获取地址
	function<int(int, int)> f4 = &Plus::plusi;
	cout << f4(1, 1) << endl;
	// 包装普通成员函数
	// 普通成员函数还有⼀个隐含的this指针参数，所以绑定时传对象或者对象的指针过去都可以
	function<double(Plus*, double, double)> f5 = &Plus::plusd;
	Plus pd;
	cout << f5(&pd, 1.1, 1.1) << endl;
	function<double(Plus, double, double)> f6 = &Plus::plusd;
	cout << f6(pd, 1.1, 1.1) << endl;
	cout << f6(pd, 1.1, 1.1) << endl;
	function<double(Plus&&, double, double)> f7 = &Plus::plusd;
	cout << f7(move(pd), 1.1, 1.1) << endl;
	cout << f7(Plus(), 1.1, 1.1) << endl;
	return 0;
}