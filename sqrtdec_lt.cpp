#include <cmath>
#include <vector>
using namespace std;

#define ll int64_t
#define __INT64_MIN__ -0x7fffffffffffffff - 1

struct sqrtdec {
    size_t blockSize;
    vector<ll> arr;
    vector<ll> sumArr;
    vector<ll> maxArr;

    void build(vector<ll>& a)
    {
        blockSize = ceil(sqrt(a.size() + .0));
        arr = a;
        sumArr.assign(blockSize, (ll)0);
        maxArr.assign(blockSize, __INT64_MIN__);

        for (int i = 0; i < (int)a.size(); ++i) {
            sumArr[i / blockSize] += a[i];
            maxArr[i / blockSize] = max(a[i], maxArr[i / blockSize]);
        }
    }

    ll rangeSum(int l, int r)
    {
        ll sum = (ll)0;
        int lblk = l / blockSize;
        int rblk = r / blockSize;
    
        if (lblk == rblk) {
            for (int i = l; i <= r; ++i) {
                sum += arr[i];
            }
        }
        else {
            for (int i = l; i < blockSize * (lblk + 1); ++i) {
                sum += arr[i];
            }
            for (int i = lblk + 1; i < rblk; ++i) {
                sum += sumArr[i];
            }
            for (int i = blockSize * rblk; i <= r; ++i) {
                sum += arr[i];
            }
        }
        return sum;
    }

    ll rangeMax(int l, int r)
    {
        ll res = -0x7fffffffffffffff - 1;
        int lblk = l / blockSize;
        int rblk = r / blockSize;
    
        if (lblk == rblk) {
            for (int i = l; i <= r; ++i) {
                res = max(res, arr[i]);
            }
        }
        else {
            for (int i = l; i < blockSize * (lblk + 1); ++i) {
                res = max(res, arr[i]);
            }
            for (int i = lblk + 1; i < rblk; ++i) {
                res = max(res, maxArr[i]);
            }
            for (int i = blockSize * rblk; i <= r; ++i) {
                res = max(res, arr[i]);
            }
        }
        return res;
    }

    void update(int idx, ll x)
    {
        sumArr[idx / blockSize] = sumArr[idx / blockSize] - arr[idx] + x;
        maxArr[idx / blockSize] = max(x, maxArr[idx / blockSize]);
        arr[idx] = x;
    }
};
