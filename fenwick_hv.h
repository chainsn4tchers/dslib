/*
	fenwick_lt is faster, prefer it to this
*/
#ifndef _FENTREE_H_
#define _FENTREE_H_

#include <vector>
#include <stdexcept>
#include <type_traits>

template <typename T>
class FenTree {
private:
	T treeSize;
	std::vector<T> tree;
	bool validate(const size_t& index) { return index > 0 && index <= treeSize; }

public:
	FenTree();
	FenTree(const std::vector<T>& a);
	FenTree(const std::vector<T>&& a);

	void init(const std::vector<T>& a);
	void init(const std::vector<T>&& a);

	T prefSum(const size_t& idx) const;
	T prefSum(const size_t&& idx) const;

	T rangeSum(const size_t& i, const size_t& j) const;
	T rangeSum(const size_t&& i, const size_t& j) const;
	T rangeSum(const size_t& i, const size_t&& j) const;
	T rangeSum(const size_t&& i, const size_t&& j) const;

	void update(const size_t& idx, const T& x);
	void update(const size_t&& idx, const T& x);
	void update(const size_t& idx, const T&& x);
	void update(const size_t&& idx, const T&& x);

	void fix(const size_t& idx, const T& x);
	void fix(const size_t&& idx, const T& x);
	void fix(const size_t& idx, const T&& x);
	void fix(const size_t&& idx, const T&& x);
};

/* impl */
template <typename T>
FenTree<T>::FenTree()
	: FenTree({})
{ }

template <typename T>
FenTree<T>::FenTree(const std::vector<T>& a)
{
	static_assert(std::is_integral<T>::value, "TYPE_ERROR: Integral type required to instantiate class 'FenTree'\n");

	treeSize = a.size();
	tree.assign(treeSize + 1, 0);

	for (size_t i = 0; i < treeSize; ++i)
		tree[i + 1] = a[i];

	for (size_t i = 1; i <= treeSize; ++i)
	{
		size_t parent = i + (i & (-i));
		if (parent <= treeSize)
			tree[parent] += tree[i];
	}
}

template <typename T>
FenTree<T>::FenTree(const std::vector<T>&& a)
{
	static_assert(std::is_integral<T>::value, "TYPE_ERROR: Integral type required to instantiate class 'FenTree'\n");

	treeSize = a.size();
	tree.assign(treeSize + 1, 0);

	for (size_t i = 0; i < treeSize; ++i)
		tree[i + 1] = a[i];

	for (size_t i = 1; i <= treeSize; ++i)
	{
		size_t parent = i + (i & (-i));
		if (parent <= treeSize)
			tree[parent] += tree[i];
	}
}

template <typename T>
T FenTree<T>::prefSum(const size_t& idx) const
{
	if (!validate(idx))
	{
		std::cerr << "INVALID_INDEX: Passed index out of bounds\n";
		return -1;
	}

	T sum = 0;

	while (idx)
	{
		sum += tree[idx];
		idx -= (idx & (-idx));
	}

	return sum;
}

template <typename T>
T FenTree<T>::prefSum(const size_t&& idx) const
{
	if (!validate(idx))
	{
		std::cerr << "INVALID_INDEX: Passed index out of bounds\n";
		return -1;
	}

	T sum = 0;

	while (idx)
	{
		sum += tree[idx];
		idx -= (idx & (-idx));
	}

	return sum;
}

template <typename T>
T FenTree<T>::rangeSum(const size_t& i, const size_t& j) const
{
	return prefSum(j) - prefSum(i - 1);
}

template <typename T>
T FenTree<T>::rangeSum(const size_t&& i, const size_t& j) const
{
	return prefSum(j) - prefSum(i - 1);
}

template <typename T>
T FenTree<T>::rangeSum(const size_t& i, const size_t&& j) const
{
	return prefSum(j) - prefSum(i - 1);
}

template <typename T>
T FenTree<T>::rangeSum(const size_t&& i, const size_t&& j) const
{
	return prefSum(j) - prefSum(i - 1);
}

template <typename T>
void FenTree<T>::update(const size_t& idx, const T& x)
{
	if (!validate(idx)) return;

	while (idx <= treeSize)
	{
		tree[idx] += x;
		idx += (idx & (-idx));
	}
}

template <typename T>
void FenTree<T>::update(const size_t&& idx, const T& x)
{
	if (!validate(idx)) return;

	while (idx <= treeSize)
	{
		tree[idx] += x;
		idx += (idx & (-idx));
	}
}

template <typename T>
void FenTree<T>::update(const size_t& idx, const T&& x)
{
	if (!validate(idx)) return;

	while (idx <= treeSize)
	{
		tree[idx] += x;
		idx += (idx & (-idx));
	}
}

template <typename T>
void FenTree<T>::update(const size_t&& idx, const T&& x)
{
	if (!validate(idx)) return;

	while (idx <= treeSize)
	{
		tree[idx] += x;
		idx += (idx & (-idx));
	}
}

template <typename T>
void FenTree<T>::fix(const size_t& idx, const T& x)
{
	if (!validate(idx)) return;

	update(idx, x - tree[idx]);
}

template <typename T>
void FenTree<T>::fix(const size_t&& idx, const T& x)
{
	if (!validate(idx)) return;

	update(idx, x - tree[idx]);
}

template <typename T>
void FenTree<T>::fix(const size_t& idx, const T&& x)
{
	if (!validate(idx)) return;

	update(idx, x - tree[idx]);
}

template <typename T>
void FenTree<T>::fix(const size_t&& idx, const T&& x)
{
	if (!validate(idx)) return;

	update(idx, x - tree[idx]);
}

#endif /* _FENTREE_H_ */