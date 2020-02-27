#pragma once
#include <vector>
using namespace std;

//使用保留余数法的哈希函数，线性探测/二次探测处理冲突的哈希表

enum State { EMPTY, EXIST, DELETE };


//不存放重复元素
template <class T>
class hashTable {
public:
	//内部类
	struct Elem {
		T _data;
		State _state;
	};

public:
	hashTable(size_t capacity = 10) 
		: _table(capacity)
		, _size(0) {}

	bool Insert(const T& data) {
		//计算哈希地址
		size_t hashAddr = HashFunc(data);

		while (_table[hashAddr]._state != EMPTY) {
			if (_table[hashAddr]._state == EXIST && _table[hashAddr]._data == data) {
				return false;
			}

			//处理哈希冲突: 线性探测
			++hashAddr;
			if (hashAddr == _table.capacity())
				hashAddr = 0;
		}

		//插入元素
		_table[hashAddr]._data = data;
		_table[hashAddr]._state = EXIST;
		++_size;
		return true;
	}

#if 0
	bool Insert(const T& data) {
		//计算哈希地址
		size_t hashAddr = HashFunc(data);
		size_t i = 0;

		while (_table[hashAddr]._state != EMPTY) {
			if (_table[hashAddr]._state == EXIST && _table[hashAddr]._data == data) {
				return false;
			}

			//二次探测
			++i;
			hashAddr = hashAddr + 2 * i + 1;
			if (hashAddr >= _table.capacity())
				hashAddr %= _table.capacity();
		}

		//插入元素
		_table[hashAddr]._data = data;
		_table[hashAddr]._state = EXIST;
		++_size;
		return true;
	}
#endif

	int Find(const T& data) {
		size_t hashAddr = HashFunc(data);

		while (_table[hashAddr]._state != EMPTY) {
			if (_table[hashAddr]._state == EXIST && _table[hashAddr]._data == data) {
				return hashAddr;
			}

			++hashAddr;
			if (hashAddr == _table.capacity())
				hashAddr = 0;
		}

		return -1;
	}

	bool Erase(const T& data) {
		int hashAddr = Find(data);
		if (hashAddr != -1) {
			_table[hashAddr]._state = DELETE;
			--_size;
			return true;
		}

		return false;
	}

private:
	vector<Elem> _table;
	size_t _size;

	//哈希函数：保留余数法
	size_t HashFunc(const T& data) {
		return data % _table.capacity();
	}
};