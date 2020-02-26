#include <iostream>

template <class T>
struct AVLTreeNode {
	AVLTreeNode* _pLeft;
	AVLTreeNode* _pRight;
	AVLTreeNode* _pParent;
	T _data;
	int _bf;	//平衡因子

	AVLTreeNode(const T& data) : _data(data)
		, _pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _bf(0) {}
};

//AVL: 二叉搜索树 + 平衡因子
template<class T>
class AVLTree {
public:
	typedef AVLTreeNode<T> Node;

	AVLTree() : _pRoot(nullptr) {}

	bool Insert(const T& data) {
		//树的第一个结点
		if (nullptr == _pRoot) {
			_pRoot = new Node(data);
			return true;
		}
		//1.按照二叉搜索树的规则插入

		// 找到二叉搜索树应该插入的位置
		Node* pCur = _pRoot;
		Node* pParent = nullptr;
		while (pCur) {
			pParent = pCur;
			if (data < pCur->_data) {
				pCur = pCur->_pLeft;
			} else if (data > pCur->_data) {
				pCur = pCur->_pRight;
			} else {
				return false;
			}
		}

		//插入新节点
		pCur = new Node(data);
		if (data < pParent->_data) {
			pParent->_pLeft = pCur;
		} else {
			pParent->_pRight = pCur;
		}
		pCur->_pParent = pParent;

		//更新pParent 的平衡因子
		while (pParent) {
			if (pCur == pParent->_pLeft)
				--pParent->_bf;
			else
				++pParent->_bf;

			//父节点高度没有变，就插入成功了
			if (0 == pParent->_bf)
				return true;
			else if (-1 == pParent->_bf || 1 == pParent->_bf) {	//父亲结点的父节点平衡因子也要变的，这就是结点结构体要保存父节点的原因，再更改上面的要循环上去，就是在循环里的原因
				pCur = pParent;
				pParent = pCur->_pParent;
			} else {	//双亲结点已经不满足AVL的性质了，对以双亲的为根的二叉树进行旋转
				if (2 == pParent->_bf) {
					//右子树高--->左单旋
					if (pCur->_bf == 1)
						RotateL(pParent);
					//
					else
						RotateRL(pParent);
				}
				else {
					//左子树高--->右单旋
					if (pCur->_bf == -1)
						RotateR(pParent);
					//
					else
						RotateLR(pParent);
				}
				//旋转之后就不需要再更新了，上面的高度还是那样
				break;
			}
		}
	}
private:
	Node* _pRoot;

	//右单旋
	void RotateR(Node* pParent) {
		// pSubL: pParent的左孩子
		// pSubLR: pParent左孩子的右孩子
		PNode pSubL = pParent->_pLeft;
		PNode pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;

		pSubL->_pRight = pParent;
		PNode pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;

		//把pParent的父结点赋给pSubL的父结点
		pSubL->_pParent = pPParent;
		//判断pParent是不是根节点
		if (NULL == pPParent) {
			_pRoot = pSubL;
			pSubL->_pParent = NULL;
		} else {
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}

		//更改平衡因子
		pParent->_bf = pSubL->_bf = 0;
	}

	//左单旋
	void RotateL(Node* pParent) {}

	//双旋：先左单旋在右单旋
	void RotateLR(Node* pParent) {
		PNode pSubL = pParent->_pLeft;
		PNode pSubLR = pSubL->_pRight;

		// 旋转之前，保存pSubLR的平衡因子，旋转完成之后，需要根据该平衡因子来调整其他节点的平衡因子
		int bf = pSubLR->_bf;

		RotateL(pParent->_pLeft);
		RotateR(pParent);

		//更改平衡因子, 因为左单旋和右单旋pParent和pSubL清零
		if (1 == bf)
			pSubL->_bf = -1;
		else if (-1 == bf)  //不能else，还有不需要更新的情况
			pParent->_bf = 1;
	}

	//先右单旋再左单旋
	void RotateRL(Node* pParent) {}
};