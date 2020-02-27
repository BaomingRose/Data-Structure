#pragma once
#include <vector>
using namespace std;

//ʹ�ñ����������Ĺ�ϣ����������̽��/����̽�⴦���ͻ�Ĺ�ϣ��

enum State { EMPTY, EXIST, DELETE };


//������ظ�Ԫ��
template <class T>
class hashTable {
public:
	//�ڲ���
	struct Elem {
		T _data;
		State _state;
	};

public:
	hashTable(size_t capacity = 10) 
		: _table(capacity)
		, _size(0) {}

	bool Insert(const T& data) {
		//�����ϣ��ַ
		size_t hashAddr = HashFunc(data);

		while (_table[hashAddr]._state != EMPTY) {
			if (_table[hashAddr]._state == EXIST && _table[hashAddr]._data == data) {
				return false;
			}

			//�����ϣ��ͻ: ����̽��
			++hashAddr;
			if (hashAddr == _table.capacity())
				hashAddr = 0;
		}

		//����Ԫ��
		_table[hashAddr]._data = data;
		_table[hashAddr]._state = EXIST;
		++_size;
		return true;
	}

#if 0
	bool Insert(const T& data) {
		//�����ϣ��ַ
		size_t hashAddr = HashFunc(data);
		size_t i = 0;

		while (_table[hashAddr]._state != EMPTY) {
			if (_table[hashAddr]._state == EXIST && _table[hashAddr]._data == data) {
				return false;
			}

			//����̽��
			++i;
			hashAddr = hashAddr + 2 * i + 1;
			if (hashAddr >= _table.capacity())
				hashAddr %= _table.capacity();
		}

		//����Ԫ��
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

	//��ϣ����������������
	size_t HashFunc(const T& data) {
		return data % _table.capacity();
	}
};