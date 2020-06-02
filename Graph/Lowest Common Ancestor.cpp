// Don't forget to clear ed after test case ends(vt, cost are cleared inside)

#include <bits/stdc++.h>
using namespace std;
const int MAX = 100010;

int LG;
int dep[MAX], par[MAX][21];
vector <int> ed[MAX];

void dfs(int s, int p, int d) {
    dep[s] = d, par[s][0] = p;
    for(int x : ed[s]) {
        if(x == p) continue;
        dfs(x, s, d+1);
    }
}

void preprocess(int root, int n) {
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

int main() {
    int n, u, v;
    cin >> n;
    for(int i=1;i<n;i++) {
        cin >> u >> v;
        ed[u].emplace_back(v);
        ed[v].emplace_back(u);
    }
    preprocess(1, n);
    //getLCA();
    return 0;
}
