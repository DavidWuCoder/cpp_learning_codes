//#define _CRT_SECURE_NO_WARNINGS
//
//#include<iostream>
//#include<set>
//using namespace std;
//int main()
//{
//	// 去重+升序排序
//	//set<int> s;
//	// 去重+降序排序（给⼀个⼤于的仿函数）
//	set<int, greater<int>> s;
//	s.insert(5);
//	s.insert(2);
//	s.insert(7);
//	s.insert(5);
//	//set<int>::iterator it = s.begin();
//	auto it = s.begin();
//	while (it != s.end())
//	{// error C3892: “it”: 不能给常量赋值
//// *it = 1;
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//	// 插⼊⼀段initializer_list列表值，已经存在的值插⼊失败
//	s.insert({ 2,8,3,9 });
//	for (auto e : s)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//	set<string> strset = { "sort", "insert", "add" };
//	// 遍历string⽐较ascll码⼤⼩顺序遍历的
//	for (auto& e : strset)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//}


//#include<iostream>
//#include<set>
//#include <unordered_set>
//using namespace std;
//int main()
//{
//	// 相⽐set不同的是，multiset是排序，但是不去重
//	multiset<int> s = { 4,2,7,2,4,8,4,5,4,9, 4 };
//	//unordered_set<int> s = { 4,2,7,2,4,8,4,5,4,9, 4 };
//	auto it = s.begin();
//	while (it != s.end())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//	// 相⽐set不同的是，x可能会存在多个，find查找中序的第⼀个
//	int x;
//	cin >> x;
//	auto pos = s.find(x);
//	while (pos != s.end() && *pos == x)
//	{
//		cout << *pos << " ";
//		++pos;
//	}
//	cout << endl;
//	// 相⽐set不同的是，count会返回x的实际个数
//	cout << s.count(x) << endl;
//	// 相⽐set不同的是，erase给值时会删除所有的x
//	s.erase(x);
//	for (auto e : s)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//	return 0;
//}

#include <map>



int main()
{
	return 0;
}