#include<stdio.h>
#include<stdlib.h>

//ʱ�䣺O(N - N^2)
//�ռ䣺O(1)
//�ȶ��ͣ��ȶ�
//�Ż�����һ����ǣ����һ��ð��û�н���������ֱ������
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