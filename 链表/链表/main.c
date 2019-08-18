#include"slist.h"

int main() {
	SList test;
	SListInit(&test);
	SListPushFront(&test, 4);
	SListPushFront(&test, 1);
	SListPushFront(&test, 2);
	SListPushFront(&test, 3);
	SListPrint(&test);
	SListPopFront(&test);

	SListPrint(&test);
	SListInsertAfter(SListFind(&test,4), 5);
	SListPrint(&test);
	SListInsertFront(&test, 5, 10);
	SListPrint(&test);
	SListDestory(&test);

	system("pause");
	return 0;
}