/***
    * call init at the start of every test case
    * matchL[x] = y means node x of left side is matched to node y of right side
    * matchR[y] = x means node y of right side is matched to node x of left side

    * y is in G[x] if there is an edge between node x and node y
      Node x is in the left and node y is in the right side

    * worst case complexity V*E
***/

namespace bpm{
    const int L = 105;
    const int R = 105;

    vector <int> G[L];
    int matchR[R], matchL[L], vis[L], it;

    /// n = number of nodes in the left side
    void init(int n) {
        SET(matchL), SET(matchR), CLR(vis);
        it = 1;
        for(int i=1;i<=n;i++) G[i].clear();
    }

    inline void addEdge(int u,int v) { G[u].pb(v); }

    bool dfs(int s) {
        vis[s] = it;
        for(auto x : G[s]) {
            if( matchR[x] == -1 or (vis[matchR[x]] != it and dfs(matchR[x])) ) {
                matchL[s] = x; matchR[x] = s;
                return true;
            }
        }
        return false;
    }

    int solve() {
        int cnt = 0;
        for(int i=1;i<=n;i++) {
            if(dfs(i)) cnt++, it++;
        }
        return cnt;
    }
}
