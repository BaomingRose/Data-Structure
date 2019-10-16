#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//时间：O(N^2)
//空间：O(1)
//稳定性：可以变成稳定
void selectSort(int* a, int n) {
	int begin = 0, end = n - 1;
	while (begin < end) {
		//每次选一个最大的和最小的,放到相应的位置
		int i, max, min;
		max = min = begin;
		//小的选第一个，大的选最后一个
		for (i = begin; i <= end; ++i) {
			if (a[i] < a[min])
				min = i;
			if (a[i] >= a[max])
				max = i;
		}
		//min--->begin	max--->end
		swap(&a[begin], &a[min]);
		//判断最大元素的位置是否发生变化
		if (max == begin)
			max = min;
		swap(&a[end], &a[max]);
		begin++;
		--end;
	}
}

#if 0
int main() {
	int a[10] = { 10, 3, 5, 2, 7, 9, 4, 1, 6, 8 };
	selectSort(a, 10);
	int i;
	for (i = 0; i < 10; ++i) {
		printf("%d ", a[i]);
	}



	return 0;
}
#endif