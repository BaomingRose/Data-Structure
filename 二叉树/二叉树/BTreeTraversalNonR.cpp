#include<iostream>
#include<stack>
#include<queue>
#include"binaryTree.h"
using namespace std;

//层序遍历
void BinaryTreeLevelOrder(BNode* root) {
	queue<BNode*> q;
	if (root) {
		//根节点入队
		q.push(root);
	}
	//每次出队头元素,带出孩子结点,入队
	while (!q.empty()) {
		BNode* _front;
		_front = q.front();
		q.pop();
		//遍历
		printf("%c ", _front->_data);
		//孩子入队
		if (_front->_left) {
			q.push(_front->_left);
		}
		if (_front->_right) {
			q.push(_front->_right);
		}
	}
	printf("\n");
}

//前序非递归遍历
void BinaryTreePrevOrderNonR(BNode* root) {
	stack<BNode*> st;
	BNode* cur = root;
	while (cur || !st.empty()) {
		while (cur) {
			printf("%c ", cur->_data);
			st.push(cur);
			cur = cur->_left;
		}
		cur = st.top()->_right;
		st.pop();
	}
}

//中序非递归遍历
void BinaryTreeInOrderNonR(BNode* root) {
	stack<BNode*> st;
	BNode* cur = root;
	while (cur || !st.empty()) {
		while (cur) {
			st.push(cur);
			cur = cur->_left;
		}
		printf("%c ", st.top()->_data);
		cur = st.top()->_right;
		st.pop();
	}
	putchar('\n');
}

//后序非递归遍历
void BinaryTreePostOrderNonR(BNode* root) {
	stack<BNode*> st;
	BNode* cur = root;
	BNode* prev = NULL;
	while (cur || !st.empty()) {
		while (cur) {
			st.push(cur);
			cur = cur->_left;
		}
		if (st.top()->_right == NULL || st.top()->_right == prev) {
			printf("%c ", st.top()->_data);
			prev = st.top();
			st.pop();
		} else {
			cur = st.top()->_right;
		}
	}
}

// 判断二叉树是否是完全二叉树
//以层序遍历方式判断
int BinaryTreeComplete(BNode* root) {
	queue<BNode*> q;
	if (root) {
		//根节点入队
		q.push(root);
	}
	//每次出队头元素,带出孩子结点,入队
	while (!q.empty()) {
		BNode* _front;
		_front = q.front();
		q.pop();
		//判断是否为空
		if (_front) {
			q.push(_front->_left);
			q.push(_front->_right);
		} else {
			//判断后面是否都为空
			break;
		}
	}
	while (!q.empty()) {
		BNode* _front = q.front();
		//判断是否为空，非空，说明不连续
		if (_front) {
			return 0;
		}
		q.pop();
	}
	return 1;
}

int main() {
	//ABD##E#H##CF##G##
	int i = 0;
	char a[] = { 'A', 'B', 'D', '#', '#', 'E', '#', 'H', '#', '#', 'C', 'F', '#', '#', 'G', '#', '#' };
	BNode* root = CreateBinaryTree(a, &i);
	printf("递归前序：\n");
	BinaryTreePrevOrder(root);
	printf("非递归前序：\n");
	BinaryTreePrevOrderNonR(root);
	putchar('\n');
	printf("递归后序：\n");
	BinaryTreePostOrder(root);
	printf("非递归后序:\n");
	BinaryTreePostOrderNonR(root);
	putchar('\n');
	printf("递归中序：\n");
	BinaryTreeInOrder(root);
	printf("非递归中序：\n");
	BinaryTreeInOrderNonR(root);
	putchar('\n');

	i = 0;
	char b[] = { 'A', 'B', 'D', '#', '#', 'E', '#', '#', 'C', 'F', '#', '#', '#' };
	BNode* root2 = CreateBinaryTree(b, &i);
	BinaryTreeLevelOrder(root);


	printf("%d\n", BinaryTreeComplete(root));
	printf("%d\n", BinaryTreeComplete(root2));

}