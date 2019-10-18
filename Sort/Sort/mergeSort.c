#include<stdio.h>
#include<stdlib.h>

//时间：N * logN
//空间：N + logN —— N
//稳定性：稳定
void _mergeSort(int* a, int left, int right, int* tmp) {
	if (left >= right) {
		return;
	}
	//分解
	int mid = left + (right - left) / 2;
	_mergeSort(a, left, mid, tmp);
	_mergeSort(a, mid + 1, right, tmp);

	//归并
	int begin1 = left, end1 = mid, begin2 = mid + 1, end2 = right;
	int tmpindex = begin1;
	while (begin1 <= end1 && begin2 <= end2) {
		if (a[begin1] <= a[begin2])
			tmp[tmpindex++] = a[begin1++];
		else 
			tmp[tmpindex++] = a[begin2++];
	}

	while (begin1 <= end1) 
		tmp[tmpindex++] = a[begin1++];
	while (begin2 <= end2) 
		tmp[tmpindex++] = a[begin2++];
	//拷贝到原有数组对应区间
	memcpy(a + left, tmp + left, (right - left + 1) * sizeof(int));
}

void mergeSort(int* a, int n) {
	int* tmp = (int*)malloc(sizeof(int) * n);
	_mergeSort(a, 0, n - 1, tmp);
	free(tmp);
}

#if 0
int main() {
	int a[10] = { 9, 1, 3, 7, 5, 2, 6, 4, 0, 8 };
	mergeSort(a, 10);
	int i;
	for (i = 0; i < 10; ++i) {
		printf("%d ", a[i]);
	}

	return 0;
}
#endif