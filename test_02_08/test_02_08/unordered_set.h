#pragma once

#include "HashTable.h"


namespace wyl
{
	template<class K>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename hash_bucket::HashTable<K, const K, SetKeyOfT>::Iterator iterator;
		typedef typename hash_bucket::HashTable<K, const K, SetKeyOfT>::ConstIterator const_iterator;

		iterator begin()
		{
			return _ht.Begin();
		}

		iterator end()
		{
			return _ht.End();
		}


		const_iterator begin() const
		{
			return _ht.Begin();
		}

		const_iterator end() const
		{
			return _ht.End();
		}


		std::pair<iterator, bool> insert(const K& key)
		{
			return _ht.Insert(key);
		}
	private:
		hash_bucket::HashTable<K, const K, SetKeyOfT> _ht;
	};

	void Print(const unordered_set<int>& st)
	{
		unordered_set<int>::const_iterator it = st.begin();
		while (it != st.end())
		{
			std::cout << *it << ' ';
			++it;
		}
		std::cout << std::endl;
	}

	void test_set1()
	{
		unordered_set<int> st;
		st.insert(1);
		st.insert(3);
		st.insert(2);
		st.insert(4);

		for (auto e : st)
		{
			std::cout << e << ' ';
		}
		Print(st);
	}
}
