/***
    Given an array of size n, each value in array can be expressed using
    20 bits.
    Query : L R K
    max(a_i ^ K) for L <= i <= R
***/


const int MAX = 200010; /// maximum size of array
const int B = 19; /// maximum number of bits in a value - 1
int root[MAX], ptr = 0;

struct node {
    int ara[2], sum;
    node() {}
} tree[ MAX * (B+1) ];

void insert(int prevnode, int &curRoot, int val) {
    curRoot = ++ptr;
    int curnode = curRoot;
    for(int i = B; i >= 0; i--) {
        bool bit = val & (1 << i);
        tree[curnode] = tree[prevnode];
        tree[curnode].ara[bit] = ++ptr;
        tree[curnode].sum += 1;
        prevnode = tree[prevnode].ara[bit];
        curnode = tree[curnode].ara[bit];
    }
    tree[curnode] = tree[prevnode];
    tree[curnode].sum += 1;
}

int find_xor_max(int prevnode, int curnode, int x) {
    int ans = 0;
    for(int i = B; i >= 0; i--) {
        bool bit = x & (1 << i);
        if(tree[tree[curnode].ara[bit ^ 1]].sum > tree[tree[prevnode].ara[bit ^ 1]].sum) {
            curnode = tree[curnode].ara[bit ^ 1];
            prevnode = tree[prevnode].ara[bit ^ 1];
            ans = ans | (1 << i);
        }
        else {
            curnode = tree[curnode].ara[bit];
            prevnode = tree[prevnode].ara[bit];
        }
    }
    return ans;
}

void solve() {
    int n, q, L, R, K;
    cin >> n;
    for(int i=1;i<=n;i++) cin >> ara[i];

    for(int i=1;i<=q;i++) {
        cin >> L >> R >> K;
        cout << find_xor_max(root[L-1],root[R],K) << endl;
    }
}
