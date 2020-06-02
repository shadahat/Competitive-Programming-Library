// clear ed[] every test case

vector <int> ed[MAX];
bool vis[MAX], cut[MAX];
int st[MAX], low[MAX], Time;

void findArt(int s,int par){
    int ch = 0;
    vis[s] = 1;
    st[s] = low[s] = ++Time;
    for(int x : ed[s]) {
        if(!vis[x]){
            ch++;
            findArt(x,s);
            low[s] = min(low[s],low[x]);
            if(par != -1 && low[x] >= st[s]) cut[s] = 1;
        }
        else if(par != x) low[s] = min(low[s],st[x]);
    }
    if(par == -1 && ch > 1) cut[s] = 1;
}

void processArticulation(int n){
    Time = 0;
    CLR(vis), CLR(cut);
    for(int i=1;i<=n;i++) if(!vis[i]) findArt(i,-1);
}
