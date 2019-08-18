#include"dequeue.h"

int main() {
	Dequeue test;
	dequeueInit(&test);
	dequeuePush(&test, 1);
	dequeuePush(&test, 2);
	dequeuePush(&test, 3);
	printf("%d\n", dequeueFront(&test));
	dequeuePop(&test);
	printf("%d\n", dequeueFront(&test));
	dequeuePop(&test);
	printf("%d\n", dequeueFront(&test));
	system("pause");
	return 0;
}