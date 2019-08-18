#ifndef _DEQUEUE_H_
#define _DEQUEUE_H_

#include<stdio.h>
#include<stdlib.h>
#define QUEUENUM 5
typedef int DataType;

//—≠ª∑∂”¡–
typedef struct {
	DataType _data[QUEUENUM];
	DataType * _head;
	DataType * _tail;
	size_t _size;
}Dequeue;

void dequeueInit(Dequeue * qu);
void dequeueEmpty(Dequeue * qu);
int dequeuePush(Dequeue * qu, DataType x);
int dequeuePop(Dequeue * qu);
int dequeueIsEmpty(Dequeue * qu);
DataType dequeueFront(Dequeue * qu);
DataType dequeueBack(Dequeue * qu);
size_t dequeueSize(Dequeue * qu);

#endif // 