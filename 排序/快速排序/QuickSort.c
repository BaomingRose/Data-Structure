#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"queue.h"
#define NUM 10000

void swapArgs(int *pa, int *pb) {
	int tmp;
	tmp = *pa;
	*pa = *pb;
	*pb = tmp;
}

//˫ָ�뷨1,ѡ��Ԫ��Ϊ��ŦԴ,��ͣ���� 
int doublePointerWay1(int * src, int start, int end) {
	int a = start, b = end;
	int flag = 0;

	while (src[b] > src[a]) {
		b--;
	}

	while (a < b) {
		swapArgs(src + b, src + a);
		flag = !flag;

		while (src[b] >= src[a]) {
			flag ? a++ : b--;
		}
	}

	return flag ? b : a;
}

//˫ָ�뷨2,ѡ�м�Ϊ��ŦԴ 
int doublePointerWay2(int * src, int start, int end) {
	int a = start, b = end - 1;
	int mid = (start + end) / 2;

	swapArgs(src + mid, src + end);

	while (a <= b) {
		while (a < end && src[a] <= src[end]) {
			a++;
		}

		while (b > 0 && src[b] >= src[end]) {
			b--;
		}

		if (a == b && (a == 0 || a == end)) {
			break;
		}

		if (a < b) {
			swapArgs(src + a, src + b);
		}
	}
	swapArgs(src + a, src + end);
	return a;
}

//�ڿӷ� 
int digWay(int * src, int start, int end) {
	int a = start, b = end;
	int flag = 0;
	int tmp = src[start];

	while (1) {
		while (b > start && src[b] >= tmp) {
			b--;
		}

		if (a < b) {
			src[a] = src[b];
		}
		else {
			src[a] = tmp;
			return a;
		}

		while (a < end && src[a] <= tmp) {
			a++;
		}

		if (a < b) {
			src[b] = src[a];
		}
		else {
			src[b] = tmp;
			return b;
		}
	}
}

//Hoare�� (��ֵȡ�з�) (Ч�����) 
int HoareWay(int * src, int start, int end) {
	int a = start + 1, b = end - 2;
	int mid = (start + end) / 2;

	if (src[start] > src[mid]) {
		swapArgs(src + start, src + mid);
	}
	if (src[mid] > src[end]) {
		swapArgs(src + mid, src + end);
	}
	if (src[start] > src[mid]) {
		swapArgs(src + start, src + mid);
	}

	if (end - start <= 2) {
		return mid;
	}

	swapArgs(src + mid, src + end - 1);

	while (a <= b) {
		while (a < end - 1 && src[a] <= src[end - 1]) {
			a++;
		}

		while (b > 1 && src[b] >= src[end - 1]) {
			b--;
		}

		if (a == b && (a == 1 || a == end - 1)) {
			break;
		}

		if (a < b) {
			swapArgs(src + a, src + b);
		}
	}
	swapArgs(src + a, src + end - 1);
	return a;
}

void dealQuickSort(int * src, int start, int end) {
	int mid;
	if (start + 8 < end) {
		mid = HoareWay(src, start, end);
		//mid = doublePointerWay1(src, start, end);
		//mid = doublePointerWay2(src, start, end);
		//mid = digWay(src, start, end);
		dealQuickSort(src, start, mid - 1);
		dealQuickSort(src, mid + 1, end);
	}
	else {
		//InsertSort(src + start, end - start + 1);
	}
}

//����ӿ� 
void QuickSort(int * src, int n) {
	dealQuickSort(src, 0, n - 1);
}


#if 1
//�ǵݹ���� (��ʡ�ռ�)
void QuickSortNonR(int * src, int n) {
	int start, end;
	int mid;
	Queue qu;

	QueueInit(&qu);

	QueuePush(&qu, 0);
	QueuePush(&qu, n - 1);

	while (!QueueIsEmpty(&qu)) {
		start = QueueTop(&qu);
		QueuePop(&qu);
		end = QueueTop(&qu);
		QueuePop(&qu);
		mid = HoareWay(src, start, end);

		if (start < mid - 1) {
			QueuePush(&qu, start);
			QueuePush(&qu, mid);
		}

		if (mid + 1 < end) {
			QueuePush(&qu, mid + 1);
			QueuePush(&qu, end);
		}
	}

	QueueDestory(&qu);
}
#endif

void printArray(int * src, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", src[i]);
	}
	putchar('\n');
}
