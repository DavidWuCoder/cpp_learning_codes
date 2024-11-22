#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <assert.h>

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

	template<class T>
	struct list_iterator
	{
		typedef list_node<T> Node;
		typedef list_iterator<T> Self;
		Node* _node;

		list_iterator(Node* node)
			:_node(node)
		{}
		T& operator*()
		{
			return _node->_data;
		}
		
		T* operator->()
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

	template<class T>
	class list
	{
		typedef list_node<T> Node;
	public:
		typedef list_iterator<T> iterator;

		iterator begin()
		{
			return (_head->_next);
		}

		iterator end()
		{
			return (_head);
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

		void push_back(const T& x)
		{
			Node* new_node = new Node(x);
			Node* tail = _head->_prev;

			new_node->_prev = tail;
			tail->_next = new_node;

			new_node->_next = _head;
			_head->_prev = new_node;
		}

	private:
		Node* _head;
	};
}