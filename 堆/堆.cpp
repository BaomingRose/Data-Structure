#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

typedef int HPDataType;

typedef struct Heap {
    HPDataType* data;
	int _size;
	int _capacity; 
}Heap;

void adjustDown(Heap* hp, int n) {
	int cur = n;
	int m;
	
	while(cur * 2 + 1 < hp->_size) {
		if(cur *2 + 2 >= hp->_size) {	//没有右孩子 
			m = cur * 2 + 1;
		} else {
			if(hp->data[cur * 2 + 1] > hp->data[cur * 2 + 2]) {
				m = cur * 2 + 1;
			} else {
				m = cur * 2 + 2;
			}
		}
		
		if(hp->data[cur] < hp->data[m]) {
			int tmp = hp->data[cur];
			hp->data[cur] = hp->data[m];
			hp->data[m] = tmp;
			
			cur = m;
		} else {
			break;
		}
	}
}
 
void HeapInit(Heap* hp, HPDataType* a, int n) {
	hp->_capacity = n * 2;
	hp->_size = n;
	hp->data = (HPDataType *)calloc(hp->_capacity, sizeof(HPDataType));
	
	int i;
	for(i = 0; i < hp->_size; ++i) {
		hp->data[i] = a[i];
	}
	for(i = n / 2 - 1; i >= 0; --i) {	//从最后一个非叶子结点开始 
		adjustDown(hp, i);
	}
}

void HeapDestory(Heap* hp) {
	if(hp->data) 
		free(hp->data);
	hp->data = NULL;
}

void HeapPush(Heap* hp, HPDataType x) {
	if(hp->_size == hp->_capacity) {
		hp->_capacity *= 2;
		hp->data = (HPDataType*)realloc(hp->data, hp->_capacity * sizeof(HPDataType)); 
	}
	
	int cur = hp->_size ;
	
	hp->data[hp->_size] = x;
	++hp->_size;
	int tmp;
	while(cur > 0) {
		if(hp->data[cur] > hp->data[(cur - 1) / 2]) {
			tmp = hp->data[cur];
			hp->data[cur] = hp->data[(cur - 1) / 2];
			hp->data[(cur - 1) / 2] = tmp;
			cur = (cur - 1) / 2;
		} else {
			break;
		}
	}
}

//堆顶和最后元素交换， 向下调整 
void HeapPop(Heap* hp) {
	if(hp->_size == 0) {
		return ;
	}
	--hp->_size ;
	
	int tmp = hp->data[0];
	hp->data[0] = hp->data[hp->_size];
	hp->data[hp->_size] = tmp;
	
	adjustDown(hp, 0);
}

HPDataType HeapTop(Heap* hp) {
	if(hp->_size == 0) {
		return (HPDataType)0;
	}
	return hp->data[0];
}

int HeapSize(Heap* hp) {
	return hp->_size ;
}

int HeapEmpty(Heap* hp) {
	return hp->_size == 0;
}

void HeapPrint(Heap* hp) {
	int i, rn = 0, bin = 2;
	for(i = 0; i < hp->_size ; ++i) {
		cout << hp->data[i] << " ";
		if(i == rn) {
			cout << endl;
			rn += bin;
			bin = bin * 2;
		}
	}
}

void HeapPrintS(Heap* hp) {
	int i;
	for(i = 0; i < hp->_size ; ++i) {
		cout << hp->data[i] << " ";
	}
}

// 堆排序 
void HeapSort(Heap* hp) {
	int tmp = hp->_size;
	
	while(hp->_size > 1) {
		HeapPop(hp);
	}
	
	hp->_size = tmp;
}
 
int main() {
	int a[10] = {29, 72, 48, 53, 45, 30, 18, 36, 15, 35};
	Heap hp;
	
	HeapInit(&hp, a, 10);
	adjustDown(&hp, 0);
	HeapPrint(&hp);
	
	cout << endl << endl;
	
	HeapPush(&hp, 10);
	HeapPrint(&hp);
	
	cout << endl << endl;
	HeapPop(&hp);
	HeapPrint(&hp);
	
	cout << endl << endl;
	HeapSort(&hp);
	HeapPrintS(&hp);
	
	HeapDestory(&hp);

	return 0;
}
