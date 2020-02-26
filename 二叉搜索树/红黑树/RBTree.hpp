#pragma once
#include <iostream>
using namespace std;

#if 0
template <class T>
void swap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}
#endif

enum COLOR {
	RED, BLACK
};

template <class T>
struct RBTreeNode {
	RBTreeNode<T>* _pLeft;
	RBTreeNode<T>* _pRight;
	RBTreeNode<T>* _pParent;
	T _data;
	int _color;

	//默认给成红色，红色只有一种情况会破坏性质限制
	RBTreeNode(const T& data = T(), COLOR color = RED) 
		: _pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _data(data)
		, _color(color) {}
};

template <class T>
class RBTree {
public:
	typedef RBTreeNode<T> Node;

	RBTree() {
		_pHead = new Node();
		_pHead->_pParent = nullptr;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}

	bool Insert(const T& data) {
		//先按照二叉搜索树的方式插入结点
		Node*& pRoot = GetRoot();
		if (nullptr == pRoot) {
			pRoot = new Node(data, BLACK);
			pRoot->_pParent = _pHead;
			_pHead->_pLeft = pRoot;
			_pHead->_pRight = pRoot;
			return true;
		}

		//按照二叉搜索树的规则找待插结点在红黑树中的位置
		Node* pCur = pRoot;
		Node* pParent = nullptr;
		while (pCur) {
			pParent = pCur;
			if (data < pCur->_data)
				pCur = pCur->_pLeft;
			else if (data > pCur->_data)
				pCur = pCur->_pRight;
			else
				return false;
		}

		//插入新节点
		pCur = new Node(data);
		if (data < pParent->_data)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;
		pCur->_pParent = pParent;

		//检测是否满足红黑树的性质---检测性质3：不能有连在一起的红色结点
		//如果pParent结点为红色则违反性质3
		while (pParent != _pHead && RED == pParent->_color) {
			Node* grandFather = pParent->_pParent;

			//父亲结点在祖先结点的左子树
			if (pParent == grandFather->_pLeft) {
				Node* uncle = grandFather->_pRight;
				//情况1：叔叔结点存在且为红
				if (uncle && uncle->_color == RED) {
					pParent->_color = BLACK;
					uncle->_color = BLACK;
					grandFather->_color = RED;

					pCur = grandFather;
					pParent = pCur->_pParent;
				}
				else {	//叔叔结点不存在 || 叔叔结点存在&&黑色
				 //情况三：变为情况二
					if (pCur == pParent->_pRight) {
						RotateL(pParent);
						swap(pParent, pCur);
					}
					//情况二：
					pParent->_color = BLACK;
					grandFather->_color = RED;
					RotateR(grandFather);

				}
			}

			//父亲结点在祖先结点的右子树
			else {
				Node* uncle = grandFather->_pLeft;
				if (uncle && uncle->_color == RED) {
					pParent->_color = BLACK;
					uncle->_color = BLACK;
					grandFather->_color = RED;

					pCur = grandFather;
					pParent = pCur->_pParent;
				}
				else { //情况二和情况三
				 //情况三
					if (pCur == pParent->_pLeft) {
						RotateR(pParent);
						swap(pParent, pCur);
					}

					//情况二：
					pParent->_color = BLACK;
					grandFather->_color = RED;
					RotateL(grandFather);
				}
			}
		}
		//可能把根结点改成红的了
		pRoot->_color = BLACK;

		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return true;
	}

	void InOrder() {
		_InOrder(GetRoot());
	}

	//判断该树是不是红黑树
	bool IsValidRBTree() {
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return true;

		//验证性质2
		if (pRoot->_color != BLACK) {
			cout << "违反性质2:根节点不是黑色" << endl;
			return false;
		}

		//验证性质4
		//获取一条路径中黑色结点的个数
		size_t blackCount = 0;
		Node* pCur = pRoot;
		while (pCur) {
			if (pCur->_color == BLACK)
				blackCount++;

			pCur = pCur->_pLeft;
		}

		size_t pathCount = 0;
		return _IsValidRBTree(pRoot, blackCount, pathCount);
	}

	bool _IsValidRBTree(Node* pRoot, size_t blackCount, size_t pathCount) {
		if (nullptr == pRoot)
			return true;

		if (pRoot->_color == BLACK)
			++pathCount;

		//验证性质3
		Node* pParent = pRoot->_pParent;
		if (pParent != _pHead && pParent->_color == RED && pRoot->_color == RED) {
			cout << "违法性质3：存在连在一起的红色结点" << endl;
			return false;
		}

		if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight) {
			if (blackCount != pathCount) {
				cout << "违反性质4：路径中黑色结点个数不相同" << endl;
				return false;
			}
		}

		return _IsValidRBTree(pRoot->_pLeft, blackCount, pathCount) &&
			_IsValidRBTree(pRoot->_pRight, blackCount, pathCount);
	}

private:
	Node* _pHead;

	Node*& GetRoot() {
		return _pHead->_pParent;
	}

	//获取最左结点
	Node* LeftMost() {
		Node* pCur = GetRoot();
		if (pCur == nullptr)
			return _pHead;

		while (pCur->_pLeft)
			pCur = pCur->_pLeft;
		return pCur;
	}

	//获取最右结点
	Node* RightMost() {
		Node* pCur = GetRoot();
		if (nullptr == pCur)
			return _pHead;

		while (pCur->_pLeft)
			pCur = pCur->_pLeft;
		return pCur;
	}

	void RotateL(Node* pParent) {
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;

		pSubR->_pLeft = pParent;
		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubR;

		//把这部分树的上面结点赋给新的父节点
		pSubR->_pParent = pPParent;
		//判断上面还有没有结点了
		if (pPParent == _pHead) {	//已经是根了
			_pHead->_pParent = pSubR;
		}
		else {
			//判断处理这部分的数是在上面结点的左还是右
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
	}

	void RotateR(Node* pParent) {
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;

		pSubL->_pRight = pParent;
		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;

		pSubL->_pParent = pPParent;
		if (pPParent == _pHead) {
			_pHead->_pParent = pSubL;
		}
		else {
			//判断处理这部分的数是在上面结点的左还是右
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
	}

	void _InOrder(Node* pRoot) {
		if (pRoot) {
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}
};
