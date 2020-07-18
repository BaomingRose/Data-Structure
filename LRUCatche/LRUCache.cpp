#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LRUCache {
public:
	LRUCache(int capacity) :_capacity(capacity) {	}

	int get(int key) {
		auto lit = _ht.find(key);
		if (lit != _ht.end()) {
			pair<int, int> data = *(lit->second);
			_data.push_front(data);
			_data.erase(lit->second);

			_ht[key] = _data.begin();

			return data.second;
		}
		return -1;
	}

	void put(int key, int value) {
		auto lit = _ht.find(key);
		if (lit != _ht.end()) {
			pair<int, int> data = *(lit->second);
			data.second = value;
			_data.push_front(data);
			_data.erase(lit->second);
			_ht[key] = _data.begin();
		} else {
			pair<int, int> data = make_pair(key, value);
			_data.push_front(data);
			_ht[key] = _data.begin();
			if (_data.size() > _capacity) {
				//需要删除哈希表中的值，不然get的时候还会找到被删掉的地址
				//傻了，end()是无值啊
				//auto it = _data.end();
				auto it = _data.end();
				it--;
				int k = it->first;
				//cout << k << endl;
				_ht.erase(k);
				_data.pop_back();
			}
		}
	}

private:
	unordered_map<int, list<pair<int, int>>::iterator> _ht;
	list<pair<int, int>> _data;
	int _capacity;
};

int main() {
	LRUCache cache = LRUCache(2);

	cache.put(1, 2);
	cache.put(2, 2);
	cout << cache.get(1) << endl;
	cache.put(3, 3);
	cout << cache.get(2) << endl;
	cache.put(4, 4);
	cout << cache.get(1) << endl;
	cout << cache.get(3) << endl;
	cout << cache.get(4) << endl;

	return 0;
}