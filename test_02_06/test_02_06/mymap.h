#pragma once

#include "RBTree.h"

namespace wyl {
	template<class K, class V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};

	public:
		typedef typename RBTree<K, std::pair<const  K, V>, MapKeyOfT>::Iterator iterator;

		iterator begin()
		{
			return _rbtree.Begin();
		}

		iterator end()
		{
			return _rbtree.End();
		}

		bool insert(const std::pair<K, V>& kv)
		{
			return _rbtree.Insert(kv);
		}
	private:
		RBTree<K, std::pair<const K, V>, MapKeyOfT> _rbtree;

	};

	void test_map()
	{
		map<int, int> m;
		m.insert({ 4, 4 });
		m.insert({ 1, 1 });
		m.insert({ 5, 5 });
		m.insert({ 3, 3 });

		map<int, int>::iterator it = m.begin();
		while (it != m.end())
		{
			std::cout << it->first << ' ' << it->second << std::endl;
			++it;
		}
		std::cout << std::endl;

		
	}
}
