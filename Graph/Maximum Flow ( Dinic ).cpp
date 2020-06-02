#include <bits/stdc++.h>
using namespace std;
#define CLR(a)          memset(a,0,sizeof(a))
#define SET(a)          memset(a,-1,sizeof(a))

// 1 based indexing (preferred ...)
// call init every test case

namespace dinic {
    using T = int;
    const T INF = 0x3f3f3f3f;
    const int MAXN = 5010;

    int n, src, snk, work[MAXN];
    T dist[MAXN];

    struct Edge{
        int to, rev_pos;
        T c, f;
    };
    vector <Edge> ed[MAXN];

    void init(int _n, int _src, int _snk) {
        n = _n, src = _src, snk = _snk;
        for(int i=0;i<=n;i++) ed[i].clear();
    }

    inline void addEdge(int u, int v, T c, T rc = 0)  {
        Edge a = {v, ed[v].size(), c, 0};
        Edge b = {u, ed[u].size(), rc, 0};
        ed[u].push_back(a);
        ed[v].push_back(b);
    }

    bool dinic_bfs(){
        SET(dist);
        dist[src] = 0;
        queue <int> q;
        q.push(src);
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(Edge &e : ed[u]){
                if(dist[e.to] == -1 and e.f < e.c){
                    dist[e.to] = dist[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return (dist[snk]>=0);
    }

    T dinic_dfs(int u, T fl){
        if (u == snk) return fl;
        for (; work[u] < ed[u].size(); work[u]++){
            Edge &e = ed[u][work[u]];
            if (e.c <= e.f) continue;
            int v = e.to;
            if (dist[v] == dist[u] + 1){
                T df = dinic_dfs(v, min(fl, e.c - e.f));
                if (df > 0){
                    e.f += df;
                    ed[v][e.rev_pos].f -= df;
                    return df;
                }
            }
        }
        return 0;
    }
    T solve() {
        T ret = 0;
        while (dinic_bfs()){
            CLR(work);
            while (T delta = dinic_dfs(src, INF)) ret += delta;
        }
        return ret;
    }
}


int main() {
    int n, m, u, v, c;
    cin >> n >> m;
    dinic::init(n, 1, n);
    while(m--) {
        cin >> u >> v >> c;
        dinic::addEdge(u, v, c, c);
    }
    cout << dinic::solve() << '\n';
    return 0;
}
