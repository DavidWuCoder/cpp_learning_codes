#include <iostream>
#pragma once
// 枚举值表⽰颜⾊
enum Colour
{
	RED,
	BLACK
};
// 这⾥我们默认按key/value结构实现
template<class T>
struct RBTreeNode
{
	// 这⾥更新控制平衡也要加⼊parent指针
	T _data;
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	Colour _col;
	RBTreeNode(const T& data)
		:_data(data)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{}
};

template<class T, class Ref, class Ptr>
struct RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T, Ref, Ptr> Self;
	Node* _node;
	Node* _root;
	RBTreeIterator(Node* node, Node* root)
		:_node(node)
		,_root(root)
	{}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &_node->_data;
	}

	T* operator()()
	{
		return &_node->_data;
	}

	Self& operator++()
	{
		if (_node->_right)
		{
			Node* minleft = _node->_right;

			while (minleft->_left)
			{
				minleft = minleft->_left;
			}

			_node = minleft;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_right)
			{
				cur = parent;
				parent = parent->_parent;
			}
			_node = parent;
		}

		return *this;
	}

	Self& operator--()
	{
		if (_node == nullptr) // end()
		{
			// --end()，特殊处理，⾛到中序最后⼀个结点，整棵树的最右结点
			Node* rightMost = _root;
			while (rightMost && rightMost->_right)
			{
				rightMost = rightMost->_right;
			}
			_node = rightMost;
		}
		else if (_node->_left)
		{
			// 左⼦树不为空，中序左⼦树最后⼀个
			Node* rightMost = _node->_left;
			while (rightMost->_right)
			{
				rightMost = rightMost->_right;
			}
			_node = rightMost;
		}
		else
		{
			// 孩⼦是⽗亲右的那个祖先
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_left)
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;
		}
		return *this;
	}
	
	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}
};


template<class K, class T, class KeyofT>
class RBTree
{
	typedef RBTreeNode<T> Node;
	Node* _root = nullptr;
public:
	typedef RBTreeIterator<T, T&, T*> Iterator;
	typedef RBTreeIterator<T, const T&, const T*> ConstIterator;

	Iterator Begin() 
	{
		Node* cur = _root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}

		return Iterator(cur, _root);
	}

	Iterator End() 
	{
		return Iterator(nullptr, _root);
	}

	ConstIterator Begin() const
	{
		Node* cur = _root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}

		return ConstIterator(cur, _root);
	}

	ConstIterator End() const
	{
		return ConstIterator(nullptr, _root);
	}

	~RBTree()
	{
		Destroy(_root);
		_root = nullptr;
	}

	// 旋转代码的实现跟AVL树是⼀样的，只是不需要更新平衡因⼦
	std::pair<Iterator, bool> Insert(const T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return std::make_pair(Iterator(_root, _root), true);
		}

		KeyofT kot;
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kot(cur->_data) < kot(data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kot(cur->_data) > kot(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return std::make_pair(Iterator(cur, _root), false);
			}
		}
		cur = new Node(data);
		Node* newnode = cur;
		// 新增结点。颜⾊红⾊给红⾊
		cur->_col = RED;
		if (kot(parent->_data) < kot(data))
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		cur->_parent = parent;

		while (parent && parent->_col == RED)
		{
			Node* grandparent = parent->_parent;

			if (parent == grandparent->_left)
			{
				Node* uncle = grandparent->_right;

				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandparent->_col = RED;

					cur = grandparent;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						//        g 
						//     p    u   
						//   c
						RotateR(grandparent);
						parent->_col = BLACK;
						grandparent->_col = RED;
					}
					else
					{
						RotateL(parent);
						RotateR(grandparent);

						cur->_col = BLACK;
						grandparent->_col = RED;
					}
					break;
				}
			}
			else
			{
				Node* uncle = grandparent->_left;

				if (uncle && uncle->_col == RED) {
					//   g
					// u   p
					//      c
					uncle->_col = parent->_col = BLACK;
					grandparent->_col = RED;

					cur = grandparent;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_right)
					{
						RotateL(grandparent);

						parent->_col = BLACK;
						grandparent->_col = RED;
					}
					else
					{
						RotateR(parent);
						RotateL(grandparent);

						cur->_col = BLACK;
						grandparent->_col = RED;
					}
					break;
				}
			}
		}

		_root->_col = BLACK;
		return std::make_pair(Iterator(newnode, _root), true);

	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}

		Node* parentParent = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (parentParent == nullptr)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parent == parentParent->_left)
			{
				parentParent->_left = subL;
			}
			else
			{
				parentParent->_right = subL;
			}
			subL->_parent = parentParent;
		}
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}

		Node* parentParent = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;

		if (parentParent == nullptr)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (parent == parentParent->_left)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}
			subR->_parent = parentParent;
		}
	}

	Iterator Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key)
			{
				cur = cur->_right;
			}
			else if (cur->_kv.first > key)
			{
				cur = cur->_left;
			}
			else
			{
				return Iterator(cur, _root);
			}
		}
		return End();
	}

	void Destroy(Node* root)
	{
		if (root == nullptr)
			return;
		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
	}

};