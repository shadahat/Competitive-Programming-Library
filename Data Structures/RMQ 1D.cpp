// 0 based array indexing
// build -> O(n logn)
// query -> O(1)

#include <bits/stdc++.h>
using namespace std;

template<class num_t, class cmp = less<num_t> > // greater
struct RMQ {
    int n;
    vector <num_t> a;
    vector <vector <num_t> > f;

    inline num_t best(const num_t& a, const num_t& b) {
        if (cmp()(a, b)) return a;
        return b;
    }
    void init(int _n) {
        n = _n;
        int p = 1; while ((1 << p) < n) p++;
        a.resize(n), f.resize(p + 1);
        a.shrink_to_fit(), f.shrink_to_fit();
        for (int i = 0; i < (int) f.size(); i++) {
            f[i].resize(n);
        }
    }
    num_t& operator [] (int u) {
        assert(u < (int) a.size());
        return a[u];
    }
    void build() {
        for (int i = 0; i < n; i++) f[0][i] = a[i];
        for (int l = 0, k; (k = 1 << l) < n; l++) {
            for (int i = 0; i + k < n; i++) {
                f[l + 1][i] = best(f[l][i], f[l][i + k]);
            }
        }
    }
    num_t query(int a, int b) {
        assert(a <= b);
        int l = a == b ? 0 : __lg(b - a);
        return best(f[l][a], f[l][b - (1 << l) + 1]);
    }
};

RMQ <int> rmq;

int main() {
    int n, x, q, L, R;
    cin >> n;
    rmq.init(n);
    for(int i=0;i<n;i++) cin >> x, rmq[i] = x;
    rmq.build();
    cin >> q;
    for(int i=0;i<q;i++) {
        cin >> L >> R;
        cout << rmq.query(L, R) << endl;
    }
    return 0;
}

