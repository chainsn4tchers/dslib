#include <bits/stdc++.h>

using namespace std;

#define ll long long
const int MXSZ = 1e6;

struct segtree {
	ll tree[MXSZ] = { 0 };

	int init(int idx, unsigned levels)
	{
		if (idx > levels) return 0;
		tree[idx] = max(init(idx * 2 + 1, levels), init(idx * 2 + 2, levels));
	}

	void build(ll* a, int n)
	{
		unsigned levels = 0;
		while ((1 << levels) < n) ++levels;
		--levels;

		int j;
		for (j = levels; j - levels < n; ++j) {
			tree[j] = a[j - levels];
		}

		init(0, levels);
	}
};