#include"queue.h"

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void QueueInit(Queue* qu) {
	assert(qu);

	qu->_head = NULL;
	qu->_rear = NULL;
}

void QueueDestroy(Queue* qu) {
	assert(qu);

	QueueNode* tmp;
	while (qu->_head) {
		tmp = qu->_head;
		qu->_head = qu->_head->_next;
		free(tmp);
	}
}

void QueuePop(Queue* qu) {
	assert(qu);

	if (qu->_head) {
		QueueNode* tmp = qu->_head;
		qu->_head = qu->_head->_next;
		free(tmp);
	}
}

void QueuePush(Queue* qu, QuDataType x) {
	assert(qu);

	QueueNode* cur = (QueueNode*)malloc(sizeof(QueueNode));
	cur->_data = x;
	cur->_next = NULL;

	if (QueueIsEmpty(qu)) {
		qu->_head = qu->_rear = cur;
		return;
	}

	qu->_rear->_next = cur;
	qu->_rear = cur;
}

QuDataType QueueTop(Queue* qu) {
	if (QueueIsEmpty(qu)) {
		return (QuDataType)0;
	}
	return qu->_head->_data;
}

int QueueIsEmpty(Queue* qu) {
	return qu->_head == NULL;
}
