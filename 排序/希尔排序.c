#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NUM 10000

void ShellSort(int * src, int n) {
	int i, j, k;
	int gap, tmp;

	for (gap = n / 2; gap; gap /= 2) { 
		for (k = 0; k < gap; k++) {
			for (i = gap + k; i < n; i += gap) {
				tmp = src[i];

				for (j = i; j >= gap && src[j - gap] > tmp; j -= gap) {
					src[j] = src[j - gap];
				}

				src[j] = tmp;
			}
		}
	}
}


#if 0
void ShellSort(int a[], int length) {
	int increment;
	int i, j;
	int temp;
	for (increment = length / 2; increment > 0; increment /= 2)  {	//�������Ʋ���,���ݼ���1
		// i�ӵ�step��ʼ���У�ӦΪ��������ĵ�һ��Ԫ��
		// �����Ȳ������ӵڶ�����ʼ����
		for (i = increment; i < length; i++) {
			temp = a[i];
			for (j = i - increment; j >= 0 && temp < a[j]; j -= increment) {
				a[j + increment] = a[j];
			}
			a[j + increment] = temp; //����һ��λ������
		}
	}
}
#endif

void PrintArray(int* src, int n) {
	int i;
	for(i = 0; i < n; ++i) {
		printf("%d\t", src[i]);
	}
}

int main() {
	
	#if 0
	int a[10] = { 9, 3, 1, 8, 4, 7, 2, 5, 0, 6};
	
	ShellSort(a, 10);
	
	PrintArray(a, 10);
	
	#else
	srand(time(0));
	
	int a[NUM], i;
	for(i = 0; i < NUM; ++i) {
		a[i] = rand() % 5000 + 1;
	}
	
	ShellSort(a, NUM);
	
	PrintArray(a, NUM);
	
	#endif
	return 0;
	
}
