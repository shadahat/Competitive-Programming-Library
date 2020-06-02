/***
    1 based indexing

    call to processBridge(node,edges) generates bridge tree
    and the edge list of that is brTree

    Clear ed , isBridge , brTree per test case
***/

const int MAXN = ?;
const int MAXE = ?;

struct edges {
    int u,v;
} ara[MAXE];

vector <int> ed[MAXN]; /// actual graph
vector <int> isBridge[MAXN]; /// if the edge is a bridge, the entry will be 1
vector <int> brTree[MAXN]; /// edges of the bridge tree

bool vis[MAXN];
int st[MAXN], low[MAXN], Time = 0;
int cnum; /// number of nodes in bridge tree
int comp[MAXN];

void findBridge(int s,int par) {
    int i,x,child = 0,j;
    vis[s] = 1;
    Time++;
    st[s] = low[s] = Time;
    for(i=0; i<ed[s].size(); i++) {
        x = ed[s][i];
        if(!vis[x]) {
            child++;
            findBridge(x,s);
            low[s] = min(low[s],low[x]);
            if(low[x] > st[s]) {
                isBridge[s][i] = 1;
                j = lower_bound(ed[x].begin(),ed[x].end(),s)-ed[x].begin();
                isBridge[x][j] = 1;
            }
        }
        else if(par!=x)
            low[s] = min(low[s],st[x]);
    }
}

void dfs(int s) {
    int i,x;
    vis[s] = 1;
    comp[s] = cnum;
    for(i=0; i<ed[s].size(); i++) {
        if(!isBridge[s][i]) {
            x = ed[s][i];
            if(!vis[x]) dfs(x);
        }
    }
}

void processBridge(int n,int m) {
    CLR(vis);
    Time = 0;
    for(int i=1; i<=n; i++) if(!vis[i]) findBridge(i,-1);

    cnum = 0;
    CLR(vis);
    for(int i=1; i<=n; i++) {
        if(!vis[i]) {
            cnum++;
            dfs(i);
        }
    }

    n = cnum; ///number of nodes in the bridge tree

    for(int i=1; i<=m; i++) {
        if(comp[ara[i].u] != comp[ara[i].v]) {
            brTree[comp[ara[i].u]].pb(comp[ara[i].v]);
            brTree[comp[ara[i].v]].pb(comp[ara[i].u]);
        }
    }
}



int main() {
    int n,m,u,v;
    scanf("%d %d",&n,&m);
    for(int i=1; i<=m; i++) {
        sii(u,v);

        ed[u].pb(v);
        ed[v].pb(u);

        isBridge[u].pb(0);
        isBridge[v].pb(0);

        ara[i].u = u;
        ara[i].v = v;
    }
    for(int i=1; i<=n; i++) sort(all(ed[i]));
    processBridge(n,m);
    return 0;
}

