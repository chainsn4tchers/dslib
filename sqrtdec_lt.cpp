#include <vector>
using namespace std;

#define sz(x) (int)(x).size()
#define ll long long

struct sqrtdec {
    size_t size;
    vector<ll> tree;
    int identity = 0;

    // holds range sum by default
    ll init(int lo, int hi, int idx, vector<ll>& a)
    {
        if (lo == hi)
            return tree[idx] = a[lo];

        int mid = lo + ((hi - lo) / 2);
        return tree[idx] = init(lo, mid, (2 * idx) + 1, a) + init(mid + 1, hi, (2 * idx) + 2, a);
    }

    void build(vector<ll>& a)
    {
        init(0, sz(a) - 1, 0, a);
    }

    ll rangeSum(int lo, int hi, int idx, int l, int r)
    {
        if (l > r)
            return identity;
        if (lo == l && hi == r)
            return tree[idx];
        int mid = lo + ((hi - lo) / 2);
        return rangeSum(lo, mid, (2 * idx) + 1, l, r) + rangeSum(mid + 1, hi, (2 * idx) + 2, l, r);
    }
};