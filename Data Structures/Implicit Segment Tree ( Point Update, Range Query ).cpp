// Not tested

int it;

void init() {
    it = 0;
}

struct Node {
    int l, r;
    ll sum;
    Node() {
        l = r = 0;
        sum = 0; // ???
    }
    Node(int _sum) {
        l = r = 0;
        sum = _sum;
    }
} tree[4 * MAX];
// make it a vector if confused about the size
// MAX = total number of points that are updated


int update(int nd, int st, int ed, int id, ll v) {
    if(!nd) {
        nd = ++it;
        tree[nd] = Node();
    }

    if(st == ed) {
        tree[nd] = Node(v);
        return nd;
    }

    int mid = (st + ed) >> 1;

    if(id <= mid) tree[nd].l = update(tree[nd].l, st, mid, id, v);
    else tree[nd].r = update(tree[nd].r, mid + 1, ed, id, v);

    tree[nd].sum = tree[tree[nd].l].sum + tree[tree[nd].r].sum;
    return nd;
}

ll query(int nd, int st, int ed, int i, int j) {
    if(!nd) return 0; // ???
    if(st >= i && ed <= j) return tree[nd].sum;
    int mid = (st + ed) >> 1;
    if(mid < i) return query(tree[nd].r, mid + 1, ed, i, j);
    else if(mid >= j) return query(tree[nd].l, st, mid, i, j);
    else return query(tree[nd].l, st, mid, i, j) + query(tree[nd].r, mid + 1, ed, i, j);
}


int main() {
    int n = 1000000000;

    init();
    int root = 0;
    root = update(root, 1, n, 5, 1);
    root = update(root, 1, n, 3, 2);
    root = update(root, 1, n, 10, 3);
    root = update(root, 1, n, 14, 4);
    cout << query(root, 1, n, 1, 15) << endl;
    root = update(root, 1, n, 14, 3);
    cout << query(root, 1, n, 1, 15) << endl;
    return 0;
}
