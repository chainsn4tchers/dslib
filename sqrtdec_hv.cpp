#include "sqrtdec_hv.h"

SqrtDecomposition::SqrtDecomposition(const std::vector<long>& v)
{
	errno = 0;
	size_t n = v.size();
	long double rootN = std::sqrt((double)n);
	if (errno == EDOM) { std::cerr << "DOMAIN_ERROR: Input out of domain\n"; return; }

	blockSize_ = (long)std::ceil(rootN);
	blockSumArray_.resize(blockSize_, 0);

	for (size_t i = 0; i < v.size(); ++i)
		blockSumArray_[i / blockSize_] += v[i];
}

SqrtDecomposition::SqrtDecomposition(const std::vector<long>&& v)
{
	errno = 0;
	size_t n = v.size();
	long double rootN = std::sqrt((double)n);
	if (errno == EDOM) { std::cerr << "DOMAIN_ERROR: Input out of domain\n"; return; }

	blockSize_ = (long)std::ceil(rootN);
	blockSumArray_.resize(blockSize_, 0);

	for (size_t i = 0; i < v.size(); ++i)
		blockSumArray_[i / blockSize_] += v[i];
}

void SqrtDecomposition::ptUpdate(const long& index, const long& t)
{
	blockSumArray_[index / blockSize_] += t - arr_[index];
	arr_[index] = t;
}

void SqrtDecomposition::ptUpdate(const long&& index, const long& t)
{
	blockSumArray_[index / blockSize_] += t - arr_[index];
	arr_[index] = t;
}

void SqrtDecomposition::ptUpdate(const long& index, const long&& t)
{
	blockSumArray_[index / blockSize_] += t - arr_[index];
	arr_[index] = t;
}

void SqrtDecomposition::ptUpdate(const long&& index, const long&& t)
{
	blockSumArray_[index / blockSize_] += t - arr_[index];
	arr_[index] = t;
}

long long SqrtDecomposition::rangeSum(const long& L, const long& R)
{
	long long res = 0;
	size_t block_L = L / blockSize_;
	size_t block_R = R / blockSize_;

	if (block_L == block_R)
	{
		for (size_t i = block_L; i <= block_R; ++i)
			res += arr_[i];
	}
	else
	{
		for (size_t i = L; i <= blockSize_; ++i)
			res += arr_[i];
		for (size_t i = block_L + 1; i < block_R; ++i)
			res += blockSumArray_[i];
		for (size_t i = block_R * blockSize_; i <= R; ++i)
			res += arr_[i];
	}

	return res;
}

long long SqrtDecomposition::rangeSum(const long&& L, const long& R)
{
	long long res = 0;
	size_t block_L = L / blockSize_;
	size_t block_R = R / blockSize_;

	if (block_L == block_R)
	{
		for (size_t i = block_L; i <= block_R; ++i)
			res += arr_[i];
	}
	else
	{
		for (size_t i = L; i <= blockSize_; ++i)
			res += arr_[i];
		for (size_t i = block_L + 1; i < block_R; ++i)
			res += blockSumArray_[i];
		for (size_t i = block_R * blockSize_; i <= R; ++i)
			res += arr_[i];
	}

	return res;
}

long long SqrtDecomposition::rangeSum(const long& L, const long&& R)
{
	long long res = 0;
	size_t block_L = L / blockSize_;
	size_t block_R = R / blockSize_;

	if (block_L == block_R)
	{
		for (size_t i = block_L; i <= block_R; ++i)
			res += arr_[i];
	}
	else
	{
		for (size_t i = L; i <= (block_L + 1) * blockSize_ - 1; ++i)
			res += arr_[i];
		for (size_t i = block_L + 1; i < block_R; ++i)
			res += blockSumArray_[i];
		for (size_t i = block_R * blockSize_; i <= R; ++i)
			res += arr_[i];
	}

	return res;
}

long long SqrtDecomposition::rangeSum(const long&& L, const long&& R)
{
	long long res = 0;
	size_t block_L = L / blockSize_;
	size_t block_R = R / blockSize_;

	if (block_L == block_R)
	{
		for (size_t i = block_L; i <= block_R; ++i)
			res += arr_[i];
	}
	else
	{
		for (size_t i = L; i < (block_L + 1) * blockSize_; ++i)
			res += arr_[i];
		for (size_t i = block_L + 1; i < block_R; ++i)
			res += blockSumArray_[i];
		for (size_t i = block_R * blockSize_; i <= R; ++i)
			res += arr_[i];
	}

	return res;
}

inline long long SqrtDecomposition::ithBlockSum(const long& i) const
{
	return blockSumArray_[i / blockSize_];
}

inline long long SqrtDecomposition::ithBlockSum(const long&& i) const
{
	return blockSumArray_[i / blockSize_];
}