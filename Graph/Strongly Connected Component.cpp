// 1 based indexing
// Step 1:  Topsort All the nodes
// Step 2:  Run DFS from the unvisited nodes in topsorted order.
//          This will mark the component related to the node.

const int MAX = ?
vector <int> ed[MAX], tr[MAX];
int where[MAX]; // component number of node i
bool vis[MAX];
int tot; // total number of components
stack <int> nodes;

void topSort(int s) {
    vis[s] = 1;
    for(int x : ed[s]) {
        if(!vis[x]) topSort(x);
    }
    nodes.push(s);
}

void markComponent(int s) {
    vis[s] = 1;
    where[s] = tot;
    for(int x : tr[s]) {
        if(!vis[x]) markComponent(x);
    }
}

// finds the SCC for nodes from 1 to n
void SCC(int n) {
    CLR(vis);
    for(int i=1; i<=n; i++) if(!vis[i]) topSort(i);
    tot = 0;
    CLR(vis);
    while(!nodes.empty()) {
        int x = nodes.top();
        nodes.pop();
        if(!vis[x]) {
            tot++;
            markComponent(x);
        }
    }
}
