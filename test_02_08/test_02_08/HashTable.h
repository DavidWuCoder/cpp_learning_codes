#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

//namespace open_address
//{
//	enum State
//	{
//		EXIST,
//		EMPTY,
//		DELETE
//	};
//
//	template<class K, class V>
//	struct HashData
//	{
//		std::pair<K, V> _kv;
//		State _state = EMPTY;
//	};
//
//	template<class K>
//	class HashFunc {
//	public:
//		size_t operator()(const K& key)
//		{
//			return (size_t)key;
//		}
//	};
//
//	template<>
//	class HashFunc<std::string> {
//	public:
//		size_t operator()(const std::string& s)
//		{
//			size_t hash = 0;
//			for (auto ch : s)
//			{
//				hash += ch;
//				hash *= 131;
//			}
//			return hash;
//		}
//	};
//
//
//	template < class K, class V, class Hash = HashFunc<K>>
//	class HashTable
//	{
//
//		// 获取素数表里比当前表大的下一个素数
//		inline unsigned long __stl_next_prime(unsigned long n)
//		{
//			// Note: assumes long is at least 32 bits.
//			static const int __stl_num_primes = 28;
//			static const unsigned long __stl_prime_list[__stl_num_primes] =
//			{
//				53, 97, 193, 389, 769,
//				1543, 3079, 6151, 12289, 24593,
//				49157, 98317, 196613, 393241, 786433,
//				1572869, 3145739, 6291469, 12582917, 25165843,
//				50331653, 100663319, 201326611, 402653189, 805306457,
//				1610612741, 3221225473, 4294967291
//			};
//
//			const unsigned long* first = __stl_prime_list;
//			const unsigned long* last = __stl_prime_list + __stl_num_primes;
//			const unsigned long* pos = std::lower_bound(first, last, n);
//			return pos == last ? *(last - 1) : *pos;
//		}
//
//	public:
//
//		HashTable()
//		{
//			_tables.resize(__stl_next_prime(1));
//		}
//
//		bool Insert(const std::pair<K, V>& kv)
//		{
//			if (Find(kv.first))
//			{
//				return false;
//			}
//
//			if ((double)_n / (double)_tables.size() >= 0.7)
//			{
//				// 获取素数表里比当前表大的下一个素数
//				size_t newSize = __stl_next_prime(_tables.size() + 1);
//				HashTable<K, V, Hash> newHT;
//				newHT._tables.resize(newSize);
//
//				for (size_t i = 0; i < _tables.size(); i++)
//				{
//					if (_tables[i]._state == EXIST)
//					{
//						newHT.Insert(_tables[i]._kv);
//					}
//				}
//				_tables.swap(newHT._tables);
//
//			}
//
//			Hash hs;
//
//			size_t hash0 = hs(kv.first) % _tables.size();
//			size_t i = 1;
//			size_t hashi = hash0;
//			while (_tables[hashi]._state == EXIST)
//			{
//				// 冲突探测
//				hashi = (hash0 + i) % _tables.size();
//				++i;
//			}
//
//			_tables[hashi]._kv = kv;
//			_tables[hashi]._state = EXIST;
//			_n++;
//			return true;
//		}
//
//		HashData<K, V>* Find(const K& key)
//		{
//			Hash hs;
//
//			size_t hash0 = hs(key) % _tables.size();
//			size_t hashi = hash0;
//			size_t i = 1;
//			while (_tables[hashi]._state != EMPTY)
//			{
//				if (_tables[hashi]._state == EXIST
//					&& _tables[hashi]._kv.first == key)
//				{
//					return &_tables[hashi];
//				}
//				// 
//				hashi = (hash0 + i) % _tables.size();
//				i++;
//			}
//			return nullptr;
//		}
//
//		bool Erase(const K& key)
//		{
//			HashData<K, V>* ret = Find(key);
//			if (ret == nullptr)
//			{
//				return false;
//			}
//			else
//			{
//				_n--;
//				ret->_state = DELETE;
//				return true;
//			}
//		}
//
//	private:
//		std::vector<HashData<K, V>> _tables;
//		size_t _n = 0; // 表中存储数据个数
//
//	};
//
//	void TestHT1()
//	{
//		HashTable<std::string, std::string> ht1;
//
//		ht1.Insert({ "1231", "21312" });
//		ht1.Insert({ "2131", "21312" });
//
//
//
//
//		/*for (size_t i = 0; i < 53; i++)
//		{
//			ht1.Insert({ rand(), i });
//		}*/
//	}
//}


