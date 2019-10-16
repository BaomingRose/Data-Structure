#include<stdio.h>
#include<assert.h>

void insertSort(int* src, int n) {
	assert(src);
	int i, j;
	for (i = 1; i < n; ++i) {
		int tmp = src[i];
		for (j = i; j > 0 && src[j - 1] > tmp; --j) {
			src[j] = src[j - 1];;
		}
		src[j] = tmp;
	}
}

//时间：O(N^2)
//空间：O(1)
//稳定性：稳定
//适合场景：接近有序的序列,时间复杂度趋近于O(N),对于有序的序列,时间复杂度O(N)
void InsertSort(int* a, int n) {
	assert(a);
	int i;
	for (i = 0; i < n - 1; ++i) {
		//单个元素的排序
		//找到已经排好序的最后一个元素的位置
		int end = i;
		//把end+1位置的元素插到合适的位置
		int tmp = a[end + 1];
		while (end >= 0 && a[end] > tmp) {
			a[end + 1] = a[end];
			--end;
		}
		//找到合适的位置
		a[end + 1] = tmp;
	}
}

#if 0
int main() {
	int a[9] = { 9, 2, 4, 5, 1, 3, 8, 6, 7 };
	InsertSort(a, 9);
	int i;
	for (i = 0; i < 9; ++i) {
		printf("%d ", a[i]);
	}

	return 0;
}
#endif