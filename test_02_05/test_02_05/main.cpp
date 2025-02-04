#define _CRT_SECURE_NO_WARNINGS

#include <vector>

#include "RBTree.h"
using namespace std;

// 测试代码
void TestRBTree1()
{
	RBTree<int, int> t;
	// 常规的测试⽤例
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	// 特殊的带有双旋场景的测试⽤例
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };


	for (auto e : a)
	{
		if (e == 14)
		{
			int x = 0;
			x++;
		}
		t.Insert({ e, e });
	}
	t.InOrder();
	std::cout << t.IsBalance() << '\n';
	//std::cout << t.IsBalanceTree() << std::endl;
}

// 插⼊⼀堆随机值，测试平衡，顺便测试⼀下⾼度和性能等
void TestRBTree2()
{
	const int N = 1000000;
	vector<int> v;
	v.reserve(N);
	srand(time(0));
	for (size_t i = 0; i < N; i++)
	{
		v.push_back(rand() + i);
	}
	size_t begin2 = clock();

	RBTree<int, int> t;
	for (auto e : v)
	{
		t.Insert(make_pair(e, e));
	}

	size_t end2 = clock();

	cout << t.IsBalance() << endl;
	cout << "Insert:" << end2 - begin2 << endl;
	cout << "Height:" << t.Height() << endl;
	cout << "Size:" << t.Size() << endl;
}

int main()
{
	//TestRBTree1();
	TestRBTree2();
	return 0;
}

