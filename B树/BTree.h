#pragma once
#include <vector>

template<class K, int M = 3>
struct BTreeNode {
	// 为了方便插入以后再分裂，实际这里我们多给了一个空间,节点中还是只能存M-1个关键字
	K _keys[M];			     
	BTreeNode<K, M>* _subs[M + 1];
	BTreeNode<K, M>* _parent;
	size_t       _keysize;           // 记录关键字的数量

	BTreeNode() {
		for (size_t i = 0; i < M + 1; ++i)
			_subs[i] = nullptr;

		_parent = nullptr;
		_keysize = 0;
	}
};

template<class K, int M>
class BTree {
	typedef BTreeNode<K, M> Node;
public:
	pair<Node*, int> Find(const K& key) {
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			int i = 0;
			while (i < cur->_keysize) {
				if (key < cur->_keys[i]) {		// 当前关键字小，就到他的左孩子去找 
					break;
				} else if (key > cur->_keys[i]) {	// 当前关键字大，继续跟下一个关键比较
					++i;               
				} else {
					return make_pair(cur, i);
				}
			}

			parent = cur;
			cur = cur->_subs[i];
		}

		return make_pair(parent, -1);
	}

	void InsertKey(Node* node, const K& key, Node* child) {
		int end = node->_keysize - 1;
		while (end >= 0 && node->_keys[end] > key) {
			node->_keys[end + 1] = node->_keys[end];
			node->_subs[end + 2] = node->_subs[end+1];
			--end;
		}

		node->_keys[end + 1] = key;
		node->_subs[end + 2] = child;
		if (child)
			child->_parent = node;

		node->_keysize++;
	}

	bool Insert(const K& key) {
		if (_root == nullptr) {
			_root = new Node;
			_root->_keys[0] = key;
			_root->_keysize = 1;
			return true;
		}

		pair<Node*, int> ret = Find(key);
		if (ret.second != -1) {
			return false;
		}

		Node* node = ret.first;
		K k = key;
		Node* child = nullptr;
		// 下面循环迭代逻辑是往node中插入k和child
		while (1) {
			InsertKey(node, k, child);
			if (node->_keysize < M) {
				return true;
			} else {
				// 如果node->_keysize == M,则说明节点满了，需要分裂处理
				int mid = M / 2;
				// 将右半区间分裂拷贝新节点中，注意除了拷贝关键字还要拷贝孩纸
				Node* newnode = new Node;
				int j = 0;
				int i = mid + 1;
				for (; i < M;) {
					newnode->_keys[j] = node->_keys[i];
					newnode->_subs[j] = node->_subs[i];
					if (node->_subs[i])
						node->_subs[i]->_parent = newnode;

					node->_keys[i] = K();
					node->_subs[i] = nullptr;

					newnode->_keysize++;
					++j;
					++i;
				}
				
				newnode->_subs[j] = node->_subs[i];
				if (node->_subs[i])
					node->_subs[i]->_parent = newnode;
				node->_subs[i] = nullptr;

				node->_keysize -= (newnode->_keysize + 1);

				// node节点的parent如果是空，则产生新的根
				if (node->_parent == nullptr) {
					_root = new Node;
					_root->_keys[0] = node->_keys[mid];
					_root->_subs[0] = node;
					_root->_subs[1] = newnode;
					node->_parent = newnode->_parent = _root;
					_root->_keysize = 1;

					node->_keys[mid] = K();

					return true;
				} else {
					// 迭代转换成往的node节点parent中去插入一个node->key[mid] 和 newnode
					k = node->_keys[mid];
					child = newnode;

					node->_keys[mid] = K();

					node = node->_parent;
				}
			}
		}

		return true;
	}

	void _InOrder(Node* cur) {
		if (cur == nullptr) {
			return;
		}

		int i = 0;
		while (i < cur->_keysize) {
			_InOrder(cur->_subs[i]);
			cout << cur->_keys[i] << " ";
			++i;
		}

		_InOrder(cur->_subs[i]);
	}

	void InOrder() {
		_InOrder(_root);
		cout << endl;
	}

private:
	Node* _root = nullptr;
};

void TestBTree() {
	/*int a[] = { 53, 139, 75, 49, 145, 36, 101 };
	BTree<int, 3> t;
	for (auto e : a)
	{
		t.Insert(e);
	}
	t.InOrder();*/


	const size_t n = 10000;
	vector<int> v;
	for (size_t i = 0; i < n; ++i) {
		v.push_back(rand());
	}

	BTree<int, 1024> t;
	for (auto e : v) {
		t.Insert(e);
	}

	t.InOrder();
}