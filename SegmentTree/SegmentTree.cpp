#include <climits>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//��С�߶�����ʵʱ�����������Сֵ�����ʵ�ֵ����������ұյ�
class MinSegmentTree {
public:
	MinSegmentTree(const vector<int>& data) {
		_size = data.size();
		_minTree.resize(2 * _size, 0);

		for (int i = 0; i < _size; ++i) {
			_minTree[_size + i] = data[i];
		}

		for (int i = _size - 1; i > 0; --i) {
			_minTree[i] = min(_minTree[2 * i], _minTree[2 * i + 1]);
		}
	}

	void update(int i, int value) {
		i += _size;
		_minTree[i] = value;

		while (i > 1) {
			i /= 2;
			_minTree[i] = min(_minTree[2 * i], _minTree[2 * i + 1]);
		}
	}

	int minBySegment(int left, int right) {
		left += _size;
		right += _size;

		int res = INT_MAX;

		//���ѭ��������Ĺؼ�
		while (left < right) {
			if ((left & 1) == 1) {
				res = min(res, _minTree[left]);
				++left;
			}

			//������ɻ���Ϊ���������ұյģ����������Ϊ��������Ч��������һ�����䵥��ż��������Ҫ�Ȱ����ż��ժ��
			if ((right & 1) == 1) {
				--right;
				res = min(res, _minTree[right]);
			}

			left >>= 1;
			right >>= 1;
		}

		return res;
	}

private:
	vector<int> _minTree;
	int _size;
};


//����߶�����ʵʱ��������ĺͣ���Ȼ������ҿ�����
class SumSegmentTree {
public:
	SumSegmentTree(const vector<int>& data) {
		_size = data.size();
		_tree.resize(2 * _size, 0);

		for (int i = 0; i < _size; ++i) {
			_tree[_size + i] = data[i];
		}

		for (int i = _size - 1; i > 0; --i) {
			_tree[i] = _tree[2 * i] + _tree[2 * i + 1];
		}
	}

	void update(int index, int value) {
		int n = index + _size;
		_tree[n] = value;

		while (n > 1) {
			n >>= 1;
			_tree[n] = _tree[2 * n] + _tree[2 * n + 1];
		}
	}

	int sumBySegment(int left, int right) {
		left += _size;
		right += _size;

		int sum = 0;

		while (left < right) {
			if ((left & 1) == 1) {
				sum += _tree[left];
				++left;
			}

			if ((right & 1) == 1) {
				--right;
				sum += _tree[right];
			}

			left >>= 1;
			right >>= 1;
		}
		return sum;
	}
private:
	vector<int> _tree;
	int _size;
};

void testMinSegmentTree() {
	vector<int> data = { 1, 2, 3, 4, 5, 6, 7 };
	MinSegmentTree tree = MinSegmentTree(data);

	cout << tree.minBySegment(1, 5) << endl;

	tree.update(4, 0);
	tree.update(5, -10);
	cout << tree.minBySegment(1, 5) << endl;
}

void testSumSegmentTree() {
	vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8 };
	SumSegmentTree tree = SumSegmentTree(data);

	cout << tree.sumBySegment(1, 5) << endl;

	tree.update(4, 0);
	cout << tree.sumBySegment(1, 5) << endl;

	tree.update(5, 100);
	cout << tree.sumBySegment(1, 5) << endl;
	cout << tree.sumBySegment(1, 6) << endl;
}

int main() {
	//testMinSegmentTree();

	testSumSegmentTree();

	return 0;
}