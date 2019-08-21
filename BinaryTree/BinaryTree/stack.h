#ifndef _STACK_H_
#define _STACK_H_

#include"BinaryTree.h"
#include<stdio.h>
#include<stdlib.h>

//用顺序表实现栈
typedef BTNode * StDataType;

typedef struct Stack {
	StDataType* array;
	size_t _size;
	size_t _capicity;
}Stack;

void StackInit(Stack* st, size_t capacity);
void StackDestroy(Stack* st);

void StackPush(Stack* st, StDataType x);
void StackPop(Stack* st);
StDataType StackTop(Stack* st);
int StackIsEmpty(Stack* st);

#endif
