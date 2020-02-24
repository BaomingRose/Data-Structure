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

		//�ǿ�
		//�ҵ�ǰ����ڶ����������е�λ��
		Node* pCur = _pRoot;
		Node* pParent = nullptr;	
		while (pCur) {
			//��pCurΪ�գ����¼pCur�ĸ��ڵ�
			pParent = pCur;		//�������ڵ�	
			if (data < pCur->_data) {
				pCur = pCur->_pLeft;
			} else if (data > pCur->_data) {
				pCur = pCur->_pRight;
			} else {
				return false;
			}
		}

		//������
		pCur = new Node(data);
		if (data > pParent->_data) {
			pParent->_pRight = pCur;
		} else {
			pParent->_pLeft = pCur;
		}
		return true;
	}

	bool Erase(const T& data) {
		//��data�ڶ�����������λ��
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
		//ɾ�����
		/*
		 * 1. û�к���	2.ֻ������	3.ֻ���Һ���	�������ֿ���ֱ��ɾ����	//��1���Ժϲ���2����3��
		 * 4.���Һ��Ӷ�����
		 */
		// 1 || 2
		if (nullptr == pCur->_pRight) {
			//Ϊ���ڵ�
			if (nullptr == pParent) {
				_pRoot = pCur->_pLeft;
			} else {
				//Ϊ���ڵ������
				if (pCur == pParent->_pLeft)
					pParent->_pLeft = pCur->_pLeft;
				//Ϊ���ڵ���Һ���
				else
					pParent->_pRight = pCur->_pLeft;
			}
			delete pCur;
		} else if (nullptr == pCur->_pLeft) {	//ֻ���Һ���
			//Ϊ���ڵ�
			if (nullptr == pParent) {
				_pRoot = pCur->_pRight;
			} else {
				//�Ǹ��ڵ������
				if (pCur == pParent->_pLeft)
					pParent->_pLeft = pCur->_pRight;
				//�Ǹ��ڵ���Һ���
				else
					pParent->_pRight = pCur->_pRight;
			}
			delete pCur;
		} else {		//���Һ��Ӿ�����
			//���������������ɾ����������
			Node* pDel = pCur->_pRight;
			pParent = pCur;
			while (pDel->_pLeft) {
				pParent = pDel;
				pDel = pDel->_pLeft;
			}

			//���������ֵ--->��ɾ���Ľ��
			pCur->_data = pDel->_data;

			//����������Ǹ��ڵ�����ӣ���Ϊ�������Ѿ����󲻻������ӣ�ֱ�Ӱ��Һ��ӽӵ����ڵ㼴�ɡ�����
			if (pDel == pParent->_pLeft) {
				pParent->_pLeft = pDel->_pRight;
			} else {	//�������Ǹ��ڵ���Һ��ӣ����������Ҫɾ�������Һ��ӣ�
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
	//����ݹ����
	void _InOrder(Node* pRoot) {
		if (pRoot) {
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}

	//�ݹ��ͷŽ�� ����ɾ��
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