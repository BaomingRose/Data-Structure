#ifndef _SLIST_H_
#define _SLIST_H_
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

// 无头单向非循环链表增删查改实现 
typedef int SLTDataType; 
typedef struct SListNode {    
	SLTDataType _data;    
	struct SListNode* _next; 
}SListNode;

typedef struct SList { 
	SListNode* _head; 
}SList;

/*
链表遍历
	for(cur = head; cur; cur = cur->next) {
		cur;
	}
	前插遍历:
	for(cur = head; cur; pre = cur, cur = cur->next) {
		cur;
	}
	也可(比下个节点的数据)
	for(cur = plist->_head; cur->_next; cur = cur->_next) {
		if(plist->_next->_data == x) {
			break;
		}
	}


	双向链表
	for(cur = head->next; cur != head; cur = cur->next) {
		cur;
	}

*/


void SListInit(SList* plist); 
void SListDestory(SList* plist);

SListNode* BuySListNode(SLTDataType x); 
void SListPushFront(SList* plist, SLTDataType x); 
void SListPopFront(SList* plist); 
SListNode* SListFind(SList* plist, SLTDataType x); 
// 在pos的后面进行插入 
void SListInsertAfter(SListNode* pos, SLTDataType x); 
// 在pos的前面进行插入 
void SListInsertFront(SList* plist, SLTDataType x, SLTDataType src);
void SListEraseAfter(SListNode* pos); 
void SListRemove(SList* plist, SLTDataType x);

void SListPrint(SList* plist); 

#endif