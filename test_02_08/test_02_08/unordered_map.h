#pragma once

#include "HashTable.h"

namespace wyl
{
	template<class K, class V>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const std::pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename hash_bucket::HashTable<K, std::pair<const K, V>, MapKeyOfT>::Iterator iterator;
		typedef typename hash_bucket::HashTable<K, std::pair<const K, V>, MapKeyOfT>::ConstIterator const_iterator;

		const_iterator begin() const
		{
			return _ht.Begin();
		}

		const_iterator end() const
		{
			return _ht.End();
		}

		V& operator[](const K& key)
		{
			std::pair<iterator, bool> ret = _ht.Insert(make_pair(key, V()));
			return ret.first->second;
		}

		iterator Find(const K& key)
		{
			return _ht.Find(key);
		}

		iterator begin()
		{
			return _ht.Begin();
		}

		iterator end()
		{
			return _ht.End();
		}

		std::pair<iterator, bool> insert(const std::pair<K, V> kv)
		{
			return _ht.Insert(kv);
		}
	private:
		hash_bucket::HashTable<K, std::pair<const K, V>, MapKeyOfT> _ht;
	};

	void Print(const unordered_map<std::string, std::string>& mp)
	{
		unordered_map<std::string, std::string>::const_iterator it = mp.begin();
		while (it != mp.end())
		{
			std::cout << it->first << ' ' << it->second << std::endl;
			++it;
		}
		std::cout << std::endl;
	}

	void test_map()
	{
		unordered_map<std::string, int> mp;
		
		std::vector<std::string> a = { "111", "111", "2222", "22", "111", "222" };

		for (auto s : a)
		{
			mp[s]++;
		}

		for (auto& kv : mp)
		{
			std::cout << kv.first << "  " << kv.second << std::endl;
		}
		std::cout << std::endl;

		/*Print(mp);*/
	}
}
