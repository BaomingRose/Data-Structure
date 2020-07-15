/*================================================
 * description：并查集的实现
=================================================*/

#include <iostream>
#include <vector>
using namespace std;

class UnoinFindSet {
public:
	UnoinFindSet(int size) {
		_info.resize(size, -1);
	}

	int findParent(int index) {
		while (_info[index] >= 0) {
			index = _info[index];
		}
		return index;
	}

	void mergeSet(int a, int b) {
		int a_parent = findParent(a);
		int b_parent = findParent(b);

		if (a_parent != b_parent) {
			_info[a_parent] += _info[b_parent];
			_info[b_parent] = a_parent;
		}
	}

	int num_of_set() {
		int size = 0;
		for (const auto& e : _info) {
			if (e < 0) {
				size += 1;
			}
		}
		return size;
	}
private:
	vector<int> _info;
};


int main() {
	int a[3][3] = { {1, 1, 0}, {1, 1, 0}, {0, 0, 1} };
	UnoinFindSet ufs(3);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < i; ++j) {
			if (a[i][j] == 1) {
				ufs.mergeSet(i, j);
			}
		}
	}

	cout << ufs.num_of_set() << endl;

	return 0;
}
