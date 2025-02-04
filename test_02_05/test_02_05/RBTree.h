#include <iostream>

#pragma once
// 枚举值表⽰颜⾊
enum Colour
{
	RED,
	BLACK
};
// 这⾥我们默认按key/value结构实现
template<class K, class V>
struct RBTreeNode
{
	// 这⾥更新控制平衡也要加⼊parent指针
	std::pair<K, V> _kv;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	Colour _col;
	RBTreeNode(const std::pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{}
};
template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	// 旋转代码的实现跟AVL树是⼀样的，只是不需要更新平衡因⼦
	bool Insert(const std::pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(kv);
		// 新增结点。颜⾊红⾊给红⾊
		cur->_col = RED;
		if (parent->_kv.first < kv.first)
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
		return true;
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

	Node* Find(const K& key)
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
				return cur;
			}
		}
		return nullptr;
	}

	bool Check(Node* root, int blackNum, const int refNum)
	{
		if (root == nullptr)
		{
			if (blackNum != refNum)
			{
				std::cout << "存在⿊⾊结点的数量不相等的路径" << std::endl;
				return false;
			}
			return true;
		}

		if (root->_col == RED && root->_parent->_col == RED)
		{
			std::cout << root->_kv.first << "存在连续的红⾊结点" << std::endl;
			return false;
		}

		if (root->_col == BLACK)
		{
			blackNum++;
		}

		return Check(root->_left, blackNum, refNum) && Check(root->_right, blackNum, refNum);

	}

	bool IsBalance()
	{
		if (_root == nullptr)
		{
			return true;
		}
		if (_root->_col == RED)
		{
			std::cout << "根节点为红色" << std::endl;
			return false;
		}

		int refNum = 0;

		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				refNum++;
			}
			cur = cur->_left;
		}
		return Check(_root, 0, refNum);
	}

	void InOrder()
	{
		_inorder(_root);
		std::cout << std::endl;
	}

	int Size()
	{
		return _size(_root);
	}

	int Height()
	{
		return _height(_root);
	}

private:
	Node* _root = nullptr;

	void _inorder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_inorder(root->_left);
		std::pair<K, V> kv = root->_kv;
		std::cout << kv.first << " : " << kv.second << std::endl;
		_inorder(root->_right);
	}

	int _height(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}

		int LeftHeight = _height(root->_left);
		int RightHeight = _height(root->_right);

		return LeftHeight > RightHeight ? LeftHeight + 1 : RightHeight + 1;

	}

	int _size(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		return _size(root->_left) + _size(root->_right) + 1;
	}
};