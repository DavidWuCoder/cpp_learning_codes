#pragma once
#include <iostream>
#include <assert.h>

template<class K, class V>
struct AVLTreeNode
{
	// 需要parent指针，后续更新平衡因⼦可以看到
	std::pair<K, V> _kv;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf; // balance factor
	AVLTreeNode(const std::pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	bool Insert(const std::pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		// 插入与二叉搜索树相同
		// 需要记录父节点
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
				// 相等说明该节点已存在
				// 我们维护的一种键值对的树，规定键是唯一的
				// 因此，这种情况认为插入失败
				return false;
			}
		}

		cur = new Node(kv);
		if (parent->_kv.first > cur->_kv.first)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;
		// 至此新增节点被插入

		// 更新平衡因子
		while (parent)
		{
			// 先更新父节点的平衡因子
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}

			// 分情况讨论
			if (parent->_bf == 0)
			{
				// 无需再向上更新
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				// 继续向上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					// 左单旋
					RotateL(parent);

				}
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					// 右单旋
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					// 右左双旋
					RotateRL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					// 左右双旋
					RotateLR(parent);
				}
				break;
			}
			else
			{
				// 平衡因子为其他值直接报警
				assert(false);
			}
		}
		return true;
	}
	
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		// 除了要修改孩子指针，还要修改父亲指针
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		Node* grandparent = parent->_parent;
		
		subL->_right = parent;
		parent->_parent = subL;

		if (grandparent == nullptr)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parent == grandparent->_left)
			{
				grandparent->_left = subL;
				subL->_parent = grandparent;
			}
			else
			{
				grandparent->_right = subL;
				subL->_parent = grandparent;

			}
		}

		parent->_bf = subL->_bf = 0;
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL) {
			subRL->_parent = parent;
		}

		Node* grandparent = parent->_parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (grandparent == nullptr)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (parent == grandparent->_left) {
				grandparent->_left = subR;
				subR->_parent = grandparent;
			}
			else
			{
				grandparent->_right = subR;
				subR->_parent = grandparent;
			}
		}
		parent->_bf = subR->_bf = 0;
	}

	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(subL);
		RotateR(parent);

		if (bf == 0)
		{
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else
		{
			assert(false);
		}

	}

	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(subR);
		RotateL(parent);

		if (bf == 0)
		{
			parent->_bf = 0;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else
		{
			assert(false);
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

	int Height()
	{
		return _Height(_root);
	}

	bool IsBalanceTree()
	{
		return _IsBalance(_root);
	}

	int Size()
	{
		return _size(_root);
	}

	void InOrder()
	{
		_Inorder(_root);
		std::cout << std::endl;
	}

private:
	Node* _root = nullptr;

	int _Height(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		int lefth = _Height(root->_left);
		int righth = _Height(root->_right);

		return lefth > righth ? lefth + 1 : righth + 1;
	}

	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
		{
			return true;
		}
		int lefth = _Height(root->_left);
		int righth = _Height(root->_right);
		int diff = righth - lefth;

		if (std::abs(diff) >= 2)
		{
			std::cout << "高度差异常" << std::endl;
			return false;
		}

		if (root->_bf != diff)
		{
			std::cout << "平衡因子异常" << std::endl;
			return false;
		}

		return _IsBalance(root->_left) && _IsBalance(root->_right);
	}

	int _size(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		
		return _size(root->_left) + _size(root->_right) + 1;
	}

	void _Inorder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_Inorder(root->_left);
		std::cout << root->_kv.first << " : " << root->_kv.second << " ";
		_Inorder(root->_right);
	}
};