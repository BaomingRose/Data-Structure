#include "BitSet.hpp"

int main() {
	int array[] = { 1, 3, 7, 4, 12, 16, 19, 13, 22, 18 };

	bitSet<24> bst;

	for (auto e : array) {
		bst.set(e);
	}

	cout << "size():" << endl;
	cout << bst.size() << endl;
	cout << "count():" << endl;
	cout << bst.count() << endl;

	if (bst.test(19)) {
		cout << "19 bit is 1" << endl;
	}
	else {
		cout << "19 bit is not 1" << endl;
	}

	cout << "É¾³ı19" << endl;
	bst.reset(19);

	if (bst.test(19)) {
		cout << "19 bit is 1" << endl;
	} else {
		cout << "19 bit is not 1" << endl;
	}

	return 0;
}