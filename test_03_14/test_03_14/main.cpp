#include <iostream>

#include<functional>
using namespace std;
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
	{}
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
//int main()
//{
//	// 包装各种可调⽤对象
//	function<int(int, int)> f1 = f;
//	function<int(int, int)> f2 = Functor();
//	function<int(int, int)> f3 = [](int a, int b) {return a + b; };
//	cout << f1(1, 1) << endl;
//	cout << f2(1, 1) << endl;
//	cout << f3(1, 1) << endl;
//	// 包装静态成员函数
//	// 成员函数要指定类域并且前⾯加&才能获取地址
//	function<int(int, int)> f4 = &Plus::plusi;
//	cout << f4(1, 1) << endl;
//	// 包装普通成员函数
//	// 普通成员函数还有⼀个隐含的this指针参数，所以绑定时传对象或者对象的指针过去都可以
//	function<double(Plus*, double, double)> f5 = &Plus::plusd;
//	Plus pd;
//	cout << f5(&pd, 1.1, 1.1) << endl;
//	function<double(Plus, double, double)> f6 = &Plus::plusd;
//	cout << f6(pd, 1.1, 1.1) << endl;
//	cout << f6(pd, 1.1, 1.1) << endl;
//	function<double(Plus&&, double, double)> f7 = &Plus::plusd;
//	cout << f7(move(pd), 1.1, 1.1) << endl;
//	cout << f7(Plus(), 1.1, 1.1) << endl;
//	return 0;
//}

int Sub(int a, int b)
{
	return (a - b) * 10;
}
int SubX(int a, int b, int c)
{
	return (a - b - c) * 10;
}
using placeholders::_1;
using placeholders::_2;
using placeholders::_3;

int main()
{
	auto sub1 = bind(Sub, _1, _2);
	cout << sub1(10, 5) << endl;
	// bind 本质返回的⼀个仿函数对象
	// 调整参数顺序（不常⽤）
	// _1代表第⼀个实参
	// _2代表第⼆个实参
	// ...
	auto sub2 = bind(Sub, _2, _1);
	cout << sub2(10, 5) << endl;

	// 调整参数个数 （常⽤）
	auto sub3 = bind(Sub, 100, _1);
	cout << sub3(5) << endl;

	// 成员函数对象进⾏绑死，就不需要每次都传递了
	function<double(Plus&&, double, double)> f6 = &Plus::plusd;
	Plus pd;
	cout << f6(move(pd), 1.1, 1.1) << endl;
	cout << f6(Plus(), 1.1, 1.1) << endl;
	// bind⼀般⽤于，绑死⼀些固定参数
	function<double(double, double)> f7 = bind(&Plus::plusd, Plus(), _1, _2);
	cout << f7(1.1, 1.1) << endl;

	// 计算复利的lambda
	auto func1 = [](double rate, double money, int year)->double {
		double ret = money;
		for (int i = 0; i < year; i++)
		{
			ret += ret * rate;
		}
		return ret - money;
		};
	// 绑死⼀些参数，实现出⽀持不同年华利率，不同⾦额和不同年份计算出复利的结算利息
	function<double(double)> func3_1_5 = bind(func1, 0.015, _1, 3);
	function<double(double)> func5_1_5 = bind(func1, 0.015, _1, 5);
	function<double(double)> func10_2_5 = bind(func1, 0.025, _1, 10);
	function<double(double)> func20_3_5 = bind(func1, 0.035, _1, 30);

	cout << func3_1_5(1000000) << endl;
	cout << func5_1_5(1000000) << endl;
	cout << func10_2_5(1000000) << endl;
	cout << func20_3_5(1000000) << endl;

	return 0;
}