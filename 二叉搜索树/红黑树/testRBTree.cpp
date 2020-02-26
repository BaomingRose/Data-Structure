#include "RBTree.hpp"


int main() {
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	RBTree<int> t;
	
	for (auto e : a) {
		t.Insert(e);
	}

	t.InOrder();
	cout << endl;

	if (t.IsValidRBTree()) {
		cout << "t is valid rbtree" << endl;
	} else {
		cout << "t is invalid rbtree" << endl;
	}

	return 0;
}