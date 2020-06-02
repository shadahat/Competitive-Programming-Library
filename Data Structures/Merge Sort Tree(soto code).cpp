const int N = 100010;

int n;
ll ara[N];
vector <ll> tree[N + N];

void build() {
    for(int i=0;i<=n;i++) tree[n + 1 + i].emplace_back(ara[i]);
    for(int i=n;i;i--) merge(tree[i << 1].begin(), tree[i << 1].end(), tree[i << 1 | 1].begin(), tree[i << 1 | 1].end(), back_inserter(tree[i]));
}

// l, r 1 based
// how many numbers in range[l, r) such that lo <= ara[i] <= hi
int get (int l, int r, ll lo, ll hi) {
    int ret = 0;
    for (l += n + 1, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            vector <ll> &vec = tree[l++];
            ret += upper_bound(vec.begin(), vec.end(), hi) - lower_bound(vec.begin(), vec.end(), lo);
        }
        if (r & 1) {
            vector <ll> &vec = tree[--r];
            ret += upper_bound(vec.begin(), vec.end(), hi) - lower_bound(vec.begin(), vec.end(), lo);
        }
    }
    return ret;
}
