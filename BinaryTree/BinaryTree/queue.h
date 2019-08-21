#ifndef _QUEUE_H_
#define _QUEUE_H_
#include"BinaryTree.h"

//用单链表实现队列
typedef BTNode * QuDataType;

typedef struct QueueNode {
	QuDataType _data;
	struct QueueNode * _next;
}QueueNode;

typedef struct Queue {
	QueueNode * _head;
	QueueNode * _rear;
}Queue;

void QueueInit(Queue* qu);
void QueueDestroy(Queue* qu);

void QueuePop(Queue* qu);
void QueuePush(Queue* qu, QuDataType x);
QuDataType QueueTop(Queue* qu);
int QueueIsEmpty(Queue* qu);

#endif // !_QUEUE_H_
