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
	pair<K, V> _kv;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	Colour _col;
	RBTreeNode(const pair<K, V>& kv)
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
	Node* _root = nullptr;

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
		cur->_col = RED;
		if (kv.first < parent->_kv.first)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;
		

		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				//   g
				//  p u
				//   
				Node* uncle = grandfather->_right;

				// 叔叔存在且为红
				if (uncle && uncle->_col == RED) 
				{
					// 变色
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;

					// 继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				// 叔叔不存在或者存在且为黑
				else
				{
					if (cur == parent->_left) {
						// 旋转 + 变色
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						RotateL(parent);
						RotateR(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				// 叔叔存在且为红
				if (uncle && uncle->_col == RED)
				{
					// 变色
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;

					// 继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				// 叔叔不存在或者存在且为黑
				else
				{
					if (cur == parent->_right) {
						// 旋转 + 变色
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						RotateR(parent);
						RotateL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
		}
		_root->_col = BLACK;
	}

	void InOrder()
	{
		_InOrder(_root);
		std::cout << std::endl;
	}

	bool Check(Node* root, int blackNum, const int refNum)
	{
		if (root == nullptr)
		{
			// 前序遍历⾛到空时，意味着⼀条路径⾛完了
			//cout << blackNum << endl;
			if (refNum != blackNum)
			{
				cout << "存在⿊⾊结点的数量不相等的路径" << endl;
				return false;
			}
			return true;
		}
		// 检查孩⼦不太⽅便，因为孩⼦有两个，且不⼀定存在，反过来检查⽗亲就⽅便多了
		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << root->_kv.first << "存在连续的红⾊结点" << endl;
			return false;
		}
		if (root->_col == BLACK)
		{
			blackNum++;
		}
		return Check(root->_left, blackNum, refNum)
			&& Check(root->_right, blackNum, refNum);
	}

	bool IsBalance()
	{
		if (_root == nullptr)
			return true;
		if (_root->_col == RED)
			return false;
		// 参考值
		int refNum = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				++refNum;
			}
			cur = cur->_left;
		}
		return Check(_root, 0, refNum);
	}
	int Size()
	{
		return _Size(_root);
	}

	int Height()
	{
		return _Height(_root);
	}
private:

	int _Size(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		else
		{
			return _Size(root->_left) + _Size(root->_right) + 1;
		}
	}

	int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		// 注意还要修改parent
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
		// 注意还要修改parent
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

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		std::cout << root->_kv.first << ':' << root->_kv.second << '\n';
		_InOrder(root->_right);
	}


};


// 测试代码
void TestRBTree1()
{
	RBTree<int, int> t;
	// 常规的测试⽤例
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	// 特殊的带有双旋场景的测试⽤例
	//int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto e : a)
	{
		t.Insert({ e, e });
	}
	t.InOrder();
	std::cout << t.IsBalance() << '\n';
	//std::cout << t.IsBalanceTree() << std::endl;
}

// 插⼊⼀堆随机值，测试平衡，顺便测试⼀下⾼度和性能等
void TestRBTree2()
{
	const int N = 1000000;
	vector<int> v;
	v.reserve(N);
	srand(time(0));
	for (size_t i = 0; i < N; i++)
	{
		v.push_back(rand() + i);
	}
	size_t begin2 = clock();

	RBTree<int, int> t;
	for (auto e : v)
	{
		t.Insert(make_pair(e, e));
	}

	size_t end2 = clock();

	cout << t.IsBalance() << endl;
	cout << "Insert:" << end2 - begin2 << endl;
	cout << "Height:" << t.Height() << endl;
	cout << "Size:" << t.Size() << endl;
}