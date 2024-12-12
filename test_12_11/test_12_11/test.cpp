#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "SearshBinaryTree.h"

int main()
{
	string arr[] = { "a", "c", "a", "c", "a", "a", "c", "a", "b", "a", "b" };
	for (int i = 0; i < 7; i++)
	{
		std::cout << arr[i] << ' ';
	}
	BSTree<string, int> countTree;
	for (const auto& str : arr)
	{
		// �Ȳ��ҁ9�6���ڲ�����������
		// 1�����ڣ�˵���9�6���ځ9�2�γ��֣����9�2<�9�6��, 1>
		// 2���ڣ�����ҵ��Ľ���Ё9�6����Ӧ�Ĵ���++
		//BSTreeNode<string, int>* ret = countTree.Find(str);
		auto ret = countTree.Find(str);
		if (ret == nullptr)
		{
			countTree.Insert(str, 1);
		}
		else
		{
			ret->_value++;
		}
	}
	countTree.InOrder();
	return 0;
}