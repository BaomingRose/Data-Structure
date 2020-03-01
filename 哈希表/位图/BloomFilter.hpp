#pragma once
#include "BitSet.hpp"

//布隆过滤器：位图 + 多个哈希函数

template <class T, size_t N, class HF1, class HF2, class HF3, class HF4, class HF5>
class BloomFilter {
	BloomFilter() {}

	void Insert(const T& data) {
		size_t bitCount = _bst.size();

		size_t index = HF1()(data) % bitCount;
		_bst.set(index);

		index = HF2()(data) % bitCount;
		_bst.set(index);

		index = HF3()(data) % bitCount;
		_bst.set(index);

		index = HF4()(data) % bitCount;
		_bst.set(index);

		index = HF5()(data) % bitCount;
		_bst.set(index);
	}

	void IsIn(const T& data) {
		size_t bitCount = _bst.size();
		size_t index = HF1()(data) % bitCount;
		if (!_bst.test(index))
			return false;

		index = HF2()(data) % bitCount;
		if (!_bst.test(index))
			return false;
		
		index = HF3()(data) % bitCount;
		if (!_bst.test(index))
			return false;

		index = HF4()(data) % bitCount;
		if (!_bst.test(index))
			return false;
		
		index = HF5()(data) % bitCount;
		if (!_bst.test(index))
			return false;

		//可能存在
		return true;
	}

private:
	bitSet<5 * N> _bst;
};