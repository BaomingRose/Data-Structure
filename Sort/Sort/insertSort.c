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

//ʱ�䣺O(N^2)
//�ռ䣺O(1)
//�ȶ��ԣ��ȶ�
//�ʺϳ������ӽ����������,ʱ�临�Ӷ�������O(N),�������������,ʱ�临�Ӷ�O(N)
void InsertSort(int* a, int n) {
	assert(a);
	int i;
	for (i = 0; i < n - 1; ++i) {
		//����Ԫ�ص�����
		//�ҵ��Ѿ��ź�������һ��Ԫ�ص�λ��
		int end = i;
		//��end+1λ�õ�Ԫ�ز嵽���ʵ�λ��
		int tmp = a[end + 1];
		while (end >= 0 && a[end] > tmp) {
			a[end + 1] = a[end];
			--end;
		}
		//�ҵ����ʵ�λ��
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