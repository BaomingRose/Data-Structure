#include"binaryTree.h"

int main() {
	//ABD##E#H##CF##G##
	int i = 0;
	char a[] = { 'A', 'B', 'D', '#', '#', 'E', '#', 'H', '#', '#', 'C', 'F', '#', '#', 'G', '#', '#' };
	BNode* root = CreateBinaryTree(a, &i);
	printf("i = %d\n", i);
	i = 0;
	BNode* root2 = CreateBinaryTree(a, &i);
	BinaryTreePrevOrder(root);
	putchar('\n');
	BinaryTreeInOrder(root);
	putchar('\n');
	BinaryTreePostOrder(root);
	putchar('\n');
	int nodeSize, leafSize;
	nodeSize = BinaryTreeSize(root);
	leafSize = BinaryTreeLeafSize(root);
	printf("nodeSize = %d, leafSize = %d \n", nodeSize, leafSize);

	BinaryTreePostOrder(root2);
	putchar('\n');

	int kNodeSize;
	kNodeSize = BinaryTreeLevelKSize(root, 3);
	printf("kNodeSize = %d\n", kNodeSize);

	int isSame = isSameTree(root, root2);
	printf("isSame = %d\n", isSame);

	printf("Æ½ºâ¶þ²æÊ÷:%d\n", isBalanced(root));

	printf("¶Ô³Æ£¿£º%d\n", isSymmetric(root));

	DeleteBinaryTree(&root);
	return 0;
}
