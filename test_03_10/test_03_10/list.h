#pragma once
namespace wyl
{
	template<class T>
	struct ListNode
	{
		ListNode<T>* _next;
		ListNode<T>* _prev;
		T _data;
		ListNode(const T& data = T())
			:_next(nullptr)
			, _prev(nullptr)
			, _data(data)
		{}
		ListNode(T&& data)
			:_next(nullptr)
			, _prev(nullptr)
			, _data(std::move(data))
		{}
		template<class... Args>
		ListNode(Args&&... args)
			:_next(nullptr)
			, _prev(nullptr)
			, _data(std::forward<Args>(args)...)
		{}
	};
	template<class T, class Ref, class Ptr>
	struct ListIterator
	{
		typedef ListNode<T> Node;
		typedef ListIterator<T, Ref, Ptr> Self;
		Node* _node;
		ListIterator(Node* node)
			:_node(node)
		{}
		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		Ref operator*()
		{
			return _node->_data;
		}
		bool operator!=(const Self& it)
		{
			return _node != it._node;
		}
	};
	template<class T>
	class list
	{
		typedef ListNode<T> Node;
	public:
		typedef ListIterator<T, T&, T*> iterator;
		typedef ListIterator<T, const T&, const T*> const_iterator;
		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
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
			insert(end(), x);
		}
		void push_back(T&& x)
		{
			insert(end(), move(x));
		}

		template<class... Args>
		void emplace_back(Args&&... args)
		{
			emplace(end(), std::forward<Args>(args)...);
		}

		iterator insert(iterator pos, const T& x)
		{
			Node* cur = pos._node;
			Node* newnode = new Node(move(x));
			Node* prev = cur->_prev;
			// prev newnode cur
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
			return iterator(newnode);
		}
		iterator insert(iterator pos, T && x)
		{
			Node* cur = pos._node;
			Node* newnode = new Node(move(x));
			Node* prev = cur->_prev;
			// prev newnode cur
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
			return iterator(newnode);
		}
		template<class... Args>
		iterator emplace(iterator pos, Args&&... args)
		{
			Node* cur = pos._node;
			Node* newnode = new Node(std::forward<Args>(args)...);
			Node* prev = cur->_prev;
			// prev newnode cur
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
			return iterator(newnode);
		}
	private:
		Node* _head;
	};
}
