/*
Let A be a subset of nodes of a tree T. Then, the auxiliary tree of A contains the nodes
" A U {LCA(x,y) | x,y element of A} " */

// Don't forget to clear ed everything after test case ends(vt, cost are cleared inside)

#include <bits/stdc++.h>
using namespace std;

#define un(x)           x.erase(unique(all(x)), x.end())
#define all(v)          v.begin(),v.end()

const int MAX = 10;

int LG, ptr;
int dep[MAX], in[MAX], par[MAX][21], stk[MAX];
vector <int> ed[MAX], vt[MAX], cost[MAX];

void dfs(int s, int p, int d) {
    dep[s] = d, par[s][0] = p, in[s] = ++ptr;
    for(int x : ed[s]) {
        if(x == p) continue;
        dfs(x, s, d+1);
    }
}

void preprocess(int root, int n) {
    ptr = 0;
    LG = __lg(n);
    memset(par, -1, sizeof(par));
    dfs(root, -1, 0);

    for(int j=1;j<=LG;j++) {
        for(int i=1;i<=n;i++) {
            if(par[i][j-1] != -1) par[i][j] = par[par[i][j-1]][j-1];
        }
    }
}


int getLCA(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i=LG;i>=0;i--) {
        if(dep[u] - (1<<i) >= dep[v]) u = par[u][i];
    }
    if(u == v) return u;
    for(int i=LG;i>=0;i--) {
        if (par[u][i] != -1 and par[u][i] - par[v][i]) {
            u = par[u][i], v = par[v][i];
        }
    }
    return par[u][0];
}

inline void addEdge(int u, int v) {
    int w = abs(dep[u] - dep[v]);
    vt[u].emplace_back(v);
    cost[u].emplace_back(w);
//    vt[v].emplace_back(u);
//    cost[v].emplace_back(w);
}

bool cmp(int a, int b) { return in[a] < in[b]; }
// returns root of the virtual tree and builds the directed edge list 'vt'
int buildTree(vector <int> &nodes) {
    assert(nodes.size() != 0);
    int sz = nodes.size();
    sort(all(nodes), cmp);
    for(int i = 1; i < sz; i++) nodes.emplace_back(getLCA(nodes[i-1], nodes[i]));
    sort(all(nodes), cmp);
    un(nodes);
    for(int e : nodes) vt[e].clear();
    int root = nodes[0];
    vector <int> st;
    for(int e : nodes) {
        while(!st.empty() and getLCA(st.back(), e) != st.back()) st.pop_back();
        if(!st.empty()) addEdge(st.back(), e);
        st.emplace_back(e);
    }
    return root;
}

int main() {
//    freopen("in.txt", "r", stdin);
    int n, m, u, v;
    cin >> n;
    for(int i=1;i<n;i++) {
        cin >> u >> v;
        ed[u].emplace_back(v);
        ed[v].emplace_back(u);
    }
    preprocess(1, n);
    cin >> m;
    vector <int> nodes(m);
    for (int i = 0; i < m; ++i) cin >> nodes[i];
    int root = buildTree(nodes);
    // nodes now contain all the nodes in the virtual tree
    for (int u : nodes) {
        cout << u << " --> ";
        for (int v : vt[u]) cout << v << " "; cout << '\n';
    }
    return 0;
}

/*

Input
7
1 2
1 3
2 4
2 5
3 6
3 7
3
2 3 7

Output
2 --> 1
3 --> 1 7
7 --> 3
1 --> 2 3
*/

