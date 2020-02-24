#include "BSTree.hpp"

void testBSTree() {
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int> t;
	
	for (auto e : a) {
		t.Insert(e);
	}

	t.InOrder();
	cout << endl << endl;

	cout << "t.Erase(6):" << endl;
	t.Erase(6);
	t.InOrder();

	cout << endl << "t.Erase(5):" << endl;
	t.Erase(5);
	t.InOrder();

	/*
	cout << "BSTree::find(0)" << endl;
	auto pRet = t.find(0);
	if (pRet) {
		cout << "0 is in BSTree" << endl;
	} else {
		cout << "0 is not in BSTree" << endl;
	}
	*/
}

int main() {
	testBSTree();

	return 0;
}