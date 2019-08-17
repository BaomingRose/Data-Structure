#include"test.h"

int main() {
	SeqList test;
	SeqListInit(&test, 10);

	SeqListPushFront(&test, 10);
	SeqListPushBack(&test, 9);
	SeqListInsert(&test, 1, 2);
	SeqListErase(&test, 2);
	SeqListRemove(&test, 9);
	SeqListModify(&test, 1, 7);

	SeqListBubbleSort(&test);
	printf("%d\n", SeqListBinaryFind(&test, 6));
	SeqListPrint(&test);
	SeqListDestory(&test);
	system("pause");
	return 0;
}