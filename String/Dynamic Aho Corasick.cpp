/***
    Suppose you have a list of strings(initially empty)
    There will be some queries.
    Query --> t s

    If t == 1, add s to your list

    else, print the total occurrences of all the
    strings of your list in s.
***/

#include <bits/stdc++.h>
using namespace std;

const int MAX = ?; /// maximum possible size of an input string

struct AC {
    int N, P;
    const int A = 26;
    vector < vector <int> > next;
    vector <int> link, out_link;
    vector < vector <int> > out;
    vector < int > prefSum;
    vector <string> pat;

    AC(): N(0), P(0) { node(); }

    int node() {
        next.emplace_back(A, 0);
        link.emplace_back(0);
        out.emplace_back(0);
        out_link.emplace_back(0);
        prefSum.emplace_back(0);
        return N++;
    }

    void clear() {
        next.clear(), link.clear(), out.clear() , out_link.clear();
        prefSum.clear();
        pat.clear();
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
        pat.push_back(T);
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
                    prefSum[v] = prefSum[link[v]] + out[v].size();
                    q.push(v);
                }
            }
        }
    }

    long long query(const string &S) {
        long long ret = 0;
        int u = 0;
        for (char c : S) {
            u = next[u][get(c)];
            ret += prefSum[u];
        }
        return ret;
    }
};

const int LOG = 23; /// log2(Total number of patterns)

///dynamic aho-corasick
struct DAC {
    AC aho[LOG];

    void insert(const string &S) {
        int pos;
        for(pos = 0; pos < LOG; pos++) if( aho[pos].P == 0 ) break;

        aho[pos].insert(S);
        for(int i=0;i<pos;i++) {
            for(string &cur : aho[i].pat) aho[pos].insert(cur);
            aho[i].clear();
        }
        aho[pos].build();
    }

    long long query(const string &S) {
        long long ret = 0;
        for(int i=0;i<LOG;i++)
            ret += aho[i].query(S);
        return ret;
    }
};

char str[MAX];

int main() {
    int n, x;
    scanf("%d",&n);
    DAC aho;
    for(int i=0;i<n;i++) {
        scanf("%d %s",&x,str);
        if(x == 1) {
            aho.insert(str);
        }
        else {
            printf("%lld\n",aho.query(str));
            fflush(stdout);
        }
    }
    return 0;
}
