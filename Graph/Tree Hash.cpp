#include <bits/stdc++.h>
using namespace std;

typedef pair <int,int> pii;

#define xx              first
#define yy              second
#define pb              push_back
#define all(v)          v.begin(),v.end()

const int N = 300010;

pii base = {982451653, 984516781};
pii mod = {1067737007, 1069815139};

inline int add(int a, int b, int m) { return a + b >= m ? a + b - m : a + b; }
inline int sub(int a, int b, int m) { return a - b < 0 ? a - b + m : a - b; }
inline int mul(int a, int b, int m) { return (a * 1LL * b) % m; }
inline pii mul(pii a, pii b) { return make_pair(mul(a.xx, b.xx, mod.xx), mul(a.yy, b.yy, mod.yy)); }
inline pii add(pii a, pii b) { return make_pair(add(a.xx, b.xx, mod.xx), add(a.yy, b.yy, mod.yy)); }
inline pii sub(pii a, pii b) { return make_pair(sub(a.xx, b.xx, mod.xx), sub(a.yy, b.yy, mod.yy)); }

int n;

// The parent of root must be 0
// Node Numbering 1 based

vector <int> ed[N];
int sz[N];
pii h[N]; // hash of it's subtree for a fixed root
pii hsh[N]; // hash of whole tree when node i is root
pii pw[N + N]; // base ^ i

void pre() {
    pw[0] = make_pair(1, 1);
    for(int i=1;i<N+N;i++) pw[i] = mul(pw[i - 1], base);
}

bool cmp(int a, int b) { return h[a] < h[b]; }

void dfs(int s, int p) {
    sz[s] = 1;
    for(int x : ed[s]) {
        if(x == p) continue;
        dfs(x, s);
        sz[s] += sz[x];
    }
    sort(all(ed[s]), cmp);
    h[s] = {1, 1};
    for(int x : ed[s]) {
        if(x == p) continue;
        h[s] = mul(h[s], pw[sz[x] + sz[x]]);
        h[s] = add(h[s], h[x]);
    }
    h[s] = mul(h[s], base);
    h[s] = add(h[s], make_pair(2, 2));
}

void go(int s, int p, pii hp) {
    int sszp = sz[p]; pii shp = h[p];
    h[p] = hp;
    sz[p] = n - sz[s];
    sort(ed[s].begin(), ed[s].end(), cmp);

    pii cur = make_pair(1, 1);
    for(int e : ed[s]) {
        cur = mul(cur, pw[sz[e] + sz[e]]);
        cur = add(cur, h[e]);
    }
    cur = mul(cur, base);
    cur = add(cur, make_pair(2, 2));
    
    hsh[s] = cur;

    vector <pii> suff(ed[s].size());
    vector <int> len(ed[s].size());
    int cl = 1;
    cur = make_pair(2, 2);

    for(int i=(int)ed[s].size()-1;i>=0;i--) {
        int e = ed[s][i];
        cur = add(cur, mul(h[e], pw[cl]));
        cl += sz[e] + sz[e];
        suff[i] = cur;
        len[i] = cl;
    }
    suff.push_back(make_pair(2, 2));
    len.push_back(1);

    cur = make_pair(1, 1);
    for(int i=0;i<ed[s].size();i++) {
        int e = ed[s][i];
        if(e - p) {
            pii tmp = add(suff[i + 1], mul(cur, pw[len[i + 1]]));
            go(e, s, tmp);
        }
        cur = mul(cur, pw[sz[e] + sz[e]]);
        cur = add(cur, h[e]);
    }
    h[p] = shp;
    sz[p] = sszp;
}

int main() {
    pre();
    int a, b;
    cin >> n;
    for(int i=1;i<n;i++) {
        cin >> a >> b;
        ed[a].pb(b);
        ed[b].pb(a);
    }
    dfs(1, -1);
    go(1, -1, {0, 0});
    return 0;
}
