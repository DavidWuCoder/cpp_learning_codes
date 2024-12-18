//#pragma once
//
//template<class K>
//class BSTNode
//{
//public:
//	K _key;
//	BSTNode<K>* _left = nullptr;
//	BSTNode<K>* _right = nullptr;
//
//	BSTNode(const K& key)
//		:_key(key)
//	{}
//};
//
//
//template<class K>
//class BSTree
//{
//	typedef BSTNode<K> Node;
//
//public:
//	bool insert(const K& key)
//	{
//		if (_root == nullptr) {
//			_root = new Node(key);
//			return true;
//		}
//
//		Node* parent = nullptr;
//		Node* cur = _root;
//
//		while (cur)
//		{
//			parent = cur;
//			if (cur->_key < key)
//			{
//
//				cur = cur->_right;
//			}
//			else if (cur->_key > key)
//			{
//				cur = cur->_left;
//			}
//			else
//			{
//				return false;
//			}
//		}
//		cur = new Node(key);
//		if (parent->_key < key)
//		{
//			parent->_right = cur;
//		}
//		else
//		{
//			parent->_left = cur;
//		}
//		return false;
//	}
//
//	bool find(const K& key)
//	{
//		Node* cur = _root;
//		while (cur)
//		{
//			if (cur->_key < key)
//			{
//				cur = cur->_right;
//			}
//			else if (cur->_key > key)
//			{
//				cur = cur->_left;
//			}
//			else
//			{
//
//				return true;
//			}
//			return false;
//		}
//	}
//
//	void Inorder()
//	{
//		_InOrder(_root);
//		std::cout << std::endl;
//	}
//
//	bool Erase(const K& key)
//	{
//		// 这里得带父节点的查找
//		Node* parent = nullptr;
//		Node* cur = _root;
//
//		while (cur)
//		{
//
//			if (cur->_key < key)
//			{
//				parent = cur;
//				cur = cur->_right;
//			}
//			else if (cur->_key > key)
//			{
//				parent = cur;
//
//				cur = cur->_left;
//			}
//			else
//			{
//				if (cur->_left == nullptr)
//				{
//					if (parent == nullptr)
//					{
//						_root = cur->_right;
//					}
//					else
//					{
//						if (parent->_left == cur)
//						{
//							parent->_left = cur->_right;
//						}
//						else
//						{
//							parent->_right = cur->_right;
//						}
//					}
//					delete cur;
//
//				}
//				else if (cur->_right == nullptr)
//				{
//					if (parent == nullptr)
//					{
//						_root = cur->_left;
//					}
//					else
//					{
//						if (parent->_left == cur)
//						{
//							parent->_left = cur->_left;
//						}
//						else
//						{
//							parent->_right = cur->_left;
//						}
//					}
//					delete cur;
//				}
//				else
//				{
//					// 找右子树的最小节点
//					Node* minRight = cur->_right;
//					Node* minRightParent = cur;
//					while (minRight->_left)
//					{
//						minRightParent = minRight;
//						minRight = minRight->_left;
//					}
//
//					cur->_key = minRight->_key;
//
//					if (minRightParent->_left == minRight)
//					{
//						minRightParent->_left = nullptr;
//					}
//					else
//					{
//						minRightParent->_right = minRight->_right;
//					}
//					delete minRight;
//
//				}
//				return true;
//			}
//		}
//
//
//		return false;
//	}
//
//private:
//	void _InOrder(Node* root)
//	{
//		if (root == nullptr)
//		{
//			return;
//		}
//		_InOrder(root->_left);
//		std::cout << root->_key << ' ';
//		_InOrder(root->_right);
//	}
//
//private:
//	Node* _root = nullptr;
//};


#pragma once

template<class K, class V>
class BSTNode
{
public:
	K _key;
	V _value;
	BSTNode<K, V>* _left = nullptr;
	BSTNode<K, V>* _right = nullptr;

	BSTNode(const K& key, const V& value)
		:_key(key)
		,_value(value)
	{}
};


template<class K, class V>
class BSTree
{
	typedef BSTNode<K, V> Node;

public:
	bool Insert(const K& key, const V& value)
	{
		if (_root == nullptr) {
			_root = new Node(key, value);
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
		cur = new Node(key, value);
		if (parent->_key < key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		return false;
	}

	Node* Find(const K& key)
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
				return cur;
			}
		}
		return nullptr;
	}

	void InOrder()
	{
		_InOrder(_root);
		std::cout << std::endl;
	}

	bool Erase(const K& key)
	{
		// 这里得带父节点的查找
		Node* parent = nullptr;
		Node* cur = _root;

		while (cur)
		{

			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;

				cur = cur->_left;
			}
			else
			{
				if (cur->_left == nullptr)
				{
					if (parent == nullptr)
					{
						_root = cur->_right;
					}
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;
						}
					}
					delete cur;

				}
				else if (cur->_right == nullptr)
				{
					if (parent == nullptr)
					{
						_root = cur->_left;
					}
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}
					delete cur;
				}
				else
				{
					// 找右子树的最小节点
					Node* minRight = cur->_right;
					Node* minRightParent = cur;
					while (minRight->_left)
					{
						minRightParent = minRight;
						minRight = minRight->_left;
					}

					cur->_key = minRight->_key;

					if (minRightParent->_left == minRight)
					{
						minRightParent->_left = nullptr;
					}
					else
					{
						minRightParent->_right = minRight->_right;
					}
					delete minRight;

				}
				return true;
			}
		}


		return false;
	}

private:
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		std::cout << root->_key << ':' << root->_value << '\n';
		_InOrder(root->_right);
	}

private:
	Node* _root = nullptr;
};