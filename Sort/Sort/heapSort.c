#include<stdio.h>
#include<stdlib.h>

void ShiftDown(int* a, int n, int root) {
	int child = root * 2 + 1;
	int parent = root;
	while (child < n) {
		if (child + 1 < n) {
			if (a[child] < a[child + 1]) {
				child += 1;
			}
		}
		if (a[parent] < a[child]) {
			int tmp = a[child];
			a[child] = a[parent];
			a[parent] = tmp;
			parent = child;
			child = parent * 2 + 1;
		} else {
			break;
		}
	}
}

void HeapSort(int* a, int n) {
	//建堆，最后一棵子树开始 ：(n - 2) / 2
	int i, end;
	for (i = (n - 2) / 2; i >= 0; --i) {
		ShiftDown(a, n, i);
	}
	//排序：1.swap	2.shiftdown
	end = n - 1;
	while (end) {
		swap(&a[0], &a[end]);
		ShiftDown(a, end, 0);
		--end;
	}
}

#if 0
int main() {
	int a[10] = { 10, 3, 5, 2, 7, 9, 4, 1, 6, 8 };
	HeapSort(a, 10);
	int i;
	for (i = 0; i < 10; ++i) {
		printf("%d ", a[i]);
	}

	return 0;
}
#endif