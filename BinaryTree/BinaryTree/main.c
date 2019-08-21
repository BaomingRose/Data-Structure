#include"BinaryTree.h"
#include<stdio.h>
#include<stdlib.h>

int main() {
	BTNode * root = BinaryTreeCreate("ABD#GI##J###CE#HK###F##");

	BinaryTreePrevOrder(root);
	putchar('\n');
	BinaryTreeInOrder(root);
	putchar('\n');
	BinaryTreePostOrder(root);
	putchar('\n');
	BinaryTreePrevOrderNonR(root);
	putchar('\n');
	BinaryTreeLevelOrder(root);
	putchar('\n');
	BinaryTreeInOrderNonR(root);
	putchar('\n');
	BinaryTreePostOrderNonR(root);
	putchar('\n');
	printf("%d\n", BinaryTreeComplete(root));


	BinaryTreeDestory(&root);
	return 0;
}