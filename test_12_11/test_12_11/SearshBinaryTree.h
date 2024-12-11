#pragma once

template<class K>
class BSTNode
{
public:
	K _key;
	BSTNode<K>* _left = nullptr;
	BSTNode<K>* _right = nullptr;

	BSTNode(const K& key)
		:_key(key)
	{}
};


template<class K>
class BSTree
{
	typedef BSTNode<K> Node;

public:
	bool insert(const K& key)
	{
		if (_root == nullptr) {
			_root = new Node(key);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;

		while (cur)
		{
			parent = cur;
			if (cur->_key < key)
			{

				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key);
		if (parent->_key < key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
	}

	bool find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{

				return true;
			}
			return false;
		}
	}

	void Inorder()
	{
		_InOrder(_root);
		std::cout << std::endl;
	}



private:
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		std::cout << root->_key << ' ';
		_InOrder(root->_right);
	}

private:
	Node* _root = nullptr;
};