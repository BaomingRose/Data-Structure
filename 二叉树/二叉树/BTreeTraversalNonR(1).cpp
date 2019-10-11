#include<iostream>
#include<stack>
#include<queue>
#include"binaryTree.h"
using namespace std;

//�������
void BinaryTreeLevelOrder(BNode* root) {
	queue<BNode*> q;
	if (root) {
		//���ڵ����
		q.push(root);
	}
	//ÿ�γ���ͷԪ��,�������ӽ��,���
	while (!q.empty()) {
		BNode* _front;
		_front = q.front();
		q.pop();
		//����
		printf("%c ", _front->_data);
		//�������
		if (_front->_left) {
			q.push(_front->_left);
		}
		if (_front->_right) {
			q.push(_front->_right);
		}
	}
	printf("\n");
}

//ǰ��ǵݹ����
void BinaryTreePrevOrderNonR(BNode* root) {
	stack<BNode*> st;
	BNode* cur = root;
	while (cur || !st.empty()) {
		while (cur) {
			printf("%c ", cur->_data);
			st.push(cur);
			cur = cur->_left;
		}
		//�������һ��������������
		cur = st.top()->_right;
		st.pop();
	}
}

//����ǵݹ����
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

//����ǵݹ����
void BinaryTreePostOrderNonR(BNode* root) {
	stack<BNode*> st;
	BNode* cur = root;
	BNode* prev = NULL;
	while (cur || !st.empty()) {
		while (cur) {
			st.push(cur);
			cur = cur->_left;
		}
		//�������һ��������������
		//�ж��Ƿ����������
		//�����������������ʸ�����ջ
		//���ڣ���������������꣬���Է��ʸ�
		if (st.top()->_right == NULL || st.top()->_right == prev) {
			printf("%c ", st.top()->_data);
			prev = st.top();
			st.pop();
		} else {	//����������,��û�з���,�ȷ���������
			cur = st.top()->_right;
		}
	}
}

// �ж϶������Ƿ�����ȫ������
//�Բ��������ʽ�ж�
int BinaryTreeComplete(BNode* root) {
	queue<BNode*> q;
	if (root) {
		//���ڵ����
		q.push(root);
	}
	//ÿ�γ���ͷԪ��,�������ӽ��,���
	while (!q.empty()) {
		BNode* _front;
		_front = q.front();
		q.pop();
		//�ж��Ƿ�Ϊ��
		if (_front) {
			q.push(_front->_left);
			q.push(_front->_right);
		} else {
			//�жϺ����Ƿ�Ϊ��
			break;
		}
	}
	while (!q.empty()) {
		BNode* _front = q.front();
		//�ж��Ƿ�Ϊ�գ��ǿգ�˵��������
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
	printf("�ݹ�ǰ��\n");
	BinaryTreePrevOrder(root);
	printf("�ǵݹ�ǰ��\n");
	BinaryTreePrevOrderNonR(root);
	putchar('\n');
	printf("�ݹ����\n");
	BinaryTreePostOrder(root);
	printf("�ǵݹ����:\n");
	BinaryTreePostOrderNonR(root);
	putchar('\n');
	printf("�ݹ�����\n");
	BinaryTreeInOrder(root);
	printf("�ǵݹ�����\n");
	BinaryTreeInOrderNonR(root);
	putchar('\n');

	i = 0;
	char b[] = { 'A', 'B', 'D', '#', '#', 'E', '#', '#', 'C', 'F', '#', '#', '#' };
	BNode* root2 = CreateBinaryTree(b, &i);
	BinaryTreeLevelOrder(root);


	printf("%d\n", BinaryTreeComplete(root));
	printf("%d\n", BinaryTreeComplete(root2));

}