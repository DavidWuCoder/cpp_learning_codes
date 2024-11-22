#define _CRT_SECURE_NO_WARNINGS

#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

//int main()
//{
//	std::list<int> lt1 = { 1, 2, 3, 4, 5 };
//	int x;
//	/*while (std::cin >> x)
//	{
//		auto pos = std::find(lt1.begin(), lt1.end(), x);
//		if (pos != lt1.end())
//		{
//			lt1.splice(lt1.begin(), lt1, pos);
//		}
//		for (auto e : lt1)
//		{
//			std::cout << e << ' ';
//		}
//		std::cout << std::endl;
//	}*/
//
//	//std::list<int> lt2 = { 1, 3, 66, 0, 1 };
//	//lt2.sort(std::greater<int>());
//	//for (auto e : lt2)
//	//{
//	//	std::cout << e << ' ';
//	//}
//
//	std::vector<int> v1 = { 1, 3, 66, 0, 1 };
//
//	//sort(v1.begin(), v1.end());
//	sort(v1.begin(), v1.end(), std::greater<int>());
//
//	for (auto e : v1)
//	{
//		std::cout << e << " ";
//	}
//	std::cout << std::endl;
//
//	return 0;
//}

#include "List.h"

struct pos
{
	int _x, _y;
	pos(int x = 0, int y = 0)
		:_x(x)
		,_y(y)
	{}
};

int main()
{
	//wyl::list<int> lt1;
	//lt1.push_back(1);
	//lt1.push_back(1);
	//lt1.push_back(1);
	//lt1.push_back(1);

	//wyl::list<int>::iterator it1 = lt1.begin();

	//while (it1 != lt1.end())
	//{
	//	std::cout << *it1 << ' ';
	//	++it1;
	//}
	//std::cout << std::endl;

	//for (auto& e : lt1)
	//{
	//	std::cout << e << ' ';
	//}
	//std::cout << '\n';

	wyl::list<pos> lt2;
	
	lt2.push_back({ 1, 2 });
	lt2.push_back({ 2, 1 });

	wyl::list<pos>::iterator it2 = lt2.begin();

	for (auto& e : lt2)
	{
		std::cout << e._x << ' ' << e._y;
	}
	std::cout << std::endl;


	while (it2 != lt2.end())
	{
		std::cout << it2->_x << ' ';
		it2++;
	}
	std::cout << std::endl;
	return 0;
}