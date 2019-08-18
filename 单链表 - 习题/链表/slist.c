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

//单链表反转
//从第二个向头插
void SListReverse(SList* plist) {
	assert(plist->_head);

	SListNode * tmp = plist->_head->_next;
	SListNode * cur = plist->_head;
	while(tmp) {
		cur->_next = tmp->_next;
		tmp->_next = plist->_head;
		
		plist->_head = tmp;
		tmp = cur->_next;

	}
}
void SListReverse2(SList* plist) {
	assert(plist->_head);
	SList * reve = (SList *)malloc(sizeof(SList));
	SListInit(reve);
	SListNode* cur;
	for (cur = plist->_head; cur; cur = cur->_next) {
	SListPushFront(reve, cur->_data);
	}
	SListDestory(plist);
	plist->_head = reve->_head;
}

//换头操作
void SListReverse3(SList* plist) {
	assert(plist->_head);
	SListNode * tmp = plist->_head->_next;
	SListNode * cur = plist->_head;
	cur->_next = NULL;			//断链，将头节点和他的next断开，有tpm记录，所以能找到
	while (tmp) {
		plist->_head = tmp;		//换新头，tmp位置会成为新的头，旧头成了它的第一个结点
		tmp = tmp->_next;		//记录下次循环中tmp的位置，因为tmp在这次循环中已经用完了，而且后面马上就要断链，所以必须在这里记录
		plist->_head->_next = cur;//断链，与旧头形成新链
		cur = plist->_head;		//记录旧头的位置，方便下次循环成链
	}
}
SListNode * getIntersectionNode(SList* listA, SList* listB) {
	int lenA = 0;
	int lenB = 0;
	SListNode *cur;
	SListNode *headlong = listA->_head;
	SListNode *headshort = listB->_head;
	int gap;
	int i;

	for (cur = listA->_head; cur; cur = cur->_next)	{
		lenA++;
	}

	for (cur = listB->_head; cur; cur = cur->_next)	{
		lenB++;
	}
	gap = lenA - lenB;
	if (gap < 0) {
		gap *= -1;
		headshort = listA->_head;
		headlong = listB->_head;
	}

	for (i = 0; i < gap; i++) {
		headlong = headlong->_next;
	}

	for (; headlong; headlong = headlong->_next, headshort = headshort->_next) {
		if (headlong == headshort) {
			return headlong;
		}
	}
	return NULL;
}

int SListHasCycle(SList* plist) {
	SListNode *fast = plist->_head;
	SListNode *slow = plist->_head;

	while (slow && fast && fast->_next) {
		slow = slow->_next;
		fast = fast->_next->_next;
		if (slow == fast) {
			return 1;
		}
	}
	return 0;
}

SListNode* SListGetCycleNode(SList* plist) {
	SListNode *fast = plist->_head;
	SListNode *slow = plist->_head;

	while (slow && fast && fast->_next) {
		slow = slow->_next;
		fast = fast->_next->_next;
		if (slow == fast) {
			return fast;
		}
	}
	return NULL;
}

SListNode * SListDetectCycle(SList* plist) {
	SListNode *tmp = SListGetCycleNode(plist);

	if (NULL == tmp) {
		return NULL;
	}

	SListNode * cur = plist->_head;
	for (; cur; cur = cur->_next, tmp = tmp->_next) {
		if (cur == tmp) {
			return cur;
		}
	}
	return NULL;
}
