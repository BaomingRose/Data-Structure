#include"slist.h"
void SListInit(SList* plist) {
	plist->_head = NULL;
}
void SListDestory(SList* plist) {
	assert(plist);

	SListNode * tmp;
	while (plist->_head) {
		tmp = plist->_head;
		plist->_head = plist->_head->_next;
		free(tmp);
	}
}

SListNode* BuySListNode(SLTDataType x) {
	return 0;
}
//头插
void SListPushFront(SList* plist, SLTDataType x) {
	assert(plist);
	SListNode * cur = (SListNode *)malloc(sizeof(SListNode));
	cur->_data = x;
	cur->_next = plist->_head;
	plist->_head = cur;
}
//头删
void SListPopFront(SList* plist) {
	assert(plist);
	SListNode *tmp = plist->_head;
	if (plist->_head) {
		tmp = plist->_head;
		plist->_head = plist->_head->_next;
		free(tmp);
	}
}
SListNode* SListFind(SList* plist, SLTDataType x) {
	assert(plist);

	SListNode * cur;
	for (cur = plist->_head; cur; cur = cur->_next) {
		if (cur->_data == x) {
			return cur;
		}
	}
	return NULL;
}
// 在pos的后面进行插入 
void SListInsertAfter(SListNode* pos, SLTDataType x) {
	assert(pos);
	SListNode * cur = (SListNode *)malloc(sizeof(SListNode));
	cur->_data = x;
	cur->_next = pos->_next;
	pos->_next = cur;
}
// 在pos的前面进行插入 
void SListInsertFront(SList* plist, SLTDataType x,SLTDataType src) {
	assert(plist);
	SListNode * cur;
	SListNode * newdata = (SListNode *)malloc(sizeof(SListNode));

	if (plist->_head->_data == x) {
		SListPushFront(plist, src);
		return;
	}
	for (cur = plist->_head; cur->_next; cur = cur->_next) {
		if (cur->_next->_data == x) {
			break;
		}
	}
	newdata->_next = cur->_next;
	cur->_next = newdata;
}
//后删
void SListEraseAfter(SListNode* pos) {
	assert(pos);
	SListNode * tmp = pos->_next;

	pos->_next = tmp->_next;
	free(tmp);
}
void SListRemove(SList* plist, SLTDataType x) {
	SListEraseAfter(SListFind(plist, x));//错误：删除x后面的结点
}

void SListPrint(SList* plist) {
	assert(plist);

	SListNode * cur;
	for (cur = plist->_head; cur; cur = cur->_next) {
		printf("%d->", cur->_data);
	}
	printf("NULL\n");
}
