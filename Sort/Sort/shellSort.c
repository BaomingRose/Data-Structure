#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<time.h>

//ʱ�䣺O(N^1.3 - N^2)
//�ռ䣺O(1)
//�ȶ��ԣ����ȶ�
void ShellSort(int *a, int n) {
	int gap = n;
	int i;
	//int num;
	//for (; gap >= 1; gap -= num) 	//������Ĵ���
	//for (num = 0; num < gap; ++num)	//����������
	while (gap > 1) {
		//gap > 1  --> Ԥ�������
		//gap = 1  -->�������
		gap = gap / 3 + 1;	//��֤���һ��gapΪ1�Ĳ�������
		for (i = 0; i < n - gap; ++i) {	//���������
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0 && a[end] > tmp) {
				a[end + gap] = a[end];
				end -= gap;
			}
			a[end + gap] = tmp;
		}
	}
}

void testSort() {
	srand(time((unsigned int)NULL));
	int i, num = 10000;
	while (scanf("%d", &num)) {
		int* arr1 = (int*)malloc(sizeof(int) * num);
		int* arr2 = (int*)malloc(sizeof(int) * num);

		for (i = 0; i < num; ++i) {
			arr1[i] = rand();
		}

		memcpy(arr2, arr1, sizeof(int) * num);

		size_t begin1, end1, begin2, end2;
		begin1 = clock();
		insertSort(arr1, num);
		end1 = clock();
		printf("InsertSort:%d\n", end1 - begin1);

		begin2 = clock();
		ShellSort(arr2, num);
		end2 = clock();
		for (i = 0; i < num; ++i) {
			printf("%d ", arr2[i]);
		}
		printf("ShellSort:%d\n", end2 - begin2);
	}
}

#if 0
int main() {
	int a[10] = { 10, 3, 6, 2, 8, 7, 4, 5, 1, 9 };
	ShellSort(a, 10);
	int i;
	for (i = 0; i < 10; ++i) {
		printf("%d ", a[i]);
	}
	putchar('\n');
	testSort();

	return 0;
}
#endif