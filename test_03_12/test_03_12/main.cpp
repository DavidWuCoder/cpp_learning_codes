#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//
////int main()
////{
////	auto add1 = [](int x, int y)->int {return x + y; };
////	std::cout << add1(1, 2) << std::endl;
////	return 0;
////}
//
//struct Goods
//{
//	string _name; // 名字
//	double _price; // 价格
//	int _evaluate; // 评价
//	// ...
//	Goods(const char* str, double price, int evaluate)
//		:_name(str)
//		, _price(price)
//		, _evaluate(evaluate)
//	{}
//};
//struct ComparePriceLess
//{
//	bool operator()(const Goods& gl, const Goods& gr)
//	{
//		return gl._price < gr._price;
//	}
//};
//struct ComparePriceGreater
//{
//	bool operator()(const Goods& gl, const Goods& gr)
//	{
//		return gl._price > gr._price;
//	}
//};
//int main()
//{
//	vector<Goods> v = { { "苹果", 2.1, 5 }, { "⾹蕉", 3, 4 }, { "橙⼦", 2.2, 3
//	}, { "菠萝", 1.5, 4 } };
//	// 类似这样的场景，我们实现仿函数对象或者函数指针⽀持商品中
//	// 不同项的⽐较，相对还是⽐较⿇烦的，那么这⾥lambda就很好⽤了
//	//sort(v.begin(), v.end(), ComparePriceLess());
//	//sort(v.begin(), v.end(), ComparePriceGreater());
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

int x = 0;
// 捕捉列表必须为空，因为全局变量不⽤捕捉就可以⽤，没有可被捕捉的变量
auto func1 = []()
	{
		x++;
	};
int main()
{
	// 只能⽤当前lambda局部域和捕捉的对象和全局对象
	int a = 0, b = 1, c = 2, d = 3;
	auto func1 = [a, &b]
		{
			// 值捕捉的变量不能修改，引⽤捕捉的变量可以修改
			//a++;
			b++;
			int ret = a + b;
			return ret;
		};
	cout << func1() << endl;
	// 隐式值捕捉
	// ⽤了哪些变量就捕捉哪些变量
	auto func2 = [=]
		{
			int ret = a + b + c;
			return ret;
		};
	cout << func2() << endl;
	// 隐式引⽤捕捉
	// ⽤了哪些变量就捕捉哪些变量
	auto func3 = [&]
		{
			a++;
			c++;
			d++;
		};
	func3();
	cout << a << " " << b << " " << c << " " << d << endl;
	// 混合捕捉1
	auto func4 = [&, a, b]
		{
			//a++;
			//b++;
			c++;
			d++;
			return a + b + c + d;
		};
	func4();
	cout << a << " " << b << " " << c << " " << d << endl;
	// 混合捕捉1
	auto func5 = [=, &a, &b]
		{
			a++;
			b++;
			/*c++;
			d++;*/
			return a + b + c + d;
		};
	func5();
	cout << a << " " << b << " " << c << " " << d << endl;
	// 局部的静态和全局变量不能捕捉，也不需要捕捉
	static int m = 0;
	auto func6 = []
		{
			int ret = x + m;
			return ret;
		};
	// 传值捕捉本质是⼀种拷⻉,并且被const修饰了
	// mutable相当于去掉const属性，可以修改了
	// 但是修改了不会影响外⾯被捕捉的值，因为是⼀种拷⻉
	auto func7 = [=]()mutable
		{
			a++;
			b++;
			c++;
			d++;
			return a + b + c + d;
		};
	cout << func7() << endl;
	cout << a << " " << b << " " << c << " " << d << endl;
	return 0;
}