// Clear ed[]

vector <int> ed[MAX];
vector <pii> res;
bool vis[MAX];
int st[MAX], low[MAX], Time;

void findBridge(int s,int par){
    vis[s] = 1;
    st[s] = low[s] = ++Time;
    for(int x : ed[s]){
        if(!vis[x]){
            findBridge(x,s);
            low[s] = min(low[s],low[x]);
            if(low[x]>st[s]) res.pb(mp(s,x));
        }
        else{
            if(par!=x) low[s] = min(low[s],st[x]);
        }
    }
}

void processBridge(int n){
    Time = 0;
    res.clear(), CLR(vis);
    for(int i=1;i<=n;i++) if(!vis[i]) findBridge(i,-1);
}
