#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define NUM 10000 

void dealMergeSort(int * src, int * tmp, int start, int end) {
	if (start >= end) {
		return;
	}

	int mid = (start + end) / 2;
	dealMergeSort(src, tmp, start, mid);
	dealMergeSort(src, tmp, mid + 1, end);

	int a = start;
	int b = mid + 1;
	int c = start;
	while (a <= mid && b <= end) {
		if (src[a] < src[b]) {
			tmp[c] = src[a];
			a++;
		}
		else {
			tmp[c] = src[b];
			b++;
		}
		c++;
	}

	for (; a <= mid; a++, c++) {
		tmp[c] = src[a];
	}

	for (; b <= end; b++, c++) {
		tmp[c] = src[b];
	}

	int i;
	for (i = start; i <= end; i++) {
		src[i] = tmp[i];
	}
}

void MergeSort(int * src, int n) {
	int * tmp = (int *)malloc(n * sizeof(int));

	dealMergeSort(src, tmp, 0, n - 1);

	free(tmp);
}

void PrintArray(int* src, int n) {
	int i;
	for(i = 0; i < n; ++i) {
		printf("%d\t", src[i]);
	}
}

int main() {
	
	#if 1
	int a[10] = { 9, 3, 1, 8, 4, 7, 2, 5, 0, 6};
	
	MergeSort(a, 10);
	
	PrintArray(a, 10);
	
	#else
	srand(time(0));
	
	int a[NUM], i;
	for(i = 0; i < NUM; ++i) {
		a[i] = rand() % 5000 + 1;
	}
	
	MergeSort(a, NUM);
	
	PrintArray(a, NUM);
	
	#endif
	return 0;
	
}
