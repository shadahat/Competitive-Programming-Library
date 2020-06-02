int it;

void init() {
    it = 0;
}

struct Node {
    int l, r;
    ll sum, lazy;
    Node() {
        l = r = 0;
        lazy = sum = 0; // ???
    }
    Node(int _sum) {
        l = r = 0;
        lazy = 0;
        sum = _sum;
    }
} tree[4 * MAX];
// make it a vector if confused about the size
// MAX = total number of points that are updated

void lazyUpdate(int nd, int st, int ed) {
    if(tree[nd].lazy != 0){
        tree[nd].sum += (ed - st + 1) * tree[nd].lazy;
        if(st != ed){
            if(!tree[nd].l) tree[nd].l = ++it, tree[it] = Node();
            if(!tree[nd].r) tree[nd].r = ++it, tree[it] = Node();
            tree[tree[nd].l].lazy += tree[nd].lazy;
            tree[tree[nd].r].lazy += tree[nd].lazy;
        }
        tree[nd].lazy = 0;
    }
}

int update(int nd, int st, int ed, int i, int j, ll v) {
    if(st > j or ed < i) return nd;

    if(!nd) {
        nd = ++it;
        tree[nd] = Node();
    }

    lazyUpdate(nd, st, ed);

    if(st >= i and ed <= j) {
        tree[nd].lazy += v;
        lazyUpdate(nd, st, ed);
        return nd;
    }

    int mid = (st + ed) >> 1;

    tree[nd].l = update(tree[nd].l, st, mid, i, j, v);
    tree[nd].r = update(tree[nd].r, mid + 1, ed, i, j, v);

    tree[nd].sum = tree[tree[nd].l].sum + tree[tree[nd].r].sum;
    return nd;
}

ll query(int nd, int st, int ed, int i, int j) {
    if(!nd) return 0; // ???
    lazyUpdate(nd, st, ed);
    if(st >= i && ed <= j) return tree[nd].sum;
    int mid = (st + ed) >> 1;
    if(mid < i) return query(tree[nd].r, mid + 1, ed, i, j);
    else if(mid >= j) return query(tree[nd].l, st, mid, i, j);
    else return query(tree[nd].l, st, mid, i, j) + query(tree[nd].r, mid + 1, ed, i, j);
}

int main()
{
    int n = 1000000000;

    int root = 0;
    root = update(root, 1, n, 1, 5, 1);
    root = update(root, 1, n, 4, 10, 1);
    root = update(root, 1, n, 9, 14, 1);
    cout << query(root, 1, n, 4, 5) << endl;
    return 0;
}
