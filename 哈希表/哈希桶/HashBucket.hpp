#pragma once
#include <iostream>
#include "common.h"
#include <string>
#include <vector>
using namespace std;

template <class T>
class TTOINTDEF {
public:
	T operator()(const T& data) {
		return data;
	}
};

class StrTOINT {
public:
	size_t operator()(const string& s) {
		const char* str = s.c_str();
		unsigned int seed = 131; // 31 131 1313 13131 131313
		unsigned int hash = 0;
		while (*str) {
			hash = hash * seed + (*str++);
		}
		return (hash & 0x7FFFFFFF);
	}
};

template <class T>
struct HashBucketNode {
	HashBucketNode<T>* _pNext;
	T _data;

	HashBucketNode(const T& data = T()) : _pNext(nullptr), _data(data) {}
};

//元素唯一
template <class T, class TTOINT = TTOINTDEF<T>>
class HashBucket {
	typedef HashBucketNode<T> Node;
public:
	HashBucket(size_t capacity = 10)
		:_table(GetNextPrime(capacity), nullptr)
		, _size(0) {}

	~HashBucket() {
		Clear();
	}

	bool Insert(const T& data) {
		//找当前元素的桶号
		size_t bucketNo = HashFunc(data);

		//确认当前元素是否在当前链表中
		Node* pCur = _table[bucketNo];
		while (pCur) {
			if (pCur->_data == data)
				return false;

			pCur = pCur->_pNext;
		}

		pCur = new Node(data);
		pCur->_pNext = _table[bucketNo];
		_table[bucketNo] = pCur;
		++_size;
		return true;
	}

	Node* Find(const T& data) {
		size_t bucketNo = HashFunc(data);

		Node* pCur = _table[bucketNo];
		while (pCur) {
			if (pCur->_data == data)
				return pCur;

			pCur = pCur->_pNext;
		}

		return nullptr;
	}

	bool Erase(const T& data) {
		size_t bucketNo = HashFunc(data);

		Node* pCur = _table[bucketNo];
		Node* pPrev = nullptr;
		while (pCur) {
			if (pCur->_data == data) {
				//删除
				if (nullptr == pPrev)
					_table[bucketNo] = pCur->_pNext;
				else
					pPrev->_pNext = pCur->_pNext;

				delete pCur;
				--_size;
				return true;
			}

			pPrev = pCur;
			pCur = pCur->_pNext;
		}

		return false;
	}

	void Clear() {
		for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo) {
			Node* pCur = _table[bucketNo];
			//依次头删
			while (pCur) {
				_table[bucketNo] = pCur->_pNext;
				delete pCur;
				pCur = _table[bucketNo];
			}
		}
		_size = 0;
	}

	void Swap(HashBucket<T, TTOINT>& newHT) {
		_table.swap(newHT._table);
		swap(_size, newHT._size);
	}

	size_t BucketCount() const {
		return _table.capacity();
	}

	size_t BucketSize(size_t bucketNo) {
		assert(bucketNo < _table.capacity());
		Node* pCur = _table[bucketNo];
		size_t count = 0;
		while (pCur) {
			++count;
			pCur = pCur->_pNext;
		}
		return count;
	}

	size_t Bucket(const T& data) {
		return HashFunc(data);
	}

	void PrintHashBucket() {
		for (size_t i = 0; i < _table.capacity(); ++i) {
			cout << "table[" << i << "]:";
			Node* pCur = _table[i];
			while (pCur) {
				cout << pCur->_data << "-->";
				pCur = pCur->_pNext;
			}
			cout << "NULL" << endl;
		}
		cout << endl;
	}

private:
	vector<Node*>  _table;
	size_t _size;

	//保证取模符号之前是整形
	size_t HashFunc(const T& data) {
		return TTOINT()(data) % _table.capacity();
	}

	void CheckCapacity() {
		if (_size == _table.capacity()) {
			HashBucket<T, TTOINT> newHB(GetNextPrime(_table.capacity()));
		
			for (size_t i = 0; i < _table.capacity(); ++i) {
				Node* pCur = _table[i];
				while (pCur) {
					//将pCur结点从旧哈希桶中移除
					_table[i] = pCur->_pNext;

					//计算PCur在新哈希桶中的位置
					size_t bucketNO = newHB.HashFunc(pCur->_data);

					//将pCur结点插入到新哈希表bucketNo桶中
					pCur->_pNext = newHB._table[bucketNO];
					newHB._table[bucketNO] = pCur;

					//取旧哈希桶下一个元素
					pCur = _table[i];
				}
			}
			this->Swap(newHB);
		}
	}
};