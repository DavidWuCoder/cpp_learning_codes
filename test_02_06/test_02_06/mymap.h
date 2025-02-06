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
		typedef typename RBTree<K, std::pair<const  K, V>, MapKeyOfT>::ConstIterator const_iterator;

		iterator begin()
		{
			return _rbtree.Begin();
		}

		iterator end()
		{
			return _rbtree.End();
		}

		const_iterator begin() const
		{
			return _rbtree.Begin();
		}

		const_iterator end() const
		{
			return _rbtree.End();
		}

		std::pair<iterator, bool> insert(const std::pair<K, V>& kv)
		{
			return _rbtree.Insert(kv);
		}

		V& operator[](const K& key)
		{
			std::pair<iterator, bool> ret = _rbtree.Insert({ key, V() });
			return ret.first->second;
		}

		iterator find(const K& key)
		{
			return _rbtree.find(key);
		}
	private:
		RBTree<K, std::pair<const K, V>, MapKeyOfT> _rbtree;

	};

	void test_map()
	{
		//map<int, int> m;
		//m.insert({ 4, 4 });
		//m.insert({ 1, 1 });
		//m.insert({ 5, 5 });
		//m.insert({ 3, 3 });

		//map<int, int>::iterator it = m.begin();
		//while (it != m.end())
		//{
		//	std::cout << it->first << ' ' << it->second << std::endl;
		//	++it;
		//}
		//std::cout << std::endl;

		map<int, int> dict;

		int a[13] = {1, -1, 0, 0, 0, 1, -1, 2, 2, 3, 4, 4, 3};

		for (int i = 0; i < 13; i++)
		{
			dict[a[i]]++;
		}

		

		for (auto& kv : dict)
		{
			std::cout << kv.first << " : " << kv.second << '\n';
		}
		std::cout << std::endl;
	}
}
