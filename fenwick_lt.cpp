#include <vector>
using namespace std;

#define MAXSIZE 1000001
#define ll long long

struct fentree {
    int treeSize;
    vector<ll> tree;

    void build(vector<ll>& a)
    {
        treeSize = a.size() + 1;
        tree.assign(treeSize, 0);
        for (int i = 1; i <= treeSize; ++i) {
            tree[i] = a[i - 1];
        }
        for (int i = 1; i <= treeSize; ++i) {
            int parent = i + (i & (-i));
            if (parent <= i) {
                tree[parent] += tree[i];
            }
        }
    }

    ll prefSum(int idx)
    {
        ll sum = 0ll;
        while (idx) {
            sum += tree[idx];
            idx -= (idx & (-idx));
        }
        return sum;
    }

    ll rangeSum(int l, int r)
    {
        return prefSum(r) - prefSum(l - 1);
    }

    void update(int idx, ll x)
    {
        while (idx <= treeSize) {
            tree[idx] += x;
            idx += (idx & (-idx));
        }
    }

    void fix(int idx, ll x)
    {
        update(idx, x - tree[idx]);
    }
};