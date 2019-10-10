#ifndef BINARYTREE_H
#define BINARYTREE_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef char elem;

typedef struct BNode {
	elem _data;
	struct BNode* _left;
	struct BNode* _right;
}BNode;

BNode* CreateBinaryTree(char* src, int * p) {
	if (src[*p] != '#') {
		BNode* root = (BNode*)malloc(sizeof(BNode));
		root->_data = src[*p];
		++(*p);
		root->_left = CreateBinaryTree(src, p);
		++(*p);
		root->_right = CreateBinaryTree(src, p);
		return root;
	} else {
		return NULL;
	}
}

//����ָ��ֱ���޸��ⲿָ�������
void DeleteBinaryTree(BNode** root) {
	BNode* curRoot = *root;
	if (curRoot) {
		DeleteBinaryTree(&curRoot->_left);
		DeleteBinaryTree(&curRoot->_right);
		free(curRoot);
		*root = NULL;
	}
}

#if 0
//һ��ָ������ͷ��ڴ�,���ǲ�û�и���root��ָ��
void BinaryTreeDestroy(BNode* root) {
	if (root) {
		BinaryTreeDestroy(root->_left);
		BinaryTreeDestroy(root->_left);
		free(root);
		root = NULL;
	}
}
#endif

int BinaryTreeSize(BNode* root) {
	if (root == NULL) {
		return 0;
	}
	return BinaryTreeSize(root->_left) + BinaryTreeSize(root->_right) + 1;
}

int BinaryTreeLeafSize(BNode* root) {
	if (root == NULL)
		return 0;
	//rootΪҶ�ӽ��
	if (root->_left == NULL && root->_right == NULL) {
		return 1;
	}
	return BinaryTreeLeafSize(root->_left) + BinaryTreeLeafSize(root->_right);
}

//��k�������
int BinaryTreeLevelKSize(BNode* root, int k) {
	if (root == NULL) {
		return 0;
	}
	if (k == 1) {
		return 1;
	}
	return BinaryTreeLevelKSize(root->_left, k - 1) + BinaryTreeLevelKSize(root->_right, k - 1);
}

BNode* BinaryTreeFind(BNode* root, elem x) {
	BNode * ret;
	//������û���ҵ�
	if (root == NULL)
		return NULL;
	if (root->_data == x)
		return root;
	ret = BinaryTreeFind(root->_left, x);
	if (ret)
		return ret;
	ret = BinaryTreeFind(root->_right, x);
	if (ret)
		return ret;
	return NULL;
}

void BinaryTreePrevOrder(BNode* root) {
	if (root) {
		printf("%c ", root->_data);
		BinaryTreePrevOrder(root->_left);
		BinaryTreePrevOrder(root->_right);
	} else {
		printf("# ");
	}
}

void BinaryTreeInOrder(BNode* root) {
	if (root) {
		BinaryTreeInOrder(root->_left);
		printf("%c ", root->_data);
		BinaryTreeInOrder(root->_right);
	} else {
		printf("# ");
	}
}

void BinaryTreePostOrder(BNode* root) {
	if (root) {
		BinaryTreePostOrder(root->_left);
		BinaryTreePostOrder(root->_right);
		printf("%c ", root->_data);
	} else {
		printf("# ");
	}
}

#if 0
//�ж��Ƿ�Ϊ��ͬ��
int isSameTree(BNode* p, BNode* q) {
	if (p == NULL && q != NULL)
		return 0;
	if (p != NULL && q == NULL)
		return 0;
	if (p == NULL && q == NULL)
		return 1;

	if (p->_data == q->_data)
		return isSameTree(p->_left, q->_left)
		&& isSameTree(p->_right, q->_right);
	else
		return 0;
}

//�ж�t�Ƿ�Ϊs������
int isSubtree(BNode* s, BNode* t) {
	if (s == NULL)
		return 0;

	//����ͬ���жϵ�ǰ������Ƿ��t��ͬ
	if (s->_data == t->_data && isSameTree(s, t))
		return 1;
	return isSubtree(s->_left, t)
		|| isSubtree(s->_right, t);
}

//�������
int maxDepth(BNode* root) {
	if (root == NULL) {
		return 0;
	}
	return max(maxDepth(root->_left), maxDepth(root->_right)) + 1;
}

//�ж��Ƿ�Ϊƽ�������
int _isBalanced(BNode* root, int* curDepth) {
	if (root == NULL) {
		//�����߶�Ϊ0
		*curDepth = 0;
		return 1;
	}
	int leftDepth = 0, rightDepth = 0;
	if (_isBalanced(root->_left, &leftDepth)
		&& _isBalanced(root->_right, &rightDepth)
		&& abs(leftDepth - rightDepth) < 2) {
		//��ǰ���ĸ߶�max(leftDepth, rightDepth)
		*curDepth = max(leftDepth, rightDepth) + 1;
		return 1;
	}
	else
		return 0;
}

int isBalanced(BNode* root) {
	int depth = 0;
	return _isBalanced(root, &depth);
}

//�ж��Ƿ�Գ�
int _isSymmetric(BNode* left, BNode* right) {
	if (left == NULL && right == NULL)
		return 1;
	if (left == NULL || right == NULL)
		return 0;
	return left->_data == right->_data
		&& _isSymmetric(left->_left, right->_right)
		&& _isSymmetric(left->_right, right->_left);
}

int isSymmetric(BNode* root) {
	if (root == NULL)
		return 1;
	return _isSymmetric(root->_left, root->_right);
}
#endif
#endif // !BINARYTREE_H
