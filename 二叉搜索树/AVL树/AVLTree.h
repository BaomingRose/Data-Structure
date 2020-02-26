#include <iostream>

template <class T>
struct AVLTreeNode {
	AVLTreeNode* _pLeft;
	AVLTreeNode* _pRight;
	AVLTreeNode* _pParent;
	T _data;
	int _bf;	//ƽ������

	AVLTreeNode(const T& data) : _data(data)
		, _pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _bf(0) {}
};

//AVL: ���������� + ƽ������
template<class T>
class AVLTree {
public:
	typedef AVLTreeNode<T> Node;

	AVLTree() : _pRoot(nullptr) {}

	bool Insert(const T& data) {
		//���ĵ�һ�����
		if (nullptr == _pRoot) {
			_pRoot = new Node(data);
			return true;
		}
		//1.���ն����������Ĺ������

		// �ҵ�����������Ӧ�ò����λ��
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

		//�����½ڵ�
		pCur = new Node(data);
		if (data < pParent->_data) {
			pParent->_pLeft = pCur;
		} else {
			pParent->_pRight = pCur;
		}
		pCur->_pParent = pParent;

		//����pParent ��ƽ������
		while (pParent) {
			if (pCur == pParent->_pLeft)
				--pParent->_bf;
			else
				++pParent->_bf;

			//���ڵ�߶�û�б䣬�Ͳ���ɹ���
			if (0 == pParent->_bf)
				return true;
			else if (-1 == pParent->_bf || 1 == pParent->_bf) {	//���׽��ĸ��ڵ�ƽ������ҲҪ��ģ�����ǽ��ṹ��Ҫ���游�ڵ��ԭ���ٸ��������Ҫѭ����ȥ��������ѭ�����ԭ��
				pCur = pParent;
				pParent = pCur->_pParent;
			} else {	//˫�׽���Ѿ�������AVL�������ˣ�����˫�׵�Ϊ���Ķ�����������ת
				if (2 == pParent->_bf) {
					//��������--->����
					if (pCur->_bf == 1)
						RotateL(pParent);
					//
					else
						RotateRL(pParent);
				}
				else {
					//��������--->�ҵ���
					if (pCur->_bf == -1)
						RotateR(pParent);
					//
					else
						RotateLR(pParent);
				}
				//��ת֮��Ͳ���Ҫ�ٸ����ˣ�����ĸ߶Ȼ�������
				break;
			}
		}
	}
private:
	Node* _pRoot;

	//�ҵ���
	void RotateR(Node* pParent) {
		// pSubL: pParent������
		// pSubLR: pParent���ӵ��Һ���
		PNode pSubL = pParent->_pLeft;
		PNode pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;

		pSubL->_pRight = pParent;
		PNode pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;

		//��pParent�ĸ���㸳��pSubL�ĸ����
		pSubL->_pParent = pPParent;
		//�ж�pParent�ǲ��Ǹ��ڵ�
		if (NULL == pPParent) {
			_pRoot = pSubL;
			pSubL->_pParent = NULL;
		} else {
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}

		//����ƽ������
		pParent->_bf = pSubL->_bf = 0;
	}

	//����
	void RotateL(Node* pParent) {}

	//˫�������������ҵ���
	void RotateLR(Node* pParent) {
		PNode pSubL = pParent->_pLeft;
		PNode pSubLR = pSubL->_pRight;

		// ��ת֮ǰ������pSubLR��ƽ�����ӣ���ת���֮����Ҫ���ݸ�ƽ�����������������ڵ��ƽ������
		int bf = pSubLR->_bf;

		RotateL(pParent->_pLeft);
		RotateR(pParent);

		//����ƽ������, ��Ϊ�������ҵ���pParent��pSubL����
		if (1 == bf)
			pSubL->_bf = -1;
		else if (-1 == bf)  //����else�����в���Ҫ���µ����
			pParent->_bf = 1;
	}

	//���ҵ���������
	void RotateRL(Node* pParent) {}
};