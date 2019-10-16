#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//ʱ�䣺O(N^2)
//�ռ䣺O(1)
//�ȶ��ԣ����Ա���ȶ�
void selectSort(int* a, int n) {
	int begin = 0, end = n - 1;
	while (begin < end) {
		//ÿ��ѡһ�����ĺ���С��,�ŵ���Ӧ��λ��
		int i, max, min;
		max = min = begin;
		//С��ѡ��һ�������ѡ���һ��
		for (i = begin; i <= end; ++i) {
			if (a[i] < a[min])
				min = i;
			if (a[i] >= a[max])
				max = i;
		}
		//min--->begin	max--->end
		swap(&a[begin], &a[min]);
		//�ж����Ԫ�ص�λ���Ƿ����仯
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