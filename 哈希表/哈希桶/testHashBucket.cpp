#if 0
#include "HashBucket.hpp"

int main() {
	HashBucket<int> hb;
	hb.Insert(21);
	hb.Insert(13);
	hb.Insert(15);
	hb.Insert(31);
	hb.Insert(47);
	hb.Insert(88);

	hb.PrintHashBucket();

	if (hb.Find(47)) {
		cout << "47 is in hashBucket[" << hb.Bucket(47) << "]" << endl;
	} else {
		cout << "47 is not in hashBucket" << endl;
	}

	cout << "É¾µô47" << endl;
	hb.Erase(47);

	if (hb.Find(47)) {
		cout << "47 is in hashBucket[" << hb.Bucket(47) << "]" << endl;
	} else {
		cout << "47 is not in hashBucket" << endl;
	}

	return 0;
}
#endif