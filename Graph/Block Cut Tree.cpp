/***
    * clear ed[],tree[] every test case
    * tot -> total number of components
    * nn -> number of nodes in the Block Cut Tree (<= n + n)
    * bcc[i] contains the nodes of the i'th component
    * any self loop or multiple edge?

    * tree[] is the edge list of BCT
    * Let c be the total number of cut vertices
    * nn = tot + c
    * Nodes([1,tot]) represent the biconnected components
    * Nodes([tot+1,tot+c]) represent the cut vertices

    * There is an edge between node x and y(1 <= x <= tot, tot+1 <= y <= tot+c)
      if cut vertex y is present in bcc[x].

    * If x is NOT a cut vertex, compNum[x] is the index of the bcc[] x is present in
    * If x is a cut vertex, compNum[x]( > tot ) is the index of x in BCT
***/


const int MAX = ?;
vector <int> ed[MAX];
bool cut[MAX];
int tot, Time, low[MAX], st[MAX];
vector <int> bcc[MAX];
stack <int> S;

void popBCC(int s,int x) {
    cut[s] = 1;
    bcc[++tot].pb(s);
    while(bcc[tot].back() ^ x) {
        bcc[tot].pb(S.top());
        S.pop();
    }
}

void dfs(int s, int p = -1) {
    S.push(s);
    int ch = 0;
    st[s] = low[s] = ++Time;
    for(int x : ed[s]) {
        if(!st[x]) {
            ch++;
            dfs(x,s);
            low[s] = min(low[s],low[x]);
            if(p != -1 && low[x] >= st[s]) popBCC(s,x);
            else if(p == -1) if(ch > 1) popBCC(s,x);
        }
        else if(p != x) low[s] = min(low[s],st[x]);
    }
    if(p == -1 && ch > 1) cut[s] = 1;
}


void processBCC(int n) {
    for(int i=1;i<=n;i++) bcc[i].clear();
    CLR(st); CLR(cut);
    Time = tot = 0;
    for(int i=1; i<=n; i++) {
        if(!st[i]) {
            dfs(i,-1);
            if(!S.empty()) ++tot;
            while(!S.empty()) {
                bcc[tot].push_back(S.top());
                S.pop();
            }
        }
    }
}

int nn;
vector <int> tree[MAX + MAX];
int compNum[MAX];

void buildTree(int n) {
    processBCC(n);

    nn = tot;
    for(int i=1;i<=n;i++) if(cut[i]) compNum[i] = ++nn;

    for(int i=1;i<=tot;i++) {
        for(int v : bcc[i]) {
            if(cut[v]) {
                tree[i].pb(compNum[v]);
                tree[compNum[v]].pb(i);
            }
            else compNum[v] = i;
        }
    }
}
