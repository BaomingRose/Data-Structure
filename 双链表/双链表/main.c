#include"List.h"

int main() {
	List list;
	ListInit(&list);
	ListPushBack(&list, 7);
	ListPushBack(&list, 6);
	ListPushBack(&list, 5);
	ListPushBack(&list, 4);
	ListPushBack(&list, 3);
	ListPushFront(&list, 8);
	ListPushFront(&list, 9);
	ListPrint(&list);
	printf("«∞…æ:\n");
	ListPopFront(&list);
	ListPrint(&list);
	printf("∫Û…æ:\n");
	ListPopBack(&list);
	ListPrint(&list);
	ListDestory(&list);

	system("pause");
	return 0;

}