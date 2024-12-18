////#define _CRT_SECURE_NO_WARNINGS
////
////#include <list>
////#include <iostream>
////#include <vector>
////#include <algorithm>
////
//////int main()
//////{
//////	std::list<int> lt1 = { 1, 2, 3, 4, 5 };
//////	int x;
//////	/*while (std::cin >> x)
//////	{
//////		auto pos = std::find(lt1.begin(), lt1.end(), x);
//////		if (pos != lt1.end())
//////		{
//////			lt1.splice(lt1.begin(), lt1, pos);
//////		}
//////		for (auto e : lt1)
//////		{
//////			std::cout << e << ' ';
//////		}
//////		std::cout << std::endl;
//////	}*/
//////
//////	//std::list<int> lt2 = { 1, 3, 66, 0, 1 };
//////	//lt2.sort(std::greater<int>());
//////	//for (auto e : lt2)
//////	//{
//////	//	std::cout << e << ' ';
//////	//}
//////
//////	std::vector<int> v1 = { 1, 3, 66, 0, 1 };
//////
//////	//sort(v1.begin(), v1.end());
//////	sort(v1.begin(), v1.end(), std::greater<int>());
//////
//////	for (auto e : v1)
//////	{
//////		std::cout << e << " ";
//////	}
//////	std::cout << std::endl;
//////
//////	return 0;
//////}
////
////#include "List.h"
////
////struct pos
////{
////	int _x, _y;
////	pos(int x = 0, int y = 0)
////		:_x(x)
////		,_y(y)
////	{}
////};
////
////int main()
////{
////	//wyl::list<int> lt1;
////	//lt1.push_back(1);
////	//lt1.push_back(1);
////	//lt1.push_back(1);
////	//lt1.push_back(1);
////
////	//wyl::list<int>::iterator it1 = lt1.begin();
////
////	//while (it1 != lt1.end())
////	//{
////	//	std::cout << *it1 << ' ';
////	//	++it1;
////	//}
////	//std::cout << std::endl;
////
////	//for (auto& e : lt1)
////	//{
////	//	std::cout << e << ' ';
////	//}
////	//std::cout << '\n';
////
////	//wyl::list<pos> lt2;
////	
////	//lt2.push_back({ 1, 2 });
////	//lt2.push_back({ 2, 1 });
////
////	//wyl::list<pos>::iterator it2 = lt2.begin();
////
////	//for (auto& e : lt2)
////	//{
////	//	std::cout << e._x << ' ' << e._y;
////	//}
////	//std::cout << std::endl;
////
////
////	//while (it2 != lt2.end())
////	//{
////	//	std::cout << it2->_x << ' ';
////	//	it2++;
////	//}
////	//std::cout << std::endl;
////
////	wyl::list<int> lt2;
////	lt2.push_back(1);
////	lt2.push_back(2);
////	lt2.push_back(3);
////
////	for (auto& e : lt2)
////	{
////		std::cout << e << ' ';
////	}
////	std::cout << std::endl;
////
////	lt2.push_front(3);
////	lt2.push_front(2);
////	lt2.push_front(1);
////
////	for (auto& e : lt2)
////	{
////		std::cout << e << ' ';
////	}
////	std::cout << std::endl;
////	return 0;
////}
//
//
//#include "List.h"
//#include <iostream>
//
//int main()
//{
//	//const wyl::list<int> lt1(10, 0);
//	//wyl::list<int>::const_iterator it = lt1.begin();
//
//	//while (it != lt1.end())
//	//{
//	//	std::cout << *it << ' ';
//	//	it++;
//	//}
//	//std::cout << std::endl;
//
//	wyl::list<int> lt1;
//	lt1.push_back(1);
//	lt1.push_back(2);
//	lt1.push_back(3);
//	lt1.push_back(4);
//	lt1.push_front(0);
//	lt1.push_front(-1);
//
//	for (auto& x : lt1)
//	{
//		std::cout << x << ' ';
//	}
//	std::cout << std::endl;
//
//	lt1.pop_back();
//	lt1.pop_front();
//
//	for (auto& x : lt1)
//	{
//		std::cout << x << ' ';
//	}
//	std::cout << std::endl;
//
//	wyl::list<int> lt2(lt1);
//
//	for (auto& x : lt2)
//	{
//		std::cout << x << ' ';
//	}
//	std::cout << std::endl;
//
//	wyl::list<int> lt3(10, 1);
//	lt2 = lt3;
//
//	for (auto& x : lt2)
//	{
//		std::cout << x << ' ';
//	}
//	std::cout << std::endl;
//	return 0;
//}

//#include <iostream>
//#include <list>
//using namespace std;
//
//template<class T>
//void removeDuplicates(list<T>& aList)
//{
//
//	T curValue;
//	list<int>::iterator cur;
//	list<int>::iterator p ;
//
//	cur = aList.begin();
//	while (cur != aList.end())
//	{
//		curValue = *cur;
//		//空白行 1
//		p = ++cur;
//		while (p != aList.end())
//		{
//			if (*p == curValue)
//			{
//				//空白行 2
//				p == cur ? cur = p = aList.erase(p) : p = aList.erase(p);
//			}
//			else
//			{
//				p++;
//			}
//		}
//	}
//}
//
//#include <stack>
//
//void main()
//
//{
//
//	stack<char> S;
//
//	char x, y;
//
//	x = 'n'; y = 'g';
//
//	S.push(x); S.push('i'); S.push(y);
//
//	S.pop(); S.push('r'); S.push('t'); S.push(x);
//
//	S.pop(); S.push('s');
//
//	while (!S.empty())
//
//	{
//
//		x = S.top();
//
//		S.pop();
//
//		cout << x;
//
//	};
//
//	cout << y;
//
//}

#include <vector>
#include <deque>
#include <list>

////template<class T1, class T2>
////template<typename T1, typename T2>
// //template<typename T, size_t N =  100, class _a = std::alloc<T>)
//template<size_t N>
//class a
//{
//
//};
//
//int main()
//{
//
//	std::deque<int> cont = { 1, 2, 3, 4, 5 };
//	std::deque<int>::iterator iter, tempIt;
//	for (iter = cont.begin(); iter != cont.end();)
//
//	{
//
//		tempIt = iter;
//
//		++iter;
//		cont.erase(tempIt);
//
//	}
//}

#include <iostream>
using namespace std;
template<typename Type>
Type Max(const Type& a, const Type& b)
{
	cout << "This is Max<Type>" << endl;
	return a > b ? a : b;
}

template<>
int Max<int>(const int& a, const int& b)
{
	cout << "This is Max<int>" << endl;
	return a > b ? a : b;
}

template<>
char Max<char>(const char& a, const char& b)
{
	cout << "This is Max<char>" << endl;
	return a > b ? a : b;
}

int Max(const int& a, const int& b)
{
	cout << "This is Max" << endl;
	return a > b ? a : b;
}

int main()
{
	Max(10, 20);
	Max(12.34, 23.45);
	Max('A', 'B');
	Max<int>(20, 30);
	return 0;
}


