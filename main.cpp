#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>

using namespace std;

class DSU {
    unordered_map<long long, long long> parent;
    unordered_map<long long, long long> sz;

public:
    long long find(long long x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            sz[x] = 1;
            return x;
        }
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(long long x, long long y) {
        x = find(x);
        y = find(y);
        if (x == y) return;

        if (sz[x] < sz[y]) swap(x, y);
        parent[y] = x;
        sz[x] += sz[y];
    }

    bool same(long long x, long long y) {
        return find(x) == find(y);
    }

    long long size(long long x) {
        return sz[find(x)];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    DSU dsu;
    int q;
    cin >> q;

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            long long x, y;
            cin >> x >> y;
            dsu.unite(x, y);
        } else if (type == 2) {
            long long x, y;
            cin >> x >> y;
            cout << (dsu.same(x, y) ? 1 : 0) << '\n';
        } else if (type == 3) {
            long long x;
            cin >> x;
            cout << dsu.size(x) << '\n';
        }
    }

    return 0;
}
