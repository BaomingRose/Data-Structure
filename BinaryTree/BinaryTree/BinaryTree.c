#include"BinaryTree.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"queue.h"
#include"stack.h"

//ABD#GI##J###CE#HK###F##
// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树 
static int s_n;

BTNode* BinaryTreeCreateExe(BTDataType* src) {
	if (src[s_n] == '#') {
		s_n++;
		return NULL;
	}

	BTNode *cur = (BTNode*)malloc(sizeof(BTNode));
	cur->_data = src[s_n];
	s_n++;

	cur->lchild = BinaryTreeCreateExe(src);
	cur->rchild = BinaryTreeCreateExe(src);

	return cur;
}


BTNode *BinaryTreeCreate(BTDataType * src) {
	s_n = 0;
	return BinaryTreeCreateExe(src);
}

void BinaryTreeDestory(BTNode** root) {
	if (*root) {
		BinaryTreeDestory(&((*root)->lchild));
		BinaryTreeDestory(&((*root)->rchild));
		free(*root);
	}
}

int BinaryTreeSize(BTNode* root) {

}

int BinaryTreeLeafSize(BTNode* root) {

}

int BinaryTreeLevelKSize(BTNode* root, int k) {

}

BTNode* BinaryTreeFind(BTNode* root, BTDataType x) {

}

// 遍历
void BinaryTreePrevOrder(BTNode* root) {
	if (root) {
		putchar(root->_data);
		BinaryTreePrevOrder(root->lchild);
		BinaryTreePrevOrder(root->rchild);
	}
}

void BinaryTreeInOrder(BTNode* root) {
	if (root) {
		BinaryTreeInOrder(root->lchild);
		putchar(root->_data);
		BinaryTreeInOrder(root->rchild);
	}

}
void BinaryTreePostOrder(BTNode* root) {
	if (root) {
		BinaryTreePostOrder(root->lchild);
		BinaryTreePostOrder(root->rchild);
		putchar(root->_data);
	}
}

// 非递归遍历
// 层序遍历
void BinaryTreeLevelOrder(BTNode* root) {
	Queue qu;
	BTNode * cur;
	QueueInit(&qu);
	QueuePush(&qu, root);
	while (!QueueIsEmpty(&qu)) {
		cur = QueueTop(&qu);
		putchar(cur->_data);
		if (cur->lchild) {
			QueuePush(&qu, cur->lchild);
		}
		if (cur->rchild) {
			QueuePush(&qu, cur->rchild);
		}

		QueuePop(&qu);
	}
	QueueDestroy(&qu);
}

void BinaryTreePrevOrderNonR(BTNode* root) {
	Stack st;
	BTNode * cur = root;

	StackInit(&st, 100);
	while (cur) {
		putchar(cur->_data);
		if (cur->rchild) {
			StackPush(&st, cur->rchild);
		}
		if (cur->lchild) {
			cur = cur->lchild;
		}
		else {
			cur = StackTop(&st);
			StackPop(&st);
		}
	}
	StackDestroy(&st);
}

void BinaryTreeInOrderNonR(BTNode * root) {
	BTNode * cur = root;

	Stack st;
	StackInit(&st, 100);

	while (cur || !StackIsEmpty(&st)) {
		for (; cur; cur = cur->lchild) {
			StackPush(&st, cur);
		}

		cur = StackTop(&st);
		if (cur) {
			putchar(cur->_data);
			StackPop(&st);
			cur = cur->rchild;
		}
	}

	StackDestroy(&st);
}

void BinaryTreePostOrderNonR(BTNode* root) {
	char tag[64];

	BTNode * cur = root;
	Stack st;
	StackInit(&st, 100);
	do {
		for (; cur; cur = cur->lchild) {
			StackPush(&st, cur);
			tag[st._size - 1] = 0;
		}
		while (!StackIsEmpty(&st) && tag[st._size - 1]) {
			cur = StackTop(&st);
			putchar(cur->_data);
			StackPop(&st);
		}
		if (!StackIsEmpty(&st)) {
			cur = StackTop(&st);
			tag[st._size - 1] = 1;
			cur = cur->rchild;
		}
	} while (!StackIsEmpty(&st));

	StackDestroy(&st);
}

// 判断二叉树是否是完全二叉树
int BinaryTreeComplete(BTNode* root) {
	Queue qu;
	BTNode * cur;
	int tag = 0;
	QueueInit(&qu);
	QueuePush(&qu, root);
	while (!QueueIsEmpty(&qu)) {
		cur = QueueTop(&qu);
		putchar(cur->_data);
		if (cur->rchild && !cur->lchild) {
			return 0;
		}
		if (tag && (cur->rchild || cur->lchild)) {
			return 0;
		}
		if (cur->lchild) {
			QueuePush(&qu, cur->lchild);
		}
		if (cur->rchild) {
			QueuePush(&qu, cur->rchild);
		}
		else {
			tag = 1;
		}
		QueuePop(&qu);
	}

	QueueDestroy(&qu);
	return 1;
}