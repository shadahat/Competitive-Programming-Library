/***
    * N = maximum possible string size
    * There won't be more that 2N - 1 nodes
    * There won't be more that 3N - 4 transitions
    * nodes are numbered from 0 to sz-1

    * scan sa::str
    * n = strlen(str)
    * call sa::build(n)

    * let's suppose sub_n represents the largest substring that is endpos equivalent to node n

    * cnt[i] = number of occurrences of sub_i in str
    * If terminal[i] = true, then sub_i is a suffix of str
    * There suffix link of node x to node y,
      Iff sub_y is the largest suffix of sub_x that is not endpos equivalent to node x.
***/
namespace sa{
    const int MAXN = 100005 << 1; /// 2 * maximum possible string size
    const int MAXC = 26; /// Size of the character set

    char str[MAXN];

    int n, sz, last; /// sz = number of nodes in the automaton( node indexing is 0 based)
    int len[MAXN], link[MAXN], ed[MAXN][MAXC], cnt[MAXN];
    bool terminal[MAXN];
    vector <int> G[MAXN];

    void init() {
        SET(ed[0]);
        len[0] = 0, link[0] = -1, sz = 1, last = 0, terminal[0] = false;
    }

    inline int scale(char c) { return c-'a'; }

    void extend(char c) {
        int cur = sz++;

        terminal[cur] = false;
        cnt[cur] = 1;

        SET(ed[cur]);
        len[cur] = len[last] + 1;
        int p = last;
        while (p != -1 && ed[p][c]==-1) {
            ed[p][c] = cur;
            p = link[p];
        }
        if (p == -1) link[cur] = 0;
        else {
            int q = ed[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int clone = sz++;
                len[clone] = len[p] + 1;
                memcpy(ed[clone],ed[q],sizeof(ed[q]));
                link[clone] = link[q];
                while (p != -1 && ed[p][c] == q) {
                    ed[p][c] = clone;
                    p = link[p];
                }
                link[q] = link[cur] = clone;

                cnt[clone] = 0;
                terminal[clone] = false;
            }
        }
        last = cur;
    }

    /// needed to generate cnt[]
    void dfs(int s) {
        for(auto x : G[s]) dfs(x), cnt[s] += cnt[x];
    }

    void build() {
        init();
        int n = strlen(str);
        for(int i=0;i<n;i++) extend(scale(str[i]));

        /// construction of cnt[]
        for(int i=1;i<sz;i++) G[link[i]].pb(i);
        dfs(0);
        for(int i=0;i<sz;i++) G[i].clear();

        /// construction of terminal[]
        for(int i=last;i!=-1;i=link[i]) terminal[i] = true;
    }
}
