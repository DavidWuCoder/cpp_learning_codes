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
int main()
{
	double rate = 0.49;
	// lambda
	auto r2 = [rate](double money, int year) {
		return money * rate * year;
		};
	// 函数对象
	Rate r1(rate);
	r1(10000, 2);
	r2(10000, 2);
	auto func1 = [] {
		cout << "hello world" << endl;
		};
	func1();
	return 0;
}