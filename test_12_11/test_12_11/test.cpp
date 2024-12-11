#include <iostream>
#include <vector>

#include "SearshBinaryTree.h"

int main()
{
	BSTree<int> t;
	std::vector<int> a = { 8, 3, 1, 1, 10, 6, 4, 7, 14, 13 };

	for (auto& x : a)
	{
		t.insert(x);
	}
	t.Inorder();
	return 0;
}