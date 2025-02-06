#pragma once

#include "RBTree.h"

namespace wyl {
	template<class K>
	class set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};

	public:
		typedef typename RBTree<K, const K, SetKeyOfT>::Iterator iterator;
		iterator begin()
		{
			return _rbtree.Begin();
		}

		iterator end()
		{
			return _rbtree.End();
		}
		bool insert(const K& key)
		{
			return _rbtree.Insert(key);
		}
	private:
		RBTree<K, const K, SetKeyOfT> _rbtree;
	};
	
	void test_set()
	{
		set<int> s;
		int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		for (auto e : a)
		{
			s.insert(e);
		}

		set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			std::cout << *it << ' ';
			++it;
		}
		std::cout << std::endl;

		it = s.end();
		while (it != s.begin())
		{
			--it;
			std::cout << *it << ' ';
		}
		std::cout << std::endl;

	}
}