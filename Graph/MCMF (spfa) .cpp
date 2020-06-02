/***
    * 1 BASED NODE INDEXING
    * call init at the start of every test case

    * Complexity --> E*Flow (A lot less actually, not sure)

    * Maximizes the flow first, then minimizes the cost

    * The algorithm finds a path with minimum cost to send one unit of flow
      and sends flow over the path as much as possible. Then tries to find
      another path in the residual graph.

    * SPFA Technique :
        The basic idea of SPFA is the same as Bellman Ford algorithm in that each
        vertex is used as a candidate to relax its adjacent vertices. The improvement
        over the latter is that instead of trying all vertices blindly, SPFA maintains
        a queue of candidate vertices and adds a vertex to the queue only if that vertex
        is relaxed. This process repeats until no more vertex can be relaxed.
        This doesn't work if there is a negative cycle in the graph
***/

namespace mcmf {
    using T = int;
    const T INF = ?; /// 0x3f3f3f3f or 0x3f3f3f3f3f3f3f3fLL
    const int MAX = ?; /// maximum number of nodes


    int  n, src, snk;
    T dis[MAX], mCap[MAX];
    int par[MAX], pos[MAX];
    bool vis[MAX];

    struct Edge{
        int to, rev_pos;
        T cap, cost, flow;
    };

    vector <Edge> ed[MAX];

    void init(int _n, int _src, int _snk) {
        n = _n, src = _src, snk = _snk;
        for(int i=1;i<=n;i++) ed[i].clear();
    }

    void addEdge(int u, int v, T cap, T cost){
        Edge a = {v, ed[v].size(), cap, cost, 0};
        Edge b = {u, ed[u].size(), 0, -cost, 0};
        ed[u].pb(a);
        ed[v].pb(b);
    }

    inline bool SPFA(){
        CLR(vis);
        for(int i=1; i<=n; i++) mCap[i] = dis[i] = INF;
        queue <int> q;
        dis[src] = 0;
        vis[src] = true; /// src is in the queue now
        q.push(src);

        while(!q.empty()){
            int u = q.front();
            q.pop();
            vis[u] = false; /// u is not in the queue now
            for(int i=0; i<ed[u].size(); i++) {
                Edge &e = ed[u][i];
                int v = e.to;
                if(e.cap>e.flow && dis[v]>dis[u]+e.cost){
                    dis[v] = dis[u] + e.cost;
                    par[v] = u;
                    pos[v] = i;
                    mCap[v] = min(mCap[u],e.cap-e.flow);
                    if(!vis[v]) {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
        }
        return (dis[snk]!=INF);
    }

    inline pair <T,T> solve() {
        T F = 0, C = 0, f;
        int u, v;
        while(SPFA()){
            u = snk;
            f = mCap[u];
            F += f;
            while(u!=src){
                v = par[u];
                ed[v][pos[u]].flow += f; /// edge of v-->u increases
                ed[u][ed[v][pos[u]].rev_pos].flow -= f;
                u = v;
            }
            C += dis[snk] * f;
        }
        return mp(F,C);
    }
}


Lets say we have filled (p - 1) positions out of n.
a[p - 1] = x

we know that among the unused numbers, s are smaller than x, b are larger than x.

So, p - 1 + s + b = n

So, we are left with s + b number.
Lets mark them -> 1 2 3 4 ... s (s + 1) (s + 2) .... (s + b)

if cur = '<'
dp[p][s][b] = dp[p + 1][s][b - 1]                 // a[p] = s + 1 -> not actual value, marked value
            + dp[p + 1][s + 1][b - 2]             // a[p] = s + 2
            + dp[p + 1][s + 2][b - 3] + ....      // a[p] = s + 3


if cur = '>'
dp[p][s][b] = dp[p + 1][s - 1][b]                 // a[p] = s
            + dp[p + 1][s - 2][b + 1]             // a[p] = s - 1
            + dp[p + 1][s - 3][b + 2] + ....      // a[p] = s - 2

