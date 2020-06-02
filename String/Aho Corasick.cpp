/***
    Given n patterns and a text T, for every pattern
    you have to output the number of times that pattern
    appears in the text.

    * Don't forget to call build() after adding all the patterns
      to the Aho Corasick trie.

    * ans[i] contains the number of occurrences of the i'th pattern

    * link[x] = y means there is a suffix link from node x to node y

    * out_link[x] = y means we can go from x to y using the suffix links
      suppose the path is as follows : x , a , b, c, ..., y
      No pattern ends in node a, b, c, ... but some pattern ends at node y.

    * After a call to build(), the trie becomes a DAG(except node 0)
      next[x][c] = y means if we are currently at node x and the character
      c arrives, we will go to node y.


    * Suppose sum of the length of the characters is N. Text length is also
      at most N. If all the patterns are unique, total number of occurrences
      of all the patterns will not be more than " N sqrt(N) ".
***/

#include <bits/stdc++.h>

using namespace std;

struct AC {
    int N, P;
    const int A = 26;
    vector < vector <int> > next;
    vector <int> link, out_link;
    vector < vector <int> > out;
    vector < int > cnt;
    vector < vector <int> > ed;
    vector <int> ans;

    AC(): N(0), P(0) { node(); }

    int node() {
        next.emplace_back(A, 0);
        link.emplace_back(0);
        out.emplace_back(0);
        out_link.emplace_back(0);
        cnt.emplace_back(0);
        ed.emplace_back(0);
        return N++;
    }

    void clear() {
        next.clear(), link.clear(), out.clear() , out_link.clear(), ed.clear();
        cnt.clear(), ans.clear();
        N = P = 0;
        node();
    }

    inline int get(char c) { return c - 'a'; }

    void insert(const string &T) {
        int u = 0;
        for (char c : T) {
            if (!next[u][get(c)]) next[u][get(c)] = node();
            u = next[u][get(c)];
        }
        out[u].push_back(P);
        ans.push_back(0);
        P++;
    }

    void build() {
        queue <int> q;
        for (q.push(0); !q.empty(); ) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < A; ++c) {
                int v = next[u][c];
                if (!v) next[u][c] = next[link[u]][c];
                else {
                    link[v] = u ? next[link[u]][c] : 0;
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    ed[link[v]].push_back(v);
                    q.push(v);
                }
            }
        }
    }

    void dfs(int s) {
        for(int x : ed[s]) dfs(x), cnt[s] += cnt[x];
        for(int e : out[s]) ans[e] = cnt[s];
    }

    void traverse(const string &S) {
        int u = 0;
        for (char c : S) {
            u = next[u][get(c)];
            cnt[u]++;
        }
        dfs(0);
    }
};

char str[1000010], pat[505];

int main() {
//    freopen("in.txt","r",stdin);

    AC aho;
    int t,T;
    scanf("%d",&T);
    for(int t=1;t<=T;t++) {
        int n;
        scanf("%d",&n);
        scanf("%s",str);
        for(int i=1;i<=n;i++) {
            scanf("%s",pat);
            aho.insert(pat);
        }
        aho.build();
        aho.traverse(str);
        printf("Case %d:\n",t);
        for(int i=0;i<n;i++) {
            printf("%d\n",aho.ans[i]);
        }
        aho.clear();
    }
    return 0;
}