namespace hash_bucket
{
	template<class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;
		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{}
	};

	template <class K>
	class HashFunc
	{
	public:
		size_t operator()(const K& s)
		{
			return (size_t)s;
		}
	};

	template<>
	class HashFunc<std::string>
	{
	public:
		size_t operator()(const std::string& s)
		{
			size_t hash = 0;
			for (auto ch : s)
			{
				hash += ch;
				hash *= 131;
			}
			return hash;
		}
	};

	// 前置声明，注意不能写默认参数
	template<class K, class T, class KeyOfT, class Hash>
	class HashTable;

	template<class K, class T, class Ref, class Ptr, class KeyOfT, class Hash>
	struct __HTIterator
	{

		typedef  HashNode<T> Node;
		typedef  HashTable<K, T, KeyOfT, Hash> HT;
		typedef __HTIterator<K, T, Ref, Ptr, KeyOfT, Hash> Self;

		Node* _node;
		const HT* _ht;

		__HTIterator(Node* node, const HT* ht)
			:_node(node)
			, _ht(ht)
		{}

		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &_node->_data;
		}

		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}

		bool operator==(const Self& s)
		{
			return _node == s._node;
		}

		Self& operator++()
		{
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				// 找下一个桶
				KeyOfT kot;
				Hash hs;
				size_t hashi = hs(kot(_node->_data)) % _ht->_tables.size();
				++hashi;
				while (hashi < _ht->_tables.size())
				{
					if (_ht->_tables[hashi])
					{
						_node = _ht->_tables[hashi];
						break;
					}
					else
					{
						++hashi;
					}
				}

				if (hashi == _ht->_tables.size())
				{
					_node = nullptr;
				}

				return *this;

			}
		}
	};

	template<class K, class T, class KeyOfT, class Hash = HashFunc<K>>
	class HashTable
	{
		template<class K, class T, class KeyOfT, class Ref, class Ptr, class Hash>
		friend struct __HTIterator;
		typedef HashNode<T> Node;

	public:
		typedef __HTIterator<K, T, T&, T*, KeyOfT, Hash> Iterator;
		typedef __HTIterator<K, T, const T&, const T*, KeyOfT, Hash> ConstIterator;

		Iterator Begin()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				if (cur)
				{
					return Iterator(cur, this);
				}
			}
			return End();
		}

		Iterator End()
		{
			return Iterator(nullptr, this);
		}

		ConstIterator Begin() const
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				if (cur)
				{
					return ConstIterator(cur, this);
				}
			}
			return End();
		}

		ConstIterator End() const
		{
			return ConstIterator(nullptr, this);
		}

		HashTable()
		{
			_tables.resize(__stl_next_prime(1), nullptr);
		}

		~HashTable()
		{
			// 依次把每个桶释放
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}

		// 获取素数表里比当前表大的下一个素数
		inline unsigned long __stl_next_prime(unsigned long n)
		{
			// Note: assumes long is at least 32 bits.
			static const int __stl_num_primes = 28;
			static const unsigned long __stl_prime_list[__stl_num_primes] =
			{
				53, 97, 193, 389, 769,
				1543, 3079, 6151, 12289, 24593,
				49157, 98317, 196613, 393241, 786433,
				1572869, 3145739, 6291469, 12582917, 25165843,
				50331653, 100663319, 201326611, 402653189, 805306457,
				1610612741, 3221225473, 4294967291
			};

			const unsigned long* first = __stl_prime_list;
			const unsigned long* last = __stl_prime_list + __stl_num_primes;
			const unsigned long* pos = std::lower_bound(first, last, n);
			return pos == last ? *(last - 1) : *pos;
		}

		std::pair<Iterator, bool> Insert(const T& data)
		{
			KeyOfT kot;

			Iterator it = Find(kot(data));

			if (it != End())
			{
				return { it, false };
			}

			Hash hs;


			// 负载因子到1就扩容
			if (_n == _tables.size())
			{
				size_t newSize = __stl_next_prime(_tables.size() + 1);
				std::vector<Node*> newTables(newSize, nullptr);
				for (size_t i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;

						size_t hashi = hs(kot(cur->_data)) % newSize;
						cur->_next = newTables[hashi];
						newTables[hashi] = cur;

						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newTables);
			}


			size_t hashi = hs(kot(data)) % _tables.size();
			Node* newnode = new Node(data);

			// 头插到桶里
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			_n++;
			return { Iterator(newnode, this), true };
		}

		Iterator Find(const K& key)
		{
			KeyOfT kot;
			Hash hs;
			size_t hashi = hs(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					return Iterator(cur, this);
				}
				cur = cur->_next;
			}
			return End();
		}

		bool Erase(const K& key)
		{
			Hash hs;
			size_t hashi = hs(key) % _tables.size();
			Node* cur = _tables[hashi];
			Node* prevnode = nullptr;
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (prevnode == nullptr)
					{
						_tables[hashi] = cur->_next;
					}
					else
					{
						prevnode->_next = cur->_next;
					}

					delete cur;
					_n--;
					return true;
				}
				prevnode = cur;
				cur = cur->_next;
			}
		}


	private:
		std::vector<Node*> _tables; // 指针数组
		size_t _n = 0;              // 表中存储数据个数
	};


	void TestHT1()
	{
		//HashTable<std::string, int> ht1;
		
		std::vector<std::string> a = { "we", "you", "you", "we", "I", "he", "she", "it" };

		//for (auto& s : a)
		//{
		//	ht1.Insert({ s , 0 });
		//}



		
		int x = 0;

	}

}