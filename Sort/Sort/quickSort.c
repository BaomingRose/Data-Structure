#include<stdio.h>
#include<stdlib.h>

int getMid(int* a, int left, int right);
int PartQuickSort2(int* a, int left, int right);
int partQuickSort3(int* a, int left, int right);
int partQuickSort4(int* a, int left, int right);

//时间复杂度：N * logN	序列有序：快排时间效率最差 -- N^2
//空间复杂度：空间可以复用，最大的递归调用链 -- logN
//单次交换
int PartQuickSort1(int* a, int left, int right) {
	int key = a[left];
	int start = left;
	//寻找大小元素交换
	while (left < right) {
		//先从右边找小于key的
		while (left < right && a[right] >= key)
			--right;
		//从左边找大于key的值
		while (left < right && a[left] <= key)
			++left;
		swap(&a[left], &a[right]);
	}
	//key的位置确定：左右相遇的位置
	swap(&a[start], &a[left]);
	return left;
}

void QuickSort(int* a, int left, int right) {
	if (left > right) {
		return;
	}
	//小区间优化：小区间不调用递归
	 else if (right - left + 1 < 5) {
		insertSort(a + left, right - left + 1);
	} else {
		int mid = partQuickSort4(a, left, right);	//PartQuickSort1
		QuickSort(a, left, mid - 1);
		QuickSort(a, mid + 1, right);
	}
}

//三数取中法
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
	//寻找大小元素交换
	while (left < right) {
		//先从右边找小于key的
		while (left < right && a[right] >= key)
			--right;
		//从左边找大于key的值
		while (left < right && a[left] <= key)
			++left;
		swap(&a[left], &a[right]);
	}
	//key的位置确定：左右相遇的位置
	swap(&a[start], &a[left]);
	return left;
}

//挖坑法
int partQuickSort3(int* a, int left, int right) {
	int mid = getMid(a, left, right);
	swap(&a[mid], &a[left]);
	int key = a[left];
	while (left < right) {
		//从右边找小
		while (left < right && a[right] >= key)
			--right;
		//填坑
		a[left] = a[right];
		//从左找大的
		while (left < right && a[left] <= key)
			++left;
		//填坑
		a[right] = a[left];
	}
	//存放key
	a[left] = key;
	return key;
}

//前后指针法
int partQuickSort4(int* a, int left, int right) {
	int mid = getMid(a, left, right);
	swap(&a[mid], &a[left]);

	//最后一个小于key的位置
	int prev = left;
	//下一个小于key的位置
	int cur = left + 1;
	int key = a[left];
	while (cur <= right) {
		//如果下一个小于key的位置于上一个小于key的位置不连续
		//说明中间有大于key的值，进行交换，大-->向后移动，小 <-- 向前移动
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
		//划分当前区间
		int mid = PartQuickSort3(a, begin, end);
		//划分左右子区间
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