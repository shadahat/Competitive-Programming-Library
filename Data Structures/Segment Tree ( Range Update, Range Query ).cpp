int ara[MAX];

struct node {
    int sum;
} tree[4 * MAX];

int lazy[4 * MAX];

node Merge(node a, node b) {
    node ret;
    ret.sum = a.sum + b.sum;
    return ret;
}

void lazyUpdate(int n, int st, int ed) {
    if(lazy[n] != 0){
        tree[n].sum += ((ed - st + 1) * lazy[n]);
        if(st != ed){
            lazy[2 * n] += lazy[n];
            lazy[2 * n + 1] += lazy[n];
        }
        lazy[n] = 0;
    }
}

void build(int n, int st, int ed) {
    lazy[n] = 0;
    if(st == ed){
        tree[n].sum = ara[st];
        return;
    }
    int mid = (st + ed) / 2;
    build(2 * n, st, mid);
    build(2 * n + 1, mid + 1, ed);
    tree[n] = Merge(tree[2 * n], tree[2 * n + 1]);
}

void update(int n, int st, int ed, int i, int j, int v) {
    lazyUpdate(n, st, ed);
    if(st > j or ed < i) return;
    if(st >= i and ed <= j){
        lazy[n] += v;
        lazyUpdate(n, st, ed);
        return;
    }
    int mid = (st + ed) / 2;
    update(2 * n, st, mid, i, j, v);
    update(2 * n + 1, mid+1, ed, i, j, v);
    tree[n] = Merge(tree[2 * n], tree[2 * n + 1]);
}

node query(int n, int st, int ed, int i, int j) {
    lazyUpdate(n, st, ed);
    if(st >= i and ed <= j) return tree[n];
    int mid = (st + ed) / 2;
    if(mid < i) return query(2 * n + 1, mid + 1, ed, i, j);
    else if(mid >= j) return query(2 * n, st, mid, i, j);
    else return Merge(query(2 * n, st, mid, i, j), query(2 * n + 1, mid + 1, ed, i, j));
}
