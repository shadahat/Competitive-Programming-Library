/** Persistent Segment Tree using static Array
    Point Update, Range Sum
    Initialize ncnt to 0 in every test case **/

const int MAX = 100010;

int ncnt = 0;

struct node {
    int sum;
    int left,right;
    node() {}
    node(int val) {
        sum = val;
        left = right = -1;
    }
} tree[ ? ];

/// input araay
int ara[MAX];
/// root nodes for all versions
int version[MAX];

void build(int n,int st,int ed) {
    if (st==ed) {
        tree[n] = node(ara[st]);
        return;
    }

    int mid = (st+ed) / 2;

    tree[n].left = ++ncnt;
    tree[n].right = ++ncnt;

    build(tree[n].left, st, mid);
    build(tree[n].right, mid+1, ed);

    tree[n].sum = tree[tree[n].left].sum + tree[tree[n].right].sum;
}

void update(int prev,int cur,int st,int ed,int id, int val)
{
    if (id > ed or id < st) return;
    if (st == ed) {
        tree[cur] = node(val);
        return;
    }
    int mid = (st+ed) / 2;
    if (id <= mid) {
        tree[cur].right = tree[prev].right;
        tree[cur].left = ++ncnt;
        update(tree[prev].left,tree[cur].left, st, mid, id, val);
    }
    else {
        tree[cur].left = tree[prev].left;
        tree[cur].right = ++ncnt;
        update(tree[prev].right, tree[cur].right, mid+1, ed, id, val);
    }
    tree[cur].sum = tree[tree[cur].left].sum + tree[tree[cur].right].sum;
}

int query(int n,int st,int ed,int i,int j){
    if(st>=i && ed<=j) return tree[n].sum;
    int mid = (st+ed)/2;
    if(mid<i) return query(tree[n].right,mid+1,ed,i,j);
    else if(mid>=j) return query(tree[n].left,st,mid,i,j);
    else return query(tree[n].left,st,mid,i,j) + query(tree[n].right,mid+1,ed,i,j);
}

int main() {
    int n,q,l,r,k;

    sii(n,q);

    version[0] = ++ncnt;
    build(version[0],1,n);

    version[1] = ++ncnt;
    update(version[0],version[1],1,n,id,val);

    query(version[0],1,n,id,id);
    query(version[1],1,n,id,id);

    return 0;
}

