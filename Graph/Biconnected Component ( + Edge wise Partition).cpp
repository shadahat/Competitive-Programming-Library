// clear ed[] every test case
// tot -> total number of components
// bccV[i] contains the nodes of the i'th component
// bccE[i] contains the edges of the i'th component
// any self loop or multiple edge?

// Problem : CF962F

const int MAX = ?;
int U[MAX], V[MAX]; // MAX = maximum number of edges
vector <int> ed[MAX];
bool cut[MAX];
int tot, Time, low[MAX], st[MAX];
vector <int> bccV[MAX], bccE[MAX];
stack <int> S;

void popBCC(int e) {
    ++tot;
    while(S.top() != e) bccE[tot].pb(S.top()), S.pop();
    bccE[tot].pb(S.top()), S.pop();
}

void dfs(int s, int p = -1) {
    int ch = 0;
    st[s] = low[s] = ++Time;
    for( int e : ed[s] ) {
        int x = s ^ U[e] ^ V[e];
        if(!st[x]) {
            ch++;
            S.push(e);
            dfs(x,s);
            low[s] = min(low[s],low[x]);
            if(p != -1 and low[x] >= st[s]) cut[s] = 1, popBCC(e);
            else if(p == -1) if(ch > 1) cut[s] = 1, popBCC(e);
        }
        else if(p != x and st[s] > st[x]) {
            low[s] = min(low[s],st[x]);
            S.push(e);
        }
    }
    if(p == -1 && ch > 1) cut[s] = 1;
}

void processBCC(int n) {
    for(int i=1;i<=n;i++) bccV[i].clear(), bccE[i].clear();
    CLR(st); CLR(cut);
    Time = tot = 0;
    for(int i=1; i<=n; i++) {
        if(!st[i]) {
            dfs(i,-1);
            if(!S.empty()) ++tot;
            while(!S.empty()) bccE[tot].push_back(S.top()), S.pop();
        }
    }
    for(int i=1;i<=tot;i++) {
        for(int e : bccE[i]) {
            bccV[i].pb(U[e]);
            bccV[i].pb(V[e]);
        }
    }
    for(int i=1;i<=tot;i++) {
        sort(all(bccV[i]));
        un(bccV[i]);
    }
}

int main() {
    int n, m;
    sii(n, m);
    for(int i=1;i<=m;i++) {
        sii(U[i],V[i]);
        ed[U[i]].pb(i);
        ed[V[i]].pb(i);
    }
    processBCC(n);
    vector <int> ans;
    for(int i=1;i<=tot;i++) {
        if(bccV[i].size() == bccE[i].size()) for(int e : bccE[i]) ans.pb(e);
    }
    sort(all(ans));
    printf("%d\n",ans.size());
    for(int v : ans) printf("%d ",v);
    puts("");
    return 0;
}
