#include<stdio.h>
#include<stdlib.h>

//时间：O(N - N^2)
//空间：O(1)
//稳定型：稳定
//优化：加一个标记，如果一趟冒泡没有交换动作，直接跳出
void BubbleSort(int* a, int n) {
	int i, j;
	for (i = n; i > 0; --i) {
		int flag = 0;
		for (j = 0; j < i - 1; j++) {
			if (a[j] > a[j + 1]) {
				swap(&a[j], &a[j + 1]);
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
}

#if 0
int main() {
	int a[10] = { 10, 3, 5, 2, 7, 9, 4, 1, 6, 8 };
	BubbleSort(a, 10);
	int i;
	for (i = 0; i < 10; ++i) {
		printf("%d ", a[i]);
	}


	return 0;
}
#endif