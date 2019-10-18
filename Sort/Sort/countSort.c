#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void countSort(int* a, int n) {
	//范围： 0—最大值
	//范围：最小值——最大值
	int min = a[0], max = a[0];
	int i;
	//获取数据的范围
	for (i = 1; i < n; ++i) {
		if (a[i] < min)
			min = a[i];
		if (a[i] > max)
			max = a[i];
	}
	int range = max - min + 1;
	int* countArr = (int*)malloc(sizeof(int) * range);
	memset(countArr, 0, sizeof(int) * range);
	//计数
	for (i = 0; i < n; ++i) {
		countArr[a[i] - min]++;
	}
	//排序
	int index = 0;
	for (i = 0; i < range; ++i) {
		while (countArr[i]--) {
			a[index++] = i + min;
		}
	}
}

int main() {
	int a[10] = { 9, 3, 4, 5, 9, 3, 4, 5, 1, 0 };
	countSort(a, 10);
	int i;
	for (i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	return 0;
}