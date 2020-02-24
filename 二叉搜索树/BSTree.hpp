#pragma once
#include <iostream>
using namespace std;

//BSTree --> binary search tree

template <class T>
struct BSTreeNode {
	T _data;
	BSTreeNode<T>* _pLeft;
	BSTreeNode<T>* _pRight;
	BSTreeNode(const T& data = T()) : _pLeft(nullptr),
		_pRight(nullptr),
		_data(data) {}
};

template <class T> 
class BSTree {
	typedef BSTreeNode<T> Node;
public:
	BSTree() : _pRoot(nullptr) {}

	~BSTree() {
		_Destroy(_pRoot);
	}

	Node* find(const T& data) {
		Node* pCur = _pRoot;
		while (pCur) {
			if (data == pCur->_data) {
				return pCur;
			} else if (data < pCur->_data) {
				pCur = pCur->_pLeft;
			} else {
				pCur = pCur->_pRight;
			}
		}
		return nullptr;
	}

	bool Insert(const T& data) {
		if (nullptr == _pRoot ) {
			_pRoot = new Node(data);
			return true;
		}

		//非空
		//找当前结点在二叉搜索树中的位置
		Node* pCur = _pRoot;
		Node* pParent = nullptr;	
		while (pCur) {
			//当pCur为空，则记录pCur的父节点
			pParent = pCur;		//保护父节点	
			if (data < pCur->_data) {
				pCur = pCur->_pLeft;
			} else if (data > pCur->_data) {
				pCur = pCur->_pRight;
			} else {
				return false;
			}
		}

		//插入结点
		pCur = new Node(data);
		if (data > pParent->_data) {
			pParent->_pRight = pCur;
		} else {
			pParent->_pLeft = pCur;
		}
		return true;
	}

	bool Erase(const T& data) {
		//找data在二叉搜索树的位置
		Node* pCur = _pRoot;
		Node* pParent = nullptr;
		while (pCur) {
			if (data < pCur->_data) {
				pParent = pCur;
				pCur = pCur->_pLeft;
			} else if (data > pCur->_data) {
				pParent = pCur;
				pCur = pCur->_pRight;
			} else {
				break;
			}
		}
		if (nullptr == pCur) {
			return false;
		}
		//删除结点
		/*
		 * 1. 没有孩子	2.只有左孩子	3.只有右孩子	（这三种可以直接删除）	//把1可以合并到2或者3上
		 * 4.左右孩子都存在
		 */
		// 1 || 2
		if (nullptr == pCur->_pRight) {
			//为根节点
			if (nullptr == pParent) {
				_pRoot = pCur->_pLeft;
			} else {
				//为父节点的左孩子
				if (pCur == pParent->_pLeft)
					pParent->_pLeft = pCur->_pLeft;
				//为父节点的右孩子
				else
					pParent->_pRight = pCur->_pLeft;
			}
			delete pCur;
		} else if (nullptr == pCur->_pLeft) {	//只有右孩子
			//为根节点
			if (nullptr == pParent) {
				_pRoot = pCur->_pRight;
			} else {
				//是父节点的左孩子
				if (pCur == pParent->_pLeft)
					pParent->_pLeft = pCur->_pRight;
				//是父节点的右孩子
				else
					pParent->_pRight = pCur->_pRight;
			}
			delete pCur;
		} else {		//左右孩子均存在
			//在右子树找替代将删除的替代结点
			Node* pDel = pCur->_pRight;
			pParent = pCur;
			while (pDel->_pLeft) {
				pParent = pDel;
				pDel = pDel->_pLeft;
			}

			//将替代结点的值--->待删除的结点
			pCur->_data = pDel->_data;

			//如果替代结点是父节点的左孩子，因为替代结点已经最左不会有左孩子，直接把右孩子接到父节点即可※※※
			if (pDel == pParent->_pLeft) {
				pParent->_pLeft = pDel->_pRight;
			} else {	//替代结点是父节点的右孩子（替代结点就是要删除结点的右孩子）
				pParent->_pRight = pDel->_pRight;
			}
			delete pDel;
		}
		return true;
	}

	void InOrder() {
		_InOrder(_pRoot);
	}


private:
	//中序递归遍历
	void _InOrder(Node* pRoot) {
		if (pRoot) {
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}

	//递归释放结点 后序删除
	void _Destroy(Node*& pRoot) {
		if (pRoot) {
			_Destroy(pRoot->_pLeft);
			_Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = nullptr;
		}
	}

private:
	Node* _pRoot;
};