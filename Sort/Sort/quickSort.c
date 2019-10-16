#include<stdio.h>
#include<stdlib.h>

int getMid(int* a, int left, int right);
int PartQuickSort2(int* a, int left, int right);
int partQuickSort3(int* a, int left, int right);
int partQuickSort4(int* a, int left, int right);

//ʱ�临�Ӷȣ�N * logN	�������򣺿���ʱ��Ч����� -- N^2
//�ռ临�Ӷȣ��ռ���Ը��ã����ĵݹ������ -- logN
//���ν���
int PartQuickSort1(int* a, int left, int right) {
	int key = a[left];
	int start = left;
	//Ѱ�Ҵ�СԪ�ؽ���
	while (left < right) {
		//�ȴ��ұ���С��key��
		while (left < right && a[right] >= key)
			--right;
		//������Ҵ���key��ֵ
		while (left < right && a[left] <= key)
			++left;
		swap(&a[left], &a[right]);
	}
	//key��λ��ȷ��������������λ��
	swap(&a[start], &a[left]);
	return left;
}

void QuickSort(int* a, int left, int right) {
	if (left > right) {
		return;
	}
	//С�����Ż���С���䲻���õݹ�
	 else if (right - left + 1 < 5) {
		insertSort(a + left, right - left + 1);
	} else {
		int mid = partQuickSort4(a, left, right);	//PartQuickSort1
		QuickSort(a, left, mid - 1);
		QuickSort(a, mid + 1, right);
	}
}

//����ȡ�з�
int getMid(int* a, int left, int right) {
	int mid = left + (right - left) / 2;
	if (a[mid] > a[left]) {
		if (a[mid] < a[right])
			return mid;
		else {
			//mid > left,right
			if (a[left] > a[right])
				return left;
			else
				return right;
		}
	} else {
		if (a[left] < a[right])
			return left;
		else {
			//left >= right , mid
			if (a[mid] > a[right])
				return mid;
			else
				return right;
		}
	}
}

int PartQuickSort2(int* a, int left, int right) {
	int mid = getMid(a, left, right);
	swap(&a[left], &a[mid]);
	int key = a[left];
	int start = left;
	//Ѱ�Ҵ�СԪ�ؽ���
	while (left < right) {
		//�ȴ��ұ���С��key��
		while (left < right && a[right] >= key)
			--right;
		//������Ҵ���key��ֵ
		while (left < right && a[left] <= key)
			++left;
		swap(&a[left], &a[right]);
	}
	//key��λ��ȷ��������������λ��
	swap(&a[start], &a[left]);
	return left;
}

//�ڿӷ�
int partQuickSort3(int* a, int left, int right) {
	int mid = getMid(a, left, right);
	swap(&a[mid], &a[left]);
	int key = a[left];
	while (left < right) {
		//���ұ���С
		while (left < right && a[right] >= key)
			--right;
		//���
		a[left] = a[right];
		//�����Ҵ��
		while (left < right && a[left] <= key)
			++left;
		//���
		a[right] = a[left];
	}
	//���key
	a[left] = key;
	return key;
}

//ǰ��ָ�뷨
int partQuickSort4(int* a, int left, int right) {
	int mid = getMid(a, left, right);
	swap(&a[mid], &a[left]);

	//���һ��С��key��λ��
	int prev = left;
	//��һ��С��key��λ��
	int cur = left + 1;
	int key = a[left];
	while (cur <= right) {
		//�����һ��С��key��λ������һ��С��key��λ�ò�����
		//˵���м��д���key��ֵ�����н�������-->����ƶ���С <-- ��ǰ�ƶ�
		if (a[cur] < key && ++prev != cur) {
			swap(&a[prev], &a[cur]);
		}
		++cur;
	}
	swap(&a[prev], &a[left]);
	return prev;
}

#if 0
void QuickSortNoR(int* a, int left, int right) {
	stack<int> st;
	if (left < right) {
		st.push(right);
		st.push(left);
	}
	while (!st.empty()) {
		int begin = st.top();
		st.pop();
		int end = st.top();
		st.pop();
		//���ֵ�ǰ����
		int mid = PartQuickSort3(a, begin, end);
		//��������������
		if (begin < mid - 1) {
			st.push(mid - 1);
			st.push(begin);
		}
		if (mid + 1 < end) {
			st.push(end);
			st.push(mid + 1);
		}
	}
}
#endif

int main() {
	int a[10] = { 9, 5, 1, 3, 7, 8, 6, 4, 2, 0 };
	QuickSort(a, 0, 9);
	int i;
	for (i = 0; i < 10; ++i) {
		printf("%d ", a[i]);
	}

	return 0;
}