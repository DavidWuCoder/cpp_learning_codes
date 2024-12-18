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
		// 先查找⽔果在不在搜索树中
		// 1、不在，说明⽔果第⼀次出现，则插⼊<⽔果, 1>
		// 2、在，则查找到的结点中⽔果对应的次数++
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