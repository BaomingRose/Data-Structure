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

	//Ĭ�ϸ��ɺ�ɫ����ɫֻ��һ��������ƻ���������
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
		//�Ȱ��ն����������ķ�ʽ������
		Node*& pRoot = GetRoot();
		if (nullptr == pRoot) {
			pRoot = new Node(data, BLACK);
			pRoot->_pParent = _pHead;
			_pHead->_pLeft = pRoot;
			_pHead->_pRight = pRoot;
			return true;
		}

		//���ն����������Ĺ����Ҵ������ں�����е�λ��
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

		//�����½ڵ�
		pCur = new Node(data);
		if (data < pParent->_data)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;
		pCur->_pParent = pParent;

		//����Ƿ���������������---�������3������������һ��ĺ�ɫ���
		//���pParent���Ϊ��ɫ��Υ������3
		while (pParent != _pHead && RED == pParent->_color) {
			Node* grandFather = pParent->_pParent;

			//���׽�������Ƚ���������
			if (pParent == grandFather->_pLeft) {
				Node* uncle = grandFather->_pRight;
				//���1�������������Ϊ��
				if (uncle && uncle->_color == RED) {
					pParent->_color = BLACK;
					uncle->_color = BLACK;
					grandFather->_color = RED;

					pCur = grandFather;
					pParent = pCur->_pParent;
				}
				else {	//�����㲻���� || ���������&&��ɫ
				 //���������Ϊ�����
					if (pCur == pParent->_pRight) {
						RotateL(pParent);
						swap(pParent, pCur);
					}
					//�������
					pParent->_color = BLACK;
					grandFather->_color = RED;
					RotateR(grandFather);

				}
			}

			//���׽�������Ƚ���������
			else {
				Node* uncle = grandFather->_pLeft;
				if (uncle && uncle->_color == RED) {
					pParent->_color = BLACK;
					uncle->_color = BLACK;
					grandFather->_color = RED;

					pCur = grandFather;
					pParent = pCur->_pParent;
				}
				else { //������������
				 //�����
					if (pCur == pParent->_pLeft) {
						RotateR(pParent);
						swap(pParent, pCur);
					}

					//�������
					pParent->_color = BLACK;
					grandFather->_color = RED;
					RotateL(grandFather);
				}
			}
		}
		//���ܰѸ����ĳɺ����
		pRoot->_color = BLACK;

		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return true;
	}

	void InOrder() {
		_InOrder(GetRoot());
	}

	//�жϸ����ǲ��Ǻ����
	bool IsValidRBTree() {
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return true;

		//��֤����2
		if (pRoot->_color != BLACK) {
			cout << "Υ������2:���ڵ㲻�Ǻ�ɫ" << endl;
			return false;
		}

		//��֤����4
		//��ȡһ��·���к�ɫ���ĸ���
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

		//��֤����3
		Node* pParent = pRoot->_pParent;
		if (pParent != _pHead && pParent->_color == RED && pRoot->_color == RED) {
			cout << "Υ������3����������һ��ĺ�ɫ���" << endl;
			return false;
		}

		if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight) {
			if (blackCount != pathCount) {
				cout << "Υ������4��·���к�ɫ����������ͬ" << endl;
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

	//��ȡ������
	Node* LeftMost() {
		Node* pCur = GetRoot();
		if (pCur == nullptr)
			return _pHead;

		while (pCur->_pLeft)
			pCur = pCur->_pLeft;
		return pCur;
	}

	//��ȡ���ҽ��
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

		//���ⲿ�����������㸳���µĸ��ڵ�
		pSubR->_pParent = pPParent;
		//�ж����滹��û�н����
		if (pPParent == _pHead) {	//�Ѿ��Ǹ���
			_pHead->_pParent = pSubR;
		}
		else {
			//�жϴ����ⲿ�ֵ��������������������
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
			//�жϴ����ⲿ�ֵ��������������������
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
