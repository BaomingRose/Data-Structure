#include<stdio.h>
#include<stdlib.h>
#include"queue.h"
#include<time.h>

int main() {
#if 1
	int a[10] = { 9, 0, 1, 5, 3, 8, 4, 7, 6, 2 };
	QuickSort(a, 10);
	printArray(a, 10);
	return 0;

#else
	srand(time(NULL));

	int i;
	int src[NUM];
	for (i = 0; i < NUM; i++)
	{
		src[i] = rand() % 5000 + 1;
	}
	QuickSort(src, NUM);
	printArray(src, NUM);
	return 0;
#endif
}