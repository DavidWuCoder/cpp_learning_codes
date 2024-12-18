#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>

#include <iostream>
#include "queue.h"
#include "stack.h"
#include "priority_queue.h"

int main()
{
	//std::stack<int> st;
	//st.push(1);
	//st.push(2);
	//st.push(3);
	//st.push(4);

	//while (!st.empty())
	//{
	//	std::cout << st.top() << ' ';
	//	st.pop();
	//}
	//std::cout << std::endl;

	//wyl::stack<int> st;

	//st.push(1);
	//st.push(2);
	//st.push(3);
	//st.push(4);

	//while (!st.empty())
	//{
	//	std::cout << st.top() << ' ';
	//	st.pop();
	//}
	//std::cout << std::endl;


	//wyl::queue<int> q;

	//q.push(1);
	//q.push(2);
	//q.push(3);
	//q.push(4);

	//while (!q.empty())
	//{
	//	std::cout << q.front() << ' ';
	//	q.pop();
	//}
	//std::cout << std::endl;
	int a[] = { 1, 4, 2, 5, 6, 3, 2 };
	wyl::priority_queue<int> pq(a, a + 7);

	//wyl::priority_queue<int, std::vector<int>, wyl::greater<int>> pq(a, a + 7);


	while (!pq.empty())
	{
		std::cout << pq.top() << std::endl;
		pq.pop();
	}

	return 0;
}

//#define _CRT_SECURE_NO_WARNINGS
//
//#include <algorithm>
//
//#include <iostream>
//#include "queue.h"
//#include "stack.h"
//#include "priority_queue.h"
//
//template<class T>
//struct Less {
//	bool operator()(const T& x, const T& y) const
//	{
//		return x < y;
//	}
//};
//
//int main()
//{
//	Less<int> lessfunc;
//
//	std::cout << lessfunc(1, 2) << std::endl;
//	return 0;
//}

#include <iostream>

template<class T, size_t N>
class Stack
{
private:
	T _a[N];
	int _top;
};


int main()
{
	Stack<int, 20> st1;
	Stack<int, 2000> st2;
	return 0;
}
