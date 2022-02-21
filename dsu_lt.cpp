#include <algorithm>
using namespace std;

const int MAXSIZE = 200006;

struct dsu {
    int comp;
    int rank[MAXSIZE];
    int parent[MAXSIZE];

    dsu(int n)
        : comp(n)
    {
        for (int i = 0; i < n; ++i) {
            rank[i] = 0;
            parent[i] = i;
        }
    }

    int root(int node)
    {
        if (parent[node] == node) return node;
        return parent[node] = root(parent[node]);
    }

    void unite(int a, int b)
    {
        a = root(a);
        b = root(b);
        if (a == b) return;

        ++comp;
        if (rank[a] != rank[b]) {
            if (rank[a] < rank[b])
                swap(a, b);
        }
        else {
            if (a < b)
                swap(a, b);
        }
        ++rank[a];
        parent[b] = a;
    }

    int components() const { return comp; };
};
