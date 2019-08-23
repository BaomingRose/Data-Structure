#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NUM 10000

void InsertSort(int* src, int n) {
	int i, j, tmp;
	for(i = 1; i < n; ++i) {
		tmp = src[i];
		for(j = i; j > 0 && src[j - 1] > tmp; --j) {
			src[j] = src[j - 1];
		}
		src[j] = tmp;
	}
} 

void PrintArray(int* src, int n) {
	int i;
	for(i = 0; i < n; ++i) {
		printf("%-4d ", src[i]);
	}
}

int main() {
	
	#if 0
	int a[10] = { 9, 3, 1, 8, 4, 7, 2, 5, 0, 6};
	
	InsertSort(a, 10);
	
	PrintArray(a, 10);
	
	#else
	srand(time(0));
	
	int a[NUM], i;
	for(i = 0; i < NUM; ++i) {
		a[i] = rand() % 5000 + 1;
	}
	
	InsertSort(a, NUM);
	
	PrintArray(a, NUM);
	
	#endif
	return 0;
	
}
