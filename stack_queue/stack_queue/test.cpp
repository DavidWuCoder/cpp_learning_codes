#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "queue.h"
#include "stack.h"

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


	wyl::queue<int> q;

	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	while (!q.empty())
	{
		std::cout << q.front() << ' ';
		q.pop();
	}
	std::cout << std::endl;
	return 0;
}