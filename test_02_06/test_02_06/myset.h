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
		typedef typename RBTree<K, const K, SetKeyOfT>::ConstIterator const_iterator;
		iterator begin()
		{
			return _rbtree.Begin();
		}

		const_iterator end()
		{
			return _rbtree.End();
		}

		const_iterator begin() const
		{
			return _rbtree.Begin();
		}

		iterator end() const
		{
			return _rbtree.End();
		}


		std::pair<iterator, bool> insert(const K& key)
		{
			return _rbtree.Insert(key);
		}

		iterator find(const K& key)
		{
			return _rbtree.find(key);
		}
	private:
		RBTree<K, const K, SetKeyOfT> _rbtree;
	};

	void Print(const set<int>& s)
	{
		set<int>::const_iterator it = s.end();
		while (it != s.begin())
		{
			--it;
			// 不⽀持修改
			//*it += 2;
			cout << *it << " ";
		}
		cout << endl;
	}
	
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

		Print(s);
	}
}