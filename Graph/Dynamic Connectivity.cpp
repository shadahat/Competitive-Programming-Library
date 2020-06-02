#include <bits/stdc++.h>
using namespace std;

/*  Problem
    + u v -> add edge (u, v) to the graph.
    - u v -> remove edge (u, v) from the graph. Currently it exists
    ? -> How may components are in the graph right now
*/


// If there are C queries of type '?'. Then, time interval in consideration is [1, C]
// We build a segment tree over the time interval [1, C]
// Each element lives in the data structure for some segments of time between additions and deletions
// Each survival segment can be broken into log(C) time ranges(check add to tree function)
// For a segment tree node, if l == r, then it denotes a query


struct dsu_save {
    int v, rnkv, u, rnku;
    dsu_save() {}
    dsu_save(int _v, int _rnkv, int _u, int _rnku)
        : v(_v), rnkv(_rnkv), u(_u), rnku(_rnku) {}
};

struct dsu_with_rollbacks {
    vector<int> p, rnk;
    int comps;
    stack <dsu_save> op;

    dsu_with_rollbacks() {}

    dsu_with_rollbacks(int n) {
        p.resize(n + 1);
        rnk.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            p[i] = i;
            rnk[i] = 0;
        }
        comps = n;
    }

    int find_set(int v) {
        return (v == p[v]) ? v : find_set(p[v]);
    }

    bool unite(int v, int u) {
        v = find_set(v);
        u = find_set(u);
        if (v == u) return false;
        comps--;
        if (rnk[v] > rnk[u]) swap(v, u);
        op.push(dsu_save(v, rnk[v], u, rnk[u]));
        p[v] = u;
        if (rnk[u] == rnk[v]) rnk[u]++;
        return true;
    }

    void rollback() {
        if (op.empty()) return;
        dsu_save x = op.top();
        op.pop();
        comps++;
        p[x.v] = x.v;
        rnk[x.v] = x.rnkv;
        p[x.u] = x.u;
        rnk[x.u] = x.rnku;
    }
};

struct edge {
    int v, u;
    bool united;
    edge(int _v, int _u) : v(_v), u(_u) {}
};

struct QueryTree {
    vector < vector <edge> > t;
    dsu_with_rollbacks dsu;
    int T;

    QueryTree() {}

    QueryTree(int _T, int n) : T(_T) {
        dsu = dsu_with_rollbacks(n);
        t.resize(4 * T + 4);
    }

    void add_to_tree(int v, int l, int r, int ul, int ur, edge& q) {
        if (ul > ur)
            return;
        if (l == ul && r == ur) {
            t[v].push_back(q);
            return;
        }
        int mid = (l + r) / 2;
        add_to_tree(2 * v, l, mid, ul, min(ur, mid), q);
        add_to_tree(2 * v + 1, mid + 1, r, max(ul, mid + 1), ur, q);
    }

    void add_edge(edge q, int l, int r) {
        add_to_tree(1, 1, T, l, r, q);
    }

    void dfs(int v, int l, int r, vector<int>& ans) {
        for (edge& q : t[v]) {
            q.united = dsu.unite(q.v, q.u);
        }
        if (l == r)
            ans[l] = dsu.comps;
        else {
            int mid = (l + r) / 2;
            dfs(2 * v, l, mid, ans);
            dfs(2 * v + 1, mid + 1, r, ans);
        }
        for (edge q : t[v]) {
            if (q.united)
                dsu.rollback();
        }
    }

    vector<int> solve() {
        vector<int> ans(T + 1);
        if(T >= 1) dfs(1, 1, T, ans);
        return ans;
    }
};

map <pair <int, int>, int> M;

// edge (u, v) is alive in query range [l, r]
struct event{
    int u, v, l, r;
    event() {}
    event(int _u, int _v, int _l, int _r) : u(_u), v(_v), l(_l), r(_r) {}
};

vector <event> E;

int main() {
    int n, q, u, v;
    string s;
    cin >> n >> q;
    int cnt = 0;
    for(int i=1;i<=q;i++) {
        cin >> s;
        if(s[0] == '+') {
            cin >> u >> v;
            if(u > v) swap(u, v);
            M[make_pair(u, v)] = cnt + 1;
        }
        else if(s[0] == '-') {
            cin >> u >> v;
            if(u > v) swap(u, v);
            E.push_back(event(u, v, M[make_pair(u, v)], cnt));
            M.erase(make_pair(u, v));
        }
        else {
            ++cnt;
        }
    }
    for(auto e : M) E.push_back(event(e.first.first, e.first.second, e.second, cnt));

    QueryTree qt = QueryTree(cnt, n);
    for(auto e : E) qt.add_edge(edge(e.u, e.v), e.l, e.r);
    vector <int> ans = qt.solve();
    for(int i=1;i<=cnt;i++) cout << ans[i] << '\n';    
    return 0;
}

