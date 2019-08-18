#include"List.h"

void ListInit(List* plist) {
	plist->_head = (ListNode *)malloc(sizeof(ListNode));
	memset(&plist->_head->_data, 0, sizeof(LTDataType));
	plist->_head->_next = plist->_head->_prev = plist->_head;
}

void ListDestory(List* plist) {
	ListNode * tmp = plist->_head->_next;

	while(tmp != plist->_head) {
		tmp->_prev->_next = tmp->_next;
		tmp->_next->_prev = tmp->_prev;
		free(tmp);
		tmp = plist->_head->_next;
	}
	free(plist->_head);
	plist->_head = NULL;
}

//后插
void ListPushBack(List* plist, LTDataType x) {
	ListNode *cur = (ListNode *)malloc(sizeof(ListNode));
	cur->_data = x;

	plist->_head->_prev->_next = cur;
	cur->_prev = plist->_head->_prev;
	plist->_head->_prev = cur;
	cur->_next = plist->_head;

}

void ListPopBack(List* plist) {
	ListNode * tmp = plist->_head->_prev;

	if (tmp != plist->_head) {
		tmp->_prev->_next = tmp->_next;
		tmp->_next->_prev = tmp->_prev;
		free(tmp);
	}
}
//前插
void ListPushFront(List* plist, LTDataType x) {
	ListNode *cur = (ListNode *)malloc(sizeof(ListNode));
	cur->_data = x;

	plist->_head->_next->_prev = cur;
	cur->_next = plist->_head->_next;
	plist->_head->_next = cur;
	cur->_prev = plist->_head;
}

void ListPopFront(List* plist) {
	ListNode * tmp = plist->_head->_next;

	if (tmp != plist->_head) {
		tmp->_prev->_next = tmp->_next;
		tmp->_next->_prev = tmp->_prev;
		free(tmp);
	}
}

ListNode* ListFind(List* plist, LTDataType x) {

}
// 在pos的前面进行插入 
void ListInsert(ListNode* pos, LTDataType x) {

}
// 删除pos位置的节点 
void ListErase(ListNode* pos) {

}
void ListRemove(List* plist, LTDataType x) {

}

void ListPrint(List* plist) {
	ListNode *cur;
	printf("head<-->");
	for (cur = plist->_head->_next; cur != plist->_head; cur = cur->_next) {
		printf("%d<-->", cur->_data);
	}
	printf("head\n");
}