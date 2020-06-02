#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 5;
const int LIM = 1e6;

// LIM is maximum possible value of any array element
// If array elements are not between 0 and 1e6, do array compression to make them so.
// After construction, ara will be changed. Keep a copy if needed later.

int ara[MAX];

struct wavelet_tree {
    int lo, hi;
    wavelet_tree *l, *r;
    vector <int> b;

    ///array elements are in range [x,y]
    ///array indices are [from, to)
	wavelet_tree(int *from, int *to, int x, int y){
		lo = x, hi = y;
		if(lo == hi or from >= to) return;
		int mid = (lo+hi)/2;
		auto f = [mid](int x){ return x <= mid; };
		b.reserve(to-from+1);
		b.push_back(0);
		for(auto it = from; it != to; it++)
			b.push_back(b.back() + f(*it));
		//see how lambda function is used here
		auto pivot = stable_partition(from, to, f);
		l = new wavelet_tree(from, pivot, lo, mid);
		r = new wavelet_tree(pivot, to, mid+1, hi);
	}

    /// k'th smallest element in subarray [l,r]
    int kth(int l, int r, int k) {
        if(l > r) return 0;
        if(lo == hi) return lo;
        int inLeft = b[r] - b[l-1];
        int lb = b[l-1]; /// amt of nos in first (l-1) nos that go in left
        int rb = b[r]; /// amt of nos in first (r) nos that go in left
        if(k <= inLeft) return this->l->kth(lb+1, rb, k);
        return this->r->kth(l-lb, r-rb, k-inLeft);
    }

    /// number of elements <= k in subarray [l,r]
    int LTE(int l, int r, int k) {
        if(l > r or k < lo) return 0;
        if(hi <= k) return r - l + 1;
        int lb = b[l-1], rb = b[r];
        return this->l->LTE(lb+1, rb, k) + this->r->LTE(l-lb, r-rb, k);
    }

    /// number of occurrences of k in subarray [l,r]
    int count(int l, int r, int k) {
        if(l > r or k < lo or k > hi) return 0;
        if(lo == hi) return r - l + 1;
        int lb = b[l-1], rb = b[r], mid = (lo+hi)/2;
        if(k <= mid) return this->l->count(lb+1, rb, k);
        return this->r->count(l-lb, r-rb, k);
    }

    /// no need to call explicitly
    ~wavelet_tree() {
        delete l;
        delete r;
    }
};

int main() {
    int n; cin >> n;
    for(int i=1; i<=n; i++) cin >> ara[i];
    wavelet_tree *Tree = new wavelet_tree(ara+1, ara+n+1, 1, LIM);
    return 0;
}

