/***
    Problem :   Given a tree, every vertex has color. Query is how many
                vertices in subtree of vertex v are colored with color c

    A call to dfs(root,-1,0) will process the answer for every query offline
    Only G needs to be cleared per case

    *****************************************************************************
    * If add() is ever called with v = -1, the whole sack becomes empty         *
    * when the execution of add() ends. So, to maintain, any kind of min/max,   *
    * if min/max is update, we don't need to keep track of the previous one.    *
    * If any value is deleted, the min/max will become +/- INF eventually.      *
    *****************************************************************************

***/

const int MAX = 1e5 + 10; /// maximum number of nodes

vector <int> G[MAX]; /// adjacency list of the tree
int sub[MAX]; /// subtree size of a node
int color[MAX]; /// color of a node
int freq[MAX];
int n;

void calcSubSize(int s,int p) {
    sub[s] = 1;
    for(int x : G[s]) {
        if(x==p) continue;
        calcSubSize(x,s);
        sub[s] += sub[x];
    }
}

void add(int s,int p,int v,int bigchild = -1) {
    freq[color[s]] += v;
    for(int x : G[s]) {
        if(x==p || x==bigchild) continue;
        add(x,s,v);
    }
}

void dfs(int s,int p,bool keep) {
    int bigChild = -1;
    for(int x : G[s]) {
        if(x==p) continue;
        if(bigChild==-1 || sub[bigChild] < sub[x] ) bigChild = x;
    }

    for(int x : G[s]) {
        if(x==p || x==bigChild) continue;
        dfs(x,s,0);
    }

    if(bigChild!=-1) dfs(bigChild,s,1);

    add(s,p,1,bigChild);

    /// freq[c] now contains the number of nodes in
    /// the subtree of 'node' that have color  c
    /// Save the answer for the queries here

    if(keep==0)
        add(s,p,-1);
}

int main() {
    input color
    construct G

    calcSubSize(root,-1);
    dfs(root,-1,0);
    return 0;
}
