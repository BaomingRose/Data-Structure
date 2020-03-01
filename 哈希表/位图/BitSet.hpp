#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <size_t N>
class bitSet {
public:
	// n/8+1的必要性，小于8则为0不够
	bitSet() : _set(N / 8 + 1, 0) {}

	//将which位置1
	bool set(size_t which) {
		if (which >= N)
			return false;

		size_t index = which / 8;
		size_t pos = which % 8;
		_set[index] |= (1 << pos);
		return true;
	}

	bool reset(size_t which) {
		if (which >= N)
			return false;

		size_t index = which / 8;
		size_t pos = which % 8;
		_set[index] &= (~(1 << pos));
		return true;
	}

	//检测which位是否为1
	bool test(size_t which) {
		if (which >= N)
			return false;

		size_t index = which / 8;
		size_t pos = which % 8;

		return 0 != (_set[index] & ((1 << pos)));
	}

	//返回比特位总的个数
	size_t size() const {
		return N;
	}

	//返回位图中为1的比特位的个数
	size_t count() const {
		//把0-255中含1的个数列出来
		int bitCnttable[256] = {
			0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2,
			3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3,
			3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3,
			4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4,
			3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5,
			6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4,
			4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
			6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5,
			3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3,
			4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6,
			6, 7, 6, 7, 7, 8 };
		size_t count = 0;
		//e为一个字节的数据 一个字节最大255
		for (auto e : _set) {
			count += bitCnttable[e];
		}

		return count;
	}

private:
	vector<unsigned char> _set;
};

