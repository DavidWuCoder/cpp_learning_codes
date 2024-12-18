#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <assert.h>
#include <algorithm>

namespace wyl {
	template<class T>
	struct list_node
	{
		T _data;
		list_node<T>* _next;
		list_node<T>* _prev;

		list_node(const T& x = T())
			:_data(x)
			, _next(nullptr)
			, _prev(nullptr)
		{}
	};

	template<class T, class Ref, class Ptr>
	struct list_iterator
	{
		typedef list_node<T> Node;
		typedef list_iterator<T, Ref, Ptr> Self;
		Node* _node;

		list_iterator(Node* node)
			:_node(node)
		{}
		Ref operator*()
		{
			return _node->_data;
		}
		
		Ptr operator->()
		{
			return &_node->_data;
		}

		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		Self operator++(int)
		{
			Self tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		Self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		Self& operator--(int)
		{
			Self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}

		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}
	};

	//template<class T>
	//struct list_const_iterator
	//{
	//	typedef list_node<T> Node;
	//	typedef list_const_iterator<T> Self;
	//	Node* _node;

	//	list_const_iterator(Node* node)
	//		:_node(node)
	//	{}
	//	const T& operator*()
	//	{
	//		return _node->_data;
	//	}

	//	const T* operator->()
	//	{
	//		return &_node->_data;
	//	}

	//	Self& operator++()
	//	{
	//		_node = _node->_next;
	//		return *this;
	//	}

	//	Self operator++(int)
	//	{
	//		Self tmp(*this);
	//		_node = _node->_next;
	//		return tmp;
	//	}

	//	Self& operator--()
	//	{
	//		_node = _node->_prev;
	//		return *this;
	//	}

	//	Self& operator--(int)
	//	{
	//		Self tmp(*this);
	//		_node = _node->_prev;
	//		return tmp;
	//	}

	//	bool operator!=(const Self& s)
	//	{
	//		return _node != s._node;
	//	}
	//};

	template<class T>
	class list
	{
		typedef list_node<T> Node;
	public:
		//typedef list_iterator<T> iterator;
		//typedef list_const_iterator<T> const_iterator;

		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}

		void empty_init()
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
		}
		list()
		{
			empty_init();
		}

		list(size_t n, const T& val = T())
		{
			empty_init();
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}

		// lt2(lt1)
		list(const list<T>& lt)
		{
			empty_init();
			for (auto& e : lt)
			{
				push_back(e);
			}
		}

		list<T>& operator=(list<T> lt)
		{
			swap(lt);
			return *this;

		}

		void swap(list<T>& tmp)
		{
			std::swap(_head, tmp._head);
		}

		~list()
		{
			clear();
			delete _head;
			_head = nullptr; 
		}

		void clear()
		{
			auto it = begin();
			while (it != end())
			{
				it = erase(it);
			}

		}

		iterator insert(iterator pos, const T& val)
		{
			Node* cur = pos._node;
			Node* newnode = new Node(val);
			Node* pre = cur->_prev;

			pre->_next = newnode;
			newnode->_prev = pre;

			newnode->_next = cur;
			cur->_prev = newnode;

			return iterator(newnode);
		}

		iterator erase(iterator pos)
		{
			assert(pos != end());
			Node* del = pos._node;
			Node* pre = del->_prev;
			Node* next = del->_next;
			
			pre->_next = next;
			next->_prev = pre;

			delete del;

			return iterator(next);
		}

		void push_back(const T& x)
		{
			//Node* new_node = new Node(x);
			//Node* tail = _head->_prev;

			//new_node->_prev = tail;
			//tail->_next = new_node;

			//new_node->_next = _head;
			//_head->_prev = new_node;

			insert(end(), x);
		}

		void push_front(const T& x)
		{
			//Node* new_node = new Node(x);
			//Node* second = _head->_next;

			//new_node->_next = second;
			//second->_prev = new_node;

			//new_node->_prev = _head;
			//_head->_next = new_node;

			insert(begin(), x);
		}

		void pop_front()
		{
			erase(begin());
		}

		void pop_back()
		{
			erase(--end());
		}

	private:
		Node* _head;
	};
}