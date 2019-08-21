#include"stack.h"
#include<assert.h>

void StackInit(Stack* st, size_t capacity) {
	assert(st);

	st->_capicity = capacity;
	st->array = (StDataType*)malloc(sizeof(StDataType) * capacity);
	assert(st->array);
	st->_size = 0;
}

void StackDestroy(Stack* st) {
	assert(st);

	if (st->array) {
		free(st->array);
		st->array = NULL;
		st->_size = 0;
		st->_capicity = 0;
	}
}

void CheckCapcity(Stack* st) {
	assert(st);

	if (st->_size == st->_capicity) {
		st->_capicity *= 2;
		st->array = (StDataType*)realloc(st->array, st->_capicity * sizeof(StDataType));
	}
}

void StackPush(Stack* st, StDataType x) {
	assert(st);

	CheckCapcity(st);

	st->array[st->_size] = x;
	++st->_size;
}

void StackPop(Stack* st) {
	assert(st || st->_size);

	--st->_size;
}

StDataType StackTop(Stack* st) {
	if (StackIsEmpty(st)) {
		return (StDataType)0;
	}
	return st->array[st->_size - 1];
}

int StackIsEmpty(Stack* st) {
	return st->_size == 0;
}
