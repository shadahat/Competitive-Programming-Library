int ara[MAX];

struct node {
    int sum;
} tree[4 * MAX];

node Merge(node a, node b) {
    node ret;
    ret.sum = a.sum + b.sum;
    return ret;
}

void build(int n, int st, int ed){
    if(st == ed){
        tree[n].sum = ara[st];
        return;
    }
    int mid = (st + ed) / 2;
    build(2 * n, st, mid);
    build(2 * n + 1, mid + 1, ed);
    tree[n] = Merge(tree[2 * n], tree[2 * n + 1]);
}

void update(int n, int st, int ed, int id, int v) {
    if(id > ed or id < st) return;
    if(st == ed and ed == id) {
        tree[n].sum = v;
        return;
    }
    int mid = (st + ed) / 2;
    update(2 * n, st, mid, id, v);
    update(2 * n + 1, mid + 1, ed, id, v);
    tree[n] = Merge(tree[2 * n], tree[2 * n + 1]);
}

node query(int n, int st, int ed, int i, int j) {
    if(st >= i and ed <= j) return tree[n];
    int mid = (st + ed) / 2;
    if(mid < i) return query(2 * n + 1, mid + 1, ed, i, j);
    else if(mid >= j) return query(2 * n, st, mid, i, j);
    else return Merge(query(2 * n, st, mid, i, j), query(2 * n + 1, mid + 1, ed, i, j));
}
