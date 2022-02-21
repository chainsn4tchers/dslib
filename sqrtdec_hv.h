#pragma once /* _SQRT_DEC_H_ */

#include <cmath>
#include <cerrno>
#include <vector>
#include <iostream>

class SqrtDecomposition {
private:
	size_t blockSize_;
	std::vector<long> arr_;
	std::vector<long> blockSumArray_;

public:
	SqrtDecomposition() = default;
	SqrtDecomposition(const std::vector<long>& n);
	SqrtDecomposition(const std::vector<long>&& n);

	void ptUpdate(const long& index, const long& t);
	void ptUpdate(const long&& index, const long& t);
	void ptUpdate(const long& index, const long&& t);
	void ptUpdate(const long&& index, const long&& t);

	long long rangeSum(const long& l, const long& r);
	long long rangeSum(const long&& l, const long& r);
	long long rangeSum(const long& l, const long&& r);
	long long rangeSum(const long&& l, const long&& r);

	inline long long ithBlockSum(const long& i) const;
	inline long long ithBlockSum(const long&& i) const;
};