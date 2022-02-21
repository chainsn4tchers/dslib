#include <vector>
using namespace std;

#define sz(x) (int)(x).size()
#define ll long long

struct segtree {
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
        size = 4 * a.size();
        tree.assign(size + 1, 0);
        init(0, sz(a) - 1, 0, a);
    }

    ll rangeSum(int lo, int hi, int idx, int l, int r)
    {
        if (l > r) return identity;
        if (lo >= l && hi <= r)
            return tree[idx];
        int mid = lo + ((hi - lo) / 2);
        return rangeSum(lo, mid, (2 * idx) + 1, l, min(r, mid)) + rangeSum(mid + 1, hi, (2 * idx) + 2, max(l, mid + 1), r);
    }

    void update(int lo, int hi, int idx, int pos, ll x)
    {
        if (lo == hi) {
            tree[lo] = x;
            return;
        }
        int mid = lo + ((hi - lo) / 2);
        if (pos <= mid)
            update(lo, mid, (2 * idx) + 1, pos, x);
        else
            update(mid + 1, hi, (2 * idx) + 2, pos, x);
        tree[idx] = tree[(2 * idx) + 1] + tree[(2 * idx) + 2];
    }
};
