/***
    LOJ : 1348
    Given a rooted tree, every node has a value.
    0 u v -> sum of the values of all the nodes on the path from u to v
    1 u x -> change the value of node u to x

    * clear ed[] for every case
***/
#include <bits/stdc++.h>
using namespace std;
const int MAX = 30010;

vector <int> ed[MAX];
int ptr, ara[MAX], par[MAX];
int sz[MAX], h[MAX], pos[MAX], head[MAX], base[MAX];

struct SegmentTree {
    struct node{
        int sum;
    } tree[4*MAX];

    node Merge(node a,node b){
        node ret;
        ret.sum = a.sum+b.sum;
        return ret;
    }

    void build(int n,int st,int ed){
        if(st==ed){
            tree[n].sum = ara[base[st]]; return;
        }
        int mid = (st+ed)/2;
        build(2*n,st,mid);
        build(2*n+1,mid+1,ed);
        tree[n] = Merge(tree[2*n],tree[2*n+1]);
    }

    void update(int n,int st,int ed,int id,int v){
        if(id>ed || id<st) return;
        if(st==ed && ed==id){
            tree[n].sum = v; return;
        }
        int mid = (st+ed)/2;
        update(2*n,st,mid,id,v);
        update(2*n+1,mid+1,ed,id,v);
        tree[n] = Merge(tree[2*n],tree[2*n+1]);
    }

    node query(int n,int st,int ed,int i,int j){
        if(st>=i && ed<=j) return tree[n];
        int mid = (st+ed)/2;
        if(mid<i) return query(2*n+1,mid+1,ed,i,j);
        else if(mid>=j) return query(2*n,st,mid,i,j);
        else return Merge(query(2*n,st,mid,i,j),query(2*n+1,mid+1,ed,i,j));
    }
} st;



void dfs (int u, int far) {
    sz[u] = 1, h[u] = far;
    for (int v : ed[u]) ed[v].erase(find(ed[v].begin(), ed[v].end(), u));
    for (int &v : ed[u]) {
        par[v] = u;
        dfs(v, far + 1);
        sz[u] += sz[v];
        if (sz[v] > sz[ed[u][0]]) swap(v, ed[u][0]);
    }
}

void hld (int u) {
    pos[u] = ++ptr;
    base[ptr] = u;
    for (int v : ed[u]) {
        head[v] = (v == ed[u][0] ? head[u] : v);
        hld(v);
    }
}

inline int query (int n,int u, int v) {
    int res = 0;
    while (head[u] != head[v]) {
        if (h[head[u]] > h[head[v]]) swap(u, v);
        res += st.query(1,1,n,pos[head[v]], pos[v]).sum;
        v = par[head[v]];
    }
    if (h[u] > h[v]) swap(u, v);
    // u is the lca of the path now
    res += st.query(1,1,n,pos[u],pos[v]).sum;
    return res;
}

inline void update(int n,int u,int v) {
    ara[u] = v;
    st.update(1,1,n,pos[u],v);
}

void build(int n,int root) {
    h[root] = 0, head[root] = root, ptr = 0;
    dfs(root,0);
    hld(root);
    st.build(1,1,n);
}

int main() {
//    freopen("in.txt","r",stdin);
    int T,n;
    scanf("%d",&T);
    for(int t=1;t<=T;t++) {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) ed[i].clear();
        for(int i=1;i<=n;i++) scanf("%d",&ara[i]);

        int u,v;
        for(int i=1;i<n;i++) {
            scanf("%d %d",&u,&v);
            u++, v++;
            ed[u].push_back(v);
            ed[v].push_back(u);
        }

        build(n,1);

        int q; scanf("%d",&q);

        int x;
        printf("Case %d:\n",t);
        for(int i=1;i<=q;i++) {
            scanf("%d %d %d",&x,&u,&v);
            if(x == 0) {
                u++, v++;
                printf("%d\n",query(n,u,v));
            }
            else {
                u++;
                update(n,u,v);
            }
        }
    }
    return 0;
}
