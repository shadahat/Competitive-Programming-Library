/***
Problem : Given an undirected graph, every node has a value.
Query :
    1 A V : Change the value of node A to V.
    2 A B : Print the path cost of node A to node B.
    Path cost of A->B is the minimum node value among all the nodes on
    the path. If there are several paths, choose the one having minimum
    cost.

Solution :

Build Block Cut Tree.

Lemma: In a biconnected graph with at least 3 nodes, for any three different vertices
A, B, and C, there is a simple path to from A to B going through C.
From the lemma, we know that if we can pass by a BCC, then we can always pass any point in the BCC.
We use a priority queue for each BCC to maintain the minimal price in the component.

For each modification, if the vertex is a cut vertex, then modify itself and its related BCCs’ priority queue.
If not, modify the priority queue of its BCC.
For each query, the answer is the minimal price on the path from x (or its BCC) to y (or its BCC).
We can use Link-Cut Trees or Heavy-Light Decomposition with Segment Trees.

To be more exact, we can only modify the father BCC of the cut vertex in order
to guarantee complexity(otherwise it would be hacked by a star graph).
When querying, if the LCA of x and y is a BCC. Then the father of the
LCA(which is a cut vertex related to the BCC) should also be taken into account.
***/

#include <bits/stdc++.h>
using namespace std;

typedef pair <int,int> pii;

#define xx              first
#define yy              second
#define pb              push_back
#define CLR(a)          memset(a,0,sizeof(a))

const int MAX = 200010;

int val[MAX];
priority_queue <pii> Q[MAX];

namespace BCT {
    vector <int> ed[MAX];
    bool cut[MAX];
    int tot, Time, low[MAX], st[MAX];
    vector <int> bcc[MAX];
    stack <int> S;

    void popBCC(int s,int x) {
        cut[s] = 1;
        bcc[++tot].pb(s);
        while(bcc[tot].back() ^ x) {
            bcc[tot].pb(S.top());
            S.pop();
        }
    }

    void dfs(int s, int p = -1) {
        S.push(s);
        int ch = 0;
        st[s] = low[s] = ++Time;
        for(int x : ed[s]) {
            if(!st[x]) {
                ch++;
                dfs(x,s);
                low[s] = min(low[s],low[x]);
                if(p != -1 && low[x] >= st[s]) popBCC(s,x);
                else if(p == -1) if(ch > 1) popBCC(s,x);
            }
            else if(p != x) low[s] = min(low[s],st[x]);
        }
        if(p == -1 && ch > 1) cut[s] = 1;
    }


    void processBCC(int n) {
        for(int i=1;i<=n;i++) bcc[i].clear();
        CLR(st); CLR(cut);
        Time = tot = 0;
        for(int i=1; i<=n; i++) {
            if(!st[i]) {
                dfs(i,-1);
                if(!S.empty()) ++tot;
                while(!S.empty()) {
                    bcc[tot].push_back(S.top());
                    S.pop();
                }
            }
        }
    }

    int nn;
    vector <int> tree[MAX];
    int compNum[MAX];

    void buildTree(int n) {
        processBCC(n);

        nn = tot;
        for(int i=1;i<=n;i++) if(cut[i]) compNum[i] = ++nn;

        for(int i=1;i<=tot;i++) {
            for(int v : bcc[i]) {
                if(cut[v]) {
                    tree[i].pb(compNum[v]);
                    tree[compNum[v]].pb(i);
                }
                else {
                    compNum[v] = i;
                }
            }
        }
    }
};


bool isArt(int nd) {
    if(nd > BCT::tot) return true;
    return false;
}

namespace HLD {
    int ptr, ara[MAX], par[MAX];
    int sz[MAX], h[MAX], pos[MAX], head[MAX], base[MAX];

    struct SegmentTree {
        struct node{
            int mn;
        } tree[4*MAX];

        node Merge(node a,node b){
            node ret;
            ret.mn = min(a.mn,b.mn);
            return ret;
        }

        void build(int n,int st,int ed){
            if(st==ed){
                tree[n].mn = ara[base[st]]; return;
            }
            int mid = (st+ed)/2;
            build(2*n,st,mid);
            build(2*n+1,mid+1,ed);
            tree[n] = Merge(tree[2*n],tree[2*n+1]);
        }

        void update(int n,int st,int ed,int id,int v){
            if(id>ed || id<st) return;
            if(st==ed && ed==id){
                tree[n].mn = v; return;
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
        for (int v : BCT::tree[u]) BCT::tree[v].erase(find(BCT::tree[v].begin(), BCT::tree[v].end(), u));
        for (int &v : BCT::tree[u]) {
            par[v] = u;
            dfs(v, far + 1);
            sz[u] += sz[v];
            if (sz[v] > sz[BCT::tree[u][0]]) swap(v, BCT::tree[u][0]);
        }
    }

    void hld (int u) {
        pos[u] = ++ptr;
        base[ptr] = u;
        for (int v : BCT::tree[u]) {
            head[v] = (v == BCT::tree[u][0] ? head[u] : v);
            hld(v);
        }
    }

    inline int query (int n,int u, int v) {
        int res = 2000000000;
        while (head[u] != head[v]) {
            if (h[head[u]] > h[head[v]]) swap(u, v);
            res = min(res,st.query(1,1,n,pos[head[v]], pos[v]).mn);
            v = par[head[v]];
        }
        if (h[u] > h[v]) swap(u, v);
        res = min(res,st.query(1,1,n,pos[u],pos[v]).mn);

        if(!isArt(u) and par[u]) res = min(res,-Q[par[u]].top().xx);
        return res;
    }

    inline void update(int n,int u,int v) {
        ara[u] = v;
        st.update(1,1,n,pos[u],v);
    }

    void build(int n,int root,int x) {
        h[root] = 0, head[root] = root, ptr = 0;
        dfs(root,0);
        hld(root);

        for(int i=1;i<=x;i++) {
            Q[BCT::compNum[i]].push({-val[i],i});
            if(BCT::cut[i]) {
                if(par[BCT::compNum[i]]) {
                    Q[par[BCT::compNum[i]]].push({-val[i],i});
                }
            }
        }


        for(int i=1;i<=n;i++) {
            ara[i] = -Q[i].top().first;
        }
        st.build(1,1,n);
    }
};

void update(int id) {
    while(true) {
        pii c = Q[id].top();
        if( val[c.yy] == -c.xx ) {
            HLD::update(BCT::nn,id,-c.xx);
            return;
        }
        else Q[id].pop();
    }
}

int main() {
    int n,m,q,a,b;
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++) cin >> val[i];
    for(int i=1;i<=m;i++) {
        cin >> a >> b;
        BCT::ed[a].pb(b);
        BCT::ed[b].pb(a);
    }

    BCT::buildTree(n);
    HLD::build(BCT::nn,1,n);

    string cmd;
    for(int i=1;i<=q;i++) {
        cin >> cmd >> a >> b;
        if(cmd == "A") {
            if(a == b) cout << val[a] << "\n";
            else cout << HLD::query(BCT::nn,BCT::compNum[a],BCT::compNum[b]) << "\n";
        }
        else {
            val[a] = b;
            Q[BCT::compNum[a]].push({-b,a});
            update(BCT::compNum[a]);
            if(BCT::cut[a]) {
                int p = HLD::par[BCT::compNum[a]];
                if(p) {
                    Q[p].push({-b,a});
                    update(p);
                }
            }
        }
    }
    return 0;
}
