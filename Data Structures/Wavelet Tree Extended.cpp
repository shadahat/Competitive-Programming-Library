#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX = 100005;

// The following code works for large values as array elements
// if array elements are small (<=1e6), remove M, S, rm[] parts
// After construction, ara will be changed. Keep a copy if needed later.

int ara[MAX];
set <int> S;
map <int, int> M;
int rm[MAX];

struct wavelet_tree {
    int lo, hi;
    wavelet_tree *l, *r;
    vector <int> b;
    vector <ll> c; /// c holds the prefix sum of elements for sum query

    ///array elements are in range [x,y]
    ///array indices are [from, to)
    wavelet_tree(int *from, int *to, int x, int y) {
        lo = x, hi = y;
        if( from >= to) return;
        if( hi == lo ) {
            b.reserve(to - from + 1); b.push_back(0);
            c.reserve(to - from + 1); c.push_back(0);
            for(auto it = from; it != to; it++) {
                b.push_back(b.back() + 1);
                c.push_back(c.back() + rm[*it]);
            }
            return;
        }
        int mid = (lo+hi)/2;
        auto f = [mid](int x) { return x <= mid; };

        b.reserve(to - from + 1); b.push_back(0);
        c.reserve(to - from + 1); c.push_back(0);
        for(auto it = from; it != to; it++) {
            b.push_back(b.back() + f(*it));
            c.push_back(c.back() + rm[*it]);
        }
        //see how lambda function is used here
        auto pivot = stable_partition(from, to, f);
        l = new wavelet_tree(from, pivot, lo, mid);
        r = new wavelet_tree(pivot, to, mid + 1, hi);
    }

    /// k'th smallest element in subarray [l,r]
    int kth(int l, int r, int k) {
        if(l > r) return 0;
        if(lo == hi) return lo;
        int inLeft = b[r] - b[l - 1];
        int lb = b[l - 1]; /// amt of nos in first (l-1) nos that go in left
        int rb = b[r]; /// amt of nos in first (r) nos that go in left
        if(k <= inLeft) return this->l->kth(lb + 1, rb, k);
        return this->r->kth(l - lb, r - rb, k - inLeft);
    }

    /// number of elements <= k in subarray [l,r]
    int LTE(int l, int r, int k) {
        if(l > r or k < lo) return 0;
        if(hi <= k) return r - l + 1;
        int lb = b[l-1], rb = b[r];
        return this->l->LTE(lb + 1, rb, k) + this->r->LTE(l - lb, r - rb, k);
    }

    /// number of occurrences of k in subarray [l,r]
    int count(int l, int r, int k) {
        if(l > r or k < lo or k > hi) return 0;
        if(lo == hi) return r - l + 1;
        int lb = b[l - 1], rb = b[r], mid = (lo + hi)/2;
        if(k <= mid) return this->l->count(lb + 1, rb, k);
        return this->r->count(l - lb, r - rb, k);
    }

    /// sum of the elements <= k in subarray [l,r]
    ll sumk(int l, int r, int k) {
        if(l > r or k < lo) return 0;
        if(hi <= k) return c[r] - c[l - 1];
        int lb = b[l - 1], rb = b[r];
        return this->l->sumk(lb + 1, rb, k) + this->r->sumk(l - lb, r - rb, k);
    }

    /// no need to call explicitly
    ~wavelet_tree() {
        delete l;
        delete r;
    }
};

int main() {
    int n; cin >> n;
    for(int i=1;i<=n;i++) cin >> ara[i], S.insert(ara[i]);
    int it = 0;
    for(int e : S) M[e] = ++it, rm[it] = e;
    for(int i=1;i<=n;i++) ara[i] = M[ara[i]];
    wavelet_tree *Tree = new wavelet_tree(ara + 1, ara + n + 1, 1, 1e5);
    /***
    to know the sum of elements in range [a, b] which are <= c
    auto it = S.upper_bound(c);
    if(it == S.begin()) sum = 0
    else it--, sum = Tree->sumk(a, b, M[*it]);
    ***/
    return 0;
}
